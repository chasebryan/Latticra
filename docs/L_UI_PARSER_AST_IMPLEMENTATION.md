# Latticra L-UI Parser AST Implementation

Status: implementation contract
Scope: fixed-size AST metadata, source-backed purpose/text extraction, parse-result integration, source-span-aware nodes, compact and detailed AST reports, and no-effect invariants.

## Purpose

The L-UI Parser AST implementation builds a fixed-size metadata tree for validated L-UI source.

It depends on successful source validation. It copies labels, bindings, source-backed purpose text, source-backed text values, and source spans into bounded public structures. It does not add rendering, command behavior, Nucleus task handling, live movement, state mutation, server interaction, recovery behavior, self-update behavior, hardware behavior, or boot behavior.

## Implementation files

```text
include/latticra/l_ui_parser.h
src/l_ui_parser_ast.c
tests/l_ui_parser_ast_invariants.c
tests/l_ui_parser_ast_detailed_report_invariants.c
tests/l_ui_ast_source_backed_text_invariants.c
scripts/test-l-ui-parser-ast.sh
scripts/test-l-ui-ast-detailed-report.sh
scripts/test-l-ui-ast-source-backed-text.sh
```

## Public API

```text
latticra_l_ui_ast_node_kind_label
latticra_l_ui_parse_ast
latticra_l_ui_ast_report
latticra_l_ui_ast_detailed_report
```

## Public types

The implementation adds:

```text
latticra_l_ui_ast_node_kind_t
latticra_l_ui_ast_card_t
latticra_l_ui_ast_rail_t
latticra_l_ui_ast_field_t
latticra_l_ui_ast_text_t
latticra_l_ui_ast_result_t
```

## Capacity constants

```text
LATTICRA_L_UI_AST_RAIL_MAX = 16
LATTICRA_L_UI_AST_FIELD_MAX = 64
LATTICRA_L_UI_AST_TEXT_MAX = 16
LATTICRA_L_UI_AST_LABEL_MAX = 64
LATTICRA_L_UI_AST_BINDING_MAX = 96
LATTICRA_L_UI_AST_PURPOSE_MAX = 128
LATTICRA_L_UI_AST_REPORT_MAX = 2048
LATTICRA_L_UI_AST_DETAILED_REPORT_MAX = 16384
```

## Node kinds

Stable node kind labels:

```text
card
rail
field
text
binding
unknown
```

## AST result

A valid AST result contains:

```text
parse_result
card
rails[]
fields[]
texts[]
rail_count
field_count
text_count
no_effect
execution_allowed
mutation_allowed
server_allowed
recovery_allowed
hardware_allowed
```

## First accepted fixture

The first accepted source remains:

```text
examples/l-ui/nucleus-preview-card.lui
```

The expected AST summary is:

```text
card=NucleusPreview
rail_count=9
field_count=23
text_count=2
effect=none
boundary=preview_only
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

## Source-backed text extraction

The AST extracts these values from validated source:

```text
purpose "..." -> ast.card.purpose
first text "..." -> ast.texts[0].value
second text "..." -> ast.texts[1].value
```

The surrounding quotes are not copied into AST values.

The extraction copies raw bytes between quotes and does not decode string escapes.

If an extracted value is too large for its fixed destination buffer, AST construction classifies the result as:

```text
LATTICRA_L_UI_PARSE_INTERNAL_ERROR
```

and avoids partial AST counts.

## Source-span usage

The AST copies source spans into populated nodes:

```text
card.span
rail.span
field.span
field.binding_span
text.span
```

Text spans cover the extracted text value range. No public purpose span is currently exposed.

Spans are metadata only.

## Ownership and lifetime

The AST implementation:

- uses fixed-size public storage;
- copies labels, purpose text, text values, binding paths, and spans;
- does not retain borrowed pointers into source;
- does not require heap allocation;
- treats all nodes as metadata only.

## Failed parse behavior

AST construction depends on successful validation by `latticra_l_ui_parse_source`.

If parsing fails:

```text
ast.parse_result.error = parser error
ast.rail_count = 0
ast.field_count = 0
ast.text_count = 0
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

No partial AST is emitted in the first implementation.

Detailed AST reporting renders a compact failed-parse report in this case.

## Compact AST report

The compact AST report renders:

```text
L-UI AST SUMMARY
card=<card>
rail_count=<n>
field_count=<n>
text_count=<n>
effect=<effect>
boundary=<boundary>
no_effect=<0|1>
execution_allowed=<0|1>
mutation_allowed=<0|1>
server_allowed=<0|1>
recovery_allowed=<0|1>
hardware_allowed=<0|1>
```

## Detailed AST report

The detailed AST report renders deterministic card, rail, field, text, source-span, binding-span, escaped-string, and no-effect metadata.

The detailed report starts with:

```text
L-UI AST DETAILED REPORT
card=NucleusPreview
purpose=operator-visible Nucleus preview report
effect=none
boundary=preview_only
rail_count=9
field_count=23
text_count=2
```

Detailed report capacity:

```text
LATTICRA_L_UI_AST_DETAILED_REPORT_MAX = 16384
```

## Test commands

Run:

```sh
sh scripts/test-l-ui-parser-ast.sh
sh scripts/test-l-ui-ast-detailed-report.sh
sh scripts/test-l-ui-ast-source-backed-text.sh
```

The main C workflow runs these checks after the AST implementation-plan guard, detailed report implementation-plan guard, and source-backed text implementation-plan guard.

## Required invariants

The AST tests verify:

```text
valid_fixture_builds_ast_summary
ast_card_name_is_nucleus_preview
ast_counts_match_fixture
ast_preserves_effect_none
ast_preserves_boundary_preview_only
ast_contains_required_rails
ast_contains_required_fields
ast_contains_text_nodes
ast_nodes_have_source_spans
ast_bindings_have_binding_spans
ast_rejects_failed_parse
ast_preserves_no_effect_flags
ast_report_contains_required_fields
ast_report_is_deterministic
ast_capacity_limits_are_enforced
ast_does_not_retain_source_pointers
ast_labels_are_stable
ast_node_kind_labels_are_stable
```

The detailed report tests verify deterministic card, rail, field, text, source-span, binding-span, failed-parse, and no-effect output.

The source-backed text tests verify extracted purpose/text values, copy ownership, quote exclusion, capacity failure classification, detailed report updates, no-effect preservation, and raw escape preservation.

## Current evidence level

This implementation is an L2 tested metadata AST, source-backed text extraction, and detailed-report model for validated L-UI source.

It is not a renderer, UI runtime, command surface, Nucleus task runner, server client, update engine, recovery system, hardware system, boot system, or security boundary.

## Next implementation step

The next implementation candidate after source-backed text extraction is:

```text
L-UI string-literal escape contract
```

That future work should define whether and how string escapes are decoded before AST extraction decodes escape sequences.

## Non-claims

This document and implementation do not claim L-UI rendering, command behavior, Nucleus task handling, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.
