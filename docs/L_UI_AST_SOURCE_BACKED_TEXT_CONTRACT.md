# Latticra L-UI AST Source-Backed Text Contract

Status: source-backed text contract
Scope: extraction of AST purpose and text values from validated L-UI source instead of fixed fixture metadata.

## Purpose

This document defines the source-backed text extraction contract for the L-UI AST.

The AST implementation extracts purpose and text values from validated `NucleusPreview` source while preserving source spans, escaped reporting, no-effect behavior, and deterministic output.

The source-backed extraction implementation is documented separately in [`L_UI_AST_SOURCE_BACKED_TEXT_IMPLEMENTATION.md`](L_UI_AST_SOURCE_BACKED_TEXT_IMPLEMENTATION.md).

The later string-literal escape decoder is documented separately in [`L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION.md`](L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION.md).

## Current boundary

The current L-UI AST stack provides:

```text
validated L-UI parser
source spans
fixed-size AST metadata
source-backed purpose value
source-backed text values
string-literal escape decoding for accepted source escapes
compact AST report
detailed AST report
escaped detailed report fields
no-effect flags
```

This contract does not add:

```text
new renderer behavior
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

## Extraction purpose

Source-backed text extraction makes the AST reflect the actual validated `.lui` source text for:

```text
card.purpose
text.value
```

This allows fixture text changes to be represented in AST metadata without hard-coded AST literals.

## Extraction targets

The implementation extracts:

```text
purpose "..."
text "..."
```

from the already-validated source.

The first accepted fixture still produces:

```text
purpose=operator-visible Nucleus preview report
value=Latticra / Nucleus Preview / effect-bound
value=preview-only no-live-movement no-host-effect no-external-effect
```

## No grammar broadening rule

Source-backed extraction does not broaden accepted L-UI syntax by itself.

The parser still rejects unsupported forms according to the existing parser contracts.

Extraction runs only after successful validation by:

```text
latticra_l_ui_parse_source
```

## Ownership rule

Extracted text is copied into fixed AST storage.

The AST does not retain borrowed pointers into the source buffer.

Destination fields:

```text
latticra_l_ui_ast_card_t.purpose
latticra_l_ui_ast_text_t.value
```

The extraction implementation preserves NUL-terminated C strings in AST storage.

## Capacity rule

Extraction respects existing capacities:

```text
LATTICRA_L_UI_AST_PURPOSE_MAX
LATTICRA_L_UI_AST_TEXT_MAX
```

The implementation classifies oversized extracted or decoded strings with:

```text
LATTICRA_L_UI_PARSE_INTERNAL_ERROR
```

and avoids partial AST output.

It does not truncate silently.

## Span rule

Extracted values keep source-span metadata where currently supported.

For purpose:

```text
card.span covers the card block
```

For text:

```text
text.span covers the source text value range
```

Source spans refer to source byte ranges, not decoded output byte ranges.

No public `purpose_span` field is added in the first source-backed extraction implementation.

## Quote handling rule

The implementation extracts quoted string contents.

For source:

```text
purpose "abc"
text "xyz"
```

AST values are:

```text
abc
xyz
```

The surrounding quotes are not copied into AST values.

Escaped quotes are respected when finding the closing quote.

## Escape handling relationship

The initial source-backed extraction phase copied raw bytes between quotes without decoding escapes.

Current source-backed AST values now decode accepted string-literal escapes according to:

```text
L_UI_STRING_LITERAL_ESCAPE_CONTRACT.md
L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION_PLAN.md
L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION.md
```

Accepted escapes such as `\n`, `\r`, `\t`, `\"`, `\\`, and uppercase `\xNN` decode before values are stored in AST-owned buffers.

Rejected escapes are classified through:

```text
LATTICRA_L_UI_PARSE_INTERNAL_ERROR
```

until parser-level string escape diagnostics are designed.

## Detailed report relationship

Detailed reports continue to render:

```text
purpose=<literal-purpose>
purpose_escaped=<escaped-purpose>
value=<literal-text>
value_escaped=<escaped-text>
```

After source-backed extraction and accepted string-literal escape decoding, those report values reflect decoded AST values.

The escaped report fields remain the stable assertion target for control bytes, quotes, backslashes, DEL, and non-ASCII bytes.

## Failed parse behavior

Failed parse behavior remains unchanged.

If source validation fails:

```text
no partial AST nodes
no extracted text
failed-parse detailed report only
```

## No-effect rule

Source-backed text extraction and string-literal escape decoding are metadata-only.

They preserve:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

## Compatibility rule

Source-backed text extraction and string-literal escape decoding do not change:

```text
latticra_l_ui_parse_source
latticra_l_ui_ast_report
latticra_l_ui_ast_detailed_report existing required fields
latticra_l_ui_diagnostic_report
parser error labels
existing accepted fixture summary
```

The first accepted fixture still reports the same AST summary counts:

```text
rail_count=9
field_count=23
text_count=2
```

## Implementation gate

Source-backed text extraction implementation required a separate implementation plan defining:

1. extraction helper shapes;
2. exact extraction targets;
3. capacity behavior;
4. span field decision;
5. quote handling behavior;
6. escape handling boundary;
7. failed-parse behavior;
8. test file names;
9. exact invariant tests;
10. compatibility expectations.

That plan is recorded in [`L_UI_AST_SOURCE_BACKED_TEXT_IMPLEMENTATION_PLAN.md`](L_UI_AST_SOURCE_BACKED_TEXT_IMPLEMENTATION_PLAN.md).

String-literal escape decoding required a separate implementation plan before decoder code. That plan is recorded in [`L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION_PLAN.md`](L_UI_STRING_LITERAL_ESCAPE_IMPLEMENTATION_PLAN.md).

## Test list

Source-backed text implementation tests verify:

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
source_backed_text_decodes_accepted_string_escapes
```

## Forbidden behavior

Source-backed text implementation must not:

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
- broaden accepted grammar without a grammar contract.

## Current validation command

This contract is guarded by:

```sh
sh scripts/test-l-ui-ast-source-backed-text-contract.sh
```

The guard is static. It validates the contract text.

## Non-claims

This document does not broaden non-string L-UI syntax, implement Unicode display behavior, add L-UI rendering, add command behavior, add Nucleus task handling, add live movement, add origin mutation, add recovery behavior, add server interaction, add self-update, add hardware support, add boot readiness, claim security isolation, claim sandboxing, or claim operating-system completeness.
