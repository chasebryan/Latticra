# Latticra Seal Signed Request Implementation

Status: initial report-only signed request metadata implementation
Scope: bounded C metadata surface for signed request posture after the report-only Seal request freshness layer. This slice does not implement signature generation, signature verification, public-key parsing, trust-store loading, key generation, private-key storage, hardware key use, revocation lookup, network trust lookup, signed request enforcement, runtime execution, runtime authority, effect execution, capability enforcement, cryptographic verification, verified receipts, object sealing, host reads, host writes, kernel behavior, Fedora approval claims, production readiness, MCP protocol implementation, MCP server behavior, MCP client behavior, AI agent execution, model execution, tool execution, shell execution, or operating-system behavior.

## Purpose

This document records the first Latticra Seal signed request metadata implementation.

The implementation accepts an existing report-only Seal request freshness metadata record and produces deterministic report-only signed request metadata.

## Added files

```text
include/latticra/seal_signed_request.h
src/seal_signed_request.c
tests/seal_signed_request_invariants.c
scripts/test-latticra-seal-signed-request.sh
```

## API summary

The signed request metadata surface adds:

```text
latticra_seal_signed_request_t
latticra_seal_signed_request_error_t
latticra_seal_signed_request_error_label
latticra_seal_signed_request_from_freshness
latticra_seal_signed_request_is_report_only
latticra_seal_signed_request_report
```

## Metadata behavior

The implementation:

```text
accepts a valid report-only Seal request freshness metadata record
sets signed_request_profile=latticra-seal-signed-request/0.1
sets signed_request_id=unset
sets signature_algorithm=unset
sets signing_key_id=unset
sets signature_hash=unset
sets signed_request_supported=0
sets signature_generation_supported=0
sets signature_verification_supported=0
sets signature_present=0
sets signature_valid=0
sets signature_algorithm_declared=0
sets signing_key_id_present=0
sets signature_hash_present=0
sets signed_request_id_present=0
sets identity_binding_declared=0
sets context_binding_declared=0
sets parameter_binding_declared=0
sets freshness_binding_declared=0
sets policy_binding_declared=0
sets trust_store_supported=0
sets revocation_lookup_supported=0
copies runtime_authority_granted from request freshness metadata
copies host_read_performed from request freshness metadata
copies host_write_performed from request freshness metadata
copies network_performed from request freshness metadata
sets mode=report-only
sets decision=report-only
sets reason=signed-request-metadata-only
renders deterministic signed request metadata
```

## Boundary

This implementation does not generate signatures, verify signatures, parse keys, load trust stores, perform revocation lookup, contact networks, create receipts, execute tools, execute shell commands, call runtime components, read host files, write host files, enforce capabilities, or grant authority.

It is metadata only.

## Failure behavior

The implementation fails closed:

```text
null output -> LATTICRA_STATUS_NULL_ARGUMENT
null request freshness metadata input -> invalid-input
invalid request freshness metadata -> invalid-freshness
non-report-only request freshness metadata -> invalid-freshness
small report buffer -> LATTICRA_STATUS_BUFFER_TOO_SMALL
```

Failures do not generate signatures, verify signatures, parse keys, contact networks, read host files, write host files, execute tools, enforce capabilities, or grant authority.

## Invariants

The invariant test verifies:

```text
valid report-only request freshness metadata produces deterministic signed request metadata
signed_request_profile is stable
signed_request_id remains unset
signature_algorithm remains unset
signing_key_id remains unset
signature_hash remains unset
signed_request_supported remains zero
signature_generation_supported remains zero
signature_verification_supported remains zero
signature_present remains zero
signature_valid remains zero
signature_algorithm_declared remains zero
signing_key_id_present remains zero
signature_hash_present remains zero
signed_request_id_present remains zero
identity_binding_declared remains zero
context_binding_declared remains zero
parameter_binding_declared remains zero
freshness_binding_declared remains zero
policy_binding_declared remains zero
trust_store_supported remains zero
revocation_lookup_supported remains zero
runtime_authority_granted remains zero
host_read_performed remains zero
host_write_performed remains zero
network_performed remains zero
mode remains report-only
decision remains report-only
reason remains signed-request-metadata-only
small report buffer fails closed
null inputs fail closed
invalid request freshness metadata fails closed
```

## Validation

Run:

```sh
sh scripts/test-latticra-seal-signed-request-contract.sh
sh scripts/test-latticra-seal-signed-request.sh
```

## Claim boundary

This implementation still does not justify the public claim that Latticra secures AI agents.

It moves the project closer by adding report-only metadata for signed request posture, but the stronger claim requires policy decision metadata, a runtime enforcement gate, and negative tests for denied unknown, unsigned, stale, and replayed requests.

## Next valid slice

The next valid Latticra Seal slice is a signed request report surface or policy decision metadata contract.

That future slice must not implement runtime behavior, host behavior, network behavior, MCP behavior, AI agent execution, model execution, tool execution, shell execution, capability enforcement, cryptographic verification, signature verification, revocation lookup, or authority grants unless a specific contract and validation path justify it.
