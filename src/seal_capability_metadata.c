#include "latticra/seal_capability_metadata.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

static size_t bounded_string_len(const char *value, size_t max_len, int *terminated) {
    size_t i;

    if (terminated != NULL) {
        *terminated = 0;
    }
    if (value == NULL) {
        return 0u;
    }
    for (i = 0u; i < max_len; ++i) {
        if (value[i] == '\0') {
            if (terminated != NULL) {
                *terminated = 1;
            }
            return i;
        }
    }
    return max_len;
}

static int text_field_valid(const char *value, size_t max_len) {
    int terminated = 0;
    size_t len = bounded_string_len(value, max_len, &terminated);

    return terminated == 1 && len > 0u;
}

static int bounded_string_is(const char *value, size_t max_len, const char *expected) {
    int terminated = 0;
    size_t value_len;
    size_t expected_len;

    if (value == NULL || expected == NULL) {
        return 0;
    }
    value_len = bounded_string_len(value, max_len, &terminated);
    if (terminated != 1) {
        return 0;
    }
    expected_len = strlen(expected);
    return value_len == expected_len && memcmp(value, expected, value_len) == 0;
}

static int text_field_empty(const char *value, size_t max_len) {
    int terminated = 0;
    size_t len = bounded_string_len(value, max_len, &terminated);

    return terminated == 1 && len == 0u;
}

static int error_valid(latticra_seal_capability_metadata_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_CAPABILITY_METADATA_OK:
    case LATTICRA_SEAL_CAPABILITY_METADATA_INVALID_INPUT:
    case LATTICRA_SEAL_CAPABILITY_METADATA_INVALID_CAPABILITY_NAME:
    case LATTICRA_SEAL_CAPABILITY_METADATA_INVALID_FIXTURE:
    case LATTICRA_SEAL_CAPABILITY_METADATA_BUFFER_TOO_SMALL:
        return 1;
    default:
        return 0;
    }
}

static int present_capability_name(const char *capability_name) {
    return capability_name != NULL && capability_name[0] != '\0';
}

static int valid_capability_name(const char *capability_name) {
    int terminated = 0;
    size_t len = bounded_string_len(capability_name,
                                    LATTICRA_SEAL_CAPABILITY_METADATA_NAME_MAX,
                                    &terminated);

    return terminated == 1 && len > 0u &&
           len < LATTICRA_SEAL_CAPABILITY_METADATA_NAME_MAX;
}

const char *latticra_seal_capability_metadata_error_label(
    latticra_seal_capability_metadata_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_CAPABILITY_METADATA_OK:
        return "ok";
    case LATTICRA_SEAL_CAPABILITY_METADATA_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_CAPABILITY_METADATA_INVALID_CAPABILITY_NAME:
        return "invalid-capability-name";
    case LATTICRA_SEAL_CAPABILITY_METADATA_INVALID_FIXTURE:
        return "invalid-fixture";
    case LATTICRA_SEAL_CAPABILITY_METADATA_BUFFER_TOO_SMALL:
        return "buffer-too-small";
    default:
        return "unknown";
    }
}

latticra_seal_capability_metadata_fixture_t latticra_seal_capability_metadata_fixture(void) {
    latticra_seal_capability_metadata_fixture_t fixture;

    memset(&fixture, 0, sizeof(fixture));
    copy_literal(fixture.capability_fixture_source,
                 sizeof(fixture.capability_fixture_source),
                 "deterministic-local-fixture");
    fixture.capability_fixture_entry_count = 3u;
    copy_literal(fixture.entries[0].capability_name,
                 sizeof(fixture.entries[0].capability_name),
                 "seal.capability.inspect");
    copy_literal(fixture.entries[0].capability_scope,
                 sizeof(fixture.entries[0].capability_scope),
                 "tool-boundary");
    copy_literal(fixture.entries[0].capability_effect_class,
                 sizeof(fixture.entries[0].capability_effect_class),
                 "none");
    copy_literal(fixture.entries[1].capability_name,
                 sizeof(fixture.entries[1].capability_name),
                 "seal.capability.report");
    copy_literal(fixture.entries[1].capability_scope,
                 sizeof(fixture.entries[1].capability_scope),
                 "evidence-boundary");
    copy_literal(fixture.entries[1].capability_effect_class,
                 sizeof(fixture.entries[1].capability_effect_class),
                 "none");
    copy_literal(fixture.entries[2].capability_name,
                 sizeof(fixture.entries[2].capability_name),
                 "seal.capability.dry_run");
    copy_literal(fixture.entries[2].capability_scope,
                 sizeof(fixture.entries[2].capability_scope),
                 "runtime-boundary");
    copy_literal(fixture.entries[2].capability_effect_class,
                 sizeof(fixture.entries[2].capability_effect_class),
                 "none");
    return fixture;
}

static const latticra_seal_capability_metadata_entry_t *fixture_find(
    const latticra_seal_capability_metadata_fixture_t *fixture,
    const char *capability_name) {
    unsigned i;

    if (fixture == NULL || capability_name == NULL ||
        fixture->capability_fixture_entry_count > LATTICRA_SEAL_CAPABILITY_METADATA_ENTRY_MAX) {
        return NULL;
    }

    for (i = 0u; i < fixture->capability_fixture_entry_count; ++i) {
        if (bounded_string_is(fixture->entries[i].capability_name,
                              LATTICRA_SEAL_CAPABILITY_METADATA_NAME_MAX,
                              capability_name)) {
            return &fixture->entries[i];
        }
    }

    return NULL;
}

static void result_init(latticra_seal_capability_metadata_result_t *result,
                        const char *capability_name) {
    latticra_seal_capability_metadata_fixture_t fixture = latticra_seal_capability_metadata_fixture();

    memset(result, 0, sizeof(*result));
    copy_literal(result->capability_metadata_profile,
                 sizeof(result->capability_metadata_profile),
                 "latticra-seal-capability-metadata/0.1");
    copy_literal(result->capability_name, sizeof(result->capability_name), capability_name);
    copy_literal(result->capability_scope, sizeof(result->capability_scope), "unknown");
    copy_literal(result->capability_effect_class, sizeof(result->capability_effect_class), "none");
    copy_literal(result->capability_fixture_source,
                 sizeof(result->capability_fixture_source),
                 fixture.capability_fixture_source);
    result->capability_fixture_entry_count = fixture.capability_fixture_entry_count;
    result->capability_lookup_performed = 1u;
    result->capability_name_present = present_capability_name(capability_name) ? 1u : 0u;
    result->capability_known = 0u;
    result->capability_unknown = 1u;
    result->capability_candidate = 0u;
    result->capability_requires_guarded_allowlist = 1u;
    result->capability_requires_policy_decision = 1u;
    result->capability_requires_runtime_gate = 1u;
    result->capability_requires_runtime_dry_run = 1u;
    result->capability_requires_operator_review = 1u;
    result->capability_grants_authority = 0u;
    result->capability_executes_tool = 0u;
    result->capability_reads_host = 0u;
    result->capability_writes_host = 0u;
    result->capability_uses_network = 0u;
    result->default_action_deny = 1u;
    result->would_allow = 0u;
    result->would_deny = 1u;
    result->would_require_operator_review = 1u;
    result->unknown_tool_denied = 1u;
    result->unsigned_request_denied = 1u;
    result->invalid_schema_denied = 1u;
    result->stale_request_denied = 1u;
    result->replayed_request_denied = 1u;
    result->invalid_signature_denied = 1u;
    result->unknown_capability_denied = 1u;
    result->missing_capability_denied = result->capability_name_present == 0u ? 1u : 0u;
    result->invalid_capability_denied = 0u;
    copy_literal(result->blocked_reason,
                 sizeof(result->blocked_reason),
                 result->capability_name_present == 0u ? "missing-capability-denied" : "default-deny-capability-metadata");
    result->report_only = 1u;
    copy_literal(result->mode, sizeof(result->mode), "report-only");
    copy_literal(result->status, sizeof(result->status), "capability-metadata");
    result->error = LATTICRA_SEAL_CAPABILITY_METADATA_INVALID_INPUT;
}

latticra_status_t latticra_seal_capability_metadata_result_missing(
    latticra_seal_capability_metadata_result_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    result_init(out, NULL);
    out->error = LATTICRA_SEAL_CAPABILITY_METADATA_OK;
    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_seal_capability_metadata_result_unknown(
    const char *capability_name,
    latticra_seal_capability_metadata_result_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    if (!valid_capability_name(capability_name)) {
        result_init(out, "invalid-capability");
        out->error = LATTICRA_SEAL_CAPABILITY_METADATA_INVALID_CAPABILITY_NAME;
        out->invalid_capability_denied = 1u;
        copy_literal(out->blocked_reason, sizeof(out->blocked_reason), "invalid-capability-denied");
        copy_literal(out->status, sizeof(out->status), "invalid-capability-name");
        return LATTICRA_STATUS_OK;
    }

    result_init(out, capability_name);
    out->error = LATTICRA_SEAL_CAPABILITY_METADATA_OK;
    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_seal_capability_metadata_result_candidate(
    const char *capability_name,
    latticra_seal_capability_metadata_result_t *out) {
    latticra_seal_capability_metadata_fixture_t fixture;
    const latticra_seal_capability_metadata_entry_t *entry;

    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    if (!valid_capability_name(capability_name)) {
        result_init(out, "invalid-capability");
        out->error = LATTICRA_SEAL_CAPABILITY_METADATA_INVALID_CAPABILITY_NAME;
        out->invalid_capability_denied = 1u;
        copy_literal(out->blocked_reason, sizeof(out->blocked_reason), "invalid-capability-denied");
        copy_literal(out->status, sizeof(out->status), "invalid-capability-name");
        return LATTICRA_STATUS_OK;
    }

    result_init(out, capability_name);
    fixture = latticra_seal_capability_metadata_fixture();
    entry = fixture_find(&fixture, capability_name);
    if (entry == NULL) {
        return latticra_seal_capability_metadata_result_unknown(capability_name, out);
    }

    out->capability_known = 1u;
    out->capability_unknown = 0u;
    out->capability_candidate = 1u;
    copy_literal(out->capability_scope, sizeof(out->capability_scope), entry->capability_scope);
    copy_literal(out->capability_effect_class,
                 sizeof(out->capability_effect_class),
                 entry->capability_effect_class);
    out->missing_capability_denied = 0u;
    copy_literal(out->blocked_reason,
                 sizeof(out->blocked_reason),
                 "known-capability-candidate-still-denied");
    out->error = LATTICRA_SEAL_CAPABILITY_METADATA_OK;
    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_seal_capability_metadata_evaluate(
    const char *capability_name,
    latticra_seal_capability_metadata_result_t *out) {
    latticra_seal_capability_metadata_fixture_t fixture;

    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    if (!present_capability_name(capability_name)) {
        return latticra_seal_capability_metadata_result_missing(out);
    }

    if (!valid_capability_name(capability_name)) {
        return latticra_seal_capability_metadata_result_unknown(capability_name, out);
    }

    fixture = latticra_seal_capability_metadata_fixture();
    if (fixture.capability_fixture_entry_count == 0u ||
        fixture.capability_fixture_entry_count > LATTICRA_SEAL_CAPABILITY_METADATA_ENTRY_MAX) {
        result_init(out, capability_name);
        out->error = LATTICRA_SEAL_CAPABILITY_METADATA_INVALID_FIXTURE;
        copy_literal(out->blocked_reason, sizeof(out->blocked_reason), "invalid-fixture");
        copy_literal(out->status, sizeof(out->status), "invalid-fixture");
        return LATTICRA_STATUS_OK;
    }

    if (fixture_find(&fixture, capability_name) != NULL) {
        return latticra_seal_capability_metadata_result_candidate(capability_name, out);
    }

    return latticra_seal_capability_metadata_result_unknown(capability_name, out);
}

int latticra_seal_capability_metadata_is_report_only(
    const latticra_seal_capability_metadata_result_t *result) {
    if (result == NULL) {
        return 0;
    }

    return result->capability_lookup_performed == 1u &&
           result->capability_fixture_entry_count <=
               LATTICRA_SEAL_CAPABILITY_METADATA_ENTRY_MAX &&
           result->capability_requires_guarded_allowlist == 1u &&
           result->capability_requires_policy_decision == 1u &&
           result->capability_requires_runtime_gate == 1u &&
           result->capability_requires_runtime_dry_run == 1u &&
           result->capability_requires_operator_review == 1u &&
           result->capability_grants_authority == 0u &&
           result->capability_executes_tool == 0u &&
           result->capability_reads_host == 0u &&
           result->capability_writes_host == 0u &&
           result->capability_uses_network == 0u &&
           result->default_action_deny == 1u &&
           result->would_allow == 0u &&
           result->would_deny == 1u &&
           result->would_require_operator_review == 1u &&
           result->report_only == 1u &&
           error_valid(result->error) &&
           bounded_string_is(result->capability_metadata_profile,
                             LATTICRA_SEAL_CAPABILITY_METADATA_PROFILE_MAX,
                             "latticra-seal-capability-metadata/0.1") &&
           ((result->capability_name_present == 1u &&
             text_field_valid(result->capability_name,
                              LATTICRA_SEAL_CAPABILITY_METADATA_NAME_MAX)) ||
            (result->capability_name_present == 0u &&
             text_field_empty(result->capability_name,
                              LATTICRA_SEAL_CAPABILITY_METADATA_NAME_MAX))) &&
           text_field_valid(result->capability_scope,
                            LATTICRA_SEAL_CAPABILITY_METADATA_SCOPE_MAX) &&
           text_field_valid(result->capability_effect_class,
                            LATTICRA_SEAL_CAPABILITY_METADATA_EFFECT_MAX) &&
           text_field_valid(result->capability_fixture_source,
                            LATTICRA_SEAL_CAPABILITY_METADATA_SOURCE_MAX) &&
           text_field_valid(result->blocked_reason,
                            LATTICRA_SEAL_CAPABILITY_METADATA_REASON_MAX) &&
           bounded_string_is(result->mode,
                             LATTICRA_SEAL_CAPABILITY_METADATA_STATUS_MAX,
                             "report-only") &&
           text_field_valid(result->status,
                            LATTICRA_SEAL_CAPABILITY_METADATA_STATUS_MAX);
}

latticra_status_t latticra_seal_capability_metadata_report(
    const latticra_seal_capability_metadata_result_t *result,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (result == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (buffer_len == 0u) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }
    if (!latticra_seal_capability_metadata_is_report_only(result)) {
        buffer[0] = '\0';
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL CAPABILITY METADATA\n"
        "capability_metadata_profile=%s\n"
        "capability_name=%s\n"
        "capability_scope=%s\n"
        "capability_effect_class=%s\n"
        "capability_fixture_source=%s\n"
        "capability_fixture_entry_count=%u\n"
        "capability_lookup_performed=%u\n"
        "capability_name_present=%u\n"
        "capability_known=%u\n"
        "capability_unknown=%u\n"
        "capability_candidate=%u\n"
        "capability_requires_guarded_allowlist=%u\n"
        "capability_requires_policy_decision=%u\n"
        "capability_requires_runtime_gate=%u\n"
        "capability_requires_runtime_dry_run=%u\n"
        "capability_requires_operator_review=%u\n"
        "capability_grants_authority=%u\n"
        "capability_executes_tool=%u\n"
        "capability_reads_host=%u\n"
        "capability_writes_host=%u\n"
        "capability_uses_network=%u\n"
        "default_action_deny=%u\n"
        "would_allow=%u\n"
        "would_deny=%u\n"
        "would_require_operator_review=%u\n"
        "unknown_tool_denied=%u\n"
        "unsigned_request_denied=%u\n"
        "invalid_schema_denied=%u\n"
        "stale_request_denied=%u\n"
        "replayed_request_denied=%u\n"
        "invalid_signature_denied=%u\n"
        "unknown_capability_denied=%u\n"
        "missing_capability_denied=%u\n"
        "invalid_capability_denied=%u\n"
        "blocked_reason=%s\n"
        "report_only=%u\n"
        "mode=%s\n"
        "error=%s\n"
        "status=%s\n",
        result->capability_metadata_profile,
        result->capability_name,
        result->capability_scope,
        result->capability_effect_class,
        result->capability_fixture_source,
        result->capability_fixture_entry_count,
        result->capability_lookup_performed,
        result->capability_name_present,
        result->capability_known,
        result->capability_unknown,
        result->capability_candidate,
        result->capability_requires_guarded_allowlist,
        result->capability_requires_policy_decision,
        result->capability_requires_runtime_gate,
        result->capability_requires_runtime_dry_run,
        result->capability_requires_operator_review,
        result->capability_grants_authority,
        result->capability_executes_tool,
        result->capability_reads_host,
        result->capability_writes_host,
        result->capability_uses_network,
        result->default_action_deny,
        result->would_allow,
        result->would_deny,
        result->would_require_operator_review,
        result->unknown_tool_denied,
        result->unsigned_request_denied,
        result->invalid_schema_denied,
        result->stale_request_denied,
        result->replayed_request_denied,
        result->invalid_signature_denied,
        result->unknown_capability_denied,
        result->missing_capability_denied,
        result->invalid_capability_denied,
        result->blocked_reason,
        result->report_only,
        result->mode,
        latticra_seal_capability_metadata_error_label(result->error),
        result->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
