#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal signed receipt proof path surface status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal signed receipt proof path surface status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_SIGNED_RECEIPT_PROOF_PATH_SURFACE_STATUS.md"
surface_doc="docs/LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_SURFACE.md"
implementation_status="docs/status/SEAL_SIGNED_RECEIPT_PROOF_PATH_STATUS.md"
product_doc="docs/latticra-seal/PRODUCT.md"
seal_status="docs/latticra-seal/STATUS.md"

require_file "$status_file"
require_file "$surface_doc"
require_file "$implementation_status"
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
require_file tests/seal_signed_receipt_proof_path_surface.c
require_file scripts/latticra-seal-signed-receipt-proof-path.sh
require_file scripts/test-latticra-seal-signed-receipt-proof-path-surface.sh
require_file scripts/test-latticra-seal-signed-receipt-proof-path-status.sh
require_file .github/workflows/latticra-seal-signed-receipt-proof-path-surface.yml
require_file .github/workflows/latticra-seal-signed-receipt-proof-path-surface-status.yml

require_contains 'Status: status record for the Latticra Seal signed receipt proof path report surface' "$status_file"
require_contains 'seal_signed_receipt_proof_path_implementation_present=1' "$status_file"
require_contains 'seal_signed_receipt_proof_path_status_present=1' "$status_file"
require_contains 'seal_signed_receipt_proof_path_surface_present=1' "$status_file"
require_contains 'seal_signed_receipt_proof_path_surface_status_present=1' "$status_file"
require_contains 'signed_receipt_proof_path_surface_predecessor_implementation_status_present=1' "$status_file"
require_contains 'signed_receipt_proof_path_surface_document_present=1' "$status_file"
require_contains 'signed_receipt_proof_path_surface_fixture_present=1' "$status_file"
require_contains 'signed_receipt_proof_path_surface_runner_present=1' "$status_file"
require_contains 'signed_receipt_proof_path_surface_guard_present=1' "$status_file"
require_contains 'signed_receipt_proof_path_surface_workflow_present=1' "$status_file"
require_contains 'uses_local_deterministic_fixture=1' "$status_file"
require_contains 'signed_receipt_proof_path_mode=verification-only' "$status_file"
require_contains 'fixture_receipt_promotion_present=1' "$status_file"
require_contains 'fixture_signing_operation_present=1' "$status_file"
require_contains 'report_file_loading_supported=0' "$status_file"
require_contains 'trust_root_loading_supported=0' "$status_file"
require_contains 'revocation_lookup_supported=0' "$status_file"
require_contains 'signature_creation_supported=0' "$status_file"
require_contains 'signature_verification_supported=0' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'effect_performed=0' "$status_file"
require_contains 'host_read_performed=0' "$status_file"
require_contains 'host_write_performed=0' "$status_file"
require_contains 'network_performed=0' "$status_file"
require_contains 'LATTICRA SEAL SIGNED RECEIPT PROOF PATH' "$status_file"
require_contains 'proof_path_profile=latticra-seal-signed-receipt-proof-path/0.1' "$status_file"
require_contains 'proof_path_state=verification-only' "$status_file"
require_contains 'digest_matches=1' "$status_file"
require_contains 'public_key_matches=1' "$status_file"
require_contains 'trust_root_required=1' "$status_file"
require_contains 'trust_root_verified=0' "$status_file"
require_contains 'revocation_required=1' "$status_file"
require_contains 'revocation_checked=0' "$status_file"
require_contains 'proof_path_verified=0' "$status_file"
require_contains 'authority_usable=0' "$status_file"
require_contains 'signature_performed=0' "$status_file"
require_contains 'signer_invoked=0' "$status_file"
require_contains 'private_key_handling=0' "$status_file"
require_contains 'trust_store_loaded=0' "$status_file"
require_contains 'revocation_lookup_performed=0' "$status_file"
require_contains 'error=ok' "$status_file"
require_contains 'status=signed-receipt-proof-path-verification-only' "$status_file"
require_contains 'The signed receipt proof path surface is now represented by `docs/LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_SURFACE.md`, with status in `docs/status/SEAL_SIGNED_RECEIPT_PROOF_PATH_SURFACE_STATUS.md`.' "$status_file"
require_contains 'The next valid Latticra Seal slice is a signed receipt trust-root boundary contract' "$status_file"
require_contains 'sh scripts/test-latticra-seal-signed-receipt-proof-path-surface-status.sh' .github/workflows/latticra-seal-signed-receipt-proof-path-surface-status.yml
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' .github/workflows/latticra-seal-signed-receipt-proof-path-surface-status.yml

require_contains 'signed_receipt_proof_path_surface=1' "$product_doc"
require_contains 'signed_receipt_proof_path_surface_status=1' "$product_doc"
require_contains 'signed_receipt_proof_path_surface_present=1' "$product_doc"
require_contains 'signed_receipt_proof_path_surface_status_present=1' "$product_doc"
require_contains 'seal_signed_receipt_proof_path=verification-only-report-surface' "$product_doc"
require_contains 'signed receipt trust-root boundary contract' "$product_doc"
require_contains 'signed_receipt_proof_path_surface_present=1' "$seal_status"
require_contains 'signed_receipt_proof_path_surface_status_present=1' "$seal_status"
require_contains 'seal_signed_receipt_proof_path_surface_present=1' README.md
require_contains 'seal_signed_receipt_proof_path_surface_status_present=1' README.md
require_contains 'signed_receipt_proof_path_surface_predecessor_implementation_status_present=1' README.md
require_contains 'docs/LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_SURFACE.md' README.md
require_contains 'docs/status/SEAL_SIGNED_RECEIPT_PROOF_PATH_SURFACE_STATUS.md' README.md
require_contains 'Latest Seal signed receipt proof path surface/status note: 2026-05-28 CDT' STATUS.md
require_contains 'Latest Seal signed receipt proof path surface/status note: 2026-05-28 CDT' docs/status/CURRENT_STATUS.md
require_contains 'Current Seal signed receipt proof path surface boundary' STATUS.md
require_contains 'Current Seal signed receipt proof path surface fields:' docs/status/CURRENT_STATUS.md
require_contains 'SEAL_SIGNED_RECEIPT_PROOF_PATH_SURFACE_STATUS.md' docs/status/README.md
require_contains 'LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_SURFACE.md' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal signed receipt proof path surface/status' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal signed receipt proof path surface/status' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/status/SEAL_SIGNED_RECEIPT_PROOF_PATH_SURFACE_STATUS.md' docs/project_notes/README.md

sh scripts/test-latticra-seal-signed-receipt-proof-path-status.sh
sh scripts/test-latticra-seal-signed-receipt-proof-path-surface.sh

printf 'latticra seal signed receipt proof path surface status: ok\n'
