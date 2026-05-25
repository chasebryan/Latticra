#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal signing operation contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal signing operation contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_SIGNING_OPERATION_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_SIGNER_INVOCATION_CONTRACT.md
require_file docs/LATTICRA_SEAL_SIGNER_INVOCATION_IMPLEMENTATION.md
require_file docs/status/SEAL_SIGNER_INVOCATION_STATUS.md
require_file include/latticra/seal_signer_invocation.h
require_file src/seal_signer_invocation.c
require_file tests/seal_signer_invocation_invariants.c
require_file scripts/test-latticra-seal-signer-invocation-contract.sh
require_file scripts/test-latticra-seal-signer-invocation.sh
require_file scripts/test-latticra-seal-signer-invocation-status.sh
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md

require_contains 'Status: Latticra Seal signing operation contract' "$contract"
require_contains 'The signing operation surface is signing-operation path classification, not signing, not verification, not signer invocation, and not runtime handoff.' "$contract"
require_contains 'This document does not sign.' "$contract"
require_contains 'This document does not handle private keys.' "$contract"
require_contains 'signer_invocation_ready=1' "$contract"
require_contains 'signer_invocation_state=invocation-metadata-only' "$contract"
require_contains 'requested_signature=Ed25519-development' "$contract"
require_contains 'requested_signing_authorization=metadata-only' "$contract"
require_contains 'requested_signer_handoff=metadata-only' "$contract"
require_contains 'requested_signer_invocation=metadata-only' "$contract"
require_contains 'requested_signing_operation=metadata-only' "$contract"
require_contains 'signing_operation_state=operation-metadata-only' "$contract"
require_contains 'signing_operation_ready=1' "$contract"
require_contains 'signature_performed=0' "$contract"
require_contains 'verification_performed=0' "$contract"
require_contains 'signer_invoked=0' "$contract"
require_contains 'private_key_handling=0' "$contract"
require_contains 'key_generation_performed=0' "$contract"
require_contains 'trust_store_loaded=0' "$contract"
require_contains 'revocation_lookup_performed=0' "$contract"
require_contains 'runtime_authority_granted=0' "$contract"
require_contains 'host_read_performed=0' "$contract"
require_contains 'host_write_performed=0' "$contract"
require_contains 'network_performed=0' "$contract"
require_contains 'signing operation metadata implementation' "$contract"

require_contains 'LATTICRA_SEAL_SIGNING_OPERATION_CONTRACT.md' README.md
require_contains 'latticra_seal_signing_operation_contract_present=1' README.md
require_contains 'seal_signing_operation_contract_present=1' README.md
require_contains 'Seal signing operation contract' STATUS.md
require_contains 'seal_signing_operation_contract_present=1' STATUS.md
require_contains 'seal_signing_operation_contract_present=1' docs/status/README.md
require_contains 'Latticra Seal signing operation contract' docs/status/CURRENT_STATUS.md
require_contains 'LATTICRA_SEAL_SIGNING_OPERATION_CONTRACT.md' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal signing operation contract' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Signing operation metadata implementation' docs/project_notes/UPCOMING_WORK.md

printf 'seal signing operation contract: ok\n'
