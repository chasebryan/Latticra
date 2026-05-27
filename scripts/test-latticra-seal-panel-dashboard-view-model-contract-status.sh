#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal panel dashboard view model contract status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal panel dashboard view model contract status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT_STATUS.md"
contract="docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT.md"
planning_status="docs/status/SEAL_PANEL_DASHBOARD_PLANNING_STATUS.md"
product_doc="docs/latticra-seal/PRODUCT.md"
seal_status="docs/latticra-seal/STATUS.md"

require_file "$status_file"
require_file "$contract"
require_file "$planning_status"
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
require_file scripts/test-latticra-seal-panel-dashboard-view-model-contract.sh
require_file scripts/test-latticra-seal-panel-dashboard-planning-status.sh
require_file .github/workflows/latticra-seal-panel-dashboard-view-model-contract.yml
require_file .github/workflows/latticra-seal-panel-dashboard-view-model-contract-status.yml

require_contains 'Status: status record for the Latticra Seal Panel dashboard view-model contract' "$status_file"
require_contains 'seal_panel_dashboard_view_model_contract_present=1' "$status_file"
require_contains 'seal_panel_dashboard_view_model_contract_status_present=1' "$status_file"
require_contains 'seal_panel_dashboard_view_model_predecessor_panel_dashboard_planning_status_present=1' "$status_file"
require_contains 'seal_panel_dashboard_view_model_profile=latticra-seal-panel-dashboard-view-model/0.1' "$status_file"
require_contains 'seal_panel_dashboard_view_model_mode=contract-only' "$status_file"
require_contains 'seal_panel_dashboard_view_model_status=not-implemented' "$status_file"
require_contains 'view_model_entry_count_max=16' "$status_file"
require_contains 'view_model_row_id_max=64' "$status_file"
require_contains 'view_model_label_max=96' "$status_file"
require_contains 'view_model_summary_max=192' "$status_file"
require_contains 'view_model_blocked_reason_max=160' "$status_file"
require_contains 'view_model_next_action_max=160' "$status_file"
require_contains 'input_contract_mode=caller-provided-report-strings' "$status_file"
require_contains 'auto_discover_reports=0' "$status_file"
require_contains 'auto_scan_host_paths=0' "$status_file"
require_contains 'report_file_loading_implemented=0' "$status_file"
require_contains 'panel_ui_implemented=0' "$status_file"
require_contains 'dashboard_view_model_implemented=0' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'effect_performed=0' "$status_file"
require_contains 'production_security_product=0' "$status_file"
require_contains 'row=seal.product.spine' "$status_file"
require_contains 'row=seal.operator.receipt' "$status_file"
require_contains 'row=seal.local.capability.registry.schema' "$status_file"
require_contains 'row=seal.policy.decision' "$status_file"
require_contains 'row=seal.signed.request' "$status_file"
require_contains 'row=seal.request.freshness' "$status_file"
require_contains 'row=seal.runtime.dry.run' "$status_file"
require_contains 'row=seal.verification.receipt' "$status_file"
require_contains 'row=seal.capability.gate' "$status_file"
require_contains 'row=seal.effect.decision' "$status_file"
require_contains 'row=seal.runtime.handoff' "$status_file"
require_contains 'row=seal.status.rollup' "$status_file"
require_contains 'missing_source_row_visible=1' "$status_file"
require_contains 'malformed_source_row_visible=1' "$status_file"
require_contains 'stale_source_row_visible=1' "$status_file"
require_contains 'missing_source_default_decision=review' "$status_file"
require_contains 'malformed_source_default_decision=deny' "$status_file"
require_contains 'stale_source_default_decision=deny' "$status_file"
require_contains 'unknown_source_default_decision=deny' "$status_file"
require_contains 'operator_review_required_for_any_missing_source=1' "$status_file"
require_contains 'authority_absent_for_all_rows=1' "$status_file"
require_contains 'docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION_PLAN.md' "$status_file"
require_contains 'docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION_PLAN_STATUS.md' "$status_file"
require_contains 'The next valid Latticra Seal slice is a signed receipt proof path that remains verification-only until trust-root and revocation boundaries are implemented.' "$status_file"
require_contains 'sh scripts/test-latticra-seal-panel-dashboard-view-model-contract-status.sh' .github/workflows/latticra-seal-panel-dashboard-view-model-contract-status.yml
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' .github/workflows/latticra-seal-panel-dashboard-view-model-contract-status.yml

require_contains 'panel_dashboard_view_model_contract=1' "$product_doc"
require_contains 'panel_dashboard_view_model_contract_status=1' "$product_doc"
require_contains 'panel_dashboard_view_model_implementation_plan=1' "$product_doc"
require_contains 'panel_dashboard_view_model_implementation_plan_status=1' "$product_doc"
require_contains 'panel_dashboard_view_model_implementation=1' "$product_doc"
require_contains 'seal_panel_dashboard=view-model-report-surface' "$product_doc"
require_contains 'panel_dashboard_view_model_contract_present=1' "$product_doc"
require_contains 'panel_dashboard_view_model_contract_status_present=1' "$product_doc"
require_contains 'bounded no-effect Seal Panel dashboard view-model implementation' "$product_doc"
require_contains 'signed receipt proof path' "$product_doc"

require_contains 'panel_dashboard_view_model_contract_present=1' "$seal_status"
require_contains 'panel_dashboard_view_model_contract_status_present=1' "$seal_status"
require_contains 'seal_panel_dashboard_view_model_contract_present=1' README.md
require_contains 'seal_panel_dashboard_view_model_contract_status_present=1' README.md
require_contains 'panel_dashboard_view_model_predecessor_panel_dashboard_planning_status_present=1' README.md
require_contains 'docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT.md' README.md
require_contains 'docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT_STATUS.md' README.md
require_contains 'Latest Seal Panel dashboard view-model contract note: 2026-05-27 CDT' STATUS.md
require_contains 'Latest Seal Panel dashboard view-model contract note: 2026-05-27 CDT' docs/status/CURRENT_STATUS.md
require_contains 'panel_dashboard_view_model_contract_present=1' STATUS.md
require_contains 'panel_dashboard_view_model_contract_status_present=1' docs/status/CURRENT_STATUS.md
require_contains 'LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT.md' docs/FOUNDATION_INDEX.md
require_contains 'SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT_STATUS.md' docs/status/README.md
require_contains 'Latticra Seal Panel dashboard view-model contract' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal Panel dashboard view-model contract' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT_STATUS.md' docs/project_notes/README.md

sh scripts/test-latticra-seal-panel-dashboard-view-model-contract.sh
sh scripts/test-latticra-seal-panel-dashboard-planning-status.sh

printf 'latticra seal panel dashboard view model contract status: ok\n'
