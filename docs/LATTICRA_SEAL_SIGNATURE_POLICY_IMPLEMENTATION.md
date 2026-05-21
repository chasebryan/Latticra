# Latticra Seal Signature Policy Implementation

Status: initial signature policy metadata implementation
Scope: bounded C metadata surface for Latticra Seal signature policy posture. This slice does not add signing, verification, key handling, network trust lookup, object sealing, capability enforcement, runtime authority, host writes, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document records the first Latticra Seal signature policy metadata implementation.

The implementation consumes unsigned manifest metadata and reports the planned signature posture while keeping all operational signature capability disabled.

## Added files

```text
include/latticra/seal_signature_policy.h
src/seal_signature_policy.c
tests/seal_signature_policy_invariants.c
scripts/test-latticra-seal-signature-policy.sh
```

## API summary

The policy surface adds:

```text
latticra_seal_signature_policy_t
latticra_seal_signature_policy_error_t
latticra_seal_signature_policy_error_label
latticra_seal_signature_policy_from_manifest
latticra_seal_signature_policy_is_metadata_only
latticra_seal_signature_policy_report
```

## Policy behavior

The implementation:

```text
accepts a valid unsigned manifest record
copies manifest profile
copies manifest kind
records planned Ed25519 metadata
records planned ML-DSA metadata
records planned SLH-DSA metadata
sets signature_state=unsupported
sets signature_supported=0
sets verification_supported=0
sets public_key_metadata_supported=0
sets private_key_handling=0
sets network_lookup_allowed=0
sets runtime_authority_granted=0
renders deterministic policy metadata
```

## Boundary

This implementation does not sign data, verify records, generate keys, store keys, contact networks, use hardware tokens, seal objects, enforce capabilities, write host files, or grant runtime authority.

It is metadata only.

## Failure behavior

The implementation fails closed:

```text
null policy output -> LATTICRA_STATUS_NULL_ARGUMENT
null manifest input -> invalid-input
invalid manifest -> invalid-manifest
small report buffer -> LATTICRA_STATUS_BUFFER_TOO_SMALL
```

## Invariants

The invariant test verifies:

```text
valid manifest produces deterministic policy metadata
manifest profile is copied
manifest kind is copied
signature_state remains unsupported
signature_supported remains zero
verification_supported remains zero
public_key_metadata_supported remains zero
private_key_handling remains zero
network_lookup_allowed remains zero
runtime_authority_granted remains zero
small report buffer fails closed
null inputs fail closed
invalid manifest fails closed
```

## Validation

Run:

```sh
sh scripts/test-latticra-seal-signature-policy.sh
```

## Next valid slice

The next valid Latticra Seal slice is a signature implementation contract.

That future slice must be contract-first and must not be added directly to this signature policy metadata implementation.
