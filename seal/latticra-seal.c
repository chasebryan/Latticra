#define _POSIX_C_SOURCE 200809L

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
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
#define REPORT_TMP_PATH "reports/latticra-seal-cli-report.tmp"
#define HASH_LIST_PATH "reports/latticra-seal-cli-hashes.txt"
#define HASH_LIST_TMP_PATH "reports/latticra-seal-cli-hashes.tmp"
#define LEGACY_SMOKE_REPORT_PATH "reports/latticra-seal-report.txt"
#define LEGACY_SMOKE_HASH_LIST_PATH "reports/latticra-seal-file-hashes.txt"
#define BASELINE_PATH "latticra.seal.lock"
#define BASELINE_TMP_PATH "latticra.seal.lock.tmp"

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
    int flags = O_RDONLY;
#ifdef O_CLOEXEC
    flags |= O_CLOEXEC;
#endif
#ifdef O_NOFOLLOW
    flags |= O_NOFOLLOW;
#endif
#ifdef O_NONBLOCK
    flags |= O_NONBLOCK;
#endif

    int fd = open(path, flags);

    if (fd < 0) {
        return false;
    }

    bool ok = fstat(fd, &st) == 0 && S_ISREG(st.st_mode);
    close(fd);
    return ok;
}

static bool ensure_report_dir(void) {
    struct stat st;

    if (lstat(REPORT_DIR, &st) == 0) {
        if (S_ISLNK(st.st_mode)) {
            fprintf(stderr, "refusing symlink report directory: %s\n", REPORT_DIR);
            return false;
        }
        if (!S_ISDIR(st.st_mode)) {
            fprintf(stderr, "refusing non-directory report path: %s\n", REPORT_DIR);
            return false;
        }
        if ((st.st_mode & (S_IWGRP | S_IWOTH)) != 0) {
            fprintf(stderr, "refusing writable report directory: %s\n", REPORT_DIR);
            return false;
        }
        return true;
    }

    if (errno != ENOENT) {
        fprintf(stderr, "could not inspect report directory: %s\n", REPORT_DIR);
        return false;
    }

    if (mkdir(REPORT_DIR, 0700) != 0) {
        fprintf(stderr, "could not create report directory: %s\n", REPORT_DIR);
        return false;
    }

    return true;
}

static FILE *open_regular_file_for_read(const char *path) {
    struct stat st;

    int flags = O_RDONLY;
#ifdef O_CLOEXEC
    flags |= O_CLOEXEC;
#endif
#ifdef O_NOFOLLOW
    flags |= O_NOFOLLOW;
#endif
#ifdef O_NONBLOCK
    flags |= O_NONBLOCK;
#endif

    int fd = open(path, flags);

    if (fd < 0) {
        return NULL;
    }

    if (fstat(fd, &st) != 0 || !S_ISREG(st.st_mode)) {
        close(fd);
        return NULL;
    }

    FILE *file = fdopen(fd, "r");

    if (!file) {
        close(fd);
    }

    return file;
}

static FILE *open_regular_file_for_write(const char *path) {
    struct stat st;

    if (lstat(path, &st) == 0) {
        if (S_ISLNK(st.st_mode) || !S_ISREG(st.st_mode)) {
            return NULL;
        }
    } else if (errno != ENOENT) {
        return NULL;
    }

    int flags = O_WRONLY | O_CREAT | O_TRUNC;
#ifdef O_CLOEXEC
    flags |= O_CLOEXEC;
#endif
#ifdef O_NOFOLLOW
    flags |= O_NOFOLLOW;
#endif
#ifdef O_NONBLOCK
    flags |= O_NONBLOCK;
#endif

    int fd = open(path, flags, 0600);

    if (fd < 0) {
        return NULL;
    }

    if (fstat(fd, &st) != 0 || !S_ISREG(st.st_mode)) {
        close(fd);
        return NULL;
    }

    (void)fchmod(fd, 0600);

    FILE *file = fdopen(fd, "w");

    if (!file) {
        close(fd);
    }

    return file;
}

static bool path_is_regular_or_missing(const char *path) {
    struct stat st;

    if (lstat(path, &st) == 0) {
        return S_ISREG(st.st_mode);
    }

    return errno == ENOENT;
}

static bool unlink_regular_if_present(const char *path) {
    struct stat st;

    if (lstat(path, &st) == 0) {
        if (!S_ISREG(st.st_mode)) {
            return false;
        }

        return unlink(path) == 0;
    }

    return errno == ENOENT;
}

static FILE *open_report_for_write(void) {
    if (!path_is_regular_or_missing(REPORT_PATH)) {
        return NULL;
    }

    return open_regular_file_for_write(REPORT_TMP_PATH);
}

static const char *visible_path(const char *path) {
    if (path[0] == '.' && path[1] == '/') {
        return path + 2;
    }

    return path;
}

static char *read_file(const char *path) {
    FILE *f = open_regular_file_for_read(path);

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
    size_t len = strlen(path);

    if (list->len == list->cap) {
        size_t next_cap = list->cap == 0 ? 64 : list->cap * 2;
        char **next = realloc(list->items, next_cap * sizeof(char *));

        if (!next) {
            return false;
        }

        list->items = next;
        list->cap = next_cap;
    }

    list->items[list->len] = malloc(len + 1);

    if (!list->items[list->len]) {
        return false;
    }

    memcpy(list->items[list->len], path, len + 1);
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

static bool pathlist_has_duplicate_items(const PathList *list) {
    for (size_t i = 0; i < list->len; i++) {
        for (size_t j = i + 1; j < list->len; j++) {
            if (strcmp(list->items[i], list->items[j]) == 0) {
                return true;
            }
        }
    }

    return false;
}

static bool string_has_control_or_backslash(const char *s) {
    for (const unsigned char *p = (const unsigned char *)s; *p != '\0'; p++) {
        if (*p < 32 || *p == 127 || *p == '\\') {
            return true;
        }
    }

    return false;
}

static bool has_more_than_one_wildcard(const char *s) {
    const char *first = strchr(s, '*');

    return first && strchr(first + 1, '*') != NULL;
}

static bool path_has_forbidden_segments(const char *path, bool allow_trailing_slash) {
    const char *p = path;

    for (;;) {
        const char *slash = strchr(p, '/');
        size_t segment_len = slash ? (size_t)(slash - p) : strlen(p);

        if (segment_len == 0) {
            if (allow_trailing_slash && !slash && p > path && p[-1] == '/') {
                return false;
            }

            return true;
        }

        if ((segment_len == 1 && p[0] == '.') ||
            (segment_len == 2 && p[0] == '.' && p[1] == '.')) {
            return true;
        }

        if (!slash) {
            return false;
        }

        p = slash + 1;
    }
}

static bool manifest_required_path_is_safe(const char *path) {
    size_t len = strlen(path);

    return len > 0 &&
           path[0] != '/' &&
           path[len - 1] != '/' &&
           !string_has_control_or_backslash(path) &&
           !has_more_than_one_wildcard(path) &&
           !strchr(path, '*') &&
           !path_has_forbidden_segments(path, false);
}

static bool hashlist_path_is_safe(const char *path) {
    size_t len = strlen(path);

    return len > 0 &&
           path[0] != '/' &&
           path[len - 1] != '/' &&
           !string_has_control_or_backslash(path) &&
           !path_has_forbidden_segments(path, false);
}

static bool manifest_exclude_pattern_is_safe(const char *pattern) {
    size_t len = strlen(pattern);

    return len > 0 &&
           pattern[0] != '/' &&
           !string_has_control_or_backslash(pattern) &&
           !has_more_than_one_wildcard(pattern) &&
           !path_has_forbidden_segments(pattern, true);
}

static bool manifest_filename_pattern_is_safe(const char *pattern) {
    size_t len = strlen(pattern);

    return len > 0 &&
           strcmp(pattern, ".") != 0 &&
           strcmp(pattern, "..") != 0 &&
           strcmp(pattern, "*") != 0 &&
           !strchr(pattern, '/') &&
           !string_has_control_or_backslash(pattern) &&
           !has_more_than_one_wildcard(pattern);
}

static bool pathlist_all_safe(const PathList *list, bool (*predicate)(const char *)) {
    for (size_t i = 0; i < list->len; i++) {
        if (!predicate(list->items[i])) {
            return false;
        }
    }

    return true;
}

static const char *basename_of(const char *path) {
    const char *slash = strrchr(path, '/');

    if (!slash) {
        return path;
    }

    return slash + 1;
}

static bool wildcard_match_n(const char *text, const char *pattern, size_t pattern_len) {
    const char *star = memchr(pattern, '*', pattern_len);
    size_t text_len = strlen(text);

    if (!star) {
        return text_len == pattern_len && strncmp(text, pattern, pattern_len) == 0;
    }

    size_t prefix_len = (size_t)(star - pattern);
    size_t suffix_len = pattern_len - prefix_len - 1;

    if (text_len < prefix_len + suffix_len) {
        return false;
    }

    return strncmp(text, pattern, prefix_len) == 0 &&
           strncmp(text + text_len - suffix_len, star + 1, suffix_len) == 0;
}

static bool pattern_uses_path(const char *pattern, size_t pattern_len) {
    return memchr(pattern, '/', pattern_len) != NULL;
}

static bool path_excluded_dir(const char *visible, const char *name, const PathList *excludes) {
    for (size_t i = 0; i < excludes->len; i++) {
        const char *pattern = excludes->items[i];
        size_t len = strlen(pattern);

        if (len == 0 || pattern[len - 1] != '/') {
            continue;
        }

        len--;

        if (len == 0) {
            continue;
        }

        const char *target = pattern_uses_path(pattern, len) ? visible : name;

        if (wildcard_match_n(target, pattern, len)) {
            return true;
        }
    }

    return false;
}

static bool path_excluded_file(const char *visible, const char *name, const PathList *excludes) {
    for (size_t i = 0; i < excludes->len; i++) {
        const char *pattern = excludes->items[i];
        size_t len = strlen(pattern);

        if (len == 0 || pattern[len - 1] == '/') {
            continue;
        }

        const char *target = pattern_uses_path(pattern, len) ? visible : name;

        if (wildcard_match_n(target, pattern, len)) {
            return true;
        }
    }

    return false;
}

static void collect_files(
    SealRun *run,
    PathList *list,
    const char *dir_path,
    const PathList *excludes
) {
    DIR *dir = opendir(dir_path);

    if (!dir) {
        char msg[512];
        snprintf(msg, sizeof(msg), "could not open directory: %s", dir_path);
        fail_run(run, msg);
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
            fail_run(run, "skipped path because it was too long");
            continue;
        }

        struct stat st;

        if (lstat(path, &st) != 0) {
            char msg[512];
            snprintf(msg, sizeof(msg), "could not stat path: %s", path);
            fail_run(run, msg);
            continue;
        }

        const char *visible = visible_path(path);

        if (S_ISDIR(st.st_mode)) {
            if (!path_excluded_dir(visible, entry->d_name, excludes)) {
                collect_files(run, list, path, excludes);
            }

            continue;
        }

        if (path_excluded_file(visible, entry->d_name, excludes)) {
            continue;
        }

        if (S_ISREG(st.st_mode)) {
            if (!pathlist_push(list, path)) {
                fail_run(run, "out of memory while collecting file paths");
                closedir(dir);
                return;
            }
        } else if (S_ISLNK(st.st_mode)) {
            char msg[512];
            snprintf(msg, sizeof(msg), "refusing symlink in digest scope: %s", visible_path(path));
            fail_run(run, msg);
        } else {
            char msg[512];
            snprintf(msg, sizeof(msg), "refusing non-regular path in digest scope: %s", visible_path(path));
            fail_run(run, msg);
        }
    }

    closedir(dir);
}

static bool filename_pattern_matches(const char *name, const char *pattern) {
    return wildcard_match_n(name, pattern, strlen(pattern));
}

static bool denied_secret_filename(const char *path, const PathList *patterns) {
    const char *name = basename_of(path);

    for (size_t i = 0; i < patterns->len; i++) {
        if (filename_pattern_matches(name, patterns->items[i])) {
            return true;
        }
    }

    return false;
}

static bool buffer_contains_marker(
    const unsigned char *buf,
    size_t len,
    const char *marker
) {
    size_t marker_len = strlen(marker);

    if (marker_len == 0 || marker_len > len) {
        return false;
    }

    for (size_t i = 0; i <= len - marker_len; i++) {
        if (memcmp(buf + i, marker, marker_len) == 0) {
            return true;
        }
    }

    return false;
}

static size_t pathlist_max_len(const PathList *list) {
    size_t max_len = 0;

    for (size_t i = 0; i < list->len; i++) {
        size_t len = strlen(list->items[i]);

        if (len > max_len) {
            max_len = len;
        }
    }

    return max_len;
}

static bool file_contains_secret_marker(
    const char *path,
    const PathList *markers,
    bool *read_ok
) {
    enum {
        read_chunk = 8192
    };

    size_t max_marker_len = pathlist_max_len(markers);
    size_t marker_overlap = max_marker_len == 0 ? 0 : max_marker_len - 1;
    unsigned char *buf = malloc(marker_overlap + read_chunk);
    size_t prefix_len = 0;
    FILE *f = open_regular_file_for_read(path);

    *read_ok = false;

    if (!buf) {
        if (f) {
            fclose(f);
        }
        return false;
    }

    if (!f) {
        free(buf);
        return false;
    }

    for (;;) {
        size_t n = fread(buf + prefix_len, 1, read_chunk, f);
        size_t total = prefix_len + n;

        for (size_t i = 0; i < markers->len; i++) {
            if (buffer_contains_marker(buf, total, markers->items[i])) {
                fclose(f);
                free(buf);
                *read_ok = true;
                return true;
            }
        }

        if (n < read_chunk) {
            if (ferror(f)) {
                fclose(f);
                free(buf);
                return false;
            }

            break;
        }

        prefix_len = total < marker_overlap ? total : marker_overlap;

        if (prefix_len > 0) {
            memmove(buf, buf + total - prefix_len, prefix_len);
        }
    }

    if (fclose(f) != 0) {
        free(buf);
        return false;
    }

    free(buf);
    *read_ok = true;
    return false;
}

static bool sha256_file(const char *path, char out_hex[65]) {
    bool ok = false;
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int digest_len = 0;
    unsigned char buf[8192];

    FILE *f = open_regular_file_for_read(path);

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

static const char *skip_line_spaces(const char *p, const char *end) {
    while (p < end && (*p == ' ' || *p == '\t')) {
        p++;
    }

    return p;
}

static bool line_tail_is_empty_or_comment(const char *p, const char *end) {
    p = skip_line_spaces(p, end);
    return p == end || *p == '#';
}

static bool line_section_name(
    const char *line,
    const char *line_end,
    const char **name_start,
    size_t *name_len
) {
    const char *p = skip_line_spaces(line, line_end);

    if (p >= line_end || *p != '[') {
        return false;
    }

    p++;

    if (p < line_end && *p == '[') {
        return false;
    }

    p = skip_line_spaces(p, line_end);

    const char *start = p;
    const char *close = memchr(p, ']', (size_t)(line_end - p));

    if (!close) {
        return false;
    }

    const char *end = close;

    while (end > start && (end[-1] == ' ' || end[-1] == '\t')) {
        end--;
    }

    if (end == start || !line_tail_is_empty_or_comment(close + 1, line_end)) {
        return false;
    }

    *name_start = start;
    *name_len = (size_t)(end - start);
    return true;
}

static bool section_matches(const char *section, size_t section_len, const char *expected) {
    size_t expected_len = strlen(expected);
    return section_len == expected_len && strncmp(section, expected, expected_len) == 0;
}

static size_t manifest_assignment_count(const char *manifest, const char *section_name, const char *key) {
    size_t count = 0;
    size_t key_len = strlen(key);
    const char *current_section = "";
    size_t current_section_len = 0;
    const char *line = manifest;

    while (*line != '\0') {
        const char *line_end = strchr(line, '\n');

        if (!line_end) {
            line_end = line + strlen(line);
        }

        while (line_end > line && line_end[-1] == '\r') {
            line_end--;
        }

        const char *p = skip_line_spaces(line, line_end);

        const char *parsed_section;
        size_t parsed_section_len;

        if (line_section_name(line, line_end, &parsed_section, &parsed_section_len)) {
            current_section = parsed_section;
            current_section_len = parsed_section_len;
        } else if (section_matches(current_section, current_section_len, section_name) &&
                   (size_t)(line_end - p) >= key_len && strncmp(p, key, key_len) == 0) {
            p += key_len;
            p = skip_line_spaces(p, line_end);

            if (p < line_end && *p == '=') {
                count++;
            }
        }

        if (*line_end == '\0') {
            break;
        }

        line = line_end + 1;
    }

    return count;
}

static bool manifest_has_assignment_value(
    const char *manifest,
    const char *section_name,
    const char *key,
    const char *expected_value,
    bool quoted
) {
    size_t key_len = strlen(key);
    size_t expected_len = strlen(expected_value);
    const char *current_section = "";
    size_t current_section_len = 0;
    const char *line = manifest;

    while (*line != '\0') {
        const char *line_end = strchr(line, '\n');

        if (!line_end) {
            line_end = line + strlen(line);
        }

        while (line_end > line && line_end[-1] == '\r') {
            line_end--;
        }

        const char *p = skip_line_spaces(line, line_end);

        const char *parsed_section;
        size_t parsed_section_len;

        if (line_section_name(line, line_end, &parsed_section, &parsed_section_len)) {
            current_section = parsed_section;
            current_section_len = parsed_section_len;
        } else if (section_matches(current_section, current_section_len, section_name) &&
                   (size_t)(line_end - p) >= key_len && strncmp(p, key, key_len) == 0) {
            p += key_len;
            p = skip_line_spaces(p, line_end);

            if (p < line_end && *p == '=') {
                p++;
                p = skip_line_spaces(p, line_end);

                if (quoted) {
                    if (p < line_end && *p == '"') {
                        p++;

                        if ((size_t)(line_end - p) >= expected_len &&
                            strncmp(p, expected_value, expected_len) == 0) {
                            p += expected_len;

                            if (p < line_end && *p == '"' &&
                                line_tail_is_empty_or_comment(p + 1, line_end)) {
                                return true;
                            }
                        }
                    }
                } else if ((size_t)(line_end - p) >= expected_len &&
                           strncmp(p, expected_value, expected_len) == 0 &&
                           line_tail_is_empty_or_comment(p + expected_len, line_end)) {
                    return true;
                }
            }
        }

        if (*line_end == '\0') {
            break;
        }

        line = line_end + 1;
    }

    return false;
}

static bool manifest_find_quoted_assignment(
    const char *manifest,
    const char *section_name,
    const char *key,
    const char **value_start,
    size_t *value_len
) {
    size_t key_len = strlen(key);
    const char *current_section = "";
    size_t current_section_len = 0;
    const char *line = manifest;

    while (*line != '\0') {
        const char *line_end = strchr(line, '\n');

        if (!line_end) {
            line_end = line + strlen(line);
        }

        while (line_end > line && line_end[-1] == '\r') {
            line_end--;
        }

        const char *p = skip_line_spaces(line, line_end);

        const char *parsed_section;
        size_t parsed_section_len;

        if (line_section_name(line, line_end, &parsed_section, &parsed_section_len)) {
            current_section = parsed_section;
            current_section_len = parsed_section_len;
        } else if (section_matches(current_section, current_section_len, section_name) &&
                   (size_t)(line_end - p) >= key_len && strncmp(p, key, key_len) == 0) {
            p += key_len;
            p = skip_line_spaces(p, line_end);

            if (p < line_end && *p == '=') {
                p++;
                p = skip_line_spaces(p, line_end);

                if (p < line_end && *p == '"') {
                    const char *start = p + 1;
                    const char *end = memchr(start, '"', (size_t)(line_end - start));

                    if (end && line_tail_is_empty_or_comment(end + 1, line_end)) {
                        *value_start = start;
                        *value_len = (size_t)(end - start);
                        return true;
                    }
                }
            }
        }

        if (*line_end == '\0') {
            break;
        }

        line = line_end + 1;
    }

    return false;
}

static bool manifest_find_assignment_value(
    const char *manifest,
    const char *section_name,
    const char *key,
    const char **value_start,
    size_t *value_len
) {
    size_t key_len = strlen(key);
    const char *current_section = "";
    size_t current_section_len = 0;
    const char *line = manifest;

    while (*line != '\0') {
        const char *line_end = strchr(line, '\n');

        if (!line_end) {
            line_end = line + strlen(line);
        }

        while (line_end > line && line_end[-1] == '\r') {
            line_end--;
        }

        const char *p = skip_line_spaces(line, line_end);
        const char *parsed_section;
        size_t parsed_section_len;

        if (line_section_name(line, line_end, &parsed_section, &parsed_section_len)) {
            current_section = parsed_section;
            current_section_len = parsed_section_len;
        } else if (section_matches(current_section, current_section_len, section_name) &&
                   (size_t)(line_end - p) >= key_len && strncmp(p, key, key_len) == 0) {
            p += key_len;
            p = skip_line_spaces(p, line_end);

            if (p < line_end && *p == '=') {
                p++;
                p = skip_line_spaces(p, line_end);

                if (p < line_end && *p == '[') {
                    const char *start = p;
                    const char *q = p;
                    int depth = 0;
                    bool in_string = false;
                    bool escaped = false;

                    while (*q != '\0') {
                        char c = *q;

                        if (in_string) {
                            if (escaped) {
                                escaped = false;
                            } else if (c == '\\') {
                                escaped = true;
                            } else if (c == '"') {
                                in_string = false;
                            }
                        } else if (c == '"') {
                            in_string = true;
                        } else if (c == '[') {
                            depth++;
                        } else if (c == ']') {
                            depth--;

                            if (depth == 0) {
                                const char *end = q + 1;
                                const char *tail_end = strchr(q, '\n');

                                if (!tail_end) {
                                    tail_end = q + strlen(q);
                                }

                                while (tail_end > q && tail_end[-1] == '\r') {
                                    tail_end--;
                                }

                                if (!line_tail_is_empty_or_comment(end, tail_end)) {
                                    return false;
                                }

                                *value_start = start;
                                *value_len = (size_t)(end - start);
                                return true;
                            }

                            if (depth < 0) {
                                return false;
                            }
                        }

                        q++;
                    }

                    return false;
                }

                *value_start = p;
                *value_len = (size_t)(line_end - p);
                return true;
            }
        }

        if (*line_end == '\0') {
            break;
        }

        line = line_end + 1;
    }

    return false;
}

static const char *skip_array_space(const char *p, const char *end) {
    for (;;) {
        while (p < end && (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')) {
            p++;
        }

        if (p < end && *p == '#') {
            while (p < end && *p != '\n') {
                p++;
            }
            continue;
        }

        return p;
    }
}

static bool parse_quoted_token(const char **cursor, const char *end, char **out) {
    const char *p = *cursor;
    char *buf = NULL;
    size_t len = 0;
    size_t cap = 0;

    if (p >= end || *p != '"') {
        return false;
    }

    p++;

    while (p < end) {
        char c = *p++;

        if (c == '"') {
            char *next = realloc(buf, len + 1);

            if (!next) {
                free(buf);
                return false;
            }

            buf = next;
            buf[len] = '\0';
            *cursor = p;
            *out = buf;
            return true;
        }

        if (c == '\\' && p < end) {
            c = *p++;
        }

        if (len + 1 >= cap) {
            size_t next_cap = cap == 0 ? 32 : cap * 2;
            char *next = realloc(buf, next_cap);

            if (!next) {
                free(buf);
                return false;
            }

            buf = next;
            cap = next_cap;
        }

        buf[len++] = c;
    }

    free(buf);
    return false;
}

static bool parse_string_array(const char *value, size_t value_len, PathList *out) {
    const char *p = value;
    const char *end = value + value_len;

    p = skip_array_space(p, end);

    if (p >= end || *p != '[') {
        return false;
    }

    p++;

    bool need_value = true;

    for (;;) {
        p = skip_array_space(p, end);

        if (p < end && *p == ']') {
            p++;
            p = skip_array_space(p, end);
            return p == end && out->len > 0;
        }

        if (!need_value) {
            if (p < end && *p == ',') {
                p++;
                need_value = true;
                continue;
            }

            return false;
        }

        if (p >= end || *p != '"') {
            return false;
        }

        char *token = NULL;

        if (!parse_quoted_token(&p, end, &token)) {
            return false;
        }

        bool pushed = token[0] != '\0' && pathlist_push(out, token);
        free(token);

        if (!pushed) {
            return false;
        }

        need_value = false;
    }
}

static bool append_string(char **buf, size_t *len, size_t *cap, const char *part) {
    size_t part_len = strlen(part);
    size_t needed = *len + part_len + 1;

    if (needed > *cap) {
        size_t next_cap = *cap == 0 ? 32 : *cap;

        while (next_cap < needed) {
            next_cap *= 2;
        }

        char *next = realloc(*buf, next_cap);

        if (!next) {
            return false;
        }

        *buf = next;
        *cap = next_cap;
    }

    memcpy(*buf + *len, part, part_len);
    *len += part_len;
    (*buf)[*len] = '\0';
    return true;
}

static bool parse_string_part_array(const char *value, size_t value_len, PathList *out) {
    const char *p = value;
    const char *end = value + value_len;

    p = skip_array_space(p, end);

    if (p >= end || *p != '[') {
        return false;
    }

    p++;

    bool need_outer_value = true;

    for (;;) {
        p = skip_array_space(p, end);

        if (p < end && *p == ']') {
            p++;
            p = skip_array_space(p, end);
            return p == end && out->len > 0;
        }

        if (!need_outer_value) {
            if (p < end && *p == ',') {
                p++;
                need_outer_value = true;
                continue;
            }

            return false;
        }

        if (p >= end || *p != '[') {
            return false;
        }

        p++;

        char *joined = NULL;
        size_t joined_len = 0;
        size_t joined_cap = 0;
        size_t part_count = 0;
        bool need_inner_value = true;

        for (;;) {
            p = skip_array_space(p, end);

            if (p < end && *p == ']') {
                p++;

                if (part_count == 0 || joined_len == 0) {
                    free(joined);
                    return false;
                }

                bool pushed = pathlist_push(out, joined);
                free(joined);

                if (!pushed) {
                    return false;
                }

                need_outer_value = false;
                break;
            }

            if (!need_inner_value) {
                if (p < end && *p == ',') {
                    p++;
                    need_inner_value = true;
                    continue;
                }

                free(joined);
                return false;
            }

            if (p >= end || *p != '"') {
                free(joined);
                return false;
            }

            char *token = NULL;

            if (!parse_quoted_token(&p, end, &token)) {
                free(joined);
                return false;
            }

            bool appended = append_string(&joined, &joined_len, &joined_cap, token);
            free(token);

            if (!appended) {
                free(joined);
                return false;
            }

            part_count++;
            need_inner_value = false;
        }
    }
}

static void require_manifest_assignment(
    SealRun *run,
    const char *manifest,
    const char *section_name,
    const char *key,
    const char *expected_value,
    bool quoted,
    const char *label
) {
    if (manifest_assignment_count(manifest, section_name, key) == 1 &&
        manifest_has_assignment_value(manifest, section_name, key, expected_value, quoted)) {
        pass(run, label);
    } else {
        fail_run(run, label);
    }
}

static void check_manifest_shape(SealRun *run, const char *manifest) {
    section(run, "Manifest shape");

    require_manifest_assignment(run, manifest, "", "schema", "latticra.seal/v0.1", true, "schema is latticra.seal/v0.1");
    require_manifest_assignment(run, manifest, "", "format", "toml", true, "format is TOML-compatible");
    require_manifest_assignment(run, manifest, "", "kind", "local-integrity-manifest", true, "kind is local-integrity-manifest");
    require_manifest_assignment(run, manifest, "seal", "mode", "local-integrity", true, "seal mode is local-integrity");
    require_manifest_assignment(run, manifest, "seal", "status", "unsigned", true, "seal status is unsigned");
    require_manifest_assignment(run, manifest, "seal", "algorithm", "sha256", true, "hash algorithm is sha256");
    require_manifest_assignment(run, manifest, "seal", "digest_encoding", "hex", true, "digest encoding is hex");
    require_manifest_assignment(run, manifest, "seal", "canonicalization", "relative-path + raw-bytes + unix-lf-preferred", true, "canonicalization is relative-path + raw-bytes + unix-lf-preferred");
    require_manifest_assignment(run, manifest, "seal", "trust_boundary", "project-root", true, "trust boundary is project-root");
}

static void check_policy_shape(SealRun *run, const char *manifest) {
    section(run, "Policy shape");

    require_manifest_assignment(run, manifest, "policy", "require_readme", "true", false, "policy requires README");
    require_manifest_assignment(run, manifest, "policy", "require_license", "true", false, "policy requires LICENSE");
    require_manifest_assignment(run, manifest, "policy", "deny_private_keys", "true", false, "policy denies private keys");
    require_manifest_assignment(run, manifest, "policy", "deny_env_files", "true", false, "policy denies .env files");
    require_manifest_assignment(run, manifest, "policy", "deny_obvious_tokens", "true", false, "policy denies obvious token markers");
}

static void check_report_shape(SealRun *run, const char *manifest) {
    section(run, "Report shape");

    require_manifest_assignment(run, manifest, "report", "default_output", REPORT_PATH, true, "report default output is " REPORT_PATH);
    require_manifest_assignment(run, manifest, "report", "hash_list_output", HASH_LIST_PATH, true, "report hash list output is " HASH_LIST_PATH);
    require_manifest_assignment(run, manifest, "report", "legacy_smoke_output", LEGACY_SMOKE_REPORT_PATH, true, "legacy smoke output is " LEGACY_SMOKE_REPORT_PATH);
    require_manifest_assignment(run, manifest, "report", "legacy_smoke_hash_list_output", LEGACY_SMOKE_HASH_LIST_PATH, true, "legacy smoke hash list output is " LEGACY_SMOKE_HASH_LIST_PATH);
    require_manifest_assignment(run, manifest, "report", "include_file_list", "true", false, "report includes file list");
    require_manifest_assignment(run, manifest, "report", "include_policy_results", "true", false, "report includes policy results");
    require_manifest_assignment(run, manifest, "report", "include_digest_summary", "true", false, "report includes digest summary");
}

static void check_required_files(SealRun *run, const char *manifest) {
    section(run, "Required project files");

    PathList required;
    required.items = NULL;
    required.len = 0;
    required.cap = 0;

    const char *value;
    size_t value_len;
    size_t required_count = manifest_assignment_count(manifest, "policy.required_files", "paths");

    if (required_count != 1 ||
        !manifest_find_assignment_value(manifest, "policy.required_files", "paths", &value, &value_len) ||
        !parse_string_array(value, value_len, &required) ||
        pathlist_has_duplicate_items(&required) ||
        !pathlist_all_safe(&required, manifest_required_path_is_safe)) {
        fail_run(run, "policy required files are missing, duplicate, or malformed");
        pathlist_free(&required);
        return;
    }

    char msg[512];
    snprintf(msg, sizeof(msg), "loaded %zu required file path(s)", required.len);
    pass(run, msg);

    for (size_t i = 0; i < required.len; i++) {
        if (file_exists(required.items[i])) {
            snprintf(msg, sizeof(msg), "required file exists: %s", required.items[i]);
            pass(run, msg);
        } else {
            snprintf(msg, sizeof(msg), "required file missing: %s", required.items[i]);
            fail_run(run, msg);
        }
    }

    pathlist_free(&required);
}

static bool load_path_scope(
    SealRun *run,
    const char *manifest,
    PathList *includes,
    PathList *excludes
) {
    const char *value;
    size_t value_len;
    size_t include_count = manifest_assignment_count(manifest, "paths", "include");

    if (include_count != 1 ||
        !manifest_find_assignment_value(manifest, "paths", "include", &value, &value_len) ||
        !parse_string_array(value, value_len, includes)) {
        fail_run(run, "path include scope is missing, duplicate, or malformed");
        return false;
    }

    if (includes->len != 1 || strcmp(includes->items[0], ".") != 0) {
        fail_run(run, "path include scope must be project root");
        return false;
    }

    size_t exclude_count = manifest_assignment_count(manifest, "paths", "exclude");

    if (exclude_count != 1 ||
        !manifest_find_assignment_value(manifest, "paths", "exclude", &value, &value_len) ||
        !parse_string_array(value, value_len, excludes) ||
        pathlist_has_duplicate_items(excludes) ||
        !pathlist_all_safe(excludes, manifest_exclude_pattern_is_safe)) {
        fail_run(run, "path exclude scope is missing, duplicate, or malformed");
        return false;
    }

    char msg[160];
    snprintf(msg, sizeof(msg), "loaded %zu path exclude pattern(s)", excludes->len);
    pass(run, msg);
    return true;
}

static bool load_policy_denials(
    SealRun *run,
    const char *manifest,
    PathList *filename_patterns,
    PathList *content_markers
) {
    const char *value;
    size_t value_len;
    size_t filename_count = manifest_assignment_count(manifest, "policy.deny_filenames", "patterns");

    if (filename_count != 1 ||
        !manifest_find_assignment_value(manifest, "policy.deny_filenames", "patterns", &value, &value_len) ||
        !parse_string_array(value, value_len, filename_patterns) ||
        pathlist_has_duplicate_items(filename_patterns) ||
        !pathlist_all_safe(filename_patterns, manifest_filename_pattern_is_safe)) {
        fail_run(run, "policy deny filename patterns are missing, duplicate, or malformed");
        return false;
    }

    size_t content_count = manifest_assignment_count(manifest, "policy.deny_contents", "pattern_parts");

    if (content_count != 1 ||
        !manifest_find_assignment_value(manifest, "policy.deny_contents", "pattern_parts", &value, &value_len) ||
        !parse_string_part_array(value, value_len, content_markers) ||
        pathlist_has_duplicate_items(content_markers)) {
        fail_run(run, "policy deny content pattern parts are missing, duplicate, or malformed");
        return false;
    }

    char msg[160];
    snprintf(msg, sizeof(msg), "loaded %zu deny filename pattern(s)", filename_patterns->len);
    pass(run, msg);
    snprintf(msg, sizeof(msg), "loaded %zu deny content marker(s)", content_markers->len);
    pass(run, msg);
    return true;
}

static void check_policy_denials(SealRun *run, const char *manifest) {
    section(run, "Policy denial scan");

    PathList filename_patterns;
    filename_patterns.items = NULL;
    filename_patterns.len = 0;
    filename_patterns.cap = 0;

    PathList content_markers;
    content_markers.items = NULL;
    content_markers.len = 0;
    content_markers.cap = 0;

    PathList includes;
    includes.items = NULL;
    includes.len = 0;
    includes.cap = 0;

    PathList excludes;
    excludes.items = NULL;
    excludes.len = 0;
    excludes.cap = 0;

    if (!load_path_scope(run, manifest, &includes, &excludes)) {
        pathlist_free(&includes);
        pathlist_free(&excludes);
        fail_run(run, "policy denial scan skipped because path scope was invalid");
        return;
    }

    if (!load_policy_denials(run, manifest, &filename_patterns, &content_markers)) {
        pathlist_free(&includes);
        pathlist_free(&excludes);
        pathlist_free(&filename_patterns);
        pathlist_free(&content_markers);
        fail_run(run, "policy denial scan skipped because policy configuration was invalid");
        return;
    }

    PathList list;
    list.items = NULL;
    list.len = 0;
    list.cap = 0;

    int traversal_failures_before = run->failures;

    collect_files(run, &list, ".", &excludes);

    if (run->failures != traversal_failures_before) {
        fail_run(run, "policy denial scan incomplete because traversal failed");
        pathlist_free(&list);
        pathlist_free(&includes);
        pathlist_free(&excludes);
        pathlist_free(&filename_patterns);
        pathlist_free(&content_markers);
        return;
    }

    qsort(list.items, list.len, sizeof(char *), cmp_string_ptr);

    size_t filename_hits = 0;
    size_t content_hits = 0;
    size_t inspect_failures = 0;

    for (size_t i = 0; i < list.len; i++) {
        const char *path = list.items[i];

        if (denied_secret_filename(path, &filename_patterns)) {
            char msg[512];
            snprintf(msg, sizeof(msg), "possible secret-bearing filename: %s", visible_path(path));
            fail_run(run, msg);
            filename_hits++;
        }

        bool read_ok;

        if (file_contains_secret_marker(path, &content_markers, &read_ok)) {
            char msg[512];
            snprintf(msg, sizeof(msg), "possible secret content marker in: %s", visible_path(path));
            fail_run(run, msg);
            content_hits++;
        } else if (!read_ok) {
            char msg[512];
            snprintf(msg, sizeof(msg), "could not inspect file for policy markers: %s", visible_path(path));
            fail_run(run, msg);
            inspect_failures++;
        }
    }

    if (filename_hits == 0) {
        pass(run, "no obvious secret-bearing filenames found");
    }

    if (content_hits == 0 && inspect_failures == 0) {
        pass(run, "no obvious secret content markers found");
    }

    pathlist_free(&list);
    pathlist_free(&includes);
    pathlist_free(&excludes);
    pathlist_free(&filename_patterns);
    pathlist_free(&content_markers);
}

static void write_digest_summary(SealRun *run, const char *manifest) {
    section(run, "Digest summary");

    PathList list;
    list.items = NULL;
    list.len = 0;
    list.cap = 0;

    PathList includes;
    includes.items = NULL;
    includes.len = 0;
    includes.cap = 0;

    PathList excludes;
    excludes.items = NULL;
    excludes.len = 0;
    excludes.cap = 0;

    if (unlink(HASH_LIST_PATH) != 0 && errno != ENOENT) {
        fail_run(run, "could not clear previous hash list");
        return;
    }

    if (unlink(HASH_LIST_TMP_PATH) != 0 && errno != ENOENT) {
        fail_run(run, "could not clear temporary hash list");
        return;
    }

    if (!load_path_scope(run, manifest, &includes, &excludes)) {
        fail_run(run, "hash list not written because path scope was invalid");
        pathlist_free(&includes);
        pathlist_free(&excludes);
        return;
    }

    int traversal_failures_before = run->failures;

    collect_files(run, &list, ".", &excludes);

    if (run->failures != traversal_failures_before) {
        fail_run(run, "hash list not written because digest traversal failed");
        pathlist_free(&list);
        pathlist_free(&includes);
        pathlist_free(&excludes);
        return;
    }

    qsort(list.items, list.len, sizeof(char *), cmp_string_ptr);

    FILE *hashes = open_regular_file_for_write(HASH_LIST_TMP_PATH);

    if (!hashes) {
        fail_run(run, "could not write hash list");
        pathlist_free(&list);
        pathlist_free(&includes);
        pathlist_free(&excludes);
        return;
    }

    size_t hashed_count = 0;
    bool hash_write_ok = true;

    for (size_t i = 0; i < list.len; i++) {
        char hex[65];

        if (!sha256_file(list.items[i], hex)) {
            char msg[512];
            snprintf(msg, sizeof(msg), "could not hash file: %s", visible_path(list.items[i]));
            fail_run(run, msg);
            continue;
        }

        if (fprintf(hashes, "%s  %s\n", hex, visible_path(list.items[i])) < 0) {
            fail_run(run, "could not write hash entry");
            hash_write_ok = false;
            break;
        }

        hashed_count++;
    }

    if (fclose(hashes) != 0) {
        fail_run(run, "could not finalize hash list");
        hash_write_ok = false;
    }

    if (run->failures != traversal_failures_before || !hash_write_ok) {
        (void)unlink(HASH_LIST_TMP_PATH);
        fail_run(run, "hash list not written because file hashing failed");
        pathlist_free(&list);
        pathlist_free(&includes);
        pathlist_free(&excludes);
        return;
    }

    if (rename(HASH_LIST_TMP_PATH, HASH_LIST_PATH) != 0) {
        (void)unlink(HASH_LIST_TMP_PATH);
        fail_run(run, "could not promote hash list");
        pathlist_free(&list);
        pathlist_free(&includes);
        pathlist_free(&excludes);
        return;
    }

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
    pathlist_free(&includes);
    pathlist_free(&excludes);
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

static int finalize_report(SealRun *run, int code) {
    if (!run->report) {
        return code;
    }

    if (fclose(run->report) != 0) {
        run->report = NULL;
        (void)unlink_regular_if_present(REPORT_TMP_PATH);
        fprintf(stderr, "could not finalize report: %s\n", REPORT_PATH);
        return 2;
    }

    run->report = NULL;

    if (!path_is_regular_or_missing(REPORT_PATH)) {
        (void)unlink_regular_if_present(REPORT_TMP_PATH);
        fprintf(stderr, "could not promote report: %s\n", REPORT_PATH);
        return 2;
    }

    if (rename(REPORT_TMP_PATH, REPORT_PATH) != 0) {
        (void)unlink_regular_if_present(REPORT_TMP_PATH);
        fprintf(stderr, "could not promote report: %s\n", REPORT_PATH);
        return 2;
    }

    return code;
}

static int command_check(void) {
    if (!ensure_report_dir()) {
        return 2;
    }

    SealRun run;
    run.failures = 0;
    run.warnings = 0;
    run.report = open_report_for_write();

    if (!run.report) {
        fprintf(stderr, "could not open report: %s\n", REPORT_PATH);
        return 2;
    }

    write_header(&run);

    section(&run, "Manifest presence");

    char *manifest = read_file(MANIFEST_PATH);

    if (!manifest) {
        fail_run(&run, "latticra.seal is missing or unreadable");
        int code = finish(&run);
        return finalize_report(&run, code);
    }

    pass(&run, "latticra.seal exists");

    check_manifest_shape(&run, manifest);
    check_policy_shape(&run, manifest);
    check_report_shape(&run, manifest);
    check_required_files(&run, manifest);
    check_policy_denials(&run, manifest);
    write_digest_summary(&run, manifest);

    free(manifest);

    int code = finish(&run);
    return finalize_report(&run, code);
}

static void print_manifest_value(
    const char *manifest,
    const char *section_name,
    const char *key,
    const char *label
) {
    const char *start;
    size_t len;
    size_t count = manifest_assignment_count(manifest, section_name, key);

    if (count == 0) {
        printf("%s: missing\n", label);
        return;
    }

    if (count > 1) {
        printf("%s: duplicate\n", label);
        return;
    }

    if (!manifest_find_quoted_assignment(manifest, section_name, key, &start, &len)) {
        printf("%s: malformed\n", label);
        return;
    }

    printf("%s: %.*s\n", label, (int)len, start);
}

static int command_manifest(void) {
    char *manifest = read_file(MANIFEST_PATH);

    if (!manifest) {
        fprintf(stderr, "could not read %s\n", MANIFEST_PATH);
        return 1;
    }

    puts("Latticra Seal Manifest Summary");
    puts("------------------------------");

    print_manifest_value(manifest, "", "schema", "Schema");
    print_manifest_value(manifest, "", "kind", "Kind");
    print_manifest_value(manifest, "project", "name", "Project");
    print_manifest_value(manifest, "project", "version", "Project Version");
    print_manifest_value(manifest, "seal", "mode", "Seal Mode");
    print_manifest_value(manifest, "seal", "status", "Seal Status");
    print_manifest_value(manifest, "seal", "algorithm", "Digest Algorithm");
    print_manifest_value(manifest, "seal", "trust_boundary", "Trust Boundary");

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

static bool is_sha256_hex(const char *hash) {
    for (size_t i = 0; i < 64; i++) {
        char c = hash[i];

        if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'))) {
            return false;
        }
    }

    return hash[64] == '\0';
}

static bool read_hash_list(const char *path, HashList *list) {
    FILE *f = open_regular_file_for_read(path);

    if (!f) {
        return false;
    }

    char line[8192];

    while (fgets(line, sizeof(line), f)) {
        if (!strchr(line, '\n') && !feof(f)) {
            fclose(f);
            return false;
        }

        strip_newline(line);

        if (strlen(line) < 67 || line[64] != ' ' || line[65] != ' ') {
            fclose(f);
            return false;
        }

        char hash[65];
        memcpy(hash, line, 64);
        hash[64] = '\0';

        if (!is_sha256_hex(hash)) {
            fclose(f);
            return false;
        }

        char *file_path = line + 66;

        if (*file_path == '\0' || *file_path == ' ' || *file_path == '\t') {
            fclose(f);
            return false;
        }

        if (!hashlist_path_is_safe(file_path)) {
            fclose(f);
            return false;
        }

        if (list->len > 0 && strcmp(list->items[list->len - 1].path, file_path) >= 0) {
            fclose(f);
            return false;
        }

        if (!hashlist_push(list, hash, file_path)) {
            fclose(f);
            return false;
        }
    }

    if (fclose(f) != 0) {
        return false;
    }

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
        hashlist_free(&baseline);
        fail_run(run, "could not read saved baseline");
        return;
    }

    if (!read_hash_list(current_path, &current)) {
        hashlist_free(&baseline);
        hashlist_free(&current);
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
    FILE *in = open_regular_file_for_read(src);

    if (!in) {
        return false;
    }

    FILE *out = open_regular_file_for_write(dst);

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

static bool write_baseline_atomic(void) {
    if (!path_is_regular_or_missing(BASELINE_PATH)) {
        return false;
    }

    if (!unlink_regular_if_present(BASELINE_TMP_PATH)) {
        return false;
    }

    if (!copy_file(HASH_LIST_PATH, BASELINE_TMP_PATH)) {
        (void)unlink_regular_if_present(BASELINE_TMP_PATH);
        return false;
    }

    if (!path_is_regular_or_missing(BASELINE_PATH)) {
        (void)unlink_regular_if_present(BASELINE_TMP_PATH);
        return false;
    }

    if (rename(BASELINE_TMP_PATH, BASELINE_PATH) != 0) {
        (void)unlink_regular_if_present(BASELINE_TMP_PATH);
        return false;
    }

    return true;
}

static bool files_equal(const char *a, const char *b) {
    FILE *fa = open_regular_file_for_read(a);

    if (!fa) {
        return false;
    }

    FILE *fb = open_regular_file_for_read(b);

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
    FILE *f = open_regular_file_for_read(path);

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

    if (!write_baseline_atomic()) {
        fprintf(stderr, "could not write baseline: %s\n", BASELINE_PATH);
        return 1;
    }

    printf("Baseline written to: %s\n", BASELINE_PATH);
    return 0;
}


static int command_verify(void) {
    if (!ensure_report_dir()) {
        return 2;
    }

    SealRun run;
    run.failures = 0;
    run.warnings = 0;
    run.report = open_report_for_write();

    if (!run.report) {
        fprintf(stderr, "could not open report: %s\n", REPORT_PATH);
        return 2;
    }

    write_header(&run);

    section(&run, "Baseline presence");

    HashList baseline_probe;
    baseline_probe.items = NULL;
    baseline_probe.len = 0;
    baseline_probe.cap = 0;

    if (!read_hash_list(BASELINE_PATH, &baseline_probe)) {
        hashlist_free(&baseline_probe);
        fail_run(&run, "latticra.seal.lock is missing or unreadable");
        int code = finish(&run);
        return finalize_report(&run, code);
    }

    hashlist_free(&baseline_probe);
    pass(&run, "latticra.seal.lock exists");

    section(&run, "Manifest presence");

    char *manifest = read_file(MANIFEST_PATH);

    if (!manifest) {
        fail_run(&run, "latticra.seal is missing or unreadable");
        int code = finish(&run);
        return finalize_report(&run, code);
    }

    pass(&run, "latticra.seal exists");

    check_manifest_shape(&run, manifest);
    check_policy_shape(&run, manifest);
    check_report_shape(&run, manifest);
    check_required_files(&run, manifest);
    check_policy_denials(&run, manifest);
    write_digest_summary(&run, manifest);

    free(manifest);

    section(&run, "Baseline comparison");

    if (run.failures == 0) {
        compare_hash_lists_report(&run, BASELINE_PATH, HASH_LIST_PATH);
    } else {
        warn_run(&run, "baseline comparison skipped because earlier checks failed");
    }

    int code = finish(&run);
    return finalize_report(&run, code);
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
