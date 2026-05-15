# Latticra L-UI Parser Diagnostics Implementation Plan

Status: implementation planning contract
Scope: diagnostic API shape, exact tests, parser result report extension rules, and no-effect constraints before diagnostic code.

## Purpose

This document defines the implementation plan for richer L-UI parser diagnostics.

The diagnostics contract is already merged and guarded. This plan decides the C API, data shape, exact test list, and report extension rules before implementation code is added.

## Relationship to previous contracts

This plan depends on:

```text
docs/L_UI_PARSER_DIAGNOSTICS.md
docs/L_UI_PARSER.md
docs/L_UI_PARSER_RESULT_REPORT.md
include/latticra/l_ui_parser.h
src/l_ui_parser.c
```

Those files remain the source of truth for parser errors, parse summaries, no-effect flags, and current result reporting.

## Implementation language decision

The first diagnostics implementation should be in C.

Reason:

- the parser is already implemented in C;
- diagnostics should be part of the same low-level ABI surface;
- the implementation should remain portable and deterministic;
- diagnostics should require no runtime beyond the current C test environment.

## Proposed module shape

The first diagnostics implementation should extend the existing parser module:

```text
include/latticra/l_ui_parser.h
src/l_ui_parser.c
tests/l_ui_parser_diagnostics_invariants.c
scripts/test-l-ui-parser-diagnostics.sh
```

A separate diagnostics source file is not required for the first implementation.

## Diagnostic enums

Add diagnostic severity enum:

```text
LATTICRA_L_UI_DIAGNOSTIC_OK
LATTICRA_L_UI_DIAGNOSTIC_ERROR
LATTICRA_L_UI_DIAGNOSTIC_INTERNAL
```

Diagnostic codes should remain stable strings instead of a second enum in the first implementation.

Reason: parser errors already have a stable enum. Code strings can be mapped directly from the parser error enum.

## Diagnostic result shape

Add a compact diagnostic struct:

```text
severity
code
message
hint
line
column
no_effect
execution_allowed
mutation_allowed
server_allowed
recovery_allowed
hardware_allowed
```

Recommended fixed sizes:

```text
LATTICRA_L_UI_DIAGNOSTIC_CODE_MAX = 16
LATTICRA_L_UI_DIAGNOSTIC_MESSAGE_MAX = 128
LATTICRA_L_UI_DIAGNOSTIC_HINT_MAX = 128
LATTICRA_L_UI_DIAGNOSTIC_REPORT_MAX = 1024
```

## Public API plan

Initial functions:

```text
const char *latticra_l_ui_diagnostic_severity_label(
    latticra_l_ui_diagnostic_severity_t severity);

latticra_status_t latticra_l_ui_diagnostic_from_parse_result(
    const latticra_l_ui_parse_result_t *parse_result,
    latticra_l_ui_diagnostic_t *diagnostic);

latticra_status_t latticra_l_ui_diagnostic_report(
    const latticra_l_ui_diagnostic_t *diagnostic,
    char *buffer,
    size_t buffer_len);
```

## Parser result report extension

The current parser result report should not be changed in the first diagnostics implementation.

Instead, diagnostics should have a separate deterministic report:

```text
L-UI PARSE DIAGNOSTIC
severity=<severity>
code=<code>
message=<message>
line=<line>
column=<column>
hint=<hint-or-empty>
no_effect=<0|1>
execution_allowed=<0|1>
mutation_allowed=<0|1>
server_allowed=<0|1>
recovery_allowed=<0|1>
hardware_allowed=<0|1>
```

This avoids destabilizing the existing parser result report.

## Mapping table

The first implementation should map parser errors to diagnostic fields exactly:

| Parser error | Severity | Code | Message |
| --- | --- | --- | --- |
| `ok` | `ok` | `LUI0000` | Parse completed successfully. |
| `null_argument` | `error` | `LUI0001` | Parser received a null argument. |
| `empty_source` | `error` | `LUI0002` | L-UI source is empty. |
| `unsupported_version` | `error` | `LUI0003` | L-UI version is not supported. |
| `missing_card` | `error` | `LUI0004` | Required card declaration is missing. |
| `missing_purpose` | `error` | `LUI0005` | Required purpose clause is missing. |
| `missing_effect` | `error` | `LUI0006` | Required effect clause is missing. |
| `unsupported_effect` | `error` | `LUI0007` | Effect declaration is not supported. |
| `missing_boundary` | `error` | `LUI0008` | Required boundary clause is missing. |
| `unsupported_boundary` | `error` | `LUI0009` | Boundary declaration is not supported. |
| `missing_rail` | `error` | `LUI0010` | Required rail is missing. |
| `unknown_rail` | `error` | `LUI0011` | Rail name is not supported. |
| `unknown_binding_prefix` | `error` | `LUI0012` | Binding prefix is not supported. |
| `missing_required_binding` | `error` | `LUI0013` | Required binding is missing. |
| `unterminated_string` | `error` | `LUI0014` | String literal is not terminated. |
| `unbalanced_brace` | `error` | `LUI0015` | Braces are not balanced. |
| `forbidden_behavior_marker` | `error` | `LUI0016` | Source contains a forbidden behavior marker. |
| `source_too_large` | `error` | `LUI0017` | Source exceeds the supported size limit. |
| `internal_error` | `internal` | `LUI0018` | Parser reached an internal error. |

## Hint mapping

Initial hints:

```text
LUI0000 -> empty hint
LUI0001 -> Provide non-null source and result pointers.
LUI0002 -> Provide L-UI source beginning with: lui 0.1
LUI0003 -> Use version header: lui 0.1
LUI0004 -> Add card NucleusPreview { ... }
LUI0005 -> Add a purpose string.
LUI0006 -> Add effect none.
LUI0007 -> Use only effect none.
LUI0008 -> Add boundary preview_only.
LUI0009 -> Use only boundary preview_only.
LUI0010 -> Add the required NucleusPreview rails.
LUI0011 -> Use only documented rail names.
LUI0012 -> Use only state. or preview. binding prefixes.
LUI0013 -> Add all required NucleusPreview bindings.
LUI0014 -> Close the string literal.
LUI0015 -> Balance opening and closing braces.
LUI0016 -> Remove behavior markers outside the static report grammar.
LUI0017 -> Keep L-UI source at or below LATTICRA_L_UI_SOURCE_MAX.
LUI0018 -> Report the internal parser error.
```

Hints must not suggest behavior outside the current no-effect grammar.

## Line and column behavior

The first implementation should copy line and column from the parse result.

Current parser line and column are conservative:

```text
line=1
column=1
```

The diagnostics implementation should not attempt richer location detection yet.

## No-effect flags

Diagnostics must copy safety flags from parse results:

```text
no_effect
execution_allowed
mutation_allowed
server_allowed
recovery_allowed
hardware_allowed
```

For all current parse paths, expected values remain:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

## Exact test list

The first diagnostics implementation PR should include tests for:

```text
ok_result_has_lui0000
empty_source_reports_lui0002
unsupported_version_reports_lui0003
missing_card_reports_lui0004
missing_purpose_reports_lui0005
missing_effect_reports_lui0006
unsupported_effect_reports_lui0007
missing_boundary_reports_lui0008
unsupported_boundary_reports_lui0009
missing_rail_reports_lui0010
unknown_binding_prefix_reports_lui0012
missing_required_binding_reports_lui0013
unterminated_string_reports_lui0014
unbalanced_brace_reports_lui0015
forbidden_marker_reports_lui0016
source_too_large_reports_lui0017
internal_error_reports_lui0018
error_diagnostics_preserve_no_effect_flags
line_and_column_are_one_based
messages_are_stable
hints_are_stable
diagnostic_report_contains_required_fields
diagnostic_report_rejects_bad_arguments_and_small_buffers
severity_labels_are_stable
```

## CI requirement

The first diagnostics implementation PR must add:

```text
scripts/test-l-ui-parser-diagnostics.sh
```

and wire it into:

```text
.github/workflows/c.yml
```

## Documentation requirement

The first diagnostics implementation PR must update:

```text
README.md
docs/FOUNDATION_INDEX.md
docs/L_UI_PARSER_DIAGNOSTICS.md
```

and add:

```text
docs/L_UI_PARSER_DIAGNOSTICS_IMPLEMENTATION.md
```

## Forbidden implementation behavior

The diagnostics implementation must not:

- parse files directly;
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
- accept unsupported effects.

## Current validation command

This plan is guarded by:

```sh
sh scripts/test-l-ui-parser-diagnostics-implementation-plan.sh
```

The guard is static. It does not implement diagnostics.

## Implementation gate

Diagnostics implementation code may be added only after this plan is merged.

## Non-claims

This document does not implement richer parser diagnostics, L-UI rendering, command behavior, Nucleus task handling, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.
