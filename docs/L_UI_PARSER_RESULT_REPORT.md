# Latticra L-UI Parser Result Report

Status: initial implementation contract
Scope: deterministic text reports for L-UI parse summaries.

## Purpose

The L-UI Parser Result Report renders `latticra_l_ui_parse_result_t` as deterministic text.

It exists so parser status, errors, counts, effect labels, boundary labels, and no-effect flags are operator-visible without adding an L-UI renderer, interactive UI, command behavior, or Nucleus task handling.

## Implementation files

```text
include/latticra/l_ui_parser.h
src/l_ui_parser.c
tests/l_ui_parser_result_report_invariants.c
scripts/test-l-ui-parser-result-report.sh
```

## Public API

```text
latticra_l_ui_parse_result_report
```

## Report shape

The report must render:

```text
L-UI PARSE RESULT
status=<status-code>
error=<error-label>
line=<line>
column=<column>
card_name=<card-name>
rail_count=<rail-count>
field_count=<field-count>
effect=<effect>
boundary=<boundary>
no_effect=<0|1>
execution_allowed=<0|1>
mutation_allowed=<0|1>
server_allowed=<0|1>
recovery_allowed=<0|1>
hardware_allowed=<0|1>
```

## Expected valid summary

For the first accepted fixture, the report should include:

```text
error=ok
card_name=NucleusPreview
rail_count=9
field_count=23
effect=none
boundary=preview_only
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

## Expected error summary

Error results must also preserve no-effect flags:

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
sh scripts/test-l-ui-parser-result-report.sh
```

The main C workflow runs this check after parser fixture integration.

## Boundary

This report must not add:

- L-UI rendering;
- interactive UI behavior;
- command behavior;
- Nucleus task handling;
- live movement;
- state mutation;
- recovery behavior;
- server interaction;
- self-update behavior;
- host effects;
- network effects;
- hardware effects;
- boot effects.

## Current evidence level

This implementation is an L2 tested report surface for L-UI parse summaries.

It is not a renderer, UI runtime, command surface, Nucleus task runner, server client, update engine, recovery system, hardware system, boot system, or security boundary.

## Next implementation step

The next implementation candidate after parser result reporting is:

```text
L-UI parser diagnostics contract
```

That future work should define stable diagnostic language and line/column behavior before richer parser diagnostics are implemented.

## Non-claims

This document and implementation do not claim L-UI rendering, command behavior, Nucleus task handling, live movement, origin mutation, recovery behavior, server interaction, self-update, hardware support, boot readiness, security isolation, sandboxing, or operating-system completeness.
