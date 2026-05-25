#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal public-key parsing status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal public-key parsing status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status_file="docs/status/SEAL_PUBLIC_KEY_PARSING_STATUS.md"

require_file "$status_file"
require_file docs/LATTICRA_SEAL_PUBLIC_KEY_PARSING_CONTRACT.md
require_file docs/LATTICRA_SEAL_PUBLIC_KEY_PARSING_IMPLEMENTATION.md
require_file include/latticra/seal_public_key_parsing.h
require_file src/seal_public_key_parsing.c
require_file tests/seal_public_key_parsing_invariants.c
require_file scripts/test-latticra-seal-public-key-parsing-contract.sh
require_file scripts/test-latticra-seal-public-key-parsing.sh
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

require_contains 'Status: status record for Latticra Seal public-key parsing metadata' "$status_file"
require_contains 'Source: local follow-up slice' "$status_file"
require_contains 'seal_public_key_parsing_contract_present=1' "$status_file"
require_contains 'seal_public_key_parsing_implementation_present=1' "$status_file"
require_contains 'seal_public_key_parsing_header_present=1' "$status_file"
require_contains 'seal_public_key_parsing_source_present=1' "$status_file"
require_contains 'seal_public_key_parsing_invariant_test_present=1' "$status_file"
require_contains 'seal_public_key_parsing_runner_present=1' "$status_file"
require_contains 'seal_public_key_parsing_metadata_present=1' "$status_file"
require_contains 'seal_public_key_parsing_status_present=1' "$status_file"
require_contains 'seal_key_material_contract_present=1' "$status_file"
require_contains 'seal_key_material_implementation_present=1' "$status_file"
require_contains 'seal_key_material_status_present=1' "$status_file"
require_contains 'public_key_parsing_profile=latticra-seal-public-key-parsing/0.1' "$status_file"
require_contains 'key_material_profile=latticra-seal-key-material/0.1' "$status_file"
require_contains 'key_handling_profile=latticra-seal-key-handling/0.1' "$status_file"
require_contains 'signing_operation_profile=latticra-seal-signing-operation/0.1' "$status_file"
require_contains 'signer_invocation_profile=latticra-seal-signer-invocation/0.1' "$status_file"
require_contains 'signer_handoff_profile=latticra-seal-signer-handoff/0.1' "$status_file"
require_contains 'signing_authorization_profile=latticra-seal-signing-authorization/0.1' "$status_file"
require_contains 'signature_request_profile=latticra-seal-signature-request/0.1' "$status_file"
require_contains 'requested_signature=Ed25519-development' "$status_file"
require_contains 'requested_signing_authorization=metadata-only' "$status_file"
require_contains 'requested_signer_handoff=metadata-only' "$status_file"
require_contains 'requested_signer_invocation=metadata-only' "$status_file"
require_contains 'requested_signing_operation=metadata-only' "$status_file"
require_contains 'requested_key_handling=metadata-only' "$status_file"
require_contains 'requested_key_material=metadata-only' "$status_file"
require_contains 'requested_public_key_parsing=metadata-only' "$status_file"
require_contains 'signing_operation_state=operation-metadata-only' "$status_file"
require_contains 'signing_operation_ready=1' "$status_file"
require_contains 'key_handling_state=key-handling-metadata-only' "$status_file"
require_contains 'key_handling_ready=1' "$status_file"
require_contains 'key_material_state=key-material-metadata-only' "$status_file"
require_contains 'key_material_ready=1' "$status_file"
require_contains 'public_key_parsing_state=public-key-parsing-metadata-only' "$status_file"
require_contains 'public_key_parsing_ready=1' "$status_file"
require_contains 'signature_performed=0' "$status_file"
require_contains 'verification_performed=0' "$status_file"
require_contains 'signer_invoked=0' "$status_file"
require_contains 'public_key_parsed=0' "$status_file"
require_contains 'key_material_loaded=0' "$status_file"
require_contains 'private_key_handling=0' "$status_file"
require_contains 'key_generation_performed=0' "$status_file"
require_contains 'hardware_key_used=0' "$status_file"
require_contains 'trust_store_loaded=0' "$status_file"
require_contains 'revocation_lookup_performed=0' "$status_file"
require_contains 'runtime_authority_granted=0' "$status_file"
require_contains 'host_read_performed=0' "$status_file"
require_contains 'host_write_performed=0' "$status_file"
require_contains 'network_performed=0' "$status_file"
require_contains 'mode=metadata-only' "$status_file"
require_contains 'status=public-key-parsing-metadata' "$status_file"
require_contains 'future key parsing implementation contract' "$status_file"

require_contains 'SEAL_PUBLIC_KEY_PARSING_STATUS.md' README.md
require_contains 'LATTICRA_SEAL_PUBLIC_KEY_PARSING_IMPLEMENTATION.md' README.md
require_contains 'latticra_seal_public_key_parsing_status_present=1' README.md
require_contains 'latticra_seal_public_key_parsing_metadata_present=1' README.md
require_contains 'seal_public_key_parsing_status_present=1' README.md
require_contains 'seal_public_key_parsing_metadata_present=1' README.md
require_contains 'Seal public-key parsing status/public-entry alignment' STATUS.md
require_contains 'Seal public-key parsing metadata implementation' STATUS.md
require_contains 'seal_public_key_parsing_status_present=1' STATUS.md
require_contains 'seal_public_key_parsing_metadata_present=1' STATUS.md
require_contains 'seal_public_key_parsing_status_present=1' docs/status/README.md
require_contains 'seal_public_key_parsing_metadata_present=1' docs/status/README.md
require_contains 'SEAL_PUBLIC_KEY_PARSING_STATUS.md' docs/status/README.md
require_contains 'Latticra Seal public-key parsing status/public-entry alignment' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal public-key parsing metadata implementation' docs/status/CURRENT_STATUS.md
require_contains 'SEAL_PUBLIC_KEY_PARSING_STATUS.md' docs/FOUNDATION_INDEX.md
require_contains 'LATTICRA_SEAL_PUBLIC_KEY_PARSING_IMPLEMENTATION.md' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal public-key parsing status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal public-key parsing metadata implementation' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Seal future key parsing implementation contract' docs/project_notes/UPCOMING_WORK.md

printf 'seal public-key parsing status: ok\n'
