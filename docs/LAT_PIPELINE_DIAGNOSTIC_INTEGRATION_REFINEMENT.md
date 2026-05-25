# Lat Pipeline Diagnostic Integration Refinement

Status: lowering-aware implementation with first-clause metadata

This slice adds a companion Lat pipeline diagnostics API that combines pipeline stage/error state with Lat semantic diagnostic class, count, first-diagnostic indices, model-stage classification, and optional Lat-to-LIR lowering diagnostic metadata.

Files:

```text
include/latticra/lat_pipeline_diagnostics.h
src/lat_pipeline_diagnostics.c
src/lat_pipeline_diagnostics_eval.c
src/lat_pipeline_diagnostics_report.c
include/latticra/lat_to_lir_diagnostics.h
src/lat_to_lir_diagnostics.c
tests/lat_pipeline_diagnostic_integration_refinement.c
```

The compatibility evaluator remains available:

```text
latticra_lat_pipeline_diagnostics_evaluate
```

The lowering-aware evaluator adds optional lowering and LIR inputs:

```text
latticra_lat_pipeline_diagnostics_evaluate_with_lowering
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

When lowering metadata is provided, the pipeline diagnostic result also records:

```text
lowering_class
lowering_error
model_error
lir_error
lowering_model_declaration_count
lowering_model_clause_count
lowering_first_transition_source_index
lowering_first_clause_node_index
lowering_first_clause_role
lowering_first_clause_effect
lowering_first_clause_name
lowering_first_clause_operator
lowering_first_clause_value
lowering_failed
model_failed
lir_failed
```

First-clause metadata is copied from the Lat-to-LIR diagnostic result. It records the first lowered clause node index, normalized clause role, effect label, name, operator text, and value text for report/audit use only.

Validation:

```sh
sh scripts/test-lat-pipeline-diagnostic-integration-refinement.sh
sh scripts/test-lat-pipeline.sh
```

Boundary: diagnostic metadata only. No Lat execution is added.
