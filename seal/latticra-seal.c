#define _POSIX_C_SOURCE 200809L

#include "latticra/seal_hybrid_envelope.h"
#include "latticra/seal_hybrid_provider_self_test.h"

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <openssl/crypto.h>
#include <openssl/evp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

#define LATTICRA_SEAL_VERSION "v0.3-dev"
#define MANIFEST_PATH "latticra.seal"
#define REPORT_DIR "reports"
#define REPORT_FILE "latticra-seal-cli-report.txt"
#define REPORT_PATH "reports/latticra-seal-cli-report.txt"
#define REPORT_TMP_FILE "latticra-seal-cli-report.tmp"
#define REPORT_TMP_PATH "reports/latticra-seal-cli-report.tmp"
#define HASH_LIST_FILE "latticra-seal-cli-hashes.txt"
#define HASH_LIST_PATH "reports/latticra-seal-cli-hashes.txt"
#define HASH_LIST_TMP_FILE "latticra-seal-cli-hashes.tmp"
#define HASH_LIST_TMP_PATH "reports/latticra-seal-cli-hashes.tmp"
#define LEGACY_SMOKE_REPORT_PATH "reports/latticra-seal-report.txt"
#define LEGACY_SMOKE_HASH_LIST_PATH "reports/latticra-seal-file-hashes.txt"
#define BASELINE_PATH "latticra.seal.lock"
#define BASELINE_TMP_PATH "latticra.seal.lock.tmp"

static const unsigned char HYBRID_SELF_CHECK_CLASSICAL_SECRET[LATTICRA_SEAL_HYBRID_CLASSICAL_SHARED_SECRET_BYTES] = {
    0x4c, 0x61, 0x74, 0x74, 0x69, 0x63, 0x72, 0x61,
    0x2d, 0x73, 0x65, 0x61, 0x6c, 0x2d, 0x63, 0x31,
    0x10, 0x32, 0x54, 0x76, 0x98, 0xba, 0xdc, 0xfe,
    0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef
};

static const unsigned char HYBRID_SELF_CHECK_PQC_SECRET[LATTICRA_SEAL_HYBRID_PQC_SHARED_SECRET_BYTES] = {
    0x4c, 0x61, 0x74, 0x74, 0x69, 0x63, 0x72, 0x61,
    0x2d, 0x73, 0x65, 0x61, 0x6c, 0x2d, 0x71, 0x31,
    0xef, 0xcd, 0xab, 0x89, 0x67, 0x45, 0x23, 0x01,
    0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10
};

static const unsigned char HYBRID_SELF_CHECK_AAD[] =
    "latticra-seal-cli:hybrid-envelope:self-check:v1";
static const unsigned char HYBRID_SELF_CHECK_PLAINTEXT[] =
    "Latticra Seal hybrid envelope command self-check payload";

typedef struct {
    int failures;
    int warnings;
    FILE *report;
    int report_dir_fd;
    int hash_list_fd;
    bool preserve_hash_list_fd;
} SealRun;

static void close_hash_list_fd(SealRun *run);

typedef struct {
    char **items;
    size_t len;
    size_t cap;
} PathList;

typedef struct {
    char *path;
    dev_t dev;
    ino_t ino;
} CollectedFile;

typedef struct {
    CollectedFile *items;
    size_t len;
    size_t cap;
} CollectedFileList;

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

static bool required_file_is_single_link_regular(const char *path) {
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

    bool ok = fstat(fd, &st) == 0 && S_ISREG(st.st_mode) && st.st_nlink == 1;
    close(fd);
    return ok;
}

static bool report_dir_stat_is_safe(const struct stat *st) {
    if (S_ISLNK(st->st_mode)) {
        fprintf(stderr, "refusing symlink report directory: %s\n", REPORT_DIR);
        return false;
    }
    if (!S_ISDIR(st->st_mode)) {
        fprintf(stderr, "refusing non-directory report path: %s\n", REPORT_DIR);
        return false;
    }
    if ((st->st_mode & (S_IWGRP | S_IWOTH)) != 0) {
        fprintf(stderr, "refusing writable report directory: %s\n", REPORT_DIR);
        return false;
    }

    return true;
}

static bool same_file_identity(const struct stat *a, const struct stat *b) {
    return a->st_dev == b->st_dev && a->st_ino == b->st_ino;
}

static bool collected_file_stat_matches(
    const CollectedFile *file,
    const struct stat *st
) {
    return file != NULL &&
           st != NULL &&
           S_ISREG(st->st_mode) &&
           st->st_nlink == 1 &&
           st->st_size >= 0 &&
           st->st_dev == file->dev &&
           st->st_ino == file->ino;
}

static bool collected_file_stream_observed_size(
    FILE *stream,
    const CollectedFile *file,
    off_t *size
) {
    struct stat st;
    int fd;

    if (stream == NULL) {
        return false;
    }

    fd = fileno(stream);
    if (fd < 0 || fstat(fd, &st) != 0) {
        return false;
    }

    if (!collected_file_stat_matches(file, &st)) {
        return false;
    }

    if (size != NULL) {
        *size = st.st_size;
    }

    return true;
}

static bool collected_file_stream_size_matches(
    FILE *stream,
    const CollectedFile *file,
    off_t expected_size
) {
    off_t current_size;

    return collected_file_stream_observed_size(stream, file, &current_size) &&
           current_size == expected_size;
}

static bool fd_single_link_regular_size(int fd, off_t *size) {
    struct stat st;

    if (fstat(fd, &st) != 0 || !S_ISREG(st.st_mode) ||
        st.st_nlink != 1 || st.st_size < 0) {
        return false;
    }

    if (size) {
        *size = st.st_size;
    }

    return true;
}

static bool fd_size_matches(int fd, off_t expected_size) {
    off_t current_size;

    return fd_single_link_regular_size(fd, &current_size) &&
           current_size == expected_size;
}

static int open_report_dir_for_artifacts(bool create_if_missing, bool *missing) {
    if (missing) {
        *missing = false;
    }

    for (int attempt = 0; attempt < 3; attempt++) {
        struct stat path_st;

        if (lstat(REPORT_DIR, &path_st) != 0) {
            if (errno == ENOENT) {
                if (!create_if_missing) {
                    if (missing) {
                        *missing = true;
                    }
                    return -1;
                }

                if (mkdir(REPORT_DIR, 0700) == 0 || errno == EEXIST) {
                    continue;
                }

                fprintf(stderr, "could not create report directory: %s\n", REPORT_DIR);
                return -1;
            }

            fprintf(stderr, "could not inspect report directory: %s\n", REPORT_DIR);
            return -1;
        }

        if (!report_dir_stat_is_safe(&path_st)) {
            return -1;
        }

        int flags = O_RDONLY;
#ifdef O_CLOEXEC
        flags |= O_CLOEXEC;
#endif
#ifdef O_DIRECTORY
        flags |= O_DIRECTORY;
#endif
#ifdef O_NOFOLLOW
        flags |= O_NOFOLLOW;
#endif

        int fd = open(REPORT_DIR, flags);

        if (fd < 0) {
            if (errno == ENOENT) {
                if (!create_if_missing) {
                    if (missing) {
                        *missing = true;
                    }
                    return -1;
                }

                continue;
            }

            fprintf(stderr, "could not open report directory: %s\n", REPORT_DIR);
            return -1;
        }

        struct stat fd_st;

        if (fstat(fd, &fd_st) != 0) {
            close(fd);
            fprintf(stderr, "could not inspect report directory: %s\n", REPORT_DIR);
            return -1;
        }

        if (!report_dir_stat_is_safe(&fd_st)) {
            close(fd);
            return -1;
        }

        if (!same_file_identity(&path_st, &fd_st)) {
            close(fd);
            continue;
        }

        return fd;
    }

    fprintf(stderr, "could not stabilize report directory: %s\n", REPORT_DIR);
    return -1;
}

static int open_regular_file_at_for_read_fd_checked(
    int dirfd,
    const char *path,
    bool require_single_link
) {
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

    int fd = openat(dirfd, path, flags);

    if (fd < 0) {
        return -1;
    }

    if (fstat(fd, &st) != 0 || !S_ISREG(st.st_mode) ||
        (require_single_link && st.st_nlink != 1)) {
        close(fd);
        return -1;
    }

    return fd;
}

static FILE *open_regular_file_at_for_read_checked(
    int dirfd,
    const char *path,
    bool require_single_link
) {
    int fd = open_regular_file_at_for_read_fd_checked(
        dirfd,
        path,
        require_single_link
    );

    if (fd < 0) {
        return NULL;
    }

    FILE *file = fdopen(fd, "r");

    if (!file) {
        close(fd);
    }

    return file;
}

static FILE *open_regular_file_for_read_checked(const char *path, bool require_single_link) {
    return open_regular_file_at_for_read_checked(AT_FDCWD, path, require_single_link);
}

static FILE *open_collected_file_for_read(const CollectedFile *file) {
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

    int fd = open(file->path, flags);

    if (fd < 0) {
        return NULL;
    }

    if (fstat(fd, &st) != 0 || !collected_file_stat_matches(file, &st)) {
        close(fd);
        return NULL;
    }

    FILE *stream = fdopen(fd, "r");

    if (!stream) {
        close(fd);
    }

    return stream;
}

static DIR *open_directory_for_traversal(
    const char *path,
    const struct stat *expected_dir
) {
    int flags = O_RDONLY;
#ifdef O_CLOEXEC
    flags |= O_CLOEXEC;
#endif
#ifdef O_DIRECTORY
    flags |= O_DIRECTORY;
#endif
#ifdef O_NOFOLLOW
    flags |= O_NOFOLLOW;
#endif

    int fd = open(path, flags);

    if (fd < 0) {
        return NULL;
    }

    struct stat st;

    if (fstat(fd, &st) != 0 || !S_ISDIR(st.st_mode) ||
        (expected_dir && !same_file_identity(&st, expected_dir))) {
        close(fd);
        return NULL;
    }

    DIR *dir = fdopendir(fd);

    if (!dir) {
        close(fd);
    }

    return dir;
}

static FILE *open_single_link_regular_file_for_read(const char *path) {
    return open_regular_file_for_read_checked(path, true);
}

static int open_single_link_regular_file_for_read_fd(const char *path) {
    return open_regular_file_at_for_read_fd_checked(AT_FDCWD, path, true);
}

static FILE *open_single_link_regular_file_at_for_read(int dirfd, const char *path) {
    return open_regular_file_at_for_read_checked(dirfd, path, true);
}

static int open_single_link_regular_file_at_for_read_fd(int dirfd, const char *path) {
    return open_regular_file_at_for_read_fd_checked(dirfd, path, true);
}

static FILE *open_new_regular_file_at_for_write(int dirfd, const char *path) {
    struct stat st;

    int flags = O_WRONLY | O_CREAT | O_EXCL;
#ifdef O_CLOEXEC
    flags |= O_CLOEXEC;
#endif
#ifdef O_NOFOLLOW
    flags |= O_NOFOLLOW;
#endif
#ifdef O_NONBLOCK
    flags |= O_NONBLOCK;
#endif

    int fd = openat(dirfd, path, flags, 0600);

    if (fd < 0) {
        return NULL;
    }

    if (fstat(fd, &st) != 0 || !S_ISREG(st.st_mode) || st.st_nlink != 1) {
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

static FILE *open_new_regular_file_for_write(const char *path) {
    return open_new_regular_file_at_for_write(AT_FDCWD, path);
}

static bool flush_and_sync_file(FILE *file) {
    if (fflush(file) != 0) {
        return false;
    }

    int fd = fileno(file);

    if (fd < 0) {
        return false;
    }

    return fsync(fd) == 0;
}

static bool sync_directory_fd(int dirfd) {
    if (fsync(dirfd) == 0) {
        return true;
    }

    return errno == EINVAL
#ifdef ENOTSUP
        || errno == ENOTSUP
#endif
        ;
}

static bool sync_cwd_directory(void) {
    int flags = O_RDONLY;
#ifdef O_CLOEXEC
    flags |= O_CLOEXEC;
#endif
#ifdef O_DIRECTORY
    flags |= O_DIRECTORY;
#endif

    int fd = open(".", flags);

    if (fd < 0) {
        return false;
    }

    bool ok = sync_directory_fd(fd);
    close(fd);
    return ok;
}

static bool path_at_is_regular_or_missing(int dirfd, const char *path) {
    struct stat st;

    if (fstatat(dirfd, path, &st, AT_SYMLINK_NOFOLLOW) == 0) {
        return S_ISREG(st.st_mode) && st.st_nlink == 1;
    }

    return errno == ENOENT;
}

static bool path_is_regular_or_missing(const char *path) {
    return path_at_is_regular_or_missing(AT_FDCWD, path);
}

static bool unlink_regular_at_if_present(int dirfd, const char *path) {
    struct stat st;

    if (fstatat(dirfd, path, &st, AT_SYMLINK_NOFOLLOW) == 0) {
        if (!S_ISREG(st.st_mode) || st.st_nlink != 1) {
            return false;
        }

        return unlinkat(dirfd, path, 0) == 0;
    }

    return errno == ENOENT;
}

static bool unlink_regular_if_present(const char *path) {
    return unlink_regular_at_if_present(AT_FDCWD, path);
}

static FILE *open_report_for_write(int report_dir_fd) {
    if (!path_at_is_regular_or_missing(report_dir_fd, REPORT_FILE)) {
        return NULL;
    }
    if (!unlink_regular_at_if_present(report_dir_fd, REPORT_TMP_FILE)) {
        return NULL;
    }

    return open_new_regular_file_at_for_write(report_dir_fd, REPORT_TMP_FILE);
}

static const char *visible_path(const char *path) {
    if (path[0] == '.' && path[1] == '/') {
        return path + 2;
    }

    return path;
}

static char *read_file(const char *path) {
    FILE *f = open_single_link_regular_file_for_read(path);

    if (!f) {
        return NULL;
    }

    struct stat before_read_st;

    if (fstat(fileno(f), &before_read_st) != 0 ||
        !S_ISREG(before_read_st.st_mode) ||
        before_read_st.st_nlink != 1 ||
        before_read_st.st_size < 0 ||
        (uintmax_t)before_read_st.st_size > (uintmax_t)SIZE_MAX - 1u) {
        fclose(f);
        return NULL;
    }

    size_t file_len = (size_t)before_read_st.st_size;

    char *buf = calloc(file_len + 1, 1);

    if (!buf) {
        fclose(f);
        return NULL;
    }

    size_t read_count = fread(buf, 1, file_len, f);
    struct stat after_read_st;
    bool stat_ok = fstat(fileno(f), &after_read_st) == 0;
    bool read_ok = read_count == file_len && !ferror(f) &&
                   stat_ok &&
                   S_ISREG(after_read_st.st_mode) &&
                   after_read_st.st_nlink == 1 &&
                   after_read_st.st_size == before_read_st.st_size &&
                   memchr(buf, '\0', file_len) == NULL;
    bool close_ok = fclose(f) == 0;

    if (!read_ok || !close_ok) {
        free(buf);
        return NULL;
    }

    buf[file_len] = '\0';
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

static bool clear_hash_artifact(SealRun *run, const char *path, const char *failure) {
    if (!run || run->report_dir_fd < 0) {
        return false;
    }

    if (!unlink_regular_at_if_present(run->report_dir_fd, path)) {
        fail_run(run, failure);
        return false;
    }

    return true;
}

static bool clear_stale_hash_artifacts(SealRun *run) {
    bool ok = true;

    if (!clear_hash_artifact(run, HASH_LIST_FILE, "could not clear previous hash list")) {
        ok = false;
    }

    if (!clear_hash_artifact(run, HASH_LIST_TMP_FILE, "could not clear temporary hash list")) {
        ok = false;
    }

    return ok;
}

static bool stdout_is_healthy(void) {
    return fflush(stdout) == 0 && !ferror(stdout);
}

static int stdout_failure(const char *label) {
    fprintf(stderr, "could not write %s to stdout\n", label);
    return 1;
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

static bool collected_filelist_push(
    CollectedFileList *list,
    const char *path,
    const struct stat *st
) {
    if (list->len == list->cap) {
        size_t next_cap = list->cap == 0 ? 64 : list->cap * 2;
        CollectedFile *next = realloc(list->items, next_cap * sizeof(CollectedFile));

        if (!next) {
            return false;
        }

        list->items = next;
        list->cap = next_cap;
    }

    char *item = xstrdup(path);

    if (!item) {
        return false;
    }

    list->items[list->len].path = item;
    list->items[list->len].dev = st->st_dev;
    list->items[list->len].ino = st->st_ino;
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

static void collected_filelist_free(CollectedFileList *list) {
    for (size_t i = 0; i < list->len; i++) {
        free(list->items[i].path);
    }

    free(list->items);
    list->items = NULL;
    list->len = 0;
    list->cap = 0;
}

static int cmp_collected_file_path(const void *a, const void *b) {
    const CollectedFile *fa = a;
    const CollectedFile *fb = b;

    return strcmp(fa->path, fb->path);
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

static bool native_generated_artifact_path_is(const char *visible) {
    return strcmp(visible, REPORT_PATH) == 0 ||
           strcmp(visible, REPORT_TMP_PATH) == 0 ||
           strcmp(visible, HASH_LIST_PATH) == 0 ||
           strcmp(visible, HASH_LIST_TMP_PATH) == 0 ||
           strcmp(visible, LEGACY_SMOKE_REPORT_PATH) == 0 ||
           strcmp(visible, LEGACY_SMOKE_HASH_LIST_PATH) == 0 ||
           strcmp(visible, BASELINE_PATH) == 0 ||
           strcmp(visible, BASELINE_TMP_PATH) == 0;
}

static void collect_files(
    SealRun *run,
    CollectedFileList *list,
    const char *dir_path,
    const PathList *excludes,
    const struct stat *expected_dir
) {
    DIR *dir = open_directory_for_traversal(dir_path, expected_dir);

    if (!dir) {
        char msg[512];
        snprintf(msg, sizeof(msg), "could not open directory: %.400s", dir_path);
        fail_run(run, msg);
        return;
    }

    struct dirent *entry;

    errno = 0;
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
            snprintf(msg, sizeof(msg), "could not stat path: %.400s", path);
            fail_run(run, msg);
            continue;
        }

        const char *visible = visible_path(path);

        if (S_ISDIR(st.st_mode)) {
            if (path_excluded_dir(visible, entry->d_name, excludes)) {
                continue;
            }

            if (!hashlist_path_is_safe(visible)) {
                char msg[512];
                snprintf(msg, sizeof(msg), "refusing unsafe path in digest scope: %.400s", visible);
                fail_run(run, msg);
                continue;
            }

            collect_files(run, list, path, excludes, &st);
            continue;
        }

        if (path_excluded_file(visible, entry->d_name, excludes)) {
            continue;
        }

        if (native_generated_artifact_path_is(visible) &&
            S_ISREG(st.st_mode) &&
            st.st_nlink == 1) {
            continue;
        }

        if (!hashlist_path_is_safe(visible)) {
            char msg[512];
            snprintf(msg, sizeof(msg), "refusing unsafe path in digest scope: %.400s", visible);
            fail_run(run, msg);
            continue;
        }

        if (S_ISREG(st.st_mode)) {
            if (st.st_nlink != 1) {
                char msg[512];
                snprintf(msg, sizeof(msg), "refusing hard-linked file in digest scope: %.400s", visible_path(path));
                fail_run(run, msg);
                continue;
            }
            if (st.st_size < 0) {
                char msg[512];
                snprintf(msg, sizeof(msg), "refusing invalid-size file in digest scope: %.400s", visible_path(path));
                fail_run(run, msg);
                continue;
            }

            if (!collected_filelist_push(list, path, &st)) {
                fail_run(run, "out of memory while collecting file paths");
                closedir(dir);
                return;
            }
        } else if (S_ISLNK(st.st_mode)) {
            char msg[512];
            snprintf(msg, sizeof(msg), "refusing symlink in digest scope: %.400s", visible_path(path));
            fail_run(run, msg);
        } else {
            char msg[512];
            snprintf(msg, sizeof(msg), "refusing non-regular path in digest scope: %.400s", visible_path(path));
            fail_run(run, msg);
        }
    }

    if (errno != 0) {
        char msg[512];
        snprintf(msg, sizeof(msg), "could not read directory: %.400s", dir_path);
        fail_run(run, msg);
    }

    if (closedir(dir) != 0) {
        char msg[512];
        snprintf(msg, sizeof(msg), "could not close directory: %.400s", dir_path);
        fail_run(run, msg);
    }
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
    const CollectedFile *file,
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
    FILE *f = open_collected_file_for_read(file);
    off_t before_size;

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

    if (!collected_file_stream_observed_size(f, file, &before_size)) {
        fclose(f);
        free(buf);
        return false;
    }

    for (;;) {
        size_t n = fread(buf + prefix_len, 1, read_chunk, f);
        size_t total = prefix_len + n;

        for (size_t i = 0; i < markers->len; i++) {
            if (buffer_contains_marker(buf, total, markers->items[i])) {
                bool stable = collected_file_stream_size_matches(f, file, before_size);
                bool close_ok = fclose(f) == 0;
                free(buf);
                *read_ok = stable && close_ok;
                return *read_ok;
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

    bool stable = collected_file_stream_size_matches(f, file, before_size);

    if (fclose(f) != 0 || !stable) {
        free(buf);
        return false;
    }

    free(buf);
    *read_ok = true;
    return false;
}

static bool sha256_stream(FILE *f, char out_hex[65]) {
    bool ok = false;
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int digest_len = 0;
    unsigned char buf[8192];

    EVP_MD_CTX *ctx = EVP_MD_CTX_new();

    if (!ctx) {
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
    return ok;
}

static bool sha256_collected_file(const CollectedFile *file, char out_hex[65]) {
    FILE *f = open_collected_file_for_read(file);
    off_t before_size;

    if (!f) {
        return false;
    }

    if (!collected_file_stream_observed_size(f, file, &before_size)) {
        fclose(f);
        return false;
    }

    bool ok = sha256_stream(f, out_hex);

    if (!collected_file_stream_size_matches(f, file, before_size)) {
        ok = false;
    }

    if (fclose(f) != 0) {
        ok = false;
    }

    return ok;
}

static bool sha256_bytes(const unsigned char *buf, size_t len, char out_hex[65]) {
    bool ok = false;
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int digest_len = 0;

    EVP_MD_CTX *ctx = EVP_MD_CTX_new();

    if (!ctx) {
        return false;
    }

    if (EVP_DigestInit_ex(ctx, EVP_sha256(), NULL) != 1) {
        goto done;
    }

    if (len > 0 && EVP_DigestUpdate(ctx, buf, len) != 1) {
        goto done;
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
    return ok;
}

static bool sha256_file_at(int dirfd, const char *path, char out_hex[65]) {
    FILE *f = open_single_link_regular_file_at_for_read(dirfd, path);

    if (!f) {
        return false;
    }

    bool ok = sha256_stream(f, out_hex);

    if (fclose(f) != 0) {
        ok = false;
    }

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

static bool manifest_section_name_is_supported(const char *section, size_t section_len) {
    return section_matches(section, section_len, "project") ||
           section_matches(section, section_len, "seal") ||
           section_matches(section, section_len, "paths") ||
           section_matches(section, section_len, "policy") ||
           section_matches(section, section_len, "policy.required_files") ||
           section_matches(section, section_len, "policy.deny_filenames") ||
           section_matches(section, section_len, "policy.deny_contents") ||
           section_matches(section, section_len, "report") ||
           section_matches(section, section_len, "proof");
}

static bool update_manifest_array_depth(
    const char *p,
    const char *line_end,
    int *array_depth
) {
    bool in_string = false;
    bool escaped = false;

    while (p < line_end) {
        char c = *p++;

        if (in_string) {
            if (escaped) {
                escaped = false;
            } else if (c == '\\') {
                escaped = true;
            } else if (c == '"') {
                in_string = false;
            }
            continue;
        }

        if (c == '#') {
            break;
        }

        if (c == '"') {
            in_string = true;
        } else if (c == '[') {
            if (*array_depth == INT_MAX) {
                return false;
            }
            (*array_depth)++;
        } else if (c == ']') {
            if (*array_depth == 0) {
                return false;
            }
            (*array_depth)--;
        }
    }

    return !in_string;
}

static bool manifest_section_headers_supported(const char *manifest) {
    const char *line = manifest;
    int array_depth = 0;

    while (*line != '\0') {
        const char *line_end = strchr(line, '\n');

        if (!line_end) {
            line_end = line + strlen(line);
        }

        while (line_end > line && line_end[-1] == '\r') {
            line_end--;
        }

        const char *p = skip_line_spaces(line, line_end);

        if (array_depth == 0 && p < line_end && *p == '[') {
            const char *section;
            size_t section_len;

            if (!line_section_name(line, line_end, &section, &section_len) ||
                !manifest_section_name_is_supported(section, section_len)) {
                return false;
            }
        } else if (!update_manifest_array_depth(p, line_end, &array_depth)) {
            return false;
        }

        if (*line_end == '\0') {
            break;
        }

        line = line_end + 1;
    }

    return array_depth == 0;
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
                    const char *end = NULL;
                    const char *q = start;

                    while (q < line_end) {
                        char c = *q;
                        unsigned char uc = (unsigned char)c;

                        if (c == '"') {
                            end = q;
                            break;
                        }

                        if (c == '\\' || uc < 32 || uc == 127) {
                            return false;
                        }

                        q++;
                    }

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

        unsigned char uc = (unsigned char)c;

        if (c == '\\' || uc < 32 || uc == 127) {
            free(buf);
            return false;
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

            if (token[0] == '\0') {
                free(token);
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

static void check_manifest_section_headers(SealRun *run, const char *manifest) {
    if (manifest_section_headers_supported(manifest)) {
        pass(run, "manifest section headers are supported");
    } else {
        fail_run(run, "manifest section headers are supported");
    }
}

static void check_optional_manifest_text_assignment(
    SealRun *run,
    const char *manifest,
    const char *section_name,
    const char *key,
    const char *expected_value,
    const char *present_label,
    const char *absent_label
) {
    size_t count = manifest_assignment_count(manifest, section_name, key);

    if (count == 0) {
        pass(run, absent_label);
        return;
    }

    const char *start;
    size_t len;

    if (count != 1 ||
        !manifest_find_quoted_assignment(manifest, section_name, key, &start, &len) ||
        len == 0) {
        fail_run(run, present_label);
        return;
    }

    if (expected_value) {
        size_t expected_len = strlen(expected_value);

        if (len != expected_len || strncmp(start, expected_value, expected_len) != 0) {
            fail_run(run, present_label);
            return;
        }
    }

    pass(run, present_label);
}

static bool load_path_scope(
    SealRun *run,
    const char *manifest,
    PathList *includes,
    PathList *excludes
);

static bool load_required_files(SealRun *run, const char *manifest, PathList *required) {
    const char *value;
    size_t value_len;
    size_t required_count = manifest_assignment_count(manifest, "policy.required_files", "paths");

    if (required_count != 1 ||
        !manifest_find_assignment_value(manifest, "policy.required_files", "paths", &value, &value_len) ||
        !parse_string_array(value, value_len, required) ||
        pathlist_has_duplicate_items(required) ||
        !pathlist_all_safe(required, manifest_required_path_is_safe)) {
        fail_run(run, "policy required files are missing, duplicate, or malformed");
        return false;
    }

    return true;
}

static bool required_path_excluded_by_scope(const char *path, const PathList *excludes) {
    if (path_excluded_file(path, basename_of(path), excludes)) {
        return true;
    }

    for (const char *slash = strchr(path, '/'); slash; slash = strchr(slash + 1, '/')) {
        char dir_path[PATH_MAX];
        size_t dir_len = (size_t)(slash - path);

        if (dir_len == 0 || dir_len >= sizeof(dir_path)) {
            return true;
        }

        memcpy(dir_path, path, dir_len);
        dir_path[dir_len] = '\0';

        if (path_excluded_dir(dir_path, basename_of(dir_path), excludes)) {
            return true;
        }
    }

    return false;
}

static const char *first_required_file_excluded_from_scope(
    const PathList *required,
    const PathList *excludes
) {
    for (size_t i = 0; i < required->len; i++) {
        if (required_path_excluded_by_scope(required->items[i], excludes)) {
            return required->items[i];
        }
    }

    return NULL;
}

static const char *first_unusable_required_file(const PathList *required) {
    for (size_t i = 0; i < required->len; i++) {
        if (!required_file_is_single_link_regular(required->items[i])) {
            return required->items[i];
        }
    }

    return NULL;
}

static void check_manifest_shape(SealRun *run, const char *manifest) {
    section(run, "Manifest shape");

    check_manifest_section_headers(run, manifest);
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

static void check_project_identity_shape(SealRun *run, const char *manifest) {
    section(run, "Project identity");

    require_manifest_assignment(
        run,
        manifest,
        "project",
        "name",
        "Latticra",
        true,
        "project name is Latticra"
    );
    require_manifest_assignment(
        run,
        manifest,
        "project",
        "id",
        "latticra",
        true,
        "project id is latticra"
    );
    require_manifest_assignment(
        run,
        manifest,
        "project",
        "version",
        "0.1.0",
        true,
        "project version is 0.1.0"
    );
    require_manifest_assignment(
        run,
        manifest,
        "project",
        "repository",
        "https://github.com/Bryforge/Latticra",
        true,
        "project repository is canonical"
    );
    require_manifest_assignment(
        run,
        manifest,
        "project",
        "license",
        "SEE LICENSE",
        true,
        "project license is SEE LICENSE"
    );
    check_optional_manifest_text_assignment(
        run,
        manifest,
        "project",
        "description",
        NULL,
        "project description is present",
        "project description is absent"
    );
}

static void check_policy_shape(SealRun *run, const char *manifest) {
    section(run, "Policy shape");

    require_manifest_assignment(run, manifest, "policy", "require_readme", "true", false, "policy requires README");
    require_manifest_assignment(run, manifest, "policy", "require_license", "true", false, "policy requires LICENSE");
    require_manifest_assignment(run, manifest, "policy", "deny_private_keys", "true", false, "policy denies private keys");
    require_manifest_assignment(run, manifest, "policy", "deny_env_files", "true", false, "policy denies .env files");
    require_manifest_assignment(run, manifest, "policy", "deny_obvious_tokens", "true", false, "policy denies obvious token markers");

    size_t large_binary_count = manifest_assignment_count(manifest, "policy", "deny_large_binaries");

    if (large_binary_count == 0) {
        pass(run, "policy large binary denial is absent");
    } else if (large_binary_count == 1 &&
               manifest_has_assignment_value(manifest, "policy", "deny_large_binaries", "false", false)) {
        pass(run, "policy large binary denial is disabled");
    } else {
        fail_run(run, "policy large binary denial is disabled");
    }

    size_t max_file_size_count = manifest_assignment_count(manifest, "policy", "max_file_size_mb");

    if (max_file_size_count == 0) {
        pass(run, "policy max file size is absent");
    } else if (max_file_size_count == 1 &&
               manifest_has_assignment_value(manifest, "policy", "max_file_size_mb", "25", false)) {
        pass(run, "policy max file size is 25 MB");
    } else {
        fail_run(run, "policy max file size is 25 MB");
    }
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

static void check_empty_proof_field(
    SealRun *run,
    const char *manifest,
    const char *key,
    const char *label
) {
    size_t proof_count = manifest_assignment_count(manifest, "proof", key);
    char msg[160];

    if (proof_count == 0) {
        snprintf(msg, sizeof(msg), "proof %s is absent", label);
        pass(run, msg);
        return;
    }

    if (proof_count == 1 &&
        manifest_has_assignment_value(manifest, "proof", key, "", true)) {
        snprintf(msg, sizeof(msg), "proof %s is empty", label);
        pass(run, msg);
    } else {
        snprintf(msg, sizeof(msg), "proof %s is empty", label);
        fail_run(run, msg);
    }
}

static void check_proof_shape(SealRun *run, const char *manifest) {
    section(run, "Proof shape");

    check_empty_proof_field(run, manifest, "manifest_hash", "manifest hash");
    check_empty_proof_field(run, manifest, "root_hash", "root hash");
    check_empty_proof_field(run, manifest, "signature_algorithm", "signature algorithm");
    check_empty_proof_field(run, manifest, "signature", "signature");
    check_empty_proof_field(run, manifest, "public_key", "public key");
}

static void check_required_files(SealRun *run, const char *manifest) {
    section(run, "Required project files");

    PathList required;
    required.items = NULL;
    required.len = 0;
    required.cap = 0;

    PathList includes;
    includes.items = NULL;
    includes.len = 0;
    includes.cap = 0;

    PathList excludes;
    excludes.items = NULL;
    excludes.len = 0;
    excludes.cap = 0;

    if (!load_required_files(run, manifest, &required)) {
        pathlist_free(&required);
        return;
    }

    char msg[512];
    snprintf(msg, sizeof(msg), "loaded %zu required file path(s)", required.len);
    pass(run, msg);

    for (size_t i = 0; i < required.len; i++) {
        if (required_file_is_single_link_regular(required.items[i])) {
            snprintf(msg, sizeof(msg), "required file exists: %.400s", required.items[i]);
            pass(run, msg);
        } else {
            snprintf(msg, sizeof(msg), "required file missing or unsafe: %.400s", required.items[i]);
            fail_run(run, msg);
        }
    }

    if (!load_path_scope(run, manifest, &includes, &excludes)) {
        fail_run(run, "required file digest scope skipped because path scope was invalid");
        pathlist_free(&required);
        pathlist_free(&includes);
        pathlist_free(&excludes);
        return;
    }

    const char *excluded_required =
        first_required_file_excluded_from_scope(&required, &excludes);

    if (excluded_required != NULL) {
        snprintf(msg, sizeof(msg), "required file excluded from digest scope: %.400s", excluded_required);
        fail_run(run, msg);
    } else {
        pass(run, "required files remain inside digest scope");
    }

    pathlist_free(&required);
    pathlist_free(&includes);
    pathlist_free(&excludes);
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

    CollectedFileList list;
    list.items = NULL;
    list.len = 0;
    list.cap = 0;

    int traversal_failures_before = run->failures;

    collect_files(run, &list, ".", &excludes, NULL);

    if (run->failures != traversal_failures_before) {
        fail_run(run, "policy denial scan incomplete because traversal failed");
        collected_filelist_free(&list);
        pathlist_free(&includes);
        pathlist_free(&excludes);
        pathlist_free(&filename_patterns);
        pathlist_free(&content_markers);
        return;
    }

    qsort(list.items, list.len, sizeof(CollectedFile), cmp_collected_file_path);

    size_t filename_hits = 0;
    size_t content_hits = 0;
    size_t inspect_failures = 0;

    for (size_t i = 0; i < list.len; i++) {
        CollectedFile *file = &list.items[i];
        const char *path = file->path;

        if (denied_secret_filename(path, &filename_patterns)) {
            char msg[512];
            snprintf(msg, sizeof(msg), "possible secret-bearing filename: %.400s", visible_path(path));
            fail_run(run, msg);
            filename_hits++;
        }

        bool read_ok;

        if (file_contains_secret_marker(file, &content_markers, &read_ok)) {
            char msg[512];
            snprintf(msg, sizeof(msg), "possible secret content marker in: %.400s", visible_path(path));
            fail_run(run, msg);
            content_hits++;
        } else if (!read_ok) {
            char msg[512];
            snprintf(msg, sizeof(msg), "could not inspect file for policy markers: %.400s", visible_path(path));
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

    collected_filelist_free(&list);
    pathlist_free(&includes);
    pathlist_free(&excludes);
    pathlist_free(&filename_patterns);
    pathlist_free(&content_markers);
}

static void write_digest_summary(
    SealRun *run,
    const char *manifest,
    bool manifest_report_shape_ok
) {
    section(run, "Digest summary");

    if (!run || run->report_dir_fd < 0) {
        fail_run(run, "hash list not written because report directory was unavailable");
        return;
    }

    int pre_digest_failures = run->failures;

    close_hash_list_fd(run);

    CollectedFileList list;
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

    if (!clear_stale_hash_artifacts(run)) {
        return;
    }

    if (!load_path_scope(run, manifest, &includes, &excludes)) {
        fail_run(run, "hash list not written because path scope was invalid");
        pathlist_free(&includes);
        pathlist_free(&excludes);
        return;
    }

    PathList required;
    required.items = NULL;
    required.len = 0;
    required.cap = 0;

    if (!load_required_files(run, manifest, &required)) {
        fail_run(run, "hash list not written because required file policy was invalid");
        pathlist_free(&required);
        pathlist_free(&includes);
        pathlist_free(&excludes);
        return;
    }

    const char *missing_required = first_unusable_required_file(&required);

    if (missing_required) {
        char msg[512];
        snprintf(
            msg,
            sizeof(msg),
            "hash list not written because required file is missing or unsafe: %.400s",
            missing_required
        );
        fail_run(run, msg);
        pathlist_free(&required);
        pathlist_free(&includes);
        pathlist_free(&excludes);
        return;
    }

    const char *excluded_required = first_required_file_excluded_from_scope(&required, &excludes);

    if (excluded_required) {
        char msg[512];
        snprintf(
            msg,
            sizeof(msg),
            "hash list not written because required file is excluded from digest scope: %.400s",
            excluded_required
        );
        fail_run(run, msg);
        pathlist_free(&required);
        pathlist_free(&includes);
        pathlist_free(&excludes);
        return;
    }

    if (!manifest_report_shape_ok) {
        fail_run(run, "hash list not written because manifest, policy, or report shape was invalid");
        pathlist_free(&required);
        pathlist_free(&includes);
        pathlist_free(&excludes);
        return;
    }

    int traversal_failures_before = run->failures;

    collect_files(run, &list, ".", &excludes, NULL);

    if (run->failures != traversal_failures_before) {
        fail_run(run, "hash list not written because digest traversal failed");
        pathlist_free(&required);
        collected_filelist_free(&list);
        pathlist_free(&includes);
        pathlist_free(&excludes);
        return;
    }

    if (pre_digest_failures != 0) {
        fail_run(run, "hash list not written because earlier checks failed");
        pathlist_free(&required);
        collected_filelist_free(&list);
        pathlist_free(&includes);
        pathlist_free(&excludes);
        return;
    }

    qsort(list.items, list.len, sizeof(CollectedFile), cmp_collected_file_path);

    FILE *hashes = open_new_regular_file_at_for_write(
        run->report_dir_fd,
        HASH_LIST_TMP_FILE
    );

    if (!hashes) {
        fail_run(run, "could not write hash list");
        pathlist_free(&required);
        collected_filelist_free(&list);
        pathlist_free(&includes);
        pathlist_free(&excludes);
        return;
    }

    size_t hashed_count = 0;
    bool hash_write_ok = true;

    for (size_t i = 0; i < list.len; i++) {
        char hex[65];
        CollectedFile *file = &list.items[i];

        if (!sha256_collected_file(file, hex)) {
            char msg[512];
            snprintf(msg, sizeof(msg), "could not hash file: %.400s", visible_path(file->path));
            fail_run(run, msg);
            continue;
        }

        if (fprintf(hashes, "%s  %s\n", hex, visible_path(file->path)) < 0) {
            fail_run(run, "could not write hash entry");
            hash_write_ok = false;
            break;
        }

        hashed_count++;
    }

    if (!flush_and_sync_file(hashes)) {
        fail_run(run, "could not sync hash list");
        hash_write_ok = false;
    }

    if (fclose(hashes) != 0) {
        fail_run(run, "could not finalize hash list");
        hash_write_ok = false;
    }

    if (run->failures != traversal_failures_before || !hash_write_ok) {
        (void)unlink_regular_at_if_present(run->report_dir_fd, HASH_LIST_TMP_FILE);
        fail_run(run, "hash list not written because file hashing failed");
        pathlist_free(&required);
        collected_filelist_free(&list);
        pathlist_free(&includes);
        pathlist_free(&excludes);
        return;
    }

    if (!path_at_is_regular_or_missing(run->report_dir_fd, HASH_LIST_FILE)) {
        (void)unlink_regular_at_if_present(run->report_dir_fd, HASH_LIST_TMP_FILE);
        fail_run(run, "could not promote hash list");
        pathlist_free(&required);
        collected_filelist_free(&list);
        pathlist_free(&includes);
        pathlist_free(&excludes);
        return;
    }

    if (renameat(
            run->report_dir_fd,
            HASH_LIST_TMP_FILE,
            run->report_dir_fd,
            HASH_LIST_FILE
        ) != 0) {
        (void)unlink_regular_at_if_present(run->report_dir_fd, HASH_LIST_TMP_FILE);
        fail_run(run, "could not promote hash list");
        pathlist_free(&required);
        collected_filelist_free(&list);
        pathlist_free(&includes);
        pathlist_free(&excludes);
        return;
    }

    if (!sync_directory_fd(run->report_dir_fd)) {
        fail_run(run, "could not sync promoted hash list");
        pathlist_free(&required);
        collected_filelist_free(&list);
        pathlist_free(&includes);
        pathlist_free(&excludes);
        return;
    }

    char manifest_hex[65];
    char root_hex[65];

    if (sha256_bytes((const unsigned char *)manifest, strlen(manifest), manifest_hex)) {
        char line[160];
        snprintf(line, sizeof(line), "manifest_sha256: %s", manifest_hex);
        emit(run, line);
    } else {
        fail_run(run, "could not hash parsed manifest");
    }

    if (sha256_file_at(run->report_dir_fd, HASH_LIST_FILE, root_hex)) {
        char line[160];
        snprintf(line, sizeof(line), "root_digest_v0_2: %s", root_hex);
        emit(run, line);
    } else {
        fail_run(run, "could not hash digest list");
    }

    run->hash_list_fd = open_single_link_regular_file_at_for_read_fd(
        run->report_dir_fd,
        HASH_LIST_FILE
    );

    if (run->hash_list_fd < 0) {
        fail_run(run, "could not retain generated hash list");
    }

    char count_line[160];
    snprintf(count_line, sizeof(count_line), "hashed_files: %zu", hashed_count);
    emit(run, count_line);

    emit(run, "hash_list: " HASH_LIST_PATH);

    pathlist_free(&required);
    collected_filelist_free(&list);
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

static void close_report_dir(SealRun *run) {
    if (run && run->report_dir_fd >= 0) {
        close(run->report_dir_fd);
        run->report_dir_fd = -1;
    }
}

static void close_hash_list_fd(SealRun *run) {
    if (run && run->hash_list_fd >= 0) {
        close(run->hash_list_fd);
        run->hash_list_fd = -1;
    }
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

static int finalize_report(SealRun *run, int code, const char *stdout_label) {
    if (!run->report) {
        close_report_dir(run);
        close_hash_list_fd(run);
        return code;
    }

    if (!flush_and_sync_file(run->report)) {
        FILE *report = run->report;
        run->report = NULL;
        (void)fclose(report);
        if (run->report_dir_fd >= 0) {
            (void)unlink_regular_at_if_present(run->report_dir_fd, REPORT_TMP_FILE);
        }
        close_report_dir(run);
        close_hash_list_fd(run);
        fprintf(stderr, "could not sync report: %s\n", REPORT_PATH);
        return 2;
    }

    if (fclose(run->report) != 0) {
        run->report = NULL;
        if (run->report_dir_fd >= 0) {
            (void)unlink_regular_at_if_present(run->report_dir_fd, REPORT_TMP_FILE);
        }
        close_report_dir(run);
        close_hash_list_fd(run);
        fprintf(stderr, "could not finalize report: %s\n", REPORT_PATH);
        return 2;
    }

    run->report = NULL;

    if (run->report_dir_fd < 0 ||
        !path_at_is_regular_or_missing(run->report_dir_fd, REPORT_FILE)) {
        if (run->report_dir_fd >= 0) {
            (void)unlink_regular_at_if_present(run->report_dir_fd, REPORT_TMP_FILE);
        }
        close_report_dir(run);
        close_hash_list_fd(run);
        fprintf(stderr, "could not promote report: %s\n", REPORT_PATH);
        return 2;
    }

    if (renameat(
            run->report_dir_fd,
            REPORT_TMP_FILE,
            run->report_dir_fd,
            REPORT_FILE
        ) != 0) {
        (void)unlink_regular_at_if_present(run->report_dir_fd, REPORT_TMP_FILE);
        close_report_dir(run);
        close_hash_list_fd(run);
        fprintf(stderr, "could not promote report: %s\n", REPORT_PATH);
        return 2;
    }

    if (!sync_directory_fd(run->report_dir_fd)) {
        close_report_dir(run);
        close_hash_list_fd(run);
        fprintf(stderr, "could not sync promoted report: %s\n", REPORT_PATH);
        return 2;
    }

    close_report_dir(run);

    if (stdout_label && !stdout_is_healthy()) {
        close_hash_list_fd(run);
        return stdout_failure(stdout_label);
    }

    if (!(run->preserve_hash_list_fd && code == 0)) {
        close_hash_list_fd(run);
    }

    return code;
}

static int run_check(bool preserve_hash_list_fd, int *out_hash_list_fd) {
    if (out_hash_list_fd) {
        *out_hash_list_fd = -1;
    }

    int report_dir_fd = open_report_dir_for_artifacts(true, NULL);

    if (report_dir_fd < 0) {
        return 2;
    }

    SealRun run;
    run.failures = 0;
    run.warnings = 0;
    run.report = NULL;
    run.report_dir_fd = report_dir_fd;
    run.hash_list_fd = -1;
    run.preserve_hash_list_fd = preserve_hash_list_fd;
    run.report = open_report_for_write(run.report_dir_fd);

    if (!run.report) {
        close_report_dir(&run);
        fprintf(stderr, "could not open report: %s\n", REPORT_PATH);
        return 2;
    }

    write_header(&run);

    section(&run, "Hash artifact freshness");

    if (!clear_stale_hash_artifacts(&run)) {
        int code = finish(&run);
        return finalize_report(&run, code, "check report");
    }

    pass(&run, "stale hash artifacts cleared before check");

    section(&run, "Manifest presence");

    char *manifest = read_file(MANIFEST_PATH);

    if (!manifest) {
        fail_run(&run, "latticra.seal is missing or unreadable");
        int code = finish(&run);
        return finalize_report(&run, code, "check report");
    }

    pass(&run, "latticra.seal exists");

    int shape_failures_before = run.failures;

    check_manifest_shape(&run, manifest);
    check_project_identity_shape(&run, manifest);
    check_policy_shape(&run, manifest);
    check_report_shape(&run, manifest);
    check_proof_shape(&run, manifest);
    bool manifest_report_shape_ok = run.failures == shape_failures_before;

    check_required_files(&run, manifest);
    check_policy_denials(&run, manifest);
    write_digest_summary(&run, manifest, manifest_report_shape_ok);

    free(manifest);

    int code = finish(&run);
    code = finalize_report(&run, code, "check report");

    if (code == 0 && preserve_hash_list_fd && out_hash_list_fd &&
        run.hash_list_fd >= 0) {
        *out_hash_list_fd = run.hash_list_fd;
        run.hash_list_fd = -1;
    }

    close_hash_list_fd(&run);
    return code;
}

static int command_check(void) {
    return run_check(false, NULL);
}

static bool print_manifest_value(
    const char *manifest,
    const char *section_name,
    const char *key,
    const char *label,
    const char *expected_value
) {
    const char *start;
    size_t len;
    size_t count = manifest_assignment_count(manifest, section_name, key);

    if (count == 0) {
        printf("%s: missing\n", label);
        return false;
    }

    if (count > 1) {
        printf("%s: duplicate\n", label);
        return false;
    }

    if (!manifest_find_quoted_assignment(manifest, section_name, key, &start, &len)) {
        printf("%s: malformed\n", label);
        return false;
    }

    if (len == 0) {
        printf("%s: empty\n", label);
        return false;
    }

    printf("%s: ", label);
    (void)fwrite(start, 1, len, stdout);

    if (expected_value) {
        size_t expected_len = strlen(expected_value);

        if (len != expected_len || strncmp(start, expected_value, expected_len) != 0) {
            puts(" (unsupported)");
            return false;
        }
    }

    putchar('\n');
    return true;
}

static int command_manifest(void) {
    char *manifest = read_file(MANIFEST_PATH);

    if (!manifest) {
        fprintf(stderr, "could not read %s\n", MANIFEST_PATH);
        return 1;
    }

    puts("Latticra Seal Manifest Summary");
    puts("------------------------------");

    bool ok = true;

    if (manifest_section_headers_supported(manifest)) {
        puts("Manifest Sections: supported");
    } else {
        puts("Manifest Sections: malformed or unsupported");
        ok = false;
    }
    if (!print_manifest_value(manifest, "", "schema", "Schema", "latticra.seal/v0.1")) {
        ok = false;
    }
    if (!print_manifest_value(manifest, "", "format", "Format", "toml")) {
        ok = false;
    }
    if (!print_manifest_value(manifest, "", "kind", "Kind", "local-integrity-manifest")) {
        ok = false;
    }
    if (!print_manifest_value(manifest, "project", "name", "Project", "Latticra")) {
        ok = false;
    }
    if (!print_manifest_value(manifest, "project", "id", "Project ID", "latticra")) {
        ok = false;
    }
    if (!print_manifest_value(manifest, "project", "version", "Project Version", "0.1.0")) {
        ok = false;
    }
    if (!print_manifest_value(
        manifest,
        "project",
        "repository",
        "Repository",
        "https://github.com/Bryforge/Latticra"
    )) {
        ok = false;
    }
    if (!print_manifest_value(manifest, "project", "license", "License", "SEE LICENSE")) {
        ok = false;
    }
    if (!print_manifest_value(manifest, "seal", "mode", "Seal Mode", "local-integrity")) {
        ok = false;
    }
    if (!print_manifest_value(manifest, "seal", "status", "Seal Status", "unsigned")) {
        ok = false;
    }
    if (!print_manifest_value(manifest, "seal", "algorithm", "Digest Algorithm", "sha256")) {
        ok = false;
    }
    if (!print_manifest_value(manifest, "seal", "digest_encoding", "Digest Encoding", "hex")) {
        ok = false;
    }
    if (!print_manifest_value(
        manifest,
        "seal",
        "canonicalization",
        "Canonicalization",
        "relative-path + raw-bytes + unix-lf-preferred"
    )) {
        ok = false;
    }
    if (!print_manifest_value(manifest, "seal", "trust_boundary", "Trust Boundary", "project-root")) {
        ok = false;
    }

    free(manifest);

    if (!stdout_is_healthy()) {
        return stdout_failure("manifest summary");
    }

    if (!ok) {
        fprintf(
            stderr,
            "manifest summary failed: required fields are missing, duplicate, malformed, empty, or unsupported\n"
        );
        return 1;
    }

    return 0;
}



static bool files_equal_fd_pair(int a_fd, int b_fd);

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

static bool read_hash_list_stream(FILE *f, HashList *list) {
    char *line = NULL;
    size_t cap = 0;
    bool ok = true;

    for (;;) {
        ssize_t nread = getline(&line, &cap, f);

        if (nread < 0) {
            ok = feof(f) && !ferror(f);
            break;
        }

        size_t line_len = (size_t)nread;

        if (memchr(line, '\0', line_len) != NULL) {
            ok = false;
            break;
        }

        if (memchr(line, '\r', line_len) != NULL) {
            ok = false;
            break;
        }

        if (line_len == 0 || line[line_len - 1] != '\n') {
            ok = false;
            break;
        }

        line_len--;
        if (line_len > 8191) {
            ok = false;
            break;
        }

        line[line_len] = '\0';

        if (line_len < 67 || line[64] != ' ' || line[65] != ' ') {
            ok = false;
            break;
        }

        char hash[65];
        memcpy(hash, line, 64);
        hash[64] = '\0';

        if (!is_sha256_hex(hash)) {
            ok = false;
            break;
        }

        char *file_path = line + 66;

        if (*file_path == '\0' || *file_path == ' ' || *file_path == '\t') {
            ok = false;
            break;
        }

        if (!hashlist_path_is_safe(file_path)) {
            ok = false;
            break;
        }

        if (list->len > 0 && strcmp(list->items[list->len - 1].path, file_path) >= 0) {
            ok = false;
            break;
        }

        if (!hashlist_push(list, hash, file_path)) {
            ok = false;
            break;
        }
    }

    free(line);
    return ok && list->len > 0;
}

static FILE *open_stream_from_fd_start(int fd) {
    if (fd < 0) {
        return NULL;
    }

    int dup_fd = dup(fd);

    if (dup_fd < 0) {
        return NULL;
    }

    if (lseek(dup_fd, 0, SEEK_SET) < 0) {
        close(dup_fd);
        return NULL;
    }

    FILE *f = fdopen(dup_fd, "r");

    if (!f) {
        close(dup_fd);
    }

    return f;
}

static bool read_hash_list_fd(int fd, HashList *list) {
    off_t before_size;

    if (!fd_single_link_regular_size(fd, &before_size) || before_size <= 0) {
        return false;
    }

    FILE *f = open_stream_from_fd_start(fd);

    if (!f) {
        return false;
    }

    bool ok = read_hash_list_stream(f, list);

    if (fclose(f) != 0) {
        ok = false;
    }

    if (ok && !fd_size_matches(fd, before_size)) {
        ok = false;
    }

    return ok;
}

static void emit_change(SealRun *run, const char *kind, const char *path) {
    printf("%s: %s\n", kind, path);

    if (run && run->report) {
        fprintf(run->report, "%s: %s\n", kind, path);
    }
}


static void compare_hash_lists_report(
    SealRun *run,
    int baseline_fd,
    int current_fd
) {
    if (files_equal_fd_pair(current_fd, baseline_fd)) {
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

    if (!read_hash_list_fd(baseline_fd, &baseline)) {
        hashlist_free(&baseline);
        fail_run(run, "could not read saved baseline");
        return;
    }

    if (!read_hash_list_fd(current_fd, &current)) {
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

static bool copy_file_fd_to_path(int src_fd, const char *dst) {
    off_t before_size;

    if (!fd_single_link_regular_size(src_fd, &before_size) || before_size <= 0) {
        return false;
    }

    FILE *in = open_stream_from_fd_start(src_fd);

    if (!in) {
        return false;
    }

    FILE *out = open_new_regular_file_for_write(dst);

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

    if (ok && !flush_and_sync_file(out)) {
        ok = false;
    }

    if (fclose(out) != 0) {
        ok = false;
    }

    if (fclose(in) != 0) {
        ok = false;
    }

    if (ok && !fd_size_matches(src_fd, before_size)) {
        ok = false;
    }

    return ok;
}

static bool write_baseline_atomic(int hash_fd) {
    if (!path_is_regular_or_missing(BASELINE_PATH)) {
        return false;
    }

    if (!unlink_regular_if_present(BASELINE_TMP_PATH)) {
        return false;
    }

    if (!copy_file_fd_to_path(hash_fd, BASELINE_TMP_PATH)) {
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

    return sync_cwd_directory();
}

static bool file_streams_equal(FILE *a, FILE *b) {
    unsigned char a_buf[8192];
    unsigned char b_buf[8192];

    for (;;) {
        size_t a_len = fread(a_buf, 1, sizeof(a_buf), a);
        size_t b_len = fread(b_buf, 1, sizeof(b_buf), b);

        if (a_len != b_len) {
            return false;
        }

        if (a_len > 0 && memcmp(a_buf, b_buf, a_len) != 0) {
            return false;
        }

        if (a_len < sizeof(a_buf)) {
            return !ferror(a) && !ferror(b);
        }
    }
}

static bool files_equal_fd_pair(int a_fd, int b_fd) {
    off_t a_before_size;
    off_t b_before_size;

    if (!fd_single_link_regular_size(a_fd, &a_before_size) ||
        !fd_single_link_regular_size(b_fd, &b_before_size)) {
        return false;
    }

    FILE *fa = open_stream_from_fd_start(a_fd);

    if (!fa) {
        return false;
    }

    FILE *fb = open_stream_from_fd_start(b_fd);

    if (!fb) {
        fclose(fa);
        return false;
    }

    bool equal = file_streams_equal(fa, fb);

    if (fclose(fa) != 0) {
        equal = false;
    }
    if (fclose(fb) != 0) {
        equal = false;
    }

    if (equal &&
        (!fd_size_matches(a_fd, a_before_size) ||
         !fd_size_matches(b_fd, b_before_size))) {
        equal = false;
    }

    return equal;
}

static void print_missing_file_hint(const char *path, const char *missing_hint) {
    fprintf(stderr, "no file found at %s\n", path);

    if (missing_hint) {
        fprintf(stderr, "%s\n", missing_hint);
    }
}

static int print_fd_to_stdout(int fd, const char *display_path) {
    off_t before_size;

    if (!fd_single_link_regular_size(fd, &before_size) || before_size <= 0) {
        fprintf(stderr, "could not read %s\n", display_path);
        return 1;
    }

    FILE *f = open_stream_from_fd_start(fd);
    unsigned char buf[8192];
    bool read_ok = true;
    bool write_ok = true;

    if (!f) {
        fprintf(stderr, "could not read %s\n", display_path);
        return 1;
    }

    for (;;) {
        size_t n = fread(buf, 1, sizeof(buf), f);

        if (n > 0 && fwrite(buf, 1, n, stdout) != n) {
            write_ok = false;
            break;
        }

        if (n < sizeof(buf)) {
            if (ferror(f)) {
                read_ok = false;
            }

            break;
        }
    }

    bool close_ok = fclose(f) == 0;

    if (!read_ok || !close_ok) {
        fprintf(stderr, "could not read %s\n", display_path);
        return 1;
    }

    if (!fd_size_matches(fd, before_size)) {
        fprintf(stderr, "could not read %s\n", display_path);
        return 1;
    }

    if (!write_ok || !stdout_is_healthy()) {
        return stdout_failure(display_path);
    }

    return 0;
}

static int print_file_to_stdout_at(
    int dirfd,
    const char *name,
    const char *display_path,
    const char *missing_hint
) {
    struct stat st;
    int fd = open_single_link_regular_file_at_for_read_fd(dirfd, name);

    if (fd < 0) {
        print_missing_file_hint(display_path, missing_hint);
        return 1;
    }

    if (fstat(fd, &st) != 0 || st.st_size <= 0) {
        close(fd);
        fprintf(stderr, "report artifact is empty: %s\n", display_path);
        return 1;
    }

    int code = print_fd_to_stdout(fd, display_path);
    close(fd);
    return code;
}

static int command_baseline(void) {
    int hash_list_fd = -1;
    int code = run_check(true, &hash_list_fd);

    if (code != 0) {
        if (hash_list_fd >= 0) {
            close(hash_list_fd);
        }
        fprintf(stderr, "baseline refused because check did not pass\n");
        return code;
    }

    if (hash_list_fd < 0) {
        fprintf(stderr, "could not write baseline: %s\n", BASELINE_PATH);
        return 1;
    }

    bool baseline_ok = write_baseline_atomic(hash_list_fd);
    close(hash_list_fd);

    if (!baseline_ok) {
        fprintf(stderr, "could not write baseline: %s\n", BASELINE_PATH);
        return 1;
    }

    printf("Baseline written to: %s\n", BASELINE_PATH);
    return stdout_is_healthy() ? 0 : stdout_failure("baseline");
}


static int command_verify(void) {
    int report_dir_fd = open_report_dir_for_artifacts(true, NULL);

    if (report_dir_fd < 0) {
        return 2;
    }

    SealRun run;
    run.failures = 0;
    run.warnings = 0;
    run.report = NULL;
    run.report_dir_fd = report_dir_fd;
    run.hash_list_fd = -1;
    run.preserve_hash_list_fd = false;
    run.report = open_report_for_write(run.report_dir_fd);

    if (!run.report) {
        close_report_dir(&run);
        fprintf(stderr, "could not open report: %s\n", REPORT_PATH);
        return 2;
    }

    write_header(&run);

    section(&run, "Hash artifact freshness");

    if (!clear_stale_hash_artifacts(&run)) {
        int code = finish(&run);
        return finalize_report(&run, code, "verify report");
    }

    pass(&run, "stale hash artifacts cleared before verify");

    section(&run, "Baseline presence");

    int baseline_fd = open_single_link_regular_file_for_read_fd(BASELINE_PATH);
    HashList baseline_probe;
    baseline_probe.items = NULL;
    baseline_probe.len = 0;
    baseline_probe.cap = 0;

    if (baseline_fd < 0 || !read_hash_list_fd(baseline_fd, &baseline_probe)) {
        if (baseline_fd >= 0) {
            close(baseline_fd);
        }
        hashlist_free(&baseline_probe);
        fail_run(&run, "latticra.seal.lock is missing or unreadable");
        int code = finish(&run);
        return finalize_report(&run, code, "verify report");
    }

    hashlist_free(&baseline_probe);
    pass(&run, "latticra.seal.lock exists");

    section(&run, "Manifest presence");

    char *manifest = read_file(MANIFEST_PATH);

    if (!manifest) {
        close(baseline_fd);
        fail_run(&run, "latticra.seal is missing or unreadable");
        int code = finish(&run);
        return finalize_report(&run, code, "verify report");
    }

    pass(&run, "latticra.seal exists");

    int shape_failures_before = run.failures;

    check_manifest_shape(&run, manifest);
    check_project_identity_shape(&run, manifest);
    check_policy_shape(&run, manifest);
    check_report_shape(&run, manifest);
    check_proof_shape(&run, manifest);
    bool manifest_report_shape_ok = run.failures == shape_failures_before;

    check_required_files(&run, manifest);
    check_policy_denials(&run, manifest);
    write_digest_summary(&run, manifest, manifest_report_shape_ok);

    free(manifest);

    section(&run, "Baseline comparison");

    if (run.failures == 0) {
        compare_hash_lists_report(&run, baseline_fd, run.hash_list_fd);
    } else {
        warn_run(&run, "baseline comparison skipped because earlier checks failed");
    }

    close(baseline_fd);
    int code = finish(&run);
    return finalize_report(&run, code, "verify report");
}

static int command_report(void) {
    bool report_dir_missing = false;
    int report_dir_fd = open_report_dir_for_artifacts(false, &report_dir_missing);

    if (report_dir_fd < 0) {
        if (report_dir_missing) {
            print_missing_file_hint(REPORT_PATH, "run: ./build/latticra-seal check");
            return 1;
        }

        return 2;
    }

    int code = print_file_to_stdout_at(
        report_dir_fd,
        REPORT_FILE,
        REPORT_PATH,
        "run: ./build/latticra-seal check"
    );

    close(report_dir_fd);
    return code;
}

static int command_hashes(void) {
    bool report_dir_missing = false;
    int report_dir_fd = open_report_dir_for_artifacts(false, &report_dir_missing);

    if (report_dir_fd < 0) {
        if (report_dir_missing) {
            print_missing_file_hint(HASH_LIST_PATH, "run: ./build/latticra-seal check");
            return 1;
        }

        return 2;
    }

    int hash_list_fd = open_single_link_regular_file_at_for_read_fd(
        report_dir_fd,
        HASH_LIST_FILE
    );

    if (hash_list_fd < 0) {
        print_missing_file_hint(HASH_LIST_PATH, "run: ./build/latticra-seal check");
        close(report_dir_fd);
        return 1;
    }

    HashList parsed;
    parsed.items = NULL;
    parsed.len = 0;
    parsed.cap = 0;

    if (!read_hash_list_fd(hash_list_fd, &parsed)) {
        hashlist_free(&parsed);
        close(hash_list_fd);
        close(report_dir_fd);
        fprintf(stderr, "hash list artifact is malformed: %s\n", HASH_LIST_PATH);
        return 1;
    }

    hashlist_free(&parsed);

    int code = print_fd_to_stdout(hash_list_fd, HASH_LIST_PATH);
    close(hash_list_fd);
    close(report_dir_fd);
    return code;
}

static int command_version(void) {
    puts("latticra-seal " LATTICRA_SEAL_VERSION);
    return stdout_is_healthy() ? 0 : stdout_failure("version");
}

static int print_hybrid_result(
    const char *label,
    const latticra_seal_hybrid_envelope_result_t *result
) {
    char rendered[LATTICRA_SEAL_HYBRID_ENVELOPE_REPORT_MAX];

    if (latticra_seal_hybrid_envelope_report(result, rendered, sizeof(rendered)) != LATTICRA_STATUS_OK) {
        fprintf(stderr, "could not render hybrid envelope %s report\n", label);
        return 1;
    }

    printf("== %s ==\n", label);
    fputs(rendered, stdout);
    return stdout_is_healthy() ? 0 : stdout_failure("hybrid envelope report");
}

static int print_hybrid_provider_self_test_result(
    const latticra_seal_hybrid_provider_self_test_t *self_test
) {
    char rendered[LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_REPORT_MAX];

    if (latticra_seal_hybrid_provider_self_test_report(
            self_test,
            rendered,
            sizeof(rendered)) != LATTICRA_STATUS_OK) {
        fprintf(stderr, "could not render hybrid provider self-test report\n");
        return 1;
    }

    fputs(rendered, stdout);
    return stdout_is_healthy() ? 0 : stdout_failure("hybrid provider self-test report");
}

static int command_hybrid(void) {
    unsigned char record[
        LATTICRA_SEAL_HYBRID_RECORD_HEADER_BYTES +
            sizeof(HYBRID_SELF_CHECK_PLAINTEXT) - 1u +
            LATTICRA_SEAL_HYBRID_RECORD_COMMITMENT_BYTES
    ];
    unsigned char recovered[sizeof(HYBRID_SELF_CHECK_PLAINTEXT) - 1u];
    size_t record_len = 0u;
    size_t recovered_len = 0u;
    latticra_seal_hybrid_envelope_result_t seal_result;
    latticra_seal_hybrid_envelope_result_t open_result;
    int exit_code = 1;

    memset(record, 0, sizeof(record));
    memset(recovered, 0, sizeof(recovered));

    puts("LATTICRA SEAL HYBRID ENVELOPE SELF-CHECK");
    puts("secret_material_output=redacted");
    puts("salt_output=redacted");
    puts("nonce_output=redacted");
    puts("ciphertext_output=redacted");
    puts("tag_output=redacted");
    puts("record_output=redacted");

    if (latticra_seal_hybrid_envelope_seal_record(
            HYBRID_SELF_CHECK_CLASSICAL_SECRET,
            sizeof(HYBRID_SELF_CHECK_CLASSICAL_SECRET),
            HYBRID_SELF_CHECK_PQC_SECRET,
            sizeof(HYBRID_SELF_CHECK_PQC_SECRET),
            HYBRID_SELF_CHECK_AAD,
            sizeof(HYBRID_SELF_CHECK_AAD) - 1u,
            HYBRID_SELF_CHECK_PLAINTEXT,
            sizeof(HYBRID_SELF_CHECK_PLAINTEXT) - 1u,
            record,
            sizeof(record),
            &record_len,
            &seal_result) != LATTICRA_STATUS_OK ||
        seal_result.error != LATTICRA_SEAL_HYBRID_ENVELOPE_OK) {
        (void)print_hybrid_result("seal", &seal_result);
        fprintf(stderr, "hybrid envelope encryption self-check failed\n");
        goto cleanup;
    }

    if (print_hybrid_result("seal", &seal_result) != 0) {
        goto cleanup;
    }

    if (latticra_seal_hybrid_envelope_open_record(
            HYBRID_SELF_CHECK_CLASSICAL_SECRET,
            sizeof(HYBRID_SELF_CHECK_CLASSICAL_SECRET),
            HYBRID_SELF_CHECK_PQC_SECRET,
            sizeof(HYBRID_SELF_CHECK_PQC_SECRET),
            HYBRID_SELF_CHECK_AAD,
            sizeof(HYBRID_SELF_CHECK_AAD) - 1u,
            record,
            record_len,
            recovered,
            sizeof(recovered),
            &recovered_len,
            &open_result) != LATTICRA_STATUS_OK ||
        open_result.error != LATTICRA_SEAL_HYBRID_ENVELOPE_OK ||
        recovered_len != sizeof(HYBRID_SELF_CHECK_PLAINTEXT) - 1u ||
        memcmp(recovered, HYBRID_SELF_CHECK_PLAINTEXT, recovered_len) != 0) {
        (void)print_hybrid_result("open", &open_result);
        fprintf(stderr, "hybrid envelope decryption self-check failed\n");
        goto cleanup;
    }

    if (print_hybrid_result("open", &open_result) != 0) {
        goto cleanup;
    }

    OPENSSL_cleanse(record, sizeof(record));
    OPENSSL_cleanse(recovered, sizeof(recovered));
    puts("cli_record_buffer_zeroized=1");
    puts("cli_recovered_plaintext_buffer_zeroized=1");
    puts("hybrid_envelope_self_check=pass");
    exit_code = stdout_is_healthy() ? 0 : stdout_failure("hybrid envelope self-check");

cleanup:
    OPENSSL_cleanse(record, sizeof(record));
    OPENSSL_cleanse(recovered, sizeof(recovered));
    return exit_code;
}

static int command_hybrid_provider_self_test(void) {
    latticra_seal_hybrid_provider_self_test_t self_test;

    if (latticra_seal_hybrid_provider_self_test_run(&self_test) != LATTICRA_STATUS_OK) {
        fprintf(stderr, "hybrid provider self-test invocation failed\n");
        return 1;
    }

    if (print_hybrid_provider_self_test_result(&self_test) != 0) {
        return 1;
    }

    if (!latticra_seal_hybrid_provider_self_test_is_authority_neutral(&self_test)) {
        fprintf(stderr, "hybrid provider self-test violated authority-neutral boundaries\n");
        return 1;
    }

    if (self_test.error != LATTICRA_SEAL_HYBRID_PROVIDER_SELF_TEST_OK) {
        fprintf(stderr, "hybrid provider self-test failed\n");
        return 1;
    }

    puts("hybrid_provider_self_test=pass");
    return stdout_is_healthy() ? 0 : stdout_failure("hybrid provider self-test");
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
    puts("  latticra-seal hybrid");
    puts("  latticra-seal hybrid-provider-self-test");
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
    puts("  hybrid     run the local hybrid envelope encrypt/decrypt self-check");
    puts("  hybrid-provider-self-test  run the provider-backed hybrid self-test");
    puts("  version    print the Seal CLI version");
    puts("  help       show this help message");
    return stdout_is_healthy() ? 0 : stdout_failure("help");
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

    if (strcmp(command, "hybrid") == 0) {
        return command_hybrid();
    }

    if (strcmp(command, "hybrid-provider-self-test") == 0) {
        return command_hybrid_provider_self_test();
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
