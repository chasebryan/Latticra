# Latticra Runtime Boundary Contract

Status: Runtime boundary contract
Scope: first runtime boundary definition before runtime implementation, command behavior, Lat execution, LIR execution, task effect execution, file I/O, network I/O, server interaction, self-update, recovery behavior, rollback, hardware behavior, boot behavior, terminal control, sandboxing, malware prevention, ransomware prevention, or operating-system behavior.

## Purpose

This document defines the first runtime boundary contract for Latticra.

Runtime boundary means the line between validated metadata/report/classification surfaces and any future behavior that could execute, mutate, interact with a host, contact a network, affect recovery, affect hardware, affect boot state, or claim runtime authority.

This document does not implement a runtime.

## Relationship to previous work

This contract depends on:

```text
docs/EFFECT_GATES.md
docs/SUPERVISOR_ARCHITECTURE.md
docs/NUCLEUS_PREVIEW.md
docs/NUCLEUS_TASK_EXECUTION_CONTRACT.md
docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION_PLAN.md
docs/NUCLEUS_TASK_EXECUTION_IMPLEMENTATION.md
docs/CONSTRAINED_CPP_AUTHORITY_LAYER_IMPLEMENTATION.md
docs/L_UI_RENDERING_IMPLEMENTATION.md
docs/LIR_SHAPE_IMPLEMENTATION.md
docs/LAT_LANGUAGE_GRAMMAR_IMPLEMENTATION.md
docs/STATE_LATTICE.md
docs/TRI_PLANE_TRANSITION.md
include/latticra/nucleus_preview.h
include/latticra/nucleus_task.h
include/latticra/l_ui_renderer.h
include/latticra/lir.h
include/latticra/lat_parser.h
include/latticra/cpp/authority.hpp
src/nucleus_preview.c
src/nucleus_task.c
src/l_ui_renderer.c
src/lir.c
src/lat_parser.c
src/cpp/authority.cpp
```

Those files remain the source of truth for effect vocabulary, Nucleus preview behavior, task classification/reporting, constrained authority, rendering, LIR metadata, Lat metadata, state lattice, tri-plane transition, and current no-effect boundaries.

## Direction checkpoint

```text
C is the metal.
C++ is the disciplined structure.
Latticra is the contract.
```

Runtime work may not bypass this relationship:

```text
Lat / Latticra Language: declares contracts and intended effects
LIR: carries validated metadata
C++ authority layer: validates authority and reports decisions
C substrate: owns bounded runtime-adjacent records and ABI-compatible surfaces
Nucleus: coordinates only after contracts and gates permit it
Runtime: remains disabled until explicit boundaries, authority, tests, and evidence exist
```

## Current runtime boundary

Current Latticra behavior includes no production runtime.

Current implemented behavior is limited to:

```text
parsing
validation
classification
preview
reporting
rendering metadata
no-effect task classification
```

Current implemented behavior does not include:

```text
command execution
Lat execution
LIR execution
runtime scheduling
process launching
plugin loading
file I/O
network I/O
server interaction
self-update
recovery behavior
rollback
hardware access
boot behavior
terminal control
sandbox enforcement
malware prevention
ransomware prevention
operating-system behavior
```

## Runtime posture

The first runtime posture is disabled-by-default.

Initial runtime posture:

```text
runtime implemented? no
default policy: deny
report-only allowed: yes
validation-only allowed: yes
preview-only allowed: yes
classification-only allowed: yes
command execution allowed: no
Lat execution allowed: no
LIR execution allowed: no
mutation allowed: no
file I/O allowed: no
network I/O allowed: no
server interaction allowed: no
self-update allowed: no
recovery allowed: no
rollback allowed: no
hardware allowed: no
boot behavior allowed: no
operator confirmation allowed to override: no
```

Operator confirmation may be represented as metadata later, but it must not override runtime policy in the first implementation.

## Runtime boundary modes

Future runtime boundary work should use explicit modes.

Initial mode labels:

```text
disabled
report-only
validation-only
preview-only
classification-only
deny-all
requires-future-gate
```

The first runtime implementation plan must choose exact enum names.

No mode may imply command execution, Lat execution, LIR execution, mutation, file I/O, network I/O, recovery, hardware, boot behavior, or sandboxing.

## Runtime request kinds

Future runtime request kinds should include:

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

Only parse, validate, classify, render/report, and authority-check requests may be considered for first no-effect runtime handling.

All effect-performing requests remain denied.

## Runtime effects

Runtime boundary work must classify effects before handling.

Initial runtime effects:

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
none -> report/validation/classification only
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

## Runtime policy results

Future runtime policy labels:

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

The first future implementation must not produce an `executed` result for effect-performing work.

## Runtime denial reasons

Future denial labels:

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

Denial reasons must be stable and report-visible.

## Required prerequisites

A future runtime request may be considered only after relevant prerequisites are explicit.

Possible prerequisites:

```text
parser_error=ok
semantic_error=ok
lir_error=ok
render_status=ok
authority_status=ok
task_policy=allow-report or allow-validation or allow-classification or allow-preview
runtime_mode=report-only or validation-only or classification-only or preview-only
effect_gate=allowed-report or allowed-validation or allowed-classification or allowed-preview
no_effect=1
execution_allowed=0
mutation_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
operator_confirmation=not-applicable
```

If any prerequisite fails, the runtime boundary must deny the request and produce a deterministic report.

## Authority requirements

Future runtime boundary work must consult authority metadata before any request is eligible.

Authority checks must include:

```text
authority status
authority validator
authority requested effect
authority denial reason
authority no-effect flags
source identity
runtime request kind
runtime effect kind
runtime boundary mode
```

Authority failure must deny the request.

Authority success must not by itself execute a request. It only satisfies one prerequisite.

## Task requirements

Future runtime boundary work must use Nucleus task classification/reporting before runtime handling.

Task requirements must include:

```text
task policy
task denial reason
task requested effect
task allowed effect
task executed flag
task mutation_allowed flag
task server_interaction_allowed flag
task recovery_allowed flag
task hardware_allowed flag
```

If the task record indicates execution, mutation, server interaction, recovery, or hardware behavior, the first runtime boundary must reject it.

## Runtime record shape

A future runtime boundary record should include:

```text
runtime_id
request_kind
requested_effect
allowed_effect
runtime_mode
policy_result
denial_reason
authority_status
task_policy
task_reason
effect_gate_state
operator_confirmation
executed
mutation_allowed
file_io_allowed
network_allowed
server_interaction_allowed
recovery_allowed
rollback_allowed
hardware_allowed
boot_allowed
evidence_level
source_identity
source_span
```

The first future implementation should use fixed-size fields and caller-owned buffers.

## Runtime report format

A future runtime boundary report should be deterministic and bounded.

Suggested report header:

```text
LATTICRA RUNTIME BOUNDARY REPORT
runtime_id=<id>
request=<request-kind>
requested_effect=<effect>
allowed_effect=<effect>
mode=<runtime-mode>
policy=<policy-result>
reason=<denial-reason>
authority_status=<authority-status>
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

## Output buffer policy

Runtime boundary reports must:

```text
write only to caller-provided buffers
require explicit buffer length
NUL-terminate on success
clear the buffer on too-small failure
avoid heap allocation
avoid file output
avoid stdout
avoid stderr
avoid terminal escape control
```

## First implementation gate

Runtime boundary implementation must not begin until a separate implementation plan defines:

1. implementation language;
2. public header path;
3. source file path;
4. runtime request struct;
5. runtime record struct;
6. runtime result struct;
7. runtime mode enum;
8. runtime policy enum;
9. runtime denial enum;
10. authority summary usage;
11. Nucleus task result usage;
12. effect-gate state usage;
13. operator-confirmation metadata shape;
14. report format;
15. capacity constants;
16. output-buffer behavior;
17. exact tests;
18. compatibility expectations;
19. non-claims.

That plan should be recorded in:

```text
RUNTIME_BOUNDARY_IMPLEMENTATION_PLAN.md
```

## Future file policy

Recommended future files:

```text
include/latticra/runtime_boundary.h
src/runtime_boundary.c
tests/runtime_boundary_invariants.c
scripts/test-runtime-boundary.sh
docs/RUNTIME_BOUNDARY_IMPLEMENTATION_PLAN.md
docs/RUNTIME_BOUNDARY_IMPLEMENTATION.md
```

The implementation plan must confirm exact paths before runtime boundary code is added.

## Future test list

A future implementation plan should include tests for:

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

## Compatibility expectations

Future runtime boundary work must not change:

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

## Forbidden behavior

Runtime boundary work must not:

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

This contract is guarded by:

```sh
sh scripts/test-runtime-boundary-contract.sh
```

The guard is static. It does not implement runtime behavior.

## Non-claims

This document does not implement runtime behavior, command behavior, Lat execution, LIR execution, task effect execution, live movement, state mutation, file I/O, network I/O, server interaction, self-update, recovery behavior, rollback, hardware support, boot behavior, terminal control, security isolation, sandboxing, malware prevention, ransomware prevention, or operating-system completeness.
