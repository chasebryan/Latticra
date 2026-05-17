# Latticra Nucleus Task Execution Contract

Status: Nucleus task execution contract
Scope: future task execution boundary, prerequisites, authority checks, effect gates, denial behavior, task records, report surfaces, future files, tests, compatibility expectations, and non-claims before any task execution implementation.

## Purpose

This document defines the first contract for future Nucleus task execution in Latticra.

Nucleus task execution means a future capability to accept a classified task request, validate every prerequisite, check effect gates and authority, produce a deterministic task record, and only then decide whether the task remains denied, preview-only, or eligible for a later explicitly gated implementation.

This document does not implement Nucleus task execution.

## Relationship to previous work

This contract depends on:

```text
docs/NUCLEUS_PREVIEW.md
docs/EFFECT_GATES.md
docs/STATE_LATTICE.md
docs/TRI_PLANE_TRANSITION.md
docs/CONSTRAINED_CPP_AUTHORITY_LAYER_CONTRACT.md
docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION_PLAN.md
docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION.md
docs/L_UI_RENDERING_CONTRACT.md
docs/L_UI_RENDERING_IMPLEMENTATION_PLAN.md
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

Those files remain the source of truth for request classification, effect vocabulary, preview denial behavior, state-lattice vocabulary, transition preview behavior, constrained C++ authority validation, deterministic L-UI rendering, LIR metadata, Lat metadata, and current no-effect boundaries.

## Direction checkpoint

```text
C is the metal.
C++ is the disciplined structure.
Latticra is the contract.
```

Task execution may not bypass this relationship:

```text
Lat / Latticra Language: declares contract and intended effects
LIR: carries validated metadata
C++ authority layer: validates authority and reports decisions
C substrate: owns bounded execution-adjacent records and ABI-compatible surfaces
Nucleus: coordinates only after contracts and gates permit it
```

## Current Nucleus boundary

Current Nucleus behavior is preview classification only.

Current Nucleus preview allows only:

```text
state-report with effect=none
state-report with effect=read
transition-preview with effect=none
transition-preview with effect=read
```

Current Nucleus preview denies:

```text
server-interaction
self-update
recovery-action
hardware-action
unknown request
local_mutation
host_mutation
network
hardware
boot
recovery
external
```

The future task execution contract must preserve this preview-only boundary until a separate implementation plan and implementation explicitly prove otherwise.

## First task execution posture

The first future implementation must be denied-by-default.

Initial task execution posture:

```text
task execution implemented? no
default policy: deny
preview allowed: yes
mutation allowed: no
network allowed: no
hardware allowed: no
boot allowed: no
recovery allowed: no
server interaction allowed: no
self-update allowed: no
operator confirmation allowed to override: no
```

Operator confirmation may be represented as metadata later, but it must not override policy in the first implementation.

## Task request kinds

Future task execution should reuse and extend the existing request vocabulary carefully.

Initial task request kinds:

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

Only report/validation/preview-style requests may be eligible for no-effect handling in the first future implementation.

All effect-performing requests remain denied.

## Task effects

Task execution must classify effects before task handling.

Initial task effects:

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

Default policy:

```text
none -> preview/report/validation only
read -> approved local metadata only
local_mutation -> deny until explicit local-mutation contract
host_mutation -> deny
network -> deny
hardware -> deny
boot -> deny
recovery -> deny
external -> deny
unknown -> deny
```

## Task policy results

Future policy result labels:

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

The first future implementation should not produce an `executed` task result for effect-performing work.

## Task denial reasons

Future denial reason labels:

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
authority-failed
effect-blocked
effect-requires-future-gate
non-no-effect-flags
operator-confirmation-not-supported
implementation-not-present
internal-error
```

Denial reasons must be stable and report-visible.

## Required prerequisites

A future task may be considered only after all relevant prerequisites are explicit.

Possible prerequisites:

```text
parser_error=ok
semantic_error=ok
lir_error=ok
authority_status=ok
render_status=ok
preview_policy=allow-preview or allow-report or allow-validation
effect_gate=allowed-preview or allowed-report or allowed-validation
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
operator_confirmation=not-applicable
```

If any prerequisite fails, the task must be denied and reported.

## Required authority checks

Future Nucleus task execution must consult authority metadata before any task is eligible.

Authority checks must include:

```text
authority status
authority validator
authority requested effect
authority denial reason
authority no-effect flags
source identity
request kind
effect kind
boundary kind
```

Authority failure must deny the task.

Authority success must not by itself execute a task. It only satisfies one prerequisite.

## Required effect-gate checks

Future task execution must consult the effect gate before task handling.

Effect gate checks must classify:

```text
requested effect
allowed effect
gate state
policy result
reason
rollback state
```

Initial allowed gate states for first implementation:

```text
disabled
blocked
planned
```

The first future implementation must not produce:

```text
armed
executed
failed
```

except as literal denied metadata in tests or reports.

## Task record shape

A future task record should include:

```text
task_id
request_kind
requested_effect
allowed_effect
policy_result
policy_reason
authority_status
authority_validator
authority_reason
gate_state
operator_confirmation
executed
mutation_allowed
server_interaction_allowed
recovery_allowed
hardware_allowed
rollback_state
evidence_level
source_identity
source_span
```

The first future implementation should use fixed-size fields and caller-owned buffers.

## Task report format

A future task report should be deterministic and bounded.

Suggested report header:

```text
LATTICRA NUCLEUS TASK REPORT
task_id=<id>
request=<request-kind>
requested_effect=<effect>
allowed_effect=<effect>
policy=<policy-result>
reason=<policy-reason>
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

## First implementation gate

Nucleus task execution implementation must not begin until a separate implementation plan defines:

1. implementation language;
2. public header path;
3. source file path;
4. task request struct;
5. task result struct;
6. task record struct;
7. task policy enum;
8. task denial enum;
9. effect-gate enum usage;
10. authority summary usage;
11. operator-confirmation metadata shape;
12. rollback metadata shape;
13. report format;
14. capacity constants;
15. output-buffer behavior;
16. exact tests;
17. compatibility expectations;
18. non-claims.

That plan should be recorded in:

```text
NUCLEUS_TASK_EXECUTION_IMPLEMENTATION_PLAN.md
```

## Future file policy

Recommended future files:

```text
include/latticra/nucleus_task.h
src/nucleus_task.c
tests/nucleus_task_execution_invariants.c
scripts/test-nucleus-task-execution.sh
docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION_PLAN.md
docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md
```

The implementation plan must confirm exact paths before task execution code is added.

## Future test list

A future implementation plan should include tests for:

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

Future Nucleus task execution work must not change:

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

## Forbidden behavior

Nucleus task execution work must not:

- bypass Nucleus preview classification;
- bypass effect gates;
- bypass constrained C++ authority validation;
- bypass parser, semantic, LIR, or render prerequisites when relevant;
- execute unknown requests;
- execute unknown effects;
- mutate state without a separate mutation contract;
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

This contract is guarded by:

```sh
sh scripts/test-nucleus-task-execution-contract.sh
```

The guard is static. It does not implement Nucleus task execution.

## Non-claims

This document does not implement Nucleus task execution, command behavior, Lat execution, LIR execution, live movement, state mutation, file I/O, network I/O, server interaction, self-update, recovery behavior, rollback, hardware support, boot behavior, terminal control, security isolation, sandboxing, malware prevention, ransomware prevention, or operating-system completeness.
