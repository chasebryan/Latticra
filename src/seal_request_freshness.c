#include "latticra/seal_request_freshness.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

static int report_string_valid(const char *value, size_t max_len) {
    size_t i;

    if (value == NULL) {
        return 0;
    }
    for (i = 0u; i < max_len; ++i) {
        if (value[i] == '\0') {
            return i > 0u;
        }
        if (value[i] == '\n' || value[i] == '\r') {
            return 0;
        }
    }
    return 0;
}

static int freshness_report_strings_valid(
    const latticra_seal_request_freshness_t *freshness) {
    return report_string_valid(freshness->freshness_profile, LATTICRA_SEAL_REQUEST_FRESHNESS_PROFILE_MAX) &&
           report_string_valid(freshness->request_id, LATTICRA_SEAL_REQUEST_FRESHNESS_ID_MAX) &&
           report_string_valid(freshness->caller_id, LATTICRA_SEAL_REQUEST_FRESHNESS_ID_MAX) &&
           report_string_valid(freshness->tool_id, LATTICRA_SEAL_REQUEST_FRESHNESS_ID_MAX) &&
           report_string_valid(freshness->request_timestamp, LATTICRA_SEAL_REQUEST_FRESHNESS_TIME_MAX) &&
           report_string_valid(freshness->request_expiration, LATTICRA_SEAL_REQUEST_FRESHNESS_TIME_MAX) &&
           report_string_valid(freshness->nonce, LATTICRA_SEAL_REQUEST_FRESHNESS_ID_MAX) &&
           report_string_valid(freshness->context_hash, LATTICRA_SEAL_REQUEST_FRESHNESS_HASH_MAX) &&
           report_string_valid(freshness->parameter_hash, LATTICRA_SEAL_REQUEST_FRESHNESS_HASH_MAX) &&
           report_string_valid(freshness->mode, LATTICRA_SEAL_REQUEST_FRESHNESS_STATE_MAX) &&
           report_string_valid(freshness->decision, LATTICRA_SEAL_REQUEST_FRESHNESS_STATE_MAX) &&
           report_string_valid(freshness->reason, LATTICRA_SEAL_REQUEST_FRESHNESS_STATE_MAX) &&
           report_string_valid(freshness->status, LATTICRA_SEAL_REQUEST_FRESHNESS_STATE_MAX);
}

const char *latticra_seal_request_freshness_error_label(
    latticra_seal_request_freshness_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_REQUEST_FRESHNESS_OK:
        return "ok";
    case LATTICRA_SEAL_REQUEST_FRESHNESS_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_REQUEST_FRESHNESS_INVALID_SCHEMA:
        return "invalid-schema";
    default:
        return "unknown";
    }
}

static void freshness_init(latticra_seal_request_freshness_t *freshness) {
    memset(freshness, 0, sizeof(*freshness));
    copy_literal(freshness->freshness_profile, sizeof(freshness->freshness_profile), "latticra-seal-request-freshness/0.1");
    copy_literal(freshness->request_id, sizeof(freshness->request_id), "unset");
    copy_literal(freshness->caller_id, sizeof(freshness->caller_id), "unset");
    copy_literal(freshness->tool_id, sizeof(freshness->tool_id), "unset");
    copy_literal(freshness->request_timestamp, sizeof(freshness->request_timestamp), "unset");
    copy_literal(freshness->request_expiration, sizeof(freshness->request_expiration), "unset");
    copy_literal(freshness->nonce, sizeof(freshness->nonce), "unset");
    copy_literal(freshness->context_hash, sizeof(freshness->context_hash), "unset");
    copy_literal(freshness->parameter_hash, sizeof(freshness->parameter_hash), "unset");
    freshness->request_freshness_supported = 0u;
    freshness->request_freshness_validation_supported = 0u;
    freshness->replay_protection_supported = 0u;
    freshness->request_id_present = 0u;
    freshness->caller_id_present = 0u;
    freshness->tool_id_present = 0u;
    freshness->request_timestamp_present = 0u;
    freshness->request_expiration_present = 0u;
    freshness->nonce_present = 0u;
    freshness->context_hash_present = 0u;
    freshness->parameter_hash_present = 0u;
    freshness->freshness_valid = 0u;
    freshness->replay_detected = 0u;
    freshness->runtime_authority_granted = 0u;
    freshness->host_read_performed = 0u;
    freshness->host_write_performed = 0u;
    freshness->network_performed = 0u;
    copy_literal(freshness->mode, sizeof(freshness->mode), "report-only");
    copy_literal(freshness->decision, sizeof(freshness->decision), "report-only");
    copy_literal(freshness->reason, sizeof(freshness->reason), "request-freshness-metadata-only");
    freshness->error = LATTICRA_SEAL_REQUEST_FRESHNESS_INVALID_INPUT;
    copy_literal(freshness->status, sizeof(freshness->status), "invalid-input");
}

latticra_status_t latticra_seal_request_freshness_from_schema(
    const latticra_seal_parameter_schema_t *schema,
    latticra_seal_request_freshness_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    freshness_init(out);

    if (schema == NULL) {
        return LATTICRA_STATUS_OK;
    }

    if (schema->error != LATTICRA_SEAL_PARAMETER_SCHEMA_OK ||
        latticra_seal_parameter_schema_is_report_only(schema) != 1) {
        out->error = LATTICRA_SEAL_REQUEST_FRESHNESS_INVALID_SCHEMA;
        copy_literal(out->reason, sizeof(out->reason), "invalid-schema");
        copy_literal(out->status, sizeof(out->status), "invalid-schema");
        return LATTICRA_STATUS_OK;
    }

    out->runtime_authority_granted = schema->runtime_authority_granted;
    out->host_read_performed = schema->host_read_performed;
    out->host_write_performed = schema->host_write_performed;
    out->network_performed = schema->network_performed;
    out->error = LATTICRA_SEAL_REQUEST_FRESHNESS_OK;
    copy_literal(out->status, sizeof(out->status), "request-freshness-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_request_freshness_is_report_only(
    const latticra_seal_request_freshness_t *freshness) {
    if (freshness == NULL) {
        return 0;
    }

    return freshness->request_freshness_supported == 0u &&
           freshness->request_freshness_validation_supported == 0u &&
           freshness->replay_protection_supported == 0u &&
           freshness->request_id_present == 0u &&
           freshness->caller_id_present == 0u &&
           freshness->tool_id_present == 0u &&
           freshness->request_timestamp_present == 0u &&
           freshness->request_expiration_present == 0u &&
           freshness->nonce_present == 0u &&
           freshness->context_hash_present == 0u &&
           freshness->parameter_hash_present == 0u &&
           freshness->freshness_valid == 0u &&
           freshness->replay_detected == 0u &&
           freshness->runtime_authority_granted == 0u &&
           freshness->host_read_performed == 0u &&
           freshness->host_write_performed == 0u &&
           freshness->network_performed == 0u;
}

latticra_status_t latticra_seal_request_freshness_report(
    const latticra_seal_request_freshness_t *freshness,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (freshness == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (buffer_len == 0u) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    if (!freshness_report_strings_valid(freshness)) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL REQUEST FRESHNESS\n"
        "freshness_profile=%s\n"
        "request_id=%s\n"
        "caller_id=%s\n"
        "tool_id=%s\n"
        "request_timestamp=%s\n"
        "request_expiration=%s\n"
        "nonce=%s\n"
        "context_hash=%s\n"
        "parameter_hash=%s\n"
        "request_freshness_supported=%u\n"
        "request_freshness_validation_supported=%u\n"
        "replay_protection_supported=%u\n"
        "request_id_present=%u\n"
        "caller_id_present=%u\n"
        "tool_id_present=%u\n"
        "request_timestamp_present=%u\n"
        "request_expiration_present=%u\n"
        "nonce_present=%u\n"
        "context_hash_present=%u\n"
        "parameter_hash_present=%u\n"
        "freshness_valid=%u\n"
        "replay_detected=%u\n"
        "runtime_authority_granted=%u\n"
        "host_read_performed=%u\n"
        "host_write_performed=%u\n"
        "network_performed=%u\n"
        "mode=%s\n"
        "decision=%s\n"
        "reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        freshness->freshness_profile,
        freshness->request_id,
        freshness->caller_id,
        freshness->tool_id,
        freshness->request_timestamp,
        freshness->request_expiration,
        freshness->nonce,
        freshness->context_hash,
        freshness->parameter_hash,
        freshness->request_freshness_supported,
        freshness->request_freshness_validation_supported,
        freshness->replay_protection_supported,
        freshness->request_id_present,
        freshness->caller_id_present,
        freshness->tool_id_present,
        freshness->request_timestamp_present,
        freshness->request_expiration_present,
        freshness->nonce_present,
        freshness->context_hash_present,
        freshness->parameter_hash_present,
        freshness->freshness_valid,
        freshness->replay_detected,
        freshness->runtime_authority_granted,
        freshness->host_read_performed,
        freshness->host_write_performed,
        freshness->network_performed,
        freshness->mode,
        freshness->decision,
        freshness->reason,
        latticra_seal_request_freshness_error_label(freshness->error),
        freshness->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
