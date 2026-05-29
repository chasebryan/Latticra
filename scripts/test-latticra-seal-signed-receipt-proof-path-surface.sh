#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal signed receipt proof path surface: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal signed receipt proof path surface: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

surface_doc="docs/LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_SURFACE.md"
output_file="$(mktemp "${TMPDIR:-/tmp}/latticra-seal-signed-receipt-proof-path-surface.XXXXXX")"
trap 'rm -f "$output_file"' EXIT INT HUP TERM

require_file "$surface_doc"
require_file docs/LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_IMPLEMENTATION.md
require_file docs/status/SEAL_SIGNED_RECEIPT_PROOF_PATH_STATUS.md
require_file include/latticra/seal_signed_receipt_proof_path.h
require_file src/seal_signed_receipt_proof_path.c
require_file tests/seal_signed_receipt_proof_path_surface.c
require_file scripts/latticra-seal-signed-receipt-proof-path.sh

require_contains 'Status: report surface for the Latticra Seal signed receipt proof path' "$surface_doc"
require_contains 'tests/seal_signed_receipt_proof_path_surface.c' "$surface_doc"
require_contains 'scripts/latticra-seal-signed-receipt-proof-path.sh' "$surface_doc"
require_contains 'signed_receipt_proof_path_mode=verification-only' "$surface_doc"
require_contains 'signed_receipt_proof_path_surface_present=1' "$surface_doc"
require_contains 'uses_local_deterministic_fixture=1' "$surface_doc"
require_contains 'trust_root_verified=0' "$surface_doc"
require_contains 'revocation_checked=0' "$surface_doc"
require_contains 'signature_performed=0' "$surface_doc"
require_contains 'signer_invoked=0' "$surface_doc"
require_contains 'runtime_authority_granted=0' "$surface_doc"
require_contains 'effect_performed=0' "$surface_doc"
require_contains 'network_performed=0' "$surface_doc"
require_contains 'The next valid Latticra Seal slice is a signed receipt trust-root boundary contract' "$surface_doc"
require_contains 'latticra_seal_signed_receipt_proof_path_render' tests/seal_signed_receipt_proof_path_surface.c
require_contains 'LATTICRA SEAL SIGNED RECEIPT PROOF PATH' src/seal_signed_receipt_proof_path.c

sh scripts/latticra-seal-signed-receipt-proof-path.sh > "$output_file"

require_contains 'LATTICRA SEAL SIGNED RECEIPT PROOF PATH' "$output_file"
require_contains 'proof_path_profile=latticra-seal-signed-receipt-proof-path/0.1' "$output_file"
require_contains 'receipt_profile=latticra-seal-verified-receipt/0.1' "$output_file"
require_contains 'verify_profile=latticra-seal-ed25519-verify/0.1' "$output_file"
require_contains 'signing_operation_profile=latticra-seal-signing-operation/0.1' "$output_file"
require_contains 'proof_path_state=verification-only' "$output_file"
require_contains 'local_verify_result_present=1' "$output_file"
require_contains 'receipt_promotion_present=1' "$output_file"
require_contains 'signing_operation_present=1' "$output_file"
require_contains 'receipt_verified=1' "$output_file"
require_contains 'digest_matches=1' "$output_file"
require_contains 'public_key_matches=1' "$output_file"
require_contains 'trust_root_required=1' "$output_file"
require_contains 'trust_root_verified=0' "$output_file"
require_contains 'revocation_required=1' "$output_file"
require_contains 'revocation_checked=0' "$output_file"
require_contains 'verification_only=1' "$output_file"
require_contains 'proof_path_verified=0' "$output_file"
require_contains 'authority_usable=0' "$output_file"
require_contains 'capability_gate_allowed=0' "$output_file"
require_contains 'runtime_authority_granted=0' "$output_file"
require_contains 'signature_performed=0' "$output_file"
require_contains 'signer_invoked=0' "$output_file"
require_contains 'private_key_handling=0' "$output_file"
require_contains 'key_generation_performed=0' "$output_file"
require_contains 'trust_store_loaded=0' "$output_file"
require_contains 'revocation_lookup_performed=0' "$output_file"
require_contains 'handoff_performed=0' "$output_file"
require_contains 'effect_performed=0' "$output_file"
require_contains 'host_read_performed=0' "$output_file"
require_contains 'host_write_performed=0' "$output_file"
require_contains 'network_performed=0' "$output_file"
require_contains 'error=ok' "$output_file"
require_contains 'status=signed-receipt-proof-path-verification-only' "$output_file"

printf 'latticra seal signed receipt proof path surface: ok\n'
