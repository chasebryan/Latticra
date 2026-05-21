#include "latticra/seal_request_freshness.h"

#include <stdio.h>
#include <string.h>

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

int main(void) {
    latticra_seal_parameter_schema_t schema = fixture_schema();
    latticra_seal_request_freshness_t freshness;
    char rendered[LATTICRA_SEAL_REQUEST_FRESHNESS_REPORT_MAX];

    if (latticra_seal_request_freshness_from_schema(&schema, &freshness) != LATTICRA_STATUS_OK) {
        fprintf(stderr, "failed to build Seal request freshness metadata\n");
        return 1;
    }

    if (freshness.error != LATTICRA_SEAL_REQUEST_FRESHNESS_OK) {
        fprintf(stderr, "invalid Seal request freshness metadata: %s\n",
                latticra_seal_request_freshness_error_label(freshness.error));
        return 1;
    }

    if (latticra_seal_request_freshness_report(&freshness, rendered, sizeof(rendered)) != LATTICRA_STATUS_OK) {
        fprintf(stderr, "failed to render Seal request freshness report\n");
        return 1;
    }

    fputs(rendered, stdout);
    return 0;
}
