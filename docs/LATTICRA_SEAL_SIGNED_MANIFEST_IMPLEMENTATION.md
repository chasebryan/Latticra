# Latticra Seal Signed Manifest Implementation

Status: initial unsigned evidence-manifest metadata implementation
Scope: bounded C manifest metadata surface after read-only measurement. This slice does not add signing, verification, key handling, object sealing, capability enforcement, runtime authority, host writes, network behavior, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document records the first Latticra Seal manifest implementation.

The implementation builds deterministic unsigned evidence-manifest metadata from a valid read-only measurement record.

## Added files

```text
include/latticra/seal_manifest.h
src/seal_manifest.c
tests/seal_manifest_invariants.c
scripts/test-latticra-seal-manifest.sh
```

## API summary

The manifest surface adds:

```text
latticra_seal_manifest_t
latticra_seal_manifest_error_t
latticra_seal_manifest_error_label
latticra_seal_manifest_from_measurement
latticra_seal_manifest_is_unsigned_metadata
latticra_seal_manifest_report
```

## Manifest behavior

The implementation:

```text
accepts a valid measurement record
copies artifact label
copies artifact size
copies digest algorithm
copies digest hex
copies measurement profile
copies contract id metadata
renders deterministic manifest text
keeps signature support at zero
keeps verification support at zero
keeps private-key handling at zero
keeps runtime authority at zero
```

## Default manifest posture

A successful unsigned manifest records:

```text
manifest_profile=latticra-seal-manifest/0.1
manifest_kind=unsigned-evidence-manifest
artifact_label=<measurement artifact label>
artifact_size_bytes=<measurement byte count>
artifact_digest_algorithm=SHA-256
artifact_digest_hex=<measurement digest>
measurement_profile=<measurement profile>
contract_id=<caller supplied contract id>
contract_digest_algorithm=not-computed
evidence_level=4
planned_signature_algorithm=Ed25519-planned
signature_supported=0
verification_supported=0
private_key_handling=0
runtime_authority_granted=0
status=unsigned-manifest
```

## Boundary

This implementation does not sign data, verify signatures, generate keys, store keys, write manifests, persist manifests, contact networks, or grant runtime authority.

It is metadata only.

## Failure behavior

The implementation fails closed:

```text
null manifest output -> LATTICRA_STATUS_NULL_ARGUMENT
null measurement input -> invalid-input
invalid measurement -> invalid-measurement
missing digest -> missing-digest
small report buffer -> LATTICRA_STATUS_BUFFER_TOO_SMALL
```

Failures do not write files, contact networks, create keys, sign records, verify records, or grant runtime authority.

## Invariants

The invariant test verifies:

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
invalid measurement fails closed
missing digest fails closed
```

## Validation

Run:

```sh
sh scripts/test-latticra-seal-manifest.sh
```

## Next valid slice

The next valid Latticra Seal slice is a signature policy contract.

That future slice must be contract-first and must not be added directly to this manifest metadata implementation.
