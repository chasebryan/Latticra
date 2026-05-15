# Latticra L-UI String-Literal Escape Contract

Status: string-literal escape contract
Scope: decoding rules for quoted L-UI source strings used by source-backed AST purpose and text values.

## Purpose

This document defines the string-literal escape contract for L-UI source strings.

Latticra now decodes the accepted string-literal escape set while materializing source-backed AST string values. The contract defines which escape sequences are accepted, how they decode, what is rejected, how spans are preserved, how failures are classified, and how reporting remains deterministic.

The implementation plan is documented separately in [`L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION_PLAN.md`](L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION_PLAN.md).

The implementation is documented separately in [`L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION.md`](L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION.md).

## Current boundary

The current L-UI AST stack provides:

```text
validated L-UI parser
source-backed purpose extraction
source-backed text extraction
accepted string-literal escape decoding
escaped report fields
source spans
no-effect flags
```

This contract does not add:

```text
parser-level invalid escape diagnostics
new accepted non-string grammar
renderer behavior
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

## Escape decoding purpose

String-literal escape decoding allows quoted L-UI strings to represent bytes that are awkward or unsafe to write literally while keeping source parsing deterministic.

Decoding applies to source-backed AST values:

```text
card.purpose
text.value
```

It remains metadata-only unless a later execution or rendering contract explicitly says otherwise.

## Accepted escape set

The implementation supports only this initial escape set:

| Source escape | Decoded byte |
| --- | --- |
| `\\` | backslash `0x5C` |
| `\"` | double quote `0x22` |
| `\n` | LF `0x0A` |
| `\r` | CR `0x0D` |
| `\t` | horizontal tab `0x09` |
| `\xNN` | byte value from two uppercase hexadecimal digits |

No other escape sequences are accepted in the first implementation.

## Hex escape rule

Hex escapes must use exactly two uppercase hexadecimal digits:

```text
\x09
\x1F
\x7F
\x80
\xFF
```

Lowercase hexadecimal digits are rejected in the first implementation.

Examples that are rejected:

```text
\x0a
\x0
\x001
\xGG
```

## Unknown escape rule

Unknown escape sequences are rejected, not copied literally.

Examples that are rejected:

```text
\a
\b
\f
\v
\u1234
\U00000000
```

## Unterminated escape rule

Unterminated escape sequences are rejected.

Examples:

```text
\
\x
\x0
```

## Output byte rule

Decoded output is byte-oriented, not Unicode-codepoint-oriented.

The implementation decodes into bounded byte buffers used by AST string fields.

A future Unicode display contract may define higher-level text behavior later.

## NUL byte rule

The contract may allow `\x00` as a decoded byte only after the AST storage model supports explicit lengths.

Current AST text fields are NUL-terminated C strings, so this implementation rejects decoded NUL bytes for AST values.

Literal `0x00` source bytes inside AST string values are also rejected.

## Storage rule

The current AST storage uses NUL-terminated fixed-size buffers:

```text
latticra_l_ui_ast_card_t.purpose
latticra_l_ui_ast_text_t.value
```

The implementation does not silently truncate decoded output.

If decoded output does not fit the destination buffer, decoding returns a stable failure and AST construction avoids partial AST output.

## Source-span rule

Decoded values preserve source-span metadata.

Spans continue to refer to source byte ranges, not decoded output byte ranges.

For text nodes:

```text
text.span covers the source value range between quotes
```

For purpose values, no public purpose span exists yet; `card.span` remains the available public metadata unless a future purpose-span contract adds a new field.

## Report relationship

Detailed AST reports continue to render:

```text
purpose=<decoded-purpose-as-current-C-string>
purpose_escaped=<report-safe-purpose>
value=<decoded-text-as-current-C-string>
value_escaped=<report-safe-text>
```

The escaped report fields remain the stable assertion target for decoded control bytes, quotes, backslashes, DEL, and non-ASCII bytes.

## Failure behavior

If string-literal escape decoding fails, AST construction avoids partial AST output.

Until parser-level string escape validation exists, invalid escapes classify the AST result as:

```text
LATTICRA_L_UI_PARSE_INTERNAL_ERROR
```

The structural parser remains compatible and does not yet expose first-class invalid escape errors.

## No-effect rule

String-literal escape decoding is metadata-only.

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

The implementation does not change:

```text
latticra_l_ui_parse_source existing accepted fixture behavior
latticra_l_ui_ast_report existing required fields
latticra_l_ui_ast_detailed_report existing required fields
latticra_l_ui_diagnostic_report existing required fields
existing escaped report field semantics
existing accepted fixture summary counts
```

The current first fixture contains no source escapes and remains unchanged.

## Implementation evidence

String-literal escape decoding required a separate implementation plan defining:

1. parser-level validation decision;
2. AST-level decoding helper shape;
3. accepted escape sequences;
4. rejected escape sequences;
5. NUL byte behavior;
6. capacity failure behavior;
7. span behavior;
8. detailed report behavior;
9. test file names;
10. exact invariant tests;
11. compatibility expectations.

That plan is recorded in [`L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION_PLAN.md`](L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION_PLAN.md).

The implementation is recorded in [`L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION.md`](L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION.md).

## Test list

The implementation tests verify:

```text
string_escape_decodes_backslash
string_escape_decodes_quote
string_escape_decodes_newline
string_escape_decodes_carriage_return
string_escape_decodes_tab
string_escape_decodes_uppercase_hex
string_escape_decodes_high_byte_hex
string_escape_rejects_lowercase_hex
string_escape_rejects_short_hex
string_escape_rejects_invalid_hex
string_escape_rejects_unknown_escape
string_escape_rejects_unterminated_escape
string_escape_rejects_decoded_nul_until_length_storage_exists
string_escape_rejects_literal_nul_until_length_storage_exists
string_escape_rejects_oversized_decoded_output
string_escape_preserves_source_spans
string_escape_updates_detailed_report_escaped_fields
string_escape_preserves_no_effect_flags
string_escape_does_not_change_parse_source_summary
string_escape_does_not_change_failed_parse_report
string_escape_is_deterministic
```

## Current validation commands

This contract is guarded by:

```sh
sh scripts/test-l-ui-string-literal-escape-contract.sh
```

The implementation is tested by:

```sh
sh scripts/test-l-ui-string-literal-escape.sh
```

## Forbidden behavior

The string-literal escape implementation must not:

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
- silently truncate decoded values;
- emit raw control bytes in escaped report fields;
- decode bindings, field names, rail names, card names, effect values, or boundary values;
- broaden accepted grammar beyond this contract without a grammar update.

## Non-claims

This document and implementation do not implement parser-level string escape diagnostics, length-carrying AST strings, Unicode display behavior, L-UI rendering, command behavior, Nucleus task handling, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.
