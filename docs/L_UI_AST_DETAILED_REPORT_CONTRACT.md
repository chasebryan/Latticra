# Latticra L-UI AST Detailed Report Contract

Status: detailed report contract
Scope: deterministic rail, field, text, source-span, and no-effect reporting for the fixed-size L-UI AST.

## Purpose

This document defines the detailed report contract for the L-UI AST.

The AST implementation exposes a compact summary report and a detailed metadata report. The detailed report makes card, rail, field, text, and source-span metadata visible without adding rendering, traversal runtime, command behavior, live movement, mutation, or external effects.

The implementation is documented separately in [`L_UI_AST_DETAILED_REPORT_IMPLEMENTATION.md`](L_UI_AST_DETAILED_REPORT_IMPLEMENTATION.md).

## Current boundary

The current AST implementation provides:

```text
fixed-size AST metadata
card summary
rail metadata
field metadata
text metadata
source spans
compact AST summary report
detailed AST metadata report
no-effect flags
```

This contract does not add:

```text
interactive UI behavior
renderer integration
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

## Detailed report purpose

A detailed AST report provides deterministic, inspectable text for validated L-UI metadata.

It supports:

- reviewing the parsed card;
- inspecting rail order and counts;
- inspecting field names and bindings;
- inspecting text nodes;
- inspecting source spans for populated nodes;
- debugging fixture changes;
- future tooling that consumes stable text output.

It remains metadata-only.

## Report function

Implemented public function:

```text
latticra_l_ui_ast_detailed_report
```

Signature:

```text
latticra_status_t latticra_l_ui_ast_detailed_report(
    const latticra_l_ui_ast_result_t *ast,
    char *buffer,
    size_t buffer_len);
```

This is additive and does not change the existing compact AST report.

## Report capacity

The bounded capacity is:

```text
LATTICRA_L_UI_AST_DETAILED_REPORT_MAX = 16384
```

The detailed report is larger than the compact AST report because it renders all populated rails, fields, text nodes, source spans, and binding spans.

## Top-level report shape

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

## Span field format

Every node section that includes a span renders:

```text
span_start_offset=<n>
span_end_offset=<n>
span_start_line=<n>
span_start_column=<n>
span_end_line=<n>
span_end_column=<n>
```

The span field names match existing parser and diagnostic report span fields.

## Card section

The card section renders:

```text
[card]
kind=card
name=NucleusPreview
purpose=operator-visible Nucleus preview report
effect=none
boundary=preview_only
rail_count=9
field_count=23
text_count=2
span_start_offset=<n>
span_end_offset=<n>
span_start_line=<n>
span_start_column=<n>
span_end_line=<n>
span_end_column=<n>
```

## Rail section

Each rail renders in AST order:

```text
[rail <index>]
kind=rail
name=<rail-name>
first_field_index=<n>
field_count=<n>
first_text_index=<n>
text_count=<n>
span_start_offset=<n>
span_end_offset=<n>
span_start_line=<n>
span_start_column=<n>
span_end_line=<n>
span_end_column=<n>
```

Required rail order:

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

## Field section

Each field renders in AST order:

```text
[field <index>]
kind=field
name=<field-name>
binding=<binding-path>
span_start_offset=<n>
span_end_offset=<n>
span_start_line=<n>
span_start_column=<n>
span_end_line=<n>
span_end_column=<n>
binding_span_start_offset=<n>
binding_span_end_offset=<n>
binding_span_start_line=<n>
binding_span_start_column=<n>
binding_span_end_line=<n>
binding_span_end_column=<n>
```

Field sections must not treat bindings as executable references.

## Text section

Each text node renders in AST order:

```text
[text <index>]
kind=text
value=<literal-text>
span_start_offset=<n>
span_end_offset=<n>
span_start_line=<n>
span_start_column=<n>
span_end_line=<n>
span_end_column=<n>
```

Text sections must not treat text values as commands.

## Determinism rules

Detailed AST reports must be deterministic.

Rules:

1. Report sections must appear in a fixed order.
2. Rails must appear in AST rail order.
3. Fields must appear in AST field order.
4. Text nodes must appear in AST text order.
5. Missing/unpopulated capacity slots must not be printed.
6. Repeated calls with the same AST must produce identical text.
7. Output must not include memory addresses.
8. Output must not depend on platform locale.

## Escaping policy

The first detailed report emits current fixture text literally because the fixture text is controlled.

Before accepting broader L-UI text values, a future escaping contract should define how to render newlines, tabs, quotes, and non-printable bytes.

## Failed parse behavior

If AST construction failed due to a parser error, detailed reporting returns a compact failed-parse report:

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

No partial AST nodes are printed for failed parses.

## No-effect rule

Detailed reporting is metadata output only.

It preserves:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

## Compatibility rule

The detailed report is additive.

It does not change:

```text
latticra_l_ui_ast_report
latticra_l_ui_parse_ast
latticra_l_ui_parse_source
latticra_l_ui_parse_result_report
latticra_l_ui_diagnostic_report
```

## Implementation gate

Detailed AST report implementation required a separate implementation plan defining:

1. public API addition;
2. report capacity;
3. exact section order;
4. failed-parse behavior;
5. escaping policy for current fixture;
6. test file names;
7. exact invariant tests;
8. compatibility expectations.

That plan is recorded in [`L_UI_AST_DETAILED_REPORT_IMPLEMENTATION_PLAN.md`](L_UI_AST_DETAILED_REPORT_IMPLEMENTATION_PLAN.md).

## Test list

Detailed report implementation tests verify:

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

## Forbidden behavior

A detailed report implementation must not:

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
- treat text nodes as commands;
- treat bindings as executable references;
- emit memory addresses.

## Current validation command

This contract is guarded by:

```sh
sh scripts/test-l-ui-ast-detailed-report-contract.sh
```

The guard is static. It validates the contract text.

## Non-claims

This document does not implement L-UI rendering, command behavior, Nucleus task handling, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.
