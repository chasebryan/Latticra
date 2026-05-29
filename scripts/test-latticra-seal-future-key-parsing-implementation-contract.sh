#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal future key parsing implementation contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal future key parsing implementation contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_FUTURE_KEY_PARSING_IMPLEMENTATION_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_PUBLIC_KEY_PARSING_CONTRACT.md
require_file docs/LATTICRA_SEAL_PUBLIC_KEY_PARSING_IMPLEMENTATION.md
require_file docs/status/SEAL_PUBLIC_KEY_PARSING_STATUS.md
require_file include/latticra/seal_public_key_parsing.h
require_file src/seal_public_key_parsing.c
require_file tests/seal_public_key_parsing_invariants.c
require_file scripts/test-latticra-seal-public-key-parsing-contract.sh
require_file scripts/test-latticra-seal-public-key-parsing.sh
require_file scripts/test-latticra-seal-public-key-parsing-status.sh
require_file docs/LATTICRA_SEAL_KEY_MATERIAL_CONTRACT.md
require_file docs/LATTICRA_SEAL_KEY_MATERIAL_IMPLEMENTATION.md
require_file docs/status/SEAL_KEY_MATERIAL_STATUS.md
require_file include/latticra/seal_key_material.h
require_file src/seal_key_material.c
require_file tests/seal_key_material_invariants.c
require_file scripts/test-latticra-seal-key-material-contract.sh
require_file scripts/test-latticra-seal-key-material.sh
require_file scripts/test-latticra-seal-key-material-status.sh
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md

require_contains 'Status: Latticra Seal future key parsing implementation contract' "$contract"
require_contains 'implementation contract, not implementation' "$contract"
require_contains 'This document does not implement public-key parsing.' "$contract"
require_contains 'seal_public_key_parsing_status_present=1' "$contract"
require_contains 'seal_public_key_parsing_metadata_present=1' "$contract"
require_contains 'public_key_parsing_profile=latticra-seal-public-key-parsing/0.1' "$contract"
require_contains 'requested_public_key_parsing=metadata-only' "$contract"
require_contains 'public_key_parsing_state=public-key-parsing-metadata-only' "$contract"
require_contains 'public_key_parsing_ready=1' "$contract"
require_contains 'key_material_profile=latticra-seal-key-material/0.1' "$contract"
require_contains 'requested_key_material=metadata-only' "$contract"
require_contains 'key_material_state=key-material-metadata-only' "$contract"
require_contains 'key_material_ready=1' "$contract"
require_contains 'future_key_parsing_contract_present=1' "$contract"
require_contains 'future_key_parsing_implementation_plan_present=1' "$contract"
require_contains 'future_key_parsing_implementation_present=0' "$contract"
require_contains 'public_key_parser_implementation_present=0' "$contract"
require_contains 'public_key_parsed=0' "$contract"
require_contains 'key_material_loaded=0' "$contract"
require_contains 'private_key_handling=0' "$contract"
require_contains 'key_generation_performed=0' "$contract"
require_contains 'hardware_key_used=0' "$contract"
require_contains 'trust_store_loaded=0' "$contract"
require_contains 'revocation_lookup_performed=0' "$contract"
require_contains 'signature_performed=0' "$contract"
require_contains 'verification_performed=0' "$contract"
require_contains 'signer_invoked=0' "$contract"
require_contains 'runtime_authority_granted=0' "$contract"
require_contains 'host_read_performed=0' "$contract"
require_contains 'host_write_performed=0' "$contract"
require_contains 'network_performed=0' "$contract"
require_contains 'future key parsing implementation plan' "$contract"

require_contains 'LATTICRA_SEAL_FUTURE_KEY_PARSING_IMPLEMENTATION_CONTRACT.md' README.md
require_contains 'latticra_seal_future_key_parsing_implementation_contract_present=1' README.md
require_contains 'seal_future_key_parsing_implementation_contract_present=1' README.md
require_contains 'Seal future key parsing implementation contract' STATUS.md
require_contains 'Seal future key parsing implementation plan' STATUS.md
require_contains 'seal_future_key_parsing_implementation_contract_present=1' STATUS.md
require_contains 'seal_future_key_parsing_implementation_contract_present=1' docs/status/README.md
require_contains 'LATTICRA_SEAL_FUTURE_KEY_PARSING_IMPLEMENTATION_CONTRACT.md' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal future key parsing implementation contract' docs/status/CURRENT_STATUS.md
require_contains 'Seal future key parsing implementation plan' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal future key parsing implementation contract' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Seal future key parsing implementation plan' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal future key parsing implementation contract' docs/project_notes/UPCOMING_WORK.md
require_contains 'Seal future key parsing implementation plan' docs/project_notes/UPCOMING_WORK.md
require_contains 'future key parsing implementation plan' docs/status/SEAL_PUBLIC_KEY_PARSING_STATUS.md
require_contains 'seal future key parsing implementation contract: ok' docs/status/SEAL_PUBLIC_KEY_PARSING_STATUS.md

printf 'seal future key parsing implementation contract: ok\n'
