#include "latticra/seal_guarded_allowlist.h"

#include <stdio.h>
#include <string.h>

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

static int valid_tool_name(const char *tool_name) {
    size_t len;

    if (tool_name == NULL) {
        return 0;
    }

    len = strlen(tool_name);
    return len > 0u && len < LATTICRA_SEAL_GUARDED_ALLOWLIST_TOOL_NAME_MAX;
}

const char *latticra_seal_guarded_allowlist_error_label(
    latticra_seal_guarded_allowlist_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_GUARDED_ALLOWLIST_OK:
        return "ok";
    case LATTICRA_SEAL_GUARDED_ALLOWLIST_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_GUARDED_ALLOWLIST_INVALID_TOOL_NAME:
        return "invalid-tool-name";
    case LATTICRA_SEAL_GUARDED_ALLOWLIST_INVALID_ALLOWLIST:
        return "invalid-allowlist";
    case LATTICRA_SEAL_GUARDED_ALLOWLIST_BUFFER_TOO_SMALL:
        return "buffer-too-small";
    default:
        return "unknown";
    }
}

latticra_seal_guarded_allowlist_t latticra_seal_guarded_allowlist_fixture(void) {
    latticra_seal_guarded_allowlist_t allowlist;

    memset(&allowlist, 0, sizeof(allowlist));
    copy_literal(allowlist.allowlist_source,
                 sizeof(allowlist.allowlist_source),
                 "deterministic-local-fixture");
    allowlist.allowlist_entry_count = 3u;
    copy_literal(allowlist.entries[0].tool_name,
                 sizeof(allowlist.entries[0].tool_name),
                 "latticra.seal.inspect");
    copy_literal(allowlist.entries[1].tool_name,
                 sizeof(allowlist.entries[1].tool_name),
                 "latticra.seal.report");
    copy_literal(allowlist.entries[2].tool_name,
                 sizeof(allowlist.entries[2].tool_name),
                 "latticra.seal.dry_run");
    return allowlist;
}

static int fixture_contains(const latticra_seal_guarded_allowlist_t *allowlist,
                            const char *tool_name) {
    unsigned i;

    if (allowlist == NULL || tool_name == NULL ||
        allowlist->allowlist_entry_count > LATTICRA_SEAL_GUARDED_ALLOWLIST_ENTRY_MAX) {
        return 0;
    }

    for (i = 0u; i < allowlist->allowlist_entry_count; ++i) {
        if (strcmp(allowlist->entries[i].tool_name, tool_name) == 0) {
            return 1;
        }
    }

    return 0;
}

static void result_init(latticra_seal_guarded_allowlist_result_t *result,
                        const char *tool_name) {
    latticra_seal_guarded_allowlist_t allowlist = latticra_seal_guarded_allowlist_fixture();

    memset(result, 0, sizeof(*result));
    copy_literal(result->guarded_allowlist_profile,
                 sizeof(result->guarded_allowlist_profile),
                 "latticra-seal-guarded-allowlist/0.1");
    copy_literal(result->tool_name, sizeof(result->tool_name), tool_name);
    copy_literal(result->allowlist_source,
                 sizeof(result->allowlist_source),
                 allowlist.allowlist_source);
    result->allowlist_entry_count = allowlist.allowlist_entry_count;
    result->allowlist_lookup_performed = 1u;
    result->requested_tool_name_present = valid_tool_name(tool_name) ? 1u : 0u;
    result->requested_tool_known = 0u;
    result->requested_tool_unknown = 1u;
    result->requested_tool_candidate = 0u;
    result->requested_tool_allow_candidate = 0u;
    result->allow_candidate_requires_policy_decision = 1u;
    result->allow_candidate_requires_runtime_gate = 1u;
    result->allow_candidate_requires_runtime_dry_run = 1u;
    result->allow_candidate_requires_operator_review = 1u;
    result->allow_candidate_grants_authority = 0u;
    result->allow_candidate_executes_tool = 0u;
    result->allow_candidate_reads_host = 0u;
    result->allow_candidate_writes_host = 0u;
    result->allow_candidate_uses_network = 0u;
    result->default_action_deny = 1u;
    result->would_allow = 0u;
    result->would_deny = 1u;
    result->would_require_operator_review = 1u;
    copy_literal(result->blocked_reason,
                 sizeof(result->blocked_reason),
                 "default-deny-guarded-allowlist");
    result->report_only = 1u;
    copy_literal(result->mode, sizeof(result->mode), "report-only");
    copy_literal(result->status, sizeof(result->status), "guarded-allowlist-metadata");
    result->error = LATTICRA_SEAL_GUARDED_ALLOWLIST_INVALID_INPUT;
}

latticra_status_t latticra_seal_guarded_allowlist_result_unknown(
    const char *tool_name,
    latticra_seal_guarded_allowlist_result_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    result_init(out, tool_name);

    if (!valid_tool_name(tool_name)) {
        out->error = LATTICRA_SEAL_GUARDED_ALLOWLIST_INVALID_TOOL_NAME;
        copy_literal(out->blocked_reason, sizeof(out->blocked_reason), "invalid-tool-name");
        copy_literal(out->status, sizeof(out->status), "invalid-tool-name");
        return LATTICRA_STATUS_OK;
    }

    out->error = LATTICRA_SEAL_GUARDED_ALLOWLIST_OK;
    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_seal_guarded_allowlist_result_candidate(
    const char *tool_name,
    latticra_seal_guarded_allowlist_result_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    result_init(out, tool_name);

    if (!valid_tool_name(tool_name)) {
        out->error = LATTICRA_SEAL_GUARDED_ALLOWLIST_INVALID_TOOL_NAME;
        copy_literal(out->blocked_reason, sizeof(out->blocked_reason), "invalid-tool-name");
        copy_literal(out->status, sizeof(out->status), "invalid-tool-name");
        return LATTICRA_STATUS_OK;
    }

    out->requested_tool_known = 1u;
    out->requested_tool_unknown = 0u;
    out->requested_tool_candidate = 1u;
    out->requested_tool_allow_candidate = 1u;
    copy_literal(out->blocked_reason,
                 sizeof(out->blocked_reason),
                 "known-tool-candidate-still-denied");
    out->error = LATTICRA_SEAL_GUARDED_ALLOWLIST_OK;
    return LATTICRA_STATUS_OK;
}

latticra_status_t latticra_seal_guarded_allowlist_evaluate(
    const char *tool_name,
    latticra_seal_guarded_allowlist_result_t *out) {
    latticra_seal_guarded_allowlist_t allowlist;

    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    if (!valid_tool_name(tool_name)) {
        return latticra_seal_guarded_allowlist_result_unknown(tool_name, out);
    }

    allowlist = latticra_seal_guarded_allowlist_fixture();
    if (allowlist.allowlist_entry_count == 0u ||
        allowlist.allowlist_entry_count > LATTICRA_SEAL_GUARDED_ALLOWLIST_ENTRY_MAX) {
        result_init(out, tool_name);
        out->error = LATTICRA_SEAL_GUARDED_ALLOWLIST_INVALID_ALLOWLIST;
        copy_literal(out->blocked_reason, sizeof(out->blocked_reason), "invalid-allowlist");
        copy_literal(out->status, sizeof(out->status), "invalid-allowlist");
        return LATTICRA_STATUS_OK;
    }

    if (fixture_contains(&allowlist, tool_name) == 1) {
        return latticra_seal_guarded_allowlist_result_candidate(tool_name, out);
    }

    return latticra_seal_guarded_allowlist_result_unknown(tool_name, out);
}

int latticra_seal_guarded_allowlist_is_report_only(
    const latticra_seal_guarded_allowlist_result_t *result) {
    if (result == NULL) {
        return 0;
    }

    return result->allowlist_lookup_performed == 1u &&
           result->allow_candidate_requires_policy_decision == 1u &&
           result->allow_candidate_requires_runtime_gate == 1u &&
           result->allow_candidate_requires_runtime_dry_run == 1u &&
           result->allow_candidate_requires_operator_review == 1u &&
           result->allow_candidate_grants_authority == 0u &&
           result->allow_candidate_executes_tool == 0u &&
           result->allow_candidate_reads_host == 0u &&
           result->allow_candidate_writes_host == 0u &&
           result->allow_candidate_uses_network == 0u &&
           result->default_action_deny == 1u &&
           result->would_allow == 0u &&
           result->would_deny == 1u &&
           result->would_require_operator_review == 1u &&
           result->report_only == 1u &&
           strcmp(result->mode, "report-only") == 0;
}

latticra_status_t latticra_seal_guarded_allowlist_report(
    const latticra_seal_guarded_allowlist_result_t *result,
    char *buffer,
    size_t buffer_len) {
    int written;

    if (result == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    written = snprintf(
        buffer,
        buffer_len,
        "LATTICRA SEAL GUARDED ALLOWLIST\n"
        "guarded_allowlist_profile=%s\n"
        "tool_name=%s\n"
        "allowlist_source=%s\n"
        "allowlist_entry_count=%u\n"
        "allowlist_lookup_performed=%u\n"
        "requested_tool_name_present=%u\n"
        "requested_tool_known=%u\n"
        "requested_tool_unknown=%u\n"
        "requested_tool_candidate=%u\n"
        "requested_tool_allow_candidate=%u\n"
        "allow_candidate_requires_policy_decision=%u\n"
        "allow_candidate_requires_runtime_gate=%u\n"
        "allow_candidate_requires_runtime_dry_run=%u\n"
        "allow_candidate_requires_operator_review=%u\n"
        "allow_candidate_grants_authority=%u\n"
        "allow_candidate_executes_tool=%u\n"
        "allow_candidate_reads_host=%u\n"
        "allow_candidate_writes_host=%u\n"
        "allow_candidate_uses_network=%u\n"
        "default_action_deny=%u\n"
        "would_allow=%u\n"
        "would_deny=%u\n"
        "would_require_operator_review=%u\n"
        "blocked_reason=%s\n"
        "report_only=%u\n"
        "mode=%s\n"
        "error=%s\n"
        "status=%s\n",
        result->guarded_allowlist_profile,
        result->tool_name,
        result->allowlist_source,
        result->allowlist_entry_count,
        result->allowlist_lookup_performed,
        result->requested_tool_name_present,
        result->requested_tool_known,
        result->requested_tool_unknown,
        result->requested_tool_candidate,
        result->requested_tool_allow_candidate,
        result->allow_candidate_requires_policy_decision,
        result->allow_candidate_requires_runtime_gate,
        result->allow_candidate_requires_runtime_dry_run,
        result->allow_candidate_requires_operator_review,
        result->allow_candidate_grants_authority,
        result->allow_candidate_executes_tool,
        result->allow_candidate_reads_host,
        result->allow_candidate_writes_host,
        result->allow_candidate_uses_network,
        result->default_action_deny,
        result->would_allow,
        result->would_deny,
        result->would_require_operator_review,
        result->blocked_reason,
        result->report_only,
        result->mode,
        latticra_seal_guarded_allowlist_error_label(result->error),
        result->status);

    if (written < 0 || (size_t)written >= buffer_len) {
        if (buffer_len > 0u) {
            buffer[0] = '\0';
        }
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
