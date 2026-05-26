#if defined(__APPLE__) && !defined(_DARWIN_C_SOURCE)
#define _DARWIN_C_SOURCE
#endif
#define _POSIX_C_SOURCE 200809L

#include "latticra/seal_measurement.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static int write_fixture(const char *path) {
    FILE *file = fopen(path, "wb");
    if (file == 0) {
        return 1;
    }
    if (fwrite("latticra", 1u, 8u, file) != 8u) {
        (void)fclose(file);
        return 1;
    }
    return fclose(file) == 0 ? 0 : 1;
}

static const char *private_tmp_root(void) {
    const char *root = getenv("TMPDIR");
    return (root != 0 && root[0] != '\0') ? root : "/tmp";
}

static int make_private_tmpdir(char *buffer, size_t buffer_len, const char *label) {
    const char *root = private_tmp_root();
    const char *separator = root[strlen(root) - 1u] == '/' ? "" : "/";
    int written = snprintf(buffer, buffer_len, "%s%slatticra-%s.XXXXXX", root, separator, label);
    if (written <= 0 || (size_t)written >= buffer_len) {
        return 1;
    }
    return mkdtemp(buffer) == 0 ? 1 : 0;
}

static int join_path(char *buffer, size_t buffer_len, const char *dir, const char *name) {
    int written = snprintf(buffer, buffer_len, "%s/%s", dir, name);
    return written > 0 && (size_t)written < buffer_len ? 0 : 1;
}

static int measurement_reads_regular_file(void) {
    latticra_seal_measurement_t measurement;
    char rendered[LATTICRA_SEAL_MEASUREMENT_REPORT_MAX];
    char tmpdir[1024];
    char path[1200];

    EXPECT_TRUE(make_private_tmpdir(tmpdir, sizeof(tmpdir), "seal-measurement") == 0, "tmpdir");
    EXPECT_TRUE(join_path(path, sizeof(path), tmpdir, "fixture.txt") == 0, "fixture path");
    EXPECT_TRUE(write_fixture(path) == 0, "fixture write");
    EXPECT_TRUE(latticra_seal_measure_file(path, &measurement) == LATTICRA_STATUS_OK, "measure status");
    EXPECT_TRUE(measurement.error == LATTICRA_SEAL_MEASUREMENT_OK, "measure ok");
    EXPECT_TRUE(strcmp(measurement.algorithm, "SHA-256") == 0, "algorithm");
    EXPECT_TRUE(measurement.artifact_size_bytes == 8u, "size");
    EXPECT_TRUE(strcmp(measurement.digest_hex, "03284a1ae75d2b26190b094726a77884d9b21569e8f85a80b92166b1682d2ebd") == 0, "digest");
    EXPECT_TRUE(measurement.read_performed == 1u, "read flag");
    EXPECT_TRUE(measurement.write_performed == 0u, "write flag");
    EXPECT_TRUE(measurement.network_performed == 0u, "network flag");
    EXPECT_TRUE(measurement.runtime_granted == 0u, "runtime flag");
    EXPECT_TRUE(latticra_seal_measurement_is_read_only(&measurement) == 1, "read-only helper");
    EXPECT_TRUE(latticra_seal_measurement_report(&measurement, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "render status");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL MEASUREMENT") != 0, "render header");
    EXPECT_TRUE(strstr(rendered, "algorithm=SHA-256") != 0, "render algorithm");
    EXPECT_TRUE(strstr(rendered, "status=measured") != 0, "render status label");
    (void)remove(path);
    (void)rmdir(tmpdir);
    return 0;
}

static int measurement_fails_closed_for_invalid_input(void) {
    latticra_seal_measurement_t measurement;
    char tiny[1];
    char tmpdir[1024];
    char missing_path[1200];

    EXPECT_TRUE(make_private_tmpdir(tmpdir, sizeof(tmpdir), "seal-measurement-invalid") == 0, "invalid tmpdir");
    EXPECT_TRUE(join_path(missing_path, sizeof(missing_path), tmpdir, "missing-file") == 0, "missing path");
    EXPECT_TRUE(latticra_seal_measure_file(0, &measurement) == LATTICRA_STATUS_OK, "null path status");
    EXPECT_TRUE(measurement.error == LATTICRA_SEAL_MEASUREMENT_INVALID_INPUT, "null path error");
    EXPECT_TRUE(measurement.read_performed == 0u, "null path no read");
    EXPECT_TRUE(latticra_seal_measure_file("", &measurement) == LATTICRA_STATUS_OK, "empty path status");
    EXPECT_TRUE(measurement.error == LATTICRA_SEAL_MEASUREMENT_INVALID_INPUT, "empty path error");
    EXPECT_TRUE(latticra_seal_measure_file(tmpdir, &measurement) == LATTICRA_STATUS_OK, "directory status");
    EXPECT_TRUE(measurement.error == LATTICRA_SEAL_MEASUREMENT_NOT_REGULAR, "directory error");
    EXPECT_TRUE(latticra_seal_measure_file(missing_path, &measurement) == LATTICRA_STATUS_OK, "missing status");
    EXPECT_TRUE(measurement.error == LATTICRA_SEAL_MEASUREMENT_OPEN_FAILED, "missing error");
    EXPECT_TRUE(latticra_seal_measurement_is_read_only(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_measurement_report(&measurement, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small buffer");
    EXPECT_TRUE(tiny[0] == '\0', "small buffer cleared");
    EXPECT_TRUE(latticra_seal_measurement_report(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null measurement");
    EXPECT_TRUE(latticra_seal_measurement_report(&measurement, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer");
    (void)rmdir(tmpdir);
    return 0;
}

int main(void) {
    if (measurement_reads_regular_file() != 0) {
        return 1;
    }
    if (measurement_fails_closed_for_invalid_input() != 0) {
        return 1;
    }
    printf("seal measurement invariants: ok\n");
    return 0;
}
