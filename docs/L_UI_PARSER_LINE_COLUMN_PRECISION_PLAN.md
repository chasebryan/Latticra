# Latticra L-UI Parser Line/Column Precision Plan

Status: precision planning contract
Scope: one-based location rules, source scanning policy, future parser changes, exact tests, and no-effect boundaries before precise diagnostics implementation.

## Purpose

This document plans richer line and column reporting for the L-UI parser.

The current parser uses conservative location defaults:

```text
line=1
column=1
```

That is acceptable for the first no-effect parser. The next step is to define how precise locations should work before changing parser logic.

## Current boundary

This plan does not implement precise location tracking.

This plan does not change parser behavior.

This plan does not add an L-UI renderer, interactive UI, command behavior, Nucleus task handling, live movement, state mutation, server interaction, update behavior, recovery behavior, hardware behavior, or boot behavior.

## Precision goal

Future parser diagnostics should report the beginning of the rejected token or clause when possible.

Examples:

```text
unsupported version      -> location of version header
missing card             -> line=1 column=1 if no card token exists
missing effect           -> location of card body start when available
unsupported effect       -> location of effect token
unsupported boundary     -> location of boundary token
missing rail             -> location of card body start when available
unknown binding prefix   -> location of bind target
unterminated string      -> location of opening quote
unbalanced brace         -> location of unmatched brace when available
forbidden marker         -> location of forbidden marker
```

## Location units

Line and column must be one-based.

```text
first line = 1
first column = 1
```

Columns count bytes in the in-memory source buffer, not terminal display cells, Unicode grapheme clusters, or rendered visual columns.

This keeps the parser portable, deterministic, and independent of terminal behavior.

## Newline policy

Recognized newline forms:

```text
\n
\r\n
\r
```

Rules:

1. `\n` increments line and resets column to 1.
2. `\r\n` counts as one newline and resets column to 1.
3. Lone `\r` counts as one newline and resets column to 1.
4. Other bytes increment column by 1.
5. Location scanning must not depend on host platform text mode.

## Source scanning helper plan

A future implementation should add internal helpers similar to:

```text
find_slice_location(source, source_len, needle, *line, *column)
find_unbalanced_brace_location(source, source_len, *line, *column)
find_unterminated_string_location(source, source_len, *line, *column)
```

These helpers should be internal to the parser implementation unless a later contract approves a public API.

## Parse result behavior

Future parser code should set:

```text
result.line
result.column
```

for the first relevant error location.

Success results may continue to use:

```text
line=1
column=1
```

unless a future AST or source-span contract requires richer success metadata.

## Error location plan

| Parser error | Planned location |
| --- | --- |
| `ok` | `line=1`, `column=1` |
| `null_argument` | `line=1`, `column=1` |
| `empty_source` | `line=1`, `column=1` |
| `unsupported_version` | first byte of source or found unsupported `lui` token |
| `missing_card` | `line=1`, `column=1` unless card-like token found |
| `missing_purpose` | first byte of `card NucleusPreview` body when available |
| `missing_effect` | first byte of `card NucleusPreview` body when available |
| `unsupported_effect` | first byte of `effect` token |
| `missing_boundary` | first byte of `card NucleusPreview` body when available |
| `unsupported_boundary` | first byte of `boundary` token |
| `missing_rail` | first byte of `card NucleusPreview` body when available |
| `unknown_rail` | first byte of unsupported rail token |
| `unknown_binding_prefix` | first byte of unsupported binding target |
| `missing_required_binding` | first byte of relevant rail when available |
| `unterminated_string` | opening quote of the unterminated string |
| `unbalanced_brace` | unmatched opening or closing brace when available |
| `forbidden_behavior_marker` | first byte of forbidden marker |
| `source_too_large` | `line=1`, `column=1` |
| `internal_error` | `line=1`, `column=1` |

## No-effect rule

Line and column precision is diagnostic metadata only.

It must not change:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

## Exact future test list

The future precision implementation PR should include tests for:

```text
unsupported_version_reports_precise_location
unsupported_effect_reports_effect_token_location
unsupported_boundary_reports_boundary_token_location
unknown_binding_prefix_reports_binding_target_location
forbidden_marker_reports_marker_location
unterminated_string_reports_opening_quote_location
unbalanced_open_brace_reports_opening_brace_location
unbalanced_close_brace_reports_closing_brace_location
missing_effect_reports_card_body_location
missing_boundary_reports_card_body_location
missing_rail_reports_card_body_location
location_scanner_handles_lf_newlines
location_scanner_handles_crlf_newlines
location_scanner_handles_cr_newlines
location_columns_are_byte_based
success_result_remains_line_one_column_one
error_locations_preserve_no_effect_flags
location_reports_are_deterministic
```

## Diagnostic report impact

The existing diagnostic report already renders:

```text
line=<line>
column=<column>
```

Future precision work should update only the values, not the report shape.

## Implementation gate

Precise line/column implementation should not be added until:

1. this plan is merged;
2. newline behavior is accepted;
3. byte-based column behavior is accepted;
4. error-location rules are accepted;
5. exact tests are present;
6. no-effect flags remain tested.

## Current validation command

This plan is guarded by:

```sh
sh scripts/test-l-ui-parser-line-column-precision-plan.sh
```

The guard is static. It does not implement precision.

## Non-claims

This document does not implement precise parser locations, L-UI rendering, command behavior, Nucleus task handling, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.
