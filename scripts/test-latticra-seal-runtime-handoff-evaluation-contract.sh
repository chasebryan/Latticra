#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal runtime handoff evaluation contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal runtime handoff evaluation contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_VERIFIED_EFFECT_DECISION_IMPLEMENTATION.md
require_file include/latticra/seal_verified_effect_decision.h
require_file src/seal_verified_effect_decision.c
require_file tests/seal_verified_effect_decision_invariants.c
require_file scripts/test-latticra-seal-verified-effect-decision.sh

require_contains 'Status: Latticra Seal runtime handoff evaluation contract' "$contract"
require_contains 'The evaluation is handoff classification, not runtime handoff.' "$contract"
require_contains 'require effect_allowed=1' "$contract"
require_contains 'require decision_state=allowed-report-only' "$contract"
require_contains 'require decision_state=allowed-evaluate-only' "$contract"
require_contains 'classify report-only as handoff_state=eligible-report-only' "$contract"
require_contains 'classify evaluate-only as handoff_state=eligible-evaluate-only' "$contract"
require_contains 'handoff_eligible=1' "$contract"
require_contains 'handoff_performed=0' "$contract"
require_contains 'effect_performed=0' "$contract"
require_contains 'runtime_authority_granted=0' "$contract"
require_contains 'host_read_performed=0' "$contract"
require_contains 'host_write_performed=0' "$contract"
require_contains 'network_performed=0' "$contract"
require_contains 'handoff_state=denied-decision' "$contract"
require_contains 'handoff_state=denied-effect' "$contract"
require_contains 'handoff_state=denied-runtime-authority' "$contract"
require_contains 'handoff_state=denied-host-effect' "$contract"
require_contains 'handoff_state=denied-network-effect' "$contract"
require_contains 'runtime handoff evaluation metadata implementation' "$contract"
require_contains 'runtime handoff report surface' "$contract"
require_contains 'sh scripts/test-latticra-seal-runtime-handoff-evaluation-contract.sh' "$contract"

printf 'seal runtime handoff evaluation contract: ok\n'
