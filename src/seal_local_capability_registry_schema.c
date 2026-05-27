#include "latticra/seal_local_capability_registry_schema.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

static int string_is(const char *value, const char *expected) {
    return value != NULL && expected != NULL && strcmp(value, expected) == 0;
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

const char *latticra_seal_local_capability_registry_schema_error_label(
    latticra_seal_local_capability_registry_schema_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_OK:
        return "ok";
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_PROFILE:
        return "invalid-profile";
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_SCOPE:
        return "invalid-scope";
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_EFFECT_CLASS:
        return "invalid-effect-class";
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_AUTHORITY_CLASS:
        return "invalid-authority-class";
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_DEFAULT_DECISION:
        return "invalid-default-decision";
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_ENTRY_CAPACITY_EXCEEDED:
        return "entry-capacity-exceeded";
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_ENTRY_WOULD_GRANT_AUTHORITY:
        return "entry-would-grant-authority";
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_ENTRY_WOULD_PERFORM_EFFECT:
        return "entry-would-perform-effect";
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_NON_REPORT_ONLY_ENTRY:
        return "non-report-only-entry";
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_BUFFER_TOO_SMALL:
        return "buffer-too-small";
    default:
        return "unknown";
    }
}

const char *latticra_seal_local_capability_registry_scope_label(
    latticra_seal_local_capability_registry_scope_t scope) {
    switch (scope) {
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCOPE_TOOL_BOUNDARY:
        return "tool-boundary";
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCOPE_REQUEST_BOUNDARY:
        return "request-boundary";
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCOPE_POLICY_BOUNDARY:
        return "policy-boundary";
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCOPE_RUNTIME_BOUNDARY:
        return "runtime-boundary";
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCOPE_EVIDENCE_BOUNDARY:
        return "evidence-boundary";
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCOPE_OPERATOR_REVIEW_BOUNDARY:
        return "operator-review-boundary";
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCOPE_INVALID:
    default:
        return "invalid";
    }
}

const char *latticra_seal_local_capability_registry_effect_class_label(
    latticra_seal_local_capability_registry_effect_class_t effect_class) {
    switch (effect_class) {
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_EFFECT_NONE:
        return "none";
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_EFFECT_TOOL:
        return "tool";
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_EFFECT_HOST_READ:
        return "host-read";
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_EFFECT_HOST_WRITE:
        return "host-write";
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_EFFECT_NETWORK:
        return "network";
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_EFFECT_RUNTIME_AUTHORITY:
        return "runtime-authority";
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_EFFECT_INVALID:
    default:
        return "invalid";
    }
}

const char *latticra_seal_local_capability_registry_authority_class_label(
    latticra_seal_local_capability_registry_authority_class_t authority_class) {
    switch (authority_class) {
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_AUTHORITY_NONE:
        return "none";
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_AUTHORITY_DESCRIPTIVE_ONLY:
        return "descriptive-only";
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_AUTHORITY_FUTURE_GUARDED:
        return "future-guarded";
    case LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_AUTHORITY_INVALID:
    default:
        return "invalid";
    }
}

latticra_status_t latticra_seal_local_capability_registry_schema_init(
    latticra_seal_local_capability_registry_schema_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(out->registry_schema_profile,
                 sizeof(out->registry_schema_profile),
                 "latticra-seal-local-capability-registry-schema/0.1");
    copy_literal(out->registry_format_version, sizeof(out->registry_format_version), "0.1");
    copy_literal(out->registry_scope, sizeof(out->registry_scope), "local-only");
    copy_literal(out->registry_mode, sizeof(out->registry_mode), "report-only");
    copy_literal(out->registry_status, sizeof(out->registry_status), "contract-only");
    out->registry_contract_present = 1u;
    out->registry_schema_planning_only = 1u;
    out->registry_loader_implemented = 0u;
    out->registry_file_loading_supported = 0u;
    out->registry_network_loading_supported = 0u;
    out->registry_signature_verification_supported = 0u;
    out->registry_trust_store_supported = 0u;
    out->registry_entry_count = 0u;
    out->registry_entry_count_max = LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_ENTRY_MAX;
    out->registry_entry_id_max = LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_ENTRY_ID_MAX;
    out->registry_namespace_max = LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_NAMESPACE_MAX;
    out->registry_name_max = LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_NAME_MAX;
    out->registry_description_max = LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_DESCRIPTION_MAX;
    out->registry_blocked_reason_max = LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_BLOCKED_REASON_MAX;
    out->default_action_deny = 1u;
    out->runtime_authority_granted = 0u;
    out->effect_performed = 0u;
    out->host_read_performed = 0u;
    out->host_write_performed = 0u;
    out->network_performed = 0u;
    out->last_error = LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_OK;
    return LATTICRA_STATUS_OK;
}

static int scope_valid(latticra_seal_local_capability_registry_scope_t scope) {
    return scope == LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCOPE_TOOL_BOUNDARY ||
           scope == LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCOPE_REQUEST_BOUNDARY ||
           scope == LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCOPE_POLICY_BOUNDARY ||
           scope == LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCOPE_RUNTIME_BOUNDARY ||
           scope == LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCOPE_EVIDENCE_BOUNDARY ||
           scope == LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCOPE_OPERATOR_REVIEW_BOUNDARY;
}

static int effect_class_valid(
    latticra_seal_local_capability_registry_effect_class_t effect_class) {
    return effect_class == LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_EFFECT_NONE ||
           effect_class == LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_EFFECT_TOOL ||
           effect_class == LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_EFFECT_HOST_READ ||
           effect_class == LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_EFFECT_HOST_WRITE ||
           effect_class == LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_EFFECT_NETWORK ||
           effect_class == LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_EFFECT_RUNTIME_AUTHORITY;
}

static int authority_class_valid(
    latticra_seal_local_capability_registry_authority_class_t authority_class) {
    return authority_class == LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_AUTHORITY_NONE ||
           authority_class == LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_AUTHORITY_DESCRIPTIVE_ONLY ||
           authority_class == LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_AUTHORITY_FUTURE_GUARDED;
}

static latticra_seal_local_capability_registry_schema_error_t entry_error(
    const latticra_seal_local_capability_registry_entry_t *entry) {
    if (entry == NULL ||
        !text_field_valid(entry->capability_id,
                          LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_ENTRY_ID_MAX) ||
        !text_field_valid(entry->capability_namespace,
                          LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_NAMESPACE_MAX) ||
        !text_field_valid(entry->capability_name,
                          LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_NAME_MAX) ||
        !text_field_valid(entry->capability_description,
                          LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_DESCRIPTION_MAX) ||
        !text_field_valid(entry->capability_blocked_reason,
                          LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_BLOCKED_REASON_MAX)) {
        return LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_INPUT;
    }

    if (!scope_valid(entry->capability_scope)) {
        return LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_SCOPE;
    }
    if (!effect_class_valid(entry->capability_effect_class)) {
        return LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_EFFECT_CLASS;
    }
    if (!authority_class_valid(entry->capability_authority_class)) {
        return LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_AUTHORITY_CLASS;
    }
    if (!string_is(entry->capability_default_decision, "deny")) {
        return LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_DEFAULT_DECISION;
    }
    if (entry->capability_grants_authority != 0u) {
        return LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_ENTRY_WOULD_GRANT_AUTHORITY;
    }
    if (entry->capability_executes_tool != 0u || entry->capability_reads_host != 0u ||
        entry->capability_writes_host != 0u || entry->capability_uses_network != 0u) {
        return LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_ENTRY_WOULD_PERFORM_EFFECT;
    }
    if (entry->capability_requires_guarded_allowlist != 1u ||
        entry->capability_requires_policy_decision != 1u ||
        entry->capability_requires_runtime_gate != 1u ||
        entry->capability_requires_runtime_dry_run != 1u ||
        entry->capability_requires_operator_review != 1u ||
        entry->capability_requires_verification_receipt != 1u ||
        entry->capability_requires_signed_request != 1u ||
        entry->capability_report_only != 1u) {
        return LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_NON_REPORT_ONLY_ENTRY;
    }

    return LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_OK;
}

static void mark_schema_error(
    latticra_seal_local_capability_registry_schema_t *schema,
    latticra_seal_local_capability_registry_schema_error_t error) {
    if (schema != NULL) {
        schema->last_error = error;
    }
}

latticra_status_t latticra_seal_local_capability_registry_schema_add_entry(
    latticra_seal_local_capability_registry_schema_t *schema,
    const latticra_seal_local_capability_registry_entry_t *entry) {
    latticra_seal_local_capability_registry_schema_error_t error;

    if (schema == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (entry == NULL) {
        mark_schema_error(schema, LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_INPUT);
        return LATTICRA_STATUS_OK;
    }
    if (schema->registry_entry_count >= LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_ENTRY_MAX ||
        schema->registry_entry_count >= schema->registry_entry_count_max) {
        mark_schema_error(schema,
                          LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_ENTRY_CAPACITY_EXCEEDED);
        return LATTICRA_STATUS_OK;
    }

    error = entry_error(entry);
    if (error != LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_OK) {
        mark_schema_error(schema, error);
        return LATTICRA_STATUS_OK;
    }

    schema->entries[schema->registry_entry_count] = *entry;
    schema->registry_entry_count += 1u;
    mark_schema_error(schema, LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_OK);
    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_seal_local_capability_registry_schema_add_default_entry(
    latticra_seal_local_capability_registry_schema_t *schema) {
    latticra_seal_local_capability_registry_entry_t entry;

    memset(&entry, 0, sizeof(entry));
    copy_literal(entry.capability_id,
                 sizeof(entry.capability_id),
                 "seal.local.registry.schema");
    copy_literal(entry.capability_namespace, sizeof(entry.capability_namespace), "seal.local");
    copy_literal(entry.capability_name,
                 sizeof(entry.capability_name),
                 "seal.local.registry.schema");
    copy_literal(entry.capability_description,
                 sizeof(entry.capability_description),
                 "Describes local Seal capability schema metadata without loading or granting capabilities.");
    entry.capability_scope =
        LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCOPE_OPERATOR_REVIEW_BOUNDARY;
    entry.capability_effect_class = LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_EFFECT_NONE;
    entry.capability_authority_class =
        LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_AUTHORITY_DESCRIPTIVE_ONLY;
    copy_literal(entry.capability_default_decision,
                 sizeof(entry.capability_default_decision),
                 "deny");
    entry.capability_requires_guarded_allowlist = 1u;
    entry.capability_requires_policy_decision = 1u;
    entry.capability_requires_runtime_gate = 1u;
    entry.capability_requires_runtime_dry_run = 1u;
    entry.capability_requires_operator_review = 1u;
    entry.capability_requires_verification_receipt = 1u;
    entry.capability_requires_signed_request = 1u;
    entry.capability_grants_authority = 0u;
    entry.capability_executes_tool = 0u;
    entry.capability_reads_host = 0u;
    entry.capability_writes_host = 0u;
    entry.capability_uses_network = 0u;
    entry.capability_report_only = 1u;
    entry.capability_deprecated = 0u;
    copy_literal(entry.capability_blocked_reason,
                 sizeof(entry.capability_blocked_reason),
                 "registry-schema-is-descriptive-only");

    return latticra_seal_local_capability_registry_schema_add_entry(schema, &entry);
}

latticra_status_t latticra_seal_local_capability_registry_schema_validate(
    latticra_seal_local_capability_registry_schema_t *schema) {
    unsigned i;

    if (schema == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    if (!string_is(schema->registry_schema_profile,
                   "latticra-seal-local-capability-registry-schema/0.1")) {
        mark_schema_error(schema, LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_PROFILE);
        return LATTICRA_STATUS_OK;
    }
    if (!string_is(schema->registry_scope, "local-only")) {
        mark_schema_error(schema, LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_SCOPE);
        return LATTICRA_STATUS_OK;
    }
    if (!string_is(schema->registry_mode, "report-only") ||
        !string_is(schema->registry_status, "contract-only") ||
        !string_is(schema->registry_format_version, "0.1") ||
        schema->registry_contract_present != 1u ||
        schema->registry_schema_planning_only != 1u ||
        schema->registry_loader_implemented != 0u ||
        schema->registry_file_loading_supported != 0u ||
        schema->registry_network_loading_supported != 0u ||
        schema->registry_signature_verification_supported != 0u ||
        schema->registry_trust_store_supported != 0u ||
        schema->default_action_deny != 1u) {
        mark_schema_error(schema, LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_INVALID_INPUT);
        return LATTICRA_STATUS_OK;
    }
    if (schema->runtime_authority_granted != 0u) {
        mark_schema_error(schema,
                          LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_ENTRY_WOULD_GRANT_AUTHORITY);
        return LATTICRA_STATUS_OK;
    }
    if (schema->effect_performed != 0u || schema->host_read_performed != 0u ||
        schema->host_write_performed != 0u || schema->network_performed != 0u) {
        mark_schema_error(schema,
                          LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_ENTRY_WOULD_PERFORM_EFFECT);
        return LATTICRA_STATUS_OK;
    }
    if (schema->registry_entry_count > LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_ENTRY_MAX ||
        schema->registry_entry_count > schema->registry_entry_count_max) {
        mark_schema_error(schema,
                          LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_ENTRY_CAPACITY_EXCEEDED);
        return LATTICRA_STATUS_OK;
    }

    for (i = 0u; i < schema->registry_entry_count; ++i) {
        latticra_seal_local_capability_registry_schema_error_t error =
            entry_error(&schema->entries[i]);
        if (error != LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_OK) {
            mark_schema_error(schema, error);
            return LATTICRA_STATUS_OK;
        }
    }

    mark_schema_error(schema, LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_OK);
    return LATTICRA_STATUS_OK;
}

int latticra_seal_local_capability_registry_schema_is_report_only(
    const latticra_seal_local_capability_registry_schema_t *schema) {
    unsigned i;

    if (schema == NULL) {
        return 0;
    }
    if (!string_is(schema->registry_schema_profile,
                   "latticra-seal-local-capability-registry-schema/0.1") ||
        !string_is(schema->registry_format_version, "0.1") ||
        !string_is(schema->registry_scope, "local-only") ||
        !string_is(schema->registry_mode, "report-only") ||
        !string_is(schema->registry_status, "contract-only") ||
        schema->registry_contract_present != 1u ||
        schema->registry_schema_planning_only != 1u ||
        schema->registry_loader_implemented != 0u ||
        schema->registry_file_loading_supported != 0u ||
        schema->registry_network_loading_supported != 0u ||
        schema->registry_signature_verification_supported != 0u ||
        schema->registry_trust_store_supported != 0u ||
        schema->default_action_deny != 1u ||
        schema->runtime_authority_granted != 0u ||
        schema->effect_performed != 0u ||
        schema->host_read_performed != 0u ||
        schema->host_write_performed != 0u ||
        schema->network_performed != 0u ||
        schema->registry_entry_count > LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_ENTRY_MAX ||
        schema->registry_entry_count > schema->registry_entry_count_max ||
        schema->last_error != LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_OK) {
        return 0;
    }

    for (i = 0u; i < schema->registry_entry_count; ++i) {
        if (entry_error(&schema->entries[i]) !=
            LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_OK) {
            return 0;
        }
    }

    return 1;
}

static int append_format(char *buffer,
                         size_t buffer_len,
                         size_t *offset,
                         const char *format,
                         ...) {
    va_list args;
    int written;
    size_t remaining;

    if (buffer == NULL || offset == NULL || format == NULL || *offset >= buffer_len) {
        return 0;
    }

    remaining = buffer_len - *offset;
    va_start(args, format);
    written = vsnprintf(buffer + *offset, remaining, format, args);
    va_end(args);

    if (written < 0 || (size_t)written >= remaining) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return 0;
    }

    *offset += (size_t)written;
    return 1;
}

latticra_status_t latticra_seal_local_capability_registry_schema_render(
    const latticra_seal_local_capability_registry_schema_t *schema,
    char *buffer,
    size_t buffer_len) {
    size_t offset = 0u;
    unsigned i;

    if (schema == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (buffer_len == 0u) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    if (!append_format(buffer,
                       buffer_len,
                       &offset,
                       "LATTICRA SEAL LOCAL CAPABILITY REGISTRY SCHEMA REPORT\n"
                       "registry_schema_profile=%s\n"
                       "registry_format_version=%s\n"
                       "registry_scope=%s\n"
                       "registry_mode=%s\n"
                       "registry_status=%s\n"
                       "registry_contract_present=%u\n"
                       "registry_schema_planning_only=%u\n"
                       "registry_loader_implemented=%u\n"
                       "registry_file_loading_supported=%u\n"
                       "registry_network_loading_supported=%u\n"
                       "registry_signature_verification_supported=%u\n"
                       "registry_trust_store_supported=%u\n"
                       "registry_entry_count=%u\n"
                       "registry_entry_count_max=%u\n"
                       "registry_entry_id_max=%u\n"
                       "registry_namespace_max=%u\n"
                       "registry_name_max=%u\n"
                       "registry_description_max=%u\n"
                       "registry_blocked_reason_max=%u\n"
                       "default_action_deny=%u\n"
                       "runtime_authority_granted=%u\n"
                       "effect_performed=%u\n"
                       "host_read_performed=%u\n"
                       "host_write_performed=%u\n"
                       "network_performed=%u\n",
                       schema->registry_schema_profile,
                       schema->registry_format_version,
                       schema->registry_scope,
                       schema->registry_mode,
                       schema->registry_status,
                       schema->registry_contract_present,
                       schema->registry_schema_planning_only,
                       schema->registry_loader_implemented,
                       schema->registry_file_loading_supported,
                       schema->registry_network_loading_supported,
                       schema->registry_signature_verification_supported,
                       schema->registry_trust_store_supported,
                       schema->registry_entry_count,
                       schema->registry_entry_count_max,
                       schema->registry_entry_id_max,
                       schema->registry_namespace_max,
                       schema->registry_name_max,
                       schema->registry_description_max,
                       schema->registry_blocked_reason_max,
                       schema->default_action_deny,
                       schema->runtime_authority_granted,
                       schema->effect_performed,
                       schema->host_read_performed,
                       schema->host_write_performed,
                       schema->network_performed)) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    for (i = 0u; i < schema->registry_entry_count; ++i) {
        const latticra_seal_local_capability_registry_entry_t *entry = &schema->entries[i];
        if (!append_format(buffer,
                           buffer_len,
                           &offset,
                           "capability_id=%s\n"
                           "capability_namespace=%s\n"
                           "capability_name=%s\n"
                           "capability_description=%s\n"
                           "capability_scope=%s\n"
                           "capability_effect_class=%s\n"
                           "capability_authority_class=%s\n"
                           "capability_default_decision=%s\n"
                           "capability_requires_guarded_allowlist=%u\n"
                           "capability_requires_policy_decision=%u\n"
                           "capability_requires_runtime_gate=%u\n"
                           "capability_requires_runtime_dry_run=%u\n"
                           "capability_requires_operator_review=%u\n"
                           "capability_requires_verification_receipt=%u\n"
                           "capability_requires_signed_request=%u\n"
                           "capability_grants_authority=%u\n"
                           "capability_executes_tool=%u\n"
                           "capability_reads_host=%u\n"
                           "capability_writes_host=%u\n"
                           "capability_uses_network=%u\n"
                           "capability_report_only=%u\n"
                           "capability_deprecated=%u\n"
                           "capability_blocked_reason=%s\n",
                           entry->capability_id,
                           entry->capability_namespace,
                           entry->capability_name,
                           entry->capability_description,
                           latticra_seal_local_capability_registry_scope_label(
                               entry->capability_scope),
                           latticra_seal_local_capability_registry_effect_class_label(
                               entry->capability_effect_class),
                           latticra_seal_local_capability_registry_authority_class_label(
                               entry->capability_authority_class),
                           entry->capability_default_decision,
                           entry->capability_requires_guarded_allowlist,
                           entry->capability_requires_policy_decision,
                           entry->capability_requires_runtime_gate,
                           entry->capability_requires_runtime_dry_run,
                           entry->capability_requires_operator_review,
                           entry->capability_requires_verification_receipt,
                           entry->capability_requires_signed_request,
                           entry->capability_grants_authority,
                           entry->capability_executes_tool,
                           entry->capability_reads_host,
                           entry->capability_writes_host,
                           entry->capability_uses_network,
                           entry->capability_report_only,
                           entry->capability_deprecated,
                           entry->capability_blocked_reason)) {
            return LATTICRA_STATUS_BUFFER_TOO_SMALL;
        }
    }

    if (!append_format(buffer,
                       buffer_len,
                       &offset,
                       "error=%s\n",
                       latticra_seal_local_capability_registry_schema_error_label(
                           schema->last_error))) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
