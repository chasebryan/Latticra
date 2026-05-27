# Kernel Runtime Entry Admission Seed

Status: controlled runtime-entry admission metadata seed
Scope: report-only bridge from scheduler run-entry metadata to runtime-entry admission intent.

This slice connects the scheduler run-entry seed to deterministic runtime-entry admission metadata.
It does not admit a process, enter runtime execution, switch CPU context, mutate a run queue,
read time, update accounting, dispatch scheduler work, or touch hardware.

## Files

```text
include/latticra/kernel_runtime_entry_admission.h
src/kernel_runtime_entry_admission.c
tests/kernel_runtime_entry_admission.c
tools/kernel_runtime_entry_admission_report.c
scripts/test-kernel-runtime-entry-admission.sh
scripts/test-kernel-runtime-entry-admission-report-runner.sh
.github/workflows/kernel-runtime-entry-admission.yml
```

## Evidence

The seed report emits a deterministic, no-effect boundary:

```text
admission_status=runtime-entry-admission-seed-ready
policy_status=report-only
scheduler_run_entry_status=scheduler-run-entry-seed-ready
scheduler_activation_status=scheduler-activation-seed-ready
admission_count=4
runtime_entry_admission_allowed=0
runtime_entry_allowed=0
scheduler_run_entry_allowed=0
dispatch_allowed=0
run_queue_mutation_allowed=0
context_switch_allowed=0
hardware_effect_allowed=0
host_effect_allowed=0
```

The first declared admission record is the kernel report process metadata:

```text
admission[0].process_label=kernel-report-process-metadata
admission[0].admission_class=kernel-report-runtime-entry-admission
admission[0].run_entry_token=0
admission[0].admission_rank=1
admission[0].admission_declared=1
admission[0].admission_planned=0
admission[0].admitted=0
admission[0].runtime_entry_entered=0
admission[0].execution_entered=0
admission[0].no_effect=1
```

The seed keeps the runtime boundary explicit: the lifecycle can name the next
metadata point after scheduler run-entry while preserving the denial of runtime entry.

## Validation

```text
sh scripts/test-kernel-runtime-entry-admission.sh
sh scripts/test-kernel-runtime-entry-admission-report-runner.sh
```
