# Kernel Preemption Seed

Status: controlled preemption metadata seed
Scope: report-only bridge from time accounting metadata to preemption decision intent.

## Purpose

This slice connects the time accounting seed to deterministic preemption decision metadata.

It does not read time, arm timers, preempt execution, dispatch work, switch contexts, mutate run queues, update scheduler credits, wake processes, or touch hardware. It records candidate preemption declarations that future scheduler work can refine behind explicit authority gates.

## Files

```text
include/latticra/kernel_preemption.h
src/kernel_preemption.c
tests/kernel_preemption.c
tools/kernel_preemption_report.c
scripts/test-kernel-preemption.sh
scripts/test-kernel-preemption-report-runner.sh
.github/workflows/kernel-preemption.yml
docs/KERNEL_PREEMPTION_SEED.md
```

## Current Posture

The default request evaluates the time accounting seed and emits:

```text
preemption_status=preemption-seed-ready
time_accounting_status=time-accounting-seed-ready
context_switch_status=context-switch-seed-ready
run_queue_status=run-queue-seed-ready
scheduler_tick_status=scheduler-tick-seed-ready
timer_source_status=timer-source-seed-ready
decision_count=4
no_effect=1
```

Authority remains denied:

```text
preemption_allowed=0
time_read_allowed=0
time_accounting_allowed=0
context_switch_allowed=0
dispatch_allowed=0
run_queue_mutation_allowed=0
scheduler_credit_update_allowed=0
process_wake_allowed=0
hardware_effect_allowed=0
host_effect_allowed=0
```

## Validation

Run:

```sh
sh scripts/test-kernel-preemption.sh
sh scripts/test-kernel-preemption-report-runner.sh
```

Expected output:

```text
kernel_preemption: ok
kernel_preemption_report_runner: ok
```

## Non-claims

This slice does not schedule execution, mutate run queues, perform context switches, read clocks, account CPU time, preempt execution, wake processes, dispatch interrupts, perform I/O, boot hardware, or replace an operating system.
