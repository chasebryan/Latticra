#include "latticra/seal_signed_request.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static void set_string(char *destination, size_t destination_len, const char *source) {
    (void)snprintf(destination, destination_len, "%s", source != 0 ? source : "");
}

static latticra_seal_request_freshness_t fixture_freshness(void) {
    latticra_seal_request_freshness_t freshness;
    memset(&freshness, 0, sizeof(freshness));
    (void)snprintf(freshness.freshness_profile, sizeof(freshness.freshness_profile), "%s", "latticra-seal-request-freshness/0.1");
    (void)snprintf(freshness.request_id, sizeof(freshness.request_id), "%s", "unset");
    (void)snprintf(freshness.caller_id, sizeof(freshness.caller_id), "%s", "unset");
    (void)snprintf(freshness.tool_id, sizeof(freshness.tool_id), "%s", "unset");
    (void)snprintf(freshness.request_timestamp, sizeof(freshness.request_timestamp), "%s", "unset");
    (void)snprintf(freshness.request_expiration, sizeof(freshness.request_expiration), "%s", "unset");
    (void)snprintf(freshness.nonce, sizeof(freshness.nonce), "%s", "unset");
    (void)snprintf(freshness.context_hash, sizeof(freshness.context_hash), "%s", "unset");
    (void)snprintf(freshness.parameter_hash, sizeof(freshness.parameter_hash), "%s", "unset");
    freshness.request_freshness_supported = 0u;
    freshness.request_freshness_validation_supported = 0u;
    freshness.replay_protection_supported = 0u;
    freshness.request_id_present = 0u;
    freshness.caller_id_present = 0u;
    freshness.tool_id_present = 0u;
    freshness.request_timestamp_present = 0u;
    freshness.request_expiration_present = 0u;
    freshness.nonce_present = 0u;
    freshness.context_hash_present = 0u;
    freshness.parameter_hash_present = 0u;
    freshness.freshness_valid = 0u;
    freshness.replay_detected = 0u;
    freshness.runtime_authority_granted = 0u;
    freshness.host_read_performed = 0u;
    freshness.host_write_performed = 0u;
    freshness.network_performed = 0u;
    (void)snprintf(freshness.mode, sizeof(freshness.mode), "%s", "report-only");
    (void)snprintf(freshness.decision, sizeof(freshness.decision), "%s", "report-only");
    (void)snprintf(freshness.reason, sizeof(freshness.reason), "%s", "request-freshness-metadata-only");
    freshness.error = LATTICRA_SEAL_REQUEST_FRESHNESS_OK;
    (void)snprintf(freshness.status, sizeof(freshness.status), "%s", "request-freshness-metadata");
    return freshness;
}

static int signed_request_stays_report_only(void) {
    latticra_seal_request_freshness_t freshness = fixture_freshness();
    latticra_seal_signed_request_t signed_request;
    char rendered[LATTICRA_SEAL_SIGNED_REQUEST_REPORT_MAX];

    EXPECT_TRUE(latticra_seal_signed_request_from_freshness(&freshness, &signed_request) == LATTICRA_STATUS_OK, "signed request status");
    EXPECT_TRUE(signed_request.error == LATTICRA_SEAL_SIGNED_REQUEST_OK, "signed request ok");
    EXPECT_TRUE(strcmp(signed_request.signed_request_profile, "latticra-seal-signed-request/0.1") == 0, "signed request profile");
    EXPECT_TRUE(strcmp(signed_request.signed_request_id, "unset") == 0, "signed request id");
    EXPECT_TRUE(strcmp(signed_request.signature_algorithm, "unset") == 0, "signature algorithm");
    EXPECT_TRUE(strcmp(signed_request.signing_key_id, "unset") == 0, "signing key id");
    EXPECT_TRUE(strcmp(signed_request.signature_hash, "unset") == 0, "signature hash");
    EXPECT_TRUE(signed_request.signed_request_supported == 0u, "signed request supported");
    EXPECT_TRUE(signed_request.signature_generation_supported == 0u, "signature generation supported");
    EXPECT_TRUE(signed_request.signature_verification_supported == 0u, "signature verification supported");
    EXPECT_TRUE(signed_request.signature_present == 0u, "signature present");
    EXPECT_TRUE(signed_request.signature_valid == 0u, "signature valid");
    EXPECT_TRUE(signed_request.signature_algorithm_declared == 0u, "signature algorithm declared");
    EXPECT_TRUE(signed_request.signing_key_id_present == 0u, "signing key id present");
    EXPECT_TRUE(signed_request.signature_hash_present == 0u, "signature hash present");
    EXPECT_TRUE(signed_request.signed_request_id_present == 0u, "signed request id present");
    EXPECT_TRUE(signed_request.identity_binding_declared == 0u, "identity binding");
    EXPECT_TRUE(signed_request.context_binding_declared == 0u, "context binding");
    EXPECT_TRUE(signed_request.parameter_binding_declared == 0u, "parameter binding");
    EXPECT_TRUE(signed_request.freshness_binding_declared == 0u, "freshness binding");
    EXPECT_TRUE(signed_request.policy_binding_declared == 0u, "policy binding");
    EXPECT_TRUE(signed_request.trust_store_supported == 0u, "trust store supported");
    EXPECT_TRUE(signed_request.revocation_lookup_supported == 0u, "revocation lookup supported");
    EXPECT_TRUE(signed_request.runtime_authority_granted == 0u, "runtime authority");
    EXPECT_TRUE(signed_request.host_read_performed == 0u, "host read");
    EXPECT_TRUE(signed_request.host_write_performed == 0u, "host write");
    EXPECT_TRUE(signed_request.network_performed == 0u, "network");
    EXPECT_TRUE(strcmp(signed_request.mode, "report-only") == 0, "mode");
    EXPECT_TRUE(strcmp(signed_request.decision, "report-only") == 0, "decision");
    EXPECT_TRUE(strcmp(signed_request.reason, "signed-request-metadata-only") == 0, "reason");
    EXPECT_TRUE(strcmp(signed_request.status, "signed-request-metadata") == 0, "status");
    EXPECT_TRUE(latticra_seal_signed_request_is_report_only(&signed_request) == 1, "report-only helper");
    EXPECT_TRUE(latticra_seal_signed_request_report(&signed_request, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "render status");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL SIGNED REQUEST") != 0, "render header");
    EXPECT_TRUE(strstr(rendered, "signed_request_profile=latticra-seal-signed-request/0.1") != 0, "render profile");
    EXPECT_TRUE(strstr(rendered, "signed_request_id=unset") != 0, "render signed id");
    EXPECT_TRUE(strstr(rendered, "signature_algorithm=unset") != 0, "render algorithm");
    EXPECT_TRUE(strstr(rendered, "signature_present=0") != 0, "render signature present");
    EXPECT_TRUE(strstr(rendered, "signature_valid=0") != 0, "render signature valid");
    EXPECT_TRUE(strstr(rendered, "signature_verification_supported=0") != 0, "render verification");
    EXPECT_TRUE(strstr(rendered, "identity_binding_declared=0") != 0, "render identity binding");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "render authority");
    EXPECT_TRUE(strstr(rendered, "mode=report-only") != 0, "render mode");
    EXPECT_TRUE(strstr(rendered, "decision=report-only") != 0, "render decision");
    EXPECT_TRUE(strstr(rendered, "status=signed-request-metadata") != 0, "render status label");
    return 0;
}

static int signed_request_fails_closed(void) {
    latticra_seal_request_freshness_t freshness = fixture_freshness();
    latticra_seal_signed_request_t signed_request;
    char tiny[1];
    char rendered[LATTICRA_SEAL_SIGNED_REQUEST_REPORT_MAX];

    EXPECT_TRUE(latticra_seal_signed_request_from_freshness(0, &signed_request) == LATTICRA_STATUS_OK, "null freshness status");
    EXPECT_TRUE(signed_request.error == LATTICRA_SEAL_SIGNED_REQUEST_INVALID_INPUT, "null freshness error");
    freshness.runtime_authority_granted = 1u;
    EXPECT_TRUE(latticra_seal_signed_request_from_freshness(&freshness, &signed_request) == LATTICRA_STATUS_OK, "bad freshness status");
    EXPECT_TRUE(signed_request.error == LATTICRA_SEAL_SIGNED_REQUEST_INVALID_FRESHNESS, "bad freshness error");
    EXPECT_TRUE(strcmp(signed_request.reason, "invalid-freshness") == 0, "bad freshness reason");
    EXPECT_TRUE(latticra_seal_signed_request_from_freshness(&freshness, 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null output");
    EXPECT_TRUE(latticra_seal_signed_request_is_report_only(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_signed_request_report(&signed_request, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small buffer");
    EXPECT_TRUE(tiny[0] == '\0', "small buffer cleared");
    EXPECT_TRUE(latticra_seal_signed_request_report(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null signed request");
    EXPECT_TRUE(latticra_seal_signed_request_report(&signed_request, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer");

    freshness = fixture_freshness();
    EXPECT_TRUE(latticra_seal_signed_request_from_freshness(&freshness, &signed_request) == LATTICRA_STATUS_OK, "signed injection source");
    set_string(signed_request.signed_request_id, sizeof(signed_request.signed_request_id), "req-1\nsignature_valid=1");
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_signed_request_report(&signed_request, rendered, sizeof(rendered)) == LATTICRA_STATUS_NULL_ARGUMENT, "newline signed request id rejected");
    EXPECT_TRUE(rendered[0] == '\0', "newline signed request id clears report");

    memset(&signed_request, 'A', sizeof(signed_request));
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_signed_request_report(&signed_request, rendered, sizeof(rendered)) == LATTICRA_STATUS_NULL_ARGUMENT, "unterminated signed request rejected");
    EXPECT_TRUE(rendered[0] == '\0', "unterminated signed request clears report");
    return 0;
}

int main(void) {
    if (signed_request_stays_report_only() != 0) {
        return 1;
    }
    if (signed_request_fails_closed() != 0) {
        return 1;
    }
    printf("seal signed request invariants: ok\n");
    return 0;
}
