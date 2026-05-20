# Kernel Scheduler Seed

Status: kernel scheduler seed implementation
Scope: compiled scheduler-slot metadata and deterministic report surface.

## Purpose

This slice adds the first kernel scheduler seed surface on top of the kernel subsystem registry.

The scheduler seed does not schedule execution. It evaluates the kernel subsystem registry, records deterministic scheduler-slot metadata, and emits a report that proves the scheduler lane is present while remaining no-effect.

## Files

```text
include/latticra/kernel_scheduler.h
src/kernel_scheduler.c
tests/kernel_scheduler.c
scripts/test-kernel-scheduler.sh
tools/kernel_scheduler_report.c
scripts/test-kernel-scheduler-report-runner.sh
.github/workflows/kernel-scheduler.yml
docs/KERNEL_SCHEDULER_SEED.md
```

## Validation

Run:

```sh
sh scripts/test-kernel-scheduler.sh
sh scripts/test-kernel-scheduler-report-runner.sh
```

Expected output:

```text
kernel_scheduler: ok
kernel_scheduler_report_runner: ok
```

The guards verify:

```text
scheduler_status=scheduler-seed-ready
policy_status=report-only
registry_status=registry-ready
slot_count=3
slot[0].label=idle-metadata
slot[1].label=kernel-report-metadata
slot[2].label=operator-report-metadata
slot[0].selection_status=not-selected
no_effect=1
```

## Boundary

This is metadata and reporting only.

It does not start scheduler behavior, select runnable work, switch contexts, run processes, mutate memory, enter runtime execution, perform I/O, operate devices, enforce a production security boundary, boot hardware, or replace an operating system.

The scheduler seed exists so future work can add scheduler policy, queues, and state machines one guarded slice at a time.