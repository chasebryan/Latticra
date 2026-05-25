#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal signing authorization contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal signing authorization contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_SIGNING_AUTHORIZATION_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_SIGNATURE_REQUEST_CONTRACT.md
require_file docs/LATTICRA_SEAL_SIGNATURE_REQUEST_IMPLEMENTATION.md
require_file docs/status/SEAL_SIGNATURE_REQUEST_STATUS.md
require_file docs/LATTICRA_SEAL_SIGNING_AUTHORIZATION_IMPLEMENTATION.md
require_file include/latticra/seal_signature_request.h
require_file include/latticra/seal_signing_authorization.h
require_file src/seal_signature_request.c
require_file src/seal_signing_authorization.c
require_file tests/seal_signature_request_invariants.c
require_file tests/seal_signing_authorization_invariants.c
require_file scripts/test-latticra-seal-signature-request-contract.sh
require_file scripts/test-latticra-seal-signature-request.sh
require_file scripts/test-latticra-seal-signature-request-status.sh
require_file scripts/test-latticra-seal-signing-authorization.sh
require_file README.md
require_file STATUS.md
require_file docs/status/README.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/project_notes/CURRENT_DIRECTION.md
require_file docs/project_notes/UPCOMING_WORK.md

require_contains 'Status: Latticra Seal signing authorization contract' "$contract"
require_contains 'The signing authorization surface is signing-path classification, not signing, not verification, and not runtime authorization.' "$contract"
require_contains 'This document does not implement signing.' "$contract"
require_contains 'signature_request_ready=1' "$contract"
require_contains 'signature_request_state=requested-metadata-only' "$contract"
require_contains 'requested_signature=Ed25519-development' "$contract"
require_contains 'requested_signing_authorization=metadata-only' "$contract"
require_contains 'signing_authorization_state=authorized-metadata-only' "$contract"
require_contains 'signing_authorization_ready=1' "$contract"
require_contains 'signature_performed=0' "$contract"
require_contains 'verification_performed=0' "$contract"
require_contains 'private_key_handling=0' "$contract"
require_contains 'key_generation_performed=0' "$contract"
require_contains 'trust_store_loaded=0' "$contract"
require_contains 'revocation_lookup_performed=0' "$contract"
require_contains 'runtime_authority_granted=0' "$contract"
require_contains 'host_read_performed=0' "$contract"
require_contains 'host_write_performed=0' "$contract"
require_contains 'network_performed=0' "$contract"
require_contains 'signing authorization metadata implementation' "$contract"

require_contains 'LATTICRA_SEAL_SIGNING_AUTHORIZATION_CONTRACT.md' README.md
require_contains 'LATTICRA_SEAL_SIGNING_AUTHORIZATION_IMPLEMENTATION.md' README.md
require_contains 'latticra_seal_signing_authorization_contract_present=1' README.md
require_contains 'latticra_seal_signing_authorization_metadata_present=1' README.md
require_contains 'seal_signing_authorization_contract_present=1' README.md
require_contains 'seal_signing_authorization_metadata_present=1' README.md
require_contains 'Seal signing authorization contract' STATUS.md
require_contains 'seal_signing_authorization_contract_present=1' STATUS.md
require_contains 'seal_signing_authorization_metadata_present=1' STATUS.md
require_contains 'seal_signing_authorization_contract_present=1' docs/status/README.md
require_contains 'seal_signing_authorization_metadata_present=1' docs/status/README.md
require_contains 'Latticra Seal signing authorization contract' docs/status/CURRENT_STATUS.md
require_contains 'Latticra Seal signing authorization metadata implementation' docs/status/CURRENT_STATUS.md
require_contains 'LATTICRA_SEAL_SIGNING_AUTHORIZATION_CONTRACT.md' docs/FOUNDATION_INDEX.md
require_contains 'LATTICRA_SEAL_SIGNING_AUTHORIZATION_IMPLEMENTATION.md' docs/FOUNDATION_INDEX.md
require_contains 'Latticra Seal signing authorization contract' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Latticra Seal signing authorization metadata implementation' docs/project_notes/CURRENT_DIRECTION.md
require_contains 'Signing authorization status/public-entry alignment' docs/project_notes/UPCOMING_WORK.md

printf 'seal signing authorization contract: ok\n'
