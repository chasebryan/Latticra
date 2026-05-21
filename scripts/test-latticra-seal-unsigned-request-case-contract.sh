#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal unsigned request case contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal unsigned request case contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

contract="docs/LATTICRA_SEAL_UNSIGNED_REQUEST_CASE_CONTRACT.md"

require_file "$contract"
require_file docs/LATTICRA_SEAL_RUNTIME_GATE_TEST_PLAN.md
require_file docs/LATTICRA_SEAL_UNKNOWN_TOOL_CASE_CONTRACT.md
require_file docs/LATTICRA_SEAL_UNKNOWN_TOOL_CASE_IMPLEMENTATION.md
require_file docs/LATTICRA_SEAL_RUNTIME_GATE_IMPLEMENTATION.md
require_file include/latticra/seal_runtime_gate.h
require_file src/seal_runtime_gate.c
require_file tests/seal_runtime_gate_invariants.c
require_file tests/seal_unknown_tool_case.c
require_file scripts/test-latticra-seal-runtime-gate-test-plan.sh
require_file scripts/test-latticra-seal-unknown-tool-case-contract.sh
require_file scripts/test-latticra-seal-unknown-tool-case.sh

require_contains 'Status: Latticra Seal unsigned request case contract' "$contract"
require_contains 'case_profile=latticra-seal-unsigned-request-case/0.1' "$contract"
require_contains 'case_name=unsigned-request' "$contract"
require_contains 'case_contract_present=1' "$contract"
require_contains 'unsigned_request_case_contract_present=1' "$contract"
require_contains 'input_signature_present=0' "$contract"
require_contains 'input_signature_valid=0' "$contract"
require_contains 'input_signed_request_present=0' "$contract"
require_contains 'expected_gate_state=report-only' "$contract"
require_contains 'expected_default_blocked=1' "$contract"
require_contains 'expected_unsigned_request_blocked=1' "$contract"
require_contains 'expected_runtime_authority_granted=0' "$contract"
require_contains 'expected_effect_performed=0' "$contract"
require_contains 'expected_host_read_performed=0' "$contract"
require_contains 'expected_host_write_performed=0' "$contract"
require_contains 'expected_network_performed=0' "$contract"
require_contains 'case_behavior_implemented=0' "$contract"
require_contains 'tests/seal_unsigned_request_case.c' "$contract"
require_contains 'scripts/test-latticra-seal-unsigned-request-case.sh' "$contract"
require_contains 'unsigned_request_case_implemented=0' "$contract"
require_contains 'signature_verification_implemented=0' "$contract"
require_contains 'authority_granted=0' "$contract"
require_contains 'unsigned request case test fixture' "$contract"

printf 'seal unsigned request case contract: ok\n'
