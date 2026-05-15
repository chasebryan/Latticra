# Latticra L-UI String-Literal Escape Contract

Status: string-literal escape contract
Scope: future decoding rules for quoted L-UI source strings before AST extraction decodes escape sequences.

## Purpose

This document defines the string-literal escape contract for L-UI source strings.

The current AST source-backed text extraction copies raw bytes between quotes and does not decode string escapes. Before AST extraction decodes escape sequences, Latticra needs a stable contract for which escape sequences are accepted, how they decode, what is rejected, how spans are preserved, and how reporting remains deterministic.

This document does not implement string-literal escape decoding.

## Current boundary

The current L-UI AST stack provides:

```text
validated L-UI parser
source-backed purpose extraction
source-backed text extraction
raw bytes copied between quotes
escaped report fields
source spans
no-effect flags
```

This contract does not add:

```text
string-literal escape decoding implementation
new accepted parser grammar
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

Future string-literal escape decoding should allow quoted L-UI strings to represent bytes that are awkward or unsafe to write literally while keeping source parsing deterministic.

Future decoding may apply to:

```text
card.purpose
text.value
```

It must remain metadata-only unless a later execution or rendering contract explicitly says otherwise.

## Accepted escape set

A future implementation should support only this initial escape set:

| Source escape | Decoded byte |
| --- | --- |
| `\\` | backslash `0x5C` |
| `\"` | double quote `0x22` |
| `\n` | LF `0x0A` |
| `\r` | CR `0x0D` |
| `\t` | horizontal tab `0x09` |
| `\xNN` | byte value from two uppercase hexadecimal digits |

No other escape sequences should be accepted in the first implementation.

## Hex escape rule

Hex escapes must use exactly two uppercase hexadecimal digits:

```text
\x00
\x09
\x1F
\x7F
\x80
\xFF
```

Lowercase hexadecimal digits should be rejected in the first implementation.

Examples that should be rejected:

```text
\x0a
\x0
\x001
\xGG
```

## Unknown escape rule

Unknown escape sequences should be rejected, not copied literally.

Examples that should be rejected:

```text
\a
\b
\f
\v
\u1234
\U00000000
```

## Unterminated escape rule

Unterminated escape sequences should be rejected.

Examples:

```text
\
\x
\x0
```

## Output byte rule

Decoded output is byte-oriented, not Unicode-codepoint-oriented.

The first implementation should decode into bounded byte buffers used by AST string fields.

A future Unicode display contract may define higher-level text behavior later.

## NUL byte rule

The contract may allow `\x00` as a decoded byte only after the AST storage model supports explicit lengths.

Current AST text fields are NUL-terminated C strings, so the first decoding implementation should reject decoded NUL bytes for AST values unless a length-carrying string storage contract is added first.

## Storage rule

The current AST storage uses NUL-terminated fixed-size buffers:

```text
latticra_l_ui_ast_card_t.purpose
latticra_l_ui_ast_text_t.value
```

A future implementation must not silently truncate decoded output.

If decoded output does not fit the destination buffer, decoding should return a stable failure and AST construction should avoid partial AST output.

## Source-span rule

Decoded values must preserve source-span metadata.

Spans should continue to refer to source byte ranges, not decoded output byte ranges.

For text nodes:

```text
text.span covers the source value range between quotes
```

For purpose values, no public purpose span exists yet; `card.span` remains the available public metadata unless a future purpose-span contract adds a new field.

## Report relationship

Detailed AST reports should continue to render:

```text
purpose=<decoded-or-current-literal-purpose>
purpose_escaped=<report-escaped-purpose>
value=<decoded-or-current-literal-text>
value_escaped=<report-escaped-text>
```

If string-literal decoding is implemented, `purpose` and `value` would contain decoded AST bytes rendered as C strings where safe, while `purpose_escaped` and `value_escaped` must remain stable report-safe representations.

## Failed parse behavior

If string-literal escape decoding fails, AST construction should avoid partial AST output.

The implementation plan must choose whether the parser reports a specific parse error or whether AST construction classifies the result as:

```text
LATTICRA_L_UI_PARSE_INTERNAL_ERROR
```

until parser-level string escape validation exists.

## No-effect rule

String-literal escape decoding is metadata-only.

It must preserve:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

## Compatibility rule

A future implementation must not change:

```text
latticra_l_ui_parse_source existing accepted fixture behavior
latticra_l_ui_ast_report existing required fields
latticra_l_ui_ast_detailed_report existing required fields
latticra_l_ui_diagnostic_report existing required fields
existing escaped report field semantics
```

The current first fixture contains no source escapes and should remain unchanged.

## Implementation gate

String-literal escape decoding implementation must not begin until a separate implementation plan defines:

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

## Future test list

A future implementation plan should include tests for:

```text
string_escape_decodes_backslash
string_escape_decodes_quote
string_escape_decodes_newline
string_escape_decodes_carriage_return
string_escape_decodes_tab
string_escape_decodes_uppercase_hex
string_escape_rejects_lowercase_hex
string_escape_rejects_short_hex
string_escape_rejects_invalid_hex
string_escape_rejects_unknown_escape
string_escape_rejects_unterminated_escape
string_escape_rejects_decoded_nul_until_length_storage_exists
string_escape_rejects_oversized_decoded_output
string_escape_preserves_source_spans
string_escape_updates_detailed_report_escaped_fields
string_escape_preserves_no_effect_flags
string_escape_does_not_change_failed_parse_report
string_escape_is_deterministic
```

## Forbidden behavior

A future string-literal escape implementation must not:

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
- broaden accepted grammar beyond this contract without a grammar update.

## Current validation command

This contract is guarded by:

```sh
sh scripts/test-l-ui-string-literal-escape-contract.sh
```

The guard is static. It does not implement string-literal escape decoding.

## Non-claims

This document does not implement string-literal escape decoding, broaden accepted L-UI text syntax, implement Unicode display behavior, add L-UI rendering, add command behavior, add Nucleus task handling, add live movement, add origin mutation, add recovery behavior, add server interaction, add self-update, add hardware support, add boot readiness, claim security isolation, claim sandboxing, or claim operating-system completeness.
