# Kernel Runtime Entry Frame Seed

Status: controlled runtime-entry frame metadata seed
Scope: report-only bridge from runtime-entry admission metadata to declared runtime-entry frame metadata.

This slice connects runtime-entry admission to deterministic runtime-entry frame metadata.
It does not build a frame, install a frame, admit a process, enter runtime execution, switch
CPU context, mutate a run queue, read time, update accounting, dispatch scheduler work, or
touch hardware.

## Files

```text
include/latticra/kernel_runtime_entry_frame.h
src/kernel_runtime_entry_frame.c
tests/kernel_runtime_entry_frame.c
tools/kernel_runtime_entry_frame_report.c
scripts/test-kernel-runtime-entry-frame.sh
scripts/test-kernel-runtime-entry-frame-report-runner.sh
.github/workflows/kernel-runtime-entry-frame.yml
```

## Evidence

The seed report emits a deterministic, no-effect boundary:

```text
frame_status=runtime-entry-frame-seed-ready
policy_status=report-only
runtime_entry_admission_status=runtime-entry-admission-seed-ready
scheduler_run_entry_status=scheduler-run-entry-seed-ready
frame_count=4
runtime_entry_frame_allowed=0
runtime_entry_admission_allowed=0
runtime_entry_allowed=0
scheduler_run_entry_allowed=0
dispatch_allowed=0
run_queue_mutation_allowed=0
context_switch_allowed=0
stack_switch_allowed=0
hardware_effect_allowed=0
host_effect_allowed=0
```

The first declared frame record is the kernel report process metadata:

```text
frame[0].process_label=kernel-report-process-metadata
frame[0].frame_class=kernel-report-runtime-entry-frame
frame[0].frame_token=0
frame[0].admission_token=0
frame[0].run_entry_token=0
frame[0].admission_rank=1
frame[0].frame_rank=1
frame[0].frame_declared=1
frame[0].frame_planned=0
frame[0].frame_built=0
frame[0].frame_installed=0
frame[0].runtime_entry_entered=0
frame[0].execution_entered=0
frame[0].no_effect=1
```

The seed keeps the runtime boundary explicit: the lifecycle can name the next
metadata point after runtime-entry admission while preserving the denial of frame
construction, runtime entry, scheduler execution, and hardware effects.

## Validation

```text
sh scripts/test-kernel-runtime-entry-frame.sh
sh scripts/test-kernel-runtime-entry-frame-report-runner.sh
```
