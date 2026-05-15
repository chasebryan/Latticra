# Latticra L-UI Parser Source-Span Contract

Status: source-span contract
Scope: source ranges, span rules, byte offsets, line/column ranges, and no-effect boundaries before AST or renderer integration.

## Purpose

This document defines the source-span contract for the L-UI parser.

The parser reports precise one-based line and column locations for selected errors. Source spans describe a range in the in-memory source buffer, not only a single point.

This document does not implement source spans. The implementation is documented separately in [`L_UI_PARSER_SOURCE_SPAN_IMPLEMENTATION.md`](L_UI_PARSER_SOURCE_SPAN_IMPLEMENTATION.md).

## Current boundary

The current parser provides:

```text
error category
line
column
source span metadata
no-effect flags
diagnostic mapping
diagnostic reports
```

This contract does not add:

```text
AST construction
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

## Span purpose

A source span identifies the source range responsible for a parser result or diagnostic.

Source spans can support:

- clearer diagnostics;
- underline-style terminal reports;
- future AST node ranges;
- fixture validation summaries;
- future L-UI tooling.

They must remain no-effect metadata.

## Source unit rules

Spans must use byte offsets over the in-memory source buffer.

Rules:

1. `start_offset` is zero-based.
2. `end_offset` is zero-based and exclusive.
3. `start_offset <= end_offset`.
4. Both offsets must be within the provided source length.
5. Line and column are one-based.
6. Columns are byte-based, not display-cell-based.
7. Spans must not depend on host text mode.

## Line and column range rules

A span includes:

```text
start_line
start_column
end_line
end_column
```

Rules:

1. Start line and column identify the first byte in the span.
2. End line and column identify the location immediately after the final byte in the span.
3. Empty spans are allowed only for missing constructs or successful/default results.
4. Empty spans should set start and end to the same location.
5. Multiline spans are allowed.

## Newline policy

The source-span scanner must preserve the current newline policy:

```text
LF   -> newline
CRLF -> one newline
CR   -> newline
```

Column reset behavior:

```text
line += 1
column = 1
```

for each logical newline.

## Span struct

The public span struct is:

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

The parser result includes:

```text
latticra_l_ui_source_span_t span;
```

## Diagnostic integration

Diagnostics include the same span shape:

```text
latticra_l_ui_source_span_t span;
```

Diagnostic reports render:

```text
span_start_offset=<n>
span_end_offset=<n>
span_start_line=<n>
span_start_column=<n>
span_end_line=<n>
span_end_column=<n>
```

## Initial span targets

The first span implementation covers:

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

## Span target behavior

| Parser result | Span |
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

## Empty span rule

Missing constructs use empty spans.

Example:

```text
start_offset=end_offset=<card-body-start-offset>
start_line=end_line=<card-body-start-line>
start_column=end_column=<card-body-start-column>
```

This keeps missing data precise without inventing source ranges.

## No-effect rule

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

## Implementation gate

Source-span implementation required a separate implementation plan defining:

1. public API changes;
2. struct placement;
3. parse result integration;
4. diagnostic integration;
5. report format changes;
6. test file names;
7. exact invariant tests;
8. compatibility expectations.

That plan is recorded in [`L_UI_PARSER_SOURCE_SPAN_IMPLEMENTATION_PLAN.md`](L_UI_PARSER_SOURCE_SPAN_IMPLEMENTATION_PLAN.md).

## Test list

Source-span implementation tests verify:

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
```

## Forbidden behavior

A source-span implementation must not:

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

This contract is guarded by:

```sh
sh scripts/test-l-ui-parser-source-span-contract.sh
```

The guard is static. It does not implement source spans.

## Non-claims

This document does not implement AST construction, L-UI rendering, command behavior, Nucleus task handling, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.
