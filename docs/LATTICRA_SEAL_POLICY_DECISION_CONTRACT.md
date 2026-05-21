# Latticra Seal Policy Decision Contract

Status: Latticra Seal policy decision contract
Scope: contract for future policy decision metadata after the report-only Seal signed request metadata layer. This document does not implement policy evaluation, allow/deny enforcement, runtime execution, runtime authority, effect execution, capability enforcement, cryptographic verification, signature verification, public-key parsing, trust-store loading, key generation, private-key storage, hardware key use, revocation lookup, network trust lookup, object sealing, host reads, host writes, kernel behavior, Fedora approval claims, production readiness, MCP protocol implementation, MCP server behavior, MCP client behavior, AI agent execution, model execution, tool execution, shell execution, or operating-system behavior.

## Purpose

This document defines the next Latticra Seal contract layer for policy decision metadata.

The purpose is to prepare a bounded report-only structure for describing whether a future signed request would be treated as allowed, denied, unsupported, or review-required by a policy gate.

This document does not implement policy decision behavior.

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
include/latticra/seal_signed_request.h
src/seal_signed_request.c
tests/seal_signed_request_invariants.c
scripts/test-latticra-seal-signed-request-contract.sh
scripts/test-latticra-seal-signed-request.sh
```

The existing signed request metadata surface remains report-only.

## Policy decision boundary

The policy decision layer may describe policy-decision metadata, default-deny posture, deny reasons, and future promotion rules.

The layer may not evaluate real policy, enforce decisions, execute tools, execute shell commands, contact networks, read host files, write host files, verify signatures, validate freshness, detect replay, or mutate system state.

Allowed in this contract slice:

```text
policy-decision vocabulary
policy-id metadata planning
policy-version metadata planning
decision-state planning
default-deny metadata planning
deny-reason metadata planning
unknown-tool denial planning
unsigned-request denial planning
invalid-schema denial planning
stale-request denial planning
replayed-request denial planning
signature-invalid denial planning
operator-review planning
report-only status planning
non-claims
static guard validation
```

Forbidden in this contract slice:

```text
policy evaluation
policy enforcement
allow decision enforcement
deny decision enforcement
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

## Initial policy decision posture

The initial policy is report-only and default-deny.

```text
seal_policy_decision_contract_present=1
policy_decision_supported=0
policy_evaluation_supported=0
policy_enforcement_supported=0
policy_id_present=0
policy_version_present=0
requested_action_present=0
requested_tool_present=0
signed_request_present=0
signature_valid=0
schema_valid=0
freshness_valid=0
replay_detected=0
default_decision=deny
decision_state=report-only
decision_allowed=0
decision_denied=1
operator_review_required=1
unknown_tool_denied=1
unsigned_request_denied=1
invalid_schema_denied=1
stale_request_denied=1
replayed_request_denied=1
invalid_signature_denied=1
runtime_authority_granted=0
host_read_performed=0
host_write_performed=0
network_performed=0
mode=contract-only
status=policy-decision-contract-only
```

## Planned metadata fields

Future policy decision metadata should be bounded and deterministic.

Planned fields:

```text
policy_decision_profile
policy_id
policy_version
requested_action
requested_tool
policy_decision_supported
policy_evaluation_supported
policy_enforcement_supported
policy_id_present
policy_version_present
requested_action_present
requested_tool_present
signed_request_present
signature_valid
schema_valid
freshness_valid
replay_detected
default_decision
decision_state
decision_allowed
decision_denied
operator_review_required
unknown_tool_denied
unsigned_request_denied
invalid_schema_denied
stale_request_denied
replayed_request_denied
invalid_signature_denied
runtime_authority_granted
mode
decision
reason
status
```

Initial values before policy decision implementation:

```text
policy_decision_profile=latticra-seal-policy-decision/0.1
policy_id=unset
policy_version=unset
requested_action=unset
requested_tool=unset
policy_decision_supported=0
policy_evaluation_supported=0
policy_enforcement_supported=0
policy_id_present=0
policy_version_present=0
requested_action_present=0
requested_tool_present=0
signed_request_present=0
signature_valid=0
schema_valid=0
freshness_valid=0
replay_detected=0
default_decision=deny
decision_state=report-only
decision_allowed=0
decision_denied=1
operator_review_required=1
unknown_tool_denied=1
unsigned_request_denied=1
invalid_schema_denied=1
stale_request_denied=1
replayed_request_denied=1
invalid_signature_denied=1
runtime_authority_granted=0
mode=contract-only
decision=report-only
reason=policy-decision-contract-only
status=policy-decision-contract-only
```

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

This contract must not be read as implementation of policy enforcement, tool security enforcement, cryptographic enforcement, or AI-agent security.

Required non-claim posture:

```text
policy_evaluation_implemented=0
policy_enforcement_implemented=0
runtime_enforcement_implemented=0
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

The next valid Latticra Seal slice is report-only policy decision metadata.

That future slice may add a bounded metadata structure, deterministic rendering, invariant tests, and a test runner.

It must not change runtime behavior, host behavior, network behavior, MCP behavior, AI agent execution, model execution, tool execution, shell execution, capability enforcement, cryptographic verification, signature verification, freshness validation, replay detection, policy enforcement, or authority grants.
