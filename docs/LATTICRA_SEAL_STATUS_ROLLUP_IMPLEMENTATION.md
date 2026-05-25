# Latticra Seal Status Rollup Implementation

Status: initial status rollup metadata implementation
Scope: bounded C metadata surface for status rollup posture after runtime handoff metadata. This slice does not implement runtime execution, runtime authority, effect execution, capability enforcement, cryptographic verification, verified receipts, public-key parsing, public-key trust stores, key generation, private-key storage, hardware key use, network trust lookup, revocation lookup, object sealing, host reads, host writes, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document records the first Latticra Seal status rollup metadata implementation.

The implementation accepts an existing runtime handoff metadata record and produces deterministic status rollup metadata for the implemented Seal chain.

## Added files

```text
include/latticra/seal_status_rollup.h
src/seal_status_rollup.c
tests/seal_status_rollup_invariants.c
scripts/test-latticra-seal-status-rollup.sh
```

## API summary

The status rollup metadata surface adds:

```text
latticra_seal_status_rollup_t
latticra_seal_status_rollup_error_t
latticra_seal_status_rollup_error_label
latticra_seal_status_rollup_from_handoff
latticra_seal_status_rollup_is_metadata_only
latticra_seal_status_rollup_report
```

## Rollup behavior

The implementation:

```text
accepts a valid runtime handoff metadata record
sets report_present=1
sets measurement_present=1
sets manifest_present=1
sets signature_policy_present=1
sets signature_metadata_present=1
sets verification_policy_present=1
sets verification_receipt_present=1
sets capability_gate_present=1
sets effect_decision_present=1
sets runtime_handoff_present=1
sets cryptographic_verification_supported=0
sets verified=0
sets capability_gate_allowed=0
copies effect_allowed from handoff metadata
copies handoff_active from handoff metadata
copies runtime_boundary_state from handoff metadata
copies runtime_authority_granted from handoff metadata
copies host_read_performed from handoff metadata
copies host_write_performed from handoff metadata
copies network_performed from handoff metadata
sets rollup_state=metadata-only
renders deterministic status rollup metadata
```

## Boundary

This implementation does not verify signatures, parse public keys, create keys, store keys, contact networks, query revocation status, persist status records, enforce capabilities, perform host reads, perform host writes, execute network behavior, call runtime components, or grant runtime authority.

It is metadata only.

## Failure behavior

The implementation fails closed:

```text
null status rollup output -> LATTICRA_STATUS_NULL_ARGUMENT
null runtime handoff metadata input -> invalid-input
invalid runtime handoff metadata -> invalid-handoff
small report buffer -> LATTICRA_STATUS_BUFFER_TOO_SMALL
```

Failures do not parse keys, create keys, persist secrets, contact networks, verify records, sign records, read host files, write host files, enforce capabilities, perform effects, call runtime components, or grant runtime authority.

## Invariants

The invariant test verifies:

```text
valid runtime handoff metadata produces deterministic status rollup metadata
report_present is one
measurement_present is one
manifest_present is one
signature_policy_present is one
signature_metadata_present is one
verification_policy_present is one
verification_receipt_present is one
capability_gate_present is one
effect_decision_present is one
runtime_handoff_present is one
cryptographic_verification_supported remains zero
verified remains zero
capability_gate_allowed remains zero
effect_allowed remains zero
handoff_active remains zero
runtime_boundary_state remains disabled
runtime_authority_granted remains zero
host_read_performed remains zero
host_write_performed remains zero
network_performed remains zero
rollup_state remains metadata-only
small report buffer fails closed
null inputs fail closed
invalid runtime handoff metadata fails closed
```

## Validation

Run:

```sh
sh scripts/test-latticra-seal-status-rollup-contract.sh
sh scripts/test-latticra-seal-status-rollup.sh
sh scripts/test-latticra-seal-status-rollup-status.sh
sh scripts/test-latticra-seal-runtime-handoff-status.sh
sh scripts/test-latticra-seal-agentic-automation-security-status.sh
```

## Next valid slice

The next valid Latticra Seal slice is a Seal agentic automation security public README/status/foundation entry-point refresh or a dedicated report command surface.

That future slice must not change runtime behavior, host behavior, network behavior, MCP behavior, AI agent execution, model execution, tool execution, shell execution, capability enforcement, cryptographic verification, or authority posture.
