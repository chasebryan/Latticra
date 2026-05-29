#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal future key parsing implementation plan: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal future key parsing implementation plan: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

plan="docs/LATTICRA_SEAL_FUTURE_KEY_PARSING_IMPLEMENTATION_PLAN.md"

require_file "$plan"
require_file docs/LATTICRA_SEAL_FUTURE_KEY_PARSING_IMPLEMENTATION_CONTRACT.md
require_file scripts/test-latticra-seal-future-key-parsing-implementation-contract.sh
require_file docs/LATTICRA_SEAL_PUBLIC_KEY_PARSING_CONTRACT.md
require_file docs/LATTICRA_SEAL_PUBLIC_KEY_PARSING_IMPLEMENTATION.md
require_file docs/status/SEAL_PUBLIC_KEY_PARSING_STATUS.md
require_file include/latticra/seal_public_key_parsing.h
require_file src/seal_public_key_parsing.c
require_file tests/seal_public_key_parsing_invariants.c
require_file scripts/test-latticra-seal-public-key-parsing-contract.sh
require_file scripts/test-latticra-seal-public-key-parsing.sh
require_file scripts/test-latticra-seal-public-key-parsing-status.sh
require_file docs/LATTICRA_SEAL_FUTURE_KEY_PARSING_IMPLEMENTATION.md
require_file docs/status/SEAL_KEY_PARSING_STATUS.md
require_file include/latticra/seal_key_parsing.h
require_file src/seal_key_parsing.c
require_file tests/seal_key_parsing_invariants.c
require_file scripts/test-latticra-seal-key-parsing.sh
require_file scripts/test-latticra-seal-key-parsing-status.sh
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md

require_contains 'Status: implementation planning contract for a future bounded no-effect Latticra Seal key parsing surface' "$plan"
require_contains 'This document is a plan, not parser code.' "$plan"
require_contains 'include/latticra/seal_key_parsing.h' "$plan"
require_contains 'src/seal_key_parsing.c' "$plan"
require_contains 'tests/seal_key_parsing_invariants.c' "$plan"
require_contains 'scripts/test-latticra-seal-key-parsing.sh' "$plan"
require_contains 'docs/LATTICRA_SEAL_FUTURE_KEY_PARSING_IMPLEMENTATION.md' "$plan"
require_contains 'docs/status/SEAL_KEY_PARSING_STATUS.md' "$plan"
require_contains 'latticra_seal_key_parsing_result_t' "$plan"
require_contains 'latticra_seal_key_parsing_from_public_key_bytes' "$plan"
require_contains 'latticra_seal_key_parsing_is_no_effect' "$plan"
require_contains 'LATTICRA_SEAL_KEY_PARSING_INPUT_MAX 4096u' "$plan"
require_contains 'LATTICRA_SEAL_KEY_PARSING_REPORT_MAX 8192u' "$plan"
require_contains 'LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_RAW_PUBLIC_KEY_32' "$plan"
require_contains 'LATTICRA_SEAL_KEY_PARSING_FORMAT_ED25519_HEX_PUBLIC_KEY_64' "$plan"
require_contains 'LATTICRA_SEAL_KEY_PARSING_FORMAT_PRIVATE_KEY_DENIED' "$plan"
require_contains 'ed25519-raw-public-key-32' "$plan"
require_contains 'ed25519-hex-public-key-64' "$plan"
require_contains 'private-key-denied' "$plan"
require_contains 'LATTICRA_SEAL_KEY_PARSING_OVERSIZED_INPUT' "$plan"
require_contains 'LATTICRA_SEAL_KEY_PARSING_PRIVATE_KEY_DENIED' "$plan"
require_contains 'LATTICRA_SEAL_KEY_PARSING_BUFFER_TOO_SMALL' "$plan"
require_contains 'key_parsing_profile=latticra-seal-key-parsing/0.1' "$plan"
require_contains 'requested_key_parsing=public-key-bytes-only' "$plan"
require_contains 'key_parsing_input_format=ed25519-raw-public-key-32' "$plan"
require_contains 'key_parsing_input_length=32' "$plan"
require_contains 'key_parsing_algorithm=Ed25519-development' "$plan"
require_contains 'key_parsing_state=public-key-parsed-metadata-only' "$plan"
require_contains 'key_parsing_ready=1' "$plan"
require_contains 'public_key_parsed=1' "$plan"
require_contains 'key_material_loaded=0' "$plan"
require_contains 'private_key_handling=0' "$plan"
require_contains 'signature_performed=0' "$plan"
require_contains 'verification_performed=0' "$plan"
require_contains 'signer_invoked=0' "$plan"
require_contains 'runtime_authority_granted=0' "$plan"
require_contains 'host_read_performed=0' "$plan"
require_contains 'host_write_performed=0' "$plan"
require_contains 'network_performed=0' "$plan"
require_contains 'Plan-Time Checkpoint' "$plan"
require_contains 'future_key_parsing_implementation_plan_present=1' "$plan"
require_contains 'future_key_parsing_implementation_present=0' "$plan"
require_contains 'public_key_parser_implementation_present=0' "$plan"
require_contains 'key_parsing_header_present=0' "$plan"
require_contains 'LATTICRA SEAL KEY PARSING' "$plan"
require_contains 'small report buffers fail closed' "$plan"
require_contains 'private key marker fails closed' "$plan"
require_contains 'Bounded no-effect key parsing implementation code may be added only after this plan is merged.' "$plan"
require_contains 'The next valid Latticra Seal slice after the implementation is key parsing status/public-entry alignment.' "$plan"

require_contains 'LATTICRA_SEAL_FUTURE_KEY_PARSING_IMPLEMENTATION_PLAN.md' README.md
require_contains 'LATTICRA_SEAL_FUTURE_KEY_PARSING_IMPLEMENTATION.md' README.md
require_contains 'latticra_seal_future_key_parsing_implementation_plan_present=1' README.md
require_contains 'latticra_seal_key_parsing_metadata_present=1' README.md
require_contains 'latticra_seal_key_parsing_status_present=1' README.md
require_contains 'seal_future_key_parsing_implementation_plan_present=1' README.md
require_contains 'seal_key_parsing_metadata_present=1' README.md
require_contains 'seal_key_parsing_status_present=1' README.md
require_contains 'Seal future key parsing implementation plan' STATUS.md
require_contains 'Seal key parsing status/public-entry alignment' STATUS.md
require_contains 'seal_key_parsing_metadata_present=1' STATUS.md
require_contains 'seal_key_parsing_status_present=1' STATUS.md
require_contains 'seal_future_key_parsing_implementation_plan_present=1' STATUS.md
require_contains 'seal_key_parsing_metadata_present=1' docs/status/README.md
require_contains 'seal_key_parsing_status_present=1' docs/status/README.md
require_contains 'seal_future_key_parsing_implementation_plan_present=1' docs/status/README.md
require_contains 'LATTICRA_SEAL_FUTURE_KEY_PARSING_IMPLEMENTATION.md' docs/FOUNDATION_INDEX.md
require_contains 'SEAL_KEY_PARSING_STATUS.md' docs/FOUNDATION_INDEX.md
require_contains 'LATTICRA_SEAL_FUTURE_KEY_PARSING_IMPLEMENTATION_PLAN.md' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal future key parsing implementation plan' docs/status/CURRENT_STATUS.md
require_contains 'Seal key parsing status/public-entry alignment' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal future key parsing implementation plan' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal bounded key parsing metadata implementation' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Seal key parsing status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal future key parsing implementation plan' docs/project_notes/UPCOMING_WORK.md
require_contains 'Latticra Seal bounded no-effect key parsing implementation' docs/project_notes/UPCOMING_WORK.md
require_contains 'Seal key parsing status/public-entry alignment' docs/project_notes/UPCOMING_WORK.md
require_contains 'seal_key_parsing_metadata_present=1' docs/status/SEAL_PUBLIC_KEY_PARSING_STATUS.md
require_contains 'seal_key_parsing_status_present=1' docs/status/SEAL_PUBLIC_KEY_PARSING_STATUS.md
require_contains 'seal key parsing invariants: ok' docs/status/SEAL_PUBLIC_KEY_PARSING_STATUS.md
require_contains 'seal key parsing status: ok' docs/status/SEAL_PUBLIC_KEY_PARSING_STATUS.md
require_contains 'seal future key parsing implementation plan: ok' docs/status/SEAL_PUBLIC_KEY_PARSING_STATUS.md

printf 'seal future key parsing implementation plan: ok\n'
