# Kernel Scheduler Dispatch Seed

Status: controlled scheduler dispatch metadata seed
Scope: report-only bridge from scheduler selection metadata to scheduler dispatch intent.

## Purpose

This slice connects the scheduler selection seed to deterministic scheduler dispatch metadata.

It does not dispatch a runnable process, dequeue or enqueue work, mutate run queues, switch contexts, update scheduler credits, update quotas, write CPU usage, preempt execution, wake processes, persist state, or touch hardware. It records dispatch declarations that future scheduler work can refine behind explicit authority gates.

## Files

```text
include/latticra/kernel_scheduler_dispatch.h
src/kernel_scheduler_dispatch.c
tests/kernel_scheduler_dispatch.c
tools/kernel_scheduler_dispatch_report.c
scripts/test-kernel-scheduler-dispatch.sh
scripts/test-kernel-scheduler-dispatch-report-runner.sh
.github/workflows/kernel-scheduler-dispatch.yml
docs/KERNEL_SCHEDULER_DISPATCH_SEED.md
```

## Current Posture

The default request evaluates the scheduler selection seed and emits:

```text
dispatch_status=scheduler-dispatch-seed-ready
scheduler_selection_status=scheduler-selection-seed-ready
scheduler_credit_status=scheduler-credit-seed-ready
preemption_status=preemption-seed-ready
time_accounting_status=time-accounting-seed-ready
context_switch_status=context-switch-seed-ready
run_queue_status=run-queue-seed-ready
scheduler_tick_status=scheduler-tick-seed-ready
timer_source_status=timer-source-seed-ready
dispatch_count=4
no_effect=1
```

Authority remains denied:

```text
scheduler_dispatch_allowed=0
scheduler_selection_allowed=0
dispatch_allowed=0
run_queue_mutation_allowed=0
context_switch_allowed=0
preemption_allowed=0
scheduler_credit_update_allowed=0
quota_update_allowed=0
cpu_usage_write_allowed=0
time_accounting_allowed=0
time_read_allowed=0
process_wake_allowed=0
hardware_effect_allowed=0
host_effect_allowed=0
```

## Validation

Run:

```sh
sh scripts/test-kernel-scheduler-dispatch.sh
sh scripts/test-kernel-scheduler-dispatch-report-runner.sh
```

Expected output:

```text
kernel_scheduler_dispatch: ok
kernel_scheduler_dispatch_report_runner: ok
```

## Non-claims

This slice does not schedule execution, dispatch a runnable process, mutate run queues, enqueue or dequeue work, perform context switches, read clocks, account CPU time, update quotas, update scheduler credits, preempt execution, wake processes, dispatch interrupts, perform I/O, boot hardware, or replace an operating system.
