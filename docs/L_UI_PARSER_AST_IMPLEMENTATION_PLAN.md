# Latticra L-UI Parser AST Implementation Plan

Status: implementation planning contract
Scope: public API changes, struct placement, capacity constants, ownership/lifetime rules, source-span integration, exact tests, and compatibility expectations before AST implementation.

## Purpose

This document defines the implementation plan for the first L-UI parser AST.

The AST contract is already merged and guarded. This plan decides the exact C API, structure layout, capacity model, ownership rules, source-span integration, report format, and test list before AST construction code is added.

## Relationship to previous contracts

This plan depends on:

```text
docs/L_UI_PARSER_AST_CONTRACT.md
docs/L_UI_PARSER_SOURCE_SPAN_IMPLEMENTATION.md
docs/L_UI_PARSER.md
include/latticra/l_ui_parser.h
src/l_ui_parser.c
```

Those files remain the source of truth for parser behavior, source spans, diagnostics, and no-effect boundaries.

## Implementation language decision

The AST implementation should be in C.

Reason:

- the parser is implemented in C;
- parse results and spans are C ABI surfaces;
- the first AST must remain fixed-size and portable;
- the current C workflow can validate AST invariants;
- no dynamic runtime should be required.

## Public API change

AST implementation requires public API additions in:

```text
include/latticra/l_ui_parser.h
```

The first AST implementation should add structs and functions, but should not change the existing parser function signatures.

## Proposed capacity constants

Add:

```text
LATTICRA_L_UI_AST_RAIL_MAX = 16
LATTICRA_L_UI_AST_FIELD_MAX = 64
LATTICRA_L_UI_AST_TEXT_MAX = 16
LATTICRA_L_UI_AST_LABEL_MAX = 64
LATTICRA_L_UI_AST_BINDING_MAX = 96
LATTICRA_L_UI_AST_PURPOSE_MAX = 128
LATTICRA_L_UI_AST_REPORT_MAX = 2048
```

These caps are intentionally larger than the first `NucleusPreview` fixture while remaining bounded.

## AST node kind enum

Add:

```text
typedef enum {
    LATTICRA_L_UI_AST_NODE_CARD = 0,
    LATTICRA_L_UI_AST_NODE_RAIL = 1,
    LATTICRA_L_UI_AST_NODE_FIELD = 2,
    LATTICRA_L_UI_AST_NODE_TEXT = 3,
    LATTICRA_L_UI_AST_NODE_BINDING = 4,
    LATTICRA_L_UI_AST_NODE_UNKNOWN = 5
} latticra_l_ui_ast_node_kind_t;
```

Reserved future node kinds such as `layout`, `theme`, `action`, and `condition` must remain unimplemented until future contracts exist.

## Card struct

Add a card summary struct:

```text
typedef struct {
    char name[LATTICRA_L_UI_AST_LABEL_MAX];
    char purpose[LATTICRA_L_UI_AST_PURPOSE_MAX];
    char effect[LATTICRA_L_UI_LABEL_MAX];
    char boundary[LATTICRA_L_UI_LABEL_MAX];
    latticra_l_ui_source_span_t span;
    size_t rail_count;
    size_t field_count;
    size_t text_count;
} latticra_l_ui_ast_card_t;
```

## Rail struct

Add:

```text
typedef struct {
    char name[LATTICRA_L_UI_AST_LABEL_MAX];
    latticra_l_ui_source_span_t span;
    size_t first_field_index;
    size_t field_count;
    size_t first_text_index;
    size_t text_count;
} latticra_l_ui_ast_rail_t;
```

## Field struct

Add:

```text
typedef struct {
    char name[LATTICRA_L_UI_AST_LABEL_MAX];
    char binding[LATTICRA_L_UI_AST_BINDING_MAX];
    latticra_l_ui_source_span_t span;
    latticra_l_ui_source_span_t binding_span;
} latticra_l_ui_ast_field_t;
```

## Text struct

Add:

```text
typedef struct {
    char value[LATTICRA_L_UI_AST_PURPOSE_MAX];
    latticra_l_ui_source_span_t span;
} latticra_l_ui_ast_text_t;
```

## AST result struct

Add:

```text
typedef struct {
    latticra_l_ui_parse_result_t parse_result;
    latticra_l_ui_ast_card_t card;
    latticra_l_ui_ast_rail_t rails[LATTICRA_L_UI_AST_RAIL_MAX];
    latticra_l_ui_ast_field_t fields[LATTICRA_L_UI_AST_FIELD_MAX];
    latticra_l_ui_ast_text_t texts[LATTICRA_L_UI_AST_TEXT_MAX];
    size_t rail_count;
    size_t field_count;
    size_t text_count;
    int no_effect;
    int execution_allowed;
    int mutation_allowed;
    int server_allowed;
    int recovery_allowed;
    int hardware_allowed;
} latticra_l_ui_ast_result_t;
```

## Public API plan

Add:

```text
const char *latticra_l_ui_ast_node_kind_label(
    latticra_l_ui_ast_node_kind_t kind);

latticra_status_t latticra_l_ui_parse_ast(
    const char *source,
    size_t source_len,
    latticra_l_ui_ast_result_t *ast);

latticra_status_t latticra_l_ui_ast_report(
    const latticra_l_ui_ast_result_t *ast,
    char *buffer,
    size_t buffer_len);
```

The AST parser should accept in-memory source only. It must not perform file I/O.

## Module shape

Add or update:

```text
include/latticra/l_ui_parser.h
src/l_ui_parser_ast.c
tests/l_ui_parser_ast_invariants.c
scripts/test-l-ui-parser-ast.sh
.github/workflows/c.yml
```

A separate `src/l_ui_parser_ast.c` keeps AST construction distinct from the validator implementation.

## Ownership and lifetime rules

The first AST must:

- use fixed-size storage;
- copy labels, purpose text, text values, binding paths, and spans;
- not store borrowed pointers into source;
- not require heap allocation;
- not expose mutable internal references;
- treat all AST nodes as metadata only.

## Source-span integration

Every populated node should carry a span when possible.

Rules:

1. Card span covers the full `card NucleusPreview { ... }` block.
2. Rail span covers the rail block.
3. Field span covers the field declaration.
4. Binding span covers only the binding path.
5. Text span covers the quoted literal text.
6. Missing constructs do not produce AST nodes.

The first implementation may use simple deterministic scanning against the first fixture, but must remain bounded and no-effect.

## Successful parse rule

AST construction should depend on successful validation by `latticra_l_ui_parse_source`.

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

No partial AST should be emitted in the first implementation.

## First accepted fixture summary

For:

```text
examples/l-ui/nucleus-preview-card.lui
```

expected AST summary:

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

## AST report shape

The first AST report should render:

```text
L-UI AST SUMMARY
card=NucleusPreview
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

Detailed node reports should be deferred until a later report contract.

## Compatibility expectations

Existing parser, diagnostics, location, and source-span tests must continue to pass.

Existing parser API signatures must not be changed.

New AST structs are additive public API.

Existing parser result and diagnostic report shapes must not be modified by the AST implementation.

## Exact implementation test list

The AST implementation PR should include tests for:

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

## Required rails

The AST must include rails for:

```text
top
state
trace
safety
gates
effects
policy
execution
bottom
```

## Required field names

The first AST implementation should include fields for:

```text
origin
route
axis
path
breadcrumb
trace
health
risk
lock
dark_phase
safe_portal
rollback
host
external
requested
request
policy
reason
executed
mutation
server
recovery
hardware
```

## Required text values

The first AST implementation should include text values for:

```text
Latticra / Nucleus Preview / effect-bound
preview-only no-live-movement no-host-effect no-external-effect
```

## Forbidden implementation behavior

The AST implementation must not:

- add file I/O to parser code;
- write files;
- open network connections;
- call server code;
- call update code;
- call recovery code;
- call hardware code;
- mutate state lattice;
- perform live movement;
- run L-UI behavior;
- render an interactive UI;
- accept unsupported effects;
- treat text nodes as commands;
- treat bindings as executable references.

## Documentation requirement

The implementation PR should update:

```text
README.md
docs/FOUNDATION_INDEX.md
docs/L_UI_PARSER_AST_CONTRACT.md
```

and add:

```text
docs/L_UI_PARSER_AST_IMPLEMENTATION.md
```

## Current validation command

This plan is guarded by:

```sh
sh scripts/test-l-ui-parser-ast-implementation-plan.sh
```

The guard is static. It does not implement an AST.

## Implementation gate

AST implementation code may be added only after this plan is merged.

## Non-claims

This document does not implement AST construction, AST traversal, L-UI rendering, command behavior, Nucleus task handling, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.
