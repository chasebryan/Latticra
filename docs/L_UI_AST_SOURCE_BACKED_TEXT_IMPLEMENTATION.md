# Latticra L-UI AST Source-Backed Text Implementation

Status: initial implementation contract
Scope: source-backed extraction of AST purpose and text values from validated L-UI source.

## Purpose

The L-UI AST Source-Backed Text implementation extracts AST purpose and text values from validated L-UI source instead of relying on fixed fixture literals.

It keeps AST storage fixed-size, copies extracted text into AST-owned buffers, preserves no-effect behavior, and leaves parser validation as the gate before extraction.

## Implementation files

```text
src/l_ui_parser_ast.c
tests/l_ui_ast_source_backed_text_invariants.c
scripts/test-l-ui-ast-source-backed-text.sh
```

## Extraction targets

The implementation extracts:

```text
purpose "..." -> ast.card.purpose
first text "..." -> ast.texts[0].value
second text "..." -> ast.texts[1].value
```

The first accepted fixture still produces:

```text
purpose=operator-visible Nucleus preview report
value=Latticra / Nucleus Preview / effect-bound
value=preview-only no-live-movement no-host-effect no-external-effect
```

## Private helpers

The implementation adds private helpers in `src/l_ui_parser_ast.c`:

```text
extract_quoted_value_after_token
copy_extracted_value
```

These helpers remain private.

## Quote behavior

The implementation copies bytes between the opening and closing quote.

For source:

```text
purpose "abc"
text "xyz"
```

AST values become:

```text
abc
xyz
```

The surrounding quotes are not copied into AST values.

## Escape handling boundary

The implementation does not decode string escapes.

It copies raw bytes between quotes while respecting escaped quotes for finding the closing quote.

For example, source bytes representing:

```text
raw\ntext
```

remain AST bytes representing:

```text
raw\ntext
```

not a decoded newline.

## Capacity behavior

Extraction respects destination capacities:

```text
LATTICRA_L_UI_AST_PURPOSE_MAX
LATTICRA_L_UI_AST_PURPOSE_MAX for text values
LATTICRA_L_UI_AST_TEXT_MAX for text node count
```

If an extracted value is too large for its destination, AST construction classifies the result as:

```text
LATTICRA_L_UI_PARSE_INTERNAL_ERROR
```

and leaves counts at zero to avoid a partial AST.

The implementation does not silently truncate extracted values.

## Span behavior

The implementation does not add a public purpose span.

`text.span` is set to the extracted text value range for text nodes. `card.span` continues to cover the card block.

## Successful parse rule

Extraction runs only after:

```text
latticra_l_ui_parse_source
```

returns `LATTICRA_STATUS_OK` and `parse_result.error == LATTICRA_L_UI_PARSE_OK`.

If parsing fails, extraction does not run.

## Detailed report relationship

Detailed reports continue to render:

```text
purpose=<literal-purpose>
purpose_escaped=<escaped-purpose>
value=<literal-text>
value_escaped=<escaped-text>
```

After source-backed extraction, these values reflect the validated source values.

## Failed parse behavior

Failed parse behavior is unchanged:

```text
ast.parse_result.error = parser error
ast.rail_count = 0
ast.field_count = 0
ast.text_count = 0
failed-parse detailed report only
```

No source-backed text values are extracted for failed parses.

## Compatibility

This implementation does not change:

```text
latticra_l_ui_parse_source
latticra_l_ui_ast_report
latticra_l_ui_ast_detailed_report existing required fields
latticra_l_ui_diagnostic_report
parser error labels
existing accepted fixture summary counts
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

Source-backed text extraction preserves:

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
sh scripts/test-l-ui-ast-source-backed-text.sh
```

The main C workflow runs this check after the source-backed text implementation-plan guard.

## Required invariants

The source-backed text tests verify:

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

## Current evidence level

This implementation is an L2 tested source-backed text extraction model for validated L-UI AST metadata.

It is not a broader text grammar, string escape decoder, Unicode display model, renderer, UI runtime, command surface, Nucleus task runner, server client, update engine, recovery system, hardware system, boot system, or security boundary.

## Next implementation step

The next implementation candidate after source-backed text extraction is:

```text
L-UI string-literal escape contract
```

That future work should define whether and how string escapes are decoded before AST extraction decodes escape sequences.

## Non-claims

This document and implementation do not broaden accepted L-UI text syntax, implement string escape decoding, implement Unicode display behavior, add L-UI rendering, add command behavior, add Nucleus task handling, add live movement, add origin mutation, add recovery behavior, add server interaction, add self-update, add hardware support, add boot readiness, claim security isolation, claim sandboxing, or claim operating-system completeness.
