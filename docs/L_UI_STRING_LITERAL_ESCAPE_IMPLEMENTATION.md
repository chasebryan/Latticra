# Latticra L-UI String-Literal Escape Implementation

Status: initial implementation contract
Scope: byte-oriented string-literal escape decoding for source-backed L-UI AST purpose and text values.

## Purpose

The L-UI String-Literal Escape implementation decodes accepted escape sequences in quoted L-UI source strings while materializing AST-owned metadata values.

This implementation keeps decoding bounded, deterministic, source-span aware, and no-effect. It does not add rendering behavior, command behavior, parser-level string escape diagnostics, Unicode display semantics, or length-carrying AST strings.

## Implementation files

```text
src/l_ui_parser_ast.c
tests/l_ui_string_literal_escape_invariants.c
scripts/test-l-ui-string-literal-escape.sh
```

Related source-backed extraction files remain active:

```text
tests/l_ui_ast_source_backed_text_invariants.c
scripts/test-l-ui-ast-source-backed-text.sh
```

## Public API decision

No new public function is added.

Decoding is integrated into:

```text
latticra_l_ui_parse_ast
```

The public AST storage remains:

```text
latticra_l_ui_ast_card_t.purpose
latticra_l_ui_ast_text_t.value
```

No new public parser error enum value is added in this slice.

## Private helper implementation

The implementation adds private helpers in `src/l_ui_parser_ast.c`:

```text
is_upper_hex_digit
upper_hex_value
append_decoded_byte
decode_l_ui_string_literal_value
extract_decoded_quoted_value_after_token
```

These helpers remain private and are used only while constructing AST string values.

## Decoding targets

The implementation decodes only source-backed AST string values:

```text
purpose "..." -> ast.card.purpose
first text "..." -> ast.texts[0].value
second text "..." -> ast.texts[1].value
```

It does not decode:

```text
card names
rail names
field names
binding values
effect values
boundary values
```

## Accepted escape behavior

The implementation accepts only this escape set:

```text
\\
\"
\n
\r
\t
\xNN
```

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

The `\xNN` form requires exactly two uppercase hexadecimal digits.

## Rejected escape behavior

The implementation rejects unknown, malformed, incomplete, and lowercase-hex escapes, including:

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

Rejected escape sequences are not copied literally.

## NUL byte behavior

Decoded NUL bytes are rejected in this implementation.

This includes:

```text
\x00
```

Literal `0x00` source bytes inside AST string values are also rejected.

Reason:

```text
latticra_l_ui_ast_card_t.purpose
latticra_l_ui_ast_text_t.value
```

are NUL-terminated fixed-size C strings and do not carry explicit decoded lengths.

## Capacity behavior

Decoded output must fit the destination buffer.

If decoded output length is greater than or equal to the destination capacity, decoding fails and clears the destination buffer when possible.

The implementation does not silently truncate decoded values.

## AST failure behavior

When string-literal escape decoding fails, AST construction returns:

```text
LATTICRA_STATUS_OK
```

and classifies the AST parse result as:

```text
LATTICRA_L_UI_PARSE_INTERNAL_ERROR
```

The AST avoids partial output:

```text
ast.rail_count = 0
ast.field_count = 0
ast.text_count = 0
ast.card.rail_count = 0
ast.card.field_count = 0
ast.card.text_count = 0
```

This preserves the current parser API until parser-level string escape diagnostics are designed.

## Source-span behavior

Source spans remain source-oriented.

For text nodes:

```text
text.span covers the source value range between quotes
```

If the source contains `\n`, the span covers the two source bytes `\` and `n`, even though the AST value contains one LF byte.

No public `purpose_span` field is added.

## Detailed report relationship

Detailed reports continue to render:

```text
purpose=<decoded-purpose-as-current-C-string>
purpose_escaped=<report-safe-purpose>
value=<decoded-text-as-current-C-string>
value_escaped=<report-safe-text>
```

For decoded control bytes, quote bytes, backslashes, DEL, and non-ASCII bytes, the stable assertion target is the escaped report field.

The existing report escaping layer remains responsible for deterministic report-safe string output.

## Parser compatibility

The structural parser remains unchanged for this slice.

`latticra_l_ui_parse_source` does not perform string-literal escape validation yet.

Invalid escape sequences found during AST construction classify the AST as:

```text
LATTICRA_L_UI_PARSE_INTERNAL_ERROR
```

until a future parser diagnostics contract promotes them to first-class parser errors.

## Failed parse compatibility

Existing failed parse behavior remains unchanged:

```text
ast.parse_result.error = parser error
ast.rail_count = 0
ast.field_count = 0
ast.text_count = 0
failed-parse detailed report only
```

String decoding does not run for structurally failed parses.

## No-effect boundary

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

## Test command

Run:

```sh
sh scripts/test-l-ui-string-literal-escape.sh
```

The main C workflow runs this check after the string-literal escape implementation-plan guard.

## Required invariants

The string-literal escape tests verify:

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

## Current evidence level

This implementation is an L2 tested string-literal escape decoding model for validated L-UI AST metadata.

It is not a parser-level string escape diagnostic system, Unicode display model, renderer, UI runtime, command surface, Nucleus task runner, server client, update engine, recovery system, hardware system, boot system, sandbox, or operating system.

## Next implementation step

The next implementation candidate is:

```text
L-UI parser-level string escape diagnostics contract
```

That future work should decide whether invalid escapes receive specific parser errors, diagnostic codes, source spans, messages, and hints instead of AST-level internal-error classification.

## Non-claims

This document and implementation do not implement parser-level escape diagnostics, implement length-carrying AST strings, broaden accepted non-string L-UI grammar, implement Unicode display behavior, add L-UI rendering, add command behavior, add Nucleus task handling, add live movement, add origin mutation, add recovery behavior, add server interaction, add self-update, add hardware support, add boot readiness, claim security isolation, claim sandboxing, or claim operating-system completeness.
