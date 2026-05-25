#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal key-handling contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal key-handling contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_KEY_HANDLING_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_KEY_HANDLING_IMPLEMENTATION.md
require_file docs/status/SEAL_KEY_HANDLING_STATUS.md
require_file include/latticra/seal_key_handling.h
require_file src/seal_key_handling.c
require_file tests/seal_key_handling_invariants.c
require_file scripts/test-latticra-seal-key-handling.sh
require_file scripts/test-latticra-seal-key-handling-status.sh
require_file docs/LATTICRA_SEAL_SIGNING_OPERATION_CONTRACT.md
require_file docs/LATTICRA_SEAL_SIGNING_OPERATION_IMPLEMENTATION.md
require_file docs/status/SEAL_SIGNING_OPERATION_STATUS.md
require_file include/latticra/seal_signing_operation.h
require_file src/seal_signing_operation.c
require_file tests/seal_signing_operation_invariants.c
require_file scripts/test-latticra-seal-signing-operation-contract.sh
require_file scripts/test-latticra-seal-signing-operation.sh
require_file scripts/test-latticra-seal-signing-operation-status.sh
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md

require_contains 'Status: Latticra Seal key-handling boundary contract' "$contract"
require_contains 'The key-handling surface is key-handling path classification, not key handling, not signing, not verification, and not trust-store behavior.' "$contract"
require_contains 'This document does not handle keys.' "$contract"
require_contains 'This document does not handle private keys.' "$contract"
require_contains 'signing_operation_ready=1' "$contract"
require_contains 'signing_operation_state=operation-metadata-only' "$contract"
require_contains 'requested_signature=Ed25519-development' "$contract"
require_contains 'requested_signing_authorization=metadata-only' "$contract"
require_contains 'requested_signer_handoff=metadata-only' "$contract"
require_contains 'requested_signer_invocation=metadata-only' "$contract"
require_contains 'requested_signing_operation=metadata-only' "$contract"
require_contains 'requested_key_handling=metadata-only' "$contract"
require_contains 'key_handling_state=key-handling-metadata-only' "$contract"
require_contains 'key_handling_ready=1' "$contract"
require_contains 'signature_performed=0' "$contract"
require_contains 'verification_performed=0' "$contract"
require_contains 'signer_invoked=0' "$contract"
require_contains 'public_key_parsed=0' "$contract"
require_contains 'key_material_loaded=0' "$contract"
require_contains 'private_key_handling=0' "$contract"
require_contains 'key_generation_performed=0' "$contract"
require_contains 'hardware_key_used=0' "$contract"
require_contains 'trust_store_loaded=0' "$contract"
require_contains 'revocation_lookup_performed=0' "$contract"
require_contains 'runtime_authority_granted=0' "$contract"
require_contains 'host_read_performed=0' "$contract"
require_contains 'host_write_performed=0' "$contract"
require_contains 'network_performed=0' "$contract"
require_contains 'key-handling metadata implementation' "$contract"
require_contains 'Status: initial key-handling metadata implementation' docs/LATTICRA_SEAL_KEY_HANDLING_IMPLEMENTATION.md
require_contains 'latticra_seal_key_handling_t' docs/LATTICRA_SEAL_KEY_HANDLING_IMPLEMENTATION.md
require_contains 'latticra_seal_key_handling_from_operation' docs/LATTICRA_SEAL_KEY_HANDLING_IMPLEMENTATION.md
require_contains 'key_handling_state=key-handling-metadata-only' docs/LATTICRA_SEAL_KEY_HANDLING_IMPLEMENTATION.md
require_contains 'key_handling_ready=1' docs/LATTICRA_SEAL_KEY_HANDLING_IMPLEMENTATION.md
require_contains 'public_key_parsed=0' docs/LATTICRA_SEAL_KEY_HANDLING_IMPLEMENTATION.md
require_contains 'key_material_loaded=0' docs/LATTICRA_SEAL_KEY_HANDLING_IMPLEMENTATION.md
require_contains 'hardware_key_used=0' docs/LATTICRA_SEAL_KEY_HANDLING_IMPLEMENTATION.md
require_contains 'latticra_seal_key_handling_t' include/latticra/seal_key_handling.h
require_contains 'latticra_seal_key_handling_from_operation' src/seal_key_handling.c
require_contains 'seal key-handling invariants: ok' tests/seal_key_handling_invariants.c
require_contains 'Status: status record for Latticra Seal key-handling metadata' docs/status/SEAL_KEY_HANDLING_STATUS.md
require_contains 'seal_key_handling_status_present=1' docs/status/SEAL_KEY_HANDLING_STATUS.md

require_contains 'LATTICRA_SEAL_KEY_HANDLING_CONTRACT.md' README.md
require_contains 'LATTICRA_SEAL_KEY_HANDLING_IMPLEMENTATION.md' README.md
require_contains 'SEAL_KEY_HANDLING_STATUS.md' README.md
require_contains 'latticra_seal_key_handling_contract_present=1' README.md
require_contains 'latticra_seal_key_handling_metadata_present=1' README.md
require_contains 'latticra_seal_key_handling_status_present=1' README.md
require_contains 'seal_key_handling_contract_present=1' README.md
require_contains 'seal_key_handling_metadata_present=1' README.md
require_contains 'seal_key_handling_status_present=1' README.md
require_contains 'Seal key-handling boundary contract' STATUS.md
require_contains 'Seal key-handling metadata implementation' STATUS.md
require_contains 'Seal key-handling status/public-entry alignment' STATUS.md
require_contains 'seal_key_handling_contract_present=1' STATUS.md
require_contains 'seal_key_handling_metadata_present=1' STATUS.md
require_contains 'seal_key_handling_status_present=1' STATUS.md
require_contains 'seal_key_handling_contract_present=1' docs/status/README.md
require_contains 'seal_key_handling_metadata_present=1' docs/status/README.md
require_contains 'seal_key_handling_status_present=1' docs/status/README.md
require_contains 'Latticra Seal key-handling boundary contract' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal key-handling metadata implementation' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal key-handling status/public-entry alignment' docs/status/CURRENT_STATUS.md
require_contains 'LATTICRA_SEAL_KEY_HANDLING_CONTRACT.md' docs/FOUNDATION_INDEX.md
require_contains 'LATTICRA_SEAL_KEY_HANDLING_IMPLEMENTATION.md' docs/FOUNDATION_INDEX.md
require_contains 'SEAL_KEY_HANDLING_STATUS.md' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal key-handling boundary contract' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal key-handling metadata implementation' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal key-handling status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Seal key-material boundary contract' docs/project_notes/UPCOMING_WORK.md

printf 'seal key-handling contract: ok\n'
