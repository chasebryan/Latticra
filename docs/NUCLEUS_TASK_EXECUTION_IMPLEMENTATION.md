# Latticra Nucleus Task Execution Implementation

Status: initial implementation contract
Scope: first no-effect C Nucleus task classification/report surface, denied-by-default policy, authority prerequisites, effect-gate metadata, caller-provided buffers, deterministic reports, invariant tests, compatibility expectations, and non-claims.

## Purpose

This document records the first Nucleus task execution implementation slice.

The implementation follows:

```text
docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md
docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION_PLAN.md
```

This slice implements task classification and report generation only.

It does not execute tasks.

## Implementation files

This slice adds:

```text
include/latticra/nucleus_task.h
src/nucleus_task.c
tests/nucleus_task_execution_invariants.c
scripts/test-nucleus-task-execution.sh
```

It also wires the test runner into:

```text
.github/workflows/c.yml
```

## Public API

The public API is:

```text
latticra_nucleus_task_request_kind_t
latticra_nucleus_task_effect_t
latticra_nucleus_task_policy_t
latticra_nucleus_task_denial_t
latticra_nucleus_task_gate_state_t
latticra_nucleus_task_operator_confirmation_t
latticra_nucleus_task_rollback_state_t
latticra_nucleus_task_authority_summary_t
latticra_nucleus_task_request_t
latticra_nucleus_task_record_t
latticra_nucleus_task_result_t
latticra_nucleus_task_request_kind_label
latticra_nucleus_task_effect_label
latticra_nucleus_task_policy_label
latticra_nucleus_task_denial_label
latticra_nucleus_task_gate_state_label
latticra_nucleus_task_operator_confirmation_label
latticra_nucleus_task_rollback_state_label
latticra_nucleus_task_classify
latticra_nucleus_task_report
```

## Capacity constants

The implementation defines:

```text
LATTICRA_NUCLEUS_TASK_ID_MAX 64u
LATTICRA_NUCLEUS_TASK_LABEL_MAX 64u
LATTICRA_NUCLEUS_TASK_REASON_MAX 128u
LATTICRA_NUCLEUS_TASK_SOURCE_IDENTITY_MAX 128u
LATTICRA_NUCLEUS_TASK_REPORT_MAX 4096u
LATTICRA_NUCLEUS_TASK_RECORD_MAX 16u
```

The task report uses caller-provided buffers and fixed-size task records.

## Request kinds

Supported request kind labels:

```text
state-report
transition-preview
render-report
lat-validate
lir-validate
authority-check
server-interaction
self-update
recovery-action
hardware-action
boot-action
unknown
```

## Effects

Supported task effect labels:

```text
none
read
local_mutation
host_mutation
network
hardware
boot
recovery
external
unknown
```

Only `none` and `read` may be eligible for no-effect report, preview, or validation classifications.

## Policy results

Supported policy labels:

```text
allow-preview
allow-report
allow-validation
deny
blocked
requires-future-gate
unsupported
internal-error
```

The implementation does not produce an executed effect-performing task.

## Denial reasons

Stable denial labels:

```text
ok
null-argument
unknown-request
unknown-effect
unsupported-request
unsupported-effect
parser-failed
semantic-failed
lir-failed
render-failed
authority-failed
effect-blocked
effect-requires-future-gate
non-no-effect-flags
operator-confirmation-not-supported
implementation-not-present
internal-error
```

## Classification behavior

Implemented classification behavior:

```text
state-report + none -> allow-report
state-report + read -> allow-report
transition-preview + none -> allow-preview
transition-preview + read -> allow-preview
render-report + none -> allow-report
render-report + read -> allow-report
lat-validate + none -> allow-validation
lat-validate + read -> allow-validation
lir-validate + none -> allow-validation
lir-validate + read -> allow-validation
authority-check + none -> allow-validation
authority-check + read -> allow-validation
server-interaction -> requires-future-gate
self-update -> requires-future-gate
recovery-action -> requires-future-gate
hardware-action -> requires-future-gate
boot-action -> requires-future-gate
unknown -> deny
unknown effect -> deny
local_mutation -> deny
host_mutation -> deny
network -> deny
hardware -> deny
boot -> deny
recovery -> deny
external -> deny
```

Allowed classifications still set:

```text
executed=0
mutation_allowed=0
server_interaction_allowed=0
recovery_allowed=0
hardware_allowed=0
```

## Prerequisite behavior

The implementation checks:

```text
request presence
result presence
authority presence
authority status
authority no-effect flags
operator confirmation metadata
Nucleus preview policy for state-report and transition-preview
render status for render-report
Lat parse status for lat-validate
LIR status for lir-validate
source identity capacity
```

Failed prerequisites deny the task and remain visible in the report.

## Report format

`latticra_nucleus_task_report` emits:

```text
LATTICRA NUCLEUS TASK REPORT
status=<integer-status>
task_id=<id>
request=<request-kind>
requested_effect=<effect>
allowed_effect=<effect>
policy=<policy-result>
reason=<denial-reason>
authority_status=<authority-status>
authority_validator=<authority-validator>
authority_reason=<authority-reason>
gate_state=<gate-state>
operator_confirmation=<confirmation-state>
executed=0
mutation_allowed=0
server_interaction_allowed=0
recovery_allowed=0
hardware_allowed=0
rollback_state=<rollback-state>
evidence_level=<level>
source_identity=<source>
span_start_offset=<offset>
span_end_offset=<offset>
```

Small buffers return `LATTICRA_STATUS_BUFFER_TOO_SMALL` and clear the output buffer.

## No-effect behavior

The implementation preserves:

```text
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
```

It does not execute commands, mutate state, open network connections, write files, read host files outside metadata, call server code, call update code, call recovery code, touch hardware, alter boot state, or perform rollback.

## Validation

Run:

```sh
sh scripts/test-nucleus-task-execution.sh
```

The test suite covers:

```text
nucleus_task_execution_denies_unknown_request
nucleus_task_execution_denies_unknown_effect
nucleus_task_execution_preserves_preview_only_boundary
nucleus_task_execution_requires_authority_success
nucleus_task_execution_requires_effect_gate_success
nucleus_task_execution_requires_no_effect_flags
nucleus_task_execution_allows_state_report_preview_only
nucleus_task_execution_allows_transition_preview_only
nucleus_task_execution_allows_render_report_only
nucleus_task_execution_allows_lat_validation_only
nucleus_task_execution_allows_lir_validation_only
nucleus_task_execution_denies_server_interaction
nucleus_task_execution_denies_self_update
nucleus_task_execution_denies_recovery_action
nucleus_task_execution_denies_hardware_action
nucleus_task_execution_denies_boot_action
nucleus_task_execution_report_is_deterministic
nucleus_task_execution_report_rejects_small_buffer
nucleus_task_execution_does_not_mutate_state
nucleus_task_execution_does_not_open_network
nucleus_task_execution_does_not_touch_hardware
nucleus_task_execution_does_not_write_files
nucleus_task_execution_does_not_call_recovery
nucleus_task_execution_does_not_override_policy_with_operator_confirmation
```

## Compatibility expectations

This implementation must not change:

```text
existing Nucleus preview classification behavior
existing Nucleus preview report behavior
state lattice behavior
tri-plane transition behavior
L-UI parser behavior
L-UI semantic validation behavior
LIR shape behavior
L-UI rendering behavior
Lat grammar behavior
constrained C++ authority behavior
no-effect flags
current accepted fixture counts
```

## Current boundary

This implementation does not provide:

```text
command behavior
Lat execution
LIR execution
live movement
state mutation
file I/O
network I/O
server interaction
self-update
recovery behavior
rollback
hardware support
boot behavior
terminal control
security isolation
sandboxing
malware prevention
ransomware prevention
operating-system completeness
```

## Non-claims

This document and implementation do not claim a finished operating system, hardened sandbox, production runtime, production security boundary, malware prevention, ransomware prevention, recovery system, update system, bootable image, public task executor, or public release readiness.
