#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal verified effect decision contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal verified effect decision contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_VERIFIED_CAPABILITY_GATE_IMPLEMENTATION.md
require_file include/latticra/seal_verified_capability_gate.h
require_file src/seal_verified_capability_gate.c
require_file tests/seal_verified_capability_gate_invariants.c
require_file scripts/test-latticra-seal-verified-capability-gate.sh

require_contains 'Status: Latticra Seal verified effect decision contract' "$contract"
require_contains 'The decision is effect classification, not effect execution.' "$contract"
require_contains 'require gate_allowed=1' "$contract"
require_contains 'require gate_state=allowed-metadata-only' "$contract"
require_contains 'classify report-only as decision_state=allowed-report-only' "$contract"
require_contains 'classify evaluate-only as decision_state=allowed-evaluate-only' "$contract"
require_contains 'effect_allowed=1' "$contract"
require_contains 'effect_performed=0' "$contract"
require_contains 'runtime_authority_granted=0' "$contract"
require_contains 'host_read_performed=0' "$contract"
require_contains 'host_write_performed=0' "$contract"
require_contains 'network_performed=0' "$contract"
require_contains 'decision_state=denied-gate' "$contract"
require_contains 'decision_state=denied-effect' "$contract"
require_contains 'decision_state=denied-runtime-authority' "$contract"
require_contains 'decision_state=denied-host-effect' "$contract"
require_contains 'decision_state=denied-network-effect' "$contract"
require_contains 'verified effect decision metadata implementation' "$contract"
require_contains 'runtime handoff evaluation from an allowed metadata-only effect decision' "$contract"
require_contains 'sh scripts/test-latticra-seal-verified-effect-decision-contract.sh' "$contract"

printf 'seal verified effect decision contract: ok\n'
