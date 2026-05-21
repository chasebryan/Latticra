# Latticra Seal Measurement Implementation

Status: initial read-only SHA-256 measurement implementation
Scope: bounded C measurement surface for caller-supplied regular files. This slice does not add signing, encryption, key handling, object sealing, capability enforcement, runtime authority, host writes, network behavior, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document records the first Latticra Seal measurement implementation.

The implementation adds read-only SHA-256 artifact measurement so Latticra can identify explicitly supplied artifacts with deterministic digest metadata.

## Added files

```text
include/latticra/seal_measurement.h
src/seal_measurement.c
tests/seal_measurement_invariants.c
scripts/test-latticra-seal-measurement.sh
```

This slice also advances the Seal report surface so it can truthfully state:

```text
measurement_supported=1
```

## API summary

The measurement surface adds:

```text
latticra_seal_measurement_t
latticra_seal_measurement_error_t
latticra_seal_measurement_error_label
latticra_seal_measure_file
latticra_seal_measurement_is_read_only
latticra_seal_measurement_report
```

## Measurement behavior

The implementation:

```text
accepts a caller-supplied path
requires a regular file
opens the file in binary read-only mode
reads bytes in bounded chunks
computes SHA-256
records byte length
renders deterministic report metadata
```

The implementation does not recurse, scan directories, create manifests, sign data, encrypt data, write files, contact networks, or grant runtime authority.

## Default report posture after this slice

The Seal report now states:

```text
seal_profile=latticra-seal/0.1-report
report_only_supported=1
measurement_supported=1
signing_supported=0
capability_gate_supported=0
sealed_objects_supported=0
effect_performed=0
host_read_performed=0
host_write_performed=0
network_performed=0
runtime_granted=0
evidence_level=3
status=report-and-measurement
```

The report itself remains no-effect. Measurement reads only when the measurement API is explicitly called.

## Measurement record posture

A successful measurement records:

```text
measurement_profile=latticra-seal-measurement/0.1
algorithm=SHA-256
artifact_label=<caller supplied path>
artifact_size_bytes=<read byte count>
digest_hex=<64 lowercase hex characters>
read_performed=1
write_performed=0
network_performed=0
runtime_granted=0
error=ok
status=measured
```

## Failure behavior

The implementation fails closed:

```text
null output -> LATTICRA_STATUS_NULL_ARGUMENT
null path -> invalid-input
empty path -> invalid-input
non-regular path -> not-regular
open failure -> open-failed
read failure -> read-failed
small report buffer -> LATTICRA_STATUS_BUFFER_TOO_SMALL
```

Failures do not write files, contact networks, persist manifests, or grant runtime authority.

## Invariants

The invariant test verifies:

```text
known fixture produces expected SHA-256 digest
regular file read is recorded
write remains zero
network remains zero
runtime grant remains zero
rendered measurement report contains required labels
null path fails closed
empty path fails closed
non-regular path fails closed
missing file fails closed
small report buffer fails closed
null report inputs fail closed
Seal report advertises measurement support only after implementation exists
```

## Validation

Run:

```sh
sh scripts/test-latticra-seal-measurement.sh
sh scripts/test-latticra-seal-measurement-contract.sh
```

## Next valid slice

The next valid Latticra Seal slice is a signed evidence-manifest contract.

That future slice must be contract-first and must not be added directly to this measurement implementation.
