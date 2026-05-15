# Latticra L-UI Parser Line/Column Precision Implementation

Status: initial implementation contract
Scope: private parser location helpers, parser touch-point updates, location invariants, and no-effect boundaries.

## Purpose

The L-UI Parser Line/Column Precision implementation adds deterministic line and column reporting for selected parser errors.

It updates private parser internals only. It does not change the public parser API.

## Implementation files

```text
src/l_ui_parser.c
tests/l_ui_parser_location_invariants.c
scripts/test-l-ui-parser-location.sh
```

## Public API stability

No public API was added for location precision.

The existing output fields remain the public location surface:

```text
latticra_l_ui_parse_result_t.line
latticra_l_ui_parse_result_t.column
```

Diagnostic reports already render those fields through the diagnostic mapping.

## Internal helper behavior

The parser now uses private helpers for:

```text
location_default
location_for_index
find_slice_index
find_slice_location
card_body_location
find_unbalanced_brace_location
find_unterminated_string_location
set_error_at
```

These helpers remain private to `src/l_ui_parser.c`.

## Location rules

Line and column are one-based.

Columns are byte-based, not display-cell-based.

Recognized newline forms:

```text
LF
CRLF
CR
```

## Implemented location touch points

The initial precision implementation covers:

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

Other errors may still use conservative default locations until a later source-span contract.

## No-effect preservation

Location precision is diagnostic metadata only.

It must not change:

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
sh scripts/test-l-ui-parser-location.sh
```

The main C workflow runs this check after the line-column implementation plan guard.

## Required invariants

The location tests verify:

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

## Current evidence level

This implementation is an L2 tested diagnostic-location model for the L-UI parser.

It is not a renderer, UI runtime, command surface, Nucleus task runner, server client, update engine, recovery system, hardware system, boot system, or security boundary.

## Next implementation step

The next implementation candidate after line/column precision is:

```text
L-UI parser source-span contract
```

That future work should define richer spans and source ranges before any AST or renderer integration.

## Non-claims

This document and implementation do not claim L-UI rendering, command behavior, Nucleus task handling, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.
