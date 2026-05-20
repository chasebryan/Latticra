# Kernel State Mutation Seed

Status: first controlled-effect implementation slice
Scope: gated in-memory kernel state transition.

## Purpose

This slice adds the first controlled effect-bearing kernel surface.

The effect is intentionally narrow:

```text
in-memory kernel state transition only
```

The state transition layer can move from one kernel state label to the next when an explicit gate allows it. It records the previous state, target state, next state, gate status, transition status, and whether a state change actually happened.

## Files

```text
include/latticra/kernel_state.h
src/kernel_state.c
tests/kernel_state.c
scripts/test-kernel-state.sh
tools/kernel_state_report.c
scripts/test-kernel-state-report-runner.sh
.github/workflows/kernel-state.yml
docs/KERNEL_STATE_MUTATION_SEED.md
```

## State ladder

The initial guarded ladder is:

```text
created
initialized
registry-ready
scheduler-ready
memory-map-ready
```

Allowed transitions are intentionally sequential:

```text
created -> initialized
initialized -> registry-ready
registry-ready -> scheduler-ready
scheduler-ready -> memory-map-ready
```

No-op transitions are allowed when the gate allows them.

Non-sequential transitions are denied and do not change state.

## Effect boundary

This slice changes the project posture from permanent no-effect reporting to controlled, explicit, test-covered internal effects.

The only effect this slice allows is:

```text
state_change_performed=1
```

The result must still report:

```text
external_effect_performed=0
```

This means no filesystem effect, network effect, process effect, device effect, boot effect, or host mutation is introduced.

## Validation

Run:

```sh
sh scripts/test-kernel-state.sh
sh scripts/test-kernel-state-report-runner.sh
```

Expected output:

```text
kernel_state: ok
kernel_state_report_runner: ok
```

The guards verify:

```text
default gate denies state change
allowed sequential transition changes state
illegal transition is denied
no-op transition is stable
state_change_performed=1 only on actual allowed transition
external_effect_performed=0 always
```

## Non-claims

This slice does not add:

```text
filesystem writes
network access
process execution
runtime entry
hardware behavior
boot behavior
device operation
scheduler execution
memory allocation
production security boundary
operating-system replacement
```

## Next possible lane

A later slice may add a kernel state machine runner or state persistence plan, but external effects should remain blocked until a separate effect contract and rollback policy exist.