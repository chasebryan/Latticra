# Latticra Seal Signature Implementation

Status: initial signature metadata envelope implementation
Scope: bounded C metadata surface for caller-supplied signature envelope metadata. This slice does not implement cryptographic signing, signature verification, key generation, private-key storage, hardware key use, network trust lookup, object sealing, capability enforcement, runtime authority, host writes, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document records the first Latticra Seal signature metadata envelope implementation.

The implementation records caller-supplied development-lane signature metadata for an existing unsigned evidence manifest. It does not create, verify, or interpret cryptographic signatures.

## Added files

```text
include/latticra/seal_signature.h
src/seal_signature.c
tests/seal_signature_invariants.c
scripts/test-latticra-seal-signature.sh
```

## API summary

The signature metadata surface adds:

```text
latticra_seal_signature_t
latticra_seal_signature_error_t
latticra_seal_signature_error_label
latticra_seal_signature_from_manifest
latticra_seal_signature_is_metadata_only
latticra_seal_signature_report
```

## Signature metadata behavior

The implementation:

```text
accepts a valid unsigned manifest record
copies manifest profile
copies manifest kind
copies artifact digest algorithm
copies artifact digest hex
copies caller-supplied signer identity label
accepts only the Ed25519-development algorithm label
records caller-supplied signature byte length
sets signature_state=metadata-only
sets signature_supported=1
sets verification_supported=0
sets private_key_handling=0
sets network_lookup_allowed=0
sets runtime_authority_granted=0
renders deterministic signature metadata
```

## Boundary

This implementation does not generate signatures, verify signatures, handle private keys, contact networks, persist signature files, seal objects, enforce capabilities, write host files, or grant runtime authority.

It is metadata only.

## Failure behavior

The implementation fails closed:

```text
null signature output -> LATTICRA_STATUS_NULL_ARGUMENT
null manifest input -> invalid-input
invalid manifest -> invalid-manifest
missing artifact digest -> missing-digest
missing signer label -> missing-signer
unsupported algorithm label -> unsupported-algorithm
zero signature byte length -> missing-signature-metadata
small report buffer -> LATTICRA_STATUS_BUFFER_TOO_SMALL
```

Failures do not generate keys, store keys, contact networks, sign records, verify records, write host files, or grant runtime authority.

## Invariants

The invariant test verifies:

```text
valid manifest plus caller-supplied signature metadata produces deterministic signature metadata
manifest profile is copied
manifest kind is copied
artifact digest algorithm is copied
artifact digest hex is copied
signer identity label is copied
signature algorithm label is copied
signature byte length is recorded
signature_supported is one
verification_supported remains zero
private_key_handling remains zero
network_lookup_allowed remains zero
runtime_authority_granted remains zero
small report buffer fails closed
null inputs fail closed
invalid manifest fails closed
missing digest fails closed
missing signer fails closed
unsupported algorithm fails closed
missing signature metadata fails closed
```

## Validation

Run:

```sh
sh scripts/test-latticra-seal-signature.sh
```

## Next valid slice

The next valid Latticra Seal slice is a verification policy contract.

That future slice must be contract-first and must not be added directly to this signature metadata implementation.
