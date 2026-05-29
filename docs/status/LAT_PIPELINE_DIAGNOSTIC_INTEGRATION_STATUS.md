# Lat Pipeline Diagnostic Integration Status

Status: merged companion diagnostics surface

This record tracks the Lat pipeline diagnostic integration slice.

Merged PR:

```text
#109 Add Lat pipeline diagnostic integration
```

Merged commit:

```text
d2880fca57bb753753844b683c14882af5ec4560
```

Primary files:

```text
include/latticra/lat_pipeline_diagnostics.h
include/latticra/lat_to_lir_diagnostics.h
src/lat_pipeline_diagnostics.c
src/lat_pipeline_diagnostics_eval.c
src/lat_pipeline_diagnostics_report.c
src/lat_to_lir_diagnostics.c
tests/lat_pipeline_diagnostic_integration_refinement.c
docs/LAT_PIPELINE_DIAGNOSTIC_INTEGRATION_REFINEMENT.md
scripts/test-lat-pipeline-diagnostic-integration-refinement.sh
.github/workflows/lat-pipeline-diagnostic-integration-refinement.yml
```

What it adds:

```text
pipeline diagnostic class
pipeline error capture
failed pipeline stage capture
semantic diagnostic class capture
semantic error capture
semantic diagnostic count capture
first diagnostic declaration index
first diagnostic clause index
optional Lat-to-LIR lowering diagnostic class capture
lowering error capture
model error capture
LIR error capture
lowering model counts
lowering transition source index
pipeline_failed flag
semantic_failed flag
lowering_failed flag
model_failed flag
lir_failed flag
no_effect_issue flag
evidence_level
```

Validation:

```sh
sh scripts/test-lat-pipeline-diagnostic-integration-refinement.sh
sh scripts/test-lat-pipeline.sh
```

Boundary: diagnostic metadata only. No Lat execution, LIR execution, compiler, interpreter, runtime, state mutation, file I/O, network I/O, hardware behavior, or operating-system completeness is added.
