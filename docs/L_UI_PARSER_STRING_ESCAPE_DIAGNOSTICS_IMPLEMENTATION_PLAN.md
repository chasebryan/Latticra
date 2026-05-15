# Latticra L-UI Parser String Escape Diagnostics Implementation Plan

Status: implementation planning contract
Scope: parser enum additions, diagnostic code additions, parse error labels, stable messages, stable hints, source-span rules, validation order, AST/report compatibility, exact test file names, and exact invariant tests before parser-level string escape diagnostics code.

## Purpose

This document defines the implementation plan for parser-level diagnostics for invalid L-UI string-literal escape sequences.

The parser string escape diagnostics contract is already merged and guarded. This plan decides the exact public enum changes, diagnostic mapping updates, parser validation helper shape, source-span behavior, AST compatibility behavior, report behavior, test files, and compatibility expectations before implementation code is added.

## Relationship to previous contracts

This plan depends on:

```text
docs/L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_CONTRACT.md
docs/L_UI_PARSER_DIAGNOSTICS.md
docs/L_UI_PARSER_DIAGNOSTICS_IMPLEMENTATION.md
docs/L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION.md
include/latticra/l_ui_parser.h
src/l_ui_parser.c
src/l_ui_parser_ast.c
```

Those files remain the source of truth for current parser diagnostics, source spans, string-literal escape decoding, AST failure behavior, and no-effect boundaries.

## Implementation language decision

Parser-level string escape diagnostics should be implemented in C.

Reason:

- the L-UI parser is implemented in C;
- diagnostics are exposed through a C public API surface;
- validation must remain bounded, deterministic, and no-effect;
- the current C workflow can validate diagnostic invariants;
- no dynamic runtime should be required.

## Public API decision

Extend the existing public parser error enum in:

```text
include/latticra/l_ui_parser.h
```

Add the new values after:

```text
LATTICRA_L_UI_PARSE_INTERNAL_ERROR = 18
```

Proposed exact values:

```text
LATTICRA_L_UI_PARSE_INVALID_STRING_ESCAPE = 19
LATTICRA_L_UI_PARSE_INVALID_HEX_ESCAPE = 20
LATTICRA_L_UI_PARSE_UNTERMINATED_ESCAPE = 21
LATTICRA_L_UI_PARSE_DECODED_NUL_IN_STRING = 22
LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING = 23
LATTICRA_L_UI_PARSE_STRING_VALUE_TOO_LARGE = 24
```

No new public function is required for the first implementation.

## Parse error label decision

Update:

```text
latticra_l_ui_parse_error_label
```

with stable labels:

```text
invalid_string_escape
invalid_hex_escape
unterminated_escape
decoded_nul_in_string
literal_nul_in_string
string_value_too_large
```

Existing labels must remain unchanged.

## Diagnostic mapping decision

Update:

```text
latticra_l_ui_diagnostic_from_parse_result
```

so the new parser errors map to:

```text
LUI0019 invalid_string_escape
LUI0020 invalid_hex_escape
LUI0021 unterminated_escape
LUI0022 decoded_nul_in_string
LUI0023 literal_nul_in_string
LUI0024 string_value_too_large
```

Severity for all new diagnostics should be:

```text
LATTICRA_L_UI_DIAGNOSTIC_ERROR
```

## Stable messages

Use these exact messages:

```text
LUI0019: String literal escape is not supported.
LUI0020: Hex string escape must use exactly two uppercase hexadecimal digits.
LUI0021: String literal escape is not terminated.
LUI0022: Decoded NUL bytes are not supported in AST strings.
LUI0023: Literal NUL bytes are not supported in AST strings.
LUI0024: Decoded string value exceeds the supported AST storage limit.
```

Messages must remain deterministic and must not include dynamic source fragments.

## Stable hints

Use these exact hints:

```text
LUI0019: Use only \\, \", \n, \r, \t, or uppercase \xNN escapes.
LUI0020: Use exactly two uppercase hex digits, such as \x0A or \x7F.
LUI0021: Complete the escape sequence or remove the trailing backslash.
LUI0022: Avoid \x00 until length-carrying AST strings exist.
LUI0023: Remove literal NUL bytes from the source string.
LUI0024: Shorten the decoded purpose or text value.
```

Hints must not suggest unsupported escape forms such as Unicode escapes.

## Parser helper plan

Add private helpers in:

```text
src/l_ui_parser.c
```

Proposed helpers:

```text
static int is_upper_hex_digit(unsigned char byte);

static unsigned char upper_hex_value(unsigned char byte);

static latticra_l_ui_parse_error_t validate_string_literal_escape_span(
    const char *source,
    size_t source_len,
    size_t value_start,
    size_t value_end,
    size_t destination_len,
    latticra_l_ui_source_span_t *span);

static latticra_l_ui_parse_error_t validate_l_ui_string_literal_escapes(
    const char *source,
    size_t source_len,
    latticra_l_ui_source_span_t *span);
```

Helpers must remain private.

The validation helper may share logic with AST decoding later, but this first implementation can duplicate small byte-oriented logic to avoid changing public API or adding shared modules.

## Validation targets

The first parser-level string escape diagnostics implementation should validate only quoted source values used as AST strings:

```text
purpose "..."
first text "..."
second text "..."
```

It should not validate or decode:

```text
card names
rail names
field names
binding values
effect values
boundary values
```

## Validation order

Parser-level string escape validation should run inside:

```text
latticra_l_ui_parse_source
```

after these checks:

```text
null argument check
empty source check
source size check
unterminated string check
unbalanced brace check
version check
card check
purpose presence check
effect presence and supported effect checks
boundary presence and supported boundary checks
forbidden behavior marker check
required rail checks
unknown binding prefix check
required binding checks
```

and before the parser returns `LATTICRA_L_UI_PARSE_OK`.

Reason:

- existing structural errors should keep their current priority;
- validation should only inspect string escapes after the accepted fixture structure is present;
- accepted sources should remain compatible;
- invalid escapes should no longer reach AST construction as internal errors when structure is otherwise valid.

## Source-span behavior

Use source-oriented spans.

Exact span expectations:

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

## Capacity behavior

Parser validation should use the current AST string storage capacity:

```text
LATTICRA_L_UI_AST_PURPOSE_MAX
```

for both purpose and text values.

If decoded output would be greater than or equal to the destination capacity, parser validation should return:

```text
LATTICRA_L_UI_PARSE_STRING_VALUE_TOO_LARGE
```

This prevents oversized decoded values from reaching AST construction.

## NUL behavior

Decoded `\x00` should return:

```text
LATTICRA_L_UI_PARSE_DECODED_NUL_IN_STRING
```

Literal `0x00` source bytes inside the validated string value range should return:

```text
LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING
```

NUL bytes remain rejected until a length-carrying AST string storage contract exists.

## AST compatibility behavior

After parser-level diagnostics are implemented, invalid escapes should be rejected by:

```text
latticra_l_ui_parse_source
```

before AST construction materializes values.

For invalid escape source, `latticra_l_ui_parse_ast` should preserve failed-parse behavior:

```text
ast.parse_result.error = parser-level string escape error
ast.rail_count = 0
ast.field_count = 0
ast.text_count = 0
failed-parse detailed report only
```

Accepted escapes must continue to decode in AST values exactly as the current string-literal escape implementation defines.

## Report compatibility behavior

Parser result reports should render the new parse error labels through existing report fields.

Diagnostic reports should render:

```text
diagnostic_severity=error
diagnostic_code=<LUI0019-through-LUI0024>
diagnostic_message=<stable-message>
diagnostic_hint=<stable-hint>
```

Detailed AST reports should continue using the failed-parse report path for rejected sources.

Existing report fields must remain stable.

## Compatibility expectations

The implementation must not change:

```text
accepted string-literal escape decoding
existing diagnostic codes LUI0000 through LUI0018
existing parser error labels for current errors
latticra_l_ui_ast_report existing required fields
latticra_l_ui_ast_detailed_report existing required fields for accepted sources
latticra_l_ui_diagnostic_report existing required fields
existing accepted fixture summary counts
```

The first accepted fixture should still report:

```text
rail_count=9
field_count=23
text_count=2
effect=none
boundary=preview_only
```

## No-effect preservation

Parser-level string escape diagnostics must preserve:

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

## Test file plan

Add:

```text
tests/l_ui_parser_string_escape_diagnostics_invariants.c
scripts/test-l-ui-parser-string-escape-diagnostics.sh
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
docs/L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_CONTRACT.md
docs/L_UI_PARSER_DIAGNOSTICS.md
docs/L_UI_PARSER_DIAGNOSTICS_IMPLEMENTATION.md
docs/L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION.md
```

and add:

```text
docs/L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_IMPLEMENTATION.md
```

## Forbidden implementation behavior

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
- broaden accepted grammar beyond the string-literal escape contract;
- change accepted escape decoding semantics.

## Current validation command

This plan is guarded by:

```sh
sh scripts/test-l-ui-parser-string-escape-diagnostics-implementation-plan.sh
```

The guard is static. It does not implement parser-level string escape diagnostics.

## Implementation gate

Parser-level string escape diagnostics implementation code may be added only after this plan is merged.

## Non-claims

This document does not implement parser-level string escape diagnostics, change parser error enums, change diagnostic codes, change AST storage, implement length-carrying AST strings, broaden accepted L-UI syntax, implement Unicode display behavior, add L-UI rendering, add command behavior, add Nucleus task handling, add live movement, add origin mutation, add recovery behavior, add server interaction, add self-update, add hardware support, add boot readiness, claim security isolation, claim sandboxing, or claim operating-system completeness.
