# Lat-to-LIR Diagnostic Refinement

Status: initial no-effect implementation

Scope: deterministic diagnostic classification and reporting for Lat-to-LIR lowering results after model-driven lowering integration.

## Purpose

This slice adds a diagnostic surface for the Lat-to-LIR boundary.

It classifies lowering outcomes without changing parser, semantic, model normalization, lowering, LIR, pipeline, runtime, or authority behavior.

## Implementation Files

```text
include/latticra/lat_to_lir_diagnostics.h
src/lat_to_lir_diagnostics.c
tests/lat_to_lir_diagnostic_refinement.c
scripts/test-lat-to-lir-diagnostic-refinement.sh
```

## Public API

The diagnostic API adds:

```text
latticra_lat_to_lir_diagnostic_class_t
latticra_lat_to_lir_diagnostic_result_t
latticra_lat_to_lir_diagnostic_class_label
latticra_lat_to_lir_diagnostics_evaluate
latticra_lat_to_lir_diagnostics_report
```

## Diagnostic Classes

The evaluator classifies lowering outcomes as:

```text
valid
parse
semantic
model
effect-check
capacity
lir
internal
```

It copies lowering error, model error, optional LIR error, model counts, first transition source index, node and edge counts, no-effect flags, failure flags, no-effect issue flag, and evidence level into a bounded result record.

## Report Format

`latticra_lat_to_lir_diagnostics_report` emits a deterministic bounded report beginning with:

```text
LAT TO LIR DIAGNOSTIC REPORT
```

Small output buffers return `LATTICRA_STATUS_BUFFER_TOO_SMALL` and clear the buffer when possible.

## Validation

Run:

```sh
sh scripts/test-lat-to-lir-diagnostic-refinement.sh
```

The invariant suite checks stable labels, valid lowering diagnostics, parse failure diagnostics, model failure diagnostics, no-effect issue diagnostics, null lowering handling, deterministic report fields, and small-buffer rejection.

## Non-Claims

This slice does not execute Lat, execute LIR, mutate state, perform file I/O, perform network I/O, perform runtime behavior, grant authority, enforce policy, or change lowering behavior.
