# Latticra Runtime Boundary Report Refinement

Status: initial runtime boundary report refinement implementation
Scope: deterministic no-effect runtime-boundary report classification, boundary-domain labeling, authorization-state labeling, evidence-level reporting, invariant tests, and guard coverage.

## Purpose

This document records the runtime-boundary report refinement that follows the Lat pipeline and Lat-specific LIR evidence reporting slice.

The refinement makes runtime boundary reports more explicit about what a request represents before any operational runtime authority exists.

Runtime boundary reporting remains a classifier and evidence surface. It is not a kernel interface, sandbox, permission system, process supervisor, boot layer, device layer, filesystem layer, network layer, or authority grant.

## Boundary principle

Latticra runtime authority is denied by default.

A runtime-boundary request may be reported as declarative, boundary-seeking, denied, or invalid. No report classification executes the request, mutates state, performs I/O, opens a network connection, touches hardware, controls a terminal, starts a process, boots a system, or grants runtime authority.

## Added report fields

The runtime boundary record now includes explicit report-refinement fields:

```text
report_classification
boundary_domain
authorization_state
evidence_level
```

The deterministic text report now emits:

```text
report_classification=<label>
boundary_domain=<label>
authorization_state=<label>
evidence_level=<number>
```

## Report classifications

Initial report classifications:

```text
declarative
boundary-seeking
denied
invalid
```

### declarative

The request is a no-effect report, validation, classification, or metadata surface that can be accepted under the current disabled-by-default runtime boundary.

### boundary-seeking

The request attempts to cross toward operational runtime authority or a future-gated operational domain.

Boundary-seeking does not mean the request is executed. It means the report identified the request as runtime-authority-seeking and kept it behind the future gate.

### denied

The request is understood but not accepted under the current prerequisites, authority summary, effect posture, operator-confirmation state, or no-effect requirements.

### invalid

The request cannot be classified as a valid boundary request because it is null, unknown, malformed, or carries unknown effect identity.

## Boundary domains

Initial report domains:

```text
memory
filesystem
network
process
device
clock
randomness
host
external-call
persistence
scheduler
unknown
```

Operational request kinds map to the clearest current domain:

```text
file-read / file-write -> filesystem
network-open / server-interaction -> network
runtime-execute / command-execute / lat-execute / lir-execute -> process
hardware-action / boot-action -> device
self-update / recovery-action / rollback-action -> persistence
nucleus-task-report -> scheduler
authority-check -> host
```

No-effect declarative requests that do not cross a specific operational surface remain `unknown` unless their requested effect provides a clearer domain.

## Authorization states

Initial authorization states:

```text
not-requested
requested
denied
unavailable
reserved-for-future
```

The current implementation uses:

```text
not-requested -> accepted no-effect report / validation / classification surfaces
denied -> known request rejected by current prerequisites or policy
unavailable -> null or unknown request/effect identity
reserved-for-future -> future-gated operational runtime request
```

`requested` is reserved as an explicit report-state label for future slices that need to distinguish request capture from denial or future reservation.

## Evidence level

The runtime boundary now records a small deterministic evidence level:

```text
0 -> invalid or unavailable boundary evidence
1 -> denied or future-gated boundary evidence
2 -> accepted no-effect declarative report / validation / classification evidence
```

This is an internal project evidence label, not a maturity certification, security level, or production-readiness score.

## Happy path

The current report-refinement happy path is:

```text
source -> parse / validate / lower -> classify -> report classification -> report domain -> report authorization state -> emit deterministic evidence
```

No unauthorized effect is executed during this path.

## Implementation files

This slice updates or adds:

```text
include/latticra/runtime_boundary.h
src/runtime_boundary.c
tests/runtime_boundary_report_refinement.c
docs/RUNTIME_BOUNDARY_REPORT_REFINEMENT.md
scripts/test-runtime-boundary-report-refinement.sh
.github/workflows/runtime-boundary-report-refinement.yml
```

The full C workflow also runs the new guard.

## Validation

Run:

```sh
sh scripts/test-runtime-boundary-report-refinement.sh
sh scripts/test-runtime-boundary.sh
```

The focused invariant tests verify:

```text
runtime_boundary_report_refinement_classifies_declarative_pipeline
runtime_boundary_report_refinement_marks_future_gate_boundary_seeking
runtime_boundary_report_refinement_maps_effect_domains
runtime_boundary_report_refinement_marks_invalid_unknown_request
runtime_boundary_report_refinement_marks_denied_prerequisite
```

The guard verifies that documentation, header declarations, implementation labels, report fields, focused tests, and workflow wiring remain present.

## Compatibility

This refinement preserves the existing runtime boundary behavior for:

```text
parse-only
validate-only
classify-only
render-report
nucleus-task-report
lat-validate
lir-validate
authority-check
lat-pipeline-validate
future-gated operational request kinds
unknown request denial
unknown effect denial
operator-confirmation non-override behavior
small-buffer behavior
Lat pipeline evidence fields
Lat-specific LIR evidence fields
```

## Non-claims

This report refinement does not provide:

```text
runtime behavior
command execution
Lat execution
LIR execution
task effect execution
live movement
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
