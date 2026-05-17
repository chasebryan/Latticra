# Latticra Nucleus Task Execution Implementation Plan

Status: implementation planning contract
Scope: exact public API, C implementation files, task request/result/record structs, policy enum, denial enum, effect-gate enum usage, authority summary usage, operator-confirmation metadata, rollback metadata, report format, capacity constants, output-buffer behavior, tests, compatibility expectations, and non-claims before Nucleus task execution code.

## Purpose

This document defines the implementation plan for the first Nucleus task execution surface.

The Nucleus task execution contract is already merged and guarded. This plan turns that contract into exact public API, file paths, structures, enums, capacity constants, report rules, prerequisite behavior, effect-gate behavior, authority-summary behavior, task-record behavior, exact tests, compatibility expectations, and non-claims before task execution code is added.

This document does not implement Nucleus task execution.

## Relationship to previous work

This plan depends on:

```text
docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md
docs/NUCLEUS_PREVIEW.md
docs/EFFECT_GATES.md
docs/STATE_LATTICE.md
docs/TRI_PLANE_TRANSITION.md
docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION.md
docs/L_UI_RENDERING_IMPLEMENTATION.md
docs/LIR_SHAPE_IMPLEMENTATION.md
docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md
include/latticra/nucleus_preview.h
include/latticra/state_lattice.h
include/latticra/tri_plane_transition.h
include/latticra/l_ui_renderer.h
include/latticra/lir.h
include/latticra/lat_parser.h
include/latticra/cpp/authority.hpp
src/nucleus_preview.c
src/l_ui_renderer.c
src/lir.c
src/lat_parser.c
src/cpp/authority.cpp
```

Those files remain the source of truth for preview classification, effect vocabulary, state lattice, transition preview, constrained authority, rendering, LIR metadata, Lat metadata, and no-effect boundaries.

## Implementation language decision

The first Nucleus task execution surface should be implemented in C.

Reason:

- current Nucleus preview classification is C;
- state lattice and tri-plane transition are C;
- L-UI rendering and LIR shape are C;
- the task surface should use bounded structs and caller-provided buffers;
- C remains the secure substrate;
- the constrained C++ authority layer remains a validation/report dependency, not the task-record storage substrate.

The first implementation should not include C++ object lifetimes in the public C API.

## Implementation files

The implementation PR should add or modify:

```text
include/latticra/nucleus_task.h
src/nucleus_task.c
tests/nucleus_task_execution_invariants.c
scripts/test-nucleus-task-execution.sh
.github/workflows/c.yml
docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md
```

The implementation PR should not add command behavior, Lat execution, LIR execution, live movement, mutation, file I/O, network I/O, server interaction, self-update, recovery behavior, rollback, hardware behavior, boot behavior, terminal control, sandboxing, malware prevention, ransomware prevention, or operating-system behavior.

## Public API shape

Add public API names:

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

Recommended function signatures:

```text
const char *latticra_nucleus_task_request_kind_label(latticra_nucleus_task_request_kind_t kind);
const char *latticra_nucleus_task_effect_label(latticra_nucleus_task_effect_t effect);
const char *latticra_nucleus_task_policy_label(latticra_nucleus_task_policy_t policy);
const char *latticra_nucleus_task_denial_label(latticra_nucleus_task_denial_t denial);
const char *latticra_nucleus_task_gate_state_label(latticra_nucleus_task_gate_state_t gate_state);
const char *latticra_nucleus_task_operator_confirmation_label(latticra_nucleus_task_operator_confirmation_t confirmation);
const char *latticra_nucleus_task_rollback_state_label(latticra_nucleus_task_rollback_state_t rollback_state);

latticra_status_t latticra_nucleus_task_classify(
    const latticra_nucleus_task_request_t *request,
    latticra_nucleus_task_result_t *result);

latticra_status_t latticra_nucleus_task_report(
    const latticra_nucleus_task_result_t *result,
    char *buffer,
    size_t buffer_len);
```

The first implementation should classify and report only. It must not execute work.

## Capacity constants

Add exact bounded constants:

```text
LATTICRA_NUCLEUS_TASK_ID_MAX 64u
LATTICRA_NUCLEUS_TASK_LABEL_MAX 64u
LATTICRA_NUCLEUS_TASK_REASON_MAX 128u
LATTICRA_NUCLEUS_TASK_SOURCE_IDENTITY_MAX 128u
LATTICRA_NUCLEUS_TASK_REPORT_MAX 4096u
LATTICRA_NUCLEUS_TASK_RECORD_MAX 16u
```

Small output buffers must return `LATTICRA_STATUS_BUFFER_TOO_SMALL` and clear the output buffer.

## Request kind enum

Add request kinds:

```text
LATTICRA_NUCLEUS_TASK_STATE_REPORT
LATTICRA_NUCLEUS_TASK_TRANSITION_PREVIEW
LATTICRA_NUCLEUS_TASK_RENDER_REPORT
LATTICRA_NUCLEUS_TASK_LAT_VALIDATE
LATTICRA_NUCLEUS_TASK_LIR_VALIDATE
LATTICRA_NUCLEUS_TASK_AUTHORITY_CHECK
LATTICRA_NUCLEUS_TASK_SERVER_INTERACTION
LATTICRA_NUCLEUS_TASK_SELF_UPDATE
LATTICRA_NUCLEUS_TASK_RECOVERY_ACTION
LATTICRA_NUCLEUS_TASK_HARDWARE_ACTION
LATTICRA_NUCLEUS_TASK_BOOT_ACTION
LATTICRA_NUCLEUS_TASK_UNKNOWN
```

Stable labels:

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

## Effect enum

Add task effects:

```text
LATTICRA_NUCLEUS_TASK_EFFECT_NONE
LATTICRA_NUCLEUS_TASK_EFFECT_READ
LATTICRA_NUCLEUS_TASK_EFFECT_LOCAL_MUTATION
LATTICRA_NUCLEUS_TASK_EFFECT_HOST_MUTATION
LATTICRA_NUCLEUS_TASK_EFFECT_NETWORK
LATTICRA_NUCLEUS_TASK_EFFECT_HARDWARE
LATTICRA_NUCLEUS_TASK_EFFECT_BOOT
LATTICRA_NUCLEUS_TASK_EFFECT_RECOVERY
LATTICRA_NUCLEUS_TASK_EFFECT_EXTERNAL
LATTICRA_NUCLEUS_TASK_EFFECT_UNKNOWN
```

Stable labels:

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

## Policy enum

Add task policies:

```text
LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_PREVIEW
LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_REPORT
LATTICRA_NUCLEUS_TASK_POLICY_ALLOW_VALIDATION
LATTICRA_NUCLEUS_TASK_POLICY_DENY
LATTICRA_NUCLEUS_TASK_POLICY_BLOCKED
LATTICRA_NUCLEUS_TASK_POLICY_REQUIRES_FUTURE_GATE
LATTICRA_NUCLEUS_TASK_POLICY_UNSUPPORTED
LATTICRA_NUCLEUS_TASK_POLICY_INTERNAL_ERROR
```

Stable labels:

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

The first implementation must not produce an executed effect-performing task.

## Denial enum

Add denial reasons:

```text
LATTICRA_NUCLEUS_TASK_DENIAL_OK
LATTICRA_NUCLEUS_TASK_DENIAL_NULL_ARGUMENT
LATTICRA_NUCLEUS_TASK_DENIAL_UNKNOWN_REQUEST
LATTICRA_NUCLEUS_TASK_DENIAL_UNKNOWN_EFFECT
LATTICRA_NUCLEUS_TASK_DENIAL_UNSUPPORTED_REQUEST
LATTICRA_NUCLEUS_TASK_DENIAL_UNSUPPORTED_EFFECT
LATTICRA_NUCLEUS_TASK_DENIAL_PARSER_FAILED
LATTICRA_NUCLEUS_TASK_DENIAL_SEMANTIC_FAILED
LATTICRA_NUCLEUS_TASK_DENIAL_LIR_FAILED
LATTICRA_NUCLEUS_TASK_DENIAL_RENDER_FAILED
LATTICRA_NUCLEUS_TASK_DENIAL_AUTHORITY_FAILED
LATTICRA_NUCLEUS_TASK_DENIAL_EFFECT_BLOCKED
LATTICRA_NUCLEUS_TASK_DENIAL_EFFECT_REQUIRES_FUTURE_GATE
LATTICRA_NUCLEUS_TASK_DENIAL_NON_NO_EFFECT_FLAGS
LATTICRA_NUCLEUS_TASK_DENIAL_OPERATOR_CONFIRMATION_NOT_SUPPORTED
LATTICRA_NUCLEUS_TASK_DENIAL_IMPLEMENTATION_NOT_PRESENT
LATTICRA_NUCLEUS_TASK_DENIAL_INTERNAL_ERROR
```

Stable labels:

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

## Gate state enum

Add gate states:

```text
LATTICRA_NUCLEUS_TASK_GATE_DISABLED
LATTICRA_NUCLEUS_TASK_GATE_BLOCKED
LATTICRA_NUCLEUS_TASK_GATE_PLANNED
LATTICRA_NUCLEUS_TASK_GATE_AVAILABLE
LATTICRA_NUCLEUS_TASK_GATE_ARMED
LATTICRA_NUCLEUS_TASK_GATE_EXECUTED
LATTICRA_NUCLEUS_TASK_GATE_FAILED
```

Stable labels:

```text
disabled
blocked
planned
available
armed
executed
failed
```

The first implementation should output only `disabled`, `blocked`, or `planned` for real classifications.

## Operator confirmation enum

Add operator-confirmation states:

```text
LATTICRA_NUCLEUS_TASK_OPERATOR_NOT_APPLICABLE
LATTICRA_NUCLEUS_TASK_OPERATOR_REQUIRED
LATTICRA_NUCLEUS_TASK_OPERATOR_PRESENT
LATTICRA_NUCLEUS_TASK_OPERATOR_REJECTED
LATTICRA_NUCLEUS_TASK_OPERATOR_NOT_SUPPORTED
```

Stable labels:

```text
not-applicable
required
present
rejected
not-supported
```

The first implementation must treat confirmation as metadata only. Confirmation must not override policy.

## Rollback state enum

Add rollback states:

```text
LATTICRA_NUCLEUS_TASK_ROLLBACK_NOT_APPLICABLE
LATTICRA_NUCLEUS_TASK_ROLLBACK_NOT_AVAILABLE
LATTICRA_NUCLEUS_TASK_ROLLBACK_REQUIRED
LATTICRA_NUCLEUS_TASK_ROLLBACK_READY
LATTICRA_NUCLEUS_TASK_ROLLBACK_BLOCKED
```

Stable labels:

```text
not-applicable
not-available
required
ready
blocked
```

The first implementation must not perform rollback.

## Authority summary struct

Add a C-compatible authority summary:

```text
latticra_status_t status;
char status_label[LATTICRA_NUCLEUS_TASK_LABEL_MAX];
char validator_label[LATTICRA_NUCLEUS_TASK_LABEL_MAX];
char requested_effect_label[LATTICRA_NUCLEUS_TASK_LABEL_MAX];
char denial_reason[LATTICRA_NUCLEUS_TASK_REASON_MAX];
int no_effect;
int execution_allowed;
int mutation_allowed;
int server_allowed;
int recovery_allowed;
int hardware_allowed;
```

This mirrors the renderer authority summary pattern and avoids exposing C++ object lifetimes through the C task API.

## Task request struct

Add request fields:

```text
char task_id[LATTICRA_NUCLEUS_TASK_ID_MAX];
latticra_nucleus_task_request_kind_t request_kind;
latticra_nucleus_task_effect_t requested_effect;
latticra_nucleus_task_operator_confirmation_t operator_confirmation;
latticra_nucleus_task_rollback_state_t rollback_state;
const latticra_nucleus_task_authority_summary_t *authority;
const latticra_nucleus_preview_t *preview;
const latticra_l_ui_render_result_t *render;
const latticra_lir_module_t *lir;
const latticra_lat_parse_result_t *lat;
const char *source_identity;
size_t source_identity_len;
latticra_l_ui_source_span_t source_span;
```

The implementation must not retain caller-owned pointers after the call returns.

## Task record struct

Add task record fields:

```text
char task_id[LATTICRA_NUCLEUS_TASK_ID_MAX];
latticra_nucleus_task_request_kind_t request_kind;
latticra_nucleus_task_effect_t requested_effect;
latticra_nucleus_task_effect_t allowed_effect;
latticra_nucleus_task_policy_t policy;
latticra_nucleus_task_denial_t denial;
latticra_nucleus_task_gate_state_t gate_state;
latticra_nucleus_task_operator_confirmation_t operator_confirmation;
latticra_nucleus_task_rollback_state_t rollback_state;
latticra_nucleus_task_authority_summary_t authority;
char source_identity[LATTICRA_NUCLEUS_TASK_SOURCE_IDENTITY_MAX];
latticra_l_ui_source_span_t source_span;
int executed;
int mutation_allowed;
int server_interaction_allowed;
int recovery_allowed;
int hardware_allowed;
unsigned int evidence_level;
```

## Task result struct

Add task result fields:

```text
latticra_status_t status;
latticra_nucleus_task_record_t record;
size_t record_count;
int no_effect;
int execution_allowed;
int mutation_allowed;
int server_allowed;
int recovery_allowed;
int hardware_allowed;
```

The result must be fully initialized on success and failure.

## Classification rules

Initial classification behavior:

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

Allowed classifications still must set:

```text
executed=0
mutation_allowed=0
server_interaction_allowed=0
recovery_allowed=0
hardware_allowed=0
```

## Prerequisite behavior

The first implementation must check relevant prerequisites.

Rules:

```text
missing request -> null-argument
missing result -> null-argument
missing authority -> authority-failed
non-ok authority -> authority-failed
non-no-effect authority flags -> non-no-effect-flags
operator confirmation present -> operator-confirmation-not-supported
render-report requires render_status=ok
lat-validate requires parser_error=ok
lir-validate requires lir_error=ok
transition-preview requires preview policy allow-preview
state-report requires preview policy allow-preview or allow-report
```

Failed prerequisites deny the task and must be visible in the report.

## Report format

`latticra_nucleus_task_report` should emit:

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

Reports must not include secrets, host environment values, filesystem contents, network data, credentials, or hardware identifiers.

## Output buffer behavior

`latticra_nucleus_task_report` should:

```text
write only to caller-provided buffers
require explicit buffer length
NUL-terminate on success
clear the buffer on too-small failure
return LATTICRA_STATUS_BUFFER_TOO_SMALL for small buffers
avoid heap allocation
avoid file output
avoid stdout
avoid stderr
avoid terminal escape control
```

## Exact implementation test list

The implementation PR should include tests for:

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

## Test file plan

Add:

```text
tests/nucleus_task_execution_invariants.c
scripts/test-nucleus-task-execution.sh
```

Wire into:

```text
.github/workflows/c.yml
```

Run after:

```text
sh scripts/test-nucleus-task-execution-implementation-plan.sh
```

and before:

```text
sh scripts/test-l-ui-static-report.sh
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
docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md
scripts/test-project-strategy-status-framework.sh
```

and add:

```text
docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md
```

## Compatibility expectations

The implementation must not change:

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

## Forbidden implementation behavior

The first implementation must not:

- bypass Nucleus preview classification;
- bypass effect gates;
- bypass constrained C++ authority validation;
- bypass parser, semantic, LIR, or render prerequisites when relevant;
- execute unknown requests;
- execute unknown effects;
- mutate state;
- write files;
- read host files outside approved metadata;
- open network connections;
- call server code;
- call update code;
- call recovery code;
- touch hardware;
- alter boot state;
- perform rollback;
- let operator confirmation override policy;
- hide denial reasons;
- omit task records;
- emit secrets, host environment values, credentials, or hardware identifiers;
- imply a production runtime, sandbox, malware prevention, ransomware prevention, recovery system, update system, or operating-system surface.

## Current validation command

This implementation plan is guarded by:

```sh
sh scripts/test-nucleus-task-execution-implementation-plan.sh
```

The guard is static. It does not implement Nucleus task execution.

## Implementation gate

Nucleus task execution code may be added only after this plan is merged.

## Non-claims

This document does not implement Nucleus task execution, command behavior, Lat execution, LIR execution, live movement, state mutation, file I/O, network I/O, server interaction, self-update, recovery behavior, rollback, hardware support, boot behavior, terminal control, security isolation, sandboxing, malware prevention, ransomware prevention, or operating-system completeness.
