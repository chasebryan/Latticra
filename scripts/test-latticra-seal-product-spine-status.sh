#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal product spine status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal product spine status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_PRODUCT_SPINE_STATUS.md"
product_doc="docs/latticra-seal/PRODUCT.md"

require_file "$status_file"
require_file "$product_doc"
require_file docs/latticra-seal/README.md
require_file docs/latticra-seal/STATUS.md
require_file scripts/test-latticra-seal-docs.sh

require_contains 'Status: status record for the Latticra Seal product spine' "$status_file"
require_contains 'seal_product_spine_document_present=1' "$status_file"
require_contains 'seal_product_spine_status_present=1' "$status_file"
require_contains 'next_generation_security_product_target=1' "$status_file"
require_contains 'observe_mode_current=1' "$status_file"
require_contains 'verify_mode_partial_local=1' "$status_file"
require_contains 'decide_mode_metadata_only=1' "$status_file"
require_contains 'handoff_mode_metadata_only=1' "$status_file"
require_contains 'enforce_mode_future_closed=1' "$status_file"
require_contains 'operator_visible_reports=1' "$status_file"
require_contains 'product_spine_changes_authority=0' "$status_file"
require_contains 'production_security_product=0' "$status_file"
require_contains 'malware_prevention=0' "$status_file"
require_contains 'ransomware_prevention=0' "$status_file"
require_contains 'runtime_enforcement=0' "$status_file"
require_contains 'kernel_enforcement=0' "$status_file"
require_contains 'root_authority=0' "$status_file"
require_contains 'network_authority=0' "$status_file"
require_contains 'capability_enforcement=0' "$status_file"
require_contains 'effect_execution=0' "$status_file"
require_contains 'ai_agent_execution_control=0' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'observe_mode=current' "$status_file"
require_contains 'verify_mode=partial-local' "$status_file"
require_contains 'decide_mode=metadata-only' "$status_file"
require_contains 'handoff_mode=metadata-only' "$status_file"
require_contains 'enforce_mode=future-closed' "$status_file"
require_contains 'bundled operator receipt report contract' "$status_file"

require_contains 'Status: product spine for Latticra Seal security-product direction' "$product_doc"
require_contains 'observe_mode=current' "$product_doc"
require_contains 'verify_mode=partial-local' "$product_doc"
require_contains 'decide_mode=metadata-only' "$product_doc"
require_contains 'handoff_mode=metadata-only' "$product_doc"
require_contains 'enforce_mode=future-closed' "$product_doc"
require_contains 'production_security_product=0' "$product_doc"
require_contains 'runtime_authority_granted=0' "$product_doc"
require_contains 'operator_receipt_report_implementation_plan_present=1' "$product_doc"
require_contains 'operator_receipt_report_implementation_present=1' "$product_doc"
require_contains 'operator_receipt_report_surface_present=1' "$product_doc"
require_contains 'operator_receipt_report_status_present=1' "$product_doc"
require_contains 'local_capability_registry_schema_contract_present=1' "$product_doc"
require_contains 'local_capability_registry_schema_implementation_plan_present=1' "$product_doc"
require_contains 'local_capability_registry_schema_implementation_present=1' "$product_doc"
require_contains 'local_capability_registry_schema_surface_present=1' "$product_doc"
require_contains 'local_capability_registry_schema_status_present=1' "$product_doc"
require_contains 'panel_dashboard_planning_checkpoint_present=1' "$product_doc"
require_contains 'panel_dashboard_planning_status_present=1' "$product_doc"
require_contains 'panel_dashboard_view_model_contract_present=1' "$product_doc"
require_contains 'panel_dashboard_view_model_contract_status_present=1' "$product_doc"
require_contains 'panel_dashboard_view_model_implementation_plan_present=1' "$product_doc"
require_contains 'panel_dashboard_view_model_implementation_plan_status_present=1' "$product_doc"
require_contains 'panel_dashboard_view_model_implementation_present=1' "$product_doc"
require_contains 'panel_dashboard_view_model_surface_present=1' "$product_doc"
require_contains 'panel_dashboard_view_model_status_present=1' "$product_doc"
require_contains 'signed_receipt_proof_path_implementation_present=1' "$product_doc"
require_contains 'signed_receipt_proof_path_status_present=1' "$product_doc"
require_contains 'seal_panel_dashboard=view-model-report-surface' "$product_doc"
require_contains 'seal_panel_dashboard_view_model=report-surface' "$product_doc"
require_contains 'seal_signed_receipt_proof_path=verification-only-implementation' "$product_doc"
require_contains 'bundled operator receipt report contract, implementation plan, implementation, report surface, and status record' "$status_file"
require_contains 'local capability registry schema contract, implementation plan, no-effect implementation, report surface, and status record are now current follow-up checkpoints' "$status_file"
require_contains 'Panel-visible Seal dashboard planning checkpoint and status record are now current follow-up checkpoints' "$status_file"
require_contains 'Seal Panel dashboard view-model contract and status record are now current follow-up checkpoints' "$status_file"
require_contains 'Seal Panel dashboard view-model implementation plan and status record are now current follow-up checkpoints' "$status_file"
require_contains 'Seal Panel dashboard view-model implementation is now a current follow-up checkpoint' "$status_file"
require_contains 'Seal Panel dashboard view-model surface/status checkpoint is now a current follow-up checkpoint' "$status_file"
require_contains 'Seal signed receipt proof path contract and verification-only implementation are now current follow-up checkpoints' "$status_file"
require_contains 'signed receipt proof path report surface/status checkpoint' "$status_file"

printf 'latticra seal product spine status: ok\n'
