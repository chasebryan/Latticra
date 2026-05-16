# Latticra L-UI Decoded NUL Acceptance Implementation Plan

Status: implementation planning contract
Scope: parser validation changes, decode helper changes, AST storage expectations, report expectations, diagnostic compatibility behavior, source-span expectations, exact test files, and exact invariant tests before escaped decoded NUL acceptance code.

## Purpose

This document defines the implementation plan for accepting escaped decoded NUL bytes in L-UI source-backed AST string values.

The decoded-NUL acceptance contract is already merged and guarded. This plan decides the exact parser validation changes, private decode helper behavior, AST storage expectations, detailed report expectations, diagnostic compatibility behavior, source-span expectations, and test coverage before implementation code is added.

This document does not implement decoded NUL acceptance.

## Relationship to previous contracts

This plan depends on:

```text
docs/L_UI_DECODED_NUL_ACCEPTANCE_CONTRACT.md
docs/L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_CONTRACT.md
docs/L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_IMPLEMENTATION_PLAN.md
docs/L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_IMPLEMENTATION.md
docs/L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_IMPLEMENTATION.md
docs/L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION.md
include/latticra/l_ui_parser.h
src/l_ui_parser.c
src/l_ui_parser_ast.c
src/l_ui_parser_diagnostics.c
```

Those files remain the source of truth for explicit AST string lengths, parser diagnostics, string-literal escape decoding, detailed reports, and no-effect behavior.

## Implementation language decision

Decoded NUL acceptance should be implemented in C.

Reason:

- parser validation lives in `src/l_ui_parser.c`;
- AST decoding lives in `src/l_ui_parser_ast.c`;
- diagnostics live in `src/l_ui_parser_diagnostics.c`;
- the public AST API is C;
- the change is byte-oriented, bounded, deterministic, and no-effect.

## Acceptance scope

The implementation should accept only escaped decoded NUL through uppercase hex syntax:

```text
\x00
```

Accepted sources after implementation:

```text
purpose "A\x00B"
text "left\x00right"
```

Literal source NUL bytes remain rejected.

## Parser validation changes

Update private string escape validation in:

```text
src/l_ui_parser.c
```

The parser currently maps escaped `\x00` to:

```text
LATTICRA_L_UI_PARSE_DECODED_NUL_IN_STRING
```

The implementation should change parser validation so escaped `\x00` in supported source-backed string values is accepted and counted as one decoded byte.

The parser must continue to reject literal source NUL bytes as:

```text
LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING
```

## Parser diagnostic compatibility

Do not remove existing parser errors or diagnostic codes:

```text
LATTICRA_L_UI_PARSE_DECODED_NUL_IN_STRING
LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING
LUI0022 decoded_nul_in_string
LUI0023 literal_nul_in_string
```

After implementation:

```text
\x00 -> accepted in source-backed string values
literal 0x00 -> LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING
```

`LUI0022` remains reserved and stable, but should not be emitted for accepted escaped `\x00` in supported string values.

## Decode helper changes

Update private string-literal decoding in:

```text
src/l_ui_parser_ast.c
```

The helper currently rejects decoded byte `0x00` through the same capacity/error path used for invalid output.

The implementation should allow decoded byte `0x00` when and only when it is produced by escaped `\x00`.

It must still reject literal source NUL bytes before value materialization.

Decoded length assignment must count decoded NUL bytes:

```text
"A\x00B" -> decoded bytes: A, 0x00, B -> length 3
```

## AST storage expectations

Use the existing length-carrying fields:

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

Existing C-string buffers remain compatibility buffers and should contain the decoded bytes plus a trailing compatibility NUL. Consumers that use `strlen` will see the prefix before the first embedded NUL.

## C-string prefix compatibility

For decoded value:

```text
A\x00B
```

Expected compatibility behavior:

```text
purpose[0] == 'A'
purpose[1] == '\0'
purpose[2] == 'B'
purpose_len == 3
strlen(purpose) == 1
```

The same rule applies to text values.

## Report expectations

Detailed AST reports should remain the authoritative inspection surface for embedded NUL values.

For purpose:

```text
purpose_len=3
purpose_escaped=A\x00B
```

For text:

```text
value_len=10
value_escaped=left\x00right
```

Raw fields remain compatibility fields only:

```text
purpose=<C-string-compatible-prefix>
value=<C-string-compatible-prefix>
```

Tests for embedded NUL must assert against:

```text
purpose_len
purpose_escaped
value_len
value_escaped
```

not raw `purpose=` or `value=` fields.

## Escaped report helper expectations

The current length-aware helper:

```text
escape_report_bytes(input, input_len, output, output_len)
```

already accepts explicit lengths.

The implementation must ensure callers pass:

```text
ast.card.purpose_len
ast.texts[index].value_len
```

for purpose and text values.

The helper should render embedded decoded NUL as:

```text
\x00
```

## Source-span expectations

Source spans remain source-oriented.

Accepted AST text spans continue to cover the full source value range between quotes.

A decoded NUL produced by source bytes `\x00` counts as one decoded byte but four source bytes.

No public decoded-byte span field is added.

## Parser validation order

Preserve the current validation order:

1. null argument checks;
2. source size checks;
3. structural parse checks;
4. string escape validation;
5. AST construction.

Structural parse errors must retain priority over decoded-NUL acceptance.

## Accepted escape compatibility

Do not broaden the accepted escape set.

Still accepted:

```text
\\
\"
\n
\r
\t
\xNN
```

where `\xNN` uses exactly two uppercase hexadecimal digits.

Still rejected:

```text
\x0a -> LATTICRA_L_UI_PARSE_INVALID_HEX_ESCAPE
\a -> LATTICRA_L_UI_PARSE_INVALID_STRING_ESCAPE
literal 0x00 -> LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING
```

## Compact report compatibility

The compact AST report:

```text
latticra_l_ui_ast_report
```

should remain unchanged.

Detailed AST reports are the stable inspection surface for embedded NUL values.

## Failed parse compatibility

Failed parse behavior remains unchanged:

```text
ast.parse_result.error = parser error
ast.rail_count = 0
ast.field_count = 0
ast.text_count = 0
failed-parse detailed report only
```

## Fixture compatibility

The first accepted fixture should still report:

```text
rail_count=9
field_count=23
text_count=2
effect=none
boundary=preview_only
```

## No-effect preservation

Decoded NUL acceptance is metadata-only.

It must preserve:

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

## Test file plan

Add:

```text
tests/l_ui_decoded_nul_acceptance_invariants.c
scripts/test-l-ui-decoded-nul-acceptance.sh
```

Wire into:

```text
.github/workflows/c.yml
```

Run after:

```text
sh scripts/test-l-ui-decoded-nul-acceptance-contract.sh
```

and before:

```text
sh scripts/test-l-ui-string-literal-escape-contract.sh
```

## Documentation requirement

The implementation PR should update:

```text
README.md
docs/FOUNDATION_INDEX.md
docs/L_UI_DECODED_NUL_ACCEPTANCE_CONTRACT.md
docs/L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_IMPLEMENTATION.md
docs/L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_IMPLEMENTATION.md
docs/L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION.md
```

and add:

```text
docs/L_UI_DECODED_NUL_ACCEPTANCE_IMPLEMENTATION.md
```

## Forbidden implementation behavior

The decoded NUL acceptance implementation must not:

- accept literal NUL source bytes;
- accept lowercase hex escapes;
- accept unknown escapes;
- broaden accepted escape forms;
- remove `LUI0022` from the diagnostic code table;
- remove `LUI0023` literal NUL rejection;
- remove existing C-string fields;
- make raw `purpose=` or `value=` report fields the assertion target for embedded NUL bytes;
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
- treat bindings as executable references.

## Current validation command

This plan is guarded by:

```sh
sh scripts/test-l-ui-decoded-nul-acceptance-implementation-plan.sh
```

The guard is static. It does not implement decoded NUL acceptance.

## Implementation gate

Decoded NUL acceptance implementation code may be added only after this plan is merged.

## Non-claims

This document does not implement decoded NUL acceptance, accept literal NUL bytes, broaden accepted L-UI syntax, implement Unicode display behavior, add L-UI rendering, add command behavior, add Nucleus task handling, add live movement, add origin mutation, add recovery behavior, add server interaction, add self-update, add hardware support, add boot readiness, claim security isolation, claim sandboxing, or claim operating-system completeness.
