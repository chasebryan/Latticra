# Kernel State Machine

Status: controlled in-memory state machine implementation
Scope: bounded kernel state object, sequential step function, transition log, and deterministic report surface.

## Purpose

This slice builds on the kernel state mutation seed.

The previous slice proved one gated in-memory transition can report `state_change_performed=1` while keeping `external_effect_performed=0`.

This slice adds a real mutable in-memory kernel state object. The machine starts in `created`, can be stepped forward through the approved kernel state ladder, records each step in a bounded transition log, and emits a deterministic state-machine report.

## Files

```text
include/latticra/kernel_state_machine.h
src/kernel_state_machine.c
tests/kernel_state_machine.c
scripts/test-kernel-state-machine.sh
tools/kernel_state_machine_report.c
scripts/test-kernel-state-machine-report-runner.sh
.github/workflows/kernel-state-machine.yml
docs/KERNEL_STATE_MACHINE.md
```

## State ladder

The machine uses the same sequential state ladder as the kernel state mutation seed:

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
```

## Controlled effect boundary

This slice allows internal machine mutation only:

```text
state_mutated=1
```

The machine must still report:

```text
external_effect_performed=0
```

This means the state machine mutates only its own in-memory struct and transition log.

## Validation

Run:

```sh
sh scripts/test-kernel-state-machine.sh
sh scripts/test-kernel-state-machine-report-runner.sh
```

Expected output:

```text
kernel_state_machine: ok
kernel_state_machine_report_runner: ok
```

The guards verify:

```text
machine starts in created
default step is denied and logged
allowed step mutates machine state
sequential steps advance the state ladder
illegal step is denied without mutation
report includes transition log
external_effect_performed=0 remains true
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

A later slice may connect the state machine to a kernel operator command or add rollback classification for in-memory state transitions before any external effects are introduced.
