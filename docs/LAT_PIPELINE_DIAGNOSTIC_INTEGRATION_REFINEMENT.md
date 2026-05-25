# Lat Pipeline Diagnostic Integration Refinement

Status: initial implementation

This slice adds a companion Lat pipeline diagnostics API that combines pipeline stage/error state with Lat semantic diagnostic class, count, first-diagnostic indices, and model-stage classification.

Files:

```text
include/latticra/lat_pipeline_diagnostics.h
src/lat_pipeline_diagnostics.c
src/lat_pipeline_diagnostics_eval.c
src/lat_pipeline_diagnostics_report.c
tests/lat_pipeline_diagnostic_integration_refinement.c
```

The diagnostic class labels include:

```text
valid
parse
semantic
model
lowering
lir
effect-check
internal
```

Validation:

```sh
sh scripts/test-lat-pipeline-diagnostic-integration-refinement.sh
sh scripts/test-lat-pipeline.sh
```

Boundary: diagnostic metadata only. No Lat execution is added.
