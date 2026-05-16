# Latticra L-UI AST Length-Carrying String Storage Implementation

Status: initial implementation contract
Scope: explicit decoded byte lengths for L-UI AST purpose and text values.

## Purpose

The L-UI AST Length-Carrying String Storage implementation adds explicit decoded byte lengths for source-backed AST string values while preserving the existing C-string compatibility buffers.

The implementation makes decoded byte lengths available for:

```text
latticra_l_ui_ast_card_t.purpose
latticra_l_ui_ast_text_t.value
```

without accepting decoded NUL bytes, broadening accepted escapes, or changing parser execution boundaries.

## Implementation files

```text
include/latticra/l_ui_parser.h
src/l_ui_parser_ast.c
tests/l_ui_ast_length_carrying_string_storage_invariants.c
scripts/test-l-ui-ast-length-carrying-string-storage.sh
```

Related active files:

```text
src/l_ui_parser.c
src/l_ui_parser_diagnostics.c
tests/l_ui_string_literal_escape_invariants.c
scripts/test-l-ui-string-literal-escape.sh
```

## Public struct additions

The implementation extends public AST structs with:

```text
latticra_l_ui_ast_card_t.purpose_len
latticra_l_ui_ast_text_t.value_len
```

Struct relationship:

```text
char purpose[LATTICRA_L_UI_AST_PURPOSE_MAX];
size_t purpose_len;

char value[LATTICRA_L_UI_AST_PURPOSE_MAX];
size_t value_len;
```

The length fields store decoded byte counts and do not include the trailing compatibility NUL byte.

## Public API compatibility

No new public function is added.

Existing public C-string fields remain:

```text
latticra_l_ui_ast_card_t.purpose
latticra_l_ui_ast_text_t.value
```

For decoded strings that do not contain NUL bytes:

```text
purpose_len == strlen(purpose)
value_len == strlen(value)
```

## Default initialization

`ast_default` initializes all string lengths to zero:

```text
ast.card.purpose_len = 0
ast.texts[index].value_len = 0
```

Failed parse AST results keep all AST string lengths at zero.

## Source-backed extraction length assignment

Source-backed extraction now assigns decoded lengths while materializing AST values:

```text
purpose "..." -> ast.card.purpose + ast.card.purpose_len
first text "..." -> ast.texts[0].value + ast.texts[0].value_len
second text "..." -> ast.texts[1].value + ast.texts[1].value_len
```

The decode path reports decoded byte counts from the same output index used to populate the destination buffer.

## Decode helper behavior

The private string-literal decode helper now reports decoded length through an output pointer:

```text
size_t *decoded_len
```

`decoded_len` is set to zero before decoding and set to the decoded byte count only on successful decoding.

Accepted escape decoding remains unchanged:

```text
\\
\"
\n
\r
\t
\xNN
```

where `\xNN` uses exactly two uppercase hexadecimal digits.

## Capacity behavior

Capacity remains bounded by:

```text
LATTICRA_L_UI_AST_PURPOSE_MAX
```

for purpose and text values.

A decoded value fits only when:

```text
decoded_len < destination_len
```

because the compatibility C string still needs a trailing NUL byte.

Oversized decoded values continue to be rejected by parser diagnostics as:

```text
LATTICRA_L_UI_PARSE_STRING_VALUE_TOO_LARGE
```

## NUL behavior

This implementation does not accept decoded or literal NUL bytes.

Parser-level diagnostics continue to reject:

```text
\x00 -> LATTICRA_L_UI_PARSE_DECODED_NUL_IN_STRING
literal 0x00 -> LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING
```

The decoded-NUL acceptance contract is recorded in:

```text
L_UI_DECODED_NUL_ACCEPTANCE_CONTRACT.md
```

A later decoded-NUL acceptance implementation may change escaped `\x00` behavior, but not literal source NUL rejection.

## Detailed report behavior

Detailed AST reports now include explicit length fields:

```text
purpose_len=<decoded-purpose-byte-length>
value_len=<decoded-text-byte-length>
```

Card section placement:

```text
[card]
kind=card
name=<name>
purpose=<purpose>
purpose_len=<purpose_len>
purpose_escaped=<purpose_escaped>
```

Text section placement:

```text
[text N]
kind=text
value=<value>
value_len=<value_len>
value_escaped=<value_escaped>
```

Existing field names remain stable.

## Length-aware escaped report behavior

The escaped report helper is byte-oriented and length-aware:

```text
escape_report_bytes(input, input_len, output, output_len)
```

Detailed report callers pass explicit AST lengths instead of `strlen` for purpose and text values.

For current non-NUL values, escaped report behavior remains compatible with previous output.

## Compact AST report compatibility

The compact AST report remains unchanged:

```text
latticra_l_ui_ast_report
```

The detailed AST report gains length fields.

Failed-parse detailed reports remain unchanged and do not include string length fields.

## Parser diagnostics compatibility

The implementation does not change existing parser diagnostics.

These diagnostics remain active:

```text
LUI0019 invalid_string_escape
LUI0020 invalid_hex_escape
LUI0021 unterminated_escape
LUI0022 decoded_nul_in_string
LUI0023 literal_nul_in_string
LUI0024 string_value_too_large
```

Decoded-NUL and literal-NUL rejection remain active.

## Source-span behavior

Source spans remain source-oriented.

Text spans continue to cover the source value range between quotes, not decoded output byte ranges.

For example, source `\n` covers two source bytes while the decoded AST value length is one byte for that escape.

No public `purpose_span` field is added.

## Compatibility

The implementation does not change:

```text
accepted string-literal escape decoding
parser-level invalid string escape diagnostics
existing diagnostic codes LUI0000 through LUI0024
existing parser error labels for current errors
latticra_l_ui_ast_report existing required fields
latticra_l_ui_diagnostic_report existing required fields
existing accepted fixture summary counts
failed-parse detailed report behavior
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

Length-carrying AST string storage is metadata-only.

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
sh scripts/test-l-ui-ast-length-carrying-string-storage.sh
```

The main C workflow runs this check after the length-carrying string storage implementation-plan guard.

## Required invariants

The length-carrying AST string storage tests verify:

```text
ast_string_storage_sets_purpose_len
ast_string_storage_sets_text_value_len
ast_string_storage_len_matches_strlen_for_non_nul_values
ast_string_storage_len_tracks_decoded_newline
ast_string_storage_len_tracks_decoded_tab
ast_string_storage_len_tracks_decoded_high_byte_hex
ast_string_storage_preserves_existing_c_string_fields
ast_string_storage_updates_detailed_report_lengths
ast_string_storage_escaped_report_uses_explicit_lengths
ast_string_storage_still_rejects_decoded_nul_until_acceptance_contract
ast_string_storage_still_rejects_literal_nul_until_acceptance_contract
ast_string_storage_still_rejects_oversized_decoded_output
ast_string_storage_preserves_source_spans
ast_string_storage_preserves_no_effect_flags
ast_string_storage_does_not_change_existing_diagnostic_codes
ast_string_storage_does_not_change_failed_parse_report
ast_string_storage_is_deterministic
```

## Current evidence level

This implementation is an L2 tested AST string metadata model for explicit decoded byte lengths.

It is not decoded-NUL acceptance, literal-NUL acceptance, a Unicode display model, renderer, UI runtime, command surface, Nucleus task runner, server client, update engine, recovery system, hardware system, boot system, sandbox, or operating system.

## Next implementation step

The decoded-NUL acceptance contract is recorded in:

```text
L_UI_DECODED_NUL_ACCEPTANCE_CONTRACT.md
```

The next implementation candidate after that contract is:

```text
L-UI decoded-NUL acceptance implementation plan
```

That future work should define parser validation changes, decode helper changes, AST storage expectations, report expectations, diagnostic compatibility behavior, source-span expectations, and exact invariant tests before accepting escaped `\x00`.

## Non-claims

This document and implementation do not accept decoded NUL bytes, accept literal NUL bytes, broaden accepted L-UI syntax, implement Unicode display behavior, add L-UI rendering, add command behavior, add Nucleus task handling, add live movement, add origin mutation, add recovery behavior, add server interaction, add self-update, add hardware support, add boot readiness, claim security isolation, claim sandboxing, or claim operating-system completeness.
