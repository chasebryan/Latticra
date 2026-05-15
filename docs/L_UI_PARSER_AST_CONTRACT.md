# Latticra L-UI Parser AST Contract

Status: AST contract
Scope: future AST shape, node ownership, source-span usage, capacity rules, diagnostics relationship, and no-effect boundaries before AST implementation.

## Purpose

This document defines the initial AST contract for the L-UI parser.

The parser currently validates source, produces parse summaries, emits precise point locations, and records source-span metadata. The next architectural step is an AST contract that defines how source may later become a structured tree without adding rendering, command behavior, live movement, or mutation.

This document does not implement an AST.

## Current boundary

The current parser provides:

```text
parse status
parse error category
point line and column
source span metadata
diagnostic mapping
diagnostic reports
no-effect flags
```

This contract does not add:

```text
AST construction
AST allocation
AST traversal
renderer integration
interactive UI behavior
command behavior
Nucleus task handling
live movement
state mutation
server interaction
update behavior
recovery behavior
hardware behavior
boot behavior
```

## AST purpose

A future AST should represent validated `.lui` source as structured, inspectable metadata.

A future AST may support:

- stable card summaries;
- rail and field enumeration;
- source-span-aware diagnostics;
- fixture validation reports;
- later renderer contracts;
- later tooling that can inspect L-UI source without executing it.

The AST must remain metadata-only until a separate renderer or execution contract exists.

## No-effect rule

AST construction must preserve:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

AST code must not run L-UI behavior.

## Ownership rule

The first AST implementation should use caller-provided storage or fixed-size result storage.

It must not require unbounded heap allocation.

It must not retain borrowed pointers into a source buffer unless a later lifetime contract explicitly permits it.

The first AST should prefer copied labels and spans:

```text
card_name
purpose
boundary
effect
rail names
field names
binding paths
source spans
```

## Public API rule

AST implementation will require a public API extension.

A future implementation plan must define:

```text
AST struct names
capacity constants
parse function shape
report function shape
error behavior
compatibility expectations
```

No AST API should be added until an implementation plan is merged.

## Proposed capacity constants

Initial proposed constants:

```text
LATTICRA_L_UI_AST_RAIL_MAX = 16
LATTICRA_L_UI_AST_FIELD_MAX = 64
LATTICRA_L_UI_AST_TEXT_MAX = 16
LATTICRA_L_UI_AST_LABEL_MAX = 64
LATTICRA_L_UI_AST_BINDING_MAX = 96
LATTICRA_L_UI_AST_PURPOSE_MAX = 128
LATTICRA_L_UI_AST_REPORT_MAX = 2048
```

These values should be reviewed in the implementation plan.

## Proposed node kinds

Initial AST node kinds:

```text
card
rail
field
text
binding
```

Reserved future node kinds:

```text
layout
theme
action
condition
```

Reserved node kinds must not become executable without a future contract.

## Card node

The first card node should include:

```text
name
purpose
effect
boundary
span
rail_count
field_count
text_count
```

The first accepted card remains:

```text
NucleusPreview
```

## Rail node

A rail node should include:

```text
name
span
first_field_index
field_count
first_text_index
text_count
```

Initial required rails:

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

## Field node

A field node should include:

```text
name
binding
span
binding_span
```

Allowed binding prefixes remain:

```text
state.
preview.
```

## Text node

A text node should include:

```text
value
span
```

Text nodes are literal metadata only. They must not be interpreted as commands.

## Source-span usage

Every AST node should carry source-span metadata when available.

Rules:

1. Card span covers the full card declaration.
2. Rail span covers the rail block.
3. Field span covers the field declaration.
4. Binding span covers the binding path only.
5. Text span covers the quoted text value or full text declaration, as defined by the implementation plan.
6. Missing constructs should not produce AST nodes.

## AST result shape

A future AST parse result may include:

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

The exact shape must be finalized in an implementation plan.

## AST report shape

A future AST report may render deterministic text such as:

```text
L-UI AST SUMMARY
card=NucleusPreview
rail_count=<n>
field_count=<n>
text_count=<n>
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

Detailed rail and field reporting should be planned separately if needed.

## Initial accepted fixture

The first AST target should be:

```text
examples/l-ui/nucleus-preview-card.lui
```

The expected summary should include:

```text
card=NucleusPreview
rail_count=9
field_count=23
text_count=2
effect=none
boundary=preview_only
```

## Diagnostics relationship

AST construction should depend on a successful parse.

If parsing fails, AST construction should return the parser error and must not emit partial executable structures.

A later contract may define partial AST behavior for diagnostics, but the first AST should avoid partial AST output.

## Forbidden behavior

A future AST implementation must not:

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

## Implementation gate

AST implementation must not begin until a separate implementation plan defines:

1. public API changes;
2. AST struct placement;
3. capacity constants;
4. ownership and lifetime rules;
5. source-span integration;
6. successful parse requirements;
7. report format;
8. test file names;
9. exact invariant tests;
10. compatibility expectations.

## Future test list

A future implementation plan should include tests for:

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
```

## Current validation command

This contract is guarded by:

```sh
sh scripts/test-l-ui-parser-ast-contract.sh
```

The guard is static. It does not implement an AST.

## Non-claims

This document does not implement AST construction, AST traversal, L-UI rendering, command behavior, Nucleus task handling, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.
