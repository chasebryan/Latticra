# Latticra Seal Signed Manifest Contract

Status: Latticra Seal signed evidence-manifest contract
Scope: contract for future signed evidence manifests after read-only measurement. This document does not implement signing, key generation, private-key storage, signature verification, Ed25519, ML-DSA, SLH-DSA, encryption, object sealing, capability enforcement, runtime authority, host writes, network behavior, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document defines the next Latticra Seal layer: signed evidence manifests.

A signed evidence manifest is a future bounded record that binds measured artifacts, contract identifiers, evidence levels, and signature metadata into an auditable structure.

This document does not implement signed manifests.

## Required predecessors

This contract depends on:

```text
docs/LATTICRA_SEAL_CONTRACT.md
docs/LATTICRA_SEAL_IMPLEMENTATION_PLAN.md
docs/LATTICRA_SEAL_REPORT_IMPLEMENTATION.md
docs/LATTICRA_SEAL_MEASUREMENT_CONTRACT.md
docs/LATTICRA_SEAL_MEASUREMENT_IMPLEMENTATION.md
include/latticra/seal_report.h
include/latticra/seal_measurement.h
src/seal_report.c
src/seal_measurement.c
scripts/test-latticra-seal-report.sh
scripts/test-latticra-seal-measurement.sh
```

The measurement surface remains the source of truth for artifact digests until signed manifests are implemented and guarded.

## Signed manifest boundary

The first signed-manifest implementation may only build deterministic manifest metadata from already-measured artifact records.

Allowed future behavior:

```text
accept a bounded measurement record
copy artifact label
copy digest algorithm
copy digest hex
copy artifact size
copy contract identifier metadata
copy evidence level
render deterministic manifest text
record signature posture as unsupported until signing exists
```

Forbidden first signed-manifest behavior:

```text
private key generation
private key storage
signature generation
signature verification
network access
encryption
object sealing
capability enforcement
runtime authority grants
host writes
manifest persistence by default
package installation
host configuration changes
```

## Planned primitive policy

Initial signature algorithm planning is:

```text
Ed25519 for local development and fast signatures
ML-DSA for future post-quantum signatures
SLH-DSA for future conservative offline/root signatures
```

This contract does not implement any of those algorithms.

No custom signature primitive may be introduced.

## Planned manifest shape

The first manifest record should be bounded and deterministic.

Planned fields:

```text
manifest_version
manifest_kind
manifest_profile
artifact_label
artifact_size_bytes
artifact_digest_algorithm
artifact_digest_hex
measurement_profile
contract_id
contract_digest_algorithm
contract_digest_hex
evidence_level
signature_algorithm_planned
signature_supported
verification_supported
private_key_handling
runtime_authority_granted
status
```

Initial values before signing support:

```text
signature_supported=0
verification_supported=0
private_key_handling=0
runtime_authority_granted=0
status=unsigned-manifest
```

## Planned files

The future implementation should use bounded C surfaces consistent with the rest of Latticra Seal.

```text
include/latticra/seal_manifest.h
src/seal_manifest.c
tests/seal_manifest_invariants.c
scripts/test-latticra-seal-manifest.sh
docs/LATTICRA_SEAL_SIGNED_MANIFEST_IMPLEMENTATION.md
```

## Report integration

After a manifest metadata implementation exists, the Seal report may add a manifest-support field in a later report refinement.

Signing support must remain false until a separate signing contract and implementation exist.

## Failure behavior

The future manifest implementation must fail closed.

Required failure states:

```text
null manifest output -> invalid
null measurement input -> invalid
invalid measurement status -> invalid
missing digest -> invalid
unsupported digest algorithm -> invalid
output buffer too small -> bounded failure
signature requested before signing support -> unsupported
```

Failures must not create files, modify files, contact networks, generate keys, sign records, verify signatures, or grant runtime authority.

## Invariant requirements

The first manifest tests must verify:

```text
valid measurement produces deterministic unsigned manifest metadata
artifact label is copied
artifact size is copied
SHA-256 digest is copied
measurement profile is copied
signature_supported remains zero
verification_supported remains zero
private_key_handling remains zero
runtime_authority_granted remains zero
small report buffer fails closed
null inputs fail closed
unsupported signing request remains unsupported
```

## Promotion rule

This contract permits only the next implementation slice:

```text
unsigned evidence-manifest metadata implementation
```

It does not permit signing implementation, verification implementation, key handling, object sealing, capability enforcement, network behavior, host writes, or runtime authority.
