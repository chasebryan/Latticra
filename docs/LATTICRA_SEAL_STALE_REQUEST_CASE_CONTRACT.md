# Latticra Seal Stale Request Case Contract

Status: Latticra Seal stale request case contract
Scope: case-specific contract after the unsigned request case fixture. This document does not implement runtime behavior, policy behavior, tool behavior, host behavior, network behavior, cryptographic behavior, freshness validation, replay detection, or authority grants.

## Purpose

This document defines the third case-specific test contract for the Seal runtime gate path.

The case is a stale request. The expected posture is that the gate remains report-only, blocked by default, and grants no authority.

This document does not implement the case behavior.

## Required predecessors

```text
docs/LATTICRA_SEAL_RUNTIME_GATE_TEST_PLAN.md
docs/LATTICRA_SEAL_UNKNOWN_TOOL_CASE_CONTRACT.md
docs/LATTICRA_SEAL_UNKNOWN_TOOL_CASE_IMPLEMENTATION.md
docs/LATTICRA_SEAL_UNSIGNED_REQUEST_CASE_CONTRACT.md
docs/LATTICRA_SEAL_UNSIGNED_REQUEST_CASE_IMPLEMENTATION.md
docs/LATTICRA_SEAL_RUNTIME_GATE_IMPLEMENTATION.md
include/latticra/seal_runtime_gate.h
src/seal_runtime_gate.c
tests/seal_runtime_gate_invariants.c
tests/seal_unknown_tool_case.c
tests/seal_unsigned_request_case.c
scripts/test-latticra-seal-runtime-gate-test-plan.sh
scripts/test-latticra-seal-unknown-tool-case.sh
scripts/test-latticra-seal-unsigned-request-case.sh
```

## Case definition

```text
case_profile=latticra-seal-stale-request-case/0.1
case_name=stale-request
case_contract_present=1
stale_request_case_contract_present=1
input_request_timestamp_present=1
input_request_expiration_present=1
input_freshness_valid=0
expected_gate_state=report-only
expected_default_blocked=1
expected_stale_request_blocked=1
expected_runtime_authority_granted=0
expected_effect_performed=0
expected_host_read_performed=0
expected_host_write_performed=0
expected_network_performed=0
case_behavior_implemented=0
```

## Future test requirements

A future implementation must add a deterministic test fixture showing that a stale request case remains blocked and does not perform effects.

Planned future file names:

```text
tests/seal_stale_request_case.c
scripts/test-latticra-seal-stale-request-case.sh
```

Expected future output:

```text
seal stale request case: ok
```

## Boundary

This contract is documentation-only.

It does not add case execution, runtime behavior, host behavior, network behavior, MCP behavior, AI agent behavior, model behavior, tool behavior, shell behavior, policy behavior, freshness validation, replay detection, cryptographic behavior, or authority grants.

## Claim gate

This contract alone does not justify the public claim that Latticra secures AI agents.

The accurate public claim remains:

```text
Latticra Seal is building a report-only trust boundary for AI-era automation.
```

A stronger claim requires implemented and validated gate behavior plus case tests for unknown, unsigned, stale, and replayed requests.

## Non-claims

```text
stale_request_case_implemented=0
runtime_gate_case_tests_implemented=0
runtime_behavior_implemented=0
policy_behavior_implemented=0
tool_behavior_implemented=0
host_behavior_implemented=0
network_behavior_implemented=0
freshness_validation_implemented=0
replay_detection_implemented=0
authority_granted=0
production_readiness_claimed=0
external_endorsement_claimed=0
```

## Next valid slice

The next valid Latticra Seal slice is the stale request case test fixture.
