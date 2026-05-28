#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal signed receipt proof path contract status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal signed receipt proof path contract status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_SIGNED_RECEIPT_PROOF_PATH_CONTRACT_STATUS.md"
contract="docs/LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_CONTRACT.md"
predecessor_status="docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATUS.md"
product_doc="docs/latticra-seal/PRODUCT.md"
seal_status="docs/latticra-seal/STATUS.md"

require_file "$status_file"
require_file "$contract"
require_file "$predecessor_status"
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
require_file scripts/test-latticra-seal-signed-receipt-proof-path-contract.sh
require_file scripts/test-latticra-seal-panel-dashboard-view-model-status.sh
require_file .github/workflows/latticra-seal-signed-receipt-proof-path-contract.yml
require_file .github/workflows/latticra-seal-signed-receipt-proof-path-contract-status.yml

require_contains 'Status: status record for the Latticra Seal signed receipt proof path contract' "$status_file"
require_contains 'seal_signed_receipt_proof_path_contract_present=1' "$status_file"
require_contains 'seal_signed_receipt_proof_path_contract_status_present=1' "$status_file"
require_contains 'signed_receipt_proof_path_predecessor_panel_dashboard_view_model_status_present=1' "$status_file"
require_contains 'signed_receipt_proof_path_profile=latticra-seal-signed-receipt-proof-path/0.1' "$status_file"
require_contains 'signed_receipt_proof_path_mode=contract-only' "$status_file"
require_contains 'signed_receipt_proof_path_status=not-implemented' "$status_file"
require_contains 'proof_path_scope=verification-only' "$status_file"
require_contains 'proof_path_authority=none' "$status_file"
require_contains 'verification_only_until_trust_root_and_revocation=1' "$status_file"
require_contains 'required_source_operator_receipt_report=1' "$status_file"
require_contains 'required_source_report_envelope=1' "$status_file"
require_contains 'required_source_signature_request=1' "$status_file"
require_contains 'required_source_verification_policy=1' "$status_file"
require_contains 'required_source_verification_receipt=1' "$status_file"
require_contains 'trust_root_required_for_promotion=1' "$status_file"
require_contains 'revocation_boundary_required_for_promotion=1' "$status_file"
require_contains 'crypto_backend_required_for_promotion=1' "$status_file"
require_contains 'operator_review_required=1' "$status_file"
require_contains 'implementation_behavior_changed=0' "$status_file"
require_contains 'runtime_behavior_added=0' "$status_file"
require_contains 'host_behavior_added=0' "$status_file"
require_contains 'network_behavior_added=0' "$status_file"
require_contains 'external_service_behavior_added=0' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'signed_receipt_proof_path_planning_only=1' "$status_file"
require_contains 'signed_receipt_proof_path_implemented=0' "$status_file"
require_contains 'signed_receipt_proof_path_report_surface_present=0' "$status_file"
require_contains 'signed_receipt_created=0' "$status_file"
require_contains 'signature_created=0' "$status_file"
require_contains 'signer_invoked=0' "$status_file"
require_contains 'signature_verification_performed=0' "$status_file"
require_contains 'cryptographic_verification_performed=0' "$status_file"
require_contains 'verified_receipt_authority=0' "$status_file"
require_contains 'capability_gate_allowed=0' "$status_file"
require_contains 'effect_performed=0' "$status_file"
require_contains 'host_read_performed=0' "$status_file"
require_contains 'host_write_performed=0' "$status_file"
require_contains 'network_performed=0' "$status_file"
require_contains 'proof_path_state=missing-evidence' "$status_file"
require_contains 'proof_path_state=malformed-evidence' "$status_file"
require_contains 'proof_path_state=unsupported-trust-root' "$status_file"
require_contains 'proof_path_state=unsupported-revocation' "$status_file"
require_contains 'proof_path_state=unverified-metadata' "$status_file"
require_contains 'proof_path_state=verification-only-blocked' "$status_file"
require_contains 'The signed receipt proof path implementation is now represented by `docs/LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_IMPLEMENTATION.md`.' "$status_file"
require_contains 'The current next valid Latticra Seal slice is a signed receipt proof path report surface/status checkpoint that remains verification-only until trust-root and revocation boundaries are implemented.' "$status_file"
require_contains 'sh scripts/test-latticra-seal-signed-receipt-proof-path-contract-status.sh' .github/workflows/latticra-seal-signed-receipt-proof-path-contract-status.yml
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' .github/workflows/latticra-seal-signed-receipt-proof-path-contract-status.yml

require_contains 'signed_receipt_proof_path_contract=1' "$product_doc"
require_contains 'signed_receipt_proof_path_contract_status=1' "$product_doc"
require_contains 'signed_receipt_proof_path_contract_present=1' "$product_doc"
require_contains 'signed_receipt_proof_path_contract_status_present=1' "$product_doc"
require_contains 'signed_receipt_proof_path_implementation=1' "$product_doc"
require_contains 'signed receipt proof path report surface/status checkpoint' "$product_doc"
require_contains 'signed_receipt_proof_path_contract_present=1' "$seal_status"
require_contains 'signed_receipt_proof_path_contract_status_present=1' "$seal_status"
require_contains 'seal_signed_receipt_proof_path_contract_present=1' README.md
require_contains 'seal_signed_receipt_proof_path_contract_status_present=1' README.md
require_contains 'signed_receipt_proof_path_predecessor_panel_dashboard_view_model_status_present=1' README.md
require_contains 'docs/LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_CONTRACT.md' README.md
require_contains 'docs/status/SEAL_SIGNED_RECEIPT_PROOF_PATH_CONTRACT_STATUS.md' README.md
require_contains 'Latest Seal signed receipt proof path contract note: 2026-05-28 CDT' STATUS.md
require_contains 'Latest Seal signed receipt proof path contract note: 2026-05-28 CDT' docs/status/CURRENT_STATUS.md
require_contains 'Current Seal signed receipt proof path contract boundary' STATUS.md
require_contains 'Current Seal signed receipt proof path contract fields:' docs/status/CURRENT_STATUS.md
require_contains 'SEAL_SIGNED_RECEIPT_PROOF_PATH_CONTRACT_STATUS.md' docs/status/README.md
require_contains 'LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_CONTRACT.md' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal signed receipt proof path contract' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal signed receipt proof path contract' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/status/SEAL_SIGNED_RECEIPT_PROOF_PATH_CONTRACT_STATUS.md' docs/project_notes/README.md

sh scripts/test-latticra-seal-signed-receipt-proof-path-contract.sh
sh scripts/test-latticra-seal-panel-dashboard-view-model-status.sh

printf 'latticra seal signed receipt proof path contract status: ok\n'
