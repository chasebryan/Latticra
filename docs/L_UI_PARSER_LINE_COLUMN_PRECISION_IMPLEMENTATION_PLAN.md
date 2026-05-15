# Latticra L-UI Parser Line/Column Precision Implementation Plan

Status: implementation planning contract
Scope: helper shapes, parser touch points, exact tests, and no-effect boundaries before changing parser location behavior.

## Purpose

This document defines the implementation plan for precise line and column reporting in the L-UI parser.

The line/column precision plan is already merged and guarded. This plan decides how parser code should be changed before any location-tracking code is added.

## Relationship to previous contracts

This plan depends on:

```text
docs/L_UI_PARSER_LINE_COLUMN_PRECISION_PLAN.md
docs/L_UI_PARSER_DIAGNOSTICS.md
docs/L_UI_PARSER_DIAGNOSTICS_IMPLEMENTATION.md
include/latticra/l_ui_parser.h
src/l_ui_parser.c
src/l_ui_parser_diagnostics.c
```

Those files remain the source of truth for parser errors, diagnostic reports, and no-effect behavior.

## Implementation language decision

The precision implementation should be in C.

Reason:

- the parser is already implemented in C;
- parse results already expose `line` and `column` fields;
- diagnostic reports already render those fields;
- precision can be added without changing the public parser API;
- precision must remain portable and deterministic.

## Proposed module touch points

The first precision implementation should modify:

```text
src/l_ui_parser.c
tests/l_ui_parser_location_invariants.c
scripts/test-l-ui-parser-location.sh
.github/workflows/c.yml
```

It should not add a new public header.

## Public API rule

No public API change is required for the first precision implementation.

Existing fields remain the output surface:

```text
latticra_l_ui_parse_result_t.line
latticra_l_ui_parse_result_t.column
```

Existing diagnostic reports already include:

```text
line=<line>
column=<column>
```

## Internal helper shapes

The parser may add internal helpers similar to:

```text
static void location_default(size_t *line, size_t *column);

static int find_slice_location(
    const char *source,
    size_t source_len,
    const char *needle,
    size_t *line,
    size_t *column);

static int find_unbalanced_brace_location(
    const char *source,
    size_t source_len,
    size_t *line,
    size_t *column);

static int find_unterminated_string_location(
    const char *source,
    size_t source_len,
    size_t *line,
    size_t *column);

static void set_error_at(
    latticra_l_ui_parse_result_t *result,
    latticra_l_ui_parse_error_t error,
    size_t line,
    size_t column);
```

These helpers should remain private to `src/l_ui_parser.c`.

## Newline scanner behavior

The scanner must support:

```text
LF:   \n
CRLF: \r\n
CR:   \r
```

Rules:

1. Line and column are one-based.
2. `\n` increments line and resets column to 1.
3. `\r\n` counts as one newline and resets column to 1.
4. Lone `\r` counts as one newline and resets column to 1.
5. All other bytes increment column by 1.
6. Columns are byte-based, not display-cell-based.
7. Scanner behavior must not depend on host text mode.

## Parser touch-point plan

Initial parser changes should set precise locations for:

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

Other errors may keep conservative defaults until a later source-span contract.

## Error location mapping

| Parser error | First implementation location |
| --- | --- |
| `ok` | `line=1`, `column=1` |
| `null_argument` | not applicable, direct status return |
| `empty_source` | `line=1`, `column=1` |
| `unsupported_version` | first `lui` token if present, otherwise `line=1`, `column=1` |
| `missing_card` | `line=1`, `column=1` |
| `missing_purpose` | card body start when available |
| `missing_effect` | card body start when available |
| `unsupported_effect` | `effect` token |
| `missing_boundary` | card body start when available |
| `unsupported_boundary` | `boundary` token |
| `missing_rail` | card body start when available |
| `unknown_rail` | unsupported `rail` token when implemented later |
| `unknown_binding_prefix` | unsupported binding target |
| `missing_required_binding` | relevant rail when available, otherwise card body start |
| `unterminated_string` | opening quote of unterminated string |
| `unbalanced_brace` | unmatched brace when available |
| `forbidden_behavior_marker` | first forbidden marker |
| `source_too_large` | `line=1`, `column=1` |
| `internal_error` | `line=1`, `column=1` |

## No-effect preservation

Precision metadata must not change safety fields:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

## Exact implementation test list

The first precision implementation PR should include tests for:

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

## Test file plan

Add:

```text
tests/l_ui_parser_location_invariants.c
scripts/test-l-ui-parser-location.sh
```

Wire into:

```text
.github/workflows/c.yml
```

## Documentation requirement

The first precision implementation PR should update:

```text
README.md
docs/FOUNDATION_INDEX.md
docs/L_UI_PARSER_LINE_COLUMN_PRECISION_PLAN.md
```

and add:

```text
docs/L_UI_PARSER_LINE_COLUMN_PRECISION_IMPLEMENTATION.md
```

## Forbidden implementation behavior

The precision implementation must not:

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
- change diagnostic report shape;
- accept unsupported effects.

## Current validation command

This plan is guarded by:

```sh
sh scripts/test-l-ui-parser-line-column-precision-implementation-plan.sh
```

The guard is static. It does not implement precision.

## Implementation gate

Precision implementation code may be added only after this plan is merged.

## Non-claims

This document does not implement precise parser locations, L-UI rendering, command behavior, Nucleus task handling, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.
