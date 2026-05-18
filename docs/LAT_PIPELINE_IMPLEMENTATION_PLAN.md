# Latticra Lat Pipeline Implementation Plan

Status: implementation planning contract
Scope: exact public API, result struct, classification rules, report surface, tests, workflow, compatibility expectations, and non-claims before Lat pipeline implementation code.

## Purpose

This plan defines the first no-effect Lat pipeline implementation.

The implementation should compose the existing bounded stages:

```text
latticra_lat_parse_source
latticra_lat_validate_module
latticra_lir_lower_lat_module
```

and summarize their outputs through one deterministic pipeline result and report.

## Implementation files

Add:

```text
include/latticra/lat_pipeline.h
src/lat_pipeline.c
tests/lat_pipeline_invariants.c
scripts/test-lat-pipeline.sh
.github/workflows/lat-pipeline.yml
docs/LAT_PIPELINE_IMPLEMENTATION.md
```

Update status and index records to include the pipeline as the next bounded no-effect Lat integration slice.

## Public API shape

Add:

```text
latticra_lat_pipeline_error_t
latticra_lat_pipeline_result_t
latticra_lat_pipeline_error_label
latticra_lat_pipeline_run_source
latticra_lat_pipeline_report
```

Recommended signatures:

```text
const char *latticra_lat_pipeline_error_label(latticra_lat_pipeline_error_t error);

latticra_status_t latticra_lat_pipeline_run_source(
    const char *source,
    size_t source_len,
    latticra_lat_parse_result_t *parse_result,
    latticra_lat_semantic_result_t *semantic_result,
    latticra_lir_module_t *module,
    latticra_lat_to_lir_result_t *lowering_result,
    latticra_lat_pipeline_result_t *pipeline_result);

latticra_status_t latticra_lat_pipeline_report(
    const latticra_lat_pipeline_result_t *result,
    char *buffer,
    size_t buffer_len);
```

## Capacity constant

Add:

```text
LATTICRA_LAT_PIPELINE_REPORT_MAX 8192u
```

## Result fields

The result should include:

```text
latticra_status_t status;
latticra_lat_pipeline_error_t error;
latticra_lat_parse_error_t parse_error;
latticra_lat_semantic_error_t semantic_error;
latticra_lat_to_lir_error_t lowering_error;
latticra_lir_error_t lir_error;
latticra_lat_source_span_t span;
char module_name[LATTICRA_LAT_NAME_MAX];
size_t source_len;
size_t declaration_count;
size_t clause_count;
size_t node_count;
size_t edge_count;
int semantic_valid;
int no_effect;
int execution_allowed;
int mutation_allowed;
int server_allowed;
int recovery_allowed;
int hardware_allowed;
```

## Error enum

Add:

```text
LATTICRA_LAT_PIPELINE_OK
LATTICRA_LAT_PIPELINE_NULL_ARGUMENT
LATTICRA_LAT_PIPELINE_PARSE_NOT_OK
LATTICRA_LAT_PIPELINE_SEMANTIC_NOT_OK
LATTICRA_LAT_PIPELINE_SEMANTIC_NOT_VALID
LATTICRA_LAT_PIPELINE_LOWERING_NOT_OK
LATTICRA_LAT_PIPELINE_NO_EFFECT_VIOLATION
LATTICRA_LAT_PIPELINE_INTERNAL_ERROR
```

Stable labels:

```text
ok
null_argument
parse_not_ok
semantic_not_ok
semantic_not_valid
lowering_not_ok
no_effect_violation
internal_error
```

## Algorithm

1. Reject null pointers with `LATTICRA_STATUS_NULL_ARGUMENT`.
2. Initialize the pipeline result deterministically.
3. Parse the source using the existing Lat parser.
4. Validate semantic metadata using the existing Lat semantic validator.
5. Lower to LIR using the existing Lat-to-LIR lowering layer.
6. Summarize parse, semantic, lowering, LIR, count, source-span, and no-effect metadata.
7. Classify the pipeline result using ordered metadata errors.
8. Emit deterministic reports with small-buffer rejection and clearing.

## Test command

Add:

```sh
sh scripts/test-lat-pipeline.sh
```

Compile with:

```text
-std=c99 -Wall -Wextra -Werror -pedantic
```

and include:

```text
src/lat_parser.c
src/lat_semantic.c
src/lir.c
src/lat_to_lir.c
src/lat_pipeline.c
tests/lat_pipeline_invariants.c
```

## Workflow

Add a dedicated workflow:

```text
.github/workflows/lat-pipeline.yml
```

The workflow should run the pipeline test script on pull requests and pushes to `main`.

## Compatibility expectations

This implementation must not change:

```text
Lat parser API or labels
Lat semantic validation API or labels
LIR API or labels
Lat-to-LIR lowering API or labels
L-UI parser, semantic, LIR, or rendering behavior
C++ authority behavior
Nucleus task behavior
runtime boundary behavior
no-effect flags
```

## Non-claims

This implementation plan does not implement Lat execution, Lat compilation, Lat interpretation, LIR execution, command behavior, runtime behavior, Nucleus task execution, mutation, file I/O, network I/O, recovery behavior, hardware behavior, sandboxing, malware prevention, ransomware prevention, or operating-system completeness.
