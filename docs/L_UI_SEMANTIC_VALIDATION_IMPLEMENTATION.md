# Latticra L-UI Semantic Validation Implementation

Status: initial implementation contract
Scope: no-effect semantic validation API, result model, reports, and invariants for L-UI ASTs.

## Purpose

The L-UI Semantic Validation implementation adds a bounded, deterministic validation layer after structural parsing and AST construction.

It validates meaning over the existing L-UI AST without rendering UI, lowering to LIR, executing bindings, reading files, writing files, opening network connections, mutating state, or calling Nucleus task behavior.

## Implementation files

```text
include/latticra/l_ui_parser.h
src/l_ui_parser_semantic.c
tests/l_ui_semantic_validation_invariants.c
scripts/test-l-ui-semantic-validation.sh
.github/workflows/c.yml
```

Related active files:

```text
src/l_ui_parser.c
src/l_ui_parser_ast.c
src/l_ui_parser_diagnostics.c
docs/L_UI_SEMANTIC_VALIDATION_CONTRACT.md
docs/L_UI_SEMANTIC_VALIDATION_IMPLEMENTATION_PLAN.md
```

## Public API

The public API adds:

```text
latticra_l_ui_semantic_error_t
latticra_l_ui_semantic_result_t
latticra_l_ui_semantic_error_label
latticra_l_ui_validate_semantics
latticra_l_ui_semantic_report
```

The validator consumes:

```text
const latticra_l_ui_ast_result_t *ast
```

and writes:

```text
latticra_l_ui_semantic_result_t *result
```

## Semantic error labels

Stable labels:

```text
ok
parser_failed
duplicate_rail
missing_required_rail
duplicate_field
field_rail_mismatch
binding_field_mismatch
unsupported_binding_target
text_rail_mismatch
card_count_mismatch
internal_error
```

## Semantic report

The semantic report is deterministic and bounded.

It starts with:

```text
L-UI SEMANTIC VALIDATION RESULT
```

and includes:

```text
status
error
parser_error
card
rail
field
binding
rail_index
field_index
text_index
rail_count
field_count
text_count
no_effect
execution_allowed
mutation_allowed
server_allowed
recovery_allowed
hardware_allowed
span_start_offset
span_end_offset
span_start_line
span_start_column
span_end_line
span_end_column
```

Small output buffers return:

```text
LATTICRA_STATUS_BUFFER_TOO_SMALL
```

and clear the output buffer.

## Checks implemented

The first semantic validation implementation verifies:

```text
card=NucleusPreview
effect=none
boundary=preview_only
rail_count=9
field_count=23
text_count=2
required rail names
rail uniqueness
rail field/text ownership metadata
field uniqueness
field names in deterministic order
binding prefixes
field/binding pair consistency
text placement
no-effect flags
```

## Parser-failed behavior

If parsing failed, semantic validation does not inspect AST nodes.

It reports:

```text
error=parser_failed
parser_error=<existing-parser-error-label>
rail_count=0
field_count=0
text_count=0
```

This does not replace parser diagnostics or failed-parse AST reports.

## Source-span behavior

Semantic failures use existing AST spans:

```text
rail errors -> rail span
field errors -> field span
binding errors -> binding span
text errors -> text span
card/count errors -> card span
parser_failed -> parse-result span
```

Semantic validation does not invent byte offsets.

## No-effect boundary

Semantic validation is metadata-only.

It preserves:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

## Compatibility

This implementation does not change:

```text
existing parser behavior
existing parser diagnostic codes
existing AST construction behavior
existing detailed AST report behavior
escaped decoded NUL acceptance
literal source-buffer NUL rejection
source-span byte offset behavior
current accepted fixture counts
compact AST report behavior
failed-parse detailed report behavior
```

The first accepted fixture still reports:

```text
rail_count=9
field_count=23
text_count=2
effect=none
boundary=preview_only
```

## Test command

Run:

```sh
sh scripts/test-l-ui-semantic-validation.sh
```

The main C workflow runs this check after the semantic validation implementation-plan guard and before the string-literal escape guards.

## Required invariants

The semantic validation tests verify:

```text
semantic_validation_accepts_current_fixture
semantic_validation_rejects_duplicate_rail
semantic_validation_rejects_missing_required_rail
semantic_validation_rejects_duplicate_field
semantic_validation_rejects_field_rail_mismatch
semantic_validation_rejects_binding_field_mismatch
semantic_validation_rejects_unsupported_binding_target
semantic_validation_rejects_text_rail_mismatch
semantic_validation_rejects_card_count_mismatch
semantic_validation_skips_when_parser_failed
semantic_validation_reports_source_spans
semantic_validation_preserves_no_effect_flags
semantic_validation_does_not_change_ast_report
semantic_validation_does_not_change_escaped_x00_acceptance
semantic_validation_does_not_change_literal_nul_rejection
semantic_validation_is_deterministic
semantic_validation_report_rejects_small_buffer
semantic_validation_error_labels_are_stable
```

## Current evidence level

This implementation is an L2 tested semantic validation layer for the current L-UI AST fixture model.

It is not LIR lowering, L-UI rendering, Lat execution, command behavior, Nucleus task execution, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, malware prevention, ransomware prevention, or operating-system completeness.

## Next implementation step

The next implementation candidate is:

```text
LIR shape contract
```

That future work should define the first Latticra Intermediate Representation shape before any lowering implementation.

## Non-claims

This document and implementation do not implement LIR lowering, L-UI rendering, Lat execution, command behavior, Nucleus task handling, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, malware prevention, ransomware prevention, or operating-system completeness.
