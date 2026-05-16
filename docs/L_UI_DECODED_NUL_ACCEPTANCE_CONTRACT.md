# Latticra L-UI Decoded NUL Acceptance Contract

Status: decoded NUL acceptance contract
Scope: future acceptance of escaped decoded NUL bytes in L-UI source-backed AST strings after length-carrying AST string storage.

## Purpose

This document defines the contract for accepting escaped decoded NUL bytes in L-UI source-backed AST string values.

The current parser rejects:

```text
\x00 -> LATTICRA_L_UI_PARSE_DECODED_NUL_IN_STRING
literal 0x00 -> LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING
```

Now that AST purpose and text values carry explicit decoded byte lengths, a future implementation may accept escaped `\x00` in quoted string values while continuing to reject literal NUL bytes in source buffers.

This document does not implement decoded NUL acceptance.

The implementation plan is documented separately in [`L_UI_DECODED_NUL_ACCEPTANCE_IMPLEMENTATION_PLAN.md`](L_UI_DECODED_NUL_ACCEPTANCE_IMPLEMENTATION_PLAN.md).

## Relationship to previous work

This contract depends on:

```text
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

Those files remain the source of truth for explicit string lengths, parser diagnostics, string-literal escape decoding, detailed reports, and no-effect behavior.

## Current boundary

The current system provides:

```text
purpose_len and value_len fields
length-aware escaped detailed report fields
source-backed AST purpose and text values
accepted string-literal escape decoding
parser-level invalid string escape diagnostics
literal NUL rejection
no-effect flags
```

This contract does not add:

```text
decoded NUL acceptance implementation
literal NUL acceptance
new accepted escape sequences beyond \x00 behavior change
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

## Acceptance decision

A future implementation may accept escaped decoded NUL bytes only through the existing uppercase hex escape form:

```text
\x00
```

Accepted source examples:

```text
purpose "A\x00B"
text "left\x00right"
```

The decoded AST byte sequence should contain the NUL byte at that position, and the explicit length field should include that byte.

## Literal NUL remains rejected

Literal `0x00` bytes in the source buffer remain rejected.

A source buffer containing a literal NUL inside a quoted value should continue to report:

```text
LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING
LUI0023 literal_nul_in_string
```

Reason:

- source buffers are still byte-oriented input;
- literal NUL bytes make source inspection and tool interop ambiguous;
- escaped NUL is deterministic and operator-visible in reports;
- accepting literal NUL requires a separate source-buffer contract.

## Parser diagnostic transition

A future implementation should stop reporting this diagnostic for escaped `\x00` in source-backed string values:

```text
LATTICRA_L_UI_PARSE_DECODED_NUL_IN_STRING
LUI0022 decoded_nul_in_string
```

`LUI0022` must remain a stable diagnostic code for compatibility, but escaped `\x00` in supported L-UI string values should no longer trigger it after decoded-NUL acceptance is implemented.

`LUI0023 literal_nul_in_string` remains active.

## Accepted escape compatibility

Decoded NUL acceptance must not broaden the accepted escape set beyond the existing contract:

```text
\\
\"
\n
\r
\t
\xNN
```

where `\xNN` uses exactly two uppercase hexadecimal digits.

Lowercase hex remains rejected:

```text
\x0a -> LATTICRA_L_UI_PARSE_INVALID_HEX_ESCAPE
```

Unknown escapes remain rejected:

```text
\a -> LATTICRA_L_UI_PARSE_INVALID_STRING_ESCAPE
```

## AST storage behavior

After implementation, escaped decoded NUL bytes should be represented in the existing AST buffers and lengths:

```text
ast.card.purpose
ast.card.purpose_len
ast.texts[index].value
ast.texts[index].value_len
```

For values containing decoded NUL bytes:

```text
purpose_len != strlen(purpose)
value_len != strlen(value)
```

The explicit length field is authoritative.

The compatibility C-string buffer remains present, but `strlen` must not be used to inspect the full value when embedded NUL bytes exist.

## Decode helper behavior

The private string-literal decode helper should allow decoded byte value `0x00` only when it came from escaped `\x00`.

It should still reject literal source NUL bytes before decoding materializes a value.

Decoded length assignment must count decoded NUL bytes:

```text
"A\x00B" -> length 3
```

## Parser validation order

Decoded NUL acceptance should preserve existing validation order:

1. null argument checks;
2. source size checks;
3. structural parse checks;
4. string escape validation;
5. AST construction.

Structural parse errors must retain priority over decoded-NUL acceptance.

## Source-span behavior

Source spans remain source-oriented.

For escaped decoded NUL:

```text
\x00 -> source span covers four source bytes when a diagnostic or test inspects that source range
```

Accepted AST text spans continue to cover the full source value range between quotes.

Decoded output byte positions are not source spans.

## Detailed report behavior

Detailed AST reports must use explicit lengths and escaped output as the stable inspection surface.

For decoded NUL bytes, escaped report fields should render:

```text
\x00
```

Examples:

```text
purpose_len=3
purpose_escaped=A\x00B

value_len=10
value_escaped=left\x00right
```

Raw C-string fields remain compatibility fields:

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

## Compact report compatibility

The compact AST report should remain unchanged in the first decoded-NUL acceptance implementation.

Detailed reports are the stable inspection surface for embedded NUL bytes.

## AST compatibility behavior

Failed parse behavior remains unchanged:

```text
ast.parse_result.error = parser error
ast.rail_count = 0
ast.field_count = 0
ast.text_count = 0
failed-parse detailed report only
```

Accepted sources should continue to produce the same rail, field, and text counts.

The first accepted fixture should still report:

```text
rail_count=9
field_count=23
text_count=2
effect=none
boundary=preview_only
```

## No-effect rule

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

## Implementation gate

Decoded NUL acceptance implementation must not begin until a separate implementation plan defines:

1. parser validation changes;
2. decode helper changes;
3. AST storage expectations;
4. report expectations;
5. diagnostic compatibility behavior;
6. source-span expectations;
7. exact test file names;
8. exact invariant tests;
9. compatibility expectations;
10. non-claims.

That plan is recorded in [`L_UI_DECODED_NUL_ACCEPTANCE_IMPLEMENTATION_PLAN.md`](L_UI_DECODED_NUL_ACCEPTANCE_IMPLEMENTATION_PLAN.md).

## Future test list

A future implementation plan should include tests for:

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

## Forbidden behavior

A future decoded NUL acceptance implementation must not:

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

This contract is guarded by:

```sh
sh scripts/test-l-ui-decoded-nul-acceptance-contract.sh
```

The guard is static. It does not implement decoded NUL acceptance.

## Non-claims

This document does not implement decoded NUL acceptance, accept literal NUL bytes, broaden accepted L-UI syntax, implement Unicode display behavior, add L-UI rendering, add command behavior, add Nucleus task handling, add live movement, add origin mutation, add recovery behavior, add server interaction, add self-update, add hardware support, add boot readiness, claim security isolation, claim sandboxing, or claim operating-system completeness.
