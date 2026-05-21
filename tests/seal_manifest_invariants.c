#include "latticra/seal_manifest.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static latticra_seal_measurement_t fixture_measurement(void) {
    latticra_seal_measurement_t measurement;
    memset(&measurement, 0, sizeof(measurement));
    (void)snprintf(measurement.measurement_profile, sizeof(measurement.measurement_profile), "%s", "latticra-seal-measurement/0.1");
    (void)snprintf(measurement.algorithm, sizeof(measurement.algorithm), "%s", "SHA-256");
    (void)snprintf(measurement.artifact_label, sizeof(measurement.artifact_label), "%s", "fixture://seal/artifact.bin");
    measurement.artifact_size_bytes = 8u;
    (void)snprintf(measurement.digest_hex, sizeof(measurement.digest_hex), "%s", "03284a1ae75d2b26190b094726a77884d9b21569e8f85a80b92166b1682d2ebd");
    measurement.read_performed = 1u;
    measurement.error = LATTICRA_SEAL_MEASUREMENT_OK;
    (void)snprintf(measurement.status, sizeof(measurement.status), "%s", "measured");
    return measurement;
}

static int manifest_copies_measurement_metadata(void) {
    latticra_seal_measurement_t measurement = fixture_measurement();
    latticra_seal_manifest_t manifest;
    char rendered[LATTICRA_SEAL_MANIFEST_REPORT_MAX];

    EXPECT_TRUE(latticra_seal_manifest_from_measurement(&measurement, "contract://seal/test", &manifest) == LATTICRA_STATUS_OK, "manifest status");
    EXPECT_TRUE(manifest.error == LATTICRA_SEAL_MANIFEST_OK, "manifest ok");
    EXPECT_TRUE(strcmp(manifest.manifest_kind, "unsigned-evidence-manifest") == 0, "kind");
    EXPECT_TRUE(strcmp(manifest.artifact_label, "fixture://seal/artifact.bin") == 0, "artifact label");
    EXPECT_TRUE(manifest.artifact_size_bytes == 8u, "artifact size");
    EXPECT_TRUE(strcmp(manifest.artifact_digest_algorithm, "SHA-256") == 0, "digest algorithm");
    EXPECT_TRUE(strcmp(manifest.artifact_digest_hex, measurement.digest_hex) == 0, "digest hex");
    EXPECT_TRUE(strcmp(manifest.measurement_profile, "latticra-seal-measurement/0.1") == 0, "measurement profile");
    EXPECT_TRUE(strcmp(manifest.contract_id, "contract://seal/test") == 0, "contract id");
    EXPECT_TRUE(latticra_seal_manifest_is_unsigned_metadata(&manifest) == 1, "unsigned helper");
    EXPECT_TRUE(latticra_seal_manifest_report(&manifest, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "render status");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL MANIFEST") != 0, "render header");
    EXPECT_TRUE(strstr(rendered, "signature_supported=0") != 0, "render signature flag");
    EXPECT_TRUE(strstr(rendered, "verification_supported=0") != 0, "render verify flag");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "render runtime flag");
    EXPECT_TRUE(strstr(rendered, "status=unsigned-manifest") != 0, "render status label");
    return 0;
}

static int manifest_fails_closed(void) {
    latticra_seal_measurement_t measurement = fixture_measurement();
    latticra_seal_manifest_t manifest;
    char tiny[1];

    EXPECT_TRUE(latticra_seal_manifest_from_measurement(0, "contract://seal/test", &manifest) == LATTICRA_STATUS_OK, "null measurement status");
    EXPECT_TRUE(manifest.error == LATTICRA_SEAL_MANIFEST_INVALID_INPUT, "null measurement error");
    measurement.error = LATTICRA_SEAL_MEASUREMENT_OPEN_FAILED;
    EXPECT_TRUE(latticra_seal_manifest_from_measurement(&measurement, "contract://seal/test", &manifest) == LATTICRA_STATUS_OK, "bad measurement status");
    EXPECT_TRUE(manifest.error == LATTICRA_SEAL_MANIFEST_INVALID_MEASUREMENT, "bad measurement error");
    measurement = fixture_measurement();
    measurement.digest_hex[0] = '\0';
    EXPECT_TRUE(latticra_seal_manifest_from_measurement(&measurement, "contract://seal/test", &manifest) == LATTICRA_STATUS_OK, "missing digest status");
    EXPECT_TRUE(manifest.error == LATTICRA_SEAL_MANIFEST_MISSING_DIGEST, "missing digest error");
    EXPECT_TRUE(latticra_seal_manifest_from_measurement(&measurement, "contract://seal/test", 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null output");
    EXPECT_TRUE(latticra_seal_manifest_is_unsigned_metadata(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_manifest_report(&manifest, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small buffer");
    EXPECT_TRUE(tiny[0] == '\0', "small buffer cleared");
    EXPECT_TRUE(latticra_seal_manifest_report(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null manifest");
    EXPECT_TRUE(latticra_seal_manifest_report(&manifest, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer");
    return 0;
}

int main(void) {
    if (manifest_copies_measurement_metadata() != 0) {
        return 1;
    }
    if (manifest_fails_closed() != 0) {
        return 1;
    }
    printf("seal manifest invariants: ok\n");
    return 0;
}
