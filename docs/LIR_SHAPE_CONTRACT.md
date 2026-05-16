# Latticra LIR Shape Contract

Status: LIR shape contract
Scope: first Latticra Intermediate Representation shape before semantic lowering, Lat integration, rendering, execution, or runtime behavior.

## Purpose

This document defines the first contract for LIR: the Latticra Intermediate Representation.

LIR is the planned internal representation between validated declarations and later implementation stages.

The current repository has structural L-UI parsing, AST construction, source spans, string handling, source-buffer policies, and semantic validation. LIR shape planning comes next so future lowering has a stable target before code is added.

This document does not implement LIR.

## Relationship to previous work

This contract depends on:

```text
docs/L_UI_PARSER_AST_IMPLEMENTATION.md
docs/L_UI_AST_DETAILED_REPORT_IMPLEMENTATION.md
docs/L_UI_SOURCE_BUFFER_LITERAL_NUL_POLICY_IMPLEMENTATION.md
docs/L_UI_SEMANTIC_VALIDATION_CONTRACT.md
docs/L_UI_SEMANTIC_VALIDATION_IMPLEMENTATION_PLAN.md
docs/L_UI_SEMANTIC_VALIDATION_IMPLEMENTATION.md
include/latticra/l_ui_parser.h
src/l_ui_parser_ast.c
src/l_ui_parser_semantic.c
```

Those files remain the source of truth for L-UI AST shape, semantic validation, source spans, no-effect metadata, and parser/semantic boundaries.

## LIR role

LIR should be a small, explicit representation used after source parsing and semantic validation.

Recommended future pipeline:

```text
source bytes
  -> structural parser
  -> AST construction
  -> semantic validation
  -> LIR lowering
  -> future analysis, rendering, planning, or execution only if separately allowed
```

LIR should not bypass parser or semantic validation.

## First LIR unit

The first LIR unit should be a module-like object representing one validated L-UI card.

Suggested root object:

```text
latticra_lir_module_t
```

Initial fields:

```text
status
source_kind
module_name
card_name
effect
boundary
node_count
edge_count
binding_count
text_count
source_span
no_effect
execution_allowed
mutation_allowed
server_allowed
recovery_allowed
hardware_allowed
```

## Source kind

Initial source kind labels:

```text
unknown
l_ui_card
lat_module
internal_fixture
```

Only `l_ui_card` is in scope for the first LIR lowering path.

## Node kinds

Initial LIR node kinds:

```text
module
card
rail
field
text
binding
effect
boundary
```

A future implementation plan may add more node kinds, but this contract keeps the first set minimal.

## Node shape

Suggested node shape:

```text
kind
name
value
binding
source_span
parent_index
first_child_index
child_count
flags
```

Rules:

- all nodes have deterministic indexes;
- parent/child relationships are index-based;
- source spans come from parser/AST metadata;
- string values use explicit lengths when needed;
- no node is executable by default.

## Edge shape

Suggested edge shape:

```text
from_index
to_index
edge_kind
source_span
```

Initial edge kinds:

```text
contains
binds
annotates
orders_before
```

Edges are metadata only. They do not execute behavior.

## Binding shape

Suggested binding shape:

```text
field_node_index
binding_target
binding_prefix
source_span
resolved_kind
```

Initial binding prefixes:

```text
state
preview
```

Initial resolved kinds:

```text
state_value
preview_value
unsupported
```

Bindings remain symbolic. LIR must not evaluate host state or preview state.

## Text shape

Text values should carry explicit byte lengths.

Suggested text shape:

```text
text_node_index
value
value_len
escaped_value
source_span
```

`value_len` remains authoritative for embedded NUL values.

Raw C-string compatibility fields must not be the assertion target for embedded NUL values.

## Effect and boundary shape

LIR should carry effect and boundary metadata from validated input.

Initial allowed values:

```text
effect=none
boundary=preview_only
```

No other effect or boundary should be accepted into first LIR shape without a separate contract.

## Semantic prerequisite

LIR lowering may only operate after semantic validation succeeds:

```text
semantic_error=ok
parser_error=ok
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

If semantic validation failed, LIR lowering should not materialize a partial LIR.

## Source-span behavior

Every LIR node that comes from source should carry a source span from parser or AST metadata.

Rules:

- module/card spans come from card spans;
- rail spans come from rail spans;
- field spans come from field spans;
- binding spans come from binding spans;
- text spans come from text spans;
- effect and boundary spans may use card metadata until more specific spans exist;
- LIR must not invent byte positions.

## Report model

A future LIR report should be deterministic and bounded.

Suggested fields:

```text
LATTICRA LIR REPORT
status=<status>
source_kind=<kind>
module=<name>
card=<name>
effect=<effect>
boundary=<boundary>
node_count=<count>
edge_count=<count>
binding_count=<count>
text_count=<count>
no_effect=<0|1>
execution_allowed=<0|1>
mutation_allowed=<0|1>
server_allowed=<0|1>
recovery_allowed=<0|1>
hardware_allowed=<0|1>
```

Detailed reports may later include node and edge tables.

## Capacity policy

The first LIR implementation should use fixed capacities aligned with existing AST limits.

Suggested capacities:

```text
LATTICRA_LIR_NODE_MAX >= LATTICRA_L_UI_AST_RAIL_MAX + LATTICRA_L_UI_AST_FIELD_MAX + LATTICRA_L_UI_AST_TEXT_MAX + card/effect/boundary overhead
LATTICRA_LIR_EDGE_MAX bounded and deterministic
LATTICRA_LIR_BINDING_MAX bounded and deterministic
LATTICRA_LIR_TEXT_MAX bounded and deterministic
```

A future implementation plan must name exact constants before code is added.

## Error model

LIR should have a separate error space from parser and semantic errors.

Recommended future labels:

```text
ok
null_argument
semantic_failed
capacity_exceeded
unsupported_source_kind
unsupported_node_kind
unsupported_effect
unsupported_boundary
internal_error
```

Exact enum names should be defined in the implementation plan.

## No-effect rule

LIR shape and reports are metadata-only.

They must preserve:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

LIR work must not render UI, execute bindings, evaluate host state, call Nucleus task code, write files, read files, open network connections, call server code, call update code, call recovery code, or touch hardware.

## Compatibility expectations

LIR shape work must not change:

```text
existing parser behavior
existing parser diagnostic codes
existing AST construction behavior
existing detailed AST report behavior
existing semantic validation behavior
escaped decoded NUL acceptance
literal source-buffer NUL rejection
source-span byte offset behavior
no-effect flags
current accepted fixture counts
```

The first accepted fixture should still report:

```text
rail_count=9
field_count=23
text_count=2
effect=none
boundary=preview_only
```

## Future implementation gate

LIR implementation must not begin until a separate implementation plan defines:

1. public API shape;
2. LIR struct names;
3. capacity constants;
4. node enum labels;
5. edge enum labels;
6. error enum labels;
7. report format;
8. semantic prerequisite behavior;
9. source-span mapping;
10. exact tests;
11. compatibility expectations;
12. non-claims.

## Future test list

A future implementation plan should include tests for:

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
lir_shape_is_deterministic
```

## Forbidden behavior

LIR shape work must not:

- lower invalid semantic input;
- execute bindings;
- evaluate host state;
- call Nucleus task execution;
- render L-UI;
- execute Lat;
- mutate state;
- write files;
- read files;
- open network connections;
- call server code;
- call update code;
- call recovery code;
- call hardware code;
- broaden accepted syntax;
- weaken parser diagnostics;
- weaken semantic validation;
- accept literal source-buffer NUL;
- remove escaped decoded NUL support;
- make raw C-string fields authoritative for embedded NUL values.

## Current validation command

This contract is guarded by:

```sh
sh scripts/test-lir-shape-contract.sh
```

The guard is static. It does not implement LIR.

## Non-claims

This document does not implement LIR, LIR lowering, L-UI rendering, Lat execution, command behavior, Nucleus task handling, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, malware prevention, ransomware prevention, or operating-system completeness.
