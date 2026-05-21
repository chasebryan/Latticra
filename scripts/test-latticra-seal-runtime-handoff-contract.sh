#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal runtime handoff contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal runtime handoff contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_RUNTIME_HANDOFF_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_EFFECT_DECISION_IMPLEMENTATION.md
require_file include/latticra/seal_effect_decision.h
require_file src/seal_effect_decision.c
require_file scripts/test-latticra-seal-effect-decision.sh

require_contains 'Status: Latticra Seal runtime handoff contract' "$contract"
require_contains 'This document does not implement runtime handoff behavior.' "$contract"
require_contains 'denied by default' "$contract"
require_contains 'handoff_state=denied-decision' "$contract"
require_contains 'effect_allowed=0' "$contract"
require_contains 'effect_performed=0' "$contract"
require_contains 'runtime_boundary_state=disabled' "$contract"
require_contains 'handoff_active=0' "$contract"
require_contains 'runtime_effect_performed=0' "$contract"
require_contains 'host_read_performed=0' "$contract"
require_contains 'host_write_performed=0' "$contract"
require_contains 'network_performed=0' "$contract"
require_contains 'runtime_authority_granted=0' "$contract"
require_contains 'runtime handoff metadata implementation' "$contract"
require_contains 'Seal status rollup contract' "$contract"

printf 'seal runtime handoff contract: ok\n'
