#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal signer handoff contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal signer handoff contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_SIGNER_HANDOFF_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_SIGNING_AUTHORIZATION_CONTRACT.md
require_file docs/LATTICRA_SEAL_SIGNING_AUTHORIZATION_IMPLEMENTATION.md
require_file docs/status/SEAL_SIGNING_AUTHORIZATION_STATUS.md
require_file docs/LATTICRA_SEAL_SIGNER_HANDOFF_IMPLEMENTATION.md
require_file docs/status/SEAL_SIGNER_HANDOFF_STATUS.md
require_file include/latticra/seal_signing_authorization.h
require_file include/latticra/seal_signer_handoff.h
require_file src/seal_signing_authorization.c
require_file src/seal_signer_handoff.c
require_file tests/seal_signing_authorization_invariants.c
require_file tests/seal_signer_handoff_invariants.c
require_file scripts/test-latticra-seal-signing-authorization-contract.sh
require_file scripts/test-latticra-seal-signing-authorization.sh
require_file scripts/test-latticra-seal-signing-authorization-status.sh
require_file scripts/test-latticra-seal-signer-handoff.sh
require_file scripts/test-latticra-seal-signer-handoff-status.sh
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md

require_contains 'Status: Latticra Seal signer handoff contract' "$contract"
require_contains 'The signer handoff surface is signer-path classification, not signing, not verification, not signer invocation, and not runtime handoff.' "$contract"
require_contains 'This document does not implement signing.' "$contract"
require_contains 'signing_authorization_ready=1' "$contract"
require_contains 'signing_authorization_state=authorized-metadata-only' "$contract"
require_contains 'requested_signature=Ed25519-development' "$contract"
require_contains 'requested_signing_authorization=metadata-only' "$contract"
require_contains 'requested_signer_handoff=metadata-only' "$contract"
require_contains 'signer_handoff_state=handoff-metadata-only' "$contract"
require_contains 'signer_handoff_ready=1' "$contract"
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
require_contains 'signer handoff metadata implementation' "$contract"
require_contains 'Status: initial signer handoff metadata implementation' docs/LATTICRA_SEAL_SIGNER_HANDOFF_IMPLEMENTATION.md
require_contains 'latticra_seal_signer_handoff_t' docs/LATTICRA_SEAL_SIGNER_HANDOFF_IMPLEMENTATION.md
require_contains 'latticra_seal_signer_handoff_from_authorization' docs/LATTICRA_SEAL_SIGNER_HANDOFF_IMPLEMENTATION.md
require_contains 'signer_handoff_profile=latticra-seal-signer-handoff/0.1' docs/LATTICRA_SEAL_SIGNER_HANDOFF_IMPLEMENTATION.md
require_contains 'signer_handoff_state=handoff-metadata-only' docs/LATTICRA_SEAL_SIGNER_HANDOFF_IMPLEMENTATION.md
require_contains 'signer_invoked=0' docs/LATTICRA_SEAL_SIGNER_HANDOFF_IMPLEMENTATION.md

require_contains 'LATTICRA_SEAL_SIGNER_HANDOFF_CONTRACT.md' README.md
require_contains 'LATTICRA_SEAL_SIGNER_HANDOFF_IMPLEMENTATION.md' README.md
require_contains 'latticra_seal_signer_handoff_contract_present=1' README.md
require_contains 'latticra_seal_signer_handoff_metadata_present=1' README.md
require_contains 'seal_signer_handoff_contract_present=1' README.md
require_contains 'seal_signer_handoff_metadata_present=1' README.md
require_contains 'Seal signer handoff contract' STATUS.md
require_contains 'Seal signer handoff metadata implementation' STATUS.md
require_contains 'Seal signer handoff status/public-entry alignment' STATUS.md
require_contains 'seal_signer_handoff_contract_present=1' STATUS.md
require_contains 'seal_signer_handoff_metadata_present=1' STATUS.md
require_contains 'seal_signer_handoff_status_present=1' STATUS.md
require_contains 'seal_signer_handoff_contract_present=1' docs/status/README.md
require_contains 'seal_signer_handoff_metadata_present=1' docs/status/README.md
require_contains 'seal_signer_handoff_status_present=1' docs/status/README.md
require_contains 'Latticra Seal signer handoff contract' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal signer handoff metadata implementation' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal signer handoff status/public-entry alignment' docs/status/CURRENT_STATUS.md
require_contains 'LATTICRA_SEAL_SIGNER_HANDOFF_CONTRACT.md' docs/FOUNDATION_INDEX.md
require_contains 'LATTICRA_SEAL_SIGNER_HANDOFF_IMPLEMENTATION.md' docs/FOUNDATION_INDEX.md
require_contains 'SEAL_SIGNER_HANDOFF_STATUS.md' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal signer handoff contract' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal signer handoff metadata implementation' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal signer handoff status/public-entry alignment' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Signer invocation contract planning' docs/project_notes/UPCOMING_WORK.md

printf 'seal signer handoff contract: ok\n'
