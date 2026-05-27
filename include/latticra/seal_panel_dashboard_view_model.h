#ifndef LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_H
#define LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_H

#include "latticra/state_lattice.h"

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_PROFILE_MAX 64u
#define LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_MODE_MAX 32u
#define LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATUS_MAX 32u
#define LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INPUT_MODE_MAX 64u
#define LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_MAX 16u
#define LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_ID_MAX 64u
#define LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_LABEL_MAX 96u
#define LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_ROW_MAX 16u
#define LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_ROW_ID_MAX 64u
#define LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_ROW_LABEL_MAX 96u
#define LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_MAX 32u
#define LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_MAX 32u
#define LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_MAX 32u
#define LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SEVERITY_MAX 32u
#define LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SUMMARY_MAX 192u
#define LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_BLOCKED_REASON_MAX 160u
#define LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_NEXT_ACTION_MAX 160u
#define LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_REPORT_MAX 8192u
#define LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_REPORT_MAX 16384u

typedef enum {
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_OK = 0,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_INPUT = 1,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_PROFILE = 2,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_SOURCE_ID = 3,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_ROW_ID = 4,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_CATEGORY = 5,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_STATE = 6,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_DECISION = 7,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_SEVERITY = 8,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_CAPACITY_EXCEEDED = 9,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_ROW_CAPACITY_EXCEEDED = 10,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_MISSING_SOURCE = 11,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_MALFORMED_SOURCE = 12,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STALE_SOURCE = 13,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_GRANT_AUTHORITY = 14,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_PERFORM_EFFECT = 15,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_TOUCH_HOST = 16,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_USE_NETWORK = 17,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_BUFFER_TOO_SMALL = 18
} latticra_seal_panel_dashboard_view_model_error_t;

typedef enum {
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_INVALID = 0,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_MODE = 1,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_EVIDENCE = 2,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_DECISION = 3,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_AUTHORITY = 4,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_SOURCE = 5,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CATEGORY_NEXT_STEP = 6
} latticra_seal_panel_dashboard_view_model_category_t;

typedef enum {
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_INVALID = 0,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_PRESENT = 1,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_MISSING = 2,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_MALFORMED = 3,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_STALE = 4,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_BLOCKED = 5,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_PLANNED = 6
} latticra_seal_panel_dashboard_view_model_state_t;

typedef enum {
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_INVALID = 0,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_DENY = 1,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_REVIEW = 2,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_UNKNOWN = 3,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_NOT_APPLICABLE = 4
} latticra_seal_panel_dashboard_view_model_decision_t;

typedef enum {
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SEVERITY_INVALID = 0,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SEVERITY_INFO = 1,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SEVERITY_WARNING = 2,
    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SEVERITY_BLOCKED = 3
} latticra_seal_panel_dashboard_view_model_severity_t;

typedef struct {
    char source_id[LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_ID_MAX];
    char source_label[LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_LABEL_MAX];
    unsigned source_report_present;
    unsigned source_report_text_present;
    unsigned source_report_malformed;
    unsigned source_report_stale;
    unsigned source_report_only;
    unsigned source_required;
    unsigned source_runtime_authority_granted;
    unsigned source_effect_performed;
    unsigned source_host_read_performed;
    unsigned source_host_write_performed;
    unsigned source_network_performed;
    char source_blocked_reason[LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_BLOCKED_REASON_MAX];
} latticra_seal_panel_dashboard_view_model_source_t;

typedef struct {
    char row_id[LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_ROW_ID_MAX];
    char row_label[LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_ROW_LABEL_MAX];
    latticra_seal_panel_dashboard_view_model_category_t row_category;
    char row_source[LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_ID_MAX];
    latticra_seal_panel_dashboard_view_model_state_t row_state;
    latticra_seal_panel_dashboard_view_model_decision_t row_decision;
    latticra_seal_panel_dashboard_view_model_severity_t row_severity;
    char row_summary[LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SUMMARY_MAX];
    char row_blocked_reason[LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_BLOCKED_REASON_MAX];
    char row_next_action[LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_NEXT_ACTION_MAX];
    unsigned evidence_present;
    unsigned source_missing;
    unsigned source_malformed;
    unsigned source_stale;
    unsigned denied_by_default;
    unsigned requires_operator_review;
    unsigned authority_absent;
    unsigned can_execute_tool;
    unsigned can_read_host;
    unsigned can_write_host;
    unsigned can_use_network;
    unsigned grants_runtime_authority;
    unsigned effect_performed;
} latticra_seal_panel_dashboard_view_model_row_t;

typedef struct {
    char seal_panel_dashboard_view_model_profile
        [LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_PROFILE_MAX];
    char seal_panel_dashboard_view_model_mode
        [LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_MODE_MAX];
    char seal_panel_dashboard_view_model_status
        [LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATUS_MAX];
    unsigned seal_panel_dashboard_view_model_contract_present;
    unsigned seal_panel_dashboard_view_model_implementation_plan_present;
    unsigned view_model_entry_count;
    unsigned view_model_entry_count_max;
    unsigned view_model_source_count;
    unsigned view_model_source_count_max;
    unsigned view_model_row_id_max;
    unsigned view_model_label_max;
    unsigned view_model_summary_max;
    unsigned view_model_blocked_reason_max;
    unsigned view_model_next_action_max;
    char input_contract_mode[LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INPUT_MODE_MAX];
    unsigned caller_provided_report_strings_only;
    unsigned missing_source_row_visible;
    unsigned malformed_source_row_visible;
    unsigned stale_source_row_visible;
    char missing_source_default_decision
        [LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_MAX];
    char malformed_source_default_decision
        [LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_MAX];
    char stale_source_default_decision
        [LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_MAX];
    char unknown_source_default_decision
        [LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_MAX];
    unsigned operator_review_required_for_any_missing_source;
    unsigned authority_absent_for_all_rows;
    unsigned auto_discover_reports;
    unsigned auto_scan_host_paths;
    unsigned report_file_loading_implemented;
    unsigned panel_ui_implemented;
    unsigned dashboard_view_model_implemented;
    unsigned runtime_authority_granted;
    unsigned effect_performed;
    unsigned host_read_performed;
    unsigned host_write_performed;
    unsigned network_performed;
    latticra_seal_panel_dashboard_view_model_error_t last_error;
    latticra_seal_panel_dashboard_view_model_source_t
        sources[LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_MAX];
    latticra_seal_panel_dashboard_view_model_row_t
        rows[LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_ROW_MAX];
} latticra_seal_panel_dashboard_view_model_t;

const char *latticra_seal_panel_dashboard_view_model_error_label(
    latticra_seal_panel_dashboard_view_model_error_t error);
const char *latticra_seal_panel_dashboard_view_model_category_label(
    latticra_seal_panel_dashboard_view_model_category_t category);
const char *latticra_seal_panel_dashboard_view_model_state_label(
    latticra_seal_panel_dashboard_view_model_state_t state);
const char *latticra_seal_panel_dashboard_view_model_decision_label(
    latticra_seal_panel_dashboard_view_model_decision_t decision);
const char *latticra_seal_panel_dashboard_view_model_severity_label(
    latticra_seal_panel_dashboard_view_model_severity_t severity);
latticra_status_t latticra_seal_panel_dashboard_view_model_init(
    latticra_seal_panel_dashboard_view_model_t *out);
latticra_status_t latticra_seal_panel_dashboard_view_model_add_source_report(
    latticra_seal_panel_dashboard_view_model_t *model,
    const char *source_id,
    const char *source_label,
    const char *source_report_text);
latticra_status_t latticra_seal_panel_dashboard_view_model_add_required_rows(
    latticra_seal_panel_dashboard_view_model_t *model);
latticra_status_t latticra_seal_panel_dashboard_view_model_validate(
    latticra_seal_panel_dashboard_view_model_t *model);
int latticra_seal_panel_dashboard_view_model_is_report_only(
    const latticra_seal_panel_dashboard_view_model_t *model);
latticra_status_t latticra_seal_panel_dashboard_view_model_render(
    const latticra_seal_panel_dashboard_view_model_t *model,
    char *buffer,
    size_t buffer_len);

#ifdef __cplusplus
}
#endif

#endif
