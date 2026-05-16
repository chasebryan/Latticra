# Latticra L-UI AST Length-Carrying String Storage Implementation Plan

Status: implementation planning contract
Scope: public struct field placement, default initialization, source-backed extraction length assignment, string-literal decode length assignment, report field additions, length-aware escaped report helper shape, parser diagnostics compatibility, capacity behavior, exact test files, and exact invariant tests before length-carrying AST string storage code.

## Purpose

This document defines the implementation plan for length-carrying AST string storage in L-UI.

The AST length-carrying string storage contract is already merged and guarded. This plan decides the exact public struct changes, default initialization rules, private helper changes, AST value materialization rules, detailed report additions, escaped report helper shape, compatibility behavior, and test coverage before implementation code is added.

This document does not implement length-carrying AST strings.

## Relationship to previous contracts

This plan depends on:

```text
docs/L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_CONTRACT.md
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

Those files remain the source of truth for AST shape, source-backed extraction, escaped detailed report fields, string-literal escape decoding, parser-level invalid escape diagnostics, and no-effect behavior.

## Implementation language decision

Length-carrying AST string storage should be implemented in C.

Reason:

- the L-UI parser and AST builder are implemented in C;
- AST structs are exposed through a C public API surface;
- report generation is implemented in C;
- storage and report changes must remain bounded, deterministic, and no-effect;
- no dynamic runtime should be required.

## Public struct field placement

Extend public AST structs in:

```text
include/latticra/l_ui_parser.h
```

Add `purpose_len` directly after the existing purpose buffer:

```text
typedef struct {
    char name[LATTICRA_L_UI_AST_LABEL_MAX];
    char purpose[LATTICRA_L_UI_AST_PURPOSE_MAX];
    size_t purpose_len;
    char effect[LATTICRA_L_UI_LABEL_MAX];
    char boundary[LATTICRA_L_UI_LABEL_MAX];
    latticra_l_ui_source_span_t span;
    size_t rail_count;
    size_t field_count;
    size_t text_count;
} latticra_l_ui_ast_card_t;
```

Add `value_len` directly after the existing text value buffer:

```text
typedef struct {
    char value[LATTICRA_L_UI_AST_PURPOSE_MAX];
    size_t value_len;
    latticra_l_ui_source_span_t span;
} latticra_l_ui_ast_text_t;
```

The length fields store decoded byte counts and do not include the trailing compatibility NUL byte.

## Public API compatibility decision

No new public function is required for the first implementation.

Existing public C-string fields remain:

```text
latticra_l_ui_ast_card_t.purpose
latticra_l_ui_ast_text_t.value
```

The new length fields add metadata but do not remove or rename existing fields.

## Default initialization rules

Update `ast_default` in:

```text
src/l_ui_parser_ast.c
```

Default values:

```text
ast.card.purpose[0] = '\0'
ast.card.purpose_len = 0
ast.texts[index].value[0] = '\0'
ast.texts[index].value_len = 0
```

Failed parse AST results must keep all AST string lengths at zero.

## Source-backed extraction length assignment

Source-backed extraction should assign decoded lengths while materializing AST values:

```text
purpose "..." -> ast.card.purpose + ast.card.purpose_len
first text "..." -> ast.texts[0].value + ast.texts[0].value_len
second text "..." -> ast.texts[1].value + ast.texts[1].value_len
```

For decoded values without NUL bytes:

```text
ast.card.purpose_len == strlen(ast.card.purpose)
ast.texts[index].value_len == strlen(ast.texts[index].value)
```

## String-literal decode helper shape

Update private decode helper behavior in:

```text
src/l_ui_parser_ast.c
```

Current helper:

```text
static latticra_status_t decode_l_ui_string_literal_value(
    const char *source,
    size_t start_offset,
    size_t end_offset,
    char *destination,
    size_t destination_len);
```

Proposed helper:

```text
static latticra_status_t decode_l_ui_string_literal_value(
    const char *source,
    size_t start_offset,
    size_t end_offset,
    char *destination,
    size_t destination_len,
    size_t *decoded_len);
```

`decoded_len` must be set only on success.

On failure, the destination should remain cleared when possible and the decoded length output should be set to zero when non-null.

## Extraction helper shape

Update the source-backed extraction helper in:

```text
src/l_ui_parser_ast.c
```

Current helper:

```text
static latticra_status_t extract_decoded_quoted_value_after_token(
    const char *source,
    size_t source_len,
    const char *token,
    size_t occurrence,
    char *destination,
    size_t destination_len,
    latticra_l_ui_source_span_t *value_span);
```

Proposed helper:

```text
static latticra_status_t extract_decoded_quoted_value_after_token(
    const char *source,
    size_t source_len,
    const char *token,
    size_t occurrence,
    char *destination,
    size_t destination_len,
    size_t *decoded_len,
    latticra_l_ui_source_span_t *value_span);
```

The helper should pass the decoded length back to the AST builder after successful decoding.

## Fill helper shape

Update private fill helpers:

```text
static void fill_text(
    latticra_l_ui_ast_result_t *ast,
    size_t index,
    const char *value,
    size_t value_len,
    const latticra_l_ui_source_span_t *span);
```

For the card purpose, assign:

```text
ast->card.purpose_len = extracted_purpose_len;
```

For text nodes, assign:

```text
ast->texts[index].value_len = value_len;
```

## Capacity behavior

Capacity remains:

```text
LATTICRA_L_UI_AST_PURPOSE_MAX
```

for purpose and text values.

A decoded value fits only when:

```text
decoded_len < destination_len
```

because the compatibility C string still needs a trailing NUL byte.

If decoded output is greater than or equal to the destination buffer length, parser validation should continue to report:

```text
LATTICRA_L_UI_PARSE_STRING_VALUE_TOO_LARGE
```

and AST construction should preserve failed-parse behavior.

## NUL behavior

This implementation must not accept decoded or literal NUL bytes.

Parser-level diagnostics must continue to reject:

```text
\x00 -> LATTICRA_L_UI_PARSE_DECODED_NUL_IN_STRING
literal 0x00 -> LATTICRA_L_UI_PARSE_LITERAL_NUL_IN_STRING
```

A later decoded-NUL acceptance contract may change this, but not this implementation.

## Report field additions

Update detailed AST reports in:

```text
latticra_l_ui_ast_detailed_report
```

Add card section field:

```text
purpose_len=<decoded-purpose-byte-length>
```

Add each text section field:

```text
value_len=<decoded-text-byte-length>
```

Recommended section placement:

```text
[card]
kind=card
name=<name>
purpose=<purpose>
purpose_len=<purpose_len>
purpose_escaped=<purpose_escaped>
```

and:

```text
[text N]
kind=text
value=<value>
value_len=<value_len>
value_escaped=<value_escaped>
```

Existing field names must remain stable.

## Length-aware escaped report helper shape

Replace or refactor the existing escaped report helper into a length-aware byte helper.

Current helper shape:

```text
static latticra_status_t escape_report_string(
    const char *input,
    size_t input_len,
    char *output,
    size_t output_len);
```

It already accepts `input_len`, but callers currently use `strlen`.

Implementation decision:

```text
keep the helper private
keep byte-oriented behavior
ensure callers pass explicit AST lengths instead of strlen for purpose and text values
```

Optional rename:

```text
escape_report_bytes
```

If renamed, keep behavior identical for non-NUL values.

## AST report compatibility

The compact AST report:

```text
latticra_l_ui_ast_report
```

should remain unchanged in the first implementation.

The detailed AST report gains length fields, but existing required fields and ordering should remain stable except for insertion of `purpose_len` and `value_len` near their corresponding values.

Failed-parse detailed reports should remain unchanged and should not include string length fields.

## Parser diagnostics compatibility

The implementation must not change existing parser diagnostics.

These diagnostics remain active:

```text
LUI0019 invalid_string_escape
LUI0020 invalid_hex_escape
LUI0021 unterminated_escape
LUI0022 decoded_nul_in_string
LUI0023 literal_nul_in_string
LUI0024 string_value_too_large
```

This implementation must not remove decoded-NUL or literal-NUL rejection.

## Source-span behavior

Source spans remain source-oriented.

Text spans continue to cover the source value range between quotes, not decoded output byte ranges.

For example, source `\n` covers two source bytes while the decoded AST value length increases by one byte.

No public `purpose_span` field is added in this implementation.

## Compatibility expectations

The implementation must not change:

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

The first accepted fixture should still report:

```text
rail_count=9
field_count=23
text_count=2
effect=none
boundary=preview_only
```

## No-effect preservation

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

## Exact implementation test list

The implementation PR should include tests for:

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

## Test file plan

Add:

```text
tests/l_ui_ast_length_carrying_string_storage_invariants.c
scripts/test-l-ui-ast-length-carrying-string-storage.sh
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
docs/L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_CONTRACT.md
docs/L_UI_PARSER_AST_IMPLEMENTATION.md
docs/L_UI_AST_SOURCE_BACKED_TEXT_IMPLEMENTATION.md
docs/L_UI_AST_ESCAPED_STRING_REPORT_IMPLEMENTATION.md
docs/L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION.md
docs/L_UI_PARSER_STRING_ESCAPE_DIAGNOSTICS_IMPLEMENTATION.md
```

and add:

```text
docs/L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_IMPLEMENTATION.md
```

## Forbidden implementation behavior

The length-carrying AST string storage implementation must not:

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
- change accepted escape decoding semantics;
- change existing parser diagnostic codes;
- make raw `purpose=` or `value=` report fields the assertion target for embedded NUL bytes.

## Current validation command

This plan is guarded by:

```sh
sh scripts/test-l-ui-ast-length-carrying-string-storage-implementation-plan.sh
```

The guard is static. It does not implement length-carrying AST string storage.

## Implementation gate

Length-carrying AST string storage implementation code may be added only after this plan is merged.

## Non-claims

This document does not implement length-carrying AST strings, accept decoded NUL bytes, accept literal NUL bytes, broaden accepted L-UI syntax, implement Unicode display behavior, add L-UI rendering, add command behavior, add Nucleus task handling, add live movement, add origin mutation, add recovery behavior, add server interaction, add self-update, add hardware support, add boot readiness, claim security isolation, claim sandboxing, or claim operating-system completeness.
