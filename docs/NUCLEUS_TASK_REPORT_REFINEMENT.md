# Latticra Nucleus Task Report Refinement

Status: initial Nucleus task report refinement implementation
Scope: deterministic no-effect task report classification, task-domain labeling, authorization-state labeling, prerequisite reporting, no-effect-chain reporting, invariant tests, and workflow coverage.

## Purpose

This document records the Nucleus task report refinement after the runtime boundary policy matrix refinement.

The goal is to make Nucleus task reports more explicit about what kind of task decision was made, which task domain it belongs to, and whether prerequisites and no-effect posture remained intact.

This refinement does not execute tasks, mutate state, perform I/O, open network connections, touch hardware, control a terminal, or provide runtime behavior.

## Added report metadata

The Nucleus task record now includes:

```text
report_classification
task_domain
authorization_state
prerequisites_satisfied
no_effect_chain_ok
```

The deterministic `LATTICRA NUCLEUS TASK REPORT` now emits those fields.

## Report classifications

Initial report classifications:

```text
accepted
future-gated
denied
invalid
```

## Task domains

Initial task domains:

```text
state
transition
render
lat
lir
authority
server
update
recovery
hardware
boot
unknown
```

## Authorization states

Initial authorization states:

```text
not-requested
checked
denied
reserved-for-future
unavailable
```

## Deterministic report meaning

The refinement reports:

```text
accepted -> task accepted as no-effect report, preview, or validation
future-gated -> operational task remains behind a future gate
denied -> known task rejected by prerequisites, authority, operator, or effect policy
invalid -> null, unknown, or malformed task/effect identity
```

`prerequisites_satisfied` is true only when the task classification reason is `ok`.

`no_effect_chain_ok` is true only when result-level and record-level execution/mutation/server/recovery/hardware flags remain denied and no-effect is preserved.

## Implementation files

This slice updates or adds:

```text
include/latticra/nucleus_task.h
src/nucleus_task.c
tests/nucleus_task_report_refinement.c
scripts/test-nucleus-task-execution.sh
docs/NUCLEUS_TASK_REPORT_REFINEMENT.md
scripts/test-nucleus-task-report-refinement.sh
.github/workflows/nucleus-task-report-refinement.yml
```

## Validation

Run:

```sh
sh scripts/test-nucleus-task-report-refinement.sh
sh scripts/test-nucleus-task-execution.sh
```

The focused invariant tests verify:

```text
nucleus_task_report_refinement_labels_are_stable
nucleus_task_report_refinement_reports_accepted_state_report
nucleus_task_report_refinement_reports_authority_check
nucleus_task_report_refinement_reports_future_gated_task
nucleus_task_report_refinement_reports_denied_prerequisite
nucleus_task_report_refinement_reports_invalid_request
```

## Compatibility

This refinement preserves existing Nucleus task behavior for:

```text
state-report preview/report behavior
transition-preview behavior
render-report behavior
Lat validation behavior
LIR validation behavior
authority-check behavior
future-gated operational task kinds
unknown request denial
unknown effect denial
operator-confirmation non-override behavior
small-buffer behavior
```

## Non-claims

This report refinement does not provide:

```text
task execution
runtime behavior
command execution
Lat execution
LIR execution
state mutation
file I/O
network I/O
server interaction
self-update
recovery behavior
rollback behavior
hardware support
boot behavior
terminal control
security isolation
sandboxing
malware prevention
ransomware prevention
certification
accreditation
operating-system completeness
```
