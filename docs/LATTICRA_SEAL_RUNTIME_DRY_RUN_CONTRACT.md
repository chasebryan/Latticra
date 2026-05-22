# Latticra Seal Runtime Dry-Run Contract

Status: planning contract for a future Latticra Seal runtime dry-run surface
Scope: contract-only planning for a future no-effect dry-run layer after the report-only policy decision and runtime gate evidence path. This document does not implement runtime behavior, runtime execution, runtime authority, effect execution, policy enforcement, capability enforcement, cryptographic verification, signature verification, freshness validation, replay detection, tool execution, AI agent execution, model execution, MCP protocol behavior, MCP server behavior, MCP client behavior, host reads, host writes, network behavior, operating-system behavior, production readiness, external endorsement, or authority grants.

## Purpose

This contract defines the next safe Latticra Seal step before any runtime enforcement work can be considered.

The future dry-run surface should answer one question:

```text
If this request reached the Seal runtime boundary, what would the boundary report, deny, and refuse to do?
```

The answer must remain no-effect, deterministic, local, and report-only.

## Required prerequisites

A future implementation may begin only after these existing layers remain present and guarded:

```text
seal_agentic_automation_metadata_present=1
seal_parameter_schema_metadata_present=1
seal_request_freshness_metadata_present=1
seal_signed_request_metadata_present=1
seal_policy_decision_metadata_present=1
seal_policy_decision_report_surface_present=1
seal_runtime_gate_metadata_present=1
seal_core_blocked_case_set_complete=1
```

## Future record shape

A future dry-run record should expose bounded metadata fields similar to:

```text
runtime_dry_run_profile=latticra-seal-runtime-dry-run/0.1
input_policy_decision_present
input_runtime_gate_present
dry_run_supported
dry_run_performed
request_class
policy_decision_state
runtime_gate_state
default_action
would_allow
would_deny
would_require_operator_review
would_execute_tool
would_read_host
would_write_host
would_use_network
would_grant_runtime_authority
blocked_reason
report_only
mode
status
```

## Initial required defaults

The initial implementation, if added later, must default to:

```text
dry_run_supported=1
dry_run_performed=1
default_action=deny
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

## Required denied cases

The dry-run surface must preserve the existing core blocked-request vocabulary:

```text
unknown_tool_denied=1
unsigned_request_denied=1
invalid_schema_denied=1
stale_request_denied=1
replayed_request_denied=1
invalid_signature_denied=1
```

## Forbidden behavior

The dry-run layer must not:

```text
evaluate real policy files
enforce policy
execute tools
execute shell commands
call a runtime executor
read host files
write host files
perform network operations
verify signatures
validate freshness against live time
perform replay-cache mutation
generate keys
load private keys
load trust stores
query revocation services
grant runtime authority
claim production readiness
claim AI-agent security
claim MCP implementation
```

## Required report surface

A future implementation must include a deterministic report renderer and a local fixture runner.

Required future files:

```text
include/latticra/seal_runtime_dry_run.h
src/seal_runtime_dry_run.c
tests/seal_runtime_dry_run_invariants.c
tests/seal_runtime_dry_run_report_surface.c
scripts/test-latticra-seal-runtime-dry-run.sh
scripts/latticra-seal-runtime-dry-run-report.sh
docs/LATTICRA_SEAL_RUNTIME_DRY_RUN_IMPLEMENTATION.md
```

## Required tests

A future implementation must prove:

```text
valid report-only policy decision input produces denied dry-run metadata
valid report-only runtime gate input remains report-only
unknown tool remains denied
unsigned request remains denied
invalid schema remains denied
stale request remains denied
replayed request remains denied
invalid signature remains denied
no runtime authority is granted
no host read is performed
no host write is performed
no network action is performed
no tool execution is performed
report rendering is deterministic
small buffers fail closed
null inputs fail closed
invalid upstream metadata fails closed
```

## Promotion rule

This contract does not authorize runtime enforcement.

Runtime enforcement may be considered only after a dry-run implementation, dry-run report surface, status record, status-index alignment, and negative-case evidence all remain merged and guarded.

## Boundary

This is a contract-only planning slice.

It does not change implementation behavior, add runtime behavior, grant authority, or change public readiness.

## Current next valid slice

The next valid slice is a no-effect runtime dry-run implementation plan.

That future slice must still avoid implementation behavior and must specify exact structs, fields, APIs, report format, fixtures, tests, and failure behavior before any C code is added.