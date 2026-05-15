# Latticra L-UI AST Source-Backed Text Contract

Status: source-backed text contract
Scope: future extraction of AST purpose and text values from validated L-UI source instead of fixed fixture metadata.

## Purpose

This document defines the source-backed text extraction contract for the L-UI AST.

The current AST implementation builds fixed metadata for the first accepted `NucleusPreview` fixture. Its purpose and text values are known fixture literals. The next step is to define how those values should be extracted from validated source while preserving source spans, escaped reporting, no-effect behavior, and deterministic output.

This document does not implement source-backed text extraction.

## Current boundary

The current AST stack provides:

```text
validated L-UI parser
source spans
fixed-size AST metadata
fixed fixture purpose value
fixed fixture text values
compact AST report
detailed AST report
escaped detailed report fields
no-effect flags
```

This contract does not add:

```text
source-backed extraction implementation
new accepted grammar
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

Source-backed text extraction should make the AST reflect the actual validated `.lui` source text for:

```text
card.purpose
text.value
```

This allows fixture text changes to be represented in AST metadata without hard-coded AST literals.

## Extraction targets

The first implementation should extract:

```text
purpose "..."
text "..."
```

from the already-validated source.

The first accepted fixture should still produce:

```text
purpose=operator-visible Nucleus preview report
value=Latticra / Nucleus Preview / effect-bound
value=preview-only no-live-movement no-host-effect no-external-effect
```

## No grammar broadening rule

Source-backed extraction must not broaden accepted L-UI syntax by itself.

The parser must still reject unsupported forms according to the existing parser contracts.

Extraction must only run after successful validation by:

```text
latticra_l_ui_parse_source
```

## Ownership rule

Extracted text must be copied into fixed AST storage.

The AST must not retain borrowed pointers into the source buffer.

Required destination fields:

```text
latticra_l_ui_ast_card_t.purpose
latticra_l_ui_ast_text_t.value
```

The extraction implementation must preserve NUL-terminated C strings in AST storage.

## Capacity rule

Extraction must respect existing capacities:

```text
LATTICRA_L_UI_AST_PURPOSE_MAX
LATTICRA_L_UI_AST_TEXT_MAX
```

The first implementation should reject or classify oversized extracted strings with a stable error behavior defined in the implementation plan.

It must not truncate silently.

## Span rule

Extracted values should keep source-span metadata.

For purpose:

```text
card.purpose_span or equivalent future span field
```

For text:

```text
text.span
```

The current `text.span` already covers text values. The implementation plan must decide whether a separate `purpose_span` field is needed or whether the card span remains sufficient for the first source-backed step.

## Quote handling rule

The first source-backed implementation should extract quoted string contents.

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

Current L-UI string escape semantics are not fully defined.

The first source-backed extraction should not introduce broad escape decoding unless a string-literal escape contract is added first.

Allowed first behavior options for the implementation plan:

1. copy raw bytes between quotes without decoding escapes; or
2. support only existing literal fixture text with no escape decoding.

The implementation plan must choose one behavior before code is added.

## Detailed report relationship

Detailed reports should continue to render:

```text
purpose=<literal-purpose>
purpose_escaped=<escaped-purpose>
value=<literal-text>
value_escaped=<escaped-text>
```

After source-backed extraction, those report values should reflect extracted source values.

## Failed parse behavior

Failed parse behavior must remain unchanged.

If source validation fails:

```text
no partial AST nodes
no extracted text
failed-parse detailed report only
```

## No-effect rule

Source-backed text extraction is metadata-only.

It must preserve:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

## Compatibility rule

Source-backed text extraction must not change:

```text
latticra_l_ui_parse_source
latticra_l_ui_ast_report
latticra_l_ui_ast_detailed_report existing required fields
latticra_l_ui_diagnostic_report
parser error labels
existing accepted fixture summary
```

The first accepted fixture should still report the same AST summary counts:

```text
rail_count=9
field_count=23
text_count=2
```

## Implementation gate

Source-backed text extraction implementation must not begin until a separate implementation plan defines:

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

## Future test list

A future implementation plan should include tests for:

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
```

## Forbidden behavior

A future source-backed text implementation must not:

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

The guard is static. It does not implement source-backed text extraction.

## Non-claims

This document does not implement source-backed text extraction, broaden accepted L-UI text syntax, implement string escape decoding, implement Unicode display behavior, add L-UI rendering, add command behavior, add Nucleus task handling, add live movement, add origin mutation, add recovery behavior, add server interaction, add self-update, add hardware support, add boot readiness, claim security isolation, claim sandboxing, or claim operating-system completeness.
