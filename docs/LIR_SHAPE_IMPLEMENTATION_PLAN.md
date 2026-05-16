# Latticra LIR Shape Implementation Plan

Status: implementation planning contract
Scope: exact API, structs, capacities, enum labels, report format, semantic prerequisite behavior, source-span mapping, tests, compatibility expectations, and non-claims before LIR code.

## Purpose

This document defines the implementation plan for the first LIR shape.

The LIR shape contract is already merged and guarded. This plan names exact public API additions, struct names, capacity constants, node enum labels, edge enum labels, error enum labels, report format, semantic prerequisite behavior, source-span mapping, test files, documentation updates, compatibility expectations, and non-claims required before LIR code is added.

This document does not implement LIR.

## Relationship to previous work

This plan depends on:

```text
docs/LIR_SHAPE_CONTRACT.md
docs/L_UI_SEMANTIC_VALIDATION_IMPLEMENTATION.md
docs/L_UI_SEMANTIC_VALIDATION_IMPLEMENTATION_PLAN.md
docs/L_UI_PARSER_AST_IMPLEMENTATION.md
docs/L_UI_AST_DETAILED_REPORT_IMPLEMENTATION.md
docs/L_UI_SOURCE_BUFFER_LITERAL_NUL_POLICY_IMPLEMENTATION.md
include/latticra/l_ui_parser.h
src/l_ui_parser_ast.c
src/l_ui_parser_semantic.c
```

Those files remain the source of truth for L-UI AST shape, semantic validation, source spans, no-effect metadata, and parser/semantic boundaries.

## Implementation language decision

The first LIR shape implementation should be in C.

Reason:

- current L-UI parser, AST, semantic validation, and reports are C;
- the first LIR lowering path consumes C structs;
- tests and runners use C and POSIX shell;
- the first LIR layer should stay deterministic, bounded, and no-effect.

## Implementation files

The implementation PR should modify:

```text
include/latticra/lir.h
include/latticra/l_ui_parser.h
src/lir.c
.github/workflows/c.yml
```

The implementation PR should add:

```text
docs/LIR_SHAPE_IMPLEMENTATION.md
tests/lir_shape_invariants.c
scripts/test-lir-shape.sh
```

The implementation should not add rendering, Lat execution, L-UI execution, Nucleus task execution, file I/O, network I/O, mutation, recovery behavior, update behavior, or hardware behavior.

## Public header plan

Add a new public LIR header:

```text
include/latticra/lir.h
```

Include it from:

```text
include/latticra/l_ui_parser.h
```

only if needed for public lowering declarations.

The header should depend only on stable shared types and L-UI parser types needed for source spans and semantic input.

## Capacity constants

Add exact bounded constants:

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

Rationale:

- current AST rail max is 16;
- current AST field max is 64;
- current AST text max is 16;
- 96 nodes gives room for module, card, rails, fields, texts, bindings, effect, and boundary metadata while remaining bounded.

## Public API shape

Add public API names:

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

Recommended function signatures:

```text
const char *latticra_lir_error_label(latticra_lir_error_t error);
const char *latticra_lir_source_kind_label(latticra_lir_source_kind_t kind);
const char *latticra_lir_node_kind_label(latticra_lir_node_kind_t kind);
const char *latticra_lir_edge_kind_label(latticra_lir_edge_kind_t kind);
const char *latticra_lir_resolved_binding_kind_label(latticra_lir_resolved_binding_kind_t kind);

latticra_status_t latticra_lir_lower_l_ui_ast(
    const latticra_l_ui_ast_result_t *ast,
    const latticra_l_ui_semantic_result_t *semantic,
    latticra_lir_module_t *module);

latticra_status_t latticra_lir_report(
    const latticra_lir_module_t *module,
    char *buffer,
    size_t buffer_len);
```

## Source kind enum

Add source kind enum values:

```text
LATTICRA_LIR_SOURCE_UNKNOWN
LATTICRA_LIR_SOURCE_L_UI_CARD
LATTICRA_LIR_SOURCE_LAT_MODULE
LATTICRA_LIR_SOURCE_INTERNAL_FIXTURE
```

Stable labels:

```text
unknown
l_ui_card
lat_module
internal_fixture
```

Only `LATTICRA_LIR_SOURCE_L_UI_CARD` should be produced by the first implementation.

## Node kind enum

Add node kind enum values:

```text
LATTICRA_LIR_NODE_MODULE
LATTICRA_LIR_NODE_CARD
LATTICRA_LIR_NODE_RAIL
LATTICRA_LIR_NODE_FIELD
LATTICRA_LIR_NODE_TEXT
LATTICRA_LIR_NODE_BINDING
LATTICRA_LIR_NODE_EFFECT
LATTICRA_LIR_NODE_BOUNDARY
LATTICRA_LIR_NODE_UNKNOWN
```

Stable labels:

```text
module
card
rail
field
text
binding
effect
boundary
unknown
```

## Edge kind enum

Add edge kind enum values:

```text
LATTICRA_LIR_EDGE_CONTAINS
LATTICRA_LIR_EDGE_BINDS
LATTICRA_LIR_EDGE_ANNOTATES
LATTICRA_LIR_EDGE_ORDERS_BEFORE
LATTICRA_LIR_EDGE_UNKNOWN
```

Stable labels:

```text
contains
binds
annotates
orders_before
unknown
```

## Resolved binding kind enum

Add resolved binding kind enum values:

```text
LATTICRA_LIR_BINDING_STATE_VALUE
LATTICRA_LIR_BINDING_PREVIEW_VALUE
LATTICRA_LIR_BINDING_UNSUPPORTED
```

Stable labels:

```text
state_value
preview_value
unsupported
```

Bindings remain symbolic and must not evaluate host state.

## Error enum

Add LIR error enum values:

```text
LATTICRA_LIR_OK
LATTICRA_LIR_NULL_ARGUMENT
LATTICRA_LIR_SEMANTIC_FAILED
LATTICRA_LIR_CAPACITY_EXCEEDED
LATTICRA_LIR_UNSUPPORTED_SOURCE_KIND
LATTICRA_LIR_UNSUPPORTED_NODE_KIND
LATTICRA_LIR_UNSUPPORTED_EFFECT
LATTICRA_LIR_UNSUPPORTED_BOUNDARY
LATTICRA_LIR_INTERNAL_ERROR
```

Stable labels:

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

## Node struct

Add node struct:

```text
latticra_lir_node_kind_t kind;
char name[LATTICRA_LIR_NAME_MAX];
char value[LATTICRA_LIR_VALUE_MAX];
char binding[LATTICRA_LIR_BINDING_MAX];
latticra_l_ui_source_span_t source_span;
size_t parent_index;
size_t first_child_index;
size_t child_count;
unsigned int flags;
```

Rules:

- indexes are deterministic;
- parent and child references use indexes;
- source spans are copied from AST metadata;
- values remain bounded;
- nodes are metadata-only.

## Edge struct

Add edge struct:

```text
size_t from_index;
size_t to_index;
latticra_lir_edge_kind_t edge_kind;
latticra_l_ui_source_span_t source_span;
```

Edges are metadata only and do not execute behavior.

## Binding reference struct

Add binding reference struct:

```text
size_t field_node_index;
char binding_target[LATTICRA_LIR_BINDING_MAX];
char binding_prefix[LATTICRA_LIR_NAME_MAX];
latticra_l_ui_source_span_t source_span;
latticra_lir_resolved_binding_kind_t resolved_kind;
```

Only `state` and `preview` prefixes are expected from current semantic validation.

## Text reference struct

Add text reference struct:

```text
size_t text_node_index;
char value[LATTICRA_LIR_VALUE_MAX];
size_t value_len;
char escaped_value[LATTICRA_LIR_VALUE_MAX];
latticra_l_ui_source_span_t source_span;
```

`value_len` is authoritative.

## Module struct

Add module struct:

```text
latticra_status_t status;
latticra_lir_error_t error;
latticra_lir_source_kind_t source_kind;
char module_name[LATTICRA_LIR_NAME_MAX];
char card_name[LATTICRA_LIR_NAME_MAX];
char effect[LATTICRA_LIR_NAME_MAX];
char boundary[LATTICRA_LIR_NAME_MAX];
latticra_l_ui_source_span_t source_span;
latticra_lir_node_t nodes[LATTICRA_LIR_NODE_MAX];
latticra_lir_edge_t edges[LATTICRA_LIR_EDGE_MAX];
latticra_lir_binding_ref_t bindings[LATTICRA_LIR_BINDING_REF_MAX];
latticra_lir_text_ref_t texts[LATTICRA_LIR_TEXT_MAX];
size_t node_count;
size_t edge_count;
size_t binding_count;
size_t text_count;
int no_effect;
int execution_allowed;
int mutation_allowed;
int server_allowed;
int recovery_allowed;
int hardware_allowed;
```

The module must be fully initialized on success and on failure.

## L-UI lowering behavior

`latticra_lir_lower_l_ui_ast` should require:

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

If the prerequisite fails, it should return `LATTICRA_STATUS_OK` with:

```text
module.error = LATTICRA_LIR_SEMANTIC_FAILED
module.node_count = 0
module.edge_count = 0
module.binding_count = 0
module.text_count = 0
```

## Initial deterministic node plan

The first implementation should produce deterministic nodes:

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
binding_count=23
text_count=2
```

Edge count may be implementation-defined but must be deterministic and bounded. The implementation plan sets expected minimum:

```text
edge_count >= 60
```

## Report format

`latticra_lir_report` should produce:

```text
LATTICRA LIR REPORT
status=<integer-status>
error=<lir-error-label>
source_kind=<source-kind-label>
module=<module-name>
card=<card-name>
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
span_start_offset=<offset>
span_end_offset=<offset>
span_start_line=<line>
span_start_column=<column>
span_end_line=<line>
span_end_column=<column>
```

Small output buffers should return `LATTICRA_STATUS_BUFFER_TOO_SMALL` and clear the buffer.

## Source-span mapping

Use these source-span mappings:

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

LIR must not invent byte offsets.

## No-effect preservation

LIR is metadata-only.

It must preserve:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

## Exact implementation test list

The implementation PR should include tests for:

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

## Test file plan

Add:

```text
tests/lir_shape_invariants.c
scripts/test-lir-shape.sh
```

Wire into:

```text
.github/workflows/c.yml
```

Run after:

```text
sh scripts/test-lir-shape-contract.sh
```

and before:

```text
sh scripts/test-l-ui-string-literal-escape-contract.sh
```

## Documentation update plan

The implementation PR should update:

```text
README.md
STATUS.md
docs/FOUNDATION_INDEX.md
docs/status/CURRENT_STATUS.md
docs/status/ANNOUNCEMENTS.md
docs/project_notes/CURRENT_DIRECTION.md
docs/project_notes/UPCOMING_WORK.md
docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
docs/LIR_SHAPE_CONTRACT.md
scripts/test-project-strategy-status-framework.sh
```

and add:

```text
docs/LIR_SHAPE_IMPLEMENTATION.md
```

## Compatibility expectations

The implementation must not change:

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

The first accepted fixture should still report:

```text
rail_count=9
field_count=23
text_count=2
effect=none
boundary=preview_only
```

## Forbidden implementation behavior

LIR shape implementation must not:

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

This implementation plan is guarded by:

```sh
sh scripts/test-lir-shape-implementation-plan.sh
```

The guard is static. It does not implement LIR.

## Implementation gate

LIR shape implementation code may be added only after this plan is merged.

## Non-claims

This document does not implement LIR, LIR lowering, L-UI rendering, Lat execution, command behavior, Nucleus task handling, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, malware prevention, ransomware prevention, or operating-system completeness.
