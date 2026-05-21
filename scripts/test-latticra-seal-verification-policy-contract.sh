#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal verification policy contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal verification policy contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_VERIFICATION_POLICY_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_SIGNATURE_IMPLEMENTATION.md
require_file include/latticra/seal_signature.h
require_file src/seal_signature.c
require_file scripts/test-latticra-seal-signature.sh

require_contains 'Status: Latticra Seal verification policy contract' "$contract"
require_contains 'This document does not implement cryptographic verification.' "$contract"
require_contains 'verification_state=unsupported' "$contract"
require_contains 'cryptographic_verification_supported=0' "$contract"
require_contains 'cryptographic_verification_performed=0' "$contract"
require_contains 'public_key_material_handling=0' "$contract"
require_contains 'private_key_handling=0' "$contract"
require_contains 'network_lookup_allowed=0' "$contract"
require_contains 'revocation_lookup_allowed=0' "$contract"
require_contains 'runtime_authority_granted=0' "$contract"
require_contains 'verification policy metadata implementation' "$contract"

printf 'seal verification policy contract: ok\n'
