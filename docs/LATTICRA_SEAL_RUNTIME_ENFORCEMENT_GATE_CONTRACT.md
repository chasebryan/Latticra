# Latticra Seal Runtime Enforcement Gate Contract

Status: Latticra Seal runtime enforcement gate contract
Scope: contract for future runtime enforcement-gate metadata after the report-only Seal policy decision metadata layer. This document does not implement runtime enforcement, allow/deny enforcement, runtime execution, runtime authority, effect execution, tool execution, shell execution, capability enforcement, cryptographic verification, signature verification, public-key parsing, trust-store loading, freshness validation, replay detection, network trust lookup, revocation lookup, object sealing, host reads, host writes, kernel behavior, Fedora approval claims, production readiness, MCP protocol implementation, MCP server behavior, MCP client behavior, AI agent execution, model execution, or operating-system behavior.

## Purpose

This document defines the Latticra Seal runtime enforcement gate contract.

The purpose is to prepare a bounded, evidence-bound gate layer that will eventually consume policy-decision metadata and report whether a requested action would remain blocked, require operator review, or be eligible for future runtime handoff.

This document does not implement runtime enforcement behavior.

## Required predecessors

This contract depends on:

```text
docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_CONTRACT.md
docs/LATTICRA_SEAL_MCP_ALIGNMENT_PLAN.md
docs/LATTICRA_SEAL_PARAMETER_SCHEMA_CONTRACT.md
docs/LATTICRA_SEAL_PARAMETER_SCHEMA_IMPLEMENTATION.md
docs/LATTICRA_SEAL_REQUEST_FRESHNESS_CONTRACT.md
docs/LATTICRA_SEAL_REQUEST_FRESHNESS_IMPLEMENTATION.md
docs/LATTICRA_SEAL_SIGNED_REQUEST_CONTRACT.md
docs/LATTICRA_SEAL_SIGNED_REQUEST_IMPLEMENTATION.md
docs/LATTICRA_SEAL_POLICY_DECISION_CONTRACT.md
docs/LATTICRA_SEAL_POLICY_DECISION_IMPLEMENTATION.md
include/latticra/seal_policy_decision.h
src/seal_policy_decision.c
tests/seal_policy_decision_invariants.c
scripts/test-latticra-seal-policy-decision-contract.sh
scripts/test-latticra-seal-policy-decision.sh
```

The existing policy decision metadata surface remains report-only and default-deny.

## Runtime enforcement gate boundary

The runtime enforcement gate layer may describe future enforcement-gate metadata, blocked-state metadata, operator-review metadata, and eligibility metadata.

The layer may not enforce allow or deny outcomes, execute tools, execute shell commands, call runtime components, contact networks, read host files, write host files, verify signatures, validate freshness, detect replay, or mutate system state.

Allowed in this contract slice:

```text
runtime-enforcement-gate vocabulary
gate-id metadata planning
gate-version metadata planning
gate-state metadata planning
policy-decision input planning
default-blocked posture planning
operator-review-required planning
unknown-tool blocked planning
unsigned-request blocked planning
invalid-schema blocked planning
stale-request blocked planning
replayed-request blocked planning
invalid-signature blocked planning
runtime-handoff eligibility planning
negative-test planning
report-only status planning
non-claims
static guard validation
```

Forbidden in this contract slice:

```text
runtime enforcement
allow enforcement
deny enforcement
runtime execution
AI agent execution
model execution
tool execution
shell command execution
runtime authority grants
effect execution
host reads
host writes
network access
capability enforcement
cryptographic verification
signature verification
freshness validation
replay detection
policy evaluation
policy enforcement
public-key parsing
public-key trust store loading
private-key handling
key generation
signature generation
revocation lookup
object sealing
kernel interaction
MCP server implementation
MCP client implementation
```

## Initial runtime enforcement gate posture

The initial policy is report-only, blocked, and deny-by-default.

```text
seal_runtime_enforcement_gate_contract_present=1
runtime_enforcement_gate_supported=0
runtime_enforcement_supported=0
runtime_enforcement_active=0
policy_decision_input_supported=0
policy_decision_consumed=0
gate_id_present=0
gate_version_present=0
gate_state=report-only
runtime_handoff_eligible=0
runtime_handoff_performed=0
allow_enforcement_supported=0
deny_enforcement_supported=0
allow_enforcement_performed=0
deny_enforcement_performed=0
effect_performed=0
default_blocked=1
operator_review_required=1
unknown_tool_blocked=1
unsigned_request_blocked=1
invalid_schema_blocked=1
stale_request_blocked=1
replayed_request_blocked=1
invalid_signature_blocked=1
runtime_authority_granted=0
host_read_performed=0
host_write_performed=0
network_performed=0
mode=contract-only
status=runtime-enforcement-gate-contract-only
```

## Planned metadata fields

Future runtime enforcement gate metadata should be bounded and deterministic.

Planned fields:

```text
runtime_enforcement_gate_profile
gate_id
gate_version
gate_state
runtime_enforcement_gate_supported
runtime_enforcement_supported
runtime_enforcement_active
policy_decision_input_supported
policy_decision_consumed
gate_id_present
gate_version_present
runtime_handoff_eligible
runtime_handoff_performed
allow_enforcement_supported
deny_enforcement_supported
allow_enforcement_performed
deny_enforcement_performed
effect_performed
default_blocked
operator_review_required
unknown_tool_blocked
unsigned_request_blocked
invalid_schema_blocked
stale_request_blocked
replayed_request_blocked
invalid_signature_blocked
runtime_authority_granted
host_read_performed
host_write_performed
network_performed
mode
decision
reason
status
```

Initial values before runtime enforcement implementation:

```text
runtime_enforcement_gate_profile=latticra-seal-runtime-enforcement-gate/0.1
gate_id=unset
gate_version=unset
gate_state=report-only
runtime_enforcement_gate_supported=0
runtime_enforcement_supported=0
runtime_enforcement_active=0
policy_decision_input_supported=0
policy_decision_consumed=0
gate_id_present=0
gate_version_present=0
runtime_handoff_eligible=0
runtime_handoff_performed=0
allow_enforcement_supported=0
deny_enforcement_supported=0
allow_enforcement_performed=0
deny_enforcement_performed=0
effect_performed=0
default_blocked=1
operator_review_required=1
unknown_tool_blocked=1
unsigned_request_blocked=1
invalid_schema_blocked=1
stale_request_blocked=1
replayed_request_blocked=1
invalid_signature_blocked=1
runtime_authority_granted=0
host_read_performed=0
host_write_performed=0
network_performed=0
mode=contract-only
decision=report-only
reason=runtime-enforcement-gate-contract-only
status=runtime-enforcement-gate-contract-only
```

## Negative-test requirements before enforcement claims

Before any future claim that Latticra secures AI-agent tool execution boundaries, the repository must include negative tests showing that the enforcement path denies or blocks:

```text
unknown tools
unsigned requests
invalid schemas
stale requests
replayed requests
invalid signatures
requests without operator approval when approval is required
requests attempting host reads without declared authority
requests attempting host writes without declared authority
requests attempting network access without declared authority
```

Those tests must remain separate from this contract slice.

## Promotion rules

The next implementation after this contract may only add bounded C metadata fields and deterministic rendering.

It must not evaluate real policies, enforce allow or deny outcomes, execute tools, execute shell commands, call runtime components, read host files, write host files, contact networks, verify signatures, validate freshness, detect replay, enforce capabilities, generate receipts, or grant authority.

## Claim gate

Latticra must not claim to secure AI agents from this contract alone.

A future claim that Latticra secures AI-agent tool execution boundaries requires, at minimum:

```text
request identity metadata implemented
parameter schema metadata implemented
request freshness metadata implemented
signed request metadata implemented
policy decision metadata implemented
runtime enforcement gate implemented
negative tests for denied unknown tools
negative tests for denied unsigned manifests
negative tests for denied stale requests
negative tests for denied replayed requests
operator-visible evidence report implemented
```

Until those are implemented and validated, the accurate public claim remains:

```text
Latticra Seal is building a report-only trust boundary for AI-era automation.
```

## Non-claims

This contract must not be read as implementation of runtime enforcement, tool security enforcement, cryptographic enforcement, or AI-agent security.

Required non-claim posture:

```text
runtime_enforcement_implemented=0
policy_enforcement_implemented=0
allow_enforcement_implemented=0
deny_enforcement_implemented=0
signed_request_verification_implemented=0
freshness_validation_implemented=0
replay_detection_implemented=0
mcp_tool_security_enforced=0
ai_agent_security_claimed=0
runtime_authority_granted=0
production_readiness_claimed=0
external_endorsement_claimed=0
```

## Next valid slice

The next valid Latticra Seal slice is report-only runtime enforcement gate metadata.

That future slice may add a bounded metadata structure, deterministic rendering, invariant tests, and a test runner.

It must not change runtime behavior, host behavior, network behavior, MCP behavior, AI agent execution, model execution, tool execution, shell execution, capability enforcement, cryptographic verification, signature verification, freshness validation, replay detection, policy enforcement, runtime enforcement, or authority grants.
