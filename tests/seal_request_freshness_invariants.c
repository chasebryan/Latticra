#include "latticra/seal_request_freshness.h"

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

static latticra_seal_parameter_schema_t fixture_schema(void) {
    latticra_seal_parameter_schema_t schema;
    memset(&schema, 0, sizeof(schema));
    (void)snprintf(schema.schema_profile, sizeof(schema.schema_profile), "%s", "latticra-seal-parameter-schema/0.1");
    (void)snprintf(schema.schema_id, sizeof(schema.schema_id), "%s", "unset");
    (void)snprintf(schema.schema_version, sizeof(schema.schema_version), "%s", "unset");
    (void)snprintf(schema.schema_language, sizeof(schema.schema_language), "%s", "unset");
    (void)snprintf(schema.schema_hash, sizeof(schema.schema_hash), "%s", "unset");
    schema.schema_present = 0u;
    schema.schema_parsing_supported = 0u;
    schema.schema_validation_supported = 0u;
    schema.schema_valid = 0u;
    schema.max_input_bytes_declared = 0u;
    schema.parameter_count_declared = 0u;
    schema.required_parameter_count_declared = 0u;
    schema.unknown_parameters_allowed = 0u;
    schema.parameter_forwarding_allowed = 0u;
    schema.input_size_within_limit = 0u;
    schema.parameter_names_reported = 0u;
    schema.runtime_authority_granted = 0u;
    schema.host_read_performed = 0u;
    schema.host_write_performed = 0u;
    schema.network_performed = 0u;
    (void)snprintf(schema.mode, sizeof(schema.mode), "%s", "report-only");
    (void)snprintf(schema.decision, sizeof(schema.decision), "%s", "report-only");
    (void)snprintf(schema.reason, sizeof(schema.reason), "%s", "parameter-schema-metadata-only");
    schema.error = LATTICRA_SEAL_PARAMETER_SCHEMA_OK;
    (void)snprintf(schema.status, sizeof(schema.status), "%s", "parameter-schema-metadata");
    return schema;
}

static int freshness_stays_report_only(void) {
    latticra_seal_parameter_schema_t schema = fixture_schema();
    latticra_seal_request_freshness_t freshness;
    char rendered[LATTICRA_SEAL_REQUEST_FRESHNESS_REPORT_MAX];

    EXPECT_TRUE(latticra_seal_request_freshness_from_schema(&schema, &freshness) == LATTICRA_STATUS_OK, "freshness status");
    EXPECT_TRUE(freshness.error == LATTICRA_SEAL_REQUEST_FRESHNESS_OK, "freshness ok");
    EXPECT_TRUE(strcmp(freshness.freshness_profile, "latticra-seal-request-freshness/0.1") == 0, "freshness profile");
    EXPECT_TRUE(strcmp(freshness.request_id, "unset") == 0, "request id");
    EXPECT_TRUE(strcmp(freshness.caller_id, "unset") == 0, "caller id");
    EXPECT_TRUE(strcmp(freshness.tool_id, "unset") == 0, "tool id");
    EXPECT_TRUE(strcmp(freshness.request_timestamp, "unset") == 0, "request timestamp");
    EXPECT_TRUE(strcmp(freshness.request_expiration, "unset") == 0, "request expiration");
    EXPECT_TRUE(strcmp(freshness.nonce, "unset") == 0, "nonce");
    EXPECT_TRUE(strcmp(freshness.context_hash, "unset") == 0, "context hash");
    EXPECT_TRUE(strcmp(freshness.parameter_hash, "unset") == 0, "parameter hash");
    EXPECT_TRUE(freshness.request_freshness_supported == 0u, "freshness supported");
    EXPECT_TRUE(freshness.request_freshness_validation_supported == 0u, "freshness validation supported");
    EXPECT_TRUE(freshness.replay_protection_supported == 0u, "replay protection supported");
    EXPECT_TRUE(freshness.request_id_present == 0u, "request id present");
    EXPECT_TRUE(freshness.caller_id_present == 0u, "caller id present");
    EXPECT_TRUE(freshness.tool_id_present == 0u, "tool id present");
    EXPECT_TRUE(freshness.request_timestamp_present == 0u, "timestamp present");
    EXPECT_TRUE(freshness.request_expiration_present == 0u, "expiration present");
    EXPECT_TRUE(freshness.nonce_present == 0u, "nonce present");
    EXPECT_TRUE(freshness.context_hash_present == 0u, "context hash present");
    EXPECT_TRUE(freshness.parameter_hash_present == 0u, "parameter hash present");
    EXPECT_TRUE(freshness.freshness_valid == 0u, "freshness valid");
    EXPECT_TRUE(freshness.replay_detected == 0u, "replay detected");
    EXPECT_TRUE(freshness.runtime_authority_granted == 0u, "runtime authority");
    EXPECT_TRUE(freshness.host_read_performed == 0u, "host read");
    EXPECT_TRUE(freshness.host_write_performed == 0u, "host write");
    EXPECT_TRUE(freshness.network_performed == 0u, "network");
    EXPECT_TRUE(strcmp(freshness.mode, "report-only") == 0, "mode");
    EXPECT_TRUE(strcmp(freshness.decision, "report-only") == 0, "decision");
    EXPECT_TRUE(strcmp(freshness.reason, "request-freshness-metadata-only") == 0, "reason");
    EXPECT_TRUE(strcmp(freshness.status, "request-freshness-metadata") == 0, "status");
    EXPECT_TRUE(latticra_seal_request_freshness_is_report_only(&freshness) == 1, "report-only helper");
    EXPECT_TRUE(latticra_seal_request_freshness_report(&freshness, rendered, sizeof(rendered)) == LATTICRA_STATUS_OK, "render status");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL REQUEST FRESHNESS") != 0, "render header");
    EXPECT_TRUE(strstr(rendered, "freshness_profile=latticra-seal-request-freshness/0.1") != 0, "render profile");
    EXPECT_TRUE(strstr(rendered, "request_id=unset") != 0, "render request id");
    EXPECT_TRUE(strstr(rendered, "nonce=unset") != 0, "render nonce");
    EXPECT_TRUE(strstr(rendered, "request_freshness_supported=0") != 0, "render supported");
    EXPECT_TRUE(strstr(rendered, "request_freshness_validation_supported=0") != 0, "render validation");
    EXPECT_TRUE(strstr(rendered, "replay_protection_supported=0") != 0, "render replay support");
    EXPECT_TRUE(strstr(rendered, "freshness_valid=0") != 0, "render freshness valid");
    EXPECT_TRUE(strstr(rendered, "replay_detected=0") != 0, "render replay detected");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "render authority");
    EXPECT_TRUE(strstr(rendered, "mode=report-only") != 0, "render mode");
    EXPECT_TRUE(strstr(rendered, "decision=report-only") != 0, "render decision");
    EXPECT_TRUE(strstr(rendered, "status=request-freshness-metadata") != 0, "render status label");
    return 0;
}

static int freshness_fails_closed(void) {
    latticra_seal_parameter_schema_t schema = fixture_schema();
    latticra_seal_request_freshness_t freshness;
    char tiny[1];
    char rendered[LATTICRA_SEAL_REQUEST_FRESHNESS_REPORT_MAX];

    EXPECT_TRUE(latticra_seal_request_freshness_from_schema(0, &freshness) == LATTICRA_STATUS_OK, "null schema status");
    EXPECT_TRUE(freshness.error == LATTICRA_SEAL_REQUEST_FRESHNESS_INVALID_INPUT, "null schema error");
    schema.runtime_authority_granted = 1u;
    EXPECT_TRUE(latticra_seal_request_freshness_from_schema(&schema, &freshness) == LATTICRA_STATUS_OK, "bad schema status");
    EXPECT_TRUE(freshness.error == LATTICRA_SEAL_REQUEST_FRESHNESS_INVALID_SCHEMA, "bad schema error");
    EXPECT_TRUE(strcmp(freshness.reason, "invalid-schema") == 0, "bad schema reason");
    EXPECT_TRUE(latticra_seal_request_freshness_from_schema(&schema, 0) == LATTICRA_STATUS_NULL_ARGUMENT, "null output");
    EXPECT_TRUE(latticra_seal_request_freshness_is_report_only(0) == 0, "null helper");
    EXPECT_TRUE(latticra_seal_request_freshness_report(&freshness, tiny, sizeof(tiny)) == LATTICRA_STATUS_BUFFER_TOO_SMALL, "small buffer");
    EXPECT_TRUE(tiny[0] == '\0', "small buffer cleared");
    EXPECT_TRUE(latticra_seal_request_freshness_report(0, tiny, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null freshness");
    EXPECT_TRUE(latticra_seal_request_freshness_report(&freshness, 0, sizeof(tiny)) == LATTICRA_STATUS_NULL_ARGUMENT, "null buffer");

    EXPECT_TRUE(latticra_seal_request_freshness_from_schema(&schema, &freshness) == LATTICRA_STATUS_OK, "freshness injection source");
    set_string(freshness.request_id, sizeof(freshness.request_id), "req-1\nruntime_authority_granted=1");
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_request_freshness_report(&freshness, rendered, sizeof(rendered)) == LATTICRA_STATUS_NULL_ARGUMENT, "newline request id rejected");
    EXPECT_TRUE(rendered[0] == '\0', "newline request id clears report");

    memset(&freshness, 'A', sizeof(freshness));
    memset(rendered, 'r', sizeof(rendered));
    EXPECT_TRUE(latticra_seal_request_freshness_report(&freshness, rendered, sizeof(rendered)) == LATTICRA_STATUS_NULL_ARGUMENT, "unterminated freshness rejected");
    EXPECT_TRUE(rendered[0] == '\0', "unterminated freshness clears report");
    return 0;
}

int main(void) {
    if (freshness_stays_report_only() != 0) {
        return 1;
    }
    if (freshness_fails_closed() != 0) {
        return 1;
    }
    printf("seal request freshness invariants: ok\n");
    return 0;
}
