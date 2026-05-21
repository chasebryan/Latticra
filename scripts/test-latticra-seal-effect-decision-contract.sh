#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal effect decision contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal effect decision contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_EFFECT_DECISION_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_CAPABILITY_GATE_IMPLEMENTATION.md
require_file include/latticra/seal_capability_gate.h
require_file src/seal_capability_gate.c
require_file scripts/test-latticra-seal-capability-gate.sh

require_contains 'Status: Latticra Seal effect decision contract' "$contract"
require_contains 'This document does not implement effect decisions.' "$contract"
require_contains 'denied by default' "$contract"
require_contains 'decision_state=denied-gate' "$contract"
require_contains 'gate_allowed=0' "$contract"
require_contains 'effect_allowed=0' "$contract"
require_contains 'effect_performed=0' "$contract"
require_contains 'host_read_performed=0' "$contract"
require_contains 'host_write_performed=0' "$contract"
require_contains 'network_performed=0' "$contract"
require_contains 'runtime_authority_granted=0' "$contract"
require_contains 'effect decision metadata implementation' "$contract"
require_contains 'runtime handoff contract' "$contract"

printf 'seal effect decision contract: ok\n'
