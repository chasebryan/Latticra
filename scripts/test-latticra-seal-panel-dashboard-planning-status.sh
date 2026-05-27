#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal panel dashboard planning status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal panel dashboard planning status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_PANEL_DASHBOARD_PLANNING_STATUS.md"
checkpoint="docs/LATTICRA_SEAL_PANEL_DASHBOARD_PLANNING_CHECKPOINT.md"
product_doc="docs/latticra-seal/PRODUCT.md"
seal_status="docs/latticra-seal/STATUS.md"

require_file "$status_file"
require_file "$checkpoint"
require_file "$product_doc"
require_file "$seal_status"
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md
require_file docs/project_notes/README.md
require_file docs/status/SEAL_LOCAL_CAPABILITY_REGISTRY_SCHEMA_STATUS.md
require_file scripts/test-latticra-seal-panel-dashboard-planning-checkpoint.sh
require_file scripts/test-latticra-seal-local-capability-registry-schema-status.sh
require_file .github/workflows/latticra-seal-panel-dashboard-planning-checkpoint.yml
require_file .github/workflows/latticra-seal-panel-dashboard-planning-status.yml

require_contains 'Status: status record for the Latticra Seal Panel dashboard planning checkpoint' "$status_file"
require_contains 'seal_panel_dashboard_planning_checkpoint_present=1' "$status_file"
require_contains 'seal_panel_dashboard_planning_status_present=1' "$status_file"
require_contains 'seal_panel_dashboard_predecessor_local_capability_registry_schema_status_present=1' "$status_file"
require_contains 'seal_panel_dashboard_profile=latticra-seal-panel-dashboard-planning/0.1' "$status_file"
require_contains 'seal_panel_dashboard_mode=planning-only' "$status_file"
require_contains 'seal_panel_dashboard_status=not-implemented' "$status_file"
require_contains 'panel_visible_target=1' "$status_file"
require_contains 'local_report_sources_planned=1' "$status_file"
require_contains 'operator_receipt_report_source_planned=1' "$status_file"
require_contains 'local_capability_registry_schema_source_planned=1' "$status_file"
require_contains 'policy_decision_source_planned=1' "$status_file"
require_contains 'runtime_dry_run_source_planned=1' "$status_file"
require_contains 'verification_receipt_source_planned=1' "$status_file"
require_contains 'capability_gate_source_planned=1' "$status_file"
require_contains 'effect_decision_source_planned=1' "$status_file"
require_contains 'operator_review_queue_preview_planned=1' "$status_file"
require_contains 'receipt_and_report_links_planned=1' "$status_file"
require_contains 'panel_ui_implemented=0' "$status_file"
require_contains 'dashboard_view_model_implemented=0' "$status_file"
require_contains 'report_file_loading_implemented=0' "$status_file"
require_contains 'auto_scan_host_paths=0' "$status_file"
require_contains 'registry_loader_implemented=0' "$status_file"
require_contains 'tool_execution_enabled=0' "$status_file"
require_contains 'policy_enforcement_enabled=0' "$status_file"
require_contains 'capability_enforcement_enabled=0' "$status_file"
require_contains 'signature_verification_enabled=0' "$status_file"
require_contains 'trust_store_lookup_enabled=0' "$status_file"
require_contains 'network_lookup_enabled=0' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'effect_performed=0' "$status_file"
require_contains 'production_security_product=0' "$status_file"
require_contains 'docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT.md' "$status_file"
require_contains 'docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT_STATUS.md' "$status_file"
require_contains 'docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION_PLAN.md' "$status_file"
require_contains 'docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION_PLAN_STATUS.md' "$status_file"
require_contains 'The next valid Latticra Seal slice is a signed receipt proof path that remains verification-only until trust-root and revocation boundaries are implemented.' "$status_file"
require_contains 'sh scripts/test-latticra-seal-panel-dashboard-planning-status.sh' .github/workflows/latticra-seal-panel-dashboard-planning-status.yml
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' .github/workflows/latticra-seal-panel-dashboard-planning-status.yml

require_contains 'panel_dashboard_planning_checkpoint=1' "$product_doc"
require_contains 'panel_dashboard_planning_status=1' "$product_doc"
require_contains 'panel_dashboard_view_model_contract=1' "$product_doc"
require_contains 'panel_dashboard_view_model_contract_status=1' "$product_doc"
require_contains 'panel_dashboard_view_model_implementation_plan=1' "$product_doc"
require_contains 'panel_dashboard_view_model_implementation_plan_status=1' "$product_doc"
require_contains 'panel_dashboard_view_model_implementation=1' "$product_doc"
require_contains 'seal_panel_dashboard=view-model-report-surface' "$product_doc"
require_contains 'panel_dashboard_planning_checkpoint_present=1' "$product_doc"
require_contains 'panel_dashboard_planning_status_present=1' "$product_doc"
require_contains 'Seal Panel dashboard view-model implementation plan' "$product_doc"
require_contains 'bounded no-effect Seal Panel dashboard view-model implementation' "$product_doc"
require_contains 'signed receipt proof path' "$product_doc"

require_contains 'panel_dashboard_planning_checkpoint_present=1' "$seal_status"
require_contains 'panel_dashboard_planning_status_present=1' "$seal_status"
require_contains 'seal_panel_dashboard_planning_checkpoint_present=1' README.md
require_contains 'seal_panel_dashboard_planning_status_present=1' README.md
require_contains 'panel_dashboard_predecessor_local_capability_registry_schema_status_present=1' README.md
require_contains 'docs/LATTICRA_SEAL_PANEL_DASHBOARD_PLANNING_CHECKPOINT.md' README.md
require_contains 'docs/status/SEAL_PANEL_DASHBOARD_PLANNING_STATUS.md' README.md
require_contains 'Latest Seal Panel dashboard planning checkpoint note: 2026-05-26 CDT' STATUS.md
require_contains 'Latest Seal Panel dashboard planning checkpoint note: 2026-05-26 CDT' docs/status/CURRENT_STATUS.md
require_contains 'panel_dashboard_planning_checkpoint_present=1' STATUS.md
require_contains 'panel_dashboard_planning_status_present=1' docs/status/CURRENT_STATUS.md
require_contains 'LATTICRA_SEAL_PANEL_DASHBOARD_PLANNING_CHECKPOINT.md' docs/FOUNDATION_INDEX.md
require_contains 'SEAL_PANEL_DASHBOARD_PLANNING_STATUS.md' docs/status/README.md
require_contains 'Latticra Seal Panel dashboard planning checkpoint' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal Panel dashboard planning checkpoint' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/status/SEAL_PANEL_DASHBOARD_PLANNING_STATUS.md' docs/project_notes/README.md

sh scripts/test-latticra-seal-panel-dashboard-planning-checkpoint.sh
sh scripts/test-latticra-seal-local-capability-registry-schema-status.sh

printf 'latticra seal panel dashboard planning status: ok\n'
