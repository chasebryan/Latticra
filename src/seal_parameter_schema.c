#include "latticra/seal_parameter_schema.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

const char *latticra_seal_parameter_schema_error_label(
    latticra_seal_parameter_schema_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_PARAMETER_SCHEMA_OK:
        return "ok";
    case LATTICRA_SEAL_PARAMETER_SCHEMA_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_PARAMETER_SCHEMA_INVALID_AGENTIC:
        return "invalid-agentic";
    default:
        return "unknown";
    }
}

static void schema_init(latticra_seal_parameter_schema_t *schema) {
    memset(schema, 0, sizeof(*schema));
    copy_literal(schema->schema_profile, sizeof(schema->schema_profile), "latticra-seal-parameter-schema/0.1");
    copy_literal(schema->schema_id, sizeof(schema->schema_id), "unset");
    copy_literal(schema->schema_version, sizeof(schema->schema_version), "unset");
    copy_literal(schema->schema_language, sizeof(schema->schema_language), "unset");
    copy_literal(schema->schema_hash, sizeof(schema->schema_hash), "unset");
    schema->schema_present = 0u;
    schema->schema_parsing_supported = 0u;
    schema->schema_validation_supported = 0u;
    schema->schema_valid = 0u;
    schema->max_input_bytes_declared = 0u;
    schema->parameter_count_declared = 0u;
    schema->required_parameter_count_declared = 0u;
    schema->unknown_parameters_allowed = 0u;
    schema->parameter_forwarding_allowed = 0u;
    schema->input_size_within_limit = 0u;
    schema->parameter_names_reported = 0u;
    schema->runtime_authority_granted = 0u;
    schema->host_read_performed = 0u;
    schema->host_write_performed = 0u;
    schema->network_performed = 0u;
    copy_literal(schema->mode, sizeof(schema->mode), "report-only");
    copy_literal(schema->decision, sizeof(schema->decision), "report-only");
    copy_literal(schema->reason, sizeof(schema->reason), "parameter-schema-metadata-only");
    schema->error = LATTICRA_SEAL_PARAMETER_SCHEMA_INVALID_INPUT;
    copy_literal(schema->status, sizeof(schema->status), "invalid-input");
}

latticra_status_t latticra_seal_parameter_schema_from_agentic(
    const latticra_seal_agentic_automation_security_t *agentic,
    latticra_seal_parameter_schema_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    schema_init(out);

    if (agentic == NULL) {
        return LATTICRA_STATUS_OK;
    }

    if (agentic->error != LATTICRA_SEAL_AGENTIC_OK ||
        latticra_seal_agentic_automation_security_is_report_only(agentic) != 1) {
        out->error = LATTICRA_SEAL_PARAMETER_SCHEMA_INVALID_AGENTIC;
        copy_literal(out->reason, sizeof(out->reason), "invalid-agentic");
        copy_literal(out->status, sizeof(out->status), "invalid-agentic");
        return LATTICRA_STATUS_OK;
    }

    out->schema_present = agentic->parameter_schema_present;
    out->schema_valid = agentic->parameter_schema_valid;
    out->runtime_authority_granted = agentic->runtime_authority_granted;
    out->host_read_performed = agentic->host_read_performed;
    out->host_write_performed = agentic->host_write_performed;
    out->network_performed = agentic->network_performed;
    out->error = LATTICRA_SEAL_PARAMETER_SCHEMA_OK;
    copy_literal(out->status, sizeof(out->status), "parameter-schema-metadata");
    return LATTICRA_STATUS_OK;
}

int latticra_seal_parameter_schema_is_report_only(
    const latticra_seal_parameter_schema_t *schema) {
    if (schema == NULL) {
        return 0;
    }

    return schema->schema_present == 0u &&
           schema->schema_parsing_supported == 0u &&
           schema->schema_validation_supported == 0u &&
           schema->schema_valid == 0u &&
           schema->max_input_bytes_declared == 0u &&
           schema->parameter_count_declared == 0u &&
           schema->required_parameter_count_declared == 0u &&
           schema->unknown_parameters_allowed == 0u &&
           schema->parameter_forwarding_allowed == 0u &&
           schema->input_size_within_limit == 0u &&
           schema->parameter_names_reported == 0u &&
           schema->runtime_authority_granted == 0u &&
           schema->host_read_performed == 0u &&
           schema->host_write_performed == 0u &&
           schema->network_performed == 0u;
}

latticra_status_t latticra_seal_parameter_schema_report(
    const latticra_seal_parameter_schema_t *schema,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (schema == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL PARAMETER SCHEMA\n"
        "schema_profile=%s\n"
        "schema_id=%s\n"
        "schema_version=%s\n"
        "schema_language=%s\n"
        "schema_hash=%s\n"
        "schema_present=%u\n"
        "schema_parsing_supported=%u\n"
        "schema_validation_supported=%u\n"
        "schema_valid=%u\n"
        "max_input_bytes_declared=%u\n"
        "parameter_count_declared=%u\n"
        "required_parameter_count_declared=%u\n"
        "unknown_parameters_allowed=%u\n"
        "parameter_forwarding_allowed=%u\n"
        "input_size_within_limit=%u\n"
        "parameter_names_reported=%u\n"
        "runtime_authority_granted=%u\n"
        "host_read_performed=%u\n"
        "host_write_performed=%u\n"
        "network_performed=%u\n"
        "mode=%s\n"
        "decision=%s\n"
        "reason=%s\n"
        "error=%s\n"
        "status=%s\n",
        schema->schema_profile,
        schema->schema_id,
        schema->schema_version,
        schema->schema_language,
        schema->schema_hash,
        schema->schema_present,
        schema->schema_parsing_supported,
        schema->schema_validation_supported,
        schema->schema_valid,
        schema->max_input_bytes_declared,
        schema->parameter_count_declared,
        schema->required_parameter_count_declared,
        schema->unknown_parameters_allowed,
        schema->parameter_forwarding_allowed,
        schema->input_size_within_limit,
        schema->parameter_names_reported,
        schema->runtime_authority_granted,
        schema->host_read_performed,
        schema->host_write_performed,
        schema->network_performed,
        schema->mode,
        schema->decision,
        schema->reason,
        latticra_seal_parameter_schema_error_label(schema->error),
        schema->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
