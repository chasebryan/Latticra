# Latticra Lat Pipeline Implementation

Status: initial implementation contract
Scope: first bounded no-effect Lat pipeline API, source composition, summary report, invariants, and workflow.

## Purpose

This slice adds a no-effect Lat pipeline that composes the existing Lat parser, Lat semantic validator, Lat model normalization layer, and Lat-to-LIR lowering layer into one deterministic report boundary.

The pipeline is intended to make the currently separate stages easier to validate together without changing the behavior of any stage.

## Added files

```text
include/latticra/lat_pipeline.h
src/lat_pipeline.c
tests/lat_pipeline_invariants.c
scripts/test-lat-pipeline.sh
.github/workflows/lat-pipeline.yml
```

## Public API

The public API adds:

```text
latticra_lat_pipeline_error_t
latticra_lat_pipeline_result_t
latticra_lat_pipeline_error_label
latticra_lat_pipeline_run_source
latticra_lat_pipeline_run_source_with_model
latticra_lat_pipeline_report
```

## Behavior

`latticra_lat_pipeline_run_source` performs the bounded metadata path:

```text
source bytes
  -> latticra_lat_parse_source
  -> latticra_lat_validate_module
  -> latticra_lat_model_normalize_module
  -> latticra_lir_lower_lat_model
  -> latticra_lat_pipeline_result_t
```

The wrapper entry point `latticra_lat_pipeline_run_source` preserves the original caller shape and runs normalization internally. The model-aware entry point `latticra_lat_pipeline_run_source_with_model` also returns the normalized model to callers. Lowering now consumes that normalized model directly.

The function records parser, semantic, model, lowering, and LIR errors separately, then classifies the aggregate pipeline state.

The companion pipeline diagnostic surface can now evaluate with optional Lat-to-LIR lowering diagnostics so pipeline reports can expose lowering class, model error, LIR error, model counts, transition source index, first-clause metadata, and failure flags without changing pipeline execution behavior.

## Report surface

`latticra_lat_pipeline_report` emits:

```text
LAT PIPELINE REPORT
```

with deterministic fields for status, aggregate error, stage errors, module name, source length, validity, parser counts, model counts, transition source index metadata, first-clause metadata copied from lowering, no-effect flags, and source spans.

Small buffers return `LATTICRA_STATUS_BUFFER_TOO_SMALL` and are cleared when possible.

## Validation

Run:

```sh
sh scripts/test-lat-pipeline.sh
```

The invariant suite covers:

```text
lat_pipeline_accepts_foundation_model
lat_pipeline_exposes_normalized_model
lat_pipeline_preserves_counts
lat_pipeline_rejects_parse_failure
lat_pipeline_rejects_semantic_failure
lat_pipeline_preserves_no_effect_flags
lat_pipeline_report_is_deterministic
lat_pipeline_report_rejects_small_buffer
lat_pipeline_error_labels_are_stable
```

## Boundary

This slice does not execute Lat, execute LIR, perform runtime behavior, mutate state, perform file I/O, perform network I/O, call server code, call recovery code, touch hardware, control a terminal, call Nucleus task execution, or grant C++ authority.

## Compatibility

The implementation is a composition layer. It does not modify parser, semantic validator, Lat model normalization, LIR, Lat-to-LIR lowering, L-UI, C++ authority, Nucleus, or runtime-boundary APIs.

## Non-claims

This implementation does not provide a Lat compiler, Lat interpreter, Lat runtime, LIR executor, command system, task executor, production runtime, security boundary, malware prevention guarantee, ransomware prevention guarantee, certification, accreditation, or operating-system replacement.
