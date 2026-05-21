#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal verification receipt contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal verification receipt contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_VERIFICATION_RECEIPT_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_VERIFICATION_POLICY_IMPLEMENTATION.md
require_file include/latticra/seal_verification_policy.h
require_file src/seal_verification_policy.c
require_file scripts/test-latticra-seal-verification-policy.sh

require_contains 'Status: Latticra Seal verification receipt contract' "$contract"
require_contains 'This document does not implement verification receipts.' "$contract"
require_contains 'receipt_state=unverified-metadata' "$contract"
require_contains 'cryptographic_verification_supported=0' "$contract"
require_contains 'cryptographic_verification_performed=0' "$contract"
require_contains 'verified=0' "$contract"
require_contains 'authority_usable=0' "$contract"
require_contains 'capability_gate_allowed=0' "$contract"
require_contains 'runtime_authority_granted=0' "$contract"
require_contains 'verification receipt metadata implementation' "$contract"
require_contains 'capability gate contract' "$contract"

printf 'seal verification receipt contract: ok\n'
