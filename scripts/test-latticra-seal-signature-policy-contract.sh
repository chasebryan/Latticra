#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal signature policy contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal signature policy contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_SIGNATURE_POLICY_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_SIGNED_MANIFEST_IMPLEMENTATION.md
require_file include/latticra/seal_manifest.h
require_file src/seal_manifest.c

require_contains 'Status: Latticra Seal signature policy contract' "$contract"
require_contains 'This document does not implement signatures.' "$contract"
require_contains 'No custom signature primitive may be introduced.' "$contract"
require_contains 'signature_supported=0' "$contract"
require_contains 'verification_supported=0' "$contract"
require_contains 'private_key_handling=0' "$contract"
require_contains 'network_lookup_allowed=0' "$contract"
require_contains 'runtime_authority_granted=0' "$contract"
require_contains 'signature policy metadata implementation' "$contract"

printf 'seal signature policy contract: ok\n'
