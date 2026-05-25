#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal key-material contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal key-material contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_KEY_MATERIAL_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_PUBLIC_KEY_PARSING_CONTRACT.md
require_file docs/LATTICRA_SEAL_KEY_MATERIAL_IMPLEMENTATION.md
require_file docs/status/SEAL_KEY_MATERIAL_STATUS.md
require_file include/latticra/seal_key_material.h
require_file src/seal_key_material.c
require_file tests/seal_key_material_invariants.c
require_file scripts/test-latticra-seal-key-material.sh
require_file scripts/test-latticra-seal-key-material-status.sh
require_file scripts/test-latticra-seal-public-key-parsing-contract.sh
require_file docs/LATTICRA_SEAL_KEY_HANDLING_CONTRACT.md
require_file docs/LATTICRA_SEAL_KEY_HANDLING_IMPLEMENTATION.md
require_file docs/status/SEAL_KEY_HANDLING_STATUS.md
require_file include/latticra/seal_key_handling.h
require_file src/seal_key_handling.c
require_file tests/seal_key_handling_invariants.c
require_file scripts/test-latticra-seal-key-handling-contract.sh
require_file scripts/test-latticra-seal-key-handling.sh
require_file scripts/test-latticra-seal-key-handling-status.sh
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md

require_contains 'Status: Latticra Seal key-material boundary contract' "$contract"
require_contains 'The key-material surface is key-material path classification, not key material handling, not public-key parsing, not signing, not verification, and not trust-store behavior.' "$contract"
require_contains 'This document does not parse public keys.' "$contract"
require_contains 'This document does not load key material.' "$contract"
require_contains 'This document does not handle private keys.' "$contract"
require_contains 'key_handling_ready=1' "$contract"
require_contains 'key_handling_state=key-handling-metadata-only' "$contract"
require_contains 'requested_signature=Ed25519-development' "$contract"
require_contains 'requested_signing_authorization=metadata-only' "$contract"
require_contains 'requested_signer_handoff=metadata-only' "$contract"
require_contains 'requested_signer_invocation=metadata-only' "$contract"
require_contains 'requested_signing_operation=metadata-only' "$contract"
require_contains 'requested_key_handling=metadata-only' "$contract"
require_contains 'requested_key_material=metadata-only' "$contract"
require_contains 'key_material_state=key-material-metadata-only' "$contract"
require_contains 'key_material_ready=1' "$contract"
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
require_contains 'key-material metadata implementation' "$contract"
require_contains 'Status: Latticra Seal public-key parsing boundary contract' docs/LATTICRA_SEAL_PUBLIC_KEY_PARSING_CONTRACT.md
require_contains 'requested_public_key_parsing=metadata-only' docs/LATTICRA_SEAL_PUBLIC_KEY_PARSING_CONTRACT.md
require_contains 'public_key_parsing_state=public-key-parsing-metadata-only' docs/LATTICRA_SEAL_PUBLIC_KEY_PARSING_CONTRACT.md
require_contains 'Status: initial key-material metadata implementation' docs/LATTICRA_SEAL_KEY_MATERIAL_IMPLEMENTATION.md
require_contains 'latticra_seal_key_material_t' docs/LATTICRA_SEAL_KEY_MATERIAL_IMPLEMENTATION.md
require_contains 'latticra_seal_key_material_from_key_handling' docs/LATTICRA_SEAL_KEY_MATERIAL_IMPLEMENTATION.md
require_contains 'key_material_state=key-material-metadata-only' docs/LATTICRA_SEAL_KEY_MATERIAL_IMPLEMENTATION.md
require_contains 'key_material_ready=1' docs/LATTICRA_SEAL_KEY_MATERIAL_IMPLEMENTATION.md
require_contains 'public_key_parsed=0' docs/LATTICRA_SEAL_KEY_MATERIAL_IMPLEMENTATION.md
require_contains 'key_material_loaded=0' docs/LATTICRA_SEAL_KEY_MATERIAL_IMPLEMENTATION.md
require_contains 'hardware_key_used=0' docs/LATTICRA_SEAL_KEY_MATERIAL_IMPLEMENTATION.md
require_contains 'latticra_seal_key_material_t' include/latticra/seal_key_material.h
require_contains 'latticra_seal_key_material_from_key_handling' src/seal_key_material.c
require_contains 'seal key-material invariants: ok' tests/seal_key_material_invariants.c

require_contains 'LATTICRA_SEAL_KEY_MATERIAL_CONTRACT.md' README.md
require_contains 'LATTICRA_SEAL_KEY_MATERIAL_IMPLEMENTATION.md' README.md
require_contains 'LATTICRA_SEAL_PUBLIC_KEY_PARSING_CONTRACT.md' README.md
require_contains 'latticra_seal_key_material_contract_present=1' README.md
require_contains 'latticra_seal_key_material_metadata_present=1' README.md
require_contains 'latticra_seal_key_material_status_present=1' README.md
require_contains 'latticra_seal_public_key_parsing_contract_present=1' README.md
require_contains 'seal_key_material_contract_present=1' README.md
require_contains 'seal_key_material_metadata_present=1' README.md
require_contains 'seal_key_material_status_present=1' README.md
require_contains 'seal_public_key_parsing_contract_present=1' README.md
require_contains 'Seal key-material boundary contract' STATUS.md
require_contains 'Seal key-material metadata implementation' STATUS.md
require_contains 'Seal key-material status/public-entry alignment' STATUS.md
require_contains 'Seal public-key parsing boundary contract' STATUS.md
require_contains 'seal_key_material_contract_present=1' STATUS.md
require_contains 'seal_key_material_metadata_present=1' STATUS.md
require_contains 'seal_key_material_status_present=1' STATUS.md
require_contains 'seal_public_key_parsing_contract_present=1' STATUS.md
require_contains 'seal_key_material_contract_present=1' docs/status/README.md
require_contains 'seal_key_material_metadata_present=1' docs/status/README.md
require_contains 'seal_key_material_status_present=1' docs/status/README.md
require_contains 'seal_public_key_parsing_contract_present=1' docs/status/README.md
require_contains 'Latticra Seal key-material boundary contract' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal key-material metadata implementation' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal key-material status/public-entry alignment' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal public-key parsing boundary contract' docs/status/CURRENT_STATUS.md
require_contains 'LATTICRA_SEAL_KEY_MATERIAL_CONTRACT.md' docs/FOUNDATION_INDEX.md
require_contains 'LATTICRA_SEAL_KEY_MATERIAL_IMPLEMENTATION.md' docs/FOUNDATION_INDEX.md
require_contains 'SEAL_KEY_MATERIAL_STATUS.md' docs/FOUNDATION_INDEX.md
require_contains 'LATTICRA_SEAL_PUBLIC_KEY_PARSING_CONTRACT.md' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal key-material boundary contract' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal key-material metadata implementation' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal key-material status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal public-key parsing boundary contract' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Seal future key parsing implementation plan' docs/project_notes/UPCOMING_WORK.md

printf 'seal key-material contract: ok\n'
