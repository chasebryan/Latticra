#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal signed receipt proof path status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal signed receipt proof path status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_SIGNED_RECEIPT_PROOF_PATH_STATUS.md"
implementation_doc="docs/LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_IMPLEMENTATION.md"
contract_status="docs/status/SEAL_SIGNED_RECEIPT_PROOF_PATH_CONTRACT_STATUS.md"
product_doc="docs/latticra-seal/PRODUCT.md"
seal_status="docs/latticra-seal/STATUS.md"

require_file "$status_file"
require_file "$implementation_doc"
require_file "$contract_status"
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
require_file include/latticra/seal_signed_receipt_proof_path.h
require_file src/seal_signed_receipt_proof_path.c
require_file tests/seal_signed_receipt_proof_path_invariants.c
require_file scripts/test-latticra-seal-signed-receipt-proof-path.sh
require_file .github/workflows/latticra-seal-signed-receipt-proof-path.yml
require_file .github/workflows/latticra-seal-signed-receipt-proof-path-status.yml

require_contains 'Status: status record for the Latticra Seal signed receipt proof path implementation' "$status_file"
require_contains 'seal_signed_receipt_proof_path_contract_present=1' "$status_file"
require_contains 'seal_signed_receipt_proof_path_contract_status_present=1' "$status_file"
require_contains 'seal_signed_receipt_proof_path_implementation_present=1' "$status_file"
require_contains 'seal_signed_receipt_proof_path_header_present=1' "$status_file"
require_contains 'seal_signed_receipt_proof_path_source_present=1' "$status_file"
require_contains 'seal_signed_receipt_proof_path_invariant_test_present=1' "$status_file"
require_contains 'seal_signed_receipt_proof_path_runner_present=1' "$status_file"
require_contains 'seal_signed_receipt_proof_path_status_present=1' "$status_file"
require_contains 'signed_receipt_proof_path_predecessor_contract_status_present=1' "$status_file"
require_contains 'signed_receipt_proof_path_profile=latticra-seal-signed-receipt-proof-path/0.1' "$status_file"
require_contains 'signed_receipt_proof_path_mode=verification-only' "$status_file"
require_contains 'signed_receipt_proof_path_status=implemented-no-effect' "$status_file"
require_contains 'local_verify_result_present=1' "$status_file"
require_contains 'receipt_promotion_present=1' "$status_file"
require_contains 'signing_operation_present=1' "$status_file"
require_contains 'receipt_verified=1' "$status_file"
require_contains 'digest_matches=1' "$status_file"
require_contains 'public_key_matches=1' "$status_file"
require_contains 'trust_root_required=1' "$status_file"
require_contains 'trust_root_verified=0' "$status_file"
require_contains 'revocation_required=1' "$status_file"
require_contains 'revocation_checked=0' "$status_file"
require_contains 'verification_only=1' "$status_file"
require_contains 'proof_path_verified=0' "$status_file"
require_contains 'authority_usable=0' "$status_file"
require_contains 'capability_gate_allowed=0' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'signature_performed=0' "$status_file"
require_contains 'signer_invoked=0' "$status_file"
require_contains 'private_key_handling=0' "$status_file"
require_contains 'key_generation_performed=0' "$status_file"
require_contains 'trust_store_loaded=0' "$status_file"
require_contains 'revocation_lookup_performed=0' "$status_file"
require_contains 'handoff_performed=0' "$status_file"
require_contains 'effect_performed=0' "$status_file"
require_contains 'host_read_performed=0' "$status_file"
require_contains 'host_write_performed=0' "$status_file"
require_contains 'network_performed=0' "$status_file"
require_contains 'signed receipt proof path report surface/status checkpoint' "$status_file"
require_contains 'Status: bounded verification-only implementation for the Latticra Seal signed receipt proof path' "$implementation_doc"
require_contains 'digest-mismatch' "$implementation_doc"
require_contains 'public-key-mismatch' "$implementation_doc"
require_contains 'receipt-authority-not-neutral' "$implementation_doc"
require_contains 'trust_root_verified=0' "$implementation_doc"
require_contains 'revocation_checked=0' "$implementation_doc"
require_contains 'proof_path_verified=0' "$implementation_doc"
require_contains 'signature_performed=0' "$implementation_doc"
require_contains 'network_performed=0' "$implementation_doc"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' .github/workflows/latticra-seal-signed-receipt-proof-path.yml
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' .github/workflows/latticra-seal-signed-receipt-proof-path-status.yml
require_contains 'sh scripts/test-latticra-seal-signed-receipt-proof-path-status.sh' .github/workflows/latticra-seal-signed-receipt-proof-path-status.yml

require_contains 'signed_receipt_proof_path_implementation=1' "$product_doc"
require_contains 'signed_receipt_proof_path_status=1' "$product_doc"
require_contains 'signed_receipt_proof_path_implementation_present=1' "$product_doc"
require_contains 'signed_receipt_proof_path_status_present=1' "$product_doc"
require_contains 'seal_signed_receipt_proof_path=verification-only-implementation' "$product_doc"
require_contains 'signed receipt proof path report surface/status checkpoint' "$product_doc"
require_contains 'signed_receipt_proof_path_implementation_present=1' "$seal_status"
require_contains 'signed_receipt_proof_path_status_present=1' "$seal_status"
require_contains 'seal_signed_receipt_proof_path_implementation_present=1' README.md
require_contains 'seal_signed_receipt_proof_path_status_present=1' README.md
require_contains 'signed_receipt_proof_path_predecessor_contract_status_present=1' README.md
require_contains 'docs/LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_IMPLEMENTATION.md' README.md
require_contains 'docs/status/SEAL_SIGNED_RECEIPT_PROOF_PATH_STATUS.md' README.md
require_contains 'Latest Seal signed receipt proof path implementation note: 2026-05-28 CDT' STATUS.md
require_contains 'Latest Seal signed receipt proof path implementation note: 2026-05-28 CDT' docs/status/CURRENT_STATUS.md
require_contains 'Current Seal signed receipt proof path implementation boundary' STATUS.md
require_contains 'Current Seal signed receipt proof path implementation fields:' docs/status/CURRENT_STATUS.md
require_contains 'SEAL_SIGNED_RECEIPT_PROOF_PATH_STATUS.md' docs/status/README.md
require_contains 'LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_IMPLEMENTATION.md' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal signed receipt proof path implementation' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal signed receipt proof path implementation' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/status/SEAL_SIGNED_RECEIPT_PROOF_PATH_STATUS.md' docs/project_notes/README.md

sh scripts/test-latticra-seal-signed-receipt-proof-path.sh
sh scripts/test-latticra-seal-signed-receipt-proof-path-contract-status.sh

printf 'latticra seal signed receipt proof path status: ok\n'
