# Latticra Lat Pipeline Report Refinement

Status: Lat pipeline report refinement implementation with comment, first-declaration, and first-clause metadata
Scope: deterministic Lat pipeline stage-summary metadata, line-comment report fields, first-declaration report fields, first-clause report fields, invariant tests, guard coverage, and workflow wiring.

## Purpose

This document records the Lat pipeline report refinement after the first Lat pipeline implementation and the runtime boundary report refinement.

The goal is to make the Lat pipeline report clearer about which stage completed, which stage failed, and whether the full no-effect chain remained intact.

This refinement does not execute Lat, execute LIR, compile Lat, interpret Lat, mutate state, perform I/O, or provide runtime behavior.

## Added report metadata

The Lat pipeline result now records:

```text
last_completed_stage
failed_stage
parse_ok
semantic_ok
model_ok
lowering_ok
lir_ok
no_effect_chain_ok
evidence_level
comment_count
first_comment_start_offset
first_comment_end_offset
first_comment_start_line
first_comment_start_column
first_comment_end_line
first_comment_end_column
first_declaration_node_index
first_declaration_kind
first_declaration_name
first_declaration_source
first_declaration_parse_index
first_declaration_first_clause_index
first_declaration_clause_count
first_declaration_source_index
first_clause_node_index
first_clause_role
first_clause_effect
first_clause_name
first_clause_operator
first_clause_value
```

The deterministic `LAT PIPELINE REPORT` now emits these fields as labels and integers. Line-comment metadata is copied from the parser result, and first-declaration plus first-clause metadata is copied from the Lat-to-LIR lowering result for audit visibility only.

## Stage labels

Initial stage labels:

```text
none
parse
semantic
model
lowering
lir
effect-check
report
unknown
```

## Evidence level

The Lat pipeline report uses a small deterministic evidence label:

```text
0 -> unavailable or internal/null pipeline evidence
1 -> partial pipeline evidence with a known failed stage
2 -> complete no-effect pipeline report evidence
```

This is a project-internal evidence label, not a certification, production-readiness claim, or security guarantee.

## Successful report path

A successful Lat pipeline report records:

```text
last_completed_stage=report
failed_stage=none
parse_ok=1
semantic_ok=1
model_ok=1
lowering_ok=1
lir_ok=1
no_effect_chain_ok=1
evidence_level=2
comment_count=<line comment count from parse result>
first_comment_start_offset=<first line comment start offset>
first_comment_end_offset=<first line comment end offset>
first_comment_start_line=<first line comment start line>
first_comment_start_column=<first line comment start column>
first_comment_end_line=<first line comment end line>
first_comment_end_column=<first line comment end column>
first_declaration_node_index=<first lowered declaration node index>
first_declaration_kind=<first lowered declaration kind>
first_declaration_name=<first lowered declaration name>
first_declaration_source=<first lowered declaration source name>
first_declaration_parse_index=<first lowered declaration parse index>
first_declaration_first_clause_index=<first lowered declaration first clause index>
first_declaration_clause_count=<first lowered declaration clause count>
first_declaration_source_index=<first lowered declaration source index>
first_clause_node_index=<first lowered clause node index>
first_clause_role=<first lowered clause role>
first_clause_effect=<first lowered clause effect>
first_clause_name=<first lowered clause name>
first_clause_operator=<first lowered clause operator text>
first_clause_value=<first lowered clause value text>
```

## Failure report path

Known failure paths record the failed stage deterministically:

```text
parse_not_ok -> failed_stage=parse
semantic_not_ok -> failed_stage=semantic
semantic_not_valid -> failed_stage=semantic
model_not_ok -> failed_stage=model
lowering_not_ok -> failed_stage=lowering
no_effect_violation -> failed_stage=effect-check
null_argument / internal_error -> failed_stage=unknown
```

## Implementation files

This slice updates or adds:

```text
include/latticra/lat_pipeline.h
src/lat_pipeline.c
tests/lat_pipeline_invariants.c
tests/lat_pipeline_report_refinement.c
docs/LAT_PIPELINE_REPORT_REFINEMENT.md
scripts/test-lat-pipeline-report-refinement.sh
.github/workflows/lat-pipeline-report-refinement.yml
```

The existing Lat pipeline runner also compiles and runs the focused report refinement tests:

```text
scripts/test-lat-pipeline.sh
```

## Validation

Run:

```sh
sh scripts/test-lat-pipeline-report-refinement.sh
sh scripts/test-lat-pipeline.sh
```

The focused invariant tests verify:

```text
lat_pipeline_report_refinement_labels_are_stable
lat_pipeline_report_refinement_reports_success_stage_summary
lat_pipeline_report_refinement_reports_parse_failure_stage
lat_pipeline_report_refinement_reports_semantic_failure_stage
lat_pipeline_report_refinement_null_result_sets_unknown_stage
```

The aggregate Lat pipeline invariants also verify that parser comment metadata is copied into the pipeline result and emitted in `LAT PIPELINE REPORT`.

## Compatibility

This refinement preserves the existing Lat pipeline behavior for:

```text
source parsing
semantic validation
Lat model normalization
Lat-to-LIR lowering
LIR metadata output
aggregate pipeline error labels
module/source/count/span reporting
parser line-comment count and first-comment span reporting
no-effect flags
small-buffer behavior
null-argument behavior
```

## Non-claims

This report refinement does not provide:

```text
Lat execution
Lat compilation
Lat interpretation
LIR execution
runtime behavior
command execution
task effect execution
state mutation
file I/O
network I/O
server interaction
hardware behavior
terminal control
security isolation
sandboxing
malware prevention
ransomware prevention
certification
accreditation
operating-system completeness
```
