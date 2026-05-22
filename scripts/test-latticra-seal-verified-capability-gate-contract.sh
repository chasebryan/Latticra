#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal verified capability gate contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal verified capability gate contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_VERIFIED_RECEIPT_PROMOTION_IMPLEMENTATION.md
require_file include/latticra/seal_verified_receipt_promotion.h
require_file src/seal_verified_receipt_promotion.c
require_file tests/seal_verified_receipt_promotion_invariants.c
require_file scripts/test-latticra-seal-verified-receipt-promotion.sh

require_contains 'Status: Latticra Seal verified capability gate contract' "$contract"
require_contains 'The gate is policy evaluation, not effect execution.' "$contract"
require_contains 'require receipt_state=verified' "$contract"
require_contains 'require verification_state=verified' "$contract"
require_contains 'require verified=1' "$contract"
require_contains 'require invalid=0' "$contract"
require_contains 'verified-receipt-inspection' "$contract"
require_contains 'verified-receipt-report' "$contract"
require_contains 'report-only' "$contract"
require_contains 'evaluate-only' "$contract"
require_contains 'gate_state=allowed-metadata-only' "$contract"
require_contains 'gate_allowed=1' "$contract"
require_contains 'runtime_authority_granted=0' "$contract"
require_contains 'effect_performed=0' "$contract"
require_contains 'host_read_performed=0' "$contract"
require_contains 'host_write_performed=0' "$contract"
require_contains 'network_performed=0' "$contract"
require_contains 'verified capability gate metadata implementation' "$contract"
require_contains 'effect decision evaluation from an allowed metadata-only capability gate' "$contract"
require_contains 'sh scripts/test-latticra-seal-verified-capability-gate-contract.sh' "$contract"

printf 'seal verified capability gate contract: ok\n'
