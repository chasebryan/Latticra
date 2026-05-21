# Latticra Seal Request Freshness Contract

Status: Latticra Seal request freshness contract
Scope: contract for future request freshness and replay metadata after the report-only Seal parameter schema report surface. This document does not implement timestamp parsing, clock trust, nonce storage, replay-cache storage, context hashing, parameter hashing, signature verification, runtime execution, runtime authority, effect execution, capability enforcement, cryptographic verification, verified receipts, public-key parsing, public-key trust stores, key generation, private-key storage, hardware key use, network trust lookup, revocation lookup, object sealing, host reads, host writes, kernel behavior, Fedora approval claims, production readiness, MCP protocol implementation, MCP server behavior, MCP client behavior, AI agent execution, model execution, tool execution, shell execution, or operating-system behavior.

## Purpose

This document defines the next Latticra Seal contract layer for request freshness and replay metadata.

The purpose is to prepare a bounded report-only structure for describing whether a future tool request is time-scoped, nonce-scoped, context-bound, and parameter-bound before any execution or enforcement is considered.

This document does not implement request freshness behavior.

## Required predecessors

This contract depends on:

```text
docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_CONTRACT.md
docs/LATTICRA_SEAL_MCP_ALIGNMENT_PLAN.md
docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_IMPLEMENTATION.md
docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_REPORT_SURFACE.md
docs/LATTICRA_SEAL_PARAMETER_SCHEMA_CONTRACT.md
docs/LATTICRA_SEAL_PARAMETER_SCHEMA_IMPLEMENTATION.md
docs/LATTICRA_SEAL_PARAMETER_SCHEMA_REPORT_SURFACE.md
docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_STATUS.md
docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_INDEX_ALIGNMENT.md
docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_REPORT_SURFACE_STATUS.md
include/latticra/seal_parameter_schema.h
src/seal_parameter_schema.c
tests/seal_parameter_schema_invariants.c
tests/seal_parameter_schema_report_surface.c
scripts/test-latticra-seal-parameter-schema-contract.sh
scripts/test-latticra-seal-parameter-schema.sh
scripts/test-latticra-seal-parameter-schema-report-surface.sh
```

The existing parameter schema metadata surface remains report-only.

## Request freshness boundary

The request freshness layer may describe whether freshness metadata is declared, present, bounded, and reportable.

The layer may not parse trusted time, maintain a nonce cache, compare real clocks, validate signatures, authorize a request, execute tools, execute shell commands, contact networks, read host files, write host files, or mutate system state.

Allowed in this contract slice:

```text
request-freshness vocabulary
request-id metadata planning
caller-id metadata planning
tool-id metadata planning
request timestamp metadata planning
request expiration metadata planning
nonce metadata planning
context hash metadata planning
parameter hash metadata planning
freshness status planning
replay status planning
report-only status planning
non-claims
static guard validation
```

Forbidden in this contract slice:

```text
timestamp parsing
trusted clock behavior
nonce storage
replay-cache storage
context hashing
parameter hashing
freshness validation
replay detection
signature verification
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
verified receipt generation
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

## Initial request freshness policy

The initial policy is report-only and closed by default.

```text
seal_request_freshness_contract_present=1
request_freshness_supported=0
request_freshness_validation_supported=0
replay_protection_supported=0
request_id_present=0
caller_id_present=0
tool_id_present=0
request_timestamp_present=0
request_expiration_present=0
nonce_present=0
context_hash_present=0
parameter_hash_present=0
freshness_valid=0
replay_detected=0
runtime_authority_granted=0
host_read_performed=0
host_write_performed=0
network_performed=0
mode=contract-only
status=request-freshness-contract-only
```

## Planned metadata fields

Future request freshness metadata should be bounded and deterministic.

Planned fields:

```text
freshness_profile
request_id
caller_id
tool_id
request_timestamp
request_expiration
nonce
context_hash
parameter_hash
request_freshness_supported
request_freshness_validation_supported
replay_protection_supported
request_id_present
caller_id_present
tool_id_present
request_timestamp_present
request_expiration_present
nonce_present
context_hash_present
parameter_hash_present
freshness_valid
replay_detected
runtime_authority_granted
mode
decision
reason
status
```

Initial values before freshness implementation:

```text
freshness_profile=latticra-seal-request-freshness/0.1
request_id=unset
caller_id=unset
tool_id=unset
request_timestamp=unset
request_expiration=unset
nonce=unset
context_hash=unset
parameter_hash=unset
request_freshness_supported=0
request_freshness_validation_supported=0
replay_protection_supported=0
request_id_present=0
caller_id_present=0
tool_id_present=0
request_timestamp_present=0
request_expiration_present=0
nonce_present=0
context_hash_present=0
parameter_hash_present=0
freshness_valid=0
replay_detected=0
runtime_authority_granted=0
mode=contract-only
decision=report-only
reason=request-freshness-contract-only
status=request-freshness-contract-only
```

## Promotion rules

The next implementation after this contract may only add bounded C metadata fields and deterministic rendering.

It must not parse trusted time, maintain a nonce cache, compare live clocks, compute hashes, validate freshness, detect replay, execute tools, execute shell commands, call runtime components, read host files, write host files, contact networks, enforce capabilities, verify signatures, generate receipts, or grant authority.

## Claim gate

Latticra must not claim to secure AI agents from this contract alone.

A future claim that Latticra secures AI agents requires, at minimum:

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

This contract must not be read as implementation of freshness validation, replay protection, signed request verification, tool security enforcement, or AI-agent security.

Required non-claim posture:

```text
freshness_validation_implemented=0
replay_protection_implemented=0
signed_request_verification_implemented=0
mcp_tool_security_enforced=0
ai_agent_security_claimed=0
runtime_authority_granted=0
production_readiness_claimed=0
external_endorsement_claimed=0
```

## Next valid slice

The next valid Latticra Seal slice is report-only request freshness metadata.

That future slice may add a bounded metadata structure, deterministic rendering, invariant tests, and a test runner.

It must not change runtime behavior, host behavior, network behavior, MCP behavior, AI agent execution, model execution, tool execution, shell execution, capability enforcement, cryptographic verification, freshness validation, replay detection, or authority grants.
