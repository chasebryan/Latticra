# Latticra Seal Capability Gate Implementation

Status: initial capability gate metadata implementation
Scope: bounded C metadata surface for capability gate posture after verification receipt metadata. This slice does not implement capability enforcement, runtime authority, cryptographic verification, verified receipts, public-key parsing, public-key trust stores, key generation, private-key storage, hardware key use, network trust lookup, revocation lookup, object sealing, host writes, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document records the first Latticra Seal capability gate metadata implementation.

The implementation accepts an existing verification receipt metadata record plus requested capability, effect, and scope labels. It produces deterministic gate metadata that remains denied by default.

## Added files

```text
include/latticra/seal_capability_gate.h
src/seal_capability_gate.c
tests/seal_capability_gate_invariants.c
scripts/test-latticra-seal-capability-gate.sh
```

## API summary

The capability gate metadata surface adds:

```text
latticra_seal_capability_gate_t
latticra_seal_capability_gate_error_t
latticra_seal_capability_gate_error_label
latticra_seal_capability_gate_from_receipt
latticra_seal_capability_gate_is_denied_metadata
latticra_seal_capability_gate_report
```

## Gate behavior

The implementation:

```text
accepts a valid verification receipt metadata record
copies receipt profile metadata
copies verification policy profile metadata
copies artifact digest algorithm metadata
copies artifact digest hex metadata
copies signer identity metadata
copies public-key identity metadata
copies receipt_state
copies verification_state
records requested capability metadata
records requested effect metadata
records requested scope metadata, defaulting to unspecified-scope
copies verified from the receipt
copies authority_usable from the receipt
copies receipt capability_gate_allowed from the receipt
sets gate_allowed=0
sets gate_state=denied-unverified
sets runtime_authority_granted=0
renders deterministic capability gate metadata
```

## Boundary

This implementation does not verify signatures, parse public keys, create keys, store keys, contact networks, query revocation status, persist capability decisions, seal objects, enforce capabilities, execute effects, write host files, or grant runtime authority.

It is metadata only.

## Failure behavior

The implementation fails closed:

```text
null capability gate output -> LATTICRA_STATUS_NULL_ARGUMENT
null verification receipt metadata input -> invalid-input
invalid verification receipt metadata -> invalid-receipt
missing artifact digest -> missing-digest
missing signer identity -> missing-signer
missing public-key identity -> missing-public-key-identity
missing requested capability -> missing-requested-capability
missing requested effect -> missing-requested-effect
small report buffer -> LATTICRA_STATUS_BUFFER_TOO_SMALL
```

Failures do not parse keys, create keys, persist secrets, contact networks, verify records, sign records, write host files, enforce capabilities, execute effects, or grant runtime authority.

## Invariants

The invariant test verifies:

```text
valid verification receipt metadata plus requested capability/effect produces deterministic gate metadata
receipt profile is copied
verification policy profile is copied
artifact digest algorithm is copied
artifact digest hex is copied
signer identity label is copied
public-key identity label is copied
receipt_state is copied
verification_state is copied
requested capability is recorded
requested effect is recorded
requested scope is recorded
missing requested scope defaults to unspecified-scope
verified remains zero
authority_usable remains zero
receipt_capability_gate_allowed remains zero
gate_allowed remains zero
gate_state remains denied-unverified
runtime_authority_granted remains zero
small report buffer fails closed
null inputs fail closed
invalid verification receipt metadata fails closed
missing digest fails closed
missing signer fails closed
missing public-key identity fails closed
missing requested capability fails closed
missing requested effect fails closed
```

## Validation

Run:

```sh
sh scripts/test-latticra-seal-capability-gate-contract.sh
sh scripts/test-latticra-seal-capability-gate.sh
sh scripts/test-latticra-seal-capability-gate-status.sh
```

Expected output:

```text
seal capability gate contract: ok
seal capability gate invariants: ok
seal capability gate status: ok
```

## Next valid slice

The next valid Latticra Seal slice is effect decision status/public-entry alignment.

That future slice must not add effect execution, capability enforcement, runtime authority, cryptographic verification, verified receipt authority, signing, host behavior, network behavior, or object sealing unless separately implemented and guarded.
