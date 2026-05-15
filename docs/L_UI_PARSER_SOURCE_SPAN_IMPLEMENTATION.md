# Latticra L-UI Parser Source-Span Implementation

Status: initial implementation contract
Scope: public source-span metadata, parse-result spans, diagnostic spans, report extensions, and invariant tests.

## Purpose

The L-UI Parser Source-Span implementation adds source-range metadata to parser results and diagnostics.

Source spans describe ranges in the in-memory source buffer. They are metadata only. They do not add AST construction, L-UI rendering, command behavior, Nucleus task handling, live movement, state mutation, server interaction, recovery behavior, self-update behavior, hardware behavior, or boot behavior.

## Implementation files

```text
include/latticra/l_ui_parser.h
src/l_ui_parser.c
src/l_ui_parser_diagnostics.c
tests/l_ui_parser_source_span_invariants.c
scripts/test-l-ui-parser-source-span.sh
```

## Public source-span struct

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

## Parse-result integration

The parser result includes:

```text
latticra_l_ui_source_span_t span;
```

## Diagnostic integration

The diagnostic result includes:

```text
latticra_l_ui_source_span_t span;
```

Diagnostics copy span metadata from parse results.

## Report extensions

Parser result reports and diagnostic reports append:

```text
span_start_offset=<n>
span_end_offset=<n>
span_start_line=<n>
span_start_column=<n>
span_end_line=<n>
span_end_column=<n>
```

The extension is append-only. Existing fields remain present and stable.

## Span rules

```text
start_offset is zero-based
end_offset is zero-based and exclusive
start_offset <= end_offset
line and column are one-based
columns are byte-based
```

## Implemented span targets

Initial source spans cover:

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

## Empty span behavior

Missing constructs use empty spans at the card-body start when available:

```text
start_offset=end_offset
start_line=end_line
start_column=end_column
```

## Default success span

Successful parses use the default empty span:

```text
start_offset=0
end_offset=0
start_line=1
start_column=1
end_line=1
end_column=1
```

## No-effect boundary

Source-span metadata must preserve:

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
sh scripts/test-l-ui-parser-source-span.sh
```

The main C workflow runs this check after the source-span implementation-plan guard.

## Required invariants

The source-span tests verify:

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

## Current evidence level

This implementation is an L2 tested source-span metadata model for the L-UI parser.

It is not an AST system, renderer, UI runtime, command surface, Nucleus task runner, server client, update engine, recovery system, hardware system, boot system, or security boundary.

## Next implementation step

The next implementation candidate after source spans is:

```text
L-UI parser AST contract
```

That future work should define AST shape, node ownership, source-span usage, and no-effect boundaries before any AST implementation.

## Non-claims

This document and implementation do not claim AST construction, L-UI rendering, command behavior, Nucleus task handling, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.
