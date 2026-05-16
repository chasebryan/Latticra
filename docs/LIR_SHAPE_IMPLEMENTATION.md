# Latticra LIR Shape Implementation

Status: initial implementation contract
Scope: bounded no-effect LIR shape API, lowering, report, and invariants for semantically valid L-UI ASTs.

## Purpose

This implementation adds the first LIR shape for Latticra.

LIR is the Latticra Intermediate Representation. The first implementation lowers only a semantically valid L-UI AST into a bounded metadata graph.

This implementation does not execute LIR, render L-UI, lower Lat, call Nucleus task behavior, read files, write files, open network connections, mutate state, or touch hardware.

## Implementation files

```text
include/latticra/lir.h
src/lir.c
tests/lir_shape_invariants.c
scripts/test-lir-shape.sh
.github/workflows/c.yml
```

Related active files:

```text
include/latticra/l_ui_parser.h
src/l_ui_parser_ast.c
src/l_ui_parser_semantic.c
docs/LIR_SHAPE_CONTRACT.md
docs/LIR_SHAPE_IMPLEMENTATION_PLAN.md
```

## Public API

The public API adds:

```text
latticra_lir_source_kind_t
latticra_lir_node_kind_t
latticra_lir_edge_kind_t
latticra_lir_resolved_binding_kind_t
latticra_lir_error_t
latticra_lir_node_t
latticra_lir_edge_t
latticra_lir_binding_ref_t
latticra_lir_text_ref_t
latticra_lir_module_t
latticra_lir_error_label
latticra_lir_source_kind_label
latticra_lir_node_kind_label
latticra_lir_edge_kind_label
latticra_lir_resolved_binding_kind_label
latticra_lir_lower_l_ui_ast
latticra_lir_report
```

## Capacity constants

The first LIR implementation uses exact bounded constants:

```text
LATTICRA_LIR_NAME_MAX 64u
LATTICRA_LIR_VALUE_MAX 128u
LATTICRA_LIR_BINDING_MAX 96u
LATTICRA_LIR_NODE_MAX 96u
LATTICRA_LIR_EDGE_MAX 128u
LATTICRA_LIR_BINDING_REF_MAX 32u
LATTICRA_LIR_TEXT_MAX 16u
LATTICRA_LIR_REPORT_MAX 8192u
```

## Lowering prerequisite

`latticra_lir_lower_l_ui_ast` requires:

```text
ast != NULL
semantic != NULL
module != NULL
ast->parse_result.error == LATTICRA_L_UI_PARSE_OK
semantic->error == LATTICRA_L_UI_SEMANTIC_OK
semantic->parser_error == LATTICRA_L_UI_PARSE_OK
semantic->no_effect == 1
semantic->execution_allowed == 0
semantic->mutation_allowed == 0
semantic->server_allowed == 0
semantic->recovery_allowed == 0
semantic->hardware_allowed == 0
```

If the prerequisite fails, it does not materialize a partial LIR graph.

Expected failure state:

```text
module.error=semantic_failed
node_count=0
edge_count=0
binding_count=0
text_count=0
```

## Deterministic node plan

Successful L-UI lowering currently produces deterministic nodes:

```text
0: module
1: card
2-10: rails in current L-UI order
11-33: fields in current AST order
34-35: text nodes
36-58: binding nodes
59: effect
60: boundary
```

Expected successful counts:

```text
node_count=61
edge_count=60
binding_count=23
text_count=2
```

## Source-span mapping

LIR nodes use existing parser/AST spans:

```text
module -> ast.card.span
card -> ast.card.span
rail -> ast.rails[index].span
field -> ast.fields[index].span
binding -> ast.fields[index].binding_span
text -> ast.texts[index].span
effect -> ast.card.span
boundary -> ast.card.span
```

LIR does not invent byte offsets.

## Text and binding preservation

Text references preserve explicit byte lengths:

```text
text_node_index
value
value_len
escaped_value
source_span
```

`value_len` is authoritative for embedded NUL values.

Binding references preserve symbolic binding metadata:

```text
field_node_index
binding_target
binding_prefix
source_span
resolved_kind
```

Initial resolved binding kinds are:

```text
state_value
preview_value
unsupported
```

Bindings remain symbolic and are not executed or evaluated.

## Report format

`latticra_lir_report` emits a deterministic bounded report beginning with:

```text
LATTICRA LIR REPORT
```

and including:

```text
status
error
source_kind
module
card
effect
boundary
node_count
edge_count
binding_count
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

## No-effect boundary

LIR shape lowering and reports are metadata-only.

They preserve:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

## Test command

Run:

```sh
sh scripts/test-lir-shape.sh
```

The main C workflow runs this check after the LIR shape implementation-plan guard and before the string-literal escape guards.

## Required invariants

The LIR shape tests verify:

```text
lir_shape_accepts_semantically_valid_l_ui_fixture
lir_shape_rejects_parser_failed_ast
lir_shape_rejects_semantic_failed_ast
lir_shape_preserves_card_metadata
lir_shape_preserves_rail_nodes
lir_shape_preserves_field_nodes
lir_shape_preserves_binding_nodes
lir_shape_preserves_text_nodes_with_lengths
lir_shape_preserves_source_spans
lir_shape_preserves_no_effect_flags
lir_shape_report_is_deterministic
lir_shape_report_rejects_small_buffer
lir_shape_does_not_change_ast_report
lir_shape_does_not_change_semantic_report
lir_shape_does_not_change_escaped_x00_acceptance
lir_shape_does_not_change_literal_nul_rejection
lir_shape_error_labels_are_stable
lir_shape_kind_labels_are_stable
lir_shape_is_deterministic
```

## Compatibility

This implementation does not change:

```text
existing parser behavior
existing parser diagnostic codes
existing AST construction behavior
existing detailed AST report behavior
existing semantic validation behavior
escaped decoded NUL acceptance
literal source-buffer NUL rejection
source-span byte offset behavior
current accepted fixture counts
```

The first accepted fixture still reports:

```text
rail_count=9
field_count=23
text_count=2
effect=none
boundary=preview_only
```

## Current evidence level

This implementation is an L2 tested intermediate-representation shape for semantically valid L-UI AST fixtures.

It is not LIR execution, L-UI rendering, Lat execution, command behavior, Nucleus task execution, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, malware prevention, ransomware prevention, or operating-system completeness.

## Next implementation step

The next implementation candidate is:

```text
Lat language grammar contract
```

That future work should define the first Lat / Latticra Programming Language grammar before implementation.

## Non-claims

This document and implementation do not implement LIR execution, L-UI rendering, Lat execution, command behavior, Nucleus task handling, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, malware prevention, ransomware prevention, or operating-system completeness.
