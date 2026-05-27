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

The current guarded ladder is:

```text
created
initialized
registry-ready
scheduler-ready
memory-map-ready
process-table-ready
syscall-table-ready
ipc-table-ready
vfs-namespace-ready
device-registry-ready
driver-catalog-ready
interrupt-table-ready
timer-source-ready
scheduler-tick-ready
run-queue-ready
context-switch-ready
time-accounting-ready
preemption-ready
scheduler-credit-ready
scheduler-selection-ready
scheduler-dispatch-ready
scheduler-handoff-ready
scheduler-activation-ready
scheduler-run-entry-ready
runtime-entry-admission-ready
runtime-entry-frame-ready
runtime-entry-register-view-ready
runtime-entry-stack-view-ready
runtime-entry-address-space-view-ready
```

Allowed transitions are intentionally sequential:

```text
created -> initialized
initialized -> registry-ready
registry-ready -> scheduler-ready
scheduler-ready -> memory-map-ready
memory-map-ready -> process-table-ready
process-table-ready -> syscall-table-ready
syscall-table-ready -> ipc-table-ready
ipc-table-ready -> vfs-namespace-ready
vfs-namespace-ready -> device-registry-ready
device-registry-ready -> driver-catalog-ready
driver-catalog-ready -> interrupt-table-ready
interrupt-table-ready -> timer-source-ready
timer-source-ready -> scheduler-tick-ready
scheduler-tick-ready -> run-queue-ready
run-queue-ready -> context-switch-ready
context-switch-ready -> time-accounting-ready
time-accounting-ready -> preemption-ready
preemption-ready -> scheduler-credit-ready
scheduler-credit-ready -> scheduler-selection-ready
scheduler-selection-ready -> scheduler-dispatch-ready
scheduler-dispatch-ready -> scheduler-handoff-ready
scheduler-handoff-ready -> scheduler-activation-ready
scheduler-activation-ready -> scheduler-run-entry-ready
scheduler-run-entry-ready -> runtime-entry-admission-ready
runtime-entry-admission-ready -> runtime-entry-frame-ready
runtime-entry-frame-ready -> runtime-entry-register-view-ready
runtime-entry-register-view-ready -> runtime-entry-stack-view-ready
runtime-entry-stack-view-ready -> runtime-entry-address-space-view-ready
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

A later slice may add state persistence planning or rollback classification, but external effects should remain blocked until a separate effect contract and rollback policy exist.
