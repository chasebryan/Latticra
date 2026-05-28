#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra seal signed receipt proof path contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal signed receipt proof path contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_PANEL_DASHBOARD_VIEW_MODEL_SURFACE.md
require_file docs/status/SEAL_PANEL_DASHBOARD_VIEW_MODEL_STATUS.md
require_file docs/LATTICRA_SEAL_OPERATOR_RECEIPT_REPORT_SURFACE.md
require_file docs/status/SEAL_OPERATOR_RECEIPT_REPORT_STATUS.md
require_file docs/LATTICRA_SEAL_REPORT_ENVELOPE_IMPLEMENTATION.md
require_file docs/status/SEAL_SIGNATURE_REQUEST_STATUS.md
require_file docs/status/SEAL_VERIFICATION_POLICY_STATUS.md
require_file docs/status/SEAL_VERIFICATION_RECEIPT_STATUS.md
require_file docs/status/SEAL_CRYPTO_VERIFY_BACKEND_STATUS.md
require_file docs/status/SEAL_ED25519_VERIFY_STATUS.md

require_contains 'Status: contract for a future verification-only Latticra Seal signed receipt proof path' "$contract"
require_contains 'signed_receipt_proof_path_profile=latticra-seal-signed-receipt-proof-path/0.1' "$contract"
require_contains 'signed_receipt_proof_path_mode=contract-only' "$contract"
require_contains 'signed_receipt_proof_path_status=not-implemented' "$contract"
require_contains 'proof_path_scope=verification-only' "$contract"
require_contains 'proof_path_authority=none' "$contract"
require_contains 'signed_receipt_proof_path_contract_present=1' "$contract"
require_contains 'signed_receipt_proof_path_planning_only=1' "$contract"
require_contains 'signed_receipt_proof_path_implemented=0' "$contract"
require_contains 'signed_receipt_proof_path_report_surface_present=0' "$contract"
require_contains 'verification_only_until_trust_root_and_revocation=1' "$contract"
require_contains 'receipt_digest_required=1' "$contract"
require_contains 'signature_request_required=1' "$contract"
require_contains 'verification_policy_required=1' "$contract"
require_contains 'verification_receipt_required=1' "$contract"
require_contains 'trust_root_required_for_promotion=1' "$contract"
require_contains 'revocation_boundary_required_for_promotion=1' "$contract"
require_contains 'crypto_backend_required_for_promotion=1' "$contract"
require_contains 'operator_review_required=1' "$contract"
require_contains 'signed_receipt_created=0' "$contract"
require_contains 'signature_created=0' "$contract"
require_contains 'signer_invoked=0' "$contract"
require_contains 'signature_verification_performed=0' "$contract"
require_contains 'cryptographic_verification_performed=0' "$contract"
require_contains 'verified_receipt_authority=0' "$contract"
require_contains 'capability_gate_allowed=0' "$contract"
require_contains 'runtime_authority_granted=0' "$contract"
require_contains 'effect_performed=0' "$contract"
require_contains 'host_read_performed=0' "$contract"
require_contains 'host_write_performed=0' "$contract"
require_contains 'network_performed=0' "$contract"
require_contains 'required_source_operator_receipt_report=1' "$contract"
require_contains 'required_source_report_envelope=1' "$contract"
require_contains 'required_source_signature_request=1' "$contract"
require_contains 'required_source_verification_policy=1' "$contract"
require_contains 'required_source_verification_receipt=1' "$contract"
require_contains 'proof_path_state=missing-evidence' "$contract"
require_contains 'proof_path_state=malformed-evidence' "$contract"
require_contains 'proof_path_state=unsupported-trust-root' "$contract"
require_contains 'proof_path_state=unsupported-revocation' "$contract"
require_contains 'proof_path_state=unverified-metadata' "$contract"
require_contains 'proof_path_state=verification-only-blocked' "$contract"
require_contains 'The future proof path must not report `verified`, `trusted`, `authority-usable`, `capability-allowed`, or `runtime-allowed` states under this contract.' "$contract"
require_contains 'signature verification' "$contract"
require_contains 'trust-root loading' "$contract"
require_contains 'revocation lookup' "$contract"
require_contains 'turning receipt evidence into execution grants' "$contract"
require_contains 'turning receipt evidence into effect grants' "$contract"
require_contains 'This contract does not authorize a signed receipt proof implementation.' "$contract"
require_contains 'The signed receipt proof path implementation is now represented by `docs/LATTICRA_SEAL_SIGNED_RECEIPT_PROOF_PATH_IMPLEMENTATION.md`.' "$contract"
require_contains 'The current next valid Latticra Seal slice is a signed receipt proof path report surface/status checkpoint that remains verification-only until trust-root and revocation boundaries are implemented.' "$contract"

printf 'latticra seal signed receipt proof path contract: ok\n'
