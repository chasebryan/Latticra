# Latticra L-UI Parser Diagnostics Implementation

Status: implementation contract
Scope: diagnostic severity, stable codes, stable messages, hints, source spans, no-effect flags, and deterministic diagnostic reports.

## Purpose

The L-UI Parser Diagnostics implementation maps parser results into stable diagnostics.

It turns `latticra_l_ui_parse_result_t` into `latticra_l_ui_diagnostic_t` and renders deterministic diagnostic reports without adding L-UI rendering, interactive UI behavior, command behavior, Nucleus task handling, live movement, state mutation, server interaction, recovery behavior, self-update behavior, hardware behavior, or boot behavior.

## Implementation files

```text
include/latticra/l_ui_parser.h
src/l_ui_parser_diagnostics.c
tests/l_ui_parser_diagnostics_invariants.c
tests/l_ui_parser_source_span_invariants.c
scripts/test-l-ui-parser-diagnostics.sh
scripts/test-l-ui-parser-source-span.sh
```

## Public API

```text
latticra_l_ui_diagnostic_severity_label
latticra_l_ui_diagnostic_from_parse_result
latticra_l_ui_diagnostic_report
```

## Severity labels

```text
ok
error
internal
```

## Diagnostic fields

```text
severity
code
message
hint
line
column
span
no_effect
execution_allowed
mutation_allowed
server_allowed
recovery_allowed
hardware_allowed
```

The diagnostic span contains:

```text
start_offset
end_offset
start_line
start_column
end_line
end_column
```

Diagnostics copy span metadata from parse results.

## Report shape

The diagnostic report renders:

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
span_start_offset=<n>
span_end_offset=<n>
span_start_line=<n>
span_start_column=<n>
span_end_line=<n>
span_end_column=<n>
```

## Stable diagnostic mapping

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

## No-effect boundary

Diagnostics copy the safety flags from parse results and preserve:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

## Test commands

Run:

```sh
sh scripts/test-l-ui-parser-diagnostics.sh
sh scripts/test-l-ui-parser-source-span.sh
```

The main C workflow runs these checks after the parser diagnostics implementation plan guard and source-span implementation plan guard.

## Required invariants

The diagnostics tests verify:

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

The source-span tests verify diagnostic span copying and diagnostic report span fields.

## Current evidence level

This implementation is an L2 tested diagnostics and source-span metadata model for the L-UI parser.

It is not a renderer, UI runtime, command surface, Nucleus task runner, server client, update engine, recovery system, hardware system, boot system, AST system, or security boundary.

## Next implementation step

The next implementation candidate after source spans is:

```text
L-UI parser AST contract
```

That future work should define AST shape, node ownership, source-span usage, and no-effect boundaries before any AST implementation.

## Non-claims

This document and implementation do not claim AST construction, L-UI rendering, command behavior, Nucleus task handling, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.
