# Latticra L-UI Parser Diagnostics Contract

Status: diagnostics contract
Scope: stable parser diagnostic language, line/column behavior, result reporting, and implementation guardrails before richer diagnostics code.

## Purpose

This document defines the diagnostics contract for the L-UI parser.

The current parser already returns an error category, line, column, and deterministic result report. This contract defines how those fields should become stable diagnostic language before richer diagnostic implementation is added.

This document does not implement new diagnostics.

## Current boundary

The current parser provides:

```text
parse status
parse error category
line
column
card name
rail count
field count
effect
boundary
no-effect flags
parser result report
```

This contract does not add:

```text
renderer behavior
interactive UI behavior
command behavior
Nucleus task handling
live movement
state mutation
server interaction
self-update behavior
hardware behavior
boot behavior
recovery behavior
```

## Diagnostic shape

A future diagnostic should be representable as:

```text
severity=<severity>
code=<stable-code>
message=<stable-message>
line=<line>
column=<column>
hint=<optional-remediation-hint>
```

## Severity levels

Initial severity levels:

```text
ok
error
internal
```

Meanings:

| Severity | Meaning |
| --- | --- |
| `ok` | Valid parse result. |
| `error` | Source was rejected with a stable user-facing reason. |
| `internal` | Unexpected parser-side failure or unknown category. |

## Stable diagnostic codes

Diagnostic codes should mirror parser error labels.

Initial codes:

```text
LUI0000 ok
LUI0001 null_argument
LUI0002 empty_source
LUI0003 unsupported_version
LUI0004 missing_card
LUI0005 missing_purpose
LUI0006 missing_effect
LUI0007 unsupported_effect
LUI0008 missing_boundary
LUI0009 unsupported_boundary
LUI0010 missing_rail
LUI0011 unknown_rail
LUI0012 unknown_binding_prefix
LUI0013 missing_required_binding
LUI0014 unterminated_string
LUI0015 unbalanced_brace
LUI0016 forbidden_behavior_marker
LUI0017 source_too_large
LUI0018 internal_error
```

## Stable messages

Initial message language should be concise and deterministic:

| Code | Message |
| --- | --- |
| `LUI0000` | Parse completed successfully. |
| `LUI0001` | Parser received a null argument. |
| `LUI0002` | L-UI source is empty. |
| `LUI0003` | L-UI version is not supported. |
| `LUI0004` | Required card declaration is missing. |
| `LUI0005` | Required purpose clause is missing. |
| `LUI0006` | Required effect clause is missing. |
| `LUI0007` | Effect declaration is not supported. |
| `LUI0008` | Required boundary clause is missing. |
| `LUI0009` | Boundary declaration is not supported. |
| `LUI0010` | Required rail is missing. |
| `LUI0011` | Rail name is not supported. |
| `LUI0012` | Binding prefix is not supported. |
| `LUI0013` | Required binding is missing. |
| `LUI0014` | String literal is not terminated. |
| `LUI0015` | Braces are not balanced. |
| `LUI0016` | Source contains a forbidden behavior marker. |
| `LUI0017` | Source exceeds the supported size limit. |
| `LUI0018` | Parser reached an internal error. |

## Line and column behavior

Line and column should be one-based.

Default values:

```text
line=1
column=1
```

A future diagnostics implementation may improve precision, but it must remain deterministic and must not require file I/O inside parser code.

Rules:

1. If a precise location is not available, return `line=1` and `column=1`.
2. If a token location is available, line and column should point to the beginning of the rejected token or clause.
3. Line and column should count bytes in the in-memory source buffer, not terminal display cells.
4. Diagnostics must not depend on platform-specific newline behavior.
5. Diagnostics must preserve no-effect flags.

## Hint language

Hints should be stable and optional.

Initial hint examples:

```text
Use version header: lui 0.1
Add card NucleusPreview { ... }
Add effect none
Add boundary preview_only
Use only state. or preview. binding prefixes
Remove unsupported effect declarations
```

Hints must not suggest behavior outside the current no-effect grammar.

## Report integration

A future parser diagnostic report may extend the current parser result report with:

```text
diagnostic_severity=<severity>
diagnostic_code=<code>
diagnostic_message=<message>
diagnostic_hint=<hint-or-empty>
```

This should be added only after tests lock down stable codes and messages.

## Required test plan for future diagnostics implementation

Future diagnostics tests should verify:

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
error_diagnostics_preserve_no_effect_flags
unknown_error_reports_internal
line_and_column_are_one_based
messages_are_stable
```

## Implementation gate

Diagnostic implementation code should not be added until:

1. this contract is merged;
2. diagnostic codes are stable;
3. message text is stable;
4. line and column behavior is accepted;
5. tests preserve no-effect flags;
6. result report extension shape is documented.

## Current validation command

This contract is guarded by:

```sh
sh scripts/test-l-ui-parser-diagnostics-contract.sh
```

The guard is static. It does not implement diagnostics.

## Non-claims

This document does not implement richer parser diagnostics, L-UI rendering, command behavior, Nucleus task handling, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.
