# Lat Pipeline Diagnostic Integration Refinement

Status: initial implementation

This slice adds a companion Lat pipeline diagnostics API that combines pipeline stage/error state with Lat semantic diagnostic class, count, and first-diagnostic indices.

Files:

```text
include/latticra/lat_pipeline_diagnostics.h
src/lat_pipeline_diagnostics.c
src/lat_pipeline_diagnostics_eval.c
src/lat_pipeline_diagnostics_report.c
tests/lat_pipeline_diagnostic_integration_refinement.c
```

Validation:

```sh
sh scripts/test-lat-pipeline-diagnostic-integration-refinement.sh
sh scripts/test-lat-pipeline.sh
```

Boundary: diagnostic metadata only. No Lat execution is added.
