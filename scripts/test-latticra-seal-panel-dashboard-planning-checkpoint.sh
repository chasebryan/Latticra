#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal panel dashboard planning checkpoint: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal panel dashboard planning checkpoint: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

checkpoint="docs/LATTICRA_SEAL_PANEL_DASHBOARD_PLANNING_CHECKPOINT.md"

require_file "$checkpoint"
require_file docs/status/SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_STATUS.md
require_file docs/LATTICRA_SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_SURFACE.md
require_file docs/status/SEAL_PANEL_DASHBOARD_PLANNING_STATUS.md
require_file scripts/test-latticra-seal-panel-dashboard-planning-status.sh
require_file .github/workflows/latticra-seal-panel-dashboard-planning-checkpoint.yml

require_contains 'Status: planning checkpoint for a Panel-visible Latticra Seal dashboard' "$checkpoint"
require_contains 'seal_panel_dashboard_profile=latticra-seal-panel-dashboard-planning/0.1' "$checkpoint"
require_contains 'seal_panel_dashboard_mode=planning-only' "$checkpoint"
require_contains 'seal_panel_dashboard_status=not-implemented' "$checkpoint"
require_contains 'panel_visible_target=1' "$checkpoint"
require_contains 'panel_dashboard_planning_checkpoint_present=1' "$checkpoint"
require_contains 'predecessor_local_capability_registry_schema_status_present=1' "$checkpoint"
require_contains 'local_report_sources_planned=1' "$checkpoint"
require_contains 'operator_receipt_report_source_planned=1' "$checkpoint"
require_contains 'local_capability_registry_schema_source_planned=1' "$checkpoint"
require_contains 'policy_decision_source_planned=1' "$checkpoint"
require_contains 'runtime_dry_run_source_planned=1' "$checkpoint"
require_contains 'verification_receipt_source_planned=1' "$checkpoint"
require_contains 'capability_gate_source_planned=1' "$checkpoint"
require_contains 'effect_decision_source_planned=1' "$checkpoint"
require_contains 'panel_ui_implemented=0' "$checkpoint"
require_contains 'dashboard_view_model_implemented=0' "$checkpoint"
require_contains 'report_file_loading_implemented=0' "$checkpoint"
require_contains 'panel_launch_performed=0' "$checkpoint"
require_contains 'panel_workflow_run=0' "$checkpoint"
require_contains 'runtime_authority_granted=0' "$checkpoint"
require_contains 'effect_performed=0' "$checkpoint"
require_contains 'host_read_performed=0' "$checkpoint"
require_contains 'host_write_performed=0' "$checkpoint"
require_contains 'network_performed=0' "$checkpoint"
require_contains 'production_security_product=0' "$checkpoint"
require_contains 'exact_view_model_fields=required' "$checkpoint"
require_contains 'missing_source_behavior=required' "$checkpoint"
require_contains 'malformed_source_behavior=required' "$checkpoint"
require_contains 'stale_source_behavior=required' "$checkpoint"
require_contains 'no_effect_execution_path=required' "$checkpoint"
require_contains 'docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT.md' "$checkpoint"
require_contains 'docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT_STATUS.md' "$checkpoint"
require_contains 'docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION_PLAN.md' "$checkpoint"
require_contains 'docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION_PLAN_STATUS.md' "$checkpoint"
require_contains 'The next valid Latticra Seal slice is a signed receipt trust-root boundary contract that remains metadata-only and does not load trust roots, perform revocation lookup, use networks, or grant authority.' "$checkpoint"
require_contains 'sh scripts/test-latticra-seal-panel-dashboard-planning-checkpoint.sh' .github/workflows/latticra-seal-panel-dashboard-planning-checkpoint.yml
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' .github/workflows/latticra-seal-panel-dashboard-planning-checkpoint.yml

printf 'latticra seal panel dashboard planning checkpoint: ok\n'
