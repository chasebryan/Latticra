# Latticra Seal Core Blocked Cases Status

Status: status record for the completed core blocked-request case set
Scope: status alignment after the unknown-tool, unsigned-request, stale-request, and replayed-request case fixtures. This record does not implement runtime behavior, enforcement, execution, effects, host operations, network operations, cryptographic verification, or authority grants.

## Purpose

This status record marks the first completed core negative-test evidence set for the Latticra Seal runtime gate metadata path.

The completed set verifies that the report-only runtime gate metadata path keeps the gate blocked and grants no authority for four core request classes.

## Completed case fixtures

```text
unknown_tool_case_fixture_present=1
unsigned_request_case_fixture_present=1
stale_request_case_fixture_present=1
replayed_request_case_fixture_present=1
core_blocked_case_set_present=1
core_blocked_case_set_complete=1
```

## Reviewed files

```text
docs/LATTICRA_SEAL_UNKNOWN_TOOL_CASE_CONTRACT.md
docs/LATTICRA_SEAL_UNKNOWN_TOOL_CASE_IMPLEMENTATION.md
docs/LATTICRA_SEAL_UNSIGNED_REQUEST_CASE_CONTRACT.md
docs/LATTICRA_SEAL_UNSIGNED_REQUEST_CASE_IMPLEMENTATION.md
docs/LATTICRA_SEAL_STALE_REQUEST_CASE_CONTRACT.md
docs/LATTICRA_SEAL_STALE_REQUEST_CASE_IMPLEMENTATION.md
docs/LATTICRA_SEAL_REPLAYED_REQUEST_CASE_CONTRACT.md
docs/LATTICRA_SEAL_REPLAYED_REQUEST_CASE_IMPLEMENTATION.md
tests/seal_unknown_tool_case.c
tests/seal_unsigned_request_case.c
tests/seal_stale_request_case.c
tests/seal_replayed_request_case.c
scripts/test-latticra-seal-unknown-tool-case.sh
scripts/test-latticra-seal-unsigned-request-case.sh
scripts/test-latticra-seal-stale-request-case.sh
scripts/test-latticra-seal-replayed-request-case.sh
```

## Validation

Run:

```sh
sh scripts/test-latticra-seal-unknown-tool-case.sh
sh scripts/test-latticra-seal-unsigned-request-case.sh
sh scripts/test-latticra-seal-stale-request-case.sh
sh scripts/test-latticra-seal-replayed-request-case.sh
```

Expected outputs:

```text
seal unknown tool case: ok
seal unsigned request case: ok
seal stale request case: ok
seal replayed request case: ok
```

## Evidence posture

```text
core_case_unknown_tool_validated=1
core_case_unsigned_request_validated=1
core_case_stale_request_validated=1
core_case_replayed_request_validated=1
runtime_gate_report_only=1
runtime_authority_granted=0
effect_performed=0
host_read_performed=0
host_write_performed=0
network_performed=0
```

## Public claim boundary

This status record is an important milestone, but it does not yet justify saying that Latticra broadly secures AI agents.

A careful public claim may now say:

```text
Latticra Seal now has a report-only runtime gate path with core negative-test evidence for AI-era tool-boundary planning.
```

The stronger claim still requires guarded runtime enforcement behavior and an operator-visible evidence report.

## Non-claims

```text
ai_agent_security_claimed=0
runtime_enforcement_implemented=0
policy_enforcement_implemented=0
tool_execution_implemented=0
host_behavior_implemented=0
network_behavior_implemented=0
authority_granted=0
production_readiness_claimed=0
external_endorsement_claimed=0
```

## Next valid slice

The next valid slice is public milestone wording for the report-only core case evidence set, or an operator-visible evidence report surface that summarizes the full Seal chain.
