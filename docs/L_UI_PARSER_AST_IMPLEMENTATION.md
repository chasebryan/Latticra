# Latticra L-UI Parser AST Implementation

Status: initial implementation contract
Scope: fixed-size AST metadata, parse-result integration, source-span-aware nodes, deterministic AST report, and no-effect invariants.

## Purpose

The L-UI Parser AST implementation builds a fixed-size metadata tree for validated L-UI source.

It depends on successful source validation. It copies labels, bindings, text values, and source spans into bounded public structures. It does not add rendering, command behavior, Nucleus task handling, live movement, state mutation, server interaction, recovery behavior, self-update behavior, hardware behavior, or boot behavior.

## Implementation files

```text
include/latticra/l_ui_parser.h
src/l_ui_parser_ast.c
tests/l_ui_parser_ast_invariants.c
scripts/test-l-ui-parser-ast.sh
```

## Public API

```text
latticra_l_ui_ast_node_kind_label
latticra_l_ui_parse_ast
latticra_l_ui_ast_report
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

## Source-span usage

The AST copies source spans into populated nodes:

```text
card.span
rail.span
field.span
field.binding_span
text.span
```

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

## AST report

The AST report renders:

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

Detailed node reporting is intentionally deferred.

## Test command

Run:

```sh
sh scripts/test-l-ui-parser-ast.sh
```

The main C workflow runs this check after the AST implementation-plan guard.

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

The implementation also checks bad argument and small-buffer behavior.

## Current evidence level

This implementation is an L2 tested metadata AST model for validated L-UI source.

It is not a renderer, UI runtime, command surface, Nucleus task runner, server client, update engine, recovery system, hardware system, boot system, or security boundary.

## Next implementation step

The next implementation candidate after the AST is:

```text
L-UI AST detailed report contract
```

That future work should define deterministic rail, field, text, and source-span reporting before adding detailed AST reports.

## Non-claims

This document and implementation do not claim L-UI rendering, command behavior, Nucleus task handling, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.
