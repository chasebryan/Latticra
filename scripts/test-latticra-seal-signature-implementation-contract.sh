#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal signature implementation contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal signature implementation contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_SIGNATURE_IMPLEMENTATION_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_SIGNATURE_POLICY_IMPLEMENTATION.md
require_file include/latticra/seal_signature_policy.h
require_file src/seal_signature_policy.c

require_contains 'Status: Latticra Seal signature implementation contract' "$contract"
require_contains 'This document does not implement signatures.' "$contract"
require_contains 'Ed25519-development' "$contract"
require_contains 'metadata-only' "$contract"
require_contains 'verification_supported=0' "$contract"
require_contains 'private_key_handling=0' "$contract"
require_contains 'network_lookup_allowed=0' "$contract"
require_contains 'runtime_authority_granted=0' "$contract"
require_contains 'signature metadata envelope implementation' "$contract"

printf 'seal signature implementation contract: ok\n'
