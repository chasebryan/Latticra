# Latticra Seal Measurement Contract

Status: Latticra Seal measurement contract
Scope: contract for future read-only artifact measurement before measurement implementation, manifest generation, signing, encryption, key handling, runtime authority, host writes, network behavior, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document defines the next Latticra Seal layer: read-only measurement.

Measurement means computing deterministic digest metadata for explicitly supplied artifacts so Latticra can later bind reports, contracts, packages, and release evidence to stable identifiers.

This document does not implement measurement.

## Required predecessors

This contract depends on:

```text
docs/LATTICRA_SEAL_CONTRACT.md
docs/LATTICRA_SEAL_IMPLEMENTATION_PLAN.md
docs/LATTICRA_SEAL_REPORT_IMPLEMENTATION.md
include/latticra/seal_report.h
src/seal_report.c
scripts/test-latticra-seal-report.sh
```

The Seal report must remain the source of truth for the current no-effect posture until measurement code is implemented and guarded.

## Measurement boundary

The first measurement implementation may only read an explicitly supplied regular file path from the caller.

Allowed future behavior:

```text
open caller-supplied file for read-only access
read file bytes in bounded chunks
compute SHA-256 digest
record byte length
record measurement status
render deterministic report metadata
```

Forbidden first measurement behavior:

```text
file writes
directory traversal by default
recursive hashing
network access
key generation
signing
encryption
manifest persistence
runtime authority grants
capability enforcement
kernel interaction
package installation
host configuration changes
```

## Approved initial digest policy

The first official measurement digest is:

```text
SHA-256
```

SHA-384 and SHA-512 may be planned later for wider digest profiles.

BLAKE3 may be planned later only for fast internal content addressing, not compliance claims.

No custom hash function may be introduced.

## Planned API shape

The first measurement implementation should use bounded C records.

Proposed files:

```text
include/latticra/seal_measurement.h
src/seal_measurement.c
tests/seal_measurement_invariants.c
scripts/test-latticra-seal-measurement.sh
docs/LATTICRA_SEAL_MEASUREMENT_IMPLEMENTATION.md
```

Proposed record fields:

```text
measurement_profile
algorithm
artifact_label
artifact_size_bytes
digest_hex
read_performed
write_performed
network_performed
runtime_granted
status
error_label
```

## Report integration

After implementation, the Seal report may advance:

```text
measurement_supported=1
```

Only after the measurement implementation and invariant tests are present.

Until then, the report must keep:

```text
measurement_supported=0
```

## Failure behavior

The future measurement implementation must fail closed.

Required failure states:

```text
null input -> invalid
empty path -> invalid
non-regular path -> invalid
open failure -> read unavailable
read failure -> read failed
output buffer too small -> bounded failure
unsupported algorithm -> invalid
```

Failures must not create files, modify files, contact networks, grant runtime authority, or persist manifests.

## Invariant requirements

The first measurement tests must verify:

```text
known fixture produces expected SHA-256 digest
regular file read is recorded
write remains zero
network remains zero
runtime grant remains zero
null input fails
empty path fails
small report buffer fails closed
unsupported path fails without mutation
Seal report only changes measurement_supported after implementation exists
```

## Promotion rule

This contract permits only the next implementation slice:

```text
read-only SHA-256 measurement implementation
```

It does not permit signing, encryption, key handling, object sealing, capability enforcement, or runtime authority.
