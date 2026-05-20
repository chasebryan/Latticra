# Kernel Lifecycle Seed

Status: controlled in-memory lifecycle runner
Scope: bounded lifecycle sequence over the kernel state machine.

## Purpose

This slice builds on the kernel state machine.

The state machine can mutate one in-memory state object through gated steps. This lifecycle seed runs the approved sequence through that state machine and records the final state, step count, state-change count, completion flag, and external-effect flag.

## Files

```text
include/latticra/kernel_lifecycle.h
src/kernel_lifecycle.c
tests/kernel_lifecycle.c
scripts/test-kernel-lifecycle.sh
.github/workflows/kernel-lifecycle.yml
docs/KERNEL_LIFECYCLE_SEED.md
```

## Lifecycle target

The default lifecycle target is:

```text
memory-map-ready
```

The approved sequence is:

```text
created -> initialized
initialized -> registry-ready
registry-ready -> scheduler-ready
scheduler-ready -> memory-map-ready
```

## Controlled effect boundary

This slice allows internal state-machine mutation only.

The result may report:

```text
state_change_count=4
lifecycle_complete=1
```

The result must still report:

```text
external_effect_performed=0
```

This means no filesystem effect, network effect, process effect, device effect, runtime-entry effect, or host mutation is introduced.

## Validation

Run:

```sh
sh scripts/test-kernel-lifecycle.sh
```

Expected output:

```text
kernel_lifecycle: ok
```

The guard verifies:

```text
default request is denied
allowed lifecycle reaches memory-map-ready
intermediate target stops correctly
step limit is respected
report includes lifecycle completion and transition log
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
device operation
scheduler execution
memory allocation
production security boundary
operating-system replacement
```

## Next possible lane

A later slice may add a lifecycle report runner, lifecycle rollback, or state persistence plan before any external effects are introduced.