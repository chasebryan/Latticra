#include "latticra/seal_panel_dashboard_view_model.h"

#include <stdio.h>
#include <string.h>

#define EXPECT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            fprintf(stderr, "FAIL: %s\n", message); \
            return 1; \
        } \
    } while (0)

static const char *report_only_fixture(void) {
    return "fixture_profile=latticra-seal-panel-source/0.1\n"
           "mode=report-only\n"
           "report_only=1\n"
           "runtime_authority_granted=0\n"
           "effect_performed=0\n"
           "host_read_performed=0\n"
           "host_write_performed=0\n"
           "network_performed=0\n";
}

static int initialized_model_is_no_effect(void) {
    latticra_seal_panel_dashboard_view_model_t model;

    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_init(&model) == LATTICRA_STATUS_OK,
                "init");
    EXPECT_TRUE(strcmp(model.seal_panel_dashboard_view_model_profile,
                       "latticra-seal-panel-dashboard-view-model/0.1") == 0,
                "profile");
    EXPECT_TRUE(strcmp(model.seal_panel_dashboard_view_model_mode, "report-only") == 0,
                "mode");
    EXPECT_TRUE(strcmp(model.seal_panel_dashboard_view_model_status, "planned-no-effect") == 0,
                "status");
    EXPECT_TRUE(model.seal_panel_dashboard_view_model_contract_present == 1u, "contract");
    EXPECT_TRUE(model.seal_panel_dashboard_view_model_implementation_plan_present == 1u,
                "plan");
    EXPECT_TRUE(model.view_model_entry_count == 0u, "entry count");
    EXPECT_TRUE(model.view_model_entry_count_max == 16u, "entry max");
    EXPECT_TRUE(model.view_model_source_count == 0u, "source count");
    EXPECT_TRUE(model.view_model_source_count_max == 16u, "source max");
    EXPECT_TRUE(strcmp(model.input_contract_mode, "caller-provided-report-strings") == 0,
                "input mode");
    EXPECT_TRUE(model.caller_provided_report_strings_only == 1u, "caller provided only");
    EXPECT_TRUE(model.missing_source_row_visible == 1u, "missing visible");
    EXPECT_TRUE(model.malformed_source_row_visible == 1u, "malformed visible");
    EXPECT_TRUE(model.stale_source_row_visible == 1u, "stale visible");
    EXPECT_TRUE(strcmp(model.missing_source_default_decision, "review") == 0,
                "missing decision");
    EXPECT_TRUE(strcmp(model.malformed_source_default_decision, "deny") == 0,
                "malformed decision");
    EXPECT_TRUE(strcmp(model.stale_source_default_decision, "deny") == 0,
                "stale decision");
    EXPECT_TRUE(strcmp(model.unknown_source_default_decision, "deny") == 0,
                "unknown decision");
    EXPECT_TRUE(model.panel_ui_implemented == 0u, "panel ui");
    EXPECT_TRUE(model.report_file_loading_implemented == 0u, "file loading");
    EXPECT_TRUE(model.auto_discover_reports == 0u, "discover reports");
    EXPECT_TRUE(model.auto_scan_host_paths == 0u, "scan host");
    EXPECT_TRUE(model.dashboard_view_model_implemented == 1u, "implemented flag");
    EXPECT_TRUE(model.runtime_authority_granted == 0u, "runtime authority");
    EXPECT_TRUE(model.effect_performed == 0u, "effect");
    EXPECT_TRUE(model.host_read_performed == 0u, "host read");
    EXPECT_TRUE(model.host_write_performed == 0u, "host write");
    EXPECT_TRUE(model.network_performed == 0u, "network");
    EXPECT_TRUE(model.last_error == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_OK,
                "last error");
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_validate(&model) ==
                    LATTICRA_STATUS_OK,
                "validate");
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_is_report_only(&model) == 1,
                "helper");
    return 0;
}

static int full_fixture_renders_required_rows(void) {
    latticra_seal_panel_dashboard_view_model_t model;
    char rendered[LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_REPORT_MAX];
    unsigned i;
    const char *ids[] = {"seal.product.spine",
                         "seal.operator.receipt",
                         "seal.local.capability.registry.schema",
                         "seal.policy.decision",
                         "seal.signed.request",
                         "seal.request.freshness",
                         "seal.runtime.dry.run",
                         "seal.verification.receipt",
                         "seal.capability.gate",
                         "seal.effect.decision",
                         "seal.runtime.handoff",
                         "seal.status.rollup"};

    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_init(&model) == LATTICRA_STATUS_OK,
                "fixture init");
    for (i = 0u; i < sizeof(ids) / sizeof(ids[0]); ++i) {
        EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_add_source_report(
                        &model,
                        ids[i],
                        ids[i],
                        report_only_fixture()) == LATTICRA_STATUS_OK,
                    "add source");
        EXPECT_TRUE(model.last_error == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_OK,
                    "add source ok");
    }
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_add_required_rows(&model) ==
                    LATTICRA_STATUS_OK,
                "add rows");
    EXPECT_TRUE(model.view_model_entry_count == 12u, "row count");
    EXPECT_TRUE(model.view_model_source_count == 12u, "source count");
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_validate(&model) ==
                    LATTICRA_STATUS_OK,
                "validate fixture");
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_is_report_only(&model) == 1,
                "fixture helper");
    for (i = 0u; i < model.view_model_entry_count; ++i) {
        EXPECT_TRUE(model.rows[i].row_state ==
                        LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_PRESENT,
                    "row present");
        EXPECT_TRUE(model.rows[i].row_decision ==
                        LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_DENY,
                    "row deny");
        EXPECT_TRUE(model.rows[i].authority_absent == 1u, "authority absent");
        EXPECT_TRUE(model.rows[i].can_execute_tool == 0u, "execute");
        EXPECT_TRUE(model.rows[i].can_read_host == 0u, "read");
        EXPECT_TRUE(model.rows[i].can_write_host == 0u, "write");
        EXPECT_TRUE(model.rows[i].can_use_network == 0u, "network");
        EXPECT_TRUE(model.rows[i].grants_runtime_authority == 0u, "grants");
        EXPECT_TRUE(model.rows[i].effect_performed == 0u, "effect");
    }

    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_render(
                    &model,
                    rendered,
                    sizeof(rendered)) == LATTICRA_STATUS_OK,
                "render");
    EXPECT_TRUE(strstr(rendered, "LATTICRA SEAL PANEL DASHBOARD VIEW MODEL REPORT") != 0,
                "render header");
    EXPECT_TRUE(strstr(rendered,
                       "seal_panel_dashboard_view_model_profile=latticra-seal-panel-dashboard-view-model/0.1") != 0,
                "render profile");
    EXPECT_TRUE(strstr(rendered, "seal_panel_dashboard_view_model_mode=report-only") != 0,
                "render mode");
    EXPECT_TRUE(strstr(rendered, "seal_panel_dashboard_view_model_status=planned-no-effect") !=
                    0,
                "render status");
    EXPECT_TRUE(strstr(rendered, "view_model_entry_count=12") != 0, "render rows");
    EXPECT_TRUE(strstr(rendered, "view_model_source_count=12") != 0, "render sources");
    EXPECT_TRUE(strstr(rendered, "input_contract_mode=caller-provided-report-strings") != 0,
                "render input");
    EXPECT_TRUE(strstr(rendered, "dashboard_view_model_implemented=1") != 0,
                "render implemented");
    EXPECT_TRUE(strstr(rendered, "panel_ui_implemented=0") != 0, "render panel");
    EXPECT_TRUE(strstr(rendered, "report_file_loading_implemented=0") != 0,
                "render file");
    EXPECT_TRUE(strstr(rendered, "auto_discover_reports=0") != 0, "render discover");
    EXPECT_TRUE(strstr(rendered, "auto_scan_host_paths=0") != 0, "render scan");
    EXPECT_TRUE(strstr(rendered, "runtime_authority_granted=0") != 0, "render authority");
    EXPECT_TRUE(strstr(rendered, "effect_performed=0") != 0, "render effect");
    EXPECT_TRUE(strstr(rendered, "row_id=seal.product.spine") != 0, "render product row");
    EXPECT_TRUE(strstr(rendered, "row_id=seal.status.rollup") != 0, "render rollup row");
    EXPECT_TRUE(strstr(rendered, "row_state=present") != 0, "render present row");
    EXPECT_TRUE(strstr(rendered, "row_decision=deny") != 0, "render deny row");
    EXPECT_TRUE(strstr(rendered, "can_execute_tool=0") != 0, "render execute");
    EXPECT_TRUE(strstr(rendered, "grants_runtime_authority=0") != 0, "render grants");
    EXPECT_TRUE(strstr(rendered, "error=ok") != 0, "render error");
    return 0;
}

static int source_failure_rows_stay_visible(void) {
    latticra_seal_panel_dashboard_view_model_t model;
    const latticra_seal_panel_dashboard_view_model_row_t *row;

    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_init(&model) == LATTICRA_STATUS_OK,
                "failure init");
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_add_required_rows(&model) ==
                    LATTICRA_STATUS_OK,
                "missing rows");
    row = &model.rows[0];
    EXPECT_TRUE(row->source_missing == 1u, "missing source");
    EXPECT_TRUE(row->row_state == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_MISSING,
                "missing state");
    EXPECT_TRUE(row->row_decision == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_REVIEW,
                "missing review");
    EXPECT_TRUE(row->requires_operator_review == 1u, "missing operator");
    EXPECT_TRUE(row->authority_absent == 1u, "missing authority");
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_is_report_only(&model) == 1,
                "missing helper");

    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_init(&model) == LATTICRA_STATUS_OK,
                "malformed init");
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_add_source_report(
                    &model,
                    "seal.product.spine",
                    "Seal product spine",
                    "mode=report-only\nreport_only=1\nsource_report_malformed=1\n") ==
                    LATTICRA_STATUS_OK,
                "malformed source");
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_add_required_rows(&model) ==
                    LATTICRA_STATUS_OK,
                "malformed rows");
    row = &model.rows[0];
    EXPECT_TRUE(row->source_malformed == 1u, "malformed flag");
    EXPECT_TRUE(row->row_state == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_MALFORMED,
                "malformed state");
    EXPECT_TRUE(row->row_decision == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_DENY,
                "malformed deny");
    EXPECT_TRUE(row->authority_absent == 1u, "malformed authority");

    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_init(&model) == LATTICRA_STATUS_OK,
                "stale init");
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_add_source_report(
                    &model,
                    "seal.product.spine",
                    "Seal product spine",
                    "mode=report-only\nreport_only=1\nsource_report_stale=1\n") ==
                    LATTICRA_STATUS_OK,
                "stale source");
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_add_required_rows(&model) ==
                    LATTICRA_STATUS_OK,
                "stale rows");
    row = &model.rows[0];
    EXPECT_TRUE(row->source_stale == 1u, "stale flag");
    EXPECT_TRUE(row->row_state == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATE_STALE,
                "stale state");
    EXPECT_TRUE(row->row_decision == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_DECISION_DENY,
                "stale deny");
    EXPECT_TRUE(row->authority_absent == 1u, "stale authority");
    return 0;
}

static int source_authority_is_rejected(const char *report_text,
                                        latticra_seal_panel_dashboard_view_model_error_t error) {
    latticra_seal_panel_dashboard_view_model_t model;

    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_init(&model) == LATTICRA_STATUS_OK,
                "authority init");
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_add_source_report(
                    &model,
                    "seal.product.spine",
                    "Seal product spine",
                    report_text) == LATTICRA_STATUS_OK,
                "authority add");
    EXPECT_TRUE(model.last_error == error, "authority error");
    EXPECT_TRUE(model.view_model_source_count == 0u, "authority not added");
    EXPECT_TRUE(model.runtime_authority_granted == 0u, "authority global");
    EXPECT_TRUE(model.effect_performed == 0u, "authority effect");
    return 0;
}

static int invalid_sources_fail_closed(void) {
    EXPECT_TRUE(source_authority_is_rejected(
                    "mode=report-only\nreport_only=1\nruntime_authority_granted=1\n",
                    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_GRANT_AUTHORITY) == 0,
                "grant rejected");
    EXPECT_TRUE(source_authority_is_rejected(
                    "mode=report-only\nreport_only=1\neffect_performed=1\n",
                    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_PERFORM_EFFECT) == 0,
                "effect rejected");
    EXPECT_TRUE(source_authority_is_rejected(
                    "mode=report-only\nreport_only=1\nhost_read_performed=1\n",
                    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_TOUCH_HOST) == 0,
                "host rejected");
    EXPECT_TRUE(source_authority_is_rejected(
                    "mode=report-only\nreport_only=1\nnetwork_performed=1\n",
                    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_USE_NETWORK) == 0,
                "network rejected");
    return 0;
}

static int invalid_model_fields_fail_closed(void) {
    latticra_seal_panel_dashboard_view_model_t model;

    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_init(&model) == LATTICRA_STATUS_OK,
                "invalid field init");
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_add_required_rows(&model) ==
                    LATTICRA_STATUS_OK,
                "invalid field rows");
    model.rows[0].row_category =
        (latticra_seal_panel_dashboard_view_model_category_t)99;
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_validate(&model) ==
                    LATTICRA_STATUS_OK,
                "invalid category validate");
    EXPECT_TRUE(model.last_error == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_CATEGORY,
                "invalid category");

    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_init(&model) == LATTICRA_STATUS_OK,
                "invalid state init");
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_add_required_rows(&model) ==
                    LATTICRA_STATUS_OK,
                "invalid state rows");
    model.rows[0].row_state = (latticra_seal_panel_dashboard_view_model_state_t)99;
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_validate(&model) ==
                    LATTICRA_STATUS_OK,
                "invalid state validate");
    EXPECT_TRUE(model.last_error == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_STATE,
                "invalid state");

    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_init(&model) == LATTICRA_STATUS_OK,
                "invalid decision init");
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_add_required_rows(&model) ==
                    LATTICRA_STATUS_OK,
                "invalid decision rows");
    model.rows[0].row_decision =
        (latticra_seal_panel_dashboard_view_model_decision_t)99;
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_validate(&model) ==
                    LATTICRA_STATUS_OK,
                "invalid decision validate");
    EXPECT_TRUE(model.last_error == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_DECISION,
                "invalid decision");

    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_init(&model) == LATTICRA_STATUS_OK,
                "invalid severity init");
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_add_required_rows(&model) ==
                    LATTICRA_STATUS_OK,
                "invalid severity rows");
    model.rows[0].row_severity =
        (latticra_seal_panel_dashboard_view_model_severity_t)99;
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_validate(&model) ==
                    LATTICRA_STATUS_OK,
                "invalid severity validate");
    EXPECT_TRUE(model.last_error == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_SEVERITY,
                "invalid severity");
    return 0;
}

static int capacity_and_api_fail_closed(void) {
    latticra_seal_panel_dashboard_view_model_t model;
    char tiny[1];
    unsigned i;

    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_init(0) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "null init");
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_validate(0) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "null validate");
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_add_source_report(0, 0, 0, 0) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "null source model");
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_add_required_rows(0) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "null rows");
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_is_report_only(0) == 0,
                "null helper");

    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_init(&model) == LATTICRA_STATUS_OK,
                "null source init");
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_add_source_report(
                    &model,
                    0,
                    "label",
                    report_only_fixture()) == LATTICRA_STATUS_OK,
                "null source id");
    EXPECT_TRUE(model.last_error == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_INVALID_INPUT,
                "null source id error");
    EXPECT_TRUE(model.view_model_source_count == 0u, "null source not added");

    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_init(&model) == LATTICRA_STATUS_OK,
                "source capacity init");
    for (i = 0u; i < LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_MAX; ++i) {
        char source_id[LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_ID_MAX];
        (void)snprintf(source_id, sizeof(source_id), "seal.source.%u", i);
        EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_add_source_report(
                        &model,
                        source_id,
                        source_id,
                        report_only_fixture()) == LATTICRA_STATUS_OK,
                    "source capacity add");
    }
    EXPECT_TRUE(model.view_model_source_count == LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_MAX,
                "source capacity full");
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_add_source_report(
                    &model,
                    "seal.source.overflow",
                    "overflow",
                    report_only_fixture()) == LATTICRA_STATUS_OK,
                "source overflow add");
    EXPECT_TRUE(model.last_error ==
                    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_CAPACITY_EXCEEDED,
                "source overflow error");

    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_init(&model) == LATTICRA_STATUS_OK,
                "row capacity init");
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_add_required_rows(&model) ==
                    LATTICRA_STATUS_OK,
                "first rows");
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_add_required_rows(&model) ==
                    LATTICRA_STATUS_OK,
                "second rows");
    EXPECT_TRUE(model.last_error ==
                    LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_ROW_CAPACITY_EXCEEDED,
                "row overflow");

    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_render(&model, tiny, sizeof(tiny)) ==
                    LATTICRA_STATUS_BUFFER_TOO_SMALL,
                "small render");
    EXPECT_TRUE(tiny[0] == '\0', "small render cleared");
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_render(0, tiny, sizeof(tiny)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "null render model");
    EXPECT_TRUE(latticra_seal_panel_dashboard_view_model_render(&model, 0, sizeof(tiny)) ==
                    LATTICRA_STATUS_NULL_ARGUMENT,
                "null render buffer");
    return 0;
}

int main(void) {
    if (initialized_model_is_no_effect() != 0) {
        return 1;
    }
    if (full_fixture_renders_required_rows() != 0) {
        return 1;
    }
    if (source_failure_rows_stay_visible() != 0) {
        return 1;
    }
    if (invalid_sources_fail_closed() != 0) {
        return 1;
    }
    if (invalid_model_fields_fail_closed() != 0) {
        return 1;
    }
    if (capacity_and_api_fail_closed() != 0) {
        return 1;
    }
    printf("seal panel dashboard view model invariants: ok\n");
    return 0;
}
