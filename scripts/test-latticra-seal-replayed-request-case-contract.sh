#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal replayed request case contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal replayed request case contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_REPLAYED_REQUEST_CASE_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_RUNTIME_GATE_TEST_PLAN.md
require_file docs/LATTICRA_SEAL_STALE_REQUEST_CASE_CONTRACT.md
require_file docs/LATTICRA_SEAL_STALE_REQUEST_CASE_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_RUNTIME_GATE_IMPLEMENTATION.md
require_file include/latticra/seal_runtime_gate.h
require_file src/seal_runtime_gate.c
require_file tests/seal_runtime_gate_invariants.c
require_file tests/seal_stale_request_case.c
require_file scripts/test-latticra-seal-runtime-gate-test-plan.sh
require_file scripts/test-latticra-seal-stale-request-case-contract.sh
require_file scripts/test-latticra-seal-stale-request-case.sh

require_contains 'Status: Latticra Seal replayed request case contract' "$contract"
require_contains 'case_profile=latticra-seal-replayed-request-case/0.1' "$contract"
require_contains 'case_name=replayed-request' "$contract"
require_contains 'case_contract_present=1' "$contract"
require_contains 'replayed_request_case_contract_present=1' "$contract"
require_contains 'input_replay_detected=1' "$contract"
require_contains 'input_nonce_reused=1' "$contract"
require_contains 'input_request_seen_before=1' "$contract"
require_contains 'expected_gate_state=report-only' "$contract"
require_contains 'expected_default_blocked=1' "$contract"
require_contains 'expected_replayed_request_blocked=1' "$contract"
require_contains 'expected_runtime_authority_granted=0' "$contract"
require_contains 'expected_effect_performed=0' "$contract"
require_contains 'expected_host_read_performed=0' "$contract"
require_contains 'expected_host_write_performed=0' "$contract"
require_contains 'expected_network_performed=0' "$contract"
require_contains 'case_behavior_implemented=0' "$contract"
require_contains 'tests/seal_replayed_request_case.c' "$contract"
require_contains 'scripts/test-latticra-seal-replayed-request-case.sh' "$contract"
require_contains 'replayed_request_case_implemented=0' "$contract"
require_contains 'replay_detection_implemented=0' "$contract"
require_contains 'authority_granted=0' "$contract"
require_contains 'replayed request case test fixture' "$contract"

printf 'seal replayed request case contract: ok\n'
