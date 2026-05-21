#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal runtime gate contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal runtime gate contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_RUNTIME_ENFORCEMENT_GATE_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_POLICY_DECISION_CONTRACT.md
require_file docs/LATTICRA_SEAL_POLICY_DECISION_IMPLEMENTATION.md
require_file include/latticra/seal_policy_decision.h
require_file src/seal_policy_decision.c
require_file scripts/test-latticra-seal-policy-decision-contract.sh
require_file scripts/test-latticra-seal-policy-decision.sh

require_contains 'Status: Latticra Seal runtime enforcement gate contract' "$contract"
require_contains 'This document does not implement runtime enforcement behavior.' "$contract"
require_contains 'seal_runtime_enforcement_gate_contract_present=1' "$contract"
require_contains 'runtime_enforcement_gate_supported=0' "$contract"
require_contains 'runtime_enforcement_supported=0' "$contract"
require_contains 'runtime_enforcement_active=0' "$contract"
require_contains 'policy_decision_input_supported=0' "$contract"
require_contains 'policy_decision_consumed=0' "$contract"
require_contains 'gate_state=report-only' "$contract"
require_contains 'runtime_handoff_eligible=0' "$contract"
require_contains 'runtime_handoff_performed=0' "$contract"
require_contains 'effect_performed=0' "$contract"
require_contains 'default_blocked=1' "$contract"
require_contains 'operator_review_required=1' "$contract"
require_contains 'runtime_authority_granted=0' "$contract"
require_contains 'host_read_performed=0' "$contract"
require_contains 'host_write_performed=0' "$contract"
require_contains 'network_performed=0' "$contract"
require_contains 'mode=contract-only' "$contract"
require_contains 'status=runtime-enforcement-gate-contract-only' "$contract"
require_contains 'negative tests showing that the enforcement path denies or blocks' "$contract"
require_contains 'Latticra must not claim to secure AI agents from this contract alone.' "$contract"
require_contains 'runtime enforcement gate implemented' "$contract"
require_contains 'runtime_enforcement_implemented=0' "$contract"
require_contains 'policy_enforcement_implemented=0' "$contract"
require_contains 'ai_agent_security_claimed=0' "$contract"
require_contains 'report-only runtime enforcement gate metadata' "$contract"

printf 'seal runtime gate contract: ok\n'
