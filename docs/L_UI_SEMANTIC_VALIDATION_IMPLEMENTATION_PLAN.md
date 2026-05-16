# Latticra L-UI Semantic Validation Implementation Plan

Status: implementation planning contract
Scope: public API shape, semantic result structs, semantic errors, diagnostic mapping, report format, semantic checks, exact tests, and compatibility expectations before semantic validation code.

## Purpose

This document defines the implementation plan for the L-UI semantic validation layer.

The semantic-validation contract is already merged and guarded. This plan names the exact API, result shape, error labels, diagnostic mapping, report format, semantic checks, source-span behavior, tests, and non-claims required before implementation code is added.

This document does not implement semantic validation.

## Relationship to previous work

This plan depends on:

```text
docs/L_UI_SEMANTIC_VALIDATION_CONTRACT.md
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

Those files remain the source of truth for parse results, AST shape, diagnostics, source spans, string storage, decoded NUL behavior, and source-buffer policy.

## Implementation language decision

Semantic validation should be implemented in C.

Reason:

- the parser and AST implementation are C;
- the public L-UI API is C;
- semantic validation consumes `latticra_l_ui_ast_result_t`;
- existing tests and runners are C and POSIX shell;
- the first semantic layer should stay deterministic, bounded, and no-effect.

## Implementation files

The implementation PR should modify:

```text
include/latticra/l_ui_parser.h
src/l_ui_parser_semantic.c
src/l_ui_parser_diagnostics.c
.github/workflows/c.yml
```

The implementation PR should add:

```text
docs/L_UI_SEMANTIC_VALIDATION_IMPLEMENTATION.md
tests/l_ui_semantic_validation_invariants.c
scripts/test-l-ui-semantic-validation.sh
```

The implementation should not add file I/O, network I/O, rendering code, LIR lowering, or task execution.

## Public API shape

Add public semantic validation API declarations to:

```text
include/latticra/l_ui_parser.h
```

Required API names:

```text
latticra_l_ui_semantic_error_t
latticra_l_ui_semantic_result_t
latticra_l_ui_semantic_error_label
latticra_l_ui_validate_semantics
latticra_l_ui_semantic_report
```

Recommended function signatures:

```text
const char *latticra_l_ui_semantic_error_label(latticra_l_ui_semantic_error_t error);

latticra_status_t latticra_l_ui_validate_semantics(
    const latticra_l_ui_ast_result_t *ast,
    latticra_l_ui_semantic_result_t *result);

latticra_status_t latticra_l_ui_semantic_report(
    const latticra_l_ui_semantic_result_t *result,
    char *buffer,
    size_t buffer_len);
```

## Semantic error enum

Add a semantic error enum with stable labels:

```text
LATTICRA_L_UI_SEMANTIC_OK
LATTICRA_L_UI_SEMANTIC_PARSER_FAILED
LATTICRA_L_UI_SEMANTIC_DUPLICATE_RAIL
LATTICRA_L_UI_SEMANTIC_MISSING_REQUIRED_RAIL
LATTICRA_L_UI_SEMANTIC_DUPLICATE_FIELD
LATTICRA_L_UI_SEMANTIC_FIELD_RAIL_MISMATCH
LATTICRA_L_UI_SEMANTIC_BINDING_FIELD_MISMATCH
LATTICRA_L_UI_SEMANTIC_UNSUPPORTED_BINDING_TARGET
LATTICRA_L_UI_SEMANTIC_TEXT_RAIL_MISMATCH
LATTICRA_L_UI_SEMANTIC_CARD_COUNT_MISMATCH
LATTICRA_L_UI_SEMANTIC_INTERNAL_ERROR
```

Required labels:

```text
ok
parser_failed
duplicate_rail
missing_required_rail
duplicate_field
field_rail_mismatch
binding_field_mismatch
unsupported_binding_target
text_rail_mismatch
card_count_mismatch
internal_error
```

## Semantic result struct

Add a semantic result struct that includes:

```text
latticra_status_t status;
latticra_l_ui_semantic_error_t error;
latticra_l_ui_parse_error_t parser_error;
latticra_l_ui_source_span_t span;
size_t rail_index;
size_t field_index;
size_t text_index;
char card_name[LATTICRA_L_UI_AST_NAME_MAX];
char rail_name[LATTICRA_L_UI_AST_NAME_MAX];
char field_name[LATTICRA_L_UI_AST_NAME_MAX];
char binding[LATTICRA_L_UI_AST_BINDING_MAX];
size_t rail_count;
size_t field_count;
size_t text_count;
int no_effect;
int execution_allowed;
int mutation_allowed;
int server_allowed;
int recovery_allowed;
int hardware_allowed;
```

The result should be deterministic and fully initialized for both success and failure.

## Semantic diagnostic mapping

Semantic validation should use a separate diagnostic code range from parser diagnostics:

```text
LUI1000-LUI1099
```

Initial mapping:

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

`parser_failed` may report a semantic not-run state in semantic reports, but it must not replace existing parser diagnostic codes.

## Semantic report format

`latticra_l_ui_semantic_report` should produce a deterministic report:

```text
L-UI SEMANTIC VALIDATION RESULT
status=<integer-status>
error=<semantic-error-label>
parser_error=<parser-error-label>
card=<card-name>
rail=<rail-name>
field=<field-name>
binding=<binding>
rail_index=<index>
field_index=<index>
text_index=<index>
rail_count=<count>
field_count=<count>
text_count=<count>
no_effect=<0|1>
execution_allowed=<0|1>
mutation_allowed=<0|1>
server_allowed=<0|1>
recovery_allowed=<0|1>
hardware_allowed=<0|1>
span_start_offset=<offset>
span_end_offset=<offset>
span_start_line=<line>
span_start_column=<column>
span_end_line=<line>
span_end_column=<column>
```

The report must return `LATTICRA_STATUS_BUFFER_TOO_SMALL` and clear the buffer when the output does not fit.

## Rail semantic checks

Semantic validation should verify exactly these rail names in deterministic order:

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

Checks:

- all required rails are present;
- no duplicate rail names exist;
- no unknown rail names exist;
- rail order is deterministic;
- rail field/text ownership metadata is consistent.

Expected rail ownership:

```text
top: text_count=1, field_count=0
state: field_count=4, text_count=0
trace: field_count=2, text_count=0
safety: field_count=4, text_count=0
gates: field_count=2, text_count=0
effects: field_count=3, text_count=0
policy: field_count=3, text_count=0
execution: field_count=5, text_count=0
bottom: text_count=1, field_count=0
```

## Field semantic checks

Expected field ownership:

```text
state: origin, route, axis, path
trace: breadcrumb, trace
safety: health, risk, lock, dark_phase
gates: safe_portal, rollback
effects: host, external, requested
policy: request, policy, reason
execution: executed, mutation, server, recovery, hardware
```

Checks:

- all required fields exist;
- no duplicate field appears within the same rail;
- field order remains deterministic;
- each field appears in its expected rail;
- field source spans remain available.

## Binding semantic checks

Allowed binding prefixes:

```text
state.
preview.
```

Expected field/binding pairs:

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

Checks:

- unsupported binding prefixes are rejected;
- mismatched field/binding pairs are rejected;
- binding source spans are used for binding diagnostics.

## Text semantic checks

Expected text ownership:

```text
top rail -> first text node
bottom rail -> second text node
```

Checks:

- exactly two text nodes exist;
- top rail owns one text node;
- bottom rail owns one text node;
- no other rail owns text nodes;
- text spans remain available;
- `value_len` is used for length-aware checks.

## Card semantic checks

Required card semantics:

```text
card=NucleusPreview
effect=none
boundary=preview_only
rail_count=9
field_count=23
text_count=2
```

Checks:

- unsupported card names are rejected;
- unsupported effect values are rejected;
- unsupported boundary values are rejected;
- card counts must match aggregate AST counts;
- no-effect flags remain denied for execution, mutation, server, recovery, and hardware.

## Parser-failed behavior

If `ast->parse_result.error != LATTICRA_L_UI_PARSE_OK`, semantic validation should not inspect semantic nodes.

Expected result:

```text
status=LATTICRA_STATUS_OK
error=LATTICRA_L_UI_SEMANTIC_PARSER_FAILED
parser_error=<existing parser error>
rail_count=0
field_count=0
text_count=0
```

This does not replace parser diagnostics or failed-parse AST reports.

## Source-span behavior

Semantic failures should report the most specific span available:

```text
rail errors -> rail span
field errors -> field span
binding errors -> binding span
text errors -> text span
card/count errors -> card span
parser_failed -> parser result span
internal_error -> default span only if no better span exists
```

Semantic validation must not invent byte offsets.

## Exact implementation test list

The implementation PR should include tests for:

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
semantic_validation_report_rejects_small_buffer
semantic_validation_error_labels_are_stable
```

## Test file plan

Add:

```text
tests/l_ui_semantic_validation_invariants.c
scripts/test-l-ui-semantic-validation.sh
```

Wire into:

```text
.github/workflows/c.yml
```

Run after:

```text
sh scripts/test-l-ui-semantic-validation-contract.sh
```

and before:

```text
sh scripts/test-l-ui-string-literal-escape-contract.sh
```

## Documentation update plan

The implementation PR should update:

```text
README.md
STATUS.md
docs/FOUNDATION_INDEX.md
docs/status/CURRENT_STATUS.md
docs/status/ANNOUNCEMENTS.md
docs/project_notes/CURRENT_DIRECTION.md
docs/project_notes/UPCOMING_WORK.md
docs/strategy/2026-05-15-2249-cdt-national-security-open-system-strategy.md
docs/L_UI_SEMANTIC_VALIDATION_CONTRACT.md
scripts/test-project-strategy-status-framework.sh
```

and add:

```text
docs/L_UI_SEMANTIC_VALIDATION_IMPLEMENTATION.md
```

## No-effect preservation

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

## Compatibility expectations

The implementation must not change:

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

## Forbidden implementation behavior

Semantic validation implementation must not:

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
- make raw `value=` or `purpose=` fields authoritative for embedded NUL values;
- change compact AST report behavior;
- change failed-parse detailed report behavior.

## Current validation command

This implementation plan is guarded by:

```sh
sh scripts/test-l-ui-semantic-validation-implementation-plan.sh
```

The guard is static. It does not implement semantic validation.

## Implementation gate

Semantic validation implementation code may be added only after this plan is merged.

## Non-claims

This document does not implement semantic validation, LIR lowering, L-UI rendering, Lat execution, command behavior, Nucleus task handling, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, malware prevention, ransomware prevention, or operating-system completeness.
