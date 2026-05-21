# Latticra Seal Effect Decision Implementation

Status: initial effect decision metadata implementation
Scope: bounded C metadata surface for effect decision posture after capability gate metadata. This slice does not implement effect execution, capability enforcement, runtime authority, cryptographic verification, verified receipts, public-key parsing, public-key trust stores, key generation, private-key storage, hardware key use, network trust lookup, revocation lookup, object sealing, host reads, host writes, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document records the first Latticra Seal effect decision metadata implementation.

The implementation accepts an existing capability gate metadata record and produces deterministic effect decision metadata. It does not perform effects and does not treat a denied gate as authority.

## Added files

```text
include/latticra/seal_effect_decision.h
src/seal_effect_decision.c
tests/seal_effect_decision_invariants.c
scripts/test-latticra-seal-effect-decision.sh
```

## API summary

The effect decision metadata surface adds:

```text
latticra_seal_effect_decision_t
latticra_seal_effect_decision_error_t
latticra_seal_effect_decision_error_label
latticra_seal_effect_decision_from_gate
latticra_seal_effect_decision_is_denied_metadata
latticra_seal_effect_decision_report
```

## Decision behavior

The implementation:

```text
accepts a valid capability gate metadata record
copies gate profile metadata
copies receipt profile metadata
copies artifact digest algorithm metadata
copies artifact digest hex metadata
copies requested capability metadata
copies requested effect metadata
copies requested scope metadata
copies gate_state
sets decision_state=denied-gate
copies gate_allowed from the gate
sets effect_allowed=0
sets effect_performed=0
sets host_read_performed=0
sets host_write_performed=0
sets network_performed=0
sets runtime_authority_granted=0
renders deterministic effect decision metadata
```

## Boundary

This implementation does not verify signatures, parse public keys, create keys, store keys, contact networks, query revocation status, persist decisions, enforce capabilities, perform host reads, perform host writes, execute network behavior, or grant runtime authority.

It is metadata only.

## Failure behavior

The implementation fails closed:

```text
null effect decision output -> LATTICRA_STATUS_NULL_ARGUMENT
null capability gate metadata input -> invalid-input
invalid capability gate metadata -> invalid-gate
missing artifact digest -> missing-digest
missing requested capability -> missing-requested-capability
missing requested effect -> missing-requested-effect
small report buffer -> LATTICRA_STATUS_BUFFER_TOO_SMALL
```

Failures do not parse keys, create keys, persist secrets, contact networks, verify records, sign records, read host files, write host files, enforce capabilities, perform effects, or grant runtime authority.

## Invariants

The invariant test verifies:

```text
valid capability gate metadata produces deterministic effect decision metadata
gate profile is copied
receipt profile is copied
artifact digest algorithm is copied
artifact digest hex is copied
requested capability is copied
requested effect is copied
requested scope is copied
gate_state is copied
decision_state remains denied-gate
gate_allowed remains zero
effect_allowed remains zero
effect_performed remains zero
host_read_performed remains zero
host_write_performed remains zero
network_performed remains zero
runtime_authority_granted remains zero
small report buffer fails closed
null inputs fail closed
invalid capability gate metadata fails closed
missing digest fails closed
missing requested capability fails closed
missing requested effect fails closed
```

## Validation

Run:

```sh
sh scripts/test-latticra-seal-effect-decision-contract.sh
sh scripts/test-latticra-seal-effect-decision.sh
```

## Next valid slice

The next valid Latticra Seal slice is a runtime handoff contract.

That future slice must be contract-first and must not be added directly to this effect decision metadata implementation.
