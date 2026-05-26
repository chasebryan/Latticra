# Kernel Context Switch Seed

Status: controlled context switch metadata seed
Scope: report-only bridge from run queue metadata to context switch intent.

## Purpose

This slice connects the run queue seed to deterministic context switch metadata.

It does not save registers, restore registers, switch stacks, switch address spaces, dispatch work, mutate run queues, preempt execution, wake processes, or touch hardware. It records candidate context switch declarations that future scheduler work can refine behind explicit authority gates.

## Files

```text
include/latticra/kernel_context_switch.h
src/kernel_context_switch.c
tests/kernel_context_switch.c
tools/kernel_context_switch_report.c
scripts/test-kernel-context-switch.sh
scripts/test-kernel-context-switch-report-runner.sh
.github/workflows/kernel-context-switch.yml
docs/KERNEL_CONTEXT_SWITCH_SEED.md
```

## Current Posture

The default request evaluates the run queue seed and emits:

```text
switch_status=context-switch-seed-ready
run_queue_status=run-queue-seed-ready
scheduler_tick_status=scheduler-tick-seed-ready
timer_source_status=timer-source-seed-ready
switch_count=4
no_effect=1
```

Authority remains denied:

```text
context_switch_allowed=0
register_save_allowed=0
register_restore_allowed=0
stack_switch_allowed=0
address_space_switch_allowed=0
dispatch_allowed=0
run_queue_mutation_allowed=0
preemption_allowed=0
time_accounting_allowed=0
process_wake_allowed=0
hardware_effect_allowed=0
host_effect_allowed=0
```

## Validation

Run:

```sh
sh scripts/test-kernel-context-switch.sh
sh scripts/test-kernel-context-switch-report-runner.sh
```

Expected output:

```text
kernel_context_switch: ok
kernel_context_switch_report_runner: ok
```

## Non-claims

This slice does not schedule execution, mutate run queues, perform a context switch, save or restore registers, switch stacks, switch address spaces, account CPU time, wake processes, dispatch interrupts, perform I/O, boot hardware, or replace an operating system.
