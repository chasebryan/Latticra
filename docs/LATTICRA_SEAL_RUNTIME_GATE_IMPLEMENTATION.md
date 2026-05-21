# Latticra Seal Runtime Gate Implementation

Status: initial report-only runtime gate metadata implementation
Scope: bounded C metadata surface for runtime gate posture after the report-only Seal policy decision layer. This slice does not implement runtime enforcement, allow/deny enforcement, runtime execution, runtime authority, effect execution, tool execution, shell execution, capability enforcement, cryptographic verification, signature verification, public-key parsing, trust-store loading, freshness validation, replay detection, network trust lookup, revocation lookup, object sealing, host reads, host writes, kernel behavior, Fedora approval claims, production readiness, MCP protocol implementation, MCP server behavior, MCP client behavior, AI agent execution, model execution, or operating-system behavior.

## Purpose

This document records the first Latticra Seal runtime gate metadata implementation.

The implementation accepts an existing report-only Seal policy decision metadata record and produces deterministic report-only runtime gate metadata.

## Added files

```text
include/latticra/seal_runtime_gate.h
src/seal_runtime_gate.c
tests/seal_runtime_gate_invariants.c
scripts/test-latticra-seal-runtime-gate.sh
```

## API summary

The runtime gate metadata surface adds:

```text
latticra_seal_runtime_gate_t
latticra_seal_runtime_gate_error_t
latticra_seal_runtime_gate_error_label
latticra_seal_runtime_gate_from_policy_decision
latticra_seal_runtime_gate_is_report_only
latticra_seal_runtime_gate_report
```

## Metadata behavior

The implementation:

```text
accepts a valid report-only Seal policy decision metadata record
sets runtime_enforcement_gate_profile=latticra-seal-runtime-enforcement-gate/0.1
sets gate_id=unset
sets gate_version=unset
sets gate_state=report-only
sets runtime_enforcement_gate_supported=0
sets runtime_enforcement_supported=0
sets runtime_enforcement_active=0
sets policy_decision_input_supported=0
sets policy_decision_consumed=0
sets gate_id_present=0
sets gate_version_present=0
sets runtime_handoff_eligible=0
sets runtime_handoff_performed=0
sets allow_enforcement_supported=0
sets deny_enforcement_supported=0
sets allow_enforcement_performed=0
sets deny_enforcement_performed=0
sets effect_performed=0
sets default_blocked=1
sets operator_review_required=1
sets unknown_tool_blocked=1
sets unsigned_request_blocked=1
sets invalid_schema_blocked=1
sets stale_request_blocked=1
sets replayed_request_blocked=1
sets invalid_signature_blocked=1
copies runtime_authority_granted from policy decision metadata
copies host_read_performed from policy decision metadata
copies host_write_performed from policy decision metadata
copies network_performed from policy decision metadata
sets mode=report-only
sets decision=report-only
sets reason=runtime-gate-metadata-only
renders deterministic runtime gate metadata
```

## Boundary

This implementation does not enforce allow outcomes, enforce deny outcomes, execute tools, execute shell commands, call runtime components, contact networks, read host files, write host files, verify signatures, validate freshness, detect replay, enforce capabilities, perform effects, or grant authority.

It is metadata only.

## Failure behavior

The implementation fails closed:

```text
null output -> LATTICRA_STATUS_NULL_ARGUMENT
null policy decision metadata input -> invalid-input
invalid policy decision metadata -> invalid-policy-decision
non-report-only policy decision metadata -> invalid-policy-decision
small report buffer -> LATTICRA_STATUS_BUFFER_TOO_SMALL
```

Failures do not evaluate policy, contact networks, read host files, write host files, execute tools, enforce capabilities, or grant authority.

## Invariants

The invariant test verifies:

```text
valid report-only policy decision metadata produces deterministic runtime gate metadata
runtime_enforcement_gate_profile is stable
gate_id remains unset
gate_version remains unset
gate_state remains report-only
runtime_enforcement_gate_supported remains zero
runtime_enforcement_supported remains zero
runtime_enforcement_active remains zero
policy_decision_input_supported remains zero
policy_decision_consumed remains zero
runtime_handoff_eligible remains zero
runtime_handoff_performed remains zero
allow_enforcement_supported remains zero
deny_enforcement_supported remains zero
allow_enforcement_performed remains zero
deny_enforcement_performed remains zero
effect_performed remains zero
default_blocked remains one
operator_review_required remains one
unknown_tool_blocked remains one
unsigned_request_blocked remains one
invalid_schema_blocked remains one
stale_request_blocked remains one
replayed_request_blocked remains one
invalid_signature_blocked remains one
runtime_authority_granted remains zero
host_read_performed remains zero
host_write_performed remains zero
network_performed remains zero
mode remains report-only
decision remains report-only
reason remains runtime-gate-metadata-only
small report buffer fails closed
null inputs fail closed
invalid policy decision metadata fails closed
```

## Validation

Run:

```sh
sh scripts/test-latticra-seal-runtime-gate-contract.sh
sh scripts/test-latticra-seal-runtime-gate.sh
```

## Claim boundary

This implementation still does not justify the public claim that Latticra secures AI agents.

It moves the project closer by adding report-only runtime gate metadata, but the stronger claim requires negative tests for denied unknown, unsigned, stale, and replayed requests plus a guarded enforcement path that actually blocks effects.

## Next valid slice

The next valid Latticra Seal slice is negative-test planning for blocked request classes or a runtime gate report surface.

That future slice must not implement runtime behavior, host behavior, network behavior, MCP behavior, AI agent execution, model execution, tool execution, shell execution, capability enforcement, cryptographic verification, signature verification, freshness validation, replay detection, policy enforcement, runtime enforcement, or authority grants unless a specific contract and validation path justify it.
