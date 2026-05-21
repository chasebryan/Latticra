# Latticra Seal Runtime Handoff Implementation

Status: initial runtime handoff metadata implementation
Scope: bounded C metadata surface for runtime handoff posture after effect decision metadata. This slice does not implement runtime execution, runtime authority, effect execution, capability enforcement, cryptographic verification, verified receipts, public-key parsing, public-key trust stores, key generation, private-key storage, hardware key use, network trust lookup, revocation lookup, object sealing, host reads, host writes, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document records the first Latticra Seal runtime handoff metadata implementation.

The implementation accepts an existing effect decision metadata record and produces deterministic runtime handoff metadata. It does not activate a runtime boundary and does not perform effects.

## Added files

```text
include/latticra/seal_runtime_handoff.h
src/seal_runtime_handoff.c
tests/seal_runtime_handoff_invariants.c
scripts/test-latticra-seal-runtime-handoff.sh
```

## API summary

The runtime handoff metadata surface adds:

```text
latticra_seal_runtime_handoff_t
latticra_seal_runtime_handoff_error_t
latticra_seal_runtime_handoff_error_label
latticra_seal_runtime_handoff_from_decision
latticra_seal_runtime_handoff_is_inactive_metadata
latticra_seal_runtime_handoff_report
```

## Handoff behavior

The implementation:

```text
accepts a valid effect decision metadata record
copies decision profile metadata
copies gate profile metadata
copies requested capability metadata
copies requested effect metadata
copies requested scope metadata
copies decision_state
copies effect_allowed
copies effect_performed
sets runtime_boundary_state=disabled
records runtime request label metadata, defaulting to no-runtime-request
sets handoff_active=0
sets runtime_effect_performed=0
sets host_read_performed=0
sets host_write_performed=0
sets network_performed=0
sets runtime_authority_granted=0
sets handoff_state=denied-decision
renders deterministic runtime handoff metadata
```

## Boundary

This implementation does not verify signatures, parse public keys, create keys, store keys, contact networks, query revocation status, persist handoff decisions, enforce capabilities, perform host reads, perform host writes, execute network behavior, call runtime components, or grant runtime authority.

It is metadata only.

## Failure behavior

The implementation fails closed:

```text
null runtime handoff output -> LATTICRA_STATUS_NULL_ARGUMENT
null effect decision metadata input -> invalid-input
invalid effect decision metadata -> invalid-decision
missing requested capability -> missing-requested-capability
missing requested effect -> missing-requested-effect
small report buffer -> LATTICRA_STATUS_BUFFER_TOO_SMALL
```

Failures do not parse keys, create keys, persist secrets, contact networks, verify records, sign records, read host files, write host files, enforce capabilities, perform effects, call runtime components, or grant runtime authority.

## Invariants

The invariant test verifies:

```text
valid effect decision metadata produces deterministic runtime handoff metadata
decision profile is copied
gate profile is copied
requested capability is copied
requested effect is copied
requested scope is copied
decision_state is copied
effect_allowed remains zero
effect_performed remains zero
runtime_boundary_state remains disabled
runtime request label is recorded
missing runtime request label defaults to no-runtime-request
handoff_active remains zero
runtime_effect_performed remains zero
host_read_performed remains zero
host_write_performed remains zero
network_performed remains zero
runtime_authority_granted remains zero
handoff_state remains denied-decision
small report buffer fails closed
null inputs fail closed
invalid effect decision metadata fails closed
missing requested capability fails closed
missing requested effect fails closed
```

## Validation

Run:

```sh
sh scripts/test-latticra-seal-runtime-handoff-contract.sh
sh scripts/test-latticra-seal-runtime-handoff.sh
```

## Next valid slice

The next valid Latticra Seal slice is a Seal status rollup contract.

That future slice must be contract-first and must not be added directly to this runtime handoff metadata implementation.
