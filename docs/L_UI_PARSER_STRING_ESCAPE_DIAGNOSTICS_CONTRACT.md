# Latticra L-UI Parser String Escape Diagnostics Contract

Status: parser string escape diagnostics contract
Scope: parser-level diagnostics for invalid L-UI string-literal escape sequences before and after parser diagnostics extension.

## Purpose

This document defines the parser-level diagnostics contract for invalid L-UI string-literal escape sequences.

The string-literal escape decoder originally ran during AST construction. Invalid escapes were classified as:

```text
LATTICRA_L_UI_PARSE_INTERNAL_ERROR
```

at the AST layer so the structural parser remained compatible. This contract defined the parser-level diagnostic surface before parser validation was extended to report invalid escapes directly.

This document does not implement parser-level string escape diagnostics.

The implementation plan is documented separately in [`L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_IMPLEMENTATION_PLAN.md`](L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_IMPLEMENTATION_PLAN.md).

The implementation is documented separately in [`L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_IMPLEMENTATION.md`](L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_IMPLEMENTATION.md).

## Relationship to existing diagnostics

This contract extends the existing parser diagnostics track:

```text
docs/L_UI_PARSER_DIAGNOSTICS.md
docs/L_UI_PARSER_DIAGNOSTICS_IMPLEMENTATION_PLAN.md
docs/L_UI_PARSER_DIAGNOSTICS_IMPLEMENTATION.md
docs/L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_IMPLEMENTATION_PLAN.md
docs/L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_IMPLEMENTATION.md
docs/L_UI_STRING_LITERAL_ESCAPE_CONTRACT.md
docs/L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION_PLAN.md
docs/L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION.md
include/latticra/l_ui_parser.h
src/l_ui_parser.c
src/l_ui_parser_ast.c
```

The existing diagnostics contract owns stable parser diagnostic language. This contract defines the extension set for rejected string-literal escapes only.

## Current boundary

The current system provides:

```text
structural L-UI parser diagnostics
source spans
line and column metadata
string-literal escape decoding during AST construction
parser-level invalid escape diagnostics
escaped detailed AST report fields
no-effect flags
```

This contract does not add:

```text
new accepted escape sequences
length-carrying AST strings
Unicode display behavior
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

## Diagnostic purpose

Parser-level string escape diagnostics make rejected string-literal escapes visible before AST construction.

The behavior allows:

```text
latticra_l_ui_parse_source
latticra_l_ui_diagnostic_from_parse_result
latticra_l_ui_diagnostic_report
```

to report stable invalid-escape categories, messages, hints, source spans, and no-effect flags.

## Parser error additions

The implementation extends `latticra_l_ui_parse_error_t` after `LATTICRA_L_UI_PARSE_INTERNAL_ERROR` with:

```text
LATTICRA_L_UI_PARSE_INVALID_STRING_ESCAPE
LATTICRA_L_UI_PARSE_INVALID_HEX_ESCAPE
LATTICRA_L_UI_PARSE_UNTERMINATED_ESCAPE
LATTICRA_L_UI_PARSE_DECODED_NUL_IN_STRING
LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING
LATTICRA_L_UI_PARSE_STRING_VALUE_TOO_LARGE
```

These names are reserved by this contract for parser-level string escape diagnostics.

## Diagnostic codes

The diagnostic codes extend the existing `LUI0000` through `LUI0018` code range:

```text
LUI0019 invalid_string_escape
LUI0020 invalid_hex_escape
LUI0021 unterminated_escape
LUI0022 decoded_nul_in_string
LUI0023 literal_nul_in_string
LUI0024 string_value_too_large
```

The code numbers are stable.

## Stable messages

Message language is concise and deterministic:

| Code | Message |
| --- | --- |
| `LUI0019` | String literal escape is not supported. |
| `LUI0020` | Hex string escape must use exactly two uppercase hexadecimal digits. |
| `LUI0021` | String literal escape is not terminated. |
| `LUI0022` | Decoded NUL bytes are not supported in AST strings. |
| `LUI0023` | Literal NUL bytes are not supported in AST strings. |
| `LUI0024` | Decoded string value exceeds the supported AST storage limit. |

Messages do not include dynamic source fragments.

## Hint language

Hint language is stable:

| Code | Hint |
| --- | --- |
| `LUI0019` | Use only \\, \", \n, \r, \t, or uppercase \xNN escapes. |
| `LUI0020` | Use exactly two uppercase hex digits, such as \x0A or \x7F. |
| `LUI0021` | Complete the escape sequence or remove the trailing backslash. |
| `LUI0022` | Avoid \x00 until length-carrying AST strings exist. |
| `LUI0023` | Remove literal NUL bytes from the source string. |
| `LUI0024` | Shorten the decoded purpose or text value. |

Hints must not suggest unsupported escape forms such as Unicode escapes.

## Source-span behavior

Diagnostics must remain source-oriented.

For invalid escapes, spans should cover the rejected source bytes:

```text
\a      -> span covers \a
\x0a    -> span covers \x0a
\xGG    -> span covers \xGG
\       -> span covers the trailing backslash
\x      -> span covers \x
\x0     -> span covers \x0
\x00    -> span covers \x00
literal NUL -> span covers the literal NUL source byte
oversized decoded output -> span covers the full source value range between quotes
```

Line and column should point to the first byte of the rejected span.

Line and column remain one-based byte positions in the in-memory source buffer.

## Validation order

Parser-level string escape validation runs only after basic structural fixture checks.

It runs before AST construction and before AST values are materialized.

It must not hide earlier structural parser errors when those errors occur before a string-literal escape can be inspected deterministically.

When source structure is valid but a string escape is invalid, the string escape diagnostic is reported instead of allowing AST construction to classify an internal error.

## Accepted escape compatibility

Parser-level diagnostics preserve the accepted escape set:

```text
\\
\"
\n
\r
\t
\xNN
```

where `\xNN` uses exactly two uppercase hexadecimal digits.

The diagnostics implementation must not broaden accepted escapes without a separate grammar or string-literal escape contract update.

## AST compatibility

Invalid escapes are rejected by:

```text
latticra_l_ui_parse_source
```

before AST construction runs.

For invalid escape source, AST behavior is:

```text
ast.parse_result.error = parser-level string escape error
ast.rail_count = 0
ast.field_count = 0
ast.text_count = 0
failed-parse detailed report only
```

Accepted escapes continue to decode in AST values exactly as the string-literal escape implementation defines.

## Report relationship

Diagnostic reports render:

```text
diagnostic_severity=error
diagnostic_code=<LUI0019-through-LUI0024>
diagnostic_message=<stable-message>
diagnostic_hint=<stable-hint>
```

Parser result reports continue to include stable parse error labels.

Detailed AST reports continue using the failed-parse report path for rejected sources.

## No-effect rule

Parser-level string escape diagnostics are metadata-only.

They preserve:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

## Compatibility rule

The implementation must not change:

```text
accepted string-literal escape decoding
latticra_l_ui_ast_report existing required fields
latticra_l_ui_ast_detailed_report existing required fields for accepted sources
latticra_l_ui_diagnostic_report existing required fields
existing diagnostic codes LUI0000 through LUI0018
existing parser error labels for current errors
existing accepted fixture summary counts
```

The first accepted fixture still reports:

```text
rail_count=9
field_count=23
text_count=2
effect=none
boundary=preview_only
```

## Implementation evidence

Parser-level string escape diagnostics implementation required a separate implementation plan defining:

1. parser enum additions;
2. diagnostic code additions;
3. parse error labels;
4. stable messages;
5. stable hints;
6. source-span rules;
7. validation order;
8. AST compatibility behavior;
9. report compatibility behavior;
10. exact test file names;
11. exact invariant tests.

That plan is recorded in [`L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_IMPLEMENTATION_PLAN.md`](L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_IMPLEMENTATION_PLAN.md).

The implementation is recorded in [`L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_IMPLEMENTATION.md`](L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_IMPLEMENTATION.md).

## Test list

The implementation tests verify:

```text
string_escape_diagnostic_rejects_unknown_escape_lui0019
string_escape_diagnostic_rejects_lowercase_hex_lui0020
string_escape_diagnostic_rejects_short_hex_lui0020
string_escape_diagnostic_rejects_invalid_hex_lui0020
string_escape_diagnostic_rejects_unterminated_escape_lui0021
string_escape_diagnostic_rejects_decoded_nul_lui0022
string_escape_diagnostic_rejects_literal_nul_lui0023
string_escape_diagnostic_rejects_oversized_decoded_output_lui0024
string_escape_diagnostic_reports_source_span
string_escape_diagnostic_reports_line_column
string_escape_diagnostic_preserves_no_effect_flags
string_escape_diagnostic_does_not_change_accepted_escape_decoding
string_escape_diagnostic_does_not_change_existing_error_codes
string_escape_diagnostic_uses_failed_parse_ast_report
string_escape_diagnostic_is_deterministic
```

## Forbidden behavior

The parser-level string escape diagnostics implementation must not:

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
- accept lowercase hex escapes;
- accept Unicode escapes;
- accept unknown escapes literally;
- allow decoded NUL bytes before length-carrying AST strings exist;
- broaden accepted grammar beyond the string-literal escape contract.

## Current validation commands

This contract is guarded by:

```sh
sh scripts/test-l-ui-parser-string-escape-diagnostics-contract.sh
```

The implementation is tested by:

```sh
sh scripts/test-l-ui-parser-string-escape-diagnostics.sh
```

## Non-claims

This document and implementation do not change AST storage, implement length-carrying AST strings, allow decoded NUL bytes, broaden accepted L-UI syntax, implement Unicode display behavior, add L-UI rendering, add command behavior, add Nucleus task handling, add live movement, add origin mutation, add recovery behavior, add server interaction, add self-update, add hardware support, add boot readiness, claim security isolation, claim sandboxing, or claim operating-system completeness.
