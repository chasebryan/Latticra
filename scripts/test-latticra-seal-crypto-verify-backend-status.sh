#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal crypto verify backend status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal crypto verify backend status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_CRYPTO_VERIFY_BACKEND_STATUS.md"

require_file "$status_file"
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md
require_file docs/project_notes/README.md
require_file docs/LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_CONTRACT.md
require_file docs/LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_IMPLEMENTATION.md
require_file docs/status/SEAL_VERIFICATION_POLICY_STATUS.md
require_file include/latticra/seal_crypto_verify_backend.h
require_file src/seal_crypto_verify_backend.c
require_file tests/seal_crypto_verify_backend_invariants.c
require_file scripts/test-latticra-seal-crypto-verify-backend.sh

require_contains 'Status: status record for the Latticra Seal crypto verify backend readiness surface' "$status_file"
require_contains 'Source: local follow-up slice' "$status_file"
require_contains 'seal_crypto_verify_backend_contract_present=1' "$status_file"
require_contains 'seal_crypto_verify_backend_implementation_present=1' "$status_file"
require_contains 'seal_crypto_verify_backend_header_present=1' "$status_file"
require_contains 'seal_crypto_verify_backend_source_present=1' "$status_file"
require_contains 'seal_crypto_verify_backend_invariant_test_present=1' "$status_file"
require_contains 'seal_crypto_verify_backend_runner_present=1' "$status_file"
require_contains 'seal_crypto_verify_backend_status_present=1' "$status_file"
require_contains 'seal_verification_policy_status_present=1' "$status_file"
require_contains 'readme_links_crypto_verify_backend_contract=1' "$status_file"
require_contains 'readme_links_crypto_verify_backend_implementation=1' "$status_file"
require_contains 'readme_links_crypto_verify_backend_status=1' "$status_file"
require_contains 'root_status_mentions_crypto_verify_backend_status=1' "$status_file"
require_contains 'status_index_links_crypto_verify_backend_status=1' "$status_file"
require_contains 'foundation_index_links_crypto_verify_backend_status=1' "$status_file"
require_contains 'project_notes_mark_crypto_verify_backend_status_complete=1' "$status_file"
require_contains 'backend_profile=latticra-seal-crypto-verify-backend/0.1' "$status_file"
require_contains 'verification_policy_profile=latticra-seal-verification-policy/0.1' "$status_file"
require_contains 'signature_profile=latticra-seal-signature/0.1' "$status_file"
require_contains 'manifest_profile=latticra-seal-manifest/0.1' "$status_file"
require_contains 'artifact_digest_algorithm=SHA-256' "$status_file"
require_contains 'signature_algorithm=Ed25519-development' "$status_file"
require_contains 'trust_source=local-fixture' "$status_file"
require_contains 'crypto_verify_state=ready-local-ed25519' "$status_file"
require_contains 'cryptographic_verification_supported=1' "$status_file"
require_contains 'cryptographic_verification_performed=0' "$status_file"
require_contains 'verified=0' "$status_file"
require_contains 'invalid=0' "$status_file"
require_contains 'authority_usable=0' "$status_file"
require_contains 'capability_gate_allowed=0' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'mode=verify-backend-ready-authority-neutral' "$status_file"
require_contains 'status=crypto-verify-backend-ready' "$status_file"
require_contains 'error=ok' "$status_file"
require_contains 'implementation_behavior_changed=1' "$status_file"
require_contains 'backend_readiness_added=1' "$status_file"
require_contains 'signature_verification_performed_by_backend=0' "$status_file"
require_contains 'real_cryptographic_verification_added=0' "$status_file"
require_contains 'signing_added=0' "$status_file"
require_contains 'key_generation_added=0' "$status_file"
require_contains 'private_key_handling_added=0' "$status_file"
require_contains 'trust_store_behavior_added=0' "$status_file"
require_contains 'revocation_lookup_added=0' "$status_file"
require_contains 'network_behavior_changed=0' "$status_file"
require_contains 'host_behavior_changed=0' "$status_file"
require_contains 'capability_enforcement_added=0' "$status_file"
require_contains 'effect_execution_added=0' "$status_file"
require_contains 'seal crypto verify backend status: ok' "$status_file"
require_contains 'seal crypto verify backend invariants: ok' "$status_file"
require_contains 'Ed25519 verify-only implementation status/public-entry alignment' "$status_file"

require_contains 'ready authority-neutral crypto verify backend/status' README.md
require_contains 'seal_crypto_verify_backend_contract_present=1' README.md
require_contains 'seal_crypto_verify_backend_ready_present=1' README.md
require_contains 'seal_crypto_verify_backend_status_present=1' README.md
require_contains 'crypto_verify_state=ready-local-ed25519' README.md
require_contains 'docs/LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_CONTRACT.md' README.md
require_contains 'docs/LATTICRA_SEAL_CRYPTO_VERIFY_BACKEND_IMPLEMENTATION.md' README.md
require_contains 'docs/status/SEAL_CRYPTO_VERIFY_BACKEND_STATUS.md' README.md

require_contains 'Latest Seal crypto verify backend status/public-entry note: 2026-05-25 CDT' STATUS.md
require_contains 'Seal crypto verify backend status/public-entry alignment' STATUS.md
require_contains 'seal_crypto_verify_backend_status_present=1' STATUS.md
require_contains 'cryptographic_verification_supported=1' STATUS.md
require_contains 'cryptographic_verification_performed=0' STATUS.md
require_contains 'real_cryptographic_verification_added=0' STATUS.md

require_contains 'SEAL_CRYPTO_VERIFY_BACKEND_STATUS.md' docs/status/README.md
require_contains 'seal_crypto_verify_backend_status_present=1' docs/status/README.md
require_contains 'ready authority-neutral crypto verify backend/status' docs/status/README.md

require_contains 'Latest Seal crypto verify backend status/public-entry note: 2026-05-25 CDT' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal crypto verify backend status/public-entry alignment' docs/status/CURRENT_STATUS.md
require_contains 'seal_crypto_verify_backend_status_present=1' docs/status/CURRENT_STATUS.md
require_contains 'cryptographic_verification_supported=1' docs/status/CURRENT_STATUS.md
require_contains 'real_cryptographic_verification_added=0' docs/status/CURRENT_STATUS.md

require_contains 'SEAL_CRYPTO_VERIFY_BACKEND_STATUS.md' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal crypto verify backend status/public-entry alignment' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal crypto verify backend status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal crypto verify backend status/public-entry alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'docs/status/SEAL_CRYPTO_VERIFY_BACKEND_STATUS.md' docs/project_notes/README.md

printf 'seal crypto verify backend status: ok\n'
