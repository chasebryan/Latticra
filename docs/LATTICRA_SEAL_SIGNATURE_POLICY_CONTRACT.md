# Latticra Seal Signature Policy Contract

Status: Latticra Seal signature policy contract
Scope: policy for future signature behavior after unsigned evidence-manifest metadata. This document does not implement signing, verification, key generation, private-key storage, hardware key use, post-quantum signatures, network trust, object sealing, capability enforcement, runtime authority, host writes, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document defines the Latticra Seal signature policy layer.

The purpose of this layer is to decide how future signatures may be represented, requested, validated, and promoted before any signature implementation exists.

This document does not implement signatures.

## Required predecessors

This contract depends on:

```text
docs/LATTICRA_SEAL_CONTRACT.md
docs/LATTICRA_SEAL_MEASUREMENT_IMPLEMENTATION.md
docs/LATTICRA_SEAL_SIGNED_MANIFEST_CONTRACT.md
docs/LATTICRA_SEAL_SIGNED_MANIFEST_IMPLEMENTATION.md
include/latticra/seal_measurement.h
include/latticra/seal_manifest.h
src/seal_measurement.c
src/seal_manifest.c
scripts/test-latticra-seal-measurement.sh
scripts/test-latticra-seal-manifest.sh
```

The manifest metadata surface remains unsigned until a later implementation explicitly adds signature support.

## Policy boundary

Allowed in this policy slice:

```text
signature vocabulary
algorithm planning
signature-state labels
public-key metadata planning
verification-state planning
failure-state planning
promotion rules
non-claims
static guard validation
```

Forbidden in this policy slice:

```text
signature generation
signature verification
key generation
private-key storage
secret handling
network trust lookup
certificate authority behavior
hardware token behavior
runtime authority grants
host writes
object sealing
capability enforcement
```

## Initial algorithm policy

Initial planned signature families:

```text
Ed25519 for local development and fast signatures
ML-DSA for future post-quantum signature support
SLH-DSA for conservative offline/root signature support
```

The first implementation after this contract may only add metadata fields and unsupported-state handling. It must not add the algorithms themselves.

No custom signature primitive may be introduced.

## Planned signature states

Future records should use explicit labels:

```text
signature_state=unsupported
signature_state=unsigned
signature_state=requested
signature_state=signed
signature_state=verified
signature_state=invalid
signature_state=unsupported-algorithm
```

For the next implementation, the expected state is:

```text
signature_state=unsupported
```

## Planned policy fields

A future signature policy record should be bounded and deterministic.

Planned fields:

```text
policy_profile
manifest_profile
manifest_kind
planned_signature_algorithm
post_quantum_algorithm_planned
conservative_root_algorithm_planned
signature_supported
verification_supported
public_key_metadata_supported
private_key_handling
network_lookup_allowed
runtime_authority_granted
status
```

Initial values before implementation:

```text
signature_supported=0
verification_supported=0
public_key_metadata_supported=0
private_key_handling=0
network_lookup_allowed=0
runtime_authority_granted=0
status=signature-policy-only
```

## Failure behavior

Future signature policy handling must fail closed.

Required failure states:

```text
null manifest -> invalid
missing manifest digest -> invalid
signature requested before support -> unsupported
unknown algorithm -> unsupported-algorithm
private-key input -> rejected
network lookup request -> rejected
runtime authority request -> rejected
```

Failures must not create keys, persist secrets, contact networks, sign records, verify records, or grant runtime authority.

## Promotion rule

This contract permits only the next implementation slice:

```text
signature policy metadata implementation
```

It does not permit signature generation, verification, key handling, object sealing, capability enforcement, network behavior, host writes, or runtime authority.

## Validation

This contract is validated by:

```sh
sh scripts/test-latticra-seal-signature-policy-contract.sh
```
