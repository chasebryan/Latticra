#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal panel dashboard view model implementation plan: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal panel dashboard view model implementation plan: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

plan="docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION_PLAN.md"

require_file "$plan"
require_file docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT.md
require_file docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT_STATUS.md
require_file docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION_PLAN_STATUS.md
require_file scripts/test-latticra-seal-panel-dashboard-view-model-contract.sh
require_file scripts/test-latticra-seal-panel-dashboard-view-model-contract-status.sh
require_file scripts/test-latticra-seal-panel-dashboard-view-model-implementation-plan-status.sh
require_file .github/workflows/latticra-seal-panel-dashboard-view-model-implementation-plan.yml

require_contains 'Status: implementation plan for a future no-effect Latticra Seal Panel dashboard view model' "$plan"
require_contains 'docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT.md' "$plan"
require_contains 'docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT_STATUS.md' "$plan"
require_contains 'scripts/test-latticra-seal-panel-dashboard-view-model-contract.sh' "$plan"
require_contains 'scripts/test-latticra-seal-panel-dashboard-view-model-contract-status.sh' "$plan"
require_contains 'include/latticra/seal_panel_dashboard_view_model.h' "$plan"
require_contains 'src/seal_panel_dashboard_view_model.c' "$plan"
require_contains 'tests/seal_panel_dashboard_view_model_invariants.c' "$plan"
require_contains 'scripts/test-latticra-seal-panel-dashboard-view-model.sh' "$plan"
require_contains 'docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION.md' "$plan"
require_contains 'tests/seal_panel_dashboard_view_model_surface.c' "$plan"
require_contains 'scripts/latticra-seal-panel-dashboard-view-model.sh' "$plan"
require_contains 'docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SURFACE.md' "$plan"
require_contains 'docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATUS.md' "$plan"
require_contains 'seal_panel_dashboard_view_model_implementation_plan_present=1' "$plan"
require_contains 'predecessor_view_model_contract_status_present=1' "$plan"
require_contains 'seal_panel_dashboard_view_model_plan_profile=latticra-seal-panel-dashboard-view-model-implementation-plan/0.1' "$plan"
require_contains 'seal_panel_dashboard_view_model_profile=latticra-seal-panel-dashboard-view-model/0.1' "$plan"
require_contains 'seal_panel_dashboard_view_model_mode=implementation-plan-only' "$plan"
require_contains 'seal_panel_dashboard_view_model_status=not-implemented' "$plan"
require_contains 'view_model_entry_count_max=16' "$plan"
require_contains 'view_model_source_count_max=16' "$plan"
require_contains 'view_model_row_id_max=64' "$plan"
require_contains 'view_model_label_max=96' "$plan"
require_contains 'view_model_summary_max=192' "$plan"
require_contains 'view_model_blocked_reason_max=160' "$plan"
require_contains 'view_model_next_action_max=160' "$plan"
require_contains 'input_contract_mode=caller-provided-report-strings' "$plan"
require_contains 'caller_provided_report_strings_only=1' "$plan"
require_contains 'deterministic_fixture_planned=1' "$plan"
require_contains 'bounded_key_value_scan_planned=1' "$plan"
require_contains 'auto_discover_reports=0' "$plan"
require_contains 'auto_scan_host_paths=0' "$plan"
require_contains 'report_file_loading_implemented=0' "$plan"
require_contains 'panel_ui_implemented=0' "$plan"
require_contains 'dashboard_view_model_implemented=0' "$plan"
require_contains 'runtime_authority_granted=0' "$plan"
require_contains 'effect_performed=0' "$plan"
require_contains 'host_read_performed=0' "$plan"
require_contains 'host_write_performed=0' "$plan"
require_contains 'network_performed=0' "$plan"
require_contains 'LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_ROW_MAX' "$plan"
require_contains 'latticra_seal_panel_dashboard_view_model_t' "$plan"
require_contains 'latticra_seal_panel_dashboard_view_model_add_source_report' "$plan"
require_contains 'latticra_seal_panel_dashboard_view_model_add_required_rows' "$plan"
require_contains 'latticra_seal_panel_dashboard_view_model_render' "$plan"
require_contains 'The API must not include a file-path input' "$plan"
require_contains 'source_report_present' "$plan"
require_contains 'source_report_malformed' "$plan"
require_contains 'source_report_stale' "$plan"
require_contains 'source_runtime_authority_granted' "$plan"
require_contains 'row=seal.product.spine' "$plan"
require_contains 'row=seal.operator.receipt' "$plan"
require_contains 'row=seal.local.capability.registry.schema' "$plan"
require_contains 'row=seal.policy.decision' "$plan"
require_contains 'row=seal.signed.request' "$plan"
require_contains 'row=seal.request.freshness' "$plan"
require_contains 'row=seal.runtime.dry.run' "$plan"
require_contains 'row=seal.verification.receipt' "$plan"
require_contains 'row=seal.capability.gate' "$plan"
require_contains 'row=seal.effect.decision' "$plan"
require_contains 'row=seal.runtime.handoff' "$plan"
require_contains 'row=seal.status.rollup' "$plan"
require_contains 'LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_MISSING_SOURCE' "$plan"
require_contains 'LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_MALFORMED_SOURCE' "$plan"
require_contains 'LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_STALE_SOURCE' "$plan"
require_contains 'LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_GRANT_AUTHORITY' "$plan"
require_contains 'LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_PERFORM_EFFECT' "$plan"
require_contains 'LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_TOUCH_HOST' "$plan"
require_contains 'LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SOURCE_WOULD_USE_NETWORK' "$plan"
require_contains 'LATTICRA SEAL PANEL DASHBOARD VIEW MODEL REPORT' "$plan"
require_contains 'missing_source_row_visible=1' "$plan"
require_contains 'malformed_source_row_visible=1' "$plan"
require_contains 'stale_source_row_visible=1' "$plan"
require_contains 'missing_source_default_decision=review' "$plan"
require_contains 'malformed_source_default_decision=deny' "$plan"
require_contains 'stale_source_default_decision=deny' "$plan"
require_contains 'unknown_source_default_decision=deny' "$plan"
require_contains 'operator_review_required_for_any_missing_source=1' "$plan"
require_contains 'authority_absent_for_all_rows=1' "$plan"
require_contains 'caller-provided source reports are accepted without file loading' "$plan"
require_contains 'turning dashboard rows into execution grants' "$plan"
require_contains 'turning dashboard rows into effect grants' "$plan"
require_contains 'The next valid Latticra Seal slice is a signed receipt proof path that remains verification-only until trust-root and revocation boundaries are implemented.' "$plan"
require_contains 'sh scripts/test-latticra-seal-panel-dashboard-view-model-implementation-plan.sh' .github/workflows/latticra-seal-panel-dashboard-view-model-implementation-plan.yml
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' .github/workflows/latticra-seal-panel-dashboard-view-model-implementation-plan.yml

printf 'latticra seal panel dashboard view model implementation plan: ok\n'
