# Latticra L-UI String-Literal Escape Implementation Plan

Status: implementation planning contract
Scope: parser-level validation decision, AST-level decoding helper shape, accepted and rejected escapes, NUL behavior, capacity behavior, span behavior, detailed report behavior, exact tests, and compatibility expectations before string-literal escape decoding code.

## Purpose

This document defines the implementation plan for L-UI string-literal escape decoding.

The string-literal escape contract is already merged and guarded. This plan decides where the first decoding implementation belongs, which private helpers should be added, how accepted escapes decode, how rejected escapes fail, how NUL bytes are handled under the current NUL-terminated AST storage model, how source spans remain source-oriented, how detailed reports stay deterministic, and which tests must exist before decoding is considered implemented.

## Relationship to previous contracts

This plan depends on:

```text
docs/L_UI_STRING_LITERAL_ESCAPE_CONTRACT.md
docs/L_UI_AST_SOURCE_BACKED_TEXT_IMPLEMENTATION.md
docs/L_UI_AST_ESCAPED_STRING_REPORT_IMPLEMENTATION.md
docs/L_UI_PARSER_AST_IMPLEMENTATION.md
include/latticra/l_ui_parser.h
src/l_ui_parser.c
src/l_ui_parser_ast.c
```

Those files remain the source of truth for accepted parser summaries, AST storage, source-backed purpose/text extraction, report escaping, source spans, parse error labels, and no-effect boundaries.

## Implementation language decision

String-literal escape decoding should be implemented in C.

Reason:

- the L-UI parser and AST builder are implemented in C;
- AST string storage is a C public API surface;
- decoding must remain bounded, deterministic, and no-effect;
- the current C workflow can validate decoding invariants;
- no dynamic runtime should be required.

## Public API decision

No new public function is needed for the first string-literal escape implementation.

Decoding should be integrated into:

```text
latticra_l_ui_parse_ast
```

The public AST fields remain:

```text
latticra_l_ui_ast_card_t.purpose
latticra_l_ui_ast_text_t.value
```

The first implementation should not add a new public `latticra_l_ui_parse_error_t` value for invalid string escapes.

## Parser-level validation decision

The first implementation should keep `latticra_l_ui_parse_source` behavior compatible and should not add parser-level string-escape validation yet.

Decision:

```text
latticra_l_ui_parse_source remains a structural parser for the current L-UI fixture shape.
latticra_l_ui_parse_ast performs string-literal escape decoding while constructing AST values.
invalid escapes found during AST decoding classify the AST result as LATTICRA_L_UI_PARSE_INTERNAL_ERROR.
```

Reason:

- the current parse error enum has no string-escape-specific error;
- adding parser-level escape errors is a broader diagnostic/API change;
- AST extraction already owns source-backed purpose/text value materialization;
- this keeps `latticra_l_ui_parse_source` accepted fixture summaries stable;
- failed AST construction already has a no-partial-output path.

A later parser diagnostics contract may promote invalid string escape reporting to parser-level errors.

## Decoding helper plan

Add private helpers in:

```text
src/l_ui_parser_ast.c
```

Proposed helpers:

```text
static int is_upper_hex_digit(unsigned char byte);

static unsigned char upper_hex_value(unsigned char byte);

static latticra_status_t decode_l_ui_string_literal_value(
    const char *source,
    size_t start_offset,
    size_t end_offset,
    char *destination,
    size_t destination_len);

static latticra_status_t extract_decoded_quoted_value_after_token(
    const char *source,
    size_t source_len,
    const char *token,
    size_t occurrence,
    char *destination,
    size_t destination_len,
    latticra_l_ui_source_span_t *value_span);
```

Helpers must remain private.

The existing raw extraction helper may be replaced or refactored, but the new behavior must decode the value before writing into the AST destination buffer.

## Extraction targets

The first implementation should decode only source-backed AST string values:

```text
purpose "..." -> ast.card.purpose
first text "..." -> ast.texts[0].value
second text "..." -> ast.texts[1].value
```

No binding values, rail names, field names, card names, effect values, or boundary values should be decoded in this slice.

## Accepted escape behavior

The first implementation should accept only:

```text
\\
\"
\n
\r
\t
\xNN
```

where `\xNN` uses exactly two uppercase hexadecimal digits.

Decoded byte mapping:

```text
\\ -> 0x5C
\" -> 0x22
\n -> 0x0A
\r -> 0x0D
\t -> 0x09
\x41 -> 0x41
\x7F -> 0x7F
\x80 -> 0x80
\xFF -> 0xFF
```

Printable non-escaped source bytes should be copied unchanged unless they are NUL bytes.

## Rejected escape behavior

The first implementation should reject:

```text
\a
\b
\f
\v
\u1234
\U00000000
\x0a
\x0
\x001
\xGG
\
\x
\x0
```

Any backslash followed by an unsupported escape marker must fail instead of being copied literally.

Lowercase hex digits must fail in the first implementation.

## NUL byte behavior

Decoded NUL bytes must be rejected in the first implementation.

This includes:

```text
\x00
```

and any literal `0x00` source byte that would enter an AST string value.

Reason:

```text
latticra_l_ui_ast_card_t.purpose
latticra_l_ui_ast_text_t.value
```

are currently NUL-terminated fixed-size C strings without explicit decoded lengths.

A later length-carrying AST string storage contract may allow NUL bytes.

## Capacity behavior

Decoding must respect destination capacities:

```text
LATTICRA_L_UI_AST_PURPOSE_MAX
latticra_l_ui_ast_card_t.purpose
latticra_l_ui_ast_text_t.value
```

If decoded output length is greater than or equal to the destination buffer length, decoding should return:

```text
LATTICRA_STATUS_BUFFER_TOO_SMALL
```

and clear the destination to an empty C string when possible.

The implementation must not silently truncate decoded values.

## AST failure behavior

If string-literal escape decoding fails, `latticra_l_ui_parse_ast` should return:

```text
LATTICRA_STATUS_OK
```

and classify the AST parse result as:

```text
ast.parse_result.error = LATTICRA_L_UI_PARSE_INTERNAL_ERROR
```

The AST must avoid partial output:

```text
ast.rail_count = 0
ast.field_count = 0
ast.text_count = 0
ast.card.rail_count = 0
ast.card.field_count = 0
ast.card.text_count = 0
```

The failed-parse detailed report path should remain the compact failed-parse report.

## Source-span behavior

Decoded values must preserve source-span metadata.

Spans continue to refer to source byte ranges, not decoded output byte ranges.

For text nodes:

```text
text.span covers the source value range between quotes
```

The span range includes the source escape bytes. For example, a source value containing `\n` has a text span over two source bytes, even though the decoded AST value contains one LF byte.

Do not add a new public `purpose_span` field in the first implementation.

## Detailed report relationship

Detailed reports should continue to render:

```text
purpose=<decoded-purpose-as-current-C-string>
purpose_escaped=<report-safe-purpose>
value=<decoded-text-as-current-C-string>
value_escaped=<report-safe-text>
```

For decoded control bytes, quote bytes, backslashes, DEL, and non-ASCII bytes, the stable assertion target should be:

```text
purpose_escaped=<report-safe-purpose>
value_escaped=<report-safe-text>
```

The existing `escape_report_string` helper must remain the report-safe representation layer.

## Successful parse rule

Decoding must run only after:

```text
latticra_l_ui_parse_source
```

returns `LATTICRA_STATUS_OK` and `parse_result.error == LATTICRA_L_UI_PARSE_OK`.

If parsing fails structurally, decoding must not run.

## Failed parse compatibility

Existing failed parse behavior must remain unchanged:

```text
ast.parse_result.error = parser error
ast.rail_count = 0
ast.field_count = 0
ast.text_count = 0
failed-parse detailed report only
```

String decoding must not hide or replace existing structural parser errors.

## Compatibility expectations

String-literal escape decoding must not change:

```text
latticra_l_ui_parse_source existing accepted fixture behavior
latticra_l_ui_ast_report existing required fields
latticra_l_ui_ast_detailed_report existing required fields
latticra_l_ui_diagnostic_report existing required fields
parser error labels
existing escaped report field semantics
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

Fixtures without source escapes must produce the same AST values they produced before this implementation.

## No-effect preservation

String-literal escape decoding is metadata-only and must preserve:

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

Invalid escape tests should assert AST classification through:

```text
LATTICRA_L_UI_PARSE_INTERNAL_ERROR
```

until parser-level string escape diagnostics are designed.

## Test file plan

Add:

```text
tests/l_ui_string_literal_escape_invariants.c
scripts/test-l-ui-string-literal-escape.sh
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
docs/L_UI_STRING_LITERAL_ESCAPE_CONTRACT.md
docs/L_UI_AST_SOURCE_BACKED_TEXT_IMPLEMENTATION.md
docs/L_UI_AST_ESCAPED_STRING_REPORT_IMPLEMENTATION.md
docs/L_UI_PARSER_AST_IMPLEMENTATION.md
```

and add:

```text
docs/L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION.md
```

## Forbidden implementation behavior

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
- decode bindings, field names, rail names, card names, effect values, or boundary values in this slice;
- broaden accepted grammar beyond the string-literal escape contract;
- add parser-level escape diagnostics without a parser diagnostics contract;
- add length-carrying AST string storage without a storage contract.

## Current validation command

This plan is guarded by:

```sh
sh scripts/test-l-ui-string-literal-escape-implementation-plan.sh
```

The guard is static. It does not implement string-literal escape decoding.

## Implementation gate

String-literal escape decoding implementation code may be added only after this plan is merged.

## Non-claims

This document does not implement string-literal escape decoding, implement parser-level escape diagnostics, implement length-carrying AST strings, broaden accepted non-string L-UI grammar, implement Unicode display behavior, add L-UI rendering, add command behavior, add Nucleus task handling, add live movement, add origin mutation, add recovery behavior, add server interaction, add self-update, add hardware support, add boot readiness, claim security isolation, claim sandboxing, or claim operating-system completeness.
