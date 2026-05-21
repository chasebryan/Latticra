# Latticra Seal Report Implementation

Status: initial no-effect Seal report implementation
Scope: bounded C report surface for Latticra Seal status labels. This slice does not add measurement, signing, object sealing, key handling, runtime authority, host writes, network behavior, kernel behavior, Fedora approval claims, production readiness, or operating-system behavior.

## Purpose

This document records the first Latticra Seal report implementation.

The implementation adds a deterministic report surface that makes the current Seal posture visible without performing operational work.

## Added files

```text
include/latticra/seal_report.h
src/seal_report.c
tests/seal_report_invariants.c
scripts/test-latticra-seal-report.sh
```

## API summary

The report surface adds:

```text
latticra_seal_report_t
latticra_seal_report_default
latticra_seal_report_is_no_effect
latticra_seal_report_render
```

The report uses fixed-size fields, no dynamic allocation, and bounded rendering through snprintf.

## Default report posture

The default report states:

```text
seal_profile=latticra-seal/0.1-report
contract_present=1
implementation_plan_present=1
report_only_supported=1
measurement_supported=0
signing_supported=0
capability_gate_supported=0
sealed_objects_supported=0
effect_performed=0
host_read_performed=0
host_write_performed=0
network_performed=0
runtime_granted=0
evidence_level=2
status=report-only
```

## Effect boundary

The implementation performs no host read, no host write, no network behavior, no runtime grant, and no object mutation.

The helper `latticra_seal_report_is_no_effect` reports true only when all effect fields remain zero.

## Failure behavior

The renderer fails closed:

```text
null report -> LATTICRA_STATUS_NULL_ARGUMENT
null buffer -> LATTICRA_STATUS_NULL_ARGUMENT
small buffer -> LATTICRA_STATUS_BUFFER_TOO_SMALL
```

When the buffer is too small and has nonzero capacity, the renderer clears the first byte.

## Invariants

The invariant test verifies:

```text
default report is report-only
contract and plan are visible
measurement remains unsupported
signing remains unsupported
capability gate remains unsupported
sealed objects remain unsupported
no host read is performed
no host write is performed
no network behavior is performed
no runtime grant is performed
rendered report contains required labels
small render buffer fails closed
null inputs fail closed
```

## Validation

Run:

```sh
sh scripts/test-latticra-seal-report.sh
```

## Next valid slice

The next valid Latticra Seal slice is a read-only measurement contract.

That future slice must be contract-first and must not be added directly to this report implementation.
