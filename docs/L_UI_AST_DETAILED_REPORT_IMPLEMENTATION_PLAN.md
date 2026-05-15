# Latticra L-UI AST Detailed Report Implementation Plan

Status: implementation planning contract
Scope: public API addition, report capacity, exact section order, failed-parse behavior, escaping policy, exact tests, and compatibility expectations before detailed AST report code.

## Purpose

This document defines the implementation plan for the L-UI AST detailed report.

The detailed report contract is already merged and guarded. This plan decides the exact public API addition, capacity, report section order, failed-parse behavior, escaping policy, exact tests, and compatibility expectations before implementation code is added.

## Relationship to previous contracts

This plan depends on:

```text
docs/L_UI_AST_DETAILED_REPORT_CONTRACT.md
docs/L_UI_PARSER_AST_IMPLEMENTATION.md
include/latticra/l_ui_parser.h
src/l_ui_parser_ast.c
```

Those files remain the source of truth for AST metadata, compact AST reporting, source spans, and no-effect boundaries.

## Implementation language decision

The detailed AST report implementation should be in C.

Reason:

- the AST implementation is in C;
- AST report APIs are C ABI surfaces;
- report generation should remain bounded and deterministic;
- the current C workflow can validate report invariants;
- no dynamic runtime should be required.

## Public API addition

Add to:

```text
include/latticra/l_ui_parser.h
```

```text
#define LATTICRA_L_UI_AST_DETAILED_REPORT_MAX 8192u

latticra_status_t latticra_l_ui_ast_detailed_report(
    const latticra_l_ui_ast_result_t *ast,
    char *buffer,
    size_t buffer_len);
```

This must be additive. Existing AST, parser, diagnostics, location, and source-span APIs must remain unchanged.

## Module shape

Update:

```text
include/latticra/l_ui_parser.h
src/l_ui_parser_ast.c
tests/l_ui_parser_ast_detailed_report_invariants.c
scripts/test-l-ui-ast-detailed-report.sh
.github/workflows/c.yml
```

Detailed report generation should live in `src/l_ui_parser_ast.c` with the compact AST report.

## Report capacity

Use:

```text
LATTICRA_L_UI_AST_DETAILED_REPORT_MAX = 8192
```

The report function must return `LATTICRA_STATUS_BUFFER_TOO_SMALL` when the provided buffer cannot hold the full deterministic report.

## Failed-parse behavior

The first implementation should render a compact failed-parse detailed report instead of rejecting report generation.

Shape:

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

This keeps report generation deterministic for failed parses while not emitting partial AST nodes.

## Escaping policy

The first implementation may render current fixture text literally.

Allowed literal values:

```text
Latticra / Nucleus Preview / effect-bound
preview-only no-live-movement no-host-effect no-external-effect
operator-visible Nucleus preview report
```

The implementation must not introduce a broader escaping model yet. A future escaping contract should define broader string rendering.

## Exact section order

A successful detailed report must render sections in this order:

```text
1. top-level summary
2. card section
3. rail sections in AST order
4. field sections in AST order
5. text sections in AST order
```

No unused capacity slots may be printed.

## Top-level summary format

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

## Card section format

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

## Rail section format

For each populated rail:

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

Required order:

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

## Field section format

For each populated field:

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

## Text section format

For each populated text node:

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

## Helper plan

The implementation may add private helpers in `src/l_ui_parser_ast.c`:

```text
append_text
append_span_fields
append_card_section
append_rail_section
append_field_section
append_text_section
append_failed_parse_report
```

Helpers should remain private and bounded.

## Compatibility expectations

The detailed report implementation must not change:

```text
latticra_l_ui_ast_report
latticra_l_ui_parse_ast
latticra_l_ui_parse_source
latticra_l_ui_parse_result_report
latticra_l_ui_diagnostic_report
```

Existing parser, diagnostic, source-span, location, and compact AST tests must continue to pass.

## No-effect preservation

Detailed reporting must preserve:

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

## Test file plan

Add:

```text
tests/l_ui_parser_ast_detailed_report_invariants.c
scripts/test-l-ui-ast-detailed-report.sh
```

Wire into:

```text
.github/workflows/c.yml
```

## Documentation requirement

The implementation PR should update:

```text
README.md
docs/FOUNDATION_INDEX.md
docs/L_UI_AST_DETAILED_REPORT_CONTRACT.md
docs/L_UI_PARSER_AST_IMPLEMENTATION.md
```

and add:

```text
docs/L_UI_AST_DETAILED_REPORT_IMPLEMENTATION.md
```

## Forbidden implementation behavior

The detailed report implementation must not:

- add file I/O to parser or AST code;
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

This plan is guarded by:

```sh
sh scripts/test-l-ui-ast-detailed-report-implementation-plan.sh
```

The guard is static. It does not implement detailed AST reporting.

## Implementation gate

Detailed AST report implementation code may be added only after this plan is merged.

## Non-claims

This document does not implement detailed AST reporting, L-UI rendering, command behavior, Nucleus task handling, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.
