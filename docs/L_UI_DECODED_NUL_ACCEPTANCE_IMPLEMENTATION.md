# Latticra L-UI Decoded NUL Acceptance Implementation

Status: initial implementation contract
Scope: escaped decoded NUL acceptance for L-UI source-backed AST strings.

## Purpose

The L-UI Decoded NUL Acceptance implementation accepts escaped decoded NUL bytes in source-backed AST string values through the existing uppercase hex escape syntax:

```text
\x00
```

The implementation relies on the explicit decoded byte lengths added by the L-UI AST length-carrying string storage implementation.

It accepts escaped decoded NUL bytes while continuing to reject literal NUL bytes in source buffers.

## Implementation files

```text
src/l_ui_parser.c
src/l_ui_parser_ast.c
tests/l_ui_decoded_nul_acceptance_invariants.c
scripts/test-l-ui-decoded-nul-acceptance.sh
```

Related active files:

```text
include/latticra/l_ui_parser.h
src/l_ui_parser_diagnostics.c
tests/l_ui_parser_string_escape_diagnostics_invariants.c
tests/l_ui_ast_length_carrying_string_storage_invariants.c
tests/l_ui_string_literal_escape_invariants.c
```

## Accepted form

Only escaped decoded NUL through uppercase hex is accepted:

```text
\x00
```

Accepted examples:

```text
purpose "A\x00B"
text "left\x00right"
```

The decoded byte sequence contains `0x00` at the escape position.

## Literal NUL remains rejected

Literal `0x00` bytes in the source buffer remain rejected.

Literal NUL still reports:

```text
LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING
LUI0023 literal_nul_in_string
```

This implementation does not add a source-buffer literal-NUL acceptance model.

## Parser validation behavior

Parser validation in:

```text
src/l_ui_parser.c
```

no longer reports:

```text
LATTICRA_L_UI_PARSE_DECODED_NUL_IN_STRING
```

for escaped `\x00` in supported source-backed string values.

The parser still rejects:

```text
\x0a -> LATTICRA_L_UI_PARSE_INVALID_HEX_ESCAPE
\a -> LATTICRA_L_UI_PARSE_INVALID_STRING_ESCAPE
literal 0x00 -> LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING
```

## Diagnostic compatibility

The implementation keeps existing parser errors and diagnostic codes stable:

```text
LATTICRA_L_UI_PARSE_DECODED_NUL_IN_STRING
LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING
LUI0022 decoded_nul_in_string
LUI0023 literal_nul_in_string
```

`LUI0022` remains available as a stable diagnostic mapping, but escaped `\x00` no longer emits it from real supported L-UI string input.

`LUI0023` remains active for literal source NUL.

## AST storage behavior

Escaped decoded NUL bytes are stored in the existing AST byte buffers and counted by explicit lengths:

```text
ast.card.purpose
ast.card.purpose_len
ast.texts[index].value
ast.texts[index].value_len
```

For embedded NUL values:

```text
purpose_len != strlen(purpose)
value_len != strlen(value)
```

The explicit length field is authoritative.

## C-string prefix compatibility

For decoded value:

```text
A\x00B
```

The AST stores:

```text
purpose[0] == 'A'
purpose[1] == '\0'
purpose[2] == 'B'
purpose_len == 3
strlen(purpose) == 1
```

The same rule applies to text values.

## Decode helper behavior

The AST string decode helper in:

```text
src/l_ui_parser_ast.c
```

now allows decoded byte `0x00` when it is produced by escaped `\x00`.

The helper still rejects literal source NUL bytes before value materialization.

Decoded length assignment counts decoded NUL bytes:

```text
"A\x00B" -> decoded bytes: A, 0x00, B -> length 3
```

## Detailed report behavior

Detailed AST reports use explicit lengths and escaped output as the stable inspection surface.

Purpose example:

```text
purpose_len=3
purpose_escaped=A\x00B
```

Text example:

```text
value_len=10
value_escaped=left\x00right
```

Raw C-string compatibility fields remain prefix-oriented:

```text
purpose=<C-string-compatible-prefix>
value=<C-string-compatible-prefix>
```

Embedded-NUL tests assert against:

```text
purpose_len
purpose_escaped
value_len
value_escaped
```

not raw `purpose=` or `value=` fields.

## Compact report compatibility

The compact AST report remains unchanged:

```text
latticra_l_ui_ast_report
```

Detailed reports remain the stable inspection surface for embedded NUL values.

## Source-span behavior

Source spans remain source-oriented.

A decoded NUL produced by source bytes `\x00` counts as one decoded byte but four source bytes.

Accepted AST text spans continue to cover the full source value range between quotes.

No public decoded-byte span field is added.

## Validation order

The implementation preserves validation order:

1. null argument checks;
2. source size checks;
3. structural parse checks;
4. string escape validation;
5. AST construction.

Structural parse errors retain priority over decoded-NUL acceptance.

## Compatibility

The implementation does not change:

```text
accepted escape forms other than \x00 behavior
parser diagnostic code stability
literal source NUL rejection
lowercase hex rejection
unknown escape rejection
existing C-string fields
compact AST report fields
failed-parse detailed report behavior
existing accepted fixture counts
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

Decoded NUL acceptance is metadata-only.

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
sh scripts/test-l-ui-decoded-nul-acceptance.sh
```

The main C workflow runs this check after the decoded-NUL acceptance implementation-plan guard and before the string-literal escape guards.

## Required invariants

The decoded-NUL acceptance tests verify:

```text
decoded_nul_accepts_purpose_x00
decoded_nul_accepts_text_x00
decoded_nul_counts_purpose_len
decoded_nul_counts_text_value_len
decoded_nul_preserves_c_string_prefix_compatibility
decoded_nul_reports_purpose_escaped_x00
decoded_nul_reports_text_value_escaped_x00
decoded_nul_does_not_emit_lui0022_for_x00
decoded_nul_still_rejects_literal_nul_lui0023
decoded_nul_still_rejects_lowercase_hex_lui0020
decoded_nul_still_rejects_unknown_escape_lui0019
decoded_nul_preserves_source_spans
decoded_nul_preserves_no_effect_flags
decoded_nul_does_not_change_failed_parse_report
decoded_nul_is_deterministic
```

## Current evidence level

This implementation is an L2 tested decoded-byte storage and reporting model for escaped decoded NUL bytes in L-UI source-backed AST strings.

It is not literal source NUL acceptance, Unicode display behavior, renderer behavior, UI runtime behavior, command behavior, Nucleus task execution, server interaction, update behavior, recovery behavior, hardware behavior, boot behavior, sandboxing, or an operating system.

## Next implementation step

The next implementation candidate is:

```text
L-UI source-buffer literal NUL policy contract
```

That future work should decide whether literal NUL bytes in source buffers remain permanently forbidden or receive their own length-aware source input policy.

## Non-claims

This document and implementation do not accept literal NUL bytes, broaden accepted L-UI syntax beyond escaped decoded NUL behavior, implement Unicode display behavior, add L-UI rendering, add command behavior, add Nucleus task handling, add live movement, add origin mutation, add recovery behavior, add server interaction, add self-update, add hardware support, add boot readiness, claim security isolation, claim sandboxing, or claim operating-system completeness.
