# Latticra Seal Signed Request Contract

Status: Latticra Seal signed request contract
Scope: contract for future signed request metadata after the report-only Seal request freshness report surface. This document does not implement signature generation, signature verification, public-key parsing, trust-store loading, key generation, private-key storage, hardware key use, signed request enforcement, runtime execution, runtime authority, effect execution, capability enforcement, cryptographic verification, verified receipts, network trust lookup, revocation lookup, object sealing, host reads, host writes, kernel behavior, Fedora approval claims, production readiness, MCP protocol implementation, MCP server behavior, MCP client behavior, AI agent execution, model execution, tool execution, shell execution, or operating-system behavior.

## Purpose

This document defines the next Latticra Seal contract layer for signed request metadata.

The purpose is to prepare a bounded report-only structure for describing whether a future tool request carries declared signature metadata and whether the signed material is expected to bind identity, context, parameters, freshness, and policy intent.

This document does not implement signed request behavior.

## Required predecessors

This contract depends on:

```text
docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_CONTRACT.md
docs/LATTICRA_SEAL_MCP_ALIGNMENT_PLAN.md
docs/LATTICRA_SEAL_PARAMETER_SCHEMA_CONTRACT.md
docs/LATTICRA_SEAL_PARAMETER_SCHEMA_IMPLEMENTATION.md
docs/LATTICRA_SEAL_PARAMETER_SCHEMA_REPORT_SURFACE.md
docs/LATTICRA_SEAL_REQUEST_FRESHNESS_CONTRACT.md
docs/LATTICRA_SEAL_REQUEST_FRESHNESS_IMPLEMENTATION.md
docs/LATTICRA_SEAL_REQUEST_FRESHNESS_REPORT_SURFACE.md
include/latticra/seal_request_freshness.h
src/seal_request_freshness.c
tests/seal_request_freshness_invariants.c
tests/seal_request_freshness_report_surface.c
scripts/test-latticra-seal-request-freshness-contract.sh
scripts/test-latticra-seal-request-freshness.sh
scripts/test-latticra-seal-request-freshness-report-surface.sh
```

The existing request freshness metadata surface remains report-only.

## Signed request boundary

The signed request layer may describe signature metadata fields, expected binding fields, and report-only verification posture.

The layer may not generate signatures, verify signatures, parse keys, load trust stores, contact networks, check revocation, authorize a request, execute tools, execute shell commands, read host files, write host files, or mutate system state.

Allowed in this contract slice:

```text
signed-request vocabulary
signature-presence metadata planning
signature-algorithm metadata planning
signing-key-id metadata planning
signature-hash metadata planning
signed-request-id planning
identity-binding metadata planning
context-binding metadata planning
parameter-binding metadata planning
freshness-binding metadata planning
policy-binding metadata planning
verification-status planning
report-only status planning
non-claims
static guard validation
```

Forbidden in this contract slice:

```text
signature generation
signature verification
public-key parsing
public-key trust store loading
private-key handling
key generation
hardware key use
revocation lookup
network trust lookup
signed request enforcement
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
object sealing
kernel interaction
MCP server implementation
MCP client implementation
```

## Initial signed request policy

The initial policy is report-only and closed by default.

```text
seal_signed_request_contract_present=1
signed_request_supported=0
signature_generation_supported=0
signature_verification_supported=0
signature_present=0
signature_valid=0
signature_algorithm_declared=0
signing_key_id_present=0
signature_hash_present=0
signed_request_id_present=0
identity_binding_declared=0
context_binding_declared=0
parameter_binding_declared=0
freshness_binding_declared=0
policy_binding_declared=0
trust_store_supported=0
revocation_lookup_supported=0
runtime_authority_granted=0
host_read_performed=0
host_write_performed=0
network_performed=0
mode=contract-only
status=signed-request-contract-only
```

## Planned metadata fields

Future signed request metadata should be bounded and deterministic.

Planned fields:

```text
signed_request_profile
signed_request_id
signature_algorithm
signing_key_id
signature_hash
signed_request_supported
signature_generation_supported
signature_verification_supported
signature_present
signature_valid
signature_algorithm_declared
signing_key_id_present
signature_hash_present
signed_request_id_present
identity_binding_declared
context_binding_declared
parameter_binding_declared
freshness_binding_declared
policy_binding_declared
trust_store_supported
revocation_lookup_supported
runtime_authority_granted
mode
decision
reason
status
```

Initial values before signed request implementation:

```text
signed_request_profile=latticra-seal-signed-request/0.1
signed_request_id=unset
signature_algorithm=unset
signing_key_id=unset
signature_hash=unset
signed_request_supported=0
signature_generation_supported=0
signature_verification_supported=0
signature_present=0
signature_valid=0
signature_algorithm_declared=0
signing_key_id_present=0
signature_hash_present=0
signed_request_id_present=0
identity_binding_declared=0
context_binding_declared=0
parameter_binding_declared=0
freshness_binding_declared=0
policy_binding_declared=0
trust_store_supported=0
revocation_lookup_supported=0
runtime_authority_granted=0
mode=contract-only
decision=report-only
reason=signed-request-contract-only
status=signed-request-contract-only
```

## Promotion rules

The next implementation after this contract may only add bounded C metadata fields and deterministic rendering.

It must not generate signatures, verify signatures, parse keys, load trust stores, perform revocation lookup, contact networks, execute tools, execute shell commands, call runtime components, read host files, write host files, enforce capabilities, generate receipts, or grant authority.

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

This contract must not be read as implementation of signed request verification, tool security enforcement, cryptographic enforcement, or AI-agent security.

Required non-claim posture:

```text
signed_request_verification_implemented=0
signature_generation_implemented=0
signature_verification_implemented=0
trust_store_implemented=0
revocation_lookup_implemented=0
mcp_tool_security_enforced=0
ai_agent_security_claimed=0
runtime_authority_granted=0
production_readiness_claimed=0
external_endorsement_claimed=0
```

## Next valid slice

The next valid Latticra Seal slice is report-only signed request metadata.

That future slice may add a bounded metadata structure, deterministic rendering, invariant tests, and a test runner.

It must not change runtime behavior, host behavior, network behavior, MCP behavior, AI agent execution, model execution, tool execution, shell execution, capability enforcement, cryptographic verification, signature verification, revocation lookup, or authority grants.
