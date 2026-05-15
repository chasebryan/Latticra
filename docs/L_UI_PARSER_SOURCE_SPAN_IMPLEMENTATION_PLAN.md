# Latticra L-UI Parser Source-Span Implementation Plan

Status: implementation planning contract
Scope: public API changes, struct placement, parse-result integration, diagnostics integration, report format changes, exact tests, and compatibility expectations before source-span implementation.

## Purpose

This document defines the implementation plan for L-UI parser source spans.

The source-span contract is already merged and guarded. This plan decides the exact C API, struct placement, parse result integration, diagnostic integration, report format changes, tests, and compatibility expectations before span code is added.

## Relationship to previous contracts

This plan depends on:

```text
docs/L_UI_PARSER_SOURCE_SPAN_CONTRACT.md
docs/L_UI_PARSER_LINE_COLUMN_PRECISION_IMPLEMENTATION.md
docs/L_UI_PARSER_DIAGNOSTICS_IMPLEMENTATION.md
include/latticra/l_ui_parser.h
src/l_ui_parser.c
src/l_ui_parser_diagnostics.c
```

Those files remain the source of truth for parser errors, precise point locations, diagnostics, and no-effect behavior.

## Implementation language decision

The source-span implementation should be in C.

Reason:

- the parser is implemented in C;
- parse results and diagnostics are C ABI surfaces;
- spans should be fixed-size metadata with no allocation requirements;
- span calculations can reuse existing private source-location scanning behavior;
- the current C workflow can validate spans.

## Public API change

Unlike line/column precision, source spans require a public API extension.

Add a public span struct in:

```text
include/latticra/l_ui_parser.h
```

Proposed public struct:

```text
typedef struct {
    size_t start_offset;
    size_t end_offset;
    size_t start_line;
    size_t start_column;
    size_t end_line;
    size_t end_column;
} latticra_l_ui_source_span_t;
```

## Parse result integration

Add span to:

```text
latticra_l_ui_parse_result_t
```

Proposed field:

```text
latticra_l_ui_source_span_t span;
```

## Diagnostic integration

Add span to:

```text
latticra_l_ui_diagnostic_t
```

Proposed field:

```text
latticra_l_ui_source_span_t span;
```

Diagnostics should copy span metadata from parse results.

## Report format changes

The parser result report should add:

```text
span_start_offset=<n>
span_end_offset=<n>
span_start_line=<n>
span_start_column=<n>
span_end_line=<n>
span_end_column=<n>
```

The diagnostic report should add the same fields:

```text
span_start_offset=<n>
span_end_offset=<n>
span_start_line=<n>
span_start_column=<n>
span_end_line=<n>
span_end_column=<n>
```

These additions are append-only to preserve existing report fields.

## Compatibility expectations

Existing consumers of parse results must continue to compile after adding the span field, assuming they do not rely on exact struct size.

Existing report tests must be updated to accept the new appended fields.

Existing behavior must remain stable:

```text
error labels unchanged
diagnostic codes unchanged
diagnostic messages unchanged
diagnostic hints unchanged
line and column fields unchanged
no-effect flags unchanged
```

## Internal helper plan

Extend private parser helpers in `src/l_ui_parser.c`.

Planned helper shapes:

```text
static void span_default(latticra_l_ui_source_span_t *span);

static void span_for_range(
    const char *source,
    size_t source_len,
    size_t start_offset,
    size_t end_offset,
    latticra_l_ui_source_span_t *span);

static int find_slice_span(
    const char *source,
    size_t source_len,
    const char *needle,
    latticra_l_ui_source_span_t *span);

static int find_unterminated_string_span(
    const char *source,
    size_t source_len,
    latticra_l_ui_source_span_t *span);

static int find_unbalanced_brace_span(
    const char *source,
    size_t source_len,
    latticra_l_ui_source_span_t *span);

static void set_error_with_span(
    latticra_l_ui_parse_result_t *result,
    latticra_l_ui_parse_error_t error,
    const latticra_l_ui_source_span_t *span);
```

These helpers should remain private.

## Span defaults

Default span for success and conservative errors:

```text
start_offset=0
end_offset=0
start_line=1
start_column=1
end_line=1
end_column=1
```

## Span calculation rules

For token spans:

```text
start_offset = first byte of token
end_offset = first byte after token
start_line/start_column = location of start_offset
end_line/end_column = location of end_offset
```

For missing constructs:

```text
start_offset = card body start offset
end_offset = card body start offset
start_line = card body start line
start_column = card body start column
end_line = start_line
end_column = start_column
```

## Initial span targets

The first implementation should add spans for:

```text
unsupported_version
unsupported_effect
unsupported_boundary
unknown_binding_prefix
forbidden_behavior_marker
unterminated_string
unbalanced_brace
missing_effect
missing_boundary
missing_rail
```

## Span mapping plan

| Parser result | Planned span |
| --- | --- |
| `unsupported_version` | unsupported version token or `lui` token |
| `unsupported_effect` | unsupported `effect ...` clause token range |
| `unsupported_boundary` | unsupported `boundary ...` clause token range |
| `unknown_binding_prefix` | unsupported binding target prefix range |
| `forbidden_behavior_marker` | forbidden marker token range |
| `unterminated_string` | opening quote through end of source |
| `unbalanced_brace` | unmatched brace byte |
| `missing_effect` | empty span at card body start |
| `missing_boundary` | empty span at card body start |
| `missing_rail` | empty span at card body start |

## No-effect preservation

Source spans are metadata only.

They must not change:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

## Exact implementation test list

The source-span implementation PR should include tests for:

```text
unsupported_effect_reports_effect_span
unsupported_boundary_reports_boundary_span
unknown_binding_prefix_reports_binding_span
forbidden_marker_reports_marker_span
unterminated_string_reports_string_span
unbalanced_open_brace_reports_brace_span
unbalanced_close_brace_reports_brace_span
missing_effect_reports_empty_card_body_span
missing_boundary_reports_empty_card_body_span
missing_rail_reports_empty_card_body_span
span_offsets_are_zero_based
span_end_offset_is_exclusive
span_line_columns_are_one_based
span_columns_are_byte_based
span_scanner_handles_lf_newlines
span_scanner_handles_crlf_newlines
span_scanner_handles_cr_newlines
span_metadata_preserves_no_effect_flags
span_reports_are_deterministic
parse_result_report_includes_span_fields
diagnostic_report_includes_span_fields
diagnostic_copies_parse_result_span
success_span_uses_default_empty_span
```

## Test file plan

Add:

```text
tests/l_ui_parser_source_span_invariants.c
scripts/test-l-ui-parser-source-span.sh
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
docs/L_UI_PARSER.md
docs/L_UI_PARSER_DIAGNOSTICS_IMPLEMENTATION.md
docs/L_UI_PARSER_SOURCE_SPAN_CONTRACT.md
```

and add:

```text
docs/L_UI_PARSER_SOURCE_SPAN_IMPLEMENTATION.md
```

## Forbidden implementation behavior

The source-span implementation must not:

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
- accept unsupported effects.

## Current validation command

This plan is guarded by:

```sh
sh scripts/test-l-ui-parser-source-span-implementation-plan.sh
```

The guard is static. It does not implement source spans.

## Implementation gate

Source-span implementation code may be added only after this plan is merged.

## Non-claims

This document does not implement source spans, AST construction, L-UI rendering, command behavior, Nucleus task handling, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.
