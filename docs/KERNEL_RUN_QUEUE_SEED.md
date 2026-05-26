# Kernel Run Queue Seed

Status: controlled run queue metadata seed
Scope: report-only bridge from scheduler tick metadata to run queue intent.

## Purpose

This slice connects the scheduler tick seed to deterministic run queue metadata.

It does not enqueue processes, dequeue processes, dispatch work, mutate run queues, switch contexts, account CPU time, wake processes, preempt execution, or touch hardware. It records queue declarations that future scheduler work can refine behind explicit authority gates.

## Files

```text
include/latticra/kernel_run_queue.h
src/kernel_run_queue.c
tests/kernel_run_queue.c
tools/kernel_run_queue_report.c
scripts/test-kernel-run-queue.sh
scripts/test-kernel-run-queue-report-runner.sh
.github/workflows/kernel-run-queue.yml
docs/KERNEL_RUN_QUEUE_SEED.md
```

## Current posture

The default request evaluates the scheduler tick seed and emits:

```text
queue_status=run-queue-seed-ready
scheduler_tick_status=scheduler-tick-seed-ready
timer_source_status=timer-source-seed-ready
interrupt_table_status=interrupt-table-seed-ready
scheduler_status=scheduler-seed-ready
queue_count=4
no_effect=1
```

Authority remains denied:

```text
run_queue_mutation_allowed=0
enqueue_allowed=0
dequeue_allowed=0
dispatch_allowed=0
context_switch_allowed=0
preemption_allowed=0
time_accounting_allowed=0
process_wake_allowed=0
hardware_effect_allowed=0
host_effect_allowed=0
```

## Validation

Run:

```sh
sh scripts/test-kernel-run-queue.sh
sh scripts/test-kernel-run-queue-report-runner.sh
```

Expected output:

```text
kernel_run_queue: ok
kernel_run_queue_report_runner: ok
```

## Non-claims

This slice does not schedule execution, mutate run queues, perform context switches, wake processes, account CPU time, dispatch interrupts, perform I/O, boot hardware, or replace an operating system.
