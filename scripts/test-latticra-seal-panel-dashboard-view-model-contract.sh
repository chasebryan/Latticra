#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal panel dashboard view model contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal panel dashboard view model contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_PANEL_DASHBOARD_PLANNING_CHECKPOINT.md
require_file docs/status/SEAL_PANEL_DASHBOARD_PLANNING_STATUS.md
require_file docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_CONTRACT_STATUS.md
require_file scripts/test-latticra-seal-panel-dashboard-view-model-contract-status.sh
require_file .github/workflows/latticra-seal-panel-dashboard-view-model-contract.yml

require_contains 'Status: contract for the future Latticra Seal Panel dashboard view model' "$contract"
require_contains 'seal_panel_dashboard_view_model_profile=latticra-seal-panel-dashboard-view-model/0.1' "$contract"
require_contains 'seal_panel_dashboard_view_model_mode=contract-only' "$contract"
require_contains 'seal_panel_dashboard_view_model_status=not-implemented' "$contract"
require_contains 'seal_panel_dashboard_view_model_contract_present=1' "$contract"
require_contains 'predecessor_panel_dashboard_planning_status_present=1' "$contract"
require_contains 'view_model_entry_count_max=16' "$contract"
require_contains 'view_model_row_id_max=64' "$contract"
require_contains 'view_model_label_max=96' "$contract"
require_contains 'view_model_summary_max=192' "$contract"
require_contains 'view_model_blocked_reason_max=160' "$contract"
require_contains 'view_model_next_action_max=160' "$contract"
require_contains 'input_contract_mode=caller-provided-report-strings' "$contract"
require_contains 'auto_discover_reports=0' "$contract"
require_contains 'auto_scan_host_paths=0' "$contract"
require_contains 'report_file_loading_implemented=0' "$contract"
require_contains 'panel_ui_implemented=0' "$contract"
require_contains 'dashboard_view_model_implemented=0' "$contract"
require_contains 'runtime_authority_granted=0' "$contract"
require_contains 'effect_performed=0' "$contract"
require_contains 'host_read_performed=0' "$contract"
require_contains 'host_write_performed=0' "$contract"
require_contains 'network_performed=0' "$contract"
require_contains 'production_security_product=0' "$contract"
require_contains 'row_id=required' "$contract"
require_contains 'row_label=required' "$contract"
require_contains 'row_category=required' "$contract"
require_contains 'row_source=required' "$contract"
require_contains 'row_state=required' "$contract"
require_contains 'row_decision=required' "$contract"
require_contains 'row_severity=required' "$contract"
require_contains 'row_summary=required' "$contract"
require_contains 'row_blocked_reason=required' "$contract"
require_contains 'row_next_action=required' "$contract"
require_contains 'row=seal.product.spine' "$contract"
require_contains 'row=seal.operator.receipt' "$contract"
require_contains 'row=seal.local.capability.registry.schema' "$contract"
require_contains 'row=seal.policy.decision' "$contract"
require_contains 'row=seal.signed.request' "$contract"
require_contains 'row=seal.request.freshness' "$contract"
require_contains 'row=seal.runtime.dry.run' "$contract"
require_contains 'row=seal.verification.receipt' "$contract"
require_contains 'row=seal.capability.gate' "$contract"
require_contains 'row=seal.effect.decision' "$contract"
require_contains 'row=seal.runtime.handoff' "$contract"
require_contains 'row=seal.status.rollup' "$contract"
require_contains 'category=mode' "$contract"
require_contains 'state=missing' "$contract"
require_contains 'decision=deny' "$contract"
require_contains 'severity=blocked' "$contract"
require_contains 'missing_source_row_visible=1' "$contract"
require_contains 'malformed_source_row_visible=1' "$contract"
require_contains 'stale_source_row_visible=1' "$contract"
require_contains 'missing_source_default_decision=review' "$contract"
require_contains 'malformed_source_default_decision=deny' "$contract"
require_contains 'stale_source_default_decision=deny' "$contract"
require_contains 'unknown_source_default_decision=deny' "$contract"
require_contains 'operator_review_required_for_any_missing_source=1' "$contract"
require_contains 'authority_absent_for_all_rows=1' "$contract"
require_contains 'docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION_PLAN.md' "$contract"
require_contains 'docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_IMPLEMENTATION_PLAN_STATUS.md' "$contract"
require_contains 'The next valid Latticra Seal slice is a signed receipt trust-root boundary contract that remains metadata-only and does not load trust roots, perform revocation lookup, use networks, or grant authority.' "$contract"
require_contains 'sh scripts/test-latticra-seal-panel-dashboard-view-model-contract.sh' .github/workflows/latticra-seal-panel-dashboard-view-model-contract.yml
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' .github/workflows/latticra-seal-panel-dashboard-view-model-contract.yml

printf 'latticra seal panel dashboard view model contract: ok\n'
