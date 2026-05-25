# Latticra Seal Verification Policy Implementation

Status: initial verification policy metadata implementation
Scope: bounded C metadata surface for verification policy posture after caller-supplied signature metadata. This slice does not implement cryptographic verification, public-key parsing, public-key trust stores, key generation, private-key storage, hardware key use, network trust lookup, revocation lookup, object sealing, capability enforcement, runtime authority, host writes, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document records the first Latticra Seal verification policy metadata implementation.

The implementation accepts an existing signature metadata envelope and produces deterministic verification policy metadata. It does not verify cryptographic signatures and does not treat signature metadata as authority.

## Added files

```text
include/latticra/seal_verification_policy.h
src/seal_verification_policy.c
tests/seal_verification_policy_invariants.c
scripts/test-latticra-seal-verification-policy.sh
```

## API summary

The verification policy metadata surface adds:

```text
latticra_seal_verification_policy_t
latticra_seal_verification_policy_error_t
latticra_seal_verification_policy_error_label
latticra_seal_verification_policy_from_signature
latticra_seal_verification_policy_is_metadata_only
latticra_seal_verification_policy_report
```

## Verification policy behavior

The implementation:

```text
accepts a valid signature metadata envelope
copies the signature profile
copies the manifest profile
copies artifact digest algorithm metadata
copies artifact digest hex metadata
copies signer identity metadata
accepts only the Ed25519-development signature algorithm label
records a caller-supplied public-key identity label
records a caller-supplied trust-source label, defaulting to local-metadata-only
sets verification_state=unsupported
sets cryptographic_verification_supported=0
sets cryptographic_verification_performed=0
sets public_key_material_handling=0
sets private_key_handling=0
sets network_lookup_allowed=0
sets revocation_lookup_allowed=0
sets runtime_authority_granted=0
renders deterministic verification policy metadata
```

## Boundary

This implementation does not parse public keys, verify signatures, create keys, store keys, contact networks, query revocation status, persist verification receipts, seal objects, enforce capabilities, write host files, or grant runtime authority.

It is metadata only.

## Failure behavior

The implementation fails closed:

```text
null verification policy output -> LATTICRA_STATUS_NULL_ARGUMENT
null signature metadata input -> invalid-input
invalid signature metadata -> invalid-signature
missing artifact digest -> missing-digest
missing signer identity -> missing-signer
missing public-key identity label -> missing-public-key-identity
unsupported algorithm label -> unsupported-algorithm
small report buffer -> LATTICRA_STATUS_BUFFER_TOO_SMALL
```

Failures do not parse keys, create keys, persist secrets, contact networks, verify records, sign records, write host files, enforce capabilities, or grant runtime authority.

## Invariants

The invariant test verifies:

```text
valid signature metadata plus public-key identity produces deterministic verification policy metadata
signature profile is copied
manifest profile is copied
artifact digest algorithm is copied
artifact digest hex is copied
signer identity label is copied
signature algorithm label is copied
public-key identity label is recorded
trust source is recorded
missing trust source defaults to local-metadata-only
verification_state remains unsupported
cryptographic_verification_supported remains zero
cryptographic_verification_performed remains zero
public_key_material_handling remains zero
private_key_handling remains zero
network_lookup_allowed remains zero
revocation_lookup_allowed remains zero
runtime_authority_granted remains zero
small report buffer fails closed
null inputs fail closed
invalid signature metadata fails closed
missing digest fails closed
missing signer fails closed
missing public-key identity fails closed
unsupported algorithm fails closed
```

## Validation

Run:

```sh
sh scripts/test-latticra-seal-verification-policy-contract.sh
sh scripts/test-latticra-seal-verification-policy.sh
sh scripts/test-latticra-seal-verification-policy-status.sh
sh scripts/test-latticra-seal-verification-receipt-status.sh
sh scripts/test-latticra-seal-capability-gate-status.sh
sh scripts/test-latticra-seal-effect-decision-status.sh
```

Expected output:

```text
seal verification policy contract: ok
seal verification policy invariants: ok
seal verification policy status: ok
seal verification receipt status: ok
seal capability gate status: ok
seal effect decision status: ok
```

## Next valid slice

The next valid Latticra Seal slice is runtime handoff status/public-entry alignment.

That future slice must not add runtime execution, effect execution, capability enforcement, cryptographic verification, verified receipt authority, signing, key material loading, private-key handling, host behavior, network behavior, or runtime authority unless separately implemented and guarded.
