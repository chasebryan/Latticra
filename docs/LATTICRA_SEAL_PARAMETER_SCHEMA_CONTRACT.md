# Latticra Seal Parameter Schema Contract

Status: Latticra Seal parameter schema contract
Scope: contract for future parameter schema metadata after the report-only Seal agentic automation security report surface. This document does not implement schema parsing, schema validation, runtime execution, runtime authority, effect execution, capability enforcement, cryptographic verification, verified receipts, public-key parsing, public-key trust stores, key generation, private-key storage, hardware key use, network trust lookup, revocation lookup, object sealing, host reads, host writes, kernel behavior, Fedora approval claims, production readiness, MCP protocol implementation, MCP server behavior, MCP client behavior, AI agent execution, model execution, tool execution, shell execution, or operating-system behavior.

## Purpose

This document defines the next Latticra Seal contract layer for declared parameter-schema metadata.

The purpose is to prepare a bounded report-only structure for describing tool-request parameters before any future validation or enforcement is considered.

This document does not implement parameter schema behavior.

## Required predecessors

This contract depends on:

```text
docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_CONTRACT.md
docs/LATTICRA_SEAL_MCP_ALIGNMENT_PLAN.md
docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_IMPLEMENTATION.md
docs/LATTICRA_SEAL_AGENTIC_AUTOMATION_SECURITY_REPORT_SURFACE.md
docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_STATUS.md
docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_INDEX_ALIGNMENT.md
docs/status/SEAL_AGENTIC_AUTOMATION_SECURITY_REPORT_SURFACE_STATUS.md
include/latticra/seal_agentic_automation_security.h
src/seal_agentic_automation_security.c
tests/seal_agentic_automation_security_invariants.c
tests/seal_agentic_automation_security_report_surface.c
scripts/test-latticra-seal-agentic-automation-security.sh
scripts/test-latticra-seal-agentic-automation-security-report-surface.sh
```

The existing agentic automation metadata surface remains report-only.

## Parameter schema boundary

The parameter schema layer may describe whether parameter schema metadata is declared, present, bounded, and reportable.

The layer may not validate arbitrary schemas, parse untrusted schema languages, accept model output as authority, grant runtime authority, execute tools, execute shell commands, contact networks, read host files, write host files, or mutate system state.

Allowed in this contract slice:

```text
parameter-schema vocabulary
schema-presence metadata planning
schema-id metadata planning
schema-version metadata planning
schema-hash metadata planning
max-input-size metadata planning
parameter-count metadata planning
required-parameter-count metadata planning
unknown-parameter policy planning
parameter-forwarding policy planning
report-only status planning
non-claims
static guard validation
```

Forbidden in this contract slice:

```text
schema parsing
schema validation
schema language implementation
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

## Initial parameter schema policy

The initial policy is report-only and closed by default.

```text
seal_parameter_schema_contract_present=1
parameter_schema_supported=0
parameter_schema_parsing_supported=0
parameter_schema_validation_supported=0
parameter_schema_present=0
parameter_schema_valid=0
schema_language_supported=0
schema_hash_present=0
max_input_bytes_declared=0
parameter_count_declared=0
required_parameter_count_declared=0
unknown_parameters_allowed=0
parameter_forwarding_allowed=0
runtime_authority_granted=0
host_read_performed=0
host_write_performed=0
network_performed=0
mode=contract-only
status=parameter-schema-contract-only
```

## Planned metadata fields

Future parameter schema metadata should be bounded and deterministic.

Planned fields:

```text
schema_profile
schema_id
schema_version
schema_language
schema_hash
schema_present
schema_parsing_supported
schema_validation_supported
schema_valid
max_input_bytes_declared
parameter_count_declared
required_parameter_count_declared
unknown_parameters_allowed
parameter_forwarding_allowed
input_size_within_limit
parameter_names_reported
runtime_authority_granted
mode
decision
reason
status
```

Initial values before schema implementation:

```text
schema_profile=latticra-seal-parameter-schema/0.1
schema_id=unset
schema_version=unset
schema_language=unset
schema_hash=unset
schema_present=0
schema_parsing_supported=0
schema_validation_supported=0
schema_valid=0
max_input_bytes_declared=0
parameter_count_declared=0
required_parameter_count_declared=0
unknown_parameters_allowed=0
parameter_forwarding_allowed=0
input_size_within_limit=0
parameter_names_reported=0
runtime_authority_granted=0
mode=contract-only
decision=report-only
reason=parameter-schema-contract-only
status=parameter-schema-contract-only
```

## Promotion rules

The next implementation after this contract may only add bounded C metadata fields and deterministic rendering.

It must not parse schema languages, validate untrusted schemas, execute tools, execute shell commands, call runtime components, read host files, write host files, contact networks, enforce capabilities, verify signatures, generate receipts, or grant authority.

## Non-claims

This contract must not be read as implementation of parameter validation or MCP tool-security enforcement.

Required non-claim posture:

```text
parameter_validation_implemented=0
schema_parser_implemented=0
schema_validator_implemented=0
mcp_tool_security_enforced=0
runtime_authority_granted=0
production_readiness_claimed=0
external_endorsement_claimed=0
```

## Next valid slice

The next valid Latticra Seal slice is report-only parameter schema metadata.

That future slice may add a bounded metadata structure, deterministic rendering, invariant tests, and a test runner.

It must not change runtime behavior, host behavior, network behavior, MCP behavior, AI agent execution, model execution, tool execution, shell execution, capability enforcement, cryptographic verification, or authority grants.
