# Latticra Seal Signature Implementation Contract

Status: Latticra Seal signature implementation contract
Scope: contract for future development-only signature implementation after signature policy metadata. This document does not implement signing, verification, key generation, private-key storage, hardware key use, post-quantum signatures, network trust lookup, object sealing, capability enforcement, runtime authority, host writes, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document defines the first allowed implementation boundary for Latticra Seal signatures.

The purpose of the future implementation is to support deterministic development-lane signing metadata for already-built unsigned evidence manifests, without granting runtime authority or introducing production trust claims.

This document does not implement signatures.

## Required predecessors

This contract depends on:

```text
docs/LATTICRA_SEAL_CONTRACT.md
docs/LATTICRA_SEAL_SIGNED_MANIFEST_CONTRACT.md
docs/LATTICRA_SEAL_SIGNED_MANIFEST_IMPLEMENTATION.md
docs/LATTICRA_SEAL_SIGNATURE_POLICY_CONTRACT.md
docs/LATTICRA_SEAL_SIGNATURE_POLICY_IMPLEMENTATION.md
include/latticra/seal_manifest.h
include/latticra/seal_signature_policy.h
src/seal_manifest.c
src/seal_signature_policy.c
scripts/test-latticra-seal-manifest.sh
scripts/test-latticra-seal-signature-policy.sh
```

The signature policy metadata surface remains the source of truth until a signature implementation is merged and guarded.

## First signature implementation boundary

The first signature implementation may only support a development-lane signature envelope.

Allowed future behavior:

```text
accept a valid manifest record
accept a caller-supplied public identity label
accept caller-supplied signature bytes as metadata
record signature algorithm label
record signature byte length
record signature state
render deterministic signature report metadata
keep private-key handling disabled
keep network lookup disabled
keep runtime authority disabled
```

Forbidden first implementation behavior:

```text
private-key generation
private-key storage
secret handling
hardware token handling
network trust lookup
certificate authority behavior
post-quantum signature implementation
object sealing
capability enforcement
runtime authority grants
host writes
package installation
host configuration changes
```

## Algorithm scope

The first implementation may use only a label for:

```text
Ed25519-development
```

The first implementation must not implement Ed25519 math, ML-DSA, SLH-DSA, or any custom signature primitive.

Real signing and verification require a later implementation contract.

## Planned signature envelope shape

The first implementation should define a bounded metadata envelope.

Planned fields:

```text
signature_profile
manifest_profile
manifest_kind
artifact_digest_algorithm
artifact_digest_hex
signer_identity_label
signature_algorithm
signature_state
signature_byte_length
signature_supported
verification_supported
private_key_handling
network_lookup_allowed
runtime_authority_granted
status
```

Initial metadata values:

```text
signature_algorithm=Ed25519-development
signature_state=metadata-only
signature_supported=1
verification_supported=0
private_key_handling=0
network_lookup_allowed=0
runtime_authority_granted=0
status=signature-metadata
```

## Planned files

The future implementation should use bounded C surfaces consistent with the rest of Latticra Seal.

```text
include/latticra/seal_signature.h
src/seal_signature.c
tests/seal_signature_invariants.c
scripts/test-latticra-seal-signature.sh
docs/LATTICRA_SEAL_SIGNATURE_IMPLEMENTATION.md
```

## Failure behavior

The future signature metadata implementation must fail closed.

Required failure states:

```text
null output -> invalid
null manifest -> invalid
invalid manifest -> invalid
missing artifact digest -> invalid
missing signer label -> invalid
missing signature bytes -> invalid
unsupported algorithm label -> unsupported
output buffer too small -> bounded failure
```

Failures must not create keys, store keys, contact networks, write host files, seal objects, enforce capabilities, verify signatures, or grant runtime authority.

## Invariant requirements

The first signature metadata tests must verify:

```text
valid manifest plus caller-supplied signature metadata produces deterministic signature metadata
manifest profile is copied
manifest kind is copied
artifact digest algorithm is copied
artifact digest hex is copied
signer identity label is copied
signature algorithm is recorded
signature byte length is recorded
verification_supported remains zero
private_key_handling remains zero
network_lookup_allowed remains zero
runtime_authority_granted remains zero
small report buffer fails closed
null inputs fail closed
invalid manifest fails closed
unsupported algorithm label fails closed
```

## Promotion rule

This contract permits only the next implementation slice:

```text
signature metadata envelope implementation
```

It does not permit real signature generation, signature verification, key generation, private-key storage, object sealing, capability enforcement, network trust lookup, host writes, or runtime authority.
