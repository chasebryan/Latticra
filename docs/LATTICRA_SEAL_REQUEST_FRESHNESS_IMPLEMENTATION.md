# Latticra Seal Request Freshness Implementation

Status: initial report-only request freshness metadata implementation
Scope: bounded C metadata surface for request freshness and replay posture after the report-only Seal parameter schema layer. This slice does not implement timestamp parsing, trusted clock behavior, nonce storage, replay-cache storage, context hashing, parameter hashing, freshness validation, replay detection, signature verification, runtime execution, runtime authority, effect execution, capability enforcement, cryptographic verification, verified receipts, public-key parsing, public-key trust stores, key generation, private-key storage, hardware key use, network trust lookup, revocation lookup, object sealing, host reads, host writes, kernel behavior, Fedora approval claims, production readiness, MCP protocol implementation, MCP server behavior, MCP client behavior, AI agent execution, model execution, tool execution, shell execution, or operating-system behavior.

## Purpose

This document records the first Latticra Seal request freshness metadata implementation.

The implementation accepts an existing report-only Seal parameter schema metadata record and produces deterministic report-only request freshness metadata.

## Added files

```text
include/latticra/seal_request_freshness.h
src/seal_request_freshness.c
tests/seal_request_freshness_invariants.c
scripts/test-latticra-seal-request-freshness.sh
```

## API summary

The request freshness metadata surface adds:

```text
latticra_seal_request_freshness_t
latticra_seal_request_freshness_error_t
latticra_seal_request_freshness_error_label
latticra_seal_request_freshness_from_schema
latticra_seal_request_freshness_is_report_only
latticra_seal_request_freshness_report
```

## Metadata behavior

The implementation:

```text
accepts a valid report-only Seal parameter schema metadata record
sets freshness_profile=latticra-seal-request-freshness/0.1
sets request_id=unset
sets caller_id=unset
sets tool_id=unset
sets request_timestamp=unset
sets request_expiration=unset
sets nonce=unset
sets context_hash=unset
sets parameter_hash=unset
sets request_freshness_supported=0
sets request_freshness_validation_supported=0
sets replay_protection_supported=0
sets request_id_present=0
sets caller_id_present=0
sets tool_id_present=0
sets request_timestamp_present=0
sets request_expiration_present=0
sets nonce_present=0
sets context_hash_present=0
sets parameter_hash_present=0
sets freshness_valid=0
sets replay_detected=0
copies runtime_authority_granted from parameter schema metadata
copies host_read_performed from parameter schema metadata
copies host_write_performed from parameter schema metadata
copies network_performed from parameter schema metadata
sets mode=report-only
sets decision=report-only
sets reason=request-freshness-metadata-only
renders deterministic request freshness metadata
```

## Boundary

This implementation does not parse timestamps, compare clocks, store nonces, maintain a replay cache, compute hashes, validate freshness, detect replay, verify signatures, parse keys, create receipts, execute tools, execute shell commands, call runtime components, contact networks, read host files, write host files, enforce capabilities, or grant authority.

It is metadata only.

## Failure behavior

The implementation fails closed:

```text
null output -> LATTICRA_STATUS_NULL_ARGUMENT
null parameter schema metadata input -> invalid-input
invalid parameter schema metadata -> invalid-schema
non-report-only parameter schema metadata -> invalid-schema
small report buffer -> LATTICRA_STATUS_BUFFER_TOO_SMALL
```

Failures do not parse time, read clocks, store nonces, contact networks, read host files, write host files, execute tools, enforce capabilities, or grant authority.

## Invariants

The invariant test verifies:

```text
valid report-only parameter schema metadata produces deterministic request freshness metadata
freshness_profile is stable
request_id remains unset
caller_id remains unset
tool_id remains unset
request_timestamp remains unset
request_expiration remains unset
nonce remains unset
context_hash remains unset
parameter_hash remains unset
request_freshness_supported remains zero
request_freshness_validation_supported remains zero
replay_protection_supported remains zero
request_id_present remains zero
caller_id_present remains zero
tool_id_present remains zero
request_timestamp_present remains zero
request_expiration_present remains zero
nonce_present remains zero
context_hash_present remains zero
parameter_hash_present remains zero
freshness_valid remains zero
replay_detected remains zero
runtime_authority_granted remains zero
host_read_performed remains zero
host_write_performed remains zero
network_performed remains zero
mode remains report-only
decision remains report-only
reason remains request-freshness-metadata-only
small report buffer fails closed
null inputs fail closed
invalid parameter schema metadata fails closed
```

## Validation

Run:

```sh
sh scripts/test-latticra-seal-request-freshness-contract.sh
sh scripts/test-latticra-seal-request-freshness.sh
```

## Claim boundary

This implementation still does not justify the public claim that Latticra secures AI agents.

It moves the project closer by adding report-only metadata for freshness and replay posture, but the stronger claim requires signed request metadata, policy decision metadata, a runtime enforcement gate, and negative tests for denied unknown, unsigned, stale, and replayed requests.

## Next valid slice

The next valid Latticra Seal slice is a request freshness report surface or a signed request metadata contract.

That future slice must not implement runtime behavior, host behavior, network behavior, MCP behavior, AI agent execution, model execution, tool execution, shell execution, capability enforcement, cryptographic verification, freshness validation, replay detection, or authority grants unless a specific contract and validation path justify it.
