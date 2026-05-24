#define _POSIX_C_SOURCE 200809L

#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <openssl/evp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#define LATTICRA_SEAL_VERSION "v0.3-dev"
#define MANIFEST_PATH "latticra.seal"
#define REPORT_DIR "reports"
#define REPORT_PATH "reports/latticra-seal-cli-report.txt"
#define HASH_LIST_PATH "reports/latticra-seal-cli-hashes.txt"
#define BASELINE_PATH "latticra.seal.lock"

typedef struct {
    int failures;
    int warnings;
    FILE *report;
} SealRun;

typedef struct {
    char **items;
    size_t len;
    size_t cap;
} PathList;

typedef struct {
    char *hash;
    char *path;
} HashEntry;

typedef struct {
    HashEntry *items;
    size_t len;
    size_t cap;
} HashList;

static char *xstrdup(const char *s) {
    size_t n = strlen(s) + 1;
    char *out = malloc(n);

    if (!out) {
        return NULL;
    }

    memcpy(out, s, n);
    return out;
}

static bool file_exists(const char *path) {
    struct stat st;
    return stat(path, &st) == 0 && S_ISREG(st.st_mode);
}

static void ensure_report_dir(void) {
    if (mkdir(REPORT_DIR, 0755) != 0 && errno != EEXIST) {
        fprintf(stderr, "warning: could not create %s\n", REPORT_DIR);
    }
}

static const char *visible_path(const char *path) {
    if (path[0] == '.' && path[1] == '/') {
        return path + 2;
    }

    return path;
}

static char *read_file(const char *path) {
    FILE *f = fopen(path, "rb");

    if (!f) {
        return NULL;
    }

    if (fseek(f, 0, SEEK_END) != 0) {
        fclose(f);
        return NULL;
    }

    long size = ftell(f);

    if (size < 0) {
        fclose(f);
        return NULL;
    }

    rewind(f);

    char *buf = calloc((size_t)size + 1, 1);

    if (!buf) {
        fclose(f);
        return NULL;
    }

    size_t read_count = fread(buf, 1, (size_t)size, f);
    fclose(f);

    if (read_count != (size_t)size) {
        free(buf);
        return NULL;
    }

    buf[size] = '\0';
    return buf;
}

static void emit(SealRun *run, const char *line) {
    puts(line);

    if (run && run->report) {
        fputs(line, run->report);
        fputc('\n', run->report);
    }
}

static void section(SealRun *run, const char *name) {
    char line[256];
    snprintf(line, sizeof(line), "\n== %s ==", name);
    emit(run, line);
}

static void pass(SealRun *run, const char *msg) {
    char line[1024];
    snprintf(line, sizeof(line), "PASS: %s", msg);
    emit(run, line);
}

static void warn_run(SealRun *run, const char *msg) {
    char line[1024];

    if (run) {
        run->warnings++;
    }

    snprintf(line, sizeof(line), "WARN: %s", msg);
    emit(run, line);
}

static void fail_run(SealRun *run, const char *msg) {
    char line[1024];

    if (run) {
        run->failures++;
    }

    snprintf(line, sizeof(line), "FAIL: %s", msg);
    emit(run, line);
}

static bool pathlist_push(PathList *list, const char *path) {
    if (list->len == list->cap) {
        size_t next_cap = list->cap == 0 ? 64 : list->cap * 2;
        char **next = realloc(list->items, next_cap * sizeof(char *));

        if (!next) {
            return false;
        }

        list->items = next;
        list->cap = next_cap;
    }

    list->items[list->len] = xstrdup(path);

    if (!list->items[list->len]) {
        return false;
    }

    list->len++;
    return true;
}

static void pathlist_free(PathList *list) {
    for (size_t i = 0; i < list->len; i++) {
        free(list->items[i]);
    }

    free(list->items);
    list->items = NULL;
    list->len = 0;
    list->cap = 0;
}

static int cmp_string_ptr(const void *a, const void *b) {
    const char *const *pa = a;
    const char *const *pb = b;
    return strcmp(*pa, *pb);
}

static const char *basename_of(const char *path) {
    const char *slash = strrchr(path, '/');

    if (!slash) {
        return path;
    }

    return slash + 1;
}

static bool ends_with(const char *s, const char *suffix) {
    size_t a = strlen(s);
    size_t b = strlen(suffix);

    if (b > a) {
        return false;
    }

    return strcmp(s + a - b, suffix) == 0;
}

static bool excluded_dir_name(const char *name) {
    return strcmp(name, ".git") == 0 ||
           strcmp(name, "target") == 0 ||
           strcmp(name, "build") == 0 ||
           strcmp(name, "dist") == 0 ||
           strcmp(name, "node_modules") == 0 ||
           strcmp(name, ".venv") == 0 ||
           strcmp(name, "__pycache__") == 0 ||
           strcmp(name, "reports") == 0;
}

static bool excluded_file_name(const char *path) {
    const char *name = basename_of(path);

    return strcmp(name, "latticra.seal.lock") == 0 ||
           ends_with(name, ".log") ||
           ends_with(name, ".tmp") ||
           strcmp(name, ".DS_Store") == 0;
}

static void collect_files(SealRun *run, PathList *list, const char *dir_path) {
    DIR *dir = opendir(dir_path);

    if (!dir) {
        char msg[512];
        snprintf(msg, sizeof(msg), "could not open directory: %s", dir_path);
        warn_run(run, msg);
        return;
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char path[PATH_MAX];

        int n = snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);

        if (n < 0 || (size_t)n >= sizeof(path)) {
            warn_run(run, "skipped path because it was too long");
            continue;
        }

        struct stat st;

        if (lstat(path, &st) != 0) {
            char msg[512];
            snprintf(msg, sizeof(msg), "could not stat path: %s", path);
            warn_run(run, msg);
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            if (!excluded_dir_name(entry->d_name)) {
                collect_files(run, list, path);
            }

            continue;
        }

        if (S_ISREG(st.st_mode)) {
            if (!excluded_file_name(path)) {
                if (!pathlist_push(list, path)) {
                    fail_run(run, "out of memory while collecting file paths");
                    closedir(dir);
                    return;
                }
            }
        }
    }

    closedir(dir);
}

static bool sha256_file(const char *path, char out_hex[65]) {
    bool ok = false;
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int digest_len = 0;
    unsigned char buf[8192];

    FILE *f = fopen(path, "rb");

    if (!f) {
        return false;
    }

    EVP_MD_CTX *ctx = EVP_MD_CTX_new();

    if (!ctx) {
        fclose(f);
        return false;
    }

    if (EVP_DigestInit_ex(ctx, EVP_sha256(), NULL) != 1) {
        goto done;
    }

    for (;;) {
        size_t n = fread(buf, 1, sizeof(buf), f);

        if (n > 0) {
            if (EVP_DigestUpdate(ctx, buf, n) != 1) {
                goto done;
            }
        }

        if (n < sizeof(buf)) {
            if (ferror(f)) {
                goto done;
            }

            break;
        }
    }

    if (EVP_DigestFinal_ex(ctx, digest, &digest_len) != 1) {
        goto done;
    }

    if (digest_len != 32) {
        goto done;
    }

    for (unsigned int i = 0; i < digest_len; i++) {
        snprintf(out_hex + (i * 2), 3, "%02x", digest[i]);
    }

    out_hex[64] = '\0';
    ok = true;

done:
    EVP_MD_CTX_free(ctx);
    fclose(f);
    return ok;
}

static void require_manifest_field(
    SealRun *run,
    const char *manifest,
    const char *needle,
    const char *label
) {
    if (strstr(manifest, needle)) {
        pass(run, label);
    } else {
        fail_run(run, label);
    }
}

static void check_manifest_shape(SealRun *run, const char *manifest) {
    section(run, "Manifest shape");

    require_manifest_field(run, manifest, "schema = \"latticra.seal/v0.1\"", "schema is latticra.seal/v0.1");
    require_manifest_field(run, manifest, "format = \"toml\"", "format is TOML-compatible");
    require_manifest_field(run, manifest, "kind = \"local-integrity-manifest\"", "kind is local-integrity-manifest");
    require_manifest_field(run, manifest, "algorithm = \"sha256\"", "hash algorithm is sha256");
    require_manifest_field(run, manifest, "trust_boundary = \"project-root\"", "trust boundary is project-root");
}

static void check_policy_shape(SealRun *run, const char *manifest) {
    section(run, "Policy shape");

    require_manifest_field(run, manifest, "require_readme = true", "policy requires README");
    require_manifest_field(run, manifest, "require_license = true", "policy requires LICENSE");
    require_manifest_field(run, manifest, "deny_private_keys = true", "policy denies private keys");
    require_manifest_field(run, manifest, "deny_env_files = true", "policy denies .env files");
    require_manifest_field(run, manifest, "deny_obvious_tokens = true", "policy denies obvious token markers");
}

static void check_required_files(SealRun *run) {
    section(run, "Required project files");

    if (file_exists("README.md")) {
        pass(run, "README.md exists");
    } else {
        fail_run(run, "README.md is missing");
    }

    if (file_exists("LICENSE")) {
        pass(run, "LICENSE exists");
    } else {
        fail_run(run, "LICENSE is missing");
    }
}

static void write_digest_summary(SealRun *run) {
    section(run, "Digest summary");

    PathList list;
    list.items = NULL;
    list.len = 0;
    list.cap = 0;

    collect_files(run, &list, ".");

    qsort(list.items, list.len, sizeof(char *), cmp_string_ptr);

    FILE *hashes = fopen(HASH_LIST_PATH, "w");

    if (!hashes) {
        fail_run(run, "could not write hash list");
        pathlist_free(&list);
        return;
    }

    size_t hashed_count = 0;

    for (size_t i = 0; i < list.len; i++) {
        char hex[65];

        if (!sha256_file(list.items[i], hex)) {
            char msg[512];
            snprintf(msg, sizeof(msg), "could not hash file: %s", visible_path(list.items[i]));
            fail_run(run, msg);
            continue;
        }

        fprintf(hashes, "%s  %s\n", hex, visible_path(list.items[i]));
        hashed_count++;
    }

    fclose(hashes);

    char manifest_hex[65];
    char root_hex[65];

    if (sha256_file(MANIFEST_PATH, manifest_hex)) {
        char line[160];
        snprintf(line, sizeof(line), "manifest_sha256: %s", manifest_hex);
        emit(run, line);
    } else {
        fail_run(run, "could not hash manifest");
    }

    if (sha256_file(HASH_LIST_PATH, root_hex)) {
        char line[160];
        snprintf(line, sizeof(line), "root_digest_v0_2: %s", root_hex);
        emit(run, line);
    } else {
        fail_run(run, "could not hash digest list");
    }

    char count_line[160];
    snprintf(count_line, sizeof(count_line), "hashed_files: %zu", hashed_count);
    emit(run, count_line);

    emit(run, "hash_list: " HASH_LIST_PATH);

    pathlist_free(&list);
}

static void write_header(SealRun *run) {
    time_t now = time(NULL);
    struct tm *utc = gmtime(&now);
    char stamp[64];

    if (utc) {
        strftime(stamp, sizeof(stamp), "%Y-%m-%dT%H:%M:%SZ", utc);
    } else {
        snprintf(stamp, sizeof(stamp), "unknown-time");
    }

    emit(run, "Latticra Seal CLI Report");
    emit(run, "Version: " LATTICRA_SEAL_VERSION);
    emit(run, "Mode: local-integrity");
    emit(run, stamp);
}

static int finish(SealRun *run) {
    section(run, "Result");

    if (run->failures == 0) {
        emit(run, "STATUS: PASS");
    } else {
        emit(run, "STATUS: FAIL");
    }

    char summary[128];

    snprintf(
        summary,
        sizeof(summary),
        "Failures: %d | Warnings: %d",
        run->failures,
        run->warnings
    );

    emit(run, summary);
    emit(run, "Report written to: " REPORT_PATH);

    return run->failures == 0 ? 0 : 1;
}

static int command_check(void) {
    ensure_report_dir();

    SealRun run;
    run.failures = 0;
    run.warnings = 0;
    run.report = fopen(REPORT_PATH, "w");

    if (!run.report) {
        fprintf(stderr, "could not open report: %s\n", REPORT_PATH);
        return 2;
    }

    write_header(&run);

    section(&run, "Manifest presence");

    if (!file_exists(MANIFEST_PATH)) {
        fail_run(&run, "latticra.seal is missing");
        int code = finish(&run);
        fclose(run.report);
        return code;
    }

    pass(&run, "latticra.seal exists");

    char *manifest = read_file(MANIFEST_PATH);

    if (!manifest) {
        fail_run(&run, "could not read latticra.seal");
        int code = finish(&run);
        fclose(run.report);
        return code;
    }

    check_manifest_shape(&run, manifest);
    check_policy_shape(&run, manifest);
    check_required_files(&run);
    write_digest_summary(&run);

    free(manifest);

    int code = finish(&run);
    fclose(run.report);
    return code;
}

static void print_manifest_value(
    const char *manifest,
    const char *key,
    const char *label
) {
    char pattern[128];
    snprintf(pattern, sizeof(pattern), "%s = \"", key);

    const char *start = strstr(manifest, pattern);

    if (!start) {
        printf("%s: missing\n", label);
        return;
    }

    start += strlen(pattern);

    const char *end = strchr(start, '"');

    if (!end || end <= start) {
        printf("%s: malformed\n", label);
        return;
    }

    printf("%s: %.*s\n", label, (int)(end - start), start);
}

static int command_manifest(void) {
    char *manifest = read_file(MANIFEST_PATH);

    if (!manifest) {
        fprintf(stderr, "could not read %s\n", MANIFEST_PATH);
        return 1;
    }

    puts("Latticra Seal Manifest Summary");
    puts("------------------------------");

    print_manifest_value(manifest, "schema", "Schema");
    print_manifest_value(manifest, "kind", "Kind");
    print_manifest_value(manifest, "name", "Project");
    print_manifest_value(manifest, "version", "Project Version");
    print_manifest_value(manifest, "mode", "Seal Mode");
    print_manifest_value(manifest, "status", "Seal Status");
    print_manifest_value(manifest, "algorithm", "Digest Algorithm");
    print_manifest_value(manifest, "trust_boundary", "Trust Boundary");

    free(manifest);
    return 0;
}



static bool files_equal(const char *a, const char *b);

static void strip_newline(char *s) {
    size_t n = strlen(s);

    while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r')) {
        s[n - 1] = '\0';
        n--;
    }
}

static bool hashlist_push(HashList *list, const char *hash, const char *path) {
    if (list->len == list->cap) {
        size_t next_cap = list->cap == 0 ? 64 : list->cap * 2;
        HashEntry *next = realloc(list->items, next_cap * sizeof(HashEntry));

        if (!next) {
            return false;
        }

        list->items = next;
        list->cap = next_cap;
    }

    list->items[list->len].hash = xstrdup(hash);
    list->items[list->len].path = xstrdup(path);

    if (!list->items[list->len].hash || !list->items[list->len].path) {
        free(list->items[list->len].hash);
        free(list->items[list->len].path);
        return false;
    }

    list->len++;
    return true;
}

static void hashlist_free(HashList *list) {
    for (size_t i = 0; i < list->len; i++) {
        free(list->items[i].hash);
        free(list->items[i].path);
    }

    free(list->items);
    list->items = NULL;
    list->len = 0;
    list->cap = 0;
}

static int cmp_hash_entry_path(const void *a, const void *b) {
    const HashEntry *ea = a;
    const HashEntry *eb = b;
    return strcmp(ea->path, eb->path);
}


static bool read_hash_list(const char *path, HashList *list) {
    FILE *f = fopen(path, "r");

    if (!f) {
        return false;
    }

    char line[8192];

    while (fgets(line, sizeof(line), f)) {
        strip_newline(line);

        if (strlen(line) < 67) {
            continue;
        }

        char hash[65];
        memcpy(hash, line, 64);
        hash[64] = '\0';

        char *file_path = line + 64;

        while (*file_path == ' ' || *file_path == '\t') {
            file_path++;
        }

        if (*file_path == '\0') {
            continue;
        }

        if (!hashlist_push(list, hash, file_path)) {
            fclose(f);
            return false;
        }
    }

    fclose(f);

    qsort(list->items, list->len, sizeof(HashEntry), cmp_hash_entry_path);
    return true;
}

static void emit_change(SealRun *run, const char *kind, const char *path) {
    printf("%s: %s\n", kind, path);

    if (run && run->report) {
        fprintf(run->report, "%s: %s\n", kind, path);
    }
}


static void compare_hash_lists_report(
    SealRun *run,
    const char *baseline_path,
    const char *current_path
) {
    if (files_equal(current_path, baseline_path)) {
        pass(run, "current file hashes match saved baseline");
        return;
    }

    HashList baseline;
    HashList current;

    baseline.items = NULL;
    baseline.len = 0;
    baseline.cap = 0;

    current.items = NULL;
    current.len = 0;
    current.cap = 0;

    if (!read_hash_list(baseline_path, &baseline)) {
        fail_run(run, "could not read saved baseline");
        return;
    }

    if (!read_hash_list(current_path, &current)) {
        hashlist_free(&baseline);
        fail_run(run, "could not read current hash list");
        return;
    }

    size_t i = 0;
    size_t j = 0;
    size_t changes = 0;

    while (i < baseline.len || j < current.len) {
        if (i >= baseline.len) {
            emit_change(run, "ADDED", current.items[j].path);
            changes++;
            j++;
            continue;
        }

        if (j >= current.len) {
            emit_change(run, "REMOVED", baseline.items[i].path);
            changes++;
            i++;
            continue;
        }

        int cmp = strcmp(baseline.items[i].path, current.items[j].path);

        if (cmp == 0) {
            if (strcmp(baseline.items[i].hash, current.items[j].hash) != 0) {
                emit_change(run, "MODIFIED", current.items[j].path);
                changes++;
            }

            i++;
            j++;
        } else if (cmp < 0) {
            emit_change(run, "REMOVED", baseline.items[i].path);
            changes++;
            i++;
        } else {
            emit_change(run, "ADDED", current.items[j].path);
            changes++;
            j++;
        }
    }

    if (changes == 0) {
        pass(run, "current file hashes match saved baseline");
    } else {
        char summary[160];
        snprintf(summary, sizeof(summary), "saved baseline differs: %zu change(s)", changes);
        fail_run(run, summary);
    }

    hashlist_free(&baseline);
    hashlist_free(&current);
}

static bool copy_file(const char *src, const char *dst) {
    FILE *in = fopen(src, "rb");

    if (!in) {
        return false;
    }

    FILE *out = fopen(dst, "wb");

    if (!out) {
        fclose(in);
        return false;
    }

    unsigned char buf[8192];
    bool ok = true;

    for (;;) {
        size_t n = fread(buf, 1, sizeof(buf), in);

        if (n > 0 && fwrite(buf, 1, n, out) != n) {
            ok = false;
            break;
        }

        if (n < sizeof(buf)) {
            if (ferror(in)) {
                ok = false;
            }

            break;
        }
    }

    if (fclose(out) != 0) {
        ok = false;
    }

    fclose(in);
    return ok;
}

static bool files_equal(const char *a, const char *b) {
    FILE *fa = fopen(a, "rb");

    if (!fa) {
        return false;
    }

    FILE *fb = fopen(b, "rb");

    if (!fb) {
        fclose(fa);
        return false;
    }

    bool equal = true;

    for (;;) {
        int ca = fgetc(fa);
        int cb = fgetc(fb);

        if (ca != cb) {
            equal = false;
            break;
        }

        if (ca == EOF || cb == EOF) {
            break;
        }
    }

    fclose(fa);
    fclose(fb);
    return equal;
}

static int print_file_to_stdout(const char *path, const char *missing_hint) {
    FILE *f = fopen(path, "r");

    if (!f) {
        fprintf(stderr, "no file found at %s\n", path);

        if (missing_hint) {
            fprintf(stderr, "%s\n", missing_hint);
        }

        return 1;
    }

    int ch;

    while ((ch = fgetc(f)) != EOF) {
        putchar(ch);
    }

    fclose(f);
    return 0;
}


static int command_baseline(void) {
    int code = command_check();

    if (code != 0) {
        fprintf(stderr, "baseline refused because check did not pass\n");
        return code;
    }

    if (!copy_file(HASH_LIST_PATH, BASELINE_PATH)) {
        fprintf(stderr, "could not write baseline: %s\n", BASELINE_PATH);
        return 1;
    }

    printf("Baseline written to: %s\n", BASELINE_PATH);
    return 0;
}


static int command_verify(void) {
    ensure_report_dir();

    SealRun run;
    run.failures = 0;
    run.warnings = 0;
    run.report = fopen(REPORT_PATH, "w");

    if (!run.report) {
        fprintf(stderr, "could not open report: %s\n", REPORT_PATH);
        return 2;
    }

    write_header(&run);

    section(&run, "Baseline presence");

    if (!file_exists(BASELINE_PATH)) {
        fail_run(&run, "latticra.seal.lock is missing");
        int code = finish(&run);
        fclose(run.report);
        return code;
    }

    pass(&run, "latticra.seal.lock exists");

    section(&run, "Manifest presence");

    if (!file_exists(MANIFEST_PATH)) {
        fail_run(&run, "latticra.seal is missing");
        int code = finish(&run);
        fclose(run.report);
        return code;
    }

    pass(&run, "latticra.seal exists");

    char *manifest = read_file(MANIFEST_PATH);

    if (!manifest) {
        fail_run(&run, "could not read latticra.seal");
        int code = finish(&run);
        fclose(run.report);
        return code;
    }

    check_manifest_shape(&run, manifest);
    check_policy_shape(&run, manifest);
    check_required_files(&run);
    write_digest_summary(&run);

    free(manifest);

    section(&run, "Baseline comparison");

    if (run.failures == 0) {
        compare_hash_lists_report(&run, BASELINE_PATH, HASH_LIST_PATH);
    } else {
        warn_run(&run, "baseline comparison skipped because earlier checks failed");
    }

    int code = finish(&run);
    fclose(run.report);
    return code;
}

static int command_report(void) {
    return print_file_to_stdout(
        REPORT_PATH,
        "run: ./build/latticra-seal check"
    );
}

static int command_hashes(void) {
    return print_file_to_stdout(
        HASH_LIST_PATH,
        "run: ./build/latticra-seal check"
    );
}

static int command_version(void) {
    puts("latticra-seal " LATTICRA_SEAL_VERSION);
    return 0;
}

static int command_help(void) {
    puts("Latticra Seal");
    puts("");
    puts("Usage:");
    puts("  latticra-seal check");
    puts("  latticra-seal manifest");
    puts("  latticra-seal baseline");
    puts("  latticra-seal verify");
    puts("  latticra-seal report");
    puts("  latticra-seal hashes");
    puts("  latticra-seal version");
    puts("  latticra-seal help");
    puts("");
    puts("Commands:");
    puts("  check      verify manifest, policy, required files, and SHA-256 digests");
    puts("  manifest   print a compact manifest summary");
    puts("  baseline   save the current hash list as latticra.seal.lock");
    puts("  verify     compare current hashes against latticra.seal.lock");
    puts("  report     print the latest generated CLI report");
    puts("  hashes     print the latest generated file hash list");
    puts("  version    print the Seal CLI version");
    puts("  help       show this help message");
    return 0;
}

int main(int argc, char **argv) {
    const char *command = "check";

    if (argc >= 2) {
        command = argv[1];
    }

    if (strcmp(command, "check") == 0) {
        return command_check();
    }

    if (strcmp(command, "manifest") == 0) {
        return command_manifest();
    }

    if (strcmp(command, "baseline") == 0) {
        return command_baseline();
    }

    if (strcmp(command, "verify") == 0) {
        return command_verify();
    }

    if (strcmp(command, "report") == 0) {
        return command_report();
    }

    if (strcmp(command, "hashes") == 0) {
        return command_hashes();
    }

    if (strcmp(command, "version") == 0) {
        return command_version();
    }

    if (
        strcmp(command, "help") == 0 ||
        strcmp(command, "-h") == 0 ||
        strcmp(command, "--help") == 0
    ) {
        return command_help();
    }

    fprintf(stderr, "unknown command: %s\n", command);
    fprintf(stderr, "run: ./build/latticra-seal help\n");
    return 2;
}
