# Latticra L-UI AST Source-Backed Text Implementation Plan

Status: implementation planning contract
Scope: extraction helpers, exact extraction targets, quote handling, capacity behavior, span decisions, exact tests, and compatibility expectations before source-backed text extraction code.

## Purpose

This document defines the implementation plan for source-backed text extraction in the L-UI AST.

The source-backed text contract is already merged and guarded. This plan decides the helper shapes, extraction targets, quote handling, escape handling boundary, capacity behavior, span decision, exact tests, and compatibility expectations before implementation code is added.

## Relationship to previous contracts

This plan depends on:

```text
docs/L_UI_AST_SOURCE_BACKED_TEXT_CONTRACT.md
docs/L_UI_PARSER_AST_IMPLEMENTATION.md
docs/L_UI_AST_ESCAPED_STRING_REPORT_IMPLEMENTATION.md
include/latticra/l_ui_parser.h
src/l_ui_parser_ast.c
```

Those files remain the source of truth for AST storage, source spans, detailed reporting, escaped fields, and no-effect boundaries.

## Implementation language decision

Source-backed text extraction should be implemented in C.

Reason:

- the AST builder is implemented in C;
- AST storage is a C public API surface;
- extraction must remain bounded, deterministic, and no-effect;
- the current C workflow can validate extraction invariants;
- no dynamic runtime should be required.

## Public API decision

No new public function is needed for the first source-backed extraction implementation.

Extraction should be integrated into:

```text
latticra_l_ui_parse_ast
```

The public AST fields remain:

```text
latticra_l_ui_ast_card_t.purpose
latticra_l_ui_ast_text_t.value
```

## Extraction helper plan

Add private helpers in:

```text
src/l_ui_parser_ast.c
```

Proposed helpers:

```text
static latticra_status_t extract_quoted_value_after_token(
    const char *source,
    size_t source_len,
    const char *token,
    size_t occurrence,
    char *destination,
    size_t destination_len,
    latticra_l_ui_source_span_t *value_span);

static latticra_status_t copy_extracted_value(
    const char *source,
    size_t start_offset,
    size_t end_offset,
    char *destination,
    size_t destination_len);
```

Helpers must remain private.

## Extraction targets

The first implementation should extract these source-backed values:

```text
purpose "..." -> ast.card.purpose
first text "..." -> ast.texts[0].value
second text "..." -> ast.texts[1].value
```

The first accepted fixture must still produce:

```text
purpose=operator-visible Nucleus preview report
value=Latticra / Nucleus Preview / effect-bound
value=preview-only no-live-movement no-host-effect no-external-effect
```

## Quote handling behavior

The first implementation should copy bytes between the opening and closing quote.

For source:

```text
purpose "abc"
text "xyz"
```

AST values should be:

```text
abc
xyz
```

The surrounding quotes must not be copied into AST values.

## Escape handling boundary

The first implementation must not decode escape sequences.

Behavior:

```text
copy raw bytes between quotes without decoding escapes
```

If later grammar accepts string escapes, a string-literal escape contract should define decoding behavior before AST extraction decodes anything.

## Capacity behavior

Extraction must respect destination capacities:

```text
LATTICRA_L_UI_AST_PURPOSE_MAX
LATTICRA_L_UI_AST_PURPOSE_MAX for text values
LATTICRA_L_UI_AST_TEXT_MAX for text node count
```

Because `latticra_l_ui_ast_text_t.value` currently uses `LATTICRA_L_UI_AST_PURPOSE_MAX`, the text extraction destination capacity is that field size. `LATTICRA_L_UI_AST_TEXT_MAX` remains the bounded capacity for the number of text nodes.

If extracted text length is greater than or equal to the destination buffer length, extraction should return:

```text
LATTICRA_STATUS_BUFFER_TOO_SMALL
```

`latticra_l_ui_parse_ast` should convert an extraction capacity failure into:

```text
ast.parse_result.error = LATTICRA_L_UI_PARSE_INTERNAL_ERROR
```

and should leave counts at zero to avoid a partial AST.

The implementation must not silently truncate extracted values.

## Span decision

Do not add a new public `purpose_span` field in the first implementation.

Reason:

- `text.span` already exists for text values;
- `card.span` covers the card block;
- adding a public purpose span would require a broader AST struct change;
- source-backed value correctness can be tested through copied values and detailed reports.

Internal extraction may compute a value span for validation, but it does not need to expose it publicly yet.

## Successful parse rule

Extraction must run only after:

```text
latticra_l_ui_parse_source
```

returns `LATTICRA_STATUS_OK` and `parse_result.error == LATTICRA_L_UI_PARSE_OK`.

If parsing fails, extraction must not run.

## Failed parse behavior

Failed parse behavior must remain unchanged:

```text
ast.parse_result.error = parser error
ast.rail_count = 0
ast.field_count = 0
ast.text_count = 0
failed-parse detailed report only
```

No source-backed text values should be extracted for failed parses.

## Detailed report relationship

Detailed reports should continue to render:

```text
purpose=<literal-purpose>
purpose_escaped=<escaped-purpose>
value=<literal-text>
value_escaped=<escaped-text>
```

After source-backed extraction, these values should reflect the extracted source values.

## Compatibility expectations

Source-backed text extraction must not change:

```text
latticra_l_ui_parse_source
latticra_l_ui_ast_report
latticra_l_ui_ast_detailed_report existing required fields
latticra_l_ui_diagnostic_report
parser error labels
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

Source-backed text extraction must preserve:

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
source_backed_purpose_matches_fixture_source
source_backed_top_text_matches_fixture_source
source_backed_bottom_text_matches_fixture_source
source_backed_text_values_are_copied
source_backed_text_does_not_retain_source_pointers
source_backed_text_excludes_quotes
source_backed_text_preserves_ast_counts
source_backed_text_preserves_no_effect_flags
source_backed_text_updates_detailed_report_literals
source_backed_text_updates_detailed_report_escaped_fields
source_backed_text_rejects_or_classifies_oversized_purpose
source_backed_text_rejects_or_classifies_oversized_text
source_backed_text_does_not_change_failed_parse_report
source_backed_text_is_deterministic
source_backed_text_does_not_decode_escapes
```

## Test file plan

Add:

```text
tests/l_ui_ast_source_backed_text_invariants.c
scripts/test-l-ui-ast-source-backed-text.sh
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
docs/L_UI_AST_SOURCE_BACKED_TEXT_CONTRACT.md
docs/L_UI_PARSER_AST_IMPLEMENTATION.md
docs/L_UI_AST_DETAILED_REPORT_IMPLEMENTATION.md
```

and add:

```text
docs/L_UI_AST_SOURCE_BACKED_TEXT_IMPLEMENTATION.md
```

## Forbidden implementation behavior

The source-backed text implementation must not:

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
- retain source-buffer pointers in the AST;
- silently truncate extracted values;
- broaden accepted grammar without a grammar contract;
- decode string escapes without a string-literal escape contract.

## Current validation command

This plan is guarded by:

```sh
sh scripts/test-l-ui-ast-source-backed-text-implementation-plan.sh
```

The guard is static. It does not implement source-backed text extraction.

## Implementation gate

Source-backed text extraction implementation code may be added only after this plan is merged.

## Non-claims

This document does not implement source-backed text extraction, broaden accepted L-UI text syntax, implement string escape decoding, implement Unicode display behavior, add L-UI rendering, add command behavior, add Nucleus task handling, add live movement, add origin mutation, add recovery behavior, add server interaction, add self-update, add hardware support, add boot readiness, claim security isolation, claim sandboxing, or claim operating-system completeness.
