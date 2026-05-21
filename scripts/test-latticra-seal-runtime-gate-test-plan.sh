#!/usr/bin/env sh
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'seal runtime gate test plan: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal runtime gate test plan: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

plan="docs/LATTICRA_SEAL_RUNTIME_GATE_TEST_PLAN.md"

require_file "$plan"
require_file docs/LATTICRA_SEAL_RUNTIME_ENFORCEMENT_GATE_CONTRACT.md
require_file docs/LATTICRA_SEAL_RUNTIME_GATE_IMPLEMENTATION.md
require_file include/latticra/seal_runtime_gate.h
require_file src/seal_runtime_gate.c
require_file tests/seal_runtime_gate_invariants.c
require_file scripts/test-latticra-seal-runtime-gate-contract.sh
require_file scripts/test-latticra-seal-runtime-gate.sh

require_contains 'Status: runtime gate test planning record' "$plan"
require_contains 'unknown_tool_case_planned=1' "$plan"
require_contains 'unsigned_request_case_planned=1' "$plan"
require_contains 'invalid_schema_case_planned=1' "$plan"
require_contains 'stale_request_case_planned=1' "$plan"
require_contains 'replayed_request_case_planned=1' "$plan"
require_contains 'invalid_signature_case_planned=1' "$plan"
require_contains 'missing_operator_approval_case_planned=1' "$plan"
require_contains 'host_read_without_authority_case_planned=1' "$plan"
require_contains 'host_write_without_authority_case_planned=1' "$plan"
require_contains 'network_without_authority_case_planned=1' "$plan"
require_contains 'expected_runtime_authority_granted=0' "$plan"
require_contains 'expected_effect_performed=0' "$plan"
require_contains 'expected_host_read_performed=0' "$plan"
require_contains 'expected_host_write_performed=0' "$plan"
require_contains 'expected_network_performed=0' "$plan"
require_contains 'This plan alone does not justify the public claim that Latticra secures AI agents.' "$plan"
require_contains 'runtime_gate_case_tests_implemented=0' "$plan"
require_contains 'authority_granted=0' "$plan"
require_contains 'unknown tool case' "$plan"

printf 'seal runtime gate test plan: ok\n'
