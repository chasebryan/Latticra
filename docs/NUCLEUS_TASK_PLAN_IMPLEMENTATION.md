# Latticra Nucleus Task Plan Implementation

Status: initial implementation record
Scope: bounded C Nucleus task plan API, no-effect task-result sequencing, deterministic plan reports, invariant tests, CI script, no-effect posture, and non-claims.

## Purpose

The Nucleus task plan layer evaluates an ordered set of already-classified Nucleus task results and produces a bounded, operator-visible plan report.

This layer does not execute tasks.
It does not perform mutation.
It does not perform network access.
It does not open files.
It does not interact with hardware.
It does not upgrade future-gated work into runnable behavior.

Its purpose is to make sequencing visible while preserving Latticra's current disabled-by-default runtime posture.

## Added files

```text
include/latticra/nucleus_task_plan.h
src/nucleus_task_plan.c
tests/nucleus_task_plan_invariants.c
scripts/test-nucleus-task-plan.sh
```

## Implementation behavior

The implementation accepts a caller-provided array of `latticra_nucleus_task_result_t` records and produces one `latticra_nucleus_task_plan_result_t`.

The evaluator preserves the following rules:

```text
bounded task count only
empty plans are denied
oversized plans are denied
only successful task results are accepted
only no-effect task flags are accepted
future-gated tasks block the plan
already-denied tasks block the plan
allowed report, preview, and validation tasks can form a no-effect sequence
```

## Report fields

The deterministic report includes:

```text
plan_id
record_count
task_count
accepted_count
blocked_count
has_blocked_task
first_blocked_index
policy
reason
no_effect
execution_allowed
mutation_allowed
server_allowed
recovery_allowed
hardware_allowed
evidence_level
```

## Covered invariants

The focused test covers:

```text
accepted no-effect report/preview/validation sequence
future-gated task blocks the plan
non-no-effect task flags block the plan
operator-visible report fields
no execution allowed
no mutation allowed
no server interaction allowed
no recovery allowed
no hardware allowed
```

## Non-claims

This implementation does not create a scheduler, executor, runtime, command runner, LIR executor, Lat executor, network service, update system, recovery engine, boot path, or hardware control layer.

It is a planning and reporting slice only.
