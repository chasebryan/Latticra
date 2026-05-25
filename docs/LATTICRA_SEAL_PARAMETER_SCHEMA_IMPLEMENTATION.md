# Latticra Seal Parameter Schema Implementation

Status: initial report-only parameter schema metadata implementation
Scope: bounded C metadata surface for parameter schema posture after the report-only Seal agentic automation security layer. This slice does not implement schema parsing, schema validation, runtime execution, runtime authority, effect execution, capability enforcement, cryptographic verification, verified receipts, public-key parsing, public-key trust stores, key generation, private-key storage, hardware key use, network trust lookup, revocation lookup, object sealing, host reads, host writes, kernel behavior, Fedora approval claims, production readiness, MCP protocol implementation, MCP server behavior, MCP client behavior, AI agent execution, model execution, tool execution, shell execution, or operating-system behavior.

## Purpose

This document records the first Latticra Seal parameter schema metadata implementation.

The implementation accepts an existing report-only Seal agentic automation security metadata record and produces deterministic report-only parameter schema metadata.

## Added files

```text
include/latticra/seal_parameter_schema.h
src/seal_parameter_schema.c
tests/seal_parameter_schema_invariants.c
scripts/test-latticra-seal-parameter-schema.sh
```

## API summary

The parameter schema metadata surface adds:

```text
latticra_seal_parameter_schema_t
latticra_seal_parameter_schema_error_t
latticra_seal_parameter_schema_error_label
latticra_seal_parameter_schema_from_agentic
latticra_seal_parameter_schema_is_report_only
latticra_seal_parameter_schema_report
```

## Metadata behavior

The implementation:

```text
accepts a valid report-only Seal agentic automation security metadata record
sets schema_profile=latticra-seal-parameter-schema/0.1
sets schema_id=unset
sets schema_version=unset
sets schema_language=unset
sets schema_hash=unset
copies schema_present from agentic parameter schema metadata
sets schema_parsing_supported=0
sets schema_validation_supported=0
copies schema_valid from agentic parameter schema metadata
sets max_input_bytes_declared=0
sets parameter_count_declared=0
sets required_parameter_count_declared=0
sets unknown_parameters_allowed=0
sets parameter_forwarding_allowed=0
sets input_size_within_limit=0
sets parameter_names_reported=0
copies runtime_authority_granted from agentic metadata
copies host_read_performed from agentic metadata
copies host_write_performed from agentic metadata
copies network_performed from agentic metadata
sets mode=report-only
sets decision=report-only
sets reason=parameter-schema-metadata-only
renders deterministic parameter schema metadata
```

## Boundary

This implementation does not parse schemas, validate schemas, implement a schema language, execute tools, execute shell commands, call runtime components, contact networks, read host files, write host files, verify signatures, generate receipts, enforce capabilities, or grant authority.

It is metadata only.

## Failure behavior

The implementation fails closed:

```text
null output -> LATTICRA_STATUS_NULL_ARGUMENT
null agentic metadata input -> invalid-input
invalid agentic metadata -> invalid-agentic
non-report-only agentic metadata -> invalid-agentic
small report buffer -> LATTICRA_STATUS_BUFFER_TOO_SMALL
```

Failures do not parse schemas, validate schemas, contact networks, read host files, write host files, execute tools, enforce capabilities, or grant authority.

## Invariants

The invariant test verifies:

```text
valid report-only agentic metadata produces deterministic parameter schema metadata
schema_profile is stable
schema_id remains unset
schema_version remains unset
schema_language remains unset
schema_hash remains unset
schema_present remains zero
schema_parsing_supported remains zero
schema_validation_supported remains zero
schema_valid remains zero
max_input_bytes_declared remains zero
parameter_count_declared remains zero
required_parameter_count_declared remains zero
unknown_parameters_allowed remains zero
parameter_forwarding_allowed remains zero
input_size_within_limit remains zero
parameter_names_reported remains zero
runtime_authority_granted remains zero
host_read_performed remains zero
host_write_performed remains zero
network_performed remains zero
mode remains report-only
decision remains report-only
reason remains parameter-schema-metadata-only
small report buffer fails closed
null inputs fail closed
invalid agentic metadata fails closed
```

## Validation

Run:

```sh
sh scripts/test-latticra-seal-parameter-schema-contract.sh
sh scripts/test-latticra-seal-parameter-schema.sh
```

## Next valid slice

The next valid Latticra Seal slice is request freshness status/public-entry alignment.

That future slice must not implement timestamp parsing, trusted clock behavior, nonce storage, replay-cache storage, context hashing, parameter hashing, freshness validation, replay detection, schema parsing, schema validation, runtime behavior, host behavior, network behavior, MCP behavior, AI agent execution, model execution, tool execution, shell execution, capability enforcement, cryptographic verification, or authority grants.
