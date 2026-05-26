# Kernel Lifecycle Seed

Status: controlled in-memory lifecycle runner
Scope: bounded lifecycle sequence over the kernel state machine.

## Purpose

This slice builds on the kernel state machine.

The state machine can mutate one in-memory state object through gated steps. This lifecycle seed runs the approved sequence through that state machine and records the final state, step count, state-change count, completion flag, and external-effect flag.

The companion report runner emits the deterministic lifecycle report from a deliberately allowed lifecycle request so the current kernel sequence evidence can be inspected through a small operator-facing tool.

## Files

```text
include/latticra/kernel_lifecycle.h
src/kernel_lifecycle.c
tests/kernel_lifecycle.c
tools/kernel_lifecycle_report.c
scripts/test-kernel-lifecycle.sh
scripts/test-kernel-lifecycle-report-runner.sh
.github/workflows/kernel-sequence.yml
docs/KERNEL_LIFECYCLE_SEED.md
```

## Lifecycle target

The default lifecycle target is:

```text
scheduler-credit-ready
```

The approved sequence is:

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
```

## Controlled effect boundary

This slice allows internal state-machine mutation only.

The result may report:

```text
state_change_count=18
lifecycle_complete=1
```

The result must still report:

```text
external_effect_performed=0
```

This means no Latticra runtime filesystem effect, network effect, process effect, device effect, runtime-entry effect, or host mutation is introduced.

The report runner only prints the deterministic lifecycle report for validation and operator inspection. The guard captures that report as test output while preserving the project boundary that the kernel lifecycle itself performs no external effects.

## Report runner

Run:

```sh
sh scripts/test-kernel-lifecycle-report-runner.sh
```

Expected output:

```text
kernel_lifecycle_report_runner: ok
```

The guard verifies:

```text
LATTICRA KERNEL LIFECYCLE REPORT
lifecycle_status=lifecycle-complete
policy_status=gate-allowed
final_state=scheduler-credit-ready
step_count=18
state_change_count=18
lifecycle_complete=1
external_effect_performed=0
machine_log_count=18
evidence_level=10
```

It also verifies the first and final transition log entries.

## Validation

Run:

```sh
sh scripts/test-kernel-lifecycle.sh
sh scripts/test-kernel-lifecycle-report-runner.sh
```

Expected output:

```text
kernel_lifecycle: ok
kernel_lifecycle_report_runner: ok
```

The guards verify:

```text
default request is denied
allowed lifecycle reaches scheduler-credit-ready
intermediate target stops correctly
step limit is respected
report includes lifecycle completion and transition log
report runner emits deterministic lifecycle evidence
external_effect_performed=0 remains true
```

## Non-claims

This slice does not add:

```text
filesystem writes in the Latticra kernel lifecycle
network access
process execution
runtime entry
hardware behavior
device operation
scheduler tick
run queue mutation
context switching
time accounting
process wakeups
timer arming
preemption
quota updates
scheduler credit updates
time reads
scheduler execution
memory allocation
production security boundary
operating-system replacement
```

## Next possible lane

A later slice may add lifecycle rollback, lifecycle-to-subsystem summary reporting, or state persistence planning before any external effects are introduced.
