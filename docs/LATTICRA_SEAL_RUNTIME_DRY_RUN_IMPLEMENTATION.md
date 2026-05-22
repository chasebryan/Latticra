# Latticra Seal Runtime Dry-Run Implementation

Status: initial no-effect runtime dry-run metadata implementation
Scope: bounded C metadata surface for Latticra Seal runtime dry-run posture after the policy decision report surface and runtime gate metadata path. This implementation does not add runtime behavior, runtime execution, runtime authority, effect execution, policy enforcement, capability enforcement, cryptographic verification, signature verification, freshness validation, replay detection, tool execution, AI agent execution, model execution, MCP protocol behavior, MCP server behavior, MCP client behavior, host reads, host writes, network behavior, operating-system behavior, production readiness, external endorsement, or authority grants.

## Purpose

This document records the first Latticra Seal runtime dry-run metadata implementation.

The implementation accepts report-only policy decision metadata and report-only runtime gate metadata, then renders deterministic metadata describing what the boundary would deny without doing it.

## Added files

```text
include/latticra/seal_runtime_dry_run.h
src/seal_runtime_dry_run.c
tests/seal_runtime_dry_run_invariants.c
scripts/test-latticra-seal-runtime-dry-run.sh
```

## API summary

The dry-run metadata surface adds:

```text
latticra_seal_runtime_dry_run_t
latticra_seal_runtime_dry_run_error_t
latticra_seal_runtime_dry_run_error_label
latticra_seal_runtime_dry_run_from_policy_and_gate
latticra_seal_runtime_dry_run_is_report_only
latticra_seal_runtime_dry_run_report
```

## Metadata behavior

The implementation:

```text
accepts report-only policy decision metadata
accepts report-only runtime gate metadata
sets runtime_dry_run_profile=latticra-seal-runtime-dry-run/0.1
sets request_class=core-blocked-request
sets policy_decision_state=report-only
sets runtime_gate_state=report-only
sets blocked_reason=default-deny-dry-run
sets status=runtime-dry-run-metadata
sets dry_run_supported=1
sets dry_run_performed=1
sets input_policy_decision_present=1
sets input_runtime_gate_present=1
sets policy_decision_report_only=1
sets runtime_gate_report_only=1
sets default_action_deny=1
sets would_allow=0
sets would_deny=1
sets would_require_operator_review=1
sets would_execute_tool=0
sets would_read_host=0
sets would_write_host=0
sets would_use_network=0
sets would_grant_runtime_authority=0
sets unknown_tool_denied=1
sets unsigned_request_denied=1
sets invalid_schema_denied=1
sets stale_request_denied=1
sets replayed_request_denied=1
sets invalid_signature_denied=1
sets report_only=1
sets mode=report-only
renders deterministic runtime dry-run metadata
```

## Failure behavior

The implementation fails closed:

```text
null output -> LATTICRA_STATUS_NULL_ARGUMENT
null policy decision input -> invalid-input
null runtime gate input -> invalid-input
invalid policy decision metadata -> invalid-policy-decision
invalid runtime gate metadata -> invalid-runtime-gate
small report buffer -> LATTICRA_STATUS_BUFFER_TOO_SMALL
```

Failures do not evaluate policies, contact networks, read host files, write host files, execute tools, enforce capabilities, or grant authority.

## Invariants

The invariant test verifies:

```text
valid report-only inputs produce dry-run metadata
runtime_dry_run_profile is stable
request_class remains core-blocked-request
policy_decision_state remains report-only
runtime_gate_state remains report-only
blocked_reason remains default-deny-dry-run
dry_run_supported remains one
dry_run_performed remains one
input policy decision remains present
input runtime gate remains present
policy decision remains report-only
runtime gate remains report-only
default action remains deny
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
report rendering is deterministic
small report buffers fail closed
null inputs fail closed
invalid upstream metadata fails closed
```

## Validation

Run:

```sh
sh scripts/test-latticra-seal-runtime-dry-run-contract.sh
sh scripts/test-latticra-seal-runtime-dry-run-implementation-plan.sh
sh scripts/test-latticra-seal-runtime-dry-run.sh
```

Expected new output:

```text
seal runtime dry-run invariants: ok
```

## Boundary

This implementation is metadata-only.

It does not execute tools, execute shell commands, read host files, write host files, use the network, evaluate external policies, load policy files, verify signatures, validate freshness against live time, mutate replay caches, grant authority, claim production readiness, claim AI-agent security, or claim MCP implementation.

## Claim boundary

This implementation does not justify the public claim that Latticra secures AI agents.

It moves the project closer by adding a no-effect dry-run layer that can describe what would be denied before any runtime enforcement path is considered.

## Next valid slice

The next valid Latticra Seal slice is a runtime dry-run report surface or runtime dry-run status alignment.

That future slice must preserve the no-effect posture and must not perform effects or grant authority.