# Latticra L-UI Semantic Validation Contract

Status: semantic validation contract
Scope: future semantic validation layer for L-UI after structural parsing, source policies, AST construction, and string handling.

## Purpose

This document defines the contract for a future L-UI semantic validation layer.

The current L-UI parser verifies a controlled structural fixture shape, source spans, diagnostics, AST metadata, string-literal escapes, escaped decoded NUL behavior, and literal source-buffer NUL rejection.

Semantic validation is the next layer. It should validate meaning after structural parsing succeeds but before any future rendering, LIR lowering, Lat integration, or Nucleus task handling.

This document does not implement semantic validation.

## Relationship to previous work

This contract depends on:

```text
docs/L_UI_PARSER.md
docs/L_UI_PARSER_AST_IMPLEMENTATION.md
docs/L_UI_AST_DETAILED_REPORT_IMPLEMENTATION.md
docs/L_UI_AST_SOURCE_BACKED_TEXT_IMPLEMENTATION.md
docs/L_UI_AST_LENGTH_CARRYING_STRING_STORAGE_IMPLEMENTATION.md
docs/L_UI_DECODED_NUL_ACCEPTANCE_IMPLEMENTATION.md
docs/L_UI_SOURCE_BUFFER_LITERAL_NUL_POLICY_IMPLEMENTATION.md
include/latticra/l_ui_parser.h
src/l_ui_parser.c
src/l_ui_parser_ast.c
src/l_ui_parser_diagnostics.c
```

Those files remain the source of truth for parse results, AST shape, diagnostics, source spans, string storage, and source-buffer policy.

## Semantic validation layer

Semantic validation is a distinct layer after structural parsing.

Recommended pipeline:

```text
source bytes
  -> structural parser
  -> parser diagnostics
  -> AST construction
  -> semantic validation
  -> semantic report
  -> future rendering or lowering only if allowed
```

Semantic validation should not replace structural parsing.

## Initial semantic scope

The first semantic validation layer should check:

```text
required rail set
rail uniqueness
field uniqueness within a rail
required field ownership
binding prefix policy
binding target consistency
text node placement
card effect boundary
card boundary policy
no-effect preservation
```

## Required rail semantics

The accepted L-UI fixture currently uses these rails:

```text
top
state
trace
safety
gates
effects
policy
execution
bottom
```

Semantic validation should verify:

- each required rail is present exactly once;
- rails appear in deterministic report order;
- rail names are known;
- each rail owns only its expected fields or text nodes;
- text-only rails do not own fields;
- field-only rails do not own text nodes unless a future contract expands the grammar.

## Field ownership semantics

Initial expected ownership:

```text
state: origin, route, axis, path
trace: breadcrumb, trace
safety: health, risk, lock, dark_phase
gates: safe_portal, rollback
effects: host, external, requested
policy: request, policy, reason
execution: executed, mutation, server, recovery, hardware
```

Semantic validation should reject fields that appear under the wrong rail, duplicate fields, or missing required fields when a semantic validation API is introduced.

## Binding semantics

Initial allowed binding prefixes:

```text
state.
preview.
```

Expected binding relationships:

```text
origin -> state.origin
route -> state.route
axis -> state.axis
path -> state.path
breadcrumb -> state.breadcrumb
trace -> state.trace
health -> state.health
risk -> state.risk
lock -> state.lock
dark_phase -> state.dark_phase
safe_portal -> state.safe_portal
rollback -> state.rollback
host -> state.host_effect
external -> state.external_effect
requested -> preview.requested_effect
request -> preview.request
policy -> preview.policy
reason -> preview.reason
executed -> preview.executed
mutation -> preview.mutation_allowed
server -> preview.server_interaction_allowed
recovery -> preview.recovery_allowed
hardware -> preview.hardware_allowed
```

Semantic validation should treat mismatched field/binding pairs as semantic errors.

## Text semantics

Initial text node placement:

```text
top rail -> first text node
bottom rail -> second text node
```

Semantic validation should verify:

- exactly two text nodes exist;
- the top rail owns the first text node;
- the bottom rail owns the second text node;
- text values use explicit `value_len` when inspected;
- raw `value=` compatibility fields are not authoritative for embedded NUL values.

## Card semantics

The initial card remains:

```text
NucleusPreview
```

Required card metadata:

```text
effect=none
boundary=preview_only
rail_count=9
field_count=23
text_count=2
```

Semantic validation should reject unsupported cards, effects, boundaries, or mismatched counts.

## Semantic diagnostic model

A future implementation should introduce semantic validation diagnostics without destabilizing existing parser diagnostic codes.

Recommended semantic diagnostic code range:

```text
LUI1000-LUI1099
```

Initial candidate diagnostics:

```text
LUI1000 semantic_validation_failed
LUI1001 duplicate_rail
LUI1002 missing_required_rail
LUI1003 duplicate_field
LUI1004 field_rail_mismatch
LUI1005 binding_field_mismatch
LUI1006 unsupported_binding_target
LUI1007 text_rail_mismatch
LUI1008 card_count_mismatch
LUI1009 semantic_internal_error
```

The exact names and codes must be finalized in the implementation plan before code is added.

## Semantic report model

A future semantic report should be deterministic and bounded.

Suggested fields:

```text
L-UI SEMANTIC VALIDATION RESULT
status=<ok|error>
semantic_error=<label>
card=<card-name>
rail_count=<count>
field_count=<count>
text_count=<count>
no_effect=<0|1>
execution_allowed=<0|1>
mutation_allowed=<0|1>
server_allowed=<0|1>
recovery_allowed=<0|1>
hardware_allowed=<0|1>
```

For semantic failures, the report should include a source span when available.

## Source-span behavior

Semantic diagnostics should use the most specific existing source span available:

- rail errors should use the rail span;
- field errors should use the field span;
- binding errors should use the binding span;
- text errors should use the text span;
- card-level errors should use the card span;
- internal semantic errors should use a default span only when no better span exists.

Semantic validation should not invent byte positions that are not represented by parser or AST metadata.

## AST relationship

Semantic validation should operate on `latticra_l_ui_ast_result_t` after `latticra_l_ui_parse_ast` returns parser success.

If `ast.parse_result.error != LATTICRA_L_UI_PARSE_OK`, semantic validation should not attempt semantic inspection and should report parser failure or semantic not-run state.

## Public API expectation

A future implementation plan should define public API additions such as:

```text
latticra_l_ui_semantic_result_t
latticra_l_ui_validate_semantics
latticra_l_ui_semantic_error_label
latticra_l_ui_semantic_report
```

No public API is added by this contract.

## No-effect rule

Semantic validation is metadata-only.

It must preserve:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

Semantic validation must not render UI, lower to LIR, execute bindings, mutate state, call Nucleus task code, interact with a server, write files, read files, or touch hardware.

## Compatibility expectations

Semantic validation must not change:

```text
existing parser behavior
existing parser diagnostic codes
existing AST construction behavior
existing detailed AST report behavior
escaped decoded NUL acceptance
literal source-buffer NUL rejection
source-span byte offset behavior
no-effect flags
current accepted fixture counts
```

The first accepted fixture should still report:

```text
rail_count=9
field_count=23
text_count=2
effect=none
boundary=preview_only
```

## Future implementation gate

Semantic validation implementation must not begin until a separate implementation plan defines:

1. public API shape;
2. semantic result struct fields;
3. semantic error enum labels;
4. diagnostic code mapping;
5. report format;
6. rail semantic checks;
7. field semantic checks;
8. binding semantic checks;
9. text semantic checks;
10. exact tests;
11. compatibility expectations;
12. non-claims.

## Future test list

A future implementation plan should include tests for:

```text
semantic_validation_accepts_current_fixture
semantic_validation_rejects_duplicate_rail
semantic_validation_rejects_missing_required_rail
semantic_validation_rejects_duplicate_field
semantic_validation_rejects_field_rail_mismatch
semantic_validation_rejects_binding_field_mismatch
semantic_validation_rejects_unsupported_binding_target
semantic_validation_rejects_text_rail_mismatch
semantic_validation_rejects_card_count_mismatch
semantic_validation_skips_when_parser_failed
semantic_validation_reports_source_spans
semantic_validation_preserves_no_effect_flags
semantic_validation_does_not_change_ast_report
semantic_validation_does_not_change_escaped_x00_acceptance
semantic_validation_does_not_change_literal_nul_rejection
semantic_validation_is_deterministic
```

## Forbidden behavior

Semantic validation must not:

- execute bindings;
- evaluate host state;
- call Nucleus task execution;
- render L-UI;
- lower to LIR;
- mutate state;
- write files;
- read files;
- open network connections;
- call server code;
- call update code;
- call recovery code;
- call hardware code;
- broaden accepted syntax;
- weaken parser diagnostics;
- accept literal source-buffer NUL;
- remove escaped decoded NUL support;
- make raw `value=` or `purpose=` fields authoritative for embedded NUL values.

## Current validation command

This contract is guarded by:

```sh
sh scripts/test-l-ui-semantic-validation-contract.sh
```

The guard is static. It does not implement semantic validation.

## Non-claims

This document does not implement semantic validation, LIR lowering, L-UI rendering, Lat execution, command behavior, Nucleus task handling, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, malware prevention, ransomware prevention, or operating-system completeness.
