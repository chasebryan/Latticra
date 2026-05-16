# Latticra L-UI AST Length-Carrying String Storage Contract

Status: AST string storage contract
Scope: future explicit decoded byte lengths for L-UI AST purpose and text values before AST string storage is extended.

## Purpose

This document defines the contract for length-carrying AST string storage in L-UI.

Current AST string storage uses fixed-size NUL-terminated C strings:

```text
latticra_l_ui_ast_card_t.purpose
latticra_l_ui_ast_text_t.value
```

That storage model cannot represent decoded NUL bytes or safely report byte-oriented decoded values that contain embedded NUL. This contract defines the future public storage shape, compatibility rules, report rules, decoding relationship, and no-effect boundary before implementation code is added.

This document does not implement length-carrying AST strings.

The implementation plan is documented separately in [`L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_IMPLEMENTATION_PLAN.md`](L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_IMPLEMENTATION_PLAN.md).

## Relationship to previous work

This contract depends on:

```text
docs/L_UI_PARSER_AST_IMPLEMENTATION.md
docs/L_UI_AST_SOURCE_BACKED_TEXT_IMPLEMENTATION.md
docs/L_UI_AST_ESCAPED_STRING_REPORT_IMPLEMENTATION.md
docs/L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION.md
docs/L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_IMPLEMENTATION.md
include/latticra/l_ui_parser.h
src/l_ui_parser_ast.c
src/l_ui_parser.c
src/l_ui_parser_diagnostics.c
```

Those files remain the current source of truth for AST shape, source-backed value materialization, escaped report fields, string-literal escape decoding, parser-level invalid escape diagnostics, and no-effect behavior.

## Current boundary

The current system provides:

```text
source-backed AST purpose and text values
accepted string-literal escape decoding
parser-level invalid string escape diagnostics
NUL rejection for decoded and literal NUL bytes
fixed-size NUL-terminated AST string buffers
escaped detailed report fields
source-oriented spans
no-effect flags
```

This contract does not add:

```text
length-carrying AST string implementation
decoded NUL acceptance
literal NUL acceptance
new accepted escape sequences
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

## Storage purpose

Length-carrying AST string storage should allow AST string values to be treated as byte sequences with explicit decoded lengths while preserving existing C-string compatibility for values that do not contain NUL bytes.

The goal is to make future decoded values unambiguous for:

```text
AST consumers
escaped detailed report fields
capacity checks
string-literal escape decoding
future NUL-capable storage work
```

## Public API shape

A future implementation should extend public AST structs in:

```text
include/latticra/l_ui_parser.h
```

by adding explicit decoded byte length fields:

```text
latticra_l_ui_ast_card_t.purpose_len
latticra_l_ui_ast_text_t.value_len
```

Proposed struct relationship:

```text
char purpose[LATTICRA_L_UI_AST_PURPOSE_MAX];
size_t purpose_len;

char value[LATTICRA_L_UI_AST_PURPOSE_MAX];
size_t value_len;
```

The length fields store decoded byte counts and do not include any trailing compatibility NUL byte.

## Compatibility rule

The existing fixed-size character buffers should remain public fields.

For decoded strings that do not contain NUL bytes:

```text
purpose_len == strlen(purpose)
value_len == strlen(value)
```

For future decoded strings that contain NUL bytes, `purpose_len` and `value_len` would be the authoritative lengths. Existing C-string fields would remain compatibility buffers but would not be sufficient to inspect the full decoded value through `strlen`.

## NUL byte rule

This contract does not make decoded NUL bytes accepted immediately.

The current parser-level diagnostics still reject:

```text
\x00 -> LATTICRA_L_UI_PARSE_DECODED_NUL_IN_STRING
literal 0x00 -> LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING
```

Decoded NUL bytes may be accepted only after:

1. length-carrying AST storage is implemented;
2. report escaping uses explicit lengths;
3. parser string escape diagnostics are updated by a separate contract;
4. string-literal escape decoding behavior is updated by a separate contract.

## Source-backed extraction rule

Source-backed extraction should continue to target:

```text
purpose "..." -> ast.card.purpose + ast.card.purpose_len
first text "..." -> ast.texts[0].value + ast.texts[0].value_len
second text "..." -> ast.texts[1].value + ast.texts[1].value_len
```

Extraction remains source-backed, deterministic, bounded, and no-effect.

## Decoding relationship

Accepted string-literal escapes should continue to decode exactly as they do now:

```text
\\
\"
\n
\r
\t
\xNN
```

where `\xNN` uses exactly two uppercase hexadecimal digits.

For all currently accepted decoded values that do not include NUL, the future length field should match the decoded byte length.

This contract does not broaden the accepted escape set.

## Capacity rule

Storage capacity remains bounded by:

```text
LATTICRA_L_UI_AST_PURPOSE_MAX
```

for both purpose and text values in the current AST model.

A decoded value fits only when:

```text
decoded_len < destination_buffer_len
```

because the compatibility buffer still needs a trailing NUL byte.

If decoded output is greater than or equal to the destination buffer length, parser validation should continue to report:

```text
LATTICRA_L_UI_PARSE_STRING_VALUE_TOO_LARGE
```

until a separate capacity expansion contract exists.

## Report behavior

Detailed reports should add explicit length fields:

```text
purpose_len=<decoded-purpose-byte-length>
value_len=<decoded-text-byte-length>
```

Existing report fields should remain:

```text
purpose=<C-string-compatible-purpose>
purpose_escaped=<length-aware-report-safe-purpose>
value=<C-string-compatible-text>
value_escaped=<length-aware-report-safe-text>
```

For values without NUL bytes, these fields should remain compatible with current output.

For any future values with embedded NUL bytes, the stable assertion target should be:

```text
purpose_len
purpose_escaped
value_len
value_escaped
```

not raw `purpose=` or `value=` C-string fields.

## Escaped report rule

The escaped report helper should become length-aware before decoded NUL bytes are accepted.

A future implementation should prefer a helper shape similar to:

```text
static latticra_status_t escape_report_bytes(
    const char *input,
    size_t input_len,
    char *output,
    size_t output_len);
```

The helper must emit report-safe byte escapes for control bytes, quotes, backslashes, DEL, non-ASCII bytes, and any future embedded NUL bytes.

## Source-span behavior

Source spans remain source-oriented.

Text spans continue to cover the source value range between quotes, not decoded output byte ranges.

For source escapes, spans include the source escape bytes. For example, `\n` covers two source bytes even though the decoded value length increases by one byte.

This contract does not add a public `purpose_span` field.

## Parser diagnostics compatibility

Current parser diagnostics remain valid:

```text
LUI0019 invalid_string_escape
LUI0020 invalid_hex_escape
LUI0021 unterminated_escape
LUI0022 decoded_nul_in_string
LUI0023 literal_nul_in_string
LUI0024 string_value_too_large
```

The first length-carrying storage implementation must not remove NUL rejection diagnostics.

A later decoded-NUL acceptance contract may change `LUI0022` behavior, but not as part of this storage contract.

## AST compatibility behavior

Failed parse behavior remains unchanged:

```text
ast.parse_result.error = parser error
ast.rail_count = 0
ast.field_count = 0
ast.text_count = 0
failed-parse detailed report only
```

Accepted sources should continue to produce the same AST counts and string values, plus explicit lengths.

The first accepted fixture should still report:

```text
rail_count=9
field_count=23
text_count=2
effect=none
boundary=preview_only
```

## No-effect rule

Length-carrying AST string storage is metadata-only.

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

Length-carrying AST string storage implementation must not begin until a separate implementation plan defines:

1. public struct field placement;
2. default initialization rules;
3. source-backed extraction length assignment;
4. string-literal decode length assignment;
5. report field additions;
6. length-aware escaped report helper shape;
7. parser diagnostics compatibility;
8. capacity behavior;
9. exact test file names;
10. exact invariant tests;
11. compatibility expectations.

That plan is recorded in [`L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_IMPLEMENTATION_PLAN.md`](L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_IMPLEMENTATION_PLAN.md).

## Future test list

A future implementation plan should include tests for:

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

## Forbidden behavior

A future length-carrying AST string storage implementation must not:

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
- accept decoded NUL bytes without a separate acceptance contract;
- accept literal NUL bytes without a separate acceptance contract;
- broaden accepted string escapes;
- remove existing C-string fields;
- silently truncate decoded values;
- make raw `purpose=` or `value=` report fields the assertion target for embedded NUL bytes.

## Current validation command

This contract is guarded by:

```sh
sh scripts/test-l-ui-ast-length-carrying-string-storage-contract.sh
```

The guard is static. It does not implement length-carrying AST string storage.

## Non-claims

This document does not implement length-carrying AST strings, accept decoded NUL bytes, accept literal NUL bytes, broaden accepted L-UI syntax, implement Unicode display behavior, add L-UI rendering, add command behavior, add Nucleus task handling, add live movement, add origin mutation, add recovery behavior, add server interaction, add self-update, add hardware support, add boot readiness, claim security isolation, claim sandboxing, or claim operating-system completeness.
