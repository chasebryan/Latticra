# Latticra L-UI Parser String Escape Diagnostics Implementation

Status: initial implementation contract
Scope: parser-level diagnostics for invalid L-UI string-literal escape sequences.

## Purpose

The L-UI Parser String Escape Diagnostics implementation promotes invalid string-literal escape failures from AST-level internal-error classification to parser-level diagnostics.

The implementation reports stable parser errors, diagnostic codes, messages, hints, source spans, and no-effect flags before AST construction materializes source-backed string values.

## Implementation files

```text
include/latticra/l_ui_parser.h
src/l_ui_parser.c
src/l_ui_parser_diagnostics.c
tests/l_ui_parser_string_escape_diagnostics_invariants.c
scripts/test-l-ui-parser-string-escape-diagnostics.sh
```

Related existing files remain active:

```text
src/l_ui_parser_ast.c
tests/l_ui_string_literal_escape_invariants.c
scripts/test-l-ui-string-literal-escape.sh
```

## Public API additions

The implementation extends `latticra_l_ui_parse_error_t` with:

```text
LATTICRA_L_UI_PARSE_INVALID_STRING_ESCAPE = 19
LATTICRA_L_UI_PARSE_INVALID_HEX_ESCAPE = 20
LATTICRA_L_UI_PARSE_UNTERMINATED_ESCAPE = 21
LATTICRA_L_UI_PARSE_DECODED_NUL_IN_STRING = 22
LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING = 23
LATTICRA_L_UI_PARSE_STRING_VALUE_TOO_LARGE = 24
```

No new public function is added.

## Parse error labels

The implementation adds stable parse error labels:

```text
invalid_string_escape
invalid_hex_escape
unterminated_escape
decoded_nul_in_string
literal_nul_in_string
string_value_too_large
```

Existing parse error labels remain unchanged.

## Diagnostic codes

The implementation adds diagnostic codes:

```text
LUI0019 invalid_string_escape
LUI0020 invalid_hex_escape
LUI0021 unterminated_escape
LUI0022 decoded_nul_in_string
LUI0023 literal_nul_in_string
LUI0024 string_value_too_large
```

Existing diagnostic codes `LUI0000` through `LUI0018` remain unchanged.

## Stable messages

The implementation uses these deterministic messages:

```text
LUI0019: String literal escape is not supported.
LUI0020: Hex string escape must use exactly two uppercase hexadecimal digits.
LUI0021: String literal escape is not terminated.
LUI0022: Decoded NUL bytes are not supported in AST strings.
LUI0023: Literal NUL bytes are not supported in AST strings.
LUI0024: Decoded string value exceeds the supported AST storage limit.
```

Messages do not include dynamic source fragments.

## Stable hints

The implementation uses these deterministic hints:

```text
LUI0019: Use only \\, \", \n, \r, \t, or uppercase \xNN escapes.
LUI0020: Use exactly two uppercase hex digits, such as \x0A or \x7F.
LUI0021: Complete the escape sequence or remove the trailing backslash.
LUI0022: Avoid \x00 until length-carrying AST strings exist.
LUI0023: Remove literal NUL bytes from the source string.
LUI0024: Shorten the decoded purpose or text value.
```

Hints do not suggest unsupported Unicode escapes.

## Parser helper implementation

The implementation adds private helpers in `src/l_ui_parser.c`:

```text
is_upper_hex_digit
upper_hex_value
validate_string_literal_escape_span
validate_l_ui_string_literal_escapes
```

These helpers remain private.

## Validation targets

The implementation validates quoted values used as source-backed AST strings:

```text
purpose "..."
first text "..."
second text "..."
```

It does not validate or decode:

```text
card names
rail names
field names
binding values
effect values
boundary values
```

## Validation order

String escape validation runs inside:

```text
latticra_l_ui_parse_source
```

after structural fixture checks and before returning `LATTICRA_L_UI_PARSE_OK`.

Existing structural errors retain priority over string escape diagnostics.

When source structure is valid but a string escape is invalid, the parser reports the string escape diagnostic instead of allowing AST construction to classify an internal error.

## Source-span behavior

Diagnostics remain source-oriented.

For invalid escapes, spans cover the rejected source bytes:

```text
\a      -> span covers \a
\x0a    -> span covers \x0a
\xGG    -> span covers \xGG
\x      -> span covers \x
\x0     -> span covers \x0
\x00    -> span covers \x00
literal NUL -> span covers the literal NUL source byte
oversized decoded output -> span covers the full source value range between quotes
```

Line and column point to the first byte of the rejected span.

Line and column remain one-based byte positions in the in-memory source buffer.

## Capacity behavior

Parser validation uses the current AST string storage capacity:

```text
LATTICRA_L_UI_AST_PURPOSE_MAX
```

for both purpose and text values.

If decoded output would be greater than or equal to the destination capacity, parser validation returns:

```text
LATTICRA_L_UI_PARSE_STRING_VALUE_TOO_LARGE
```

## NUL behavior

Decoded `\x00` returns:

```text
LATTICRA_L_UI_PARSE_DECODED_NUL_IN_STRING
```

Literal `0x00` source bytes inside the validated string value range return:

```text
LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING
```

NUL bytes remain rejected until a length-carrying AST string storage contract exists.

## AST compatibility behavior

Invalid escapes are rejected by:

```text
latticra_l_ui_parse_source
```

before AST construction materializes values.

For invalid escape source, `latticra_l_ui_parse_ast` preserves failed-parse behavior:

```text
ast.parse_result.error = parser-level string escape error
ast.rail_count = 0
ast.field_count = 0
ast.text_count = 0
failed-parse detailed report only
```

Accepted escapes continue to decode in AST values exactly as the string-literal escape implementation defines.

## Report compatibility behavior

Parser result reports render the new parse error labels through existing report fields.

Diagnostic reports render:

```text
diagnostic_severity=error
diagnostic_code=<LUI0019-through-LUI0024>
diagnostic_message=<stable-message>
diagnostic_hint=<stable-hint>
```

Detailed AST reports continue using the failed-parse report path for rejected sources.

Existing report fields remain stable.

## Compatibility

The implementation does not change:

```text
accepted string-literal escape decoding
existing diagnostic codes LUI0000 through LUI0018
existing parser error labels for current errors
latticra_l_ui_ast_report existing required fields
latticra_l_ui_ast_detailed_report existing required fields for accepted sources
latticra_l_ui_diagnostic_report existing required fields
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

## No-effect boundary

Parser-level string escape diagnostics preserve:

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
sh scripts/test-l-ui-parser-string-escape-diagnostics.sh
```

The main C workflow runs this check after the parser string escape diagnostics implementation-plan guard.

## Required invariants

The parser string escape diagnostics tests verify:

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

## Current evidence level

This implementation is an L2 tested parser-level diagnostic model for invalid L-UI string-literal escapes.

It is not a length-carrying AST string model, Unicode display model, renderer, UI runtime, command surface, Nucleus task runner, server client, update engine, recovery system, hardware system, boot system, sandbox, or operating system.

## Next implementation step

The next implementation candidate is:

```text
L-UI length-carrying AST string storage contract
```

That future work should define explicit AST string lengths before decoded NUL bytes can ever be accepted.

## Non-claims

This document and implementation do not implement length-carrying AST strings, allow decoded NUL bytes, broaden accepted L-UI syntax, implement Unicode display behavior, add L-UI rendering, add command behavior, add Nucleus task handling, add live movement, add origin mutation, add recovery behavior, add server interaction, add self-update, add hardware support, add boot readiness, claim security isolation, claim sandboxing, or claim operating-system completeness.
