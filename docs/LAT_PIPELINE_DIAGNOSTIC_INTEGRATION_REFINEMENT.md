# Lat Pipeline Diagnostic Integration Refinement

Status: lowering-aware implementation with pipeline-span, comment, first-declaration, and first-clause metadata

This slice adds a companion Lat pipeline diagnostics API that combines pipeline stage/error state with pipeline span metadata, parser line-comment metadata, Lat semantic diagnostic class, count, first-diagnostic indices, model-stage classification, and optional Lat-to-LIR lowering diagnostic metadata.

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
pipeline_span_start_offset
pipeline_span_end_offset
pipeline_span_start_line
pipeline_span_start_column
pipeline_span_end_line
pipeline_span_end_column
comment_count
first_comment_start_offset
first_comment_end_offset
first_comment_start_line
first_comment_start_column
first_comment_end_line
first_comment_end_column
lowering_model_declaration_count
lowering_model_clause_count
lowering_first_declaration_node_index
lowering_first_declaration_kind
lowering_first_declaration_name
lowering_first_declaration_source
lowering_first_declaration_parse_index
lowering_first_declaration_first_clause_index
lowering_first_declaration_clause_count
lowering_first_declaration_source_index
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

Pipeline span metadata is copied from the Lat pipeline result. It records the successful module span or the parse-failure diagnostic span for report/audit use only.

Comment metadata is copied from the Lat pipeline result. It records the parser line-comment count and first-comment span for diagnostic/report audit use only, including parse-failure diagnostics where a line comment appears before an unsupported block-comment opener.

First-declaration metadata is copied from the Lat-to-LIR diagnostic result. It records the first lowered declaration node index, declaration kind, name, source name, parse declaration index, first-clause index, clause count, and source declaration index for report/audit use only.

First-clause metadata is copied from the Lat-to-LIR diagnostic result. It records the first lowered clause node index, normalized clause role, effect label, name, operator text, and value text for report/audit use only.

Validation:

```sh
sh scripts/test-lat-pipeline-diagnostic-integration-refinement.sh
sh scripts/test-lat-pipeline.sh
```

Boundary: diagnostic metadata only. No Lat execution is added.
