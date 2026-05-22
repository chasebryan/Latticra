# Latticra Seal Runtime Dry-Run Implementation Plan

Status: implementation planning contract for a future no-effect Latticra Seal runtime dry-run surface
Scope: implementation plan only after the Latticra Seal runtime dry-run contract. This document does not implement runtime behavior, runtime execution, runtime authority, effect execution, policy enforcement, capability enforcement, cryptographic verification, signature verification, freshness validation, replay detection, tool execution, AI agent execution, model execution, MCP protocol behavior, MCP server behavior, MCP client behavior, host reads, host writes, network behavior, operating-system behavior, production readiness, external endorsement, or authority grants.

## Purpose

This plan defines the exact future implementation shape for a no-effect Seal runtime dry-run layer.

The future implementation should render what the Seal boundary would deny without executing tools, contacting networks, touching host state, or granting authority.

## Required contract

The implementation plan depends on:

```text
docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_CONTRACT.md
scripts/test-latticra-seal-runtime-dry-run-contract.sh
```

The contract must remain merged and guarded before implementation code is added.

## Future files

The future implementation slice should add:

```text
include/latticra/seal_runtime_dry_run.h
src/seal_runtime_dry_run.c
tests/seal_runtime_dry_run_invariants.c
scripts/test-latticra-seal-runtime-dry-run.sh
docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_IMPLEMENTATION.md
```

A later report-surface slice may add:

```text
tests/seal_runtime_dry_run_report_surface.c
scripts/latticra-seal-runtime-dry-run-report.sh
scripts/test-latticra-seal-runtime-dry-run-report-surface.sh
```

## Header API plan

The future header should define:

```text
LATTICRA_SEAL_RUNTIME_DRY_RUN_PROFILE_MAX
LATTICRA_SEAL_RUNTIME_DRY_RUN_STATE_MAX
LATTICRA_SEAL_RUNTIME_DRY_RUN_REASON_MAX
LATTICRA_SEAL_RUNTIME_DRY_RUN_REPORT_MAX
latticra_seal_runtime_dry_run_error_t
latticra_seal_runtime_dry_run_t
latticra_seal_runtime_dry_run_error_label
latticra_seal_runtime_dry_run_from_policy_and_gate
latticra_seal_runtime_dry_run_is_report_only
latticra_seal_runtime_dry_run_report
```

## Error model

The future error enum should include:

```text
LATTICRA_SEAL_RUNTIME_DRY_RUN_OK
LATTICRA_SEAL_RUNTIME_DRY_RUN_INVALID_INPUT
LATTICRA_SEAL_RUNTIME_DRY_RUN_INVALID_POLICY_DECISION
LATTICRA_SEAL_RUNTIME_DRY_RUN_INVALID_RUNTIME_GATE
```

## Record fields

The future record should include:

```text
runtime_dry_run_profile
request_class
policy_decision_state
runtime_gate_state
blocked_reason
status
dry_run_supported
dry_run_performed
input_policy_decision_present
input_runtime_gate_present
policy_decision_report_only
runtime_gate_report_only
default_action_deny
would_allow
would_deny
would_require_operator_review
would_execute_tool
would_read_host
would_write_host
would_use_network
would_grant_runtime_authority
unknown_tool_denied
unsigned_request_denied
invalid_schema_denied
stale_request_denied
replayed_request_denied
invalid_signature_denied
report_only
mode
error
```

## Initial constants

The initial future implementation should emit:

```text
runtime_dry_run_profile=latticra-seal-runtime-dry-run/0.1
request_class=core-blocked-request
policy_decision_state=report-only
runtime_gate_state=report-only
blocked_reason=default-deny-dry-run
status=runtime-dry-run-metadata
dry_run_supported=1
dry_run_performed=1
input_policy_decision_present=1
input_runtime_gate_present=1
policy_decision_report_only=1
runtime_gate_report_only=1
default_action_deny=1
would_allow=0
would_deny=1
would_require_operator_review=1
would_execute_tool=0
would_read_host=0
would_write_host=0
would_use_network=0
would_grant_runtime_authority=0
unknown_tool_denied=1
unsigned_request_denied=1
invalid_schema_denied=1
stale_request_denied=1
replayed_request_denied=1
invalid_signature_denied=1
report_only=1
mode=report-only
```

## Function behavior

The future builder should:

```text
accept a report-only Seal policy decision metadata input
accept a report-only Seal runtime gate metadata input
reject null output
return invalid-input for null upstream inputs
return invalid-policy-decision for non-report-only policy decision metadata
return invalid-runtime-gate for non-report-only runtime gate metadata
copy no authority from upstream inputs
render deterministic metadata only
```

## Required report format

The report should begin with:

```text
LATTICRA SEAL RUNTIME DRY RUN
```

It should render all fields as stable `key=value` lines.

Required report fields:

```text
runtime_dry_run_profile=latticra-seal-runtime-dry-run/0.1
request_class=core-blocked-request
policy_decision_state=report-only
runtime_gate_state=report-only
blocked_reason=default-deny-dry-run
would_allow=0
would_deny=1
would_require_operator_review=1
would_execute_tool=0
would_read_host=0
would_write_host=0
would_use_network=0
would_grant_runtime_authority=0
report_only=1
mode=report-only
status=runtime-dry-run-metadata
```

## Required invariant tests

The future invariant test should verify:

```text
valid report-only inputs produce dry-run metadata
runtime_dry_run_profile is stable
request_class is core-blocked-request
policy_decision_state remains report-only
runtime_gate_state remains report-only
blocked_reason is default-deny-dry-run
dry_run_supported remains one
dry_run_performed remains one
would_allow remains zero
would_deny remains one
would_require_operator_review remains one
would_execute_tool remains zero
would_read_host remains zero
would_write_host remains zero
would_use_network remains zero
would_grant_runtime_authority remains zero
all core denied case flags remain one
report_only remains one
mode remains report-only
status remains runtime-dry-run-metadata
small report buffers fail closed
null inputs fail closed
invalid upstream metadata fails closed
```

## Required build runner

The future test runner should compile only local C sources and fixtures.

Planned runner:

```sh
sh scripts/test-latticra-seal-runtime-dry-run.sh
```

It should compile:

```text
src/seal_runtime_dry_run.c
src/seal_runtime_gate.c
src/seal_policy_decision.c
src/seal_signed_request.c
src/seal_request_freshness.c
src/seal_parameter_schema.c
src/seal_agentic_automation_security.c
src/seal_status_rollup.c
tests/seal_runtime_dry_run_invariants.c
```

## Explicit non-goals

The future implementation must not:

```text
execute tools
execute shell commands
read host files
write host files
use the network
evaluate external policies
load policy files
verify signatures
validate freshness against live time
mutate replay caches
grant authority
claim production readiness
claim AI-agent security
claim MCP implementation
```

## Promotion rule

No runtime enforcement work may begin from this plan alone.

A future C implementation must first be merged with tests, a report surface, status record, and negative-case evidence while preserving the report-only boundary.

## Current next valid slice

The next valid Latticra Seal slice is the no-effect runtime dry-run implementation.

That future slice must implement only deterministic metadata, local fixtures, fail-closed behavior, and report rendering. It must not perform effects or grant authority.