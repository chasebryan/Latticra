#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#define LATTICRA_SEAL_VERSION "v0.1"
#define MANIFEST_PATH "latticra.seal"
#define REPORT_DIR "reports"
#define REPORT_PATH "reports/latticra-seal-cli-report.txt"

typedef struct {
    int failures;
    int warnings;
    FILE *report;
} SealRun;

static bool file_exists(const char *path) {
    struct stat st;
    return stat(path, &st) == 0 && S_ISREG(st.st_mode);
}

static void ensure_report_dir(void) {
    if (mkdir(REPORT_DIR, 0755) != 0 && errno != EEXIST) {
        fprintf(stderr, "warning: could not create %s\n", REPORT_DIR);
    }
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

    if (run->report) {
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
    char line[512];
    snprintf(line, sizeof(line), "PASS: %s", msg);
    emit(run, line);
}

static void warn(SealRun *run, const char *msg) {
    char line[512];
    run->warnings++;
    snprintf(line, sizeof(line), "WARN: %s", msg);
    emit(run, line);
}

static void fail(SealRun *run, const char *msg) {
    char line[512];
    run->failures++;
    snprintf(line, sizeof(line), "FAIL: %s", msg);
    emit(run, line);
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
        fail(run, label);
    }
}

static void check_manifest_shape(SealRun *run, const char *manifest) {
    section(run, "Manifest shape");

    require_manifest_field(
        run,
        manifest,
        "schema = \"latticra.seal/v0.1\"",
        "schema is latticra.seal/v0.1"
    );

    require_manifest_field(
        run,
        manifest,
        "format = \"toml\"",
        "format is TOML-compatible"
    );

    require_manifest_field(
        run,
        manifest,
        "kind = \"local-integrity-manifest\"",
        "kind is local-integrity-manifest"
    );

    require_manifest_field(
        run,
        manifest,
        "algorithm = \"sha256\"",
        "hash algorithm is sha256"
    );

    require_manifest_field(
        run,
        manifest,
        "trust_boundary = \"project-root\"",
        "trust boundary is project-root"
    );
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
        fail(run, "README.md is missing");
    }

    if (file_exists("LICENSE")) {
        pass(run, "LICENSE exists");
    } else {
        fail(run, "LICENSE is missing");
    }
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
        fail(&run, "latticra.seal is missing");
        int code = finish(&run);
        fclose(run.report);
        return code;
    }

    pass(&run, "latticra.seal exists");

    char *manifest = read_file(MANIFEST_PATH);
    if (!manifest) {
        fail(&run, "could not read latticra.seal");
        int code = finish(&run);
        fclose(run.report);
        return code;
    }

    check_manifest_shape(&run, manifest);
    check_policy_shape(&run, manifest);
    check_required_files(&run);

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

static int command_report(void) {
    FILE *f = fopen(REPORT_PATH, "r");

    if (!f) {
        fprintf(stderr, "no report found at %s\n", REPORT_PATH);
        fprintf(stderr, "run: ./build/latticra-seal check\n");
        return 1;
    }

    int ch;
    while ((ch = fgetc(f)) != EOF) {
        putchar(ch);
    }

    fclose(f);
    return 0;
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
    puts("  latticra-seal report");
    puts("  latticra-seal version");
    puts("  latticra-seal help");
    puts("");
    puts("Commands:");
    puts("  check      verify manifest shape, policy shape, and required files");
    puts("  manifest   print a compact manifest summary");
    puts("  report     print the latest generated CLI report");
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

    if (strcmp(command, "report") == 0) {
        return command_report();
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
