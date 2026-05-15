# Latticra L-UI AST Detailed Report Implementation

Status: implementation contract
Scope: bounded detailed AST reporting for card, rail, field, text, source-span, escaped string, and no-effect metadata.

## Purpose

The L-UI AST Detailed Report implementation renders deterministic text for the fixed-size L-UI AST metadata model.

It makes card, rail, field, text, source-span, binding-span, and escaped string metadata visible without adding rendering, command behavior, Nucleus task handling, live movement, state mutation, server interaction, recovery behavior, self-update behavior, hardware behavior, or boot behavior.

## Implementation files

```text
include/latticra/l_ui_parser.h
src/l_ui_parser_ast.c
tests/l_ui_parser_ast_detailed_report_invariants.c
tests/l_ui_ast_escaped_string_report_invariants.c
scripts/test-l-ui-ast-detailed-report.sh
scripts/test-l-ui-ast-escaped-string-report.sh
```

## Public API

```text
latticra_l_ui_ast_detailed_report
```

## Report capacity

```text
LATTICRA_L_UI_AST_DETAILED_REPORT_MAX = 16384
```

The detailed report is larger than the compact AST report because it prints every populated rail, field, text node, source span, binding span, and escaped string field.

## Report shape

The report starts with:

```text
L-UI AST DETAILED REPORT
card=NucleusPreview
purpose=operator-visible Nucleus preview report
effect=none
boundary=preview_only
rail_count=9
field_count=23
text_count=2
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

Then it renders sections in deterministic order:

```text
[card]
[rail 0] ... [rail 8]
[field 0] ... [field 22]
[text 0] ... [text 1]
```

Unused capacity slots are not printed.

## Escaped string fields

The detailed report keeps existing literal fields and adds escaped variants:

```text
purpose=<literal-purpose>
purpose_escaped=<escaped-purpose>
value=<literal-text>
value_escaped=<escaped-text>
```

Escaped fields are additive and appear only in:

```text
[card]
[text <index>]
```

Escaped fields do not appear in failed-parse reports.

## Span fields

Node spans render as:

```text
span_start_offset=<n>
span_end_offset=<n>
span_start_line=<n>
span_start_column=<n>
span_end_line=<n>
span_end_column=<n>
```

Field binding spans render as:

```text
binding_span_start_offset=<n>
binding_span_end_offset=<n>
binding_span_start_line=<n>
binding_span_start_column=<n>
binding_span_end_line=<n>
binding_span_end_column=<n>
```

## Failed parse behavior

If AST construction contains a parser error, the detailed report renders a compact failed-parse report:

```text
L-UI AST DETAILED REPORT
parse_error=<error-label>
rail_count=0
field_count=0
text_count=0
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

No partial AST nodes or escaped fields are printed for failed parses.

## Escaping policy

Escaped string fields use the byte-oriented escaping model documented in:

```text
docs/L_UI_AST_ESCAPED_STRING_REPORT_IMPLEMENTATION.md
```

The first implementation renders current literal fields for compatibility while adding escaped fields for fixture-safe comparisons and future broader text handling.

## Compatibility

The implementation does not change:

```text
latticra_l_ui_ast_report
latticra_l_ui_parse_ast
latticra_l_ui_parse_source
latticra_l_ui_parse_result_report
latticra_l_ui_diagnostic_report
latticra_l_ui_ast_detailed_report existing required fields
```

## No-effect boundary

Detailed reporting preserves:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

## Test commands

Run:

```sh
sh scripts/test-l-ui-ast-detailed-report.sh
sh scripts/test-l-ui-ast-escaped-string-report.sh
```

The main C workflow runs these checks after the detailed report implementation-plan guard and escaped string report implementation-plan guard.

## Required invariants

The detailed report tests verify:

```text
detailed_report_contains_title
detailed_report_contains_card_section
detailed_report_contains_all_rails
detailed_report_contains_all_fields
detailed_report_contains_all_text_nodes
detailed_report_preserves_rail_order
detailed_report_preserves_field_order
detailed_report_preserves_text_order
detailed_report_includes_card_span
detailed_report_includes_rail_spans
detailed_report_includes_field_spans
detailed_report_includes_binding_spans
detailed_report_includes_text_spans
detailed_report_preserves_no_effect_flags
detailed_report_is_deterministic
detailed_report_rejects_bad_arguments
detailed_report_rejects_small_buffers
detailed_report_omits_unused_capacity_slots
detailed_report_handles_failed_parse
```

The escaped string report tests verify additive escaped purpose/text fields and byte-oriented escaping behavior.

## Current evidence level

This implementation is an L2 tested detailed metadata and escaped string report for the fixed-size L-UI AST.

It is not a renderer, UI runtime, command surface, Nucleus task runner, server client, update engine, recovery system, hardware system, boot system, or security boundary.

## Next implementation step

The next implementation candidate after escaped string reporting is:

```text
L-UI AST source-backed text extraction contract
```

That future work should define how AST purpose and text values are extracted from source instead of fixed fixture metadata.

## Non-claims

This document and implementation do not claim L-UI rendering, command behavior, Nucleus task handling, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.
