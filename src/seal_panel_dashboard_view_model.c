#include "latticra/seal_panel_dashboard_view_model.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    const char *row_id;
    const char *row_label;
    latticra_seal_panel_dashboard_view_model_category_t category;
    const char *present_summary;
} required_row_spec_t;

static const required_row_spec_t required_rows[] = {
    {"seal.product.spine",
     "Seal product spine",
     LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_MODE,
     "Product spine evidence remains report-only and denied by default."},
    {"seal.operator.receipt",
     "Seal operator receipt",
     LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_EVIDENCE,
     "Operator receipt evidence is visible without granting authority."},
    {"seal.local.capability.registry.schema",
     "Seal local capability registry schema",
     LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_SOURCE,
     "Capability registry schema evidence is descriptive only."},
    {"seal.policy.decision",
     "Seal policy decision",
     LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_DECISION,
     "Policy decision evidence remains denied by default."},
    {"seal.signed.request",
     "Seal signed request",
     LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_EVIDENCE,
     "Signed request evidence is display-only in this view model."},
    {"seal.request.freshness",
     "Seal request freshness",
     LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_EVIDENCE,
     "Request freshness evidence is visible without runtime authority."},
    {"seal.runtime.dry.run",
     "Seal runtime dry run",
     LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_DECISION,
     "Runtime dry-run evidence stays no-effect and denied."},
    {"seal.verification.receipt",
     "Seal verification receipt",
     LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_EVIDENCE,
     "Verification receipt evidence is visible without trust-store lookup."},
    {"seal.capability.gate",
     "Seal capability gate",
     LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_AUTHORITY,
     "Capability gate evidence remains authority-neutral."},
    {"seal.effect.decision",
     "Seal effect decision",
     LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_AUTHORITY,
     "Effect decision evidence cannot perform effects."},
    {"seal.runtime.handoff",
     "Seal runtime handoff",
     LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_AUTHORITY,
     "Runtime handoff evidence remains inactive."},
    {"seal.status.rollup",
     "Seal status rollup",
     LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_NEXT_STEP,
     "Status rollup evidence points to the next guarded slice."}};

static void copy_literal(char *destination, size_t destination_len, const char *source) {
    if (destination_len == 0u) {
        return;
    }
    (void)snprintf(destination, destination_len, "%s", source != NULL ? source : "");
}

static int string_is(const char *value, const char *expected) {
    return value != NULL && expected != NULL && strcmp(value, expected) == 0;
}

static int text_contains(const char *value, const char *needle) {
    return value != NULL && needle != NULL && strstr(value, needle) != NULL;
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

const char *latticra_seal_panel_dashboard_view_model_error_label(
    latticra_seal_panel_dashboard_view_model_error_t error) {
    switch (error) {
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_OK:
        return "ok";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_INPUT:
        return "invalid-input";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_PROFILE:
        return "invalid-profile";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_SOURCE_ID:
        return "invalid-source-id";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_ROW_ID:
        return "invalid-row-id";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_CATEGORY:
        return "invalid-category";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_STATE:
        return "invalid-state";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_DECISION:
        return "invalid-decision";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_SEVERITY:
        return "invalid-severity";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_CAPACITY_EXCEEDED:
        return "source-capacity-exceeded";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_ROW_CAPACITY_EXCEEDED:
        return "row-capacity-exceeded";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_MISSING_SOURCE:
        return "missing-source";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_MALFORMED_SOURCE:
        return "malformed-source";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STALE_SOURCE:
        return "stale-source";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_GRANT_AUTHORITY:
        return "source-would-grant-authority";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_PERFORM_EFFECT:
        return "source-would-perform-effect";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_TOUCH_HOST:
        return "source-would-touch-host";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_USE_NETWORK:
        return "source-would-use-network";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_BUFFER_TOO_SMALL:
        return "buffer-too-small";
    default:
        return "unknown";
    }
}

const char *latticra_seal_panel_dashboard_view_model_category_label(
    latticra_seal_panel_dashboard_view_model_category_t category) {
    switch (category) {
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_MODE:
        return "mode";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_EVIDENCE:
        return "evidence";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_DECISION:
        return "decision";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_AUTHORITY:
        return "authority";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_SOURCE:
        return "source";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_NEXT_STEP:
        return "next-step";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_INVALID:
    default:
        return "invalid";
    }
}

const char *latticra_seal_panel_dashboard_view_model_state_label(
    latticra_seal_panel_dashboard_view_model_state_t state) {
    switch (state) {
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_PRESENT:
        return "present";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_MISSING:
        return "missing";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_MALFORMED:
        return "malformed";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_STALE:
        return "stale";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_BLOCKED:
        return "blocked";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_PLANNED:
        return "planned";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_INVALID:
    default:
        return "invalid";
    }
}

const char *latticra_seal_panel_dashboard_view_model_decision_label(
    latticra_seal_panel_dashboard_view_model_decision_t decision) {
    switch (decision) {
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_DENY:
        return "deny";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_REVIEW:
        return "review";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_UNKNOWN:
        return "unknown";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_NOT_APPLICABLE:
        return "not-applicable";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_INVALID:
    default:
        return "invalid";
    }
}

const char *latticra_seal_panel_dashboard_view_model_severity_label(
    latticra_seal_panel_dashboard_view_model_severity_t severity) {
    switch (severity) {
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SEVERITY_INFO:
        return "info";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SEVERITY_WARNING:
        return "warning";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SEVERITY_BLOCKED:
        return "blocked";
    case LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SEVERITY_INVALID:
    default:
        return "invalid";
    }
}

static int category_valid(latticra_seal_panel_dashboard_view_model_category_t category) {
    return category == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_MODE ||
           category == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_EVIDENCE ||
           category == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_DECISION ||
           category == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_AUTHORITY ||
           category == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_SOURCE ||
           category == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_NEXT_STEP;
}

static int state_valid(latticra_seal_panel_dashboard_view_model_state_t state) {
    return state == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_PRESENT ||
           state == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_MISSING ||
           state == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_MALFORMED ||
           state == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_STALE ||
           state == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_BLOCKED ||
           state == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_PLANNED;
}

static int decision_valid(latticra_seal_panel_dashboard_view_model_decision_t decision) {
    return decision == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_DENY ||
           decision == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_REVIEW ||
           decision == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_UNKNOWN ||
           decision == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_NOT_APPLICABLE;
}

static int severity_valid(latticra_seal_panel_dashboard_view_model_severity_t severity) {
    return severity == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SEVERITY_INFO ||
           severity == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SEVERITY_WARNING ||
           severity == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SEVERITY_BLOCKED;
}

static void mark_error(latticra_seal_panel_dashboard_view_model_t *model,
                       latticra_seal_panel_dashboard_view_model_error_t error) {
    if (model != NULL) {
        model->last_error = error;
    }
}

latticra_status_t latticra_seal_panel_dashboard_view_model_init(
    latticra_seal_panel_dashboard_view_model_t *out) {
    if (out == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    memset(out, 0, sizeof(*out));
    copy_literal(out->seal_panel_dashboard_view_model_profile,
                 sizeof(out->seal_panel_dashboard_view_model_profile),
                 "latticra-seal-panel-dashboard-view-model/0.1");
    copy_literal(out->seal_panel_dashboard_view_model_mode,
                 sizeof(out->seal_panel_dashboard_view_model_mode),
                 "report-only");
    copy_literal(out->seal_panel_dashboard_view_model_status,
                 sizeof(out->seal_panel_dashboard_view_model_status),
                 "planned-no-effect");
    out->seal_panel_dashboard_view_model_contract_present = 1u;
    out->seal_panel_dashboard_view_model_implementation_plan_present = 1u;
    out->view_model_entry_count = 0u;
    out->view_model_entry_count_max = LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_ROW_MAX;
    out->view_model_source_count = 0u;
    out->view_model_source_count_max = LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_MAX;
    out->view_model_row_id_max = LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_ROW_ID_MAX;
    out->view_model_label_max = LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_ROW_LABEL_MAX;
    out->view_model_summary_max = LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SUMMARY_MAX;
    out->view_model_blocked_reason_max =
        LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_BLOCKED_REASON_MAX;
    out->view_model_next_action_max =
        LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_NEXT_ACTION_MAX;
    copy_literal(out->input_contract_mode,
                 sizeof(out->input_contract_mode),
                 "caller-provided-report-strings");
    out->caller_provided_report_strings_only = 1u;
    out->missing_source_row_visible = 1u;
    out->malformed_source_row_visible = 1u;
    out->stale_source_row_visible = 1u;
    copy_literal(out->missing_source_default_decision,
                 sizeof(out->missing_source_default_decision),
                 "review");
    copy_literal(out->malformed_source_default_decision,
                 sizeof(out->malformed_source_default_decision),
                 "deny");
    copy_literal(out->stale_source_default_decision,
                 sizeof(out->stale_source_default_decision),
                 "deny");
    copy_literal(out->unknown_source_default_decision,
                 sizeof(out->unknown_source_default_decision),
                 "deny");
    out->operator_review_required_for_any_missing_source = 1u;
    out->authority_absent_for_all_rows = 1u;
    out->auto_discover_reports = 0u;
    out->auto_scan_host_paths = 0u;
    out->report_file_loading_implemented = 0u;
    out->panel_ui_implemented = 0u;
    out->dashboard_view_model_implemented = 1u;
    out->runtime_authority_granted = 0u;
    out->effect_performed = 0u;
    out->host_read_performed = 0u;
    out->host_write_performed = 0u;
    out->network_performed = 0u;
    out->last_error = LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_OK;
    return LATTICRA_STATUS_OK;
}

static int report_mentions_report_only(const char *report) {
    return text_contains(report, "report_only=1") ||
           text_contains(report, "_report_only=1") ||
           text_contains(report, "mode=report-only") ||
           text_contains(report, "receipt_mode=report-only") ||
           text_contains(report, "registry_mode=report-only") ||
           text_contains(report, "seal_panel_dashboard_view_model_mode=report-only") ||
           text_contains(report, "report-only");
}

static int report_mentions_malformed(const char *report) {
    return text_contains(report, "source_report_malformed=1") ||
           text_contains(report, "malformed_source=1") ||
           text_contains(report, "malformed_report=1");
}

static int report_mentions_stale(const char *report) {
    return text_contains(report, "source_report_stale=1") ||
           text_contains(report, "stale_source=1") ||
           text_contains(report, "stale_report=1");
}

static int report_mentions_authority(const char *report) {
    return text_contains(report, "runtime_authority_granted=1") ||
           text_contains(report, "grants_runtime_authority=1") ||
           text_contains(report, "would_grant_runtime_authority=1") ||
           text_contains(report, "capability_grants_authority=1");
}

static int report_mentions_effect(const char *report) {
    return text_contains(report, "effect_performed=1") ||
           text_contains(report, "can_execute_tool=1") ||
           text_contains(report, "capability_executes_tool=1") ||
           text_contains(report, "would_execute_tool=1") ||
           text_contains(report, "tool_execution_enabled=1");
}

static int report_mentions_host_touch(const char *report) {
    return text_contains(report, "host_read_performed=1") ||
           text_contains(report, "host_write_performed=1") ||
           text_contains(report, "can_read_host=1") ||
           text_contains(report, "can_write_host=1") ||
           text_contains(report, "capability_reads_host=1") ||
           text_contains(report, "capability_writes_host=1") ||
           text_contains(report, "would_read_host=1") ||
           text_contains(report, "would_write_host=1");
}

static int report_mentions_network(const char *report) {
    return text_contains(report, "network_performed=1") ||
           text_contains(report, "can_use_network=1") ||
           text_contains(report, "capability_uses_network=1") ||
           text_contains(report, "would_use_network=1") ||
           text_contains(report, "network_lookup_enabled=1");
}

latticra_status_t latticra_seal_panel_dashboard_view_model_add_source_report(
    latticra_seal_panel_dashboard_view_model_t *model,
    const char *source_id,
    const char *source_label,
    const char *source_report_text) {
    latticra_seal_panel_dashboard_view_model_source_t source;
    int terminated = 0;

    if (model == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (!text_field_valid(source_id, LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_ID_MAX) ||
        !text_field_valid(source_label,
                          LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_LABEL_MAX) ||
        !text_field_valid(source_report_text,
                          LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_REPORT_MAX)) {
        mark_error(model, LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_INPUT);
        return LATTICRA_STATUS_OK;
    }
    (void)bounded_string_len(source_report_text,
                             LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_REPORT_MAX,
                             &terminated);
    if (terminated != 1) {
        mark_error(model, LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_INPUT);
        return LATTICRA_STATUS_OK;
    }
    if (model->view_model_source_count >= LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_MAX ||
        model->view_model_source_count >= model->view_model_source_count_max) {
        mark_error(model, LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_CAPACITY_EXCEEDED);
        return LATTICRA_STATUS_OK;
    }
    if (report_mentions_authority(source_report_text)) {
        mark_error(model,
                   LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_GRANT_AUTHORITY);
        return LATTICRA_STATUS_OK;
    }
    if (report_mentions_effect(source_report_text)) {
        mark_error(model,
                   LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_PERFORM_EFFECT);
        return LATTICRA_STATUS_OK;
    }
    if (report_mentions_host_touch(source_report_text)) {
        mark_error(model, LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_TOUCH_HOST);
        return LATTICRA_STATUS_OK;
    }
    if (report_mentions_network(source_report_text)) {
        mark_error(model, LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_USE_NETWORK);
        return LATTICRA_STATUS_OK;
    }

    memset(&source, 0, sizeof(source));
    copy_literal(source.source_id, sizeof(source.source_id), source_id);
    copy_literal(source.source_label, sizeof(source.source_label), source_label);
    source.source_report_present = 1u;
    source.source_report_text_present = 1u;
    source.source_report_malformed = report_mentions_malformed(source_report_text) ? 1u : 0u;
    source.source_report_stale = report_mentions_stale(source_report_text) ? 1u : 0u;
    source.source_report_only = report_mentions_report_only(source_report_text) ? 1u : 0u;
    source.source_required = 1u;
    source.source_runtime_authority_granted = 0u;
    source.source_effect_performed = 0u;
    source.source_host_read_performed = 0u;
    source.source_host_write_performed = 0u;
    source.source_network_performed = 0u;
    if (source.source_report_only != 1u) {
        source.source_report_malformed = 1u;
        copy_literal(source.source_blocked_reason,
                     sizeof(source.source_blocked_reason),
                     "source-report-not-report-only");
    } else if (source.source_report_malformed == 1u) {
        copy_literal(source.source_blocked_reason,
                     sizeof(source.source_blocked_reason),
                     "malformed-source-denied");
    } else if (source.source_report_stale == 1u) {
        copy_literal(source.source_blocked_reason,
                     sizeof(source.source_blocked_reason),
                     "stale-source-denied");
    } else {
        copy_literal(source.source_blocked_reason,
                     sizeof(source.source_blocked_reason),
                     "report-only-source-denied-by-default");
    }

    model->sources[model->view_model_source_count] = source;
    model->view_model_source_count += 1u;
    mark_error(model, LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_OK);
    return LATTICRA_STATUS_OK;
}

static const latticra_seal_panel_dashboard_view_model_source_t *find_source(
    const latticra_seal_panel_dashboard_view_model_t *model,
    const char *source_id) {
    unsigned i;

    if (model == NULL || source_id == NULL) {
        return NULL;
    }
    for (i = 0u; i < model->view_model_source_count; ++i) {
        if (string_is(model->sources[i].source_id, source_id)) {
            return &model->sources[i];
        }
    }
    return NULL;
}

static void fill_row_from_source(
    latticra_seal_panel_dashboard_view_model_row_t *row,
    const required_row_spec_t *spec,
    const latticra_seal_panel_dashboard_view_model_source_t *source) {
    memset(row, 0, sizeof(*row));
    copy_literal(row->row_id, sizeof(row->row_id), spec->row_id);
    copy_literal(row->row_label, sizeof(row->row_label), spec->row_label);
    row->row_category = spec->category;
    copy_literal(row->row_source, sizeof(row->row_source), spec->row_id);
    row->denied_by_default = 1u;
    row->requires_operator_review = 1u;
    row->authority_absent = 1u;
    row->can_execute_tool = 0u;
    row->can_read_host = 0u;
    row->can_write_host = 0u;
    row->can_use_network = 0u;
    row->grants_runtime_authority = 0u;
    row->effect_performed = 0u;

    if (source == NULL) {
        row->row_state = LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_MISSING;
        row->row_decision = LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_REVIEW;
        row->row_severity = LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SEVERITY_WARNING;
        copy_literal(row->row_summary,
                     sizeof(row->row_summary),
                     "Source evidence is missing and remains review-only.");
        copy_literal(row->row_blocked_reason,
                     sizeof(row->row_blocked_reason),
                     "source-missing-no-authority");
        copy_literal(row->row_next_action,
                     sizeof(row->row_next_action),
                     "provide caller-supplied report string before review");
        row->evidence_present = 0u;
        row->source_missing = 1u;
        return;
    }

    row->evidence_present = 1u;
    if (source->source_report_malformed == 1u) {
        row->row_state = LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_MALFORMED;
        row->row_decision = LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_DENY;
        row->row_severity = LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SEVERITY_BLOCKED;
        copy_literal(row->row_summary,
                     sizeof(row->row_summary),
                     "Malformed source evidence remains visible and denied.");
        copy_literal(row->row_blocked_reason,
                     sizeof(row->row_blocked_reason),
                     source->source_blocked_reason);
        copy_literal(row->row_next_action,
                     sizeof(row->row_next_action),
                     "repair caller-supplied report string before review");
        row->source_malformed = 1u;
        return;
    }
    if (source->source_report_stale == 1u) {
        row->row_state = LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_STALE;
        row->row_decision = LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_DENY;
        row->row_severity = LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SEVERITY_BLOCKED;
        copy_literal(row->row_summary,
                     sizeof(row->row_summary),
                     "Stale source evidence remains visible and denied.");
        copy_literal(row->row_blocked_reason,
                     sizeof(row->row_blocked_reason),
                     source->source_blocked_reason);
        copy_literal(row->row_next_action,
                     sizeof(row->row_next_action),
                     "refresh caller-supplied report string before review");
        row->source_stale = 1u;
        return;
    }

    row->row_state = LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_PRESENT;
    row->row_decision = LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_DENY;
    row->row_severity = LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SEVERITY_INFO;
    copy_literal(row->row_summary, sizeof(row->row_summary), spec->present_summary);
    copy_literal(row->row_blocked_reason,
                 sizeof(row->row_blocked_reason),
                 source->source_blocked_reason);
    copy_literal(row->row_next_action,
                 sizeof(row->row_next_action),
                 "keep in operator review until signed authority exists");
}

latticra_status_t latticra_seal_panel_dashboard_view_model_add_required_rows(
    latticra_seal_panel_dashboard_view_model_t *model) {
    size_t i;

    if (model == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (model->view_model_entry_count + (unsigned)(sizeof(required_rows) / sizeof(required_rows[0])) >
            LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_ROW_MAX ||
        model->view_model_entry_count + (unsigned)(sizeof(required_rows) / sizeof(required_rows[0])) >
            model->view_model_entry_count_max) {
        mark_error(model, LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_ROW_CAPACITY_EXCEEDED);
        return LATTICRA_STATUS_OK;
    }

    for (i = 0u; i < sizeof(required_rows) / sizeof(required_rows[0]); ++i) {
        const latticra_seal_panel_dashboard_view_model_source_t *source =
            find_source(model, required_rows[i].row_id);
        fill_row_from_source(&model->rows[model->view_model_entry_count],
                             &required_rows[i],
                             source);
        model->view_model_entry_count += 1u;
    }
    mark_error(model, LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_OK);
    return LATTICRA_STATUS_OK;
}

static latticra_seal_panel_dashboard_view_model_error_t source_error(
    const latticra_seal_panel_dashboard_view_model_source_t *source) {
    if (source == NULL ||
        !text_field_valid(source->source_id,
                          LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_ID_MAX) ||
        !text_field_valid(source->source_label,
                          LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_LABEL_MAX) ||
        !text_field_valid(source->source_blocked_reason,
                          LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_BLOCKED_REASON_MAX) ||
        source->source_report_present != 1u ||
        source->source_report_text_present != 1u ||
        source->source_required != 1u) {
        return LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_INPUT;
    }
    if (source->source_runtime_authority_granted != 0u) {
        return LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_GRANT_AUTHORITY;
    }
    if (source->source_effect_performed != 0u) {
        return LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_PERFORM_EFFECT;
    }
    if (source->source_host_read_performed != 0u ||
        source->source_host_write_performed != 0u) {
        return LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_TOUCH_HOST;
    }
    if (source->source_network_performed != 0u) {
        return LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_USE_NETWORK;
    }
    return LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_OK;
}

static latticra_seal_panel_dashboard_view_model_error_t row_error(
    const latticra_seal_panel_dashboard_view_model_row_t *row) {
    if (row == NULL ||
        !text_field_valid(row->row_id, LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_ROW_ID_MAX) ||
        !text_field_valid(row->row_label,
                          LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_ROW_LABEL_MAX) ||
        !text_field_valid(row->row_source,
                          LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_ID_MAX) ||
        !text_field_valid(row->row_summary,
                          LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SUMMARY_MAX) ||
        !text_field_valid(row->row_blocked_reason,
                          LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_BLOCKED_REASON_MAX) ||
        !text_field_valid(row->row_next_action,
                          LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_NEXT_ACTION_MAX)) {
        return LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_INPUT;
    }
    if (!category_valid(row->row_category)) {
        return LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_CATEGORY;
    }
    if (!state_valid(row->row_state)) {
        return LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_STATE;
    }
    if (!decision_valid(row->row_decision)) {
        return LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_DECISION;
    }
    if (!severity_valid(row->row_severity)) {
        return LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_SEVERITY;
    }
    if (row->can_execute_tool != 0u || row->effect_performed != 0u) {
        return LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_PERFORM_EFFECT;
    }
    if (row->can_read_host != 0u || row->can_write_host != 0u) {
        return LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_TOUCH_HOST;
    }
    if (row->can_use_network != 0u) {
        return LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_USE_NETWORK;
    }
    if (row->grants_runtime_authority != 0u || row->authority_absent != 1u) {
        return LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_GRANT_AUTHORITY;
    }
    if (row->denied_by_default != 1u || row->requires_operator_review != 1u) {
        return LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_DECISION;
    }
    if (row->source_missing == 1u &&
        (row->row_state != LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_MISSING ||
         row->row_decision != LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_REVIEW)) {
        return LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_MISSING_SOURCE;
    }
    if (row->source_malformed == 1u &&
        (row->row_state != LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_MALFORMED ||
         row->row_decision != LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_DENY)) {
        return LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_MALFORMED_SOURCE;
    }
    if (row->source_stale == 1u &&
        (row->row_state != LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_STALE ||
         row->row_decision != LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_DENY)) {
        return LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STALE_SOURCE;
    }
    return LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_OK;
}

latticra_status_t latticra_seal_panel_dashboard_view_model_validate(
    latticra_seal_panel_dashboard_view_model_t *model) {
    unsigned i;

    if (model == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }

    if (!string_is(model->seal_panel_dashboard_view_model_profile,
                   "latticra-seal-panel-dashboard-view-model/0.1")) {
        mark_error(model, LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_PROFILE);
        return LATTICRA_STATUS_OK;
    }
    if (!string_is(model->seal_panel_dashboard_view_model_mode, "report-only") ||
        !string_is(model->seal_panel_dashboard_view_model_status, "planned-no-effect") ||
        !string_is(model->input_contract_mode, "caller-provided-report-strings") ||
        model->seal_panel_dashboard_view_model_contract_present != 1u ||
        model->seal_panel_dashboard_view_model_implementation_plan_present != 1u ||
        model->caller_provided_report_strings_only != 1u ||
        model->missing_source_row_visible != 1u ||
        model->malformed_source_row_visible != 1u ||
        model->stale_source_row_visible != 1u ||
        !string_is(model->missing_source_default_decision, "review") ||
        !string_is(model->malformed_source_default_decision, "deny") ||
        !string_is(model->stale_source_default_decision, "deny") ||
        !string_is(model->unknown_source_default_decision, "deny") ||
        model->operator_review_required_for_any_missing_source != 1u ||
        model->authority_absent_for_all_rows != 1u ||
        model->auto_discover_reports != 0u ||
        model->auto_scan_host_paths != 0u ||
        model->report_file_loading_implemented != 0u ||
        model->panel_ui_implemented != 0u ||
        model->dashboard_view_model_implemented != 1u) {
        mark_error(model, LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_INPUT);
        return LATTICRA_STATUS_OK;
    }
    if (model->runtime_authority_granted != 0u) {
        mark_error(model,
                   LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_GRANT_AUTHORITY);
        return LATTICRA_STATUS_OK;
    }
    if (model->effect_performed != 0u) {
        mark_error(model,
                   LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_PERFORM_EFFECT);
        return LATTICRA_STATUS_OK;
    }
    if (model->host_read_performed != 0u || model->host_write_performed != 0u) {
        mark_error(model, LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_TOUCH_HOST);
        return LATTICRA_STATUS_OK;
    }
    if (model->network_performed != 0u) {
        mark_error(model, LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_USE_NETWORK);
        return LATTICRA_STATUS_OK;
    }
    if (model->view_model_source_count > LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_MAX ||
        model->view_model_source_count > model->view_model_source_count_max) {
        mark_error(model, LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_CAPACITY_EXCEEDED);
        return LATTICRA_STATUS_OK;
    }
    if (model->view_model_entry_count > LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_ROW_MAX ||
        model->view_model_entry_count > model->view_model_entry_count_max) {
        mark_error(model, LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_ROW_CAPACITY_EXCEEDED);
        return LATTICRA_STATUS_OK;
    }

    for (i = 0u; i < model->view_model_source_count; ++i) {
        latticra_seal_panel_dashboard_view_model_error_t error = source_error(&model->sources[i]);
        if (error != LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_OK) {
            mark_error(model, error);
            return LATTICRA_STATUS_OK;
        }
    }
    for (i = 0u; i < model->view_model_entry_count; ++i) {
        latticra_seal_panel_dashboard_view_model_error_t error = row_error(&model->rows[i]);
        if (error != LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_OK) {
            mark_error(model, error);
            return LATTICRA_STATUS_OK;
        }
    }

    mark_error(model, LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_OK);
    return LATTICRA_STATUS_OK;
}

int latticra_seal_panel_dashboard_view_model_is_report_only(
    const latticra_seal_panel_dashboard_view_model_t *model) {
    unsigned i;

    if (model == NULL ||
        !string_is(model->seal_panel_dashboard_view_model_profile,
                   "latticra-seal-panel-dashboard-view-model/0.1") ||
        !string_is(model->seal_panel_dashboard_view_model_mode, "report-only") ||
        !string_is(model->seal_panel_dashboard_view_model_status, "planned-no-effect") ||
        !string_is(model->input_contract_mode, "caller-provided-report-strings") ||
        model->seal_panel_dashboard_view_model_contract_present != 1u ||
        model->seal_panel_dashboard_view_model_implementation_plan_present != 1u ||
        model->caller_provided_report_strings_only != 1u ||
        model->missing_source_row_visible != 1u ||
        model->malformed_source_row_visible != 1u ||
        model->stale_source_row_visible != 1u ||
        model->operator_review_required_for_any_missing_source != 1u ||
        model->authority_absent_for_all_rows != 1u ||
        model->auto_discover_reports != 0u ||
        model->auto_scan_host_paths != 0u ||
        model->report_file_loading_implemented != 0u ||
        model->panel_ui_implemented != 0u ||
        model->dashboard_view_model_implemented != 1u ||
        model->runtime_authority_granted != 0u ||
        model->effect_performed != 0u ||
        model->host_read_performed != 0u ||
        model->host_write_performed != 0u ||
        model->network_performed != 0u ||
        model->view_model_source_count > LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_MAX ||
        model->view_model_entry_count > LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_ROW_MAX ||
        model->last_error != LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_OK) {
        return 0;
    }

    for (i = 0u; i < model->view_model_source_count; ++i) {
        if (source_error(&model->sources[i]) != LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_OK) {
            return 0;
        }
    }
    for (i = 0u; i < model->view_model_entry_count; ++i) {
        if (row_error(&model->rows[i]) != LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_OK) {
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

latticra_status_t latticra_seal_panel_dashboard_view_model_render(
    const latticra_seal_panel_dashboard_view_model_t *model,
    char *buffer,
    size_t buffer_len) {
    size_t offset = 0u;
    unsigned i;

    if (model == NULL || buffer == NULL) {
        return LATTICRA_STATUS_NULL_ARGUMENT;
    }
    if (buffer_len == 0u) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    if (!append_format(buffer,
                       buffer_len,
                       &offset,
                       "LATTICRA SEAL PANEL DASHBOARD VIEW MODEL REPORT\n"
                       "seal_panel_dashboard_view_model_profile=%s\n"
                       "seal_panel_dashboard_view_model_mode=%s\n"
                       "seal_panel_dashboard_view_model_status=%s\n"
                       "seal_panel_dashboard_view_model_contract_present=%u\n"
                       "seal_panel_dashboard_view_model_implementation_plan_present=%u\n"
                       "view_model_entry_count=%u\n"
                       "view_model_entry_count_max=%u\n"
                       "view_model_source_count=%u\n"
                       "view_model_source_count_max=%u\n"
                       "input_contract_mode=%s\n"
                       "missing_source_row_visible=%u\n"
                       "malformed_source_row_visible=%u\n"
                       "stale_source_row_visible=%u\n"
                       "missing_source_default_decision=%s\n"
                       "malformed_source_default_decision=%s\n"
                       "stale_source_default_decision=%s\n"
                       "unknown_source_default_decision=%s\n"
                       "operator_review_required_for_any_missing_source=%u\n"
                       "authority_absent_for_all_rows=%u\n"
                       "panel_ui_implemented=%u\n"
                       "dashboard_view_model_implemented=%u\n"
                       "report_file_loading_implemented=%u\n"
                       "auto_discover_reports=%u\n"
                       "auto_scan_host_paths=%u\n"
                       "runtime_authority_granted=%u\n"
                       "effect_performed=%u\n"
                       "host_read_performed=%u\n"
                       "host_write_performed=%u\n"
                       "network_performed=%u\n",
                       model->seal_panel_dashboard_view_model_profile,
                       model->seal_panel_dashboard_view_model_mode,
                       model->seal_panel_dashboard_view_model_status,
                       model->seal_panel_dashboard_view_model_contract_present,
                       model->seal_panel_dashboard_view_model_implementation_plan_present,
                       model->view_model_entry_count,
                       model->view_model_entry_count_max,
                       model->view_model_source_count,
                       model->view_model_source_count_max,
                       model->input_contract_mode,
                       model->missing_source_row_visible,
                       model->malformed_source_row_visible,
                       model->stale_source_row_visible,
                       model->missing_source_default_decision,
                       model->malformed_source_default_decision,
                       model->stale_source_default_decision,
                       model->unknown_source_default_decision,
                       model->operator_review_required_for_any_missing_source,
                       model->authority_absent_for_all_rows,
                       model->panel_ui_implemented,
                       model->dashboard_view_model_implemented,
                       model->report_file_loading_implemented,
                       model->auto_discover_reports,
                       model->auto_scan_host_paths,
                       model->runtime_authority_granted,
                       model->effect_performed,
                       model->host_read_performed,
                       model->host_write_performed,
                       model->network_performed)) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    for (i = 0u; i < model->view_model_entry_count; ++i) {
        const latticra_seal_panel_dashboard_view_model_row_t *row = &model->rows[i];
        if (!append_format(buffer,
                           buffer_len,
                           &offset,
                           "row_id=%s\n"
                           "row_label=%s\n"
                           "row_category=%s\n"
                           "row_source=%s\n"
                           "row_state=%s\n"
                           "row_decision=%s\n"
                           "row_severity=%s\n"
                           "row_summary=%s\n"
                           "row_blocked_reason=%s\n"
                           "row_next_action=%s\n"
                           "evidence_present=%u\n"
                           "source_missing=%u\n"
                           "source_malformed=%u\n"
                           "source_stale=%u\n"
                           "denied_by_default=%u\n"
                           "requires_operator_review=%u\n"
                           "authority_absent=%u\n"
                           "can_execute_tool=%u\n"
                           "can_read_host=%u\n"
                           "can_write_host=%u\n"
                           "can_use_network=%u\n"
                           "grants_runtime_authority=%u\n"
                           "effect_performed=%u\n",
                           row->row_id,
                           row->row_label,
                           latticra_seal_panel_dashboard_view_model_category_label(
                               row->row_category),
                           row->row_source,
                           latticra_seal_panel_dashboard_view_model_state_label(row->row_state),
                           latticra_seal_panel_dashboard_view_model_decision_label(
                               row->row_decision),
                           latticra_seal_panel_dashboard_view_model_severity_label(
                               row->row_severity),
                           row->row_summary,
                           row->row_blocked_reason,
                           row->row_next_action,
                           row->evidence_present,
                           row->source_missing,
                           row->source_malformed,
                           row->source_stale,
                           row->denied_by_default,
                           row->requires_operator_review,
                           row->authority_absent,
                           row->can_execute_tool,
                           row->can_read_host,
                           row->can_write_host,
                           row->can_use_network,
                           row->grants_runtime_authority,
                           row->effect_performed)) {
            return LATTICRA_STATUS_BUFFER_TOO_SMALL;
        }
    }

    if (!append_format(buffer,
                       buffer_len,
                       &offset,
                       "error=%s\n",
                       latticra_seal_panel_dashboard_view_model_error_label(
                           model->last_error))) {
        return LATTICRA_STATUS_BUFFER_TOO_SMALL;
    }

    return LATTICRA_STATUS_OK;
}
