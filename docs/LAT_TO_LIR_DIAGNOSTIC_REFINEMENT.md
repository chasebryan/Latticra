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

It copies lowering error, model error, optional LIR error, model counts, first transition source index, first-clause metadata, node and edge counts, no-effect flags, failure flags, no-effect issue flag, and evidence level into a bounded result record.

The diagnostic result preserves the first lowered clause:

```text
first_clause_node_index
first_clause_role
first_clause_effect
first_clause_name
first_clause_operator
first_clause_value
```

These fields are copied from lowering metadata only. Operators are not evaluated.

The Lat pipeline diagnostic integration can consume this result through `latticra_lat_pipeline_diagnostics_evaluate_with_lowering`, preserving the older pipeline diagnostic evaluator for existing callers. Pipeline diagnostics copy the first-clause metadata with `lowering_` prefixes so aggregate reports can retain the first lowered clause role, effect, name, operator, value, and node index.

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

The invariant suite checks stable labels, valid lowering diagnostics, first-clause diagnostic metadata, parse failure diagnostics, model failure diagnostics, no-effect issue diagnostics, null lowering handling, deterministic report fields, and small-buffer rejection.

## Non-Claims

This slice does not execute Lat, execute LIR, mutate state, perform file I/O, perform network I/O, perform runtime behavior, grant authority, enforce policy, or change lowering behavior.
