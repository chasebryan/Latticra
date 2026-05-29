#!/usr/bin/env sh
set -eu

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-panel-dashboard-view-model-surface.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal panel dashboard view model surface: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal panel dashboard view model surface: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

doc="docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SURFACE.md"
report="$tmpdir/latticra-seal-panel-dashboard-view-model.out"

require_file "$doc"
require_file tests/seal_panel_dashboard_view_model_surface.c
require_file scripts/latticra-seal-panel-dashboard-view-model.sh
require_file include/latticra/seal_panel_dashboard_view_model.h
require_file src/seal_panel_dashboard_view_model.c
require_file scripts/test-latticra-seal-panel-dashboard-view-model.sh
require_file docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION.md
require_file .github/workflows/latticra-seal-panel-dashboard-view-model-surface.yml

require_contains 'Status: report surface for the Latticra Seal Panel dashboard view model' "$doc"
require_contains 'tests/seal_panel_dashboard_view_model_surface.c' "$doc"
require_contains 'scripts/latticra-seal-panel-dashboard-view-model.sh' "$doc"
require_contains 'LATTICRA SEAL PANEL DASHBOARD VIEW MODEL REPORT' "$doc"
require_contains 'seal_panel_dashboard_view_model_profile=latticra-seal-panel-dashboard-view-model/0.1' "$doc"
require_contains 'seal_panel_dashboard_view_model_mode=report-only' "$doc"
require_contains 'seal_panel_dashboard_view_model_status=planned-no-effect' "$doc"
require_contains 'view_model_entry_count=12' "$doc"
require_contains 'view_model_source_count=12' "$doc"
require_contains 'input_contract_mode=caller-provided-report-strings' "$doc"
require_contains 'missing_source_row_visible=1' "$doc"
require_contains 'malformed_source_row_visible=1' "$doc"
require_contains 'stale_source_row_visible=1' "$doc"
require_contains 'operator_review_required_for_any_missing_source=1' "$doc"
require_contains 'authority_absent_for_all_rows=1' "$doc"
require_contains 'panel_ui_implemented=0' "$doc"
require_contains 'dashboard_view_model_implemented=1' "$doc"
require_contains 'report_file_loading_implemented=0' "$doc"
require_contains 'auto_discover_reports=0' "$doc"
require_contains 'auto_scan_host_paths=0' "$doc"
require_contains 'runtime_authority_granted=0' "$doc"
require_contains 'effect_performed=0' "$doc"
require_contains 'host_read_performed=0' "$doc"
require_contains 'host_write_performed=0' "$doc"
require_contains 'network_performed=0' "$doc"
require_contains 'row_id=seal.product.spine' "$doc"
require_contains 'row_id=seal.status.rollup' "$doc"
require_contains 'row_decision=deny' "$doc"
require_contains 'can_execute_tool=0' "$doc"
require_contains 'can_read_host=0' "$doc"
require_contains 'can_write_host=0' "$doc"
require_contains 'can_use_network=0' "$doc"
require_contains 'grants_runtime_authority=0' "$doc"
require_contains 'docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATUS.md' "$doc"

sh scripts/latticra-seal-panel-dashboard-view-model.sh > "$report"

require_contains 'LATTICRA SEAL PANEL DASHBOARD VIEW MODEL REPORT' "$report"
require_contains 'seal_panel_dashboard_view_model_profile=latticra-seal-panel-dashboard-view-model/0.1' "$report"
require_contains 'seal_panel_dashboard_view_model_mode=report-only' "$report"
require_contains 'seal_panel_dashboard_view_model_status=planned-no-effect' "$report"
require_contains 'view_model_entry_count=12' "$report"
require_contains 'view_model_source_count=12' "$report"
require_contains 'input_contract_mode=caller-provided-report-strings' "$report"
require_contains 'panel_ui_implemented=0' "$report"
require_contains 'dashboard_view_model_implemented=1' "$report"
require_contains 'report_file_loading_implemented=0' "$report"
require_contains 'auto_discover_reports=0' "$report"
require_contains 'auto_scan_host_paths=0' "$report"
require_contains 'runtime_authority_granted=0' "$report"
require_contains 'effect_performed=0' "$report"
require_contains 'host_read_performed=0' "$report"
require_contains 'host_write_performed=0' "$report"
require_contains 'network_performed=0' "$report"
require_contains 'row_id=seal.product.spine' "$report"
require_contains 'row_id=seal.operator.receipt' "$report"
require_contains 'row_id=seal.local.capability.registry.schema' "$report"
require_contains 'row_id=seal.policy.decision' "$report"
require_contains 'row_id=seal.signed.request' "$report"
require_contains 'row_id=seal.request.freshness' "$report"
require_contains 'row_id=seal.runtime.dry.run' "$report"
require_contains 'row_id=seal.verification.receipt' "$report"
require_contains 'row_id=seal.capability.gate' "$report"
require_contains 'row_id=seal.effect.decision' "$report"
require_contains 'row_id=seal.runtime.handoff' "$report"
require_contains 'row_id=seal.status.rollup' "$report"
require_contains 'row_decision=deny' "$report"
require_contains 'can_execute_tool=0' "$report"
require_contains 'can_read_host=0' "$report"
require_contains 'can_write_host=0' "$report"
require_contains 'can_use_network=0' "$report"
require_contains 'grants_runtime_authority=0' "$report"
require_contains 'error=ok' "$report"

printf 'latticra seal panel dashboard view model surface: ok\n'
