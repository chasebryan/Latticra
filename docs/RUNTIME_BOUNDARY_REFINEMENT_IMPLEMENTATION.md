# Latticra Runtime Boundary Refinement Implementation

Status: runtime boundary refinement implementation with Lat pipeline clause, declaration, module/count, stage-summary, parse-error, semantic-error, downstream-stage-error, span, comment, Lat LIR no-effect, and Lat LIR edge-kind evidence
Scope: no-effect runtime-boundary evidence reporting for Lat pipeline metadata, Lat pipeline first-clause metadata, Lat pipeline first-declaration metadata, Lat pipeline module/count metadata, Lat pipeline stage-summary metadata, Lat pipeline parse-error metadata, Lat pipeline semantic-error metadata, Lat pipeline downstream stage-error metadata, Lat pipeline span metadata, Lat pipeline line-comment metadata, Lat-specific LIR no-effect metadata, and Lat-specific LIR edge-kind metadata.

## Purpose

This implementation slice refines the runtime boundary so it can classify and report Lat pipeline evidence and Lat-specific LIR evidence without executing Lat, executing LIR, mutating state, performing I/O, opening network connections, touching hardware, or enabling runtime behavior.

The implementation follows:

```text
docs/RUNTIME_BOUNDARY_REFINEMENT_PLAN.md
```

## Added / changed files

```text
include/latticra/runtime_boundary.h
src/runtime_boundary.c
tests/runtime_boundary_lat_pipeline_evidence.c
docs/RUNTIME_BOUNDARY_REFINEMENT_IMPLEMENTATION.md
```

The existing runtime boundary test runner automatically includes the new invariant file:

```text
scripts/test-runtime-boundary.sh
```

## Public API refinement

The runtime boundary request now accepts optional Lat pipeline metadata:

```text
const latticra_lat_pipeline_result_t *lat_pipeline
```

The runtime boundary request kinds now include:

```text
LATTICRA_RUNTIME_BOUNDARY_LAT_PIPELINE_VALIDATE
```

The runtime boundary record now carries no-effect evidence fields for:

```text
lat_pipeline_status
lat_pipeline_error
lat_pipeline_parse_error
lat_pipeline_span_start_offset
lat_pipeline_span_end_offset
lat_pipeline_span_start_line
lat_pipeline_span_start_column
lat_pipeline_span_end_line
lat_pipeline_span_end_column
lat_pipeline_semantic_error
lat_pipeline_model_error
lat_pipeline_lowering_error
lat_pipeline_lir_error
lat_pipeline_last_completed_stage
lat_pipeline_failed_stage
lat_pipeline_parse_ok
lat_pipeline_semantic_ok
lat_pipeline_model_ok
lat_pipeline_lowering_ok
lat_pipeline_lir_ok
lat_pipeline_no_effect_chain_ok
lat_pipeline_evidence_level
lat_pipeline_semantic_valid
lat_pipeline_module_name
lat_pipeline_source_len
lat_pipeline_declaration_count
lat_pipeline_clause_count
lat_pipeline_model_declaration_count
lat_pipeline_model_clause_count
lat_pipeline_first_declaration_node_index
lat_pipeline_first_declaration_kind
lat_pipeline_first_declaration_name
lat_pipeline_first_declaration_source
lat_pipeline_first_declaration_parse_index
lat_pipeline_first_declaration_first_clause_index
lat_pipeline_first_declaration_clause_count
lat_pipeline_first_declaration_source_index
lat_pipeline_first_transition_source_index
lat_pipeline_first_clause_node_index
lat_pipeline_first_clause_role
lat_pipeline_first_clause_effect
lat_pipeline_first_clause_name
lat_pipeline_first_clause_operator
lat_pipeline_first_clause_value
lat_pipeline_node_count
lat_pipeline_edge_count
lat_pipeline_comment_count
lat_pipeline_first_comment_start_offset
lat_pipeline_first_comment_end_offset
lat_pipeline_first_comment_start_line
lat_pipeline_first_comment_start_column
lat_pipeline_first_comment_end_line
lat_pipeline_first_comment_end_column
lat_lir_source_kind
lat_lir_module_node_count
lat_lir_no_effect_chain_ok
lat_lir_evidence_level
lat_lir_no_effect
lat_lir_execution_allowed
lat_lir_mutation_allowed
lat_lir_server_allowed
lat_lir_recovery_allowed
lat_lir_hardware_allowed
lat_lir_contains_edge_count
lat_lir_binds_edge_count
lat_lir_annotates_edge_count
lat_lir_orders_before_edge_count
lat_lir_transition_edge_count
lat_lir_has_lat_state_nodes
lat_lir_has_lat_transition_nodes
lat_lir_has_transition_source_edges
```

## Behavior

The new `lat-pipeline-validate` request is allowed only when:

```text
mode == validation-only
requested effect is none or read
authority metadata is present and no-effect
Lat pipeline metadata is present and OK
Lat pipeline semantic_valid is true
Lat pipeline no-effect flags are preserved
```

Failed Lat pipeline metadata is denied with the closest existing runtime-boundary denial label:

```text
parse_not_ok -> parser-failed
semantic_not_ok / semantic_not_valid -> semantic-failed
no_effect_violation -> non-no-effect-flags
other pipeline failure -> lir-failed
```

Lat execution and LIR execution remain future-gated.

## Report surface

`latticra_runtime_boundary_report` now includes deterministic report fields for Lat pipeline evidence, Lat pipeline first-clause evidence, Lat pipeline first-declaration evidence, Lat pipeline module/count evidence, Lat pipeline stage-summary evidence, Lat pipeline parse-error evidence, Lat pipeline semantic-error evidence, Lat pipeline downstream stage-error evidence, Lat pipeline span evidence, Lat pipeline line-comment evidence, Lat-specific LIR no-effect evidence, and Lat-specific LIR edge-kind evidence.

The runtime boundary report capacity is increased to preserve bounded output with the expanded report surface.

## Validation

Run:

```sh
sh scripts/test-runtime-boundary.sh
```

The focused evidence tests verify:

```text
runtime_boundary_allows_valid_lat_pipeline_metadata
runtime_boundary_denies_failed_lat_pipeline_metadata
runtime_boundary_denies_parse_failed_lat_pipeline_metadata
runtime_boundary_denies_model_failed_lat_pipeline_metadata
runtime_boundary_reports_lat_pipeline_evidence
runtime_boundary_keeps_lat_lir_execution_future_gated
```

The Lat pipeline evidence invariants also verify that parser error metadata, semantic error metadata, downstream model/lowering/LIR error metadata, first-clause metadata, first-declaration metadata, module/count metadata, stage-summary metadata, parser diagnostic/module span metadata, line-comment count, first-comment span metadata, Lat-specific LIR no-effect flags, and Lat-specific LIR edge-kind counts are copied into runtime-boundary records and reports, including denied records for failed Lat pipeline metadata.

## Compatibility

This refinement preserves existing runtime boundary behavior for:

```text
parse-only
validate-only
classify-only
render-report
nucleus-task-report
lat-validate
lir-validate
authority-check
future-gated operational request kinds
unknown request denial
unknown effect denial
operator confirmation non-override behavior
small-buffer behavior
Lat pipeline parse-error evidence reporting
Lat pipeline semantic-error evidence reporting
Lat pipeline downstream stage-error evidence reporting
Lat pipeline first-clause evidence reporting
Lat pipeline first-declaration evidence reporting
Lat pipeline module/count evidence reporting
Lat pipeline stage-summary evidence reporting
Lat pipeline diagnostic/module span evidence reporting
Lat pipeline line-comment evidence reporting
Lat LIR no-effect evidence reporting
Lat LIR edge-kind evidence reporting
denied Lat pipeline comment evidence recording
```

## Boundary

This implementation does not provide runtime behavior, command execution, Lat execution, LIR execution, task effect execution, live movement, state mutation, file I/O, network I/O, server interaction, self-update, recovery behavior, rollback, hardware support, boot behavior, terminal control, security isolation, sandboxing, malware prevention, ransomware prevention, certification, accreditation, or operating-system completeness.
