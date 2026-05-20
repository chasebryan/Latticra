# Kernel Lifecycle Rollback Plan

Status: planning and guardrail record
Scope: rollback semantics for the bounded kernel lifecycle sequence.

## Purpose

The kernel lifecycle can currently move a local in-memory state machine from `created` to `memory-map-ready` when an explicit gate allows the sequence.

This plan defines how Latticra should reason about failed, partial, or interrupted lifecycle progress before any rollback implementation exists.

The goal is to make failure handling auditable before adding more kernel surfaces.

## Rollback meaning

Rollback means:

```text
record the last safe lifecycle state
classify the incomplete transition
report the reason rollback would be required
preserve the no-external-effect boundary
```

Rollback does not yet mean:

```text
restore persisted state
write recovery metadata
restart a runtime
undo hardware work
operate devices
spawn or stop processes
```

## Current lifecycle ladder

```text
created
initialized
registry-ready
scheduler-ready
memory-map-ready
```

The current approved forward path remains:

```text
created -> initialized
initialized -> registry-ready
registry-ready -> scheduler-ready
scheduler-ready -> memory-map-ready
```

## Rollback trigger classes

Planned rollback classification should cover:

```text
null-request
invalid-target
target-before-current
step-limit-reached
no-forward-step
step-request-failed
step-failed
step-did-not-advance
external-effect-blocked
```

## Planned report fields

A later implementation may emit fields such as:

```text
rollback_plan_status=planned
rollback_required=1
rollback_performed=0
rollback_reason=step-limit-reached
last_safe_state=registry-ready
attempted_target=memory-map-ready
final_state=registry-ready
state_mutated_before_stop=1
external_effect_performed=0
persistence_allowed=0
recovery_authority_allowed=0
```

## Safety rule

Rollback planning must remain report-only until a separate authority contract exists.

The first implementation should only classify and report rollback posture. It should not persist state, start execution, use host recovery actions, or claim operating-system readiness.

## Guardrail checklist

Any future rollback implementation must preserve:

```text
external_effect_performed=0
persistence_allowed=0
recovery_authority_allowed=0
runtime_entry_allowed=0
```

It must also keep rollback reports deterministic and testable through a focused guard.

## Implementation sequence

Recommended order:

```text
1. Add rollback classification structs.
2. Add a no-effect rollback evaluator.
3. Add tests for complete, limited, invalid, and denied lifecycle paths.
4. Add a report runner.
5. Add status/docs alignment only after the implementation guard passes.
```

## Validation

This planning slice is validated by:

```sh
sh scripts/test-kernel-lifecycle-rollback-plan.sh
```

Expected output:

```text
kernel_lifecycle_rollback_plan: ok
```

## Non-claims

This plan does not implement rollback. It only records the rules that a future rollback classifier must follow.
