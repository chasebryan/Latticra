#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal verified receipt promotion contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal verified receipt promotion contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_ED25519_VERIFY_IMPLEMENTATION.md
require_file include/latticra/seal_ed25519_verify.h
require_file src/seal_ed25519_verify.c
require_file tests/seal_ed25519_verify_invariants.c
require_file scripts/test-latticra-seal-ed25519-verify.sh

require_contains 'Status: Latticra Seal verified receipt promotion contract' "$contract"
require_contains 'This document does not implement verified receipt promotion' "$contract"
require_contains 'The promotion is evidence promotion, not permission promotion.' "$contract"
require_contains 'The Ed25519 verify-only result is the only allowed input source' "$contract"
require_contains 'require cryptographic_verification_supported=1' "$contract"
require_contains 'require cryptographic_verification_performed=1' "$contract"
require_contains 'require verified=1' "$contract"
require_contains 'require invalid=0' "$contract"
require_contains 'require crypto_verify_state=verified' "$contract"
require_contains 'receipt_state=verified' "$contract"
require_contains 'verification_state=verified' "$contract"
require_contains 'A promoted verified receipt remains authority-neutral.' "$contract"
require_contains 'authority_usable=0' "$contract"
require_contains 'capability_gate_allowed=0' "$contract"
require_contains 'runtime_authority_granted=0' "$contract"
require_contains 'verified receipt promotion metadata implementation' "$contract"
require_contains 'capability gate evaluation of a verified but authority-neutral receipt' "$contract"
require_contains 'sh scripts/test-latticra-seal-verified-receipt-promotion-contract.sh' "$contract"

printf 'seal verified receipt promotion contract: ok\n'
