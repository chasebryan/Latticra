# Latticra L-UI AST Escaped String Report Implementation Plan

Status: implementation planning contract
Scope: private escape helper shape, escaped report fields, destination sizing, too-small behavior, exact tests, and compatibility expectations before escaped string report implementation.

## Purpose

This document defines the implementation plan for escaped string reporting in the L-UI AST detailed report.

The escaped string report contract is already merged and guarded. This plan decides the private helper shape, exact escaped fields, placement in the detailed AST report, destination sizes, too-small behavior, test files, exact tests, and compatibility expectations before code is added.

## Relationship to previous contracts

This plan depends on:

```text
docs/L_UI_AST_ESCAPED_STRING_REPORT_CONTRACT.md
docs/L_UI_AST_DETAILED_REPORT_IMPLEMENTATION.md
include/latticra/l_ui_parser.h
src/l_ui_parser_ast.c
```

Those files remain the source of truth for detailed AST reporting, text metadata, source spans, and no-effect boundaries.

## Implementation language decision

Escaped string reporting should be implemented in C.

Reason:

- the AST detailed report is implemented in C;
- report generation is part of the C public API surface;
- escaping should remain bounded, deterministic, and byte-oriented;
- the current C workflow can validate all escaping invariants;
- no dynamic runtime should be required.

## Public API decision

No new public function is needed for the first escaping implementation.

Escaping should be added to the existing detailed report API:

```text
latticra_l_ui_ast_detailed_report
```

The implementation should add escaped fields to the detailed report output while preserving existing required literal fields.

## Private helper shape

Add a private helper in:

```text
src/l_ui_parser_ast.c
```

Proposed helper:

```text
static latticra_status_t escape_report_string(
    const char *input,
    size_t input_len,
    char *output,
    size_t output_len);
```

The helper must remain private.

## Destination sizes

Add private bounded local buffers for escaped strings in `src/l_ui_parser_ast.c`.

Required destination sizes:

```text
escaped purpose buffer >= LATTICRA_L_UI_AST_PURPOSE_MAX * 4 + 1
escaped text buffer >= LATTICRA_L_UI_AST_PURPOSE_MAX * 4 + 1
```

The first implementation may use private macros:

```text
LATTICRA_L_UI_AST_ESCAPED_PURPOSE_MAX
LATTICRA_L_UI_AST_ESCAPED_TEXT_MAX
```

These do not need to be public unless future callers need direct escaping support.

## Escaped fields

Add escaped fields to the detailed report only:

```text
purpose_escaped=<escaped-purpose>
value_escaped=<escaped-text>
```

The existing literal fields should remain:

```text
purpose=<literal-purpose>
value=<literal-text>
```

This makes the first implementation additive.

## Field placement

Add escaped fields in these sections:

```text
[card]
[text <index>]
```

Placement rules:

1. In `[card]`, print `purpose_escaped` immediately after `purpose`.
2. In `[text <index>]`, print `value_escaped` immediately after `value`.
3. Do not add escaped fields to rail sections.
4. Do not add escaped fields to field sections.
5. Do not add escaped fields to failed-parse reports.

## Escape rules

The helper must implement the contract escape table:

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

Printable ASCII bytes from `0x20` through `0x7E`, except double quote and backslash, should be emitted literally.

## Hex rule

Hex escapes must use uppercase hexadecimal digits:

```text
0123456789ABCDEF
```

Lowercase hexadecimal output is not allowed.

## Byte-oriented rule

Escaping is byte-oriented, not Unicode-codepoint-oriented.

Input should be treated as `unsigned char` bytes for classification and hex output.

## Too-small behavior

If the destination buffer cannot hold the full escaped string and terminating NUL, `escape_report_string` must return:

```text
LATTICRA_STATUS_BUFFER_TOO_SMALL
```

The helper should clear the output buffer to an empty string when possible.

`latticra_l_ui_ast_detailed_report` must propagate this status if escaping fails.

## NUL behavior

The first implementation should support NUL bytes in the private helper test path through explicit `input_len`.

For existing AST strings, the helper will receive `strlen(...)` because current AST text fields are C strings. Dedicated helper tests should still validate NUL handling with byte arrays.

## Failed parse behavior

Escaping must not change failed-parse detailed report behavior.

Failed parse detailed reports should continue to render:

```text
parse_error=<error-label>
rail_count=0
field_count=0
text_count=0
```

No escaped fields should appear in failed-parse reports.

## Compatibility expectations

Escaped string reporting must be additive.

It must not change:

```text
latticra_l_ui_ast_report
latticra_l_ui_parse_ast
latticra_l_ui_parse_source
latticra_l_ui_parse_result_report
latticra_l_ui_diagnostic_report
latticra_l_ui_ast_detailed_report existing required fields
```

Existing parser, diagnostic, source-span, AST, compact report, and detailed report tests must continue to pass.

## No-effect preservation

Escaped string reporting must preserve:

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

## Test file plan

Add:

```text
tests/l_ui_ast_escaped_string_report_invariants.c
scripts/test-l-ui-ast-escaped-string-report.sh
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
docs/L_UI_AST_ESCAPED_STRING_REPORT_CONTRACT.md
docs/L_UI_AST_DETAILED_REPORT_IMPLEMENTATION.md
```

and add:

```text
docs/L_UI_AST_ESCAPED_STRING_REPORT_IMPLEMENTATION.md
```

## Forbidden implementation behavior

The escaped string implementation must not:

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
- emit memory addresses;
- emit raw control bytes in escaped fields;
- emit raw non-ASCII bytes in escaped fields.

## Current validation command

This plan is guarded by:

```sh
sh scripts/test-l-ui-ast-escaped-string-report-implementation-plan.sh
```

The guard is static. It does not implement escaped string reporting.

## Implementation gate

Escaped string report implementation code may be added only after this plan is merged.

## Non-claims

This document does not implement escaped string reporting, broaden accepted L-UI text syntax, implement Unicode display behavior, add L-UI rendering, add command behavior, add Nucleus task handling, add live movement, add origin mutation, add recovery behavior, add server interaction, add self-update, add hardware support, add boot readiness, claim security isolation, claim sandboxing, or claim operating-system completeness.
