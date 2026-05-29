#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal ed25519 verify status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal ed25519 verify status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_ED25519_VERIFY_STATUS.md"

require_file "$status_file"
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md
require_file docs/project_notes/README.md
require_file docs/LATTICRA_SEAL_ED25519_VERIFY_ONLY_CONTRACT.md
require_file docs/LATTICRA_SEAL_ED25519_VERIFY_IMPLEMENTATION.md
require_file docs/status/SEAL_CRYPTO_VERIFY_BACKEND_STATUS.md
require_file include/latticra/seal_ed25519_verify.h
require_file src/seal_ed25519_verify.c
require_file tests/seal_ed25519_verify_invariants.c
require_file scripts/test-latticra-seal-ed25519-verify-only-contract.sh
require_file scripts/test-latticra-seal-ed25519-verify.sh

require_contains 'Status: status record for the Latticra Seal Ed25519 verify-only result surface' "$status_file"
require_contains 'Source: local follow-up slice' "$status_file"
require_contains 'seal_ed25519_verify_only_contract_present=1' "$status_file"
require_contains 'seal_ed25519_verify_implementation_present=1' "$status_file"
require_contains 'seal_ed25519_verify_header_present=1' "$status_file"
require_contains 'seal_ed25519_verify_source_present=1' "$status_file"
require_contains 'seal_ed25519_verify_invariant_test_present=1' "$status_file"
require_contains 'seal_ed25519_verify_runner_present=1' "$status_file"
require_contains 'seal_ed25519_verify_status_present=1' "$status_file"
require_contains 'seal_crypto_verify_backend_status_present=1' "$status_file"
require_contains 'readme_links_ed25519_verify_contract=1' "$status_file"
require_contains 'readme_links_ed25519_verify_implementation=1' "$status_file"
require_contains 'readme_links_ed25519_verify_status=1' "$status_file"
require_contains 'root_status_mentions_ed25519_verify_status=1' "$status_file"
require_contains 'status_index_links_ed25519_verify_status=1' "$status_file"
require_contains 'foundation_index_links_ed25519_verify_status=1' "$status_file"
require_contains 'project_notes_mark_ed25519_verify_status_complete=1' "$status_file"
require_contains 'ed25519_verify_profile=latticra-seal-ed25519-verify/0.1' "$status_file"
require_contains 'backend_profile=latticra-seal-crypto-verify-backend/0.1' "$status_file"
require_contains 'verification_policy_profile=latticra-seal-verification-policy/0.1' "$status_file"
require_contains 'message_label=rfc8032-test-vector-2' "$status_file"
require_contains 'message_size_bytes=1' "$status_file"
require_contains 'message_digest_algorithm=SHA-256' "$status_file"
require_contains 'public_key_identity_label=rfc8032-test-key' "$status_file"
require_contains 'public_key_size_bytes=32' "$status_file"
require_contains 'signature_algorithm=Ed25519-development' "$status_file"
require_contains 'signature_size_bytes=64' "$status_file"
require_contains 'trust_source=local-test-vector' "$status_file"
require_contains 'crypto_verify_state=verified' "$status_file"
require_contains 'cryptographic_verification_supported=1' "$status_file"
require_contains 'cryptographic_verification_performed=1' "$status_file"
require_contains 'verified=1' "$status_file"
require_contains 'invalid=0' "$status_file"
require_contains 'authority_usable=0' "$status_file"
require_contains 'capability_gate_allowed=0' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'mode=verify-only-authority-neutral' "$status_file"
require_contains 'status=ed25519-verified' "$status_file"
require_contains 'error=ok' "$status_file"
require_contains 'local_ed25519_verification_added=1' "$status_file"
require_contains 'signing_added=0' "$status_file"
require_contains 'key_generation_added=0' "$status_file"
require_contains 'private_key_handling_added=0' "$status_file"
require_contains 'trust_store_behavior_added=0' "$status_file"
require_contains 'revocation_lookup_added=0' "$status_file"
require_contains 'network_behavior_changed=0' "$status_file"
require_contains 'host_behavior_changed=0' "$status_file"
require_contains 'capability_enforcement_added=0' "$status_file"
require_contains 'effect_execution_added=0' "$status_file"
require_contains 'seal ed25519 verify status: ok' "$status_file"
require_contains 'seal ed25519 verify invariants: ok' "$status_file"
require_contains 'verified receipt promotion status/public-entry alignment' "$status_file"

require_contains 'local Ed25519 verify-only implementation/status' README.md
require_contains 'seal_ed25519_verify_only_contract_present=1' README.md
require_contains 'seal_ed25519_verify_implementation_present=1' README.md
require_contains 'seal_ed25519_verify_status_present=1' README.md
require_contains 'ed25519_cryptographic_verification_performed=1' README.md
require_contains 'ed25519_verified=1' README.md
require_contains 'ed25519_authority_usable=0' README.md
require_contains 'docs/LATTICRA_SEAL_ED25519_VERIFY_ONLY_CONTRACT.md' README.md
require_contains 'docs/LATTICRA_SEAL_ED25519_VERIFY_IMPLEMENTATION.md' README.md
require_contains 'docs/status/SEAL_ED25519_VERIFY_STATUS.md' README.md

require_contains 'Latest Seal Ed25519 verify status/public-entry note: 2026-05-25 CDT' STATUS.md
require_contains 'Seal Ed25519 verify-only status/public-entry alignment' STATUS.md
require_contains 'seal_ed25519_verify_status_present=1' STATUS.md
require_contains 'ed25519_cryptographic_verification_performed=1' STATUS.md
require_contains 'ed25519_authority_usable=0' STATUS.md

require_contains 'SEAL_ED25519_VERIFY_STATUS.md' docs/status/README.md
require_contains 'seal_ed25519_verify_status_present=1' docs/status/README.md
require_contains 'local Ed25519 verify-only implementation/status' docs/status/README.md

require_contains 'Latest Seal Ed25519 verify status/public-entry note: 2026-05-25 CDT' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal Ed25519 verify-only status/public-entry alignment' docs/status/CURRENT_STATUS.md
require_contains 'seal_ed25519_verify_status_present=1' docs/status/CURRENT_STATUS.md
require_contains 'ed25519_cryptographic_verification_performed=1' docs/status/CURRENT_STATUS.md
require_contains 'ed25519_authority_usable=0' docs/status/CURRENT_STATUS.md

require_contains 'SEAL_ED25519_VERIFY_STATUS.md' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal Ed25519 verify-only status/public-entry alignment' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal Ed25519 verify-only status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal Ed25519 verify-only status/public-entry alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/status/SEAL_ED25519_VERIFY_STATUS.md' docs/project_notes/README.md

printf 'seal ed25519 verify status: ok\n'
