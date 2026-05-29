# Kernel Time Accounting Seed

Status: controlled time accounting metadata seed
Scope: report-only bridge from context switch metadata to CPU charge intent.

## Purpose

This slice connects the context switch seed to deterministic time accounting metadata.

It does not read time, charge CPU usage, write process usage counters, update quotas, update scheduler credits, mutate run queues, wake processes, preempt execution, or touch hardware. It records candidate accounting declarations that future scheduler work can refine behind explicit authority gates.

## Files

```text
include/latticra/kernel_time_accounting.h
src/kernel_time_accounting.c
tests/kernel_time_accounting.c
tools/kernel_time_accounting_report.c
scripts/test-kernel-time-accounting.sh
scripts/test-kernel-time-accounting-report-runner.sh
.github/workflows/kernel-time-accounting.yml
docs/KERNEL_TIME_ACCOUNTING_SEED.md
```

## Current Posture

The default request evaluates the context switch seed and emits:

```text
accounting_status=time-accounting-seed-ready
context_switch_status=context-switch-seed-ready
run_queue_status=run-queue-seed-ready
scheduler_tick_status=scheduler-tick-seed-ready
timer_source_status=timer-source-seed-ready
account_count=4
no_effect=1
```

Authority remains denied:

```text
time_accounting_allowed=0
time_read_allowed=0
cpu_usage_write_allowed=0
quota_update_allowed=0
scheduler_credit_update_allowed=0
context_switch_allowed=0
run_queue_mutation_allowed=0
preemption_allowed=0
process_wake_allowed=0
hardware_effect_allowed=0
host_effect_allowed=0
```

## Validation

Run:

```sh
sh scripts/test-kernel-time-accounting.sh
sh scripts/test-kernel-time-accounting-report-runner.sh
```

Expected output:

```text
kernel_time_accounting: ok
kernel_time_accounting_report_runner: ok
```

## Non-claims

This slice does not schedule execution, mutate run queues, perform context switches, read clocks, account CPU time, wake processes, dispatch interrupts, perform I/O, boot hardware, or replace an operating system.
