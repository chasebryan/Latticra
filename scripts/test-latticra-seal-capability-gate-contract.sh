#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal capability gate contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal capability gate contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_CAPABILITY_GATE_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_VERIFICATION_RECEIPT_IMPLEMENTATION.md
require_file include/latticra/seal_verification_receipt.h
require_file src/seal_verification_receipt.c
require_file scripts/test-latticra-seal-verification-receipt.sh

require_contains 'Status: Latticra Seal capability gate contract' "$contract"
require_contains 'This document does not implement capability gates.' "$contract"
require_contains 'denied by default' "$contract"
require_contains 'gate_state=denied-unverified' "$contract"
require_contains 'verified=0' "$contract"
require_contains 'authority_usable=0' "$contract"
require_contains 'receipt_capability_gate_allowed=0' "$contract"
require_contains 'gate_allowed=0' "$contract"
require_contains 'runtime_authority_granted=0' "$contract"
require_contains 'capability gate metadata implementation' "$contract"
require_contains 'effect authorization contract' "$contract"

printf 'seal capability gate contract: ok\n'
