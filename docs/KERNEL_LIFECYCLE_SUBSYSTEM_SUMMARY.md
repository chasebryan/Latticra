# Kernel Lifecycle Subsystem Summary

Status: controlled lifecycle-to-subsystem summary
Scope: report-only integration between the kernel lifecycle runner and the kernel subsystem registry.

## Purpose

This slice connects two existing kernel evidence surfaces:

```text
kernel lifecycle runner
kernel subsystem registry
```

The lifecycle runner can move a local in-memory kernel state machine from `created` to `memory-map-ready` through gated internal state changes.

The subsystem registry exposes boot, runtime, scheduler, memory, process, filesystem, network, device, and security subsystem posture.

The summary combines those surfaces into one deterministic report so the project can answer:

```text
Which kernel subsystems are lifecycle-ready?
Which subsystems still deny authority?
Did the lifecycle stay externally inert?
Is the registry still no-effect?
```

## Files

```text
include/latticra/kernel_lifecycle_subsystem_summary.h
src/kernel_lifecycle_subsystem_summary.c
tests/kernel_lifecycle_subsystem_summary.c
tools/kernel_lifecycle_subsystem_summary_report.c
scripts/test-kernel-lifecycle-subsystem-summary.sh
scripts/test-kernel-lifecycle-subsystem-summary-report-runner.sh
.github/workflows/kernel-lifecycle-subsystem-summary.yml
docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
```

## Default target

The default summary request allows the lifecycle runner to reach:

```text
memory-map-ready
```

That produces:

```text
summary_status=summary-ready
final_state=memory-map-ready
lifecycle_complete=1
lifecycle_step_count=4
lifecycle_state_change_count=4
external_effect_performed=0
registry_no_effect=1
no_external_effect_chain=1
```

## Subsystem posture

Expected readiness examples:

```text
boot -> boot-sequence-seeded
scheduler -> scheduler-ready-metadata
memory -> memory-map-ready
runtime -> runtime-not-entered
security -> security-not-production-boundary
```

Authority remains denied:

```text
runtime_entry_allowed=0
scheduler_execution_allowed=0
memory_allocation_allowed=0
```

Subsystem authority labels include:

```text
boot-denied
runtime-entry-denied
scheduler-execution-denied
memory-allocation-denied
process-execution-denied
filesystem-denied
network-denied
device-denied
not-production-boundary
```

## Controlled boundary

This slice may report internal lifecycle state mutation:

```text
lifecycle_state_mutated=1
```

It must still report:

```text
external_effect_performed=0
no_external_effect_chain=1
```

This is a summary/reporting slice only. It does not expand kernel authority or claim product readiness.

## Validation

Run:

```sh
sh scripts/test-kernel-lifecycle-subsystem-summary.sh
sh scripts/test-kernel-lifecycle-subsystem-summary-report-runner.sh
```

Expected output:

```text
kernel_lifecycle_subsystem_summary: ok
kernel_lifecycle_subsystem_summary_report_runner: ok
```

The guards verify:

```text
default request targets memory-map-ready
summary reaches memory-map-ready
summary marks boot/scheduler/memory as lifecycle-ready metadata
runtime remains not entered
runtime entry remains denied
scheduler execution remains denied
memory allocation remains denied
network and device authority remain denied
limited lifecycle summary reports incomplete readiness
external_effect_performed=0 remains true
```

## Non-claims

This slice does not make Latticra bootable, runnable as an operating system, product-ready, or authority-expanded.

## Next possible lane

A later slice may add lifecycle rollback planning, kernel memory-region validation against lifecycle readiness, or a process descriptor seed. Those should remain report-only unless a separate authority contract is introduced first.
