# Kernel Scheduler Run Entry Seed

Status: controlled scheduler run-entry metadata seed
Scope: report-only bridge from scheduler activation metadata to runtime entry intent.

This slice connects the scheduler activation seed to deterministic scheduler run-entry metadata.
It does not enter runtime execution, activate a process, switch CPU context, mutate a run queue,
read time, update accounting, dispatch scheduler work, or touch hardware.

## Files

```text
include/latticra/kernel_scheduler_run_entry.h
src/kernel_scheduler_run_entry.c
tests/kernel_scheduler_run_entry.c
tools/kernel_scheduler_run_entry_report.c
scripts/test-kernel-scheduler-run-entry.sh
scripts/test-kernel-scheduler-run-entry-report-runner.sh
.github/workflows/kernel-scheduler-run-entry.yml
```

## Evidence

The seed report emits a deterministic, no-effect boundary:

```text
run_entry_status=scheduler-run-entry-seed-ready
policy_status=report-only
scheduler_activation_status=scheduler-activation-seed-ready
scheduler_handoff_status=scheduler-handoff-seed-ready
run_entry_count=4
scheduler_run_entry_allowed=0
scheduler_activation_allowed=0
dispatch_allowed=0
run_queue_mutation_allowed=0
context_switch_allowed=0
runtime_entry_allowed=0
hardware_effect_allowed=0
host_effect_allowed=0
```

The first declared run-entry record is the kernel report process metadata:

```text
run_entry[0].process_label=kernel-report-process-metadata
run_entry[0].run_entry_class=kernel-report-scheduler-run-entry
run_entry[0].activation_token=0
run_entry[0].run_entry_rank=1
run_entry[0].run_entry_declared=1
run_entry[0].run_entry_planned=0
run_entry[0].run_entry_prepared=0
run_entry[0].execution_entered=0
run_entry[0].no_effect=1
```

The seed keeps the scheduler path honest: the lifecycle can now name the next
metadata point after activation while preserving the denial of runtime entry.

## Validation

```text
sh scripts/test-kernel-scheduler-run-entry.sh
sh scripts/test-kernel-scheduler-run-entry-report-runner.sh
```
