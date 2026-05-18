# Latticra Lat Pipeline Contract

Status: Lat pipeline contract
Scope: bounded no-effect composition of Lat grammar parsing, Lat semantic validation, and Lat-to-LIR lowering.

## Purpose

This contract defines the first Lat / Latticra Language pipeline boundary.

The pipeline consumes Lat source bytes and coordinates the already bounded stages:

```text
Lat source -> grammar parser -> semantic validator -> Lat-to-LIR lowering -> pipeline report
```

The pipeline is not a compiler, interpreter, runtime, executor, package manager, or operating-system surface. It is a deterministic composition/report boundary over parser, semantic, and LIR metadata.

## Relationship to existing work

This contract depends on:

```text
include/latticra/lat_parser.h
include/latticra/lat_semantic.h
include/latticra/lat_to_lir.h
include/latticra/lir.h
src/lat_parser.c
src/lat_semantic.c
src/lat_to_lir.c
docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md
docs/LAT_SEMANTIC_VALIDATION_IMPLEMENTATION.md
docs/LAT_TO_LIR_LOWERING_IMPLEMENTATION.md
```

Those files remain the source of truth for syntax parsing, semantic validation, LIR shape, lowering behavior, reports, capacities, and non-claims.

## Pipeline posture

The pipeline must preserve:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

The pipeline must not execute Lat or LIR. It must not evaluate host state, mutate state, write files, read files, open network connections, invoke server behavior, invoke recovery behavior, touch hardware, boot anything, or perform command behavior.

## Input contract

The pipeline accepts:

```text
const char *source
size_t source_len
```

The caller provides storage for all intermediate and final records:

```text
latticra_lat_parse_result_t
latticra_lat_semantic_result_t
latticra_lir_module_t
latticra_lat_to_lir_result_t
latticra_lat_pipeline_result_t
```

The pipeline does not allocate memory and does not take ownership of caller buffers.

## Output contract

The pipeline produces:

```text
latticra_lat_pipeline_result_t
```

The result summarizes:

```text
status
pipeline error
parse error
semantic error
lowering error
LIR error
module name
source length
declaration count
clause count
node count
edge count
semantic_valid
no-effect flags
source span
```

## Stable pipeline error labels

The first stable pipeline labels are:

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

## Classification rules

Pipeline classification is ordered:

1. Null arguments return `LATTICRA_STATUS_NULL_ARGUMENT`.
2. Parser status failures are internal status failures.
3. Parser metadata errors are summarized as `parse_not_ok`.
4. Semantic metadata errors are summarized as `semantic_not_ok`.
5. A semantic result that is not valid is summarized as `semantic_not_valid`.
6. Lat-to-LIR or LIR metadata errors are summarized as `lowering_not_ok`.
7. Any no-effect flag violation is summarized as `no_effect_violation`.
8. Only a fully successful bounded path reports `ok`.

## Report format

`latticra_lat_pipeline_report` emits a deterministic bounded report beginning with:

```text
LAT PIPELINE REPORT
```

The report includes status, error labels, module metadata, counts, no-effect flags, and source-span metadata.

Small output buffers must return `LATTICRA_STATUS_BUFFER_TOO_SMALL` and clear the buffer when possible.

## Required implementation files

The implementation slice must add:

```text
include/latticra/lat_pipeline.h
src/lat_pipeline.c
tests/lat_pipeline_invariants.c
scripts/test-lat-pipeline.sh
.github/workflows/lat-pipeline.yml
docs/LAT_PIPELINE_IMPLEMENTATION_PLAN.md
docs/LAT_PIPELINE_IMPLEMENTATION.md
```

## Required tests

The implementation must include invariant coverage for:

```text
lat_pipeline_accepts_foundation_model
lat_pipeline_preserves_counts
lat_pipeline_rejects_parse_failure
lat_pipeline_rejects_semantic_failure
lat_pipeline_preserves_no_effect_flags
lat_pipeline_report_is_deterministic
lat_pipeline_report_rejects_small_buffer
lat_pipeline_error_labels_are_stable
```

## Compatibility expectations

This contract must not change parser behavior, semantic validation behavior, LIR shape behavior, Lat-to-LIR lowering behavior, L-UI behavior, C++ authority behavior, Nucleus behavior, runtime behavior, or existing report labels.

## Non-claims

This contract does not implement Lat execution, Lat compilation, Lat interpretation, LIR execution, L-UI rendering, command behavior, runtime behavior, Nucleus task execution, mutation, file I/O, network I/O, recovery behavior, hardware behavior, malware prevention, ransomware prevention, sandboxing, certification, accreditation, or operating-system completeness.
