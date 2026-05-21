#include "latticra/seal_measurement.h"

#include <stdio.h>
#include <string.h>

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

static int measurement_reads_regular_file(void) {
    const char *path = "/tmp/latticra-seal-measurement-fixture.txt";
    latticra_seal_measurement_t measurement;
    char rendered[LATTICRA_SEAL_MEASUREMENT_REPORT_MAX];

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
    return 0;
}

static int measurement_fails_closed_for_invalid_input(void) {
    latticra_seal_measurement_t measurement;
    char tiny[1];

    EXPECT_TRUE(latticra_seal_measure_file(0, &measurement) == LATTICRA_STATUS_OK, "null path status");
    EXPECT_TRUE(measurement.error == LATTICRA_SEAL_MEASUREMENT_INVALID_INPUT, "null path error");
    EXPECT_TRUE(measurement.read_performed == 0u, "null path no read");
    EXPECT_TRUE(latticra_seal_measure_file("", &measurement) == LATTICRA_STATUS_OK, "empty path status");
    EXPECT_TRUE(measurement.error == LATTICRA_SEAL_MEASUREMENT_INVALID_INPUT, "empty path error");
    EXPECT_TRUE(latticra_seal_measure_file("/tmp", &measurement) == LATTICRA_STATUS_OK, "directory status");
    EXPECT_TRUE(measurement.error == LATTICRA_SEAL_MEASUREMENT_NOT_REGULAR, "directory error");
    EXPECT_TRUE(latticra_seal_measure_file("/tmp/latticra-seal-missing-file", &measurement) == LATTICRA_STATUS_OK, "missing status");
    EXPECT_TRUE(measurement.error == LATTICRA_SEAL_MEASUREMENT_OPEN_FAILED, "missing error");
    EXPECT_TRUE(latticra_seal_measurement_is_read_only(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_measurement_report(&measurement, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small buffer");
    EXPECT_TRUE(tiny[0] == '\0', "small buffer cleared");
    EXPECT_TRUE(latticra_seal_measurement_report(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null measurement");
    EXPECT_TRUE(latticra_seal_measurement_report(&measurement, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer");
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
