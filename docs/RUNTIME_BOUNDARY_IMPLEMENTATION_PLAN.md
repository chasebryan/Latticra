# Latticra Runtime Boundary Implementation Plan

Status: implementation planning contract
Scope: exact public API, C implementation files, runtime request/record/result structs, runtime mode enum, runtime policy enum, runtime denial enum, effect enum, authority summary usage, Nucleus task result usage, effect-gate state usage, operator-confirmation metadata, report format, capacity constants, output-buffer behavior, tests, compatibility expectations, and non-claims before runtime boundary code.

## Purpose

This document defines the implementation plan for the first runtime boundary surface.

The Runtime boundary contract is already merged and guarded. This plan turns that contract into exact public API, file paths, data structures, enums, capacity constants, report rules, prerequisite behavior, task-result behavior, authority behavior, exact tests, compatibility expectations, and non-claims before runtime boundary code is added.

This document does not implement runtime behavior.

## Relationship to previous work

This plan depends on:

```text
docs/RUNTIME_BOUNDARY_CONTRACT.md
docs/EFFECT_GATES.md
docs/SUPERVISOR_ARCHITECTURE.md
docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md
docs/NUCLEUS_PREVIEW.md
docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION.md
docs/L_UI_RENDERING_IMPLEMENTATION.md
docs/LIR_SHAPE_IMPLEMENTATION.md
docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md
include/latticra/nucleus_task.h
include/latticra/nucleus_preview.h
include/latticra/l_ui_renderer.h
include/latticra/lir.h
include/latticra/lat_parser.h
include/latticra/cpp/authority.hpp
src/nucleus_task.c
src/nucleus_preview.c
src/l_ui_renderer.c
src/lir.c
src/lat_parser.c
src/cpp/authority.cpp
```

Those files remain the source of truth for task classification, preview classification, constrained authority, rendering, LIR metadata, Lat metadata, and no-effect boundaries.

## Implementation language decision

The first runtime boundary surface should be implemented in C.

Reason:

- Nucleus preview is C;
- Nucleus task classification/reporting is C;
- L-UI rendering, LIR shape, and Lat grammar are C;
- the boundary should use bounded structs and caller-provided buffers;
- C remains the secure substrate;
- the constrained C++ authority layer remains a validation/report dependency, not the runtime boundary storage substrate.

The first implementation must not expose C++ object lifetimes through the public C runtime boundary API.

## Implementation files

The implementation PR should add or modify:

```text
include/latticra/runtime_boundary.h
src/runtime_boundary.c
tests/runtime_boundary_invariants.c
scripts/test-runtime-boundary.sh
.github/workflows/c.yml
docs/RUNTIME_BOUNDARY_IMPLEMENTATION.md
```

The implementation PR should not add command behavior, Lat execution, LIR execution, task effect execution, live movement, mutation, file I/O, network I/O, server interaction, self-update, recovery behavior, rollback, hardware behavior, boot behavior, terminal control, sandboxing, malware prevention, ransomware prevention, or operating-system behavior.

## Public API shape

Add public API names:

```text
latticra_runtime_boundary_request_kind_t
latticra_runtime_boundary_effect_t
latticra_runtime_boundary_mode_t
latticra_runtime_boundary_policy_t
latticra_runtime_boundary_denial_t
latticra_runtime_boundary_gate_state_t
latticra_runtime_boundary_operator_confirmation_t
latticra_runtime_boundary_authority_summary_t
latticra_runtime_boundary_request_t
latticra_runtime_boundary_record_t
latticra_runtime_boundary_result_t
latticra_runtime_boundary_request_kind_label
latticra_runtime_boundary_effect_label
latticra_runtime_boundary_mode_label
latticra_runtime_boundary_policy_label
latticra_runtime_boundary_denial_label
latticra_runtime_boundary_gate_state_label
latticra_runtime_boundary_operator_confirmation_label
latticra_runtime_boundary_classify
latticra_runtime_boundary_report
```

Recommended function signatures:

```text
const char *latticra_runtime_boundary_request_kind_label(latticra_runtime_boundary_request_kind_t kind);
const char *latticra_runtime_boundary_effect_label(latticra_runtime_boundary_effect_t effect);
const char *latticra_runtime_boundary_mode_label(latticra_runtime_boundary_mode_t mode);
const char *latticra_runtime_boundary_policy_label(latticra_runtime_boundary_policy_t policy);
const char *latticra_runtime_boundary_denial_label(latticra_runtime_boundary_denial_t denial);
const char *latticra_runtime_boundary_gate_state_label(latticra_runtime_boundary_gate_state_t gate_state);
const char *latticra_runtime_boundary_operator_confirmation_label(latticra_runtime_boundary_operator_confirmation_t confirmation);

latticra_status_t latticra_runtime_boundary_classify(
    const latticra_runtime_boundary_request_t *request,
    latticra_runtime_boundary_result_t *result);

latticra_status_t latticra_runtime_boundary_report(
    const latticra_runtime_boundary_result_t *result,
    char *buffer,
    size_t buffer_len);
```

The first implementation should classify and report only. It must not execute runtime behavior.

## Capacity constants

Add exact bounded constants:

```text
LATTICRA_RUNTIME_BOUNDARY_ID_MAX 64u
LATTICRA_RUNTIME_BOUNDARY_LABEL_MAX 64u
LATTICRA_RUNTIME_BOUNDARY_REASON_MAX 128u
LATTICRA_RUNTIME_BOUNDARY_SOURCE_IDENTITY_MAX 128u
LATTICRA_RUNTIME_BOUNDARY_REPORT_MAX 4096u
LATTICRA_RUNTIME_BOUNDARY_RECORD_MAX 16u
```

Small output buffers must return `LATTICRA_STATUS_BUFFER_TOO_SMALL` and clear the output buffer.

## Request kind enum

Add request kinds:

```text
LATTICRA_RUNTIME_BOUNDARY_PARSE_ONLY
LATTICRA_RUNTIME_BOUNDARY_VALIDATE_ONLY
LATTICRA_RUNTIME_BOUNDARY_CLASSIFY_ONLY
LATTICRA_RUNTIME_BOUNDARY_RENDER_REPORT
LATTICRA_RUNTIME_BOUNDARY_NUCLEUS_TASK_REPORT
LATTICRA_RUNTIME_BOUNDARY_LAT_VALIDATE
LATTICRA_RUNTIME_BOUNDARY_LIR_VALIDATE
LATTICRA_RUNTIME_BOUNDARY_AUTHORITY_CHECK
LATTICRA_RUNTIME_BOUNDARY_RUNTIME_EXECUTE
LATTICRA_RUNTIME_BOUNDARY_COMMAND_EXECUTE
LATTICRA_RUNTIME_BOUNDARY_LAT_EXECUTE
LATTICRA_RUNTIME_BOUNDARY_LIR_EXECUTE
LATTICRA_RUNTIME_BOUNDARY_FILE_READ
LATTICRA_RUNTIME_BOUNDARY_FILE_WRITE
LATTICRA_RUNTIME_BOUNDARY_NETWORK_OPEN
LATTICRA_RUNTIME_BOUNDARY_SERVER_INTERACTION
LATTICRA_RUNTIME_BOUNDARY_SELF_UPDATE
LATTICRA_RUNTIME_BOUNDARY_RECOVERY_ACTION
LATTICRA_RUNTIME_BOUNDARY_ROLLBACK_ACTION
LATTICRA_RUNTIME_BOUNDARY_HARDWARE_ACTION
LATTICRA_RUNTIME_BOUNDARY_BOOT_ACTION
LATTICRA_RUNTIME_BOUNDARY_UNKNOWN
```

Stable labels:

```text
parse-only
validate-only
classify-only
render-report
nucleus-task-report
lat-validate
lir-validate
authority-check
runtime-execute
command-execute
lat-execute
lir-execute
file-read
file-write
network-open
server-interaction
self-update
recovery-action
rollback-action
hardware-action
boot-action
unknown
```

## Effect enum

Add runtime effects:

```text
LATTICRA_RUNTIME_BOUNDARY_EFFECT_NONE
LATTICRA_RUNTIME_BOUNDARY_EFFECT_READ
LATTICRA_RUNTIME_BOUNDARY_EFFECT_LOCAL_MUTATION
LATTICRA_RUNTIME_BOUNDARY_EFFECT_HOST_MUTATION
LATTICRA_RUNTIME_BOUNDARY_EFFECT_NETWORK
LATTICRA_RUNTIME_BOUNDARY_EFFECT_HARDWARE
LATTICRA_RUNTIME_BOUNDARY_EFFECT_BOOT
LATTICRA_RUNTIME_BOUNDARY_EFFECT_RECOVERY
LATTICRA_RUNTIME_BOUNDARY_EFFECT_EXTERNAL
LATTICRA_RUNTIME_BOUNDARY_EFFECT_UNKNOWN
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

Only `none` and `read` may be eligible for no-effect report, validation, classification, or preview boundary handling.

## Runtime mode enum

Add runtime modes:

```text
LATTICRA_RUNTIME_BOUNDARY_MODE_DISABLED
LATTICRA_RUNTIME_BOUNDARY_MODE_REPORT_ONLY
LATTICRA_RUNTIME_BOUNDARY_MODE_VALIDATION_ONLY
LATTICRA_RUNTIME_BOUNDARY_MODE_PREVIEW_ONLY
LATTICRA_RUNTIME_BOUNDARY_MODE_CLASSIFICATION_ONLY
LATTICRA_RUNTIME_BOUNDARY_MODE_DENY_ALL
LATTICRA_RUNTIME_BOUNDARY_MODE_REQUIRES_FUTURE_GATE
```

Stable labels:

```text
disabled
report-only
validation-only
preview-only
classification-only
deny-all
requires-future-gate
```

No mode may imply execution, mutation, file I/O, network I/O, recovery, hardware, boot behavior, or sandboxing.

## Policy enum

Add runtime policies:

```text
LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_REPORT
LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_VALIDATION
LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_CLASSIFICATION
LATTICRA_RUNTIME_BOUNDARY_POLICY_ALLOW_PREVIEW
LATTICRA_RUNTIME_BOUNDARY_POLICY_DENY
LATTICRA_RUNTIME_BOUNDARY_POLICY_BLOCKED
LATTICRA_RUNTIME_BOUNDARY_POLICY_REQUIRES_FUTURE_GATE
LATTICRA_RUNTIME_BOUNDARY_POLICY_UNSUPPORTED
LATTICRA_RUNTIME_BOUNDARY_POLICY_INTERNAL_ERROR
```

Stable labels:

```text
allow-report
allow-validation
allow-classification
allow-preview
deny
blocked
requires-future-gate
unsupported
internal-error
```

The first implementation must not produce an executed effect-performing result.

## Denial enum

Add denial reasons:

```text
LATTICRA_RUNTIME_BOUNDARY_DENIAL_OK
LATTICRA_RUNTIME_BOUNDARY_DENIAL_NULL_ARGUMENT
LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNKNOWN_REQUEST
LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNKNOWN_EFFECT
LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNSUPPORTED_REQUEST
LATTICRA_RUNTIME_BOUNDARY_DENIAL_UNSUPPORTED_EFFECT
LATTICRA_RUNTIME_BOUNDARY_DENIAL_PARSER_FAILED
LATTICRA_RUNTIME_BOUNDARY_DENIAL_SEMANTIC_FAILED
LATTICRA_RUNTIME_BOUNDARY_DENIAL_LIR_FAILED
LATTICRA_RUNTIME_BOUNDARY_DENIAL_RENDER_FAILED
LATTICRA_RUNTIME_BOUNDARY_DENIAL_AUTHORITY_FAILED
LATTICRA_RUNTIME_BOUNDARY_DENIAL_TASK_FAILED
LATTICRA_RUNTIME_BOUNDARY_DENIAL_RUNTIME_DISABLED
LATTICRA_RUNTIME_BOUNDARY_DENIAL_EFFECT_BLOCKED
LATTICRA_RUNTIME_BOUNDARY_DENIAL_EFFECT_REQUIRES_FUTURE_GATE
LATTICRA_RUNTIME_BOUNDARY_DENIAL_NON_NO_EFFECT_FLAGS
LATTICRA_RUNTIME_BOUNDARY_DENIAL_OPERATOR_CONFIRMATION_NOT_SUPPORTED
LATTICRA_RUNTIME_BOUNDARY_DENIAL_IMPLEMENTATION_NOT_PRESENT
LATTICRA_RUNTIME_BOUNDARY_DENIAL_INTERNAL_ERROR
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
task-failed
runtime-disabled
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
LATTICRA_RUNTIME_BOUNDARY_GATE_DISABLED
LATTICRA_RUNTIME_BOUNDARY_GATE_BLOCKED
LATTICRA_RUNTIME_BOUNDARY_GATE_PLANNED
LATTICRA_RUNTIME_BOUNDARY_GATE_AVAILABLE
LATTICRA_RUNTIME_BOUNDARY_GATE_ARMED
LATTICRA_RUNTIME_BOUNDARY_GATE_EXECUTED
LATTICRA_RUNTIME_BOUNDARY_GATE_FAILED
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
LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_APPLICABLE
LATTICRA_RUNTIME_BOUNDARY_OPERATOR_REQUIRED
LATTICRA_RUNTIME_BOUNDARY_OPERATOR_PRESENT
LATTICRA_RUNTIME_BOUNDARY_OPERATOR_REJECTED
LATTICRA_RUNTIME_BOUNDARY_OPERATOR_NOT_SUPPORTED
```

Stable labels:

```text
not-applicable
required
present
rejected
not-supported
```

Confirmation is metadata only. It must not override policy.

## Authority summary struct

Add a C-compatible authority summary:

```text
latticra_status_t status;
char status_label[LATTICRA_RUNTIME_BOUNDARY_LABEL_MAX];
char validator_label[LATTICRA_RUNTIME_BOUNDARY_LABEL_MAX];
char requested_effect_label[LATTICRA_RUNTIME_BOUNDARY_LABEL_MAX];
char denial_reason[LATTICRA_RUNTIME_BOUNDARY_REASON_MAX];
int no_effect;
int execution_allowed;
int mutation_allowed;
int server_allowed;
int recovery_allowed;
int hardware_allowed;
```

This mirrors existing authority summary patterns and avoids exposing C++ object lifetimes through the C runtime boundary API.

## Runtime request struct

Add request fields:

```text
char runtime_id[LATTICRA_RUNTIME_BOUNDARY_ID_MAX];
latticra_runtime_boundary_request_kind_t request_kind;
latticra_runtime_boundary_effect_t requested_effect;
latticra_runtime_boundary_mode_t mode;
latticra_runtime_boundary_operator_confirmation_t operator_confirmation;
const latticra_runtime_boundary_authority_summary_t *authority;
const latticra_nucleus_task_result_t *task;
const latticra_l_ui_render_result_t *render;
const latticra_lir_module_t *lir;
const latticra_lat_parse_result_t *lat;
const char *source_identity;
size_t source_identity_len;
latticra_l_ui_source_span_t source_span;
```

The implementation must not retain caller-owned pointers after the call returns.

## Runtime record struct

Add record fields:

```text
char runtime_id[LATTICRA_RUNTIME_BOUNDARY_ID_MAX];
latticra_runtime_boundary_request_kind_t request_kind;
latticra_runtime_boundary_effect_t requested_effect;
latticra_runtime_boundary_effect_t allowed_effect;
latticra_runtime_boundary_mode_t mode;
latticra_runtime_boundary_policy_t policy;
latticra_runtime_boundary_denial_t denial;
latticra_runtime_boundary_gate_state_t gate_state;
latticra_runtime_boundary_operator_confirmation_t operator_confirmation;
latticra_runtime_boundary_authority_summary_t authority;
latticra_nucleus_task_policy_t task_policy;
latticra_nucleus_task_denial_t task_reason;
char source_identity[LATTICRA_RUNTIME_BOUNDARY_SOURCE_IDENTITY_MAX];
latticra_l_ui_source_span_t source_span;
int executed;
int mutation_allowed;
int file_io_allowed;
int network_allowed;
int server_interaction_allowed;
int recovery_allowed;
int rollback_allowed;
int hardware_allowed;
int boot_allowed;
unsigned int evidence_level;
```

## Runtime result struct

Add result fields:

```text
latticra_status_t status;
latticra_runtime_boundary_record_t record;
size_t record_count;
int no_effect;
int execution_allowed;
int mutation_allowed;
int file_io_allowed;
int network_allowed;
int server_allowed;
int recovery_allowed;
int rollback_allowed;
int hardware_allowed;
int boot_allowed;
```

The result must be fully initialized on success and failure.

## Classification rules

Initial classification behavior:

```text
parse-only + none -> allow-report
parse-only + read -> allow-report
validate-only + none -> allow-validation
validate-only + read -> allow-validation
classify-only + none -> allow-classification
classify-only + read -> allow-classification
render-report + none -> allow-report
render-report + read -> allow-report
nucleus-task-report + none -> allow-report
nucleus-task-report + read -> allow-report
lat-validate + none -> allow-validation
lat-validate + read -> allow-validation
lir-validate + none -> allow-validation
lir-validate + read -> allow-validation
authority-check + none -> allow-validation
authority-check + read -> allow-validation
runtime-execute -> requires-future-gate
command-execute -> requires-future-gate
lat-execute -> requires-future-gate
lir-execute -> requires-future-gate
file-read -> requires-future-gate
file-write -> requires-future-gate
network-open -> requires-future-gate
server-interaction -> requires-future-gate
self-update -> requires-future-gate
recovery-action -> requires-future-gate
rollback-action -> requires-future-gate
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
file_io_allowed=0
network_allowed=0
server_interaction_allowed=0
recovery_allowed=0
rollback_allowed=0
hardware_allowed=0
boot_allowed=0
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
runtime mode disabled -> runtime-disabled unless request is report-only metadata
render-report requires render_status=ok
nucleus-task-report requires task policy allow-report or allow-validation or allow-classification or allow-preview
lat-validate requires parser_error=ok
lir-validate requires lir_error=ok
runtime-execute requires future gate
command-execute requires future gate
lat-execute requires future gate
lir-execute requires future gate
file-read requires future gate
file-write requires future gate
network-open requires future gate
server-interaction requires future gate
self-update requires future gate
recovery-action requires future gate
rollback-action requires future gate
hardware-action requires future gate
boot-action requires future gate
```

Failed prerequisites deny the request and must be visible in the report.

## Report format

`latticra_runtime_boundary_report` should emit:

```text
LATTICRA RUNTIME BOUNDARY REPORT
status=<integer-status>
runtime_id=<id>
request=<request-kind>
requested_effect=<effect>
allowed_effect=<effect>
mode=<runtime-mode>
policy=<policy-result>
reason=<denial-reason>
authority_status=<authority-status>
authority_validator=<authority-validator>
authority_reason=<authority-reason>
task_policy=<task-policy>
task_reason=<task-reason>
effect_gate_state=<gate-state>
operator_confirmation=<confirmation-state>
executed=0
mutation_allowed=0
file_io_allowed=0
network_allowed=0
server_interaction_allowed=0
recovery_allowed=0
rollback_allowed=0
hardware_allowed=0
boot_allowed=0
evidence_level=<level>
source_identity=<source>
span_start_offset=<offset>
span_end_offset=<offset>
```

Reports must not include secrets, host environment values, filesystem contents, network data, credentials, tokens, keys, hardware identifiers, or process information.

## Output buffer behavior

`latticra_runtime_boundary_report` should:

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
runtime_boundary_denies_unknown_request
runtime_boundary_denies_unknown_effect
runtime_boundary_denies_runtime_execute
runtime_boundary_denies_command_execute
runtime_boundary_denies_lat_execute
runtime_boundary_denies_lir_execute
runtime_boundary_denies_file_read
runtime_boundary_denies_file_write
runtime_boundary_denies_network_open
runtime_boundary_denies_server_interaction
runtime_boundary_denies_self_update
runtime_boundary_denies_recovery_action
runtime_boundary_denies_rollback_action
runtime_boundary_denies_hardware_action
runtime_boundary_denies_boot_action
runtime_boundary_requires_authority_success
runtime_boundary_requires_task_success
runtime_boundary_requires_no_effect_flags
runtime_boundary_allows_parse_only_report_only
runtime_boundary_allows_validate_only
runtime_boundary_allows_classify_only
runtime_boundary_allows_render_report_only
runtime_boundary_report_is_deterministic
runtime_boundary_report_rejects_small_buffer
runtime_boundary_does_not_mutate_state
runtime_boundary_does_not_write_files
runtime_boundary_does_not_open_network
runtime_boundary_does_not_touch_hardware
runtime_boundary_does_not_call_recovery
runtime_boundary_does_not_override_policy_with_operator_confirmation
```

## Test file plan

Add:

```text
tests/runtime_boundary_invariants.c
scripts/test-runtime-boundary.sh
```

Wire into:

```text
.github/workflows/c.yml
```

Run after:

```text
sh scripts/test-runtime-boundary-implementation-plan.sh
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
docs/RUNTIME_BOUNDARY_CONTRACT.md
scripts/test-project-strategy-status-framework.sh
```

and add:

```text
docs/RUNTIME_BOUNDARY_IMPLEMENTATION.md
```

## Compatibility expectations

The implementation must not change:

```text
existing Nucleus preview classification behavior
existing Nucleus task classification behavior
existing Nucleus task report behavior
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

- bypass Nucleus task classification;
- bypass effect gates;
- bypass constrained C++ authority validation;
- bypass parser, semantic, LIR, render, or task prerequisites when relevant;
- execute unknown requests;
- execute unknown effects;
- execute commands;
- execute Lat;
- execute LIR;
- launch processes;
- load plugins;
- mutate state;
- write files;
- read host files outside approved metadata;
- open network connections;
- call server code;
- call update code;
- call recovery code;
- perform rollback;
- touch hardware;
- alter boot state;
- use terminal control;
- let operator confirmation override policy;
- hide denial reasons;
- omit runtime records;
- emit secrets, host environment values, credentials, tokens, keys, hardware identifiers, or process information;
- imply a production runtime, sandbox, malware prevention, ransomware prevention, recovery system, update system, or operating-system surface.

## Current validation command

This implementation plan is guarded by:

```sh
sh scripts/test-runtime-boundary-implementation-plan.sh
```

The guard is static. It does not implement runtime boundary behavior.

## Implementation gate

Runtime boundary code may be added only after this plan is merged.

## Non-claims

This document does not implement runtime behavior, command behavior, Lat execution, LIR execution, task effect execution, live movement, state mutation, file I/O, network I/O, server interaction, self-update, recovery behavior, rollback, hardware support, boot behavior, terminal control, security isolation, sandboxing, malware prevention, ransomware prevention, or operating-system completeness.
