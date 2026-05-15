# Latticra L-UI AST Escaped String Report Implementation

Status: initial implementation contract
Scope: byte-oriented escaped string fields for detailed AST report metadata.

## Purpose

The L-UI AST Escaped String Report implementation adds additive escaped string fields to the detailed AST report.

It keeps existing literal fields intact and adds escaped fields for report values that may later contain broader text bytes.

## Implementation files

```text
src/l_ui_parser_ast.c
tests/l_ui_ast_escaped_string_report_invariants.c
scripts/test-l-ui-ast-escaped-string-report.sh
```

## Public API impact

No new public function is added.

Escaping is integrated into the existing detailed report API:

```text
latticra_l_ui_ast_detailed_report
```

## Private helper

The implementation adds a private helper in `src/l_ui_parser_ast.c`:

```text
escape_report_string
```

The helper is byte-oriented and remains private.

## Escaped report fields

The detailed AST report now includes additive escaped fields:

```text
purpose_escaped=<escaped-purpose>
value_escaped=<escaped-text>
```

Existing literal fields remain:

```text
purpose=<literal-purpose>
value=<literal-text>
```

## Field placement

Escaped fields are placed as follows:

```text
[card]
purpose=<literal-purpose>
purpose_escaped=<escaped-purpose>

[text <index>]
value=<literal-text>
value_escaped=<escaped-text>
```

Escaped fields are not added to rail sections, field sections, or failed-parse reports.

## Escape rules

The helper implements the required byte escape table:

| Input byte | Report text |
| --- | --- |
| newline LF `0x0A` | `\n` |
| carriage return CR `0x0D` | `\r` |
| horizontal tab `0x09` | `\t` |
| double quote `0x22` | `\"` |
| backslash `0x5C` | `\\` |
| NUL `0x00` | `\x00` |
| other control bytes `0x01`-`0x1F` | `\xNN` |
| DEL `0x7F` | `\x7F` |
| non-ASCII bytes `0x80`-`0xFF` | `\xNN` |

Printable ASCII bytes from `0x20` through `0x7E`, except double quote and backslash, are emitted literally.

Hex digits are uppercase:

```text
0123456789ABCDEF
```

## Buffer behavior

If the output buffer is too small, escaping returns:

```text
LATTICRA_STATUS_BUFFER_TOO_SMALL
```

When possible, the destination buffer is cleared to an empty string on failure.

## NUL behavior

The private helper supports NUL bytes through explicit input lengths.

Existing AST string fields are still C strings, so detailed report integration uses `strlen(...)` for current AST values. Dedicated tests validate explicit NUL byte escaping through the private helper test path.

## Failed parse behavior

Failed-parse detailed reports are unchanged.

They continue to render:

```text
parse_error=<error-label>
rail_count=0
field_count=0
text_count=0
```

No escaped fields appear in failed-parse reports.

## Compatibility

This implementation does not change:

```text
latticra_l_ui_ast_report
latticra_l_ui_parse_ast
latticra_l_ui_parse_source
latticra_l_ui_parse_result_report
latticra_l_ui_diagnostic_report
latticra_l_ui_ast_detailed_report existing required fields
```

## No-effect boundary

Escaped string reporting preserves:

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
sh scripts/test-l-ui-ast-escaped-string-report.sh
```

The main C workflow runs this check after the escaped string report implementation-plan guard.

## Required invariants

The escaped string report tests verify:

```text
escape_preserves_printable_ascii
escape_newline_as_backslash_n
escape_carriage_return_as_backslash_r
escape_tab_as_backslash_t
escape_quote_as_backslash_quote
escape_backslash_as_double_backslash
escape_nul_as_hex_00
escape_control_bytes_as_uppercase_hex
escape_del_as_uppercase_hex
escape_non_ascii_bytes_as_uppercase_hex
escape_rejects_small_buffers
escape_is_deterministic
detailed_report_contains_escaped_purpose
detailed_report_contains_escaped_text_values
detailed_report_escaped_fields_are_additive
detailed_report_escape_preserves_no_effect_flags
detailed_report_escape_does_not_change_failed_parse_report
```

The implementation also verifies mutated AST purpose and text values with newline, carriage return, tab, quote, and backslash bytes.

## Current evidence level

This implementation is an L2 tested byte-oriented escaping model for detailed AST report string fields.

It is not a broader text grammar, Unicode display model, renderer, UI runtime, command surface, Nucleus task runner, server client, update engine, recovery system, hardware system, boot system, or security boundary.

## Next implementation step

The next implementation candidate after escaped string reporting is:

```text
L-UI AST source-backed text extraction contract
```

That future work should define how AST text values are extracted from source instead of being fixed fixture metadata.

## Non-claims

This document and implementation do not broaden accepted L-UI text syntax, implement Unicode display behavior, add L-UI rendering, add command behavior, add Nucleus task handling, add live movement, add origin mutation, add recovery behavior, add server interaction, add self-update, add hardware support, add boot readiness, claim security isolation, claim sandboxing, or claim operating-system completeness.
