# Kernel Runtime Entry Register View Seed

Status: controlled runtime-entry register-view metadata seed
Scope: report-only bridge from runtime-entry frame metadata to declared register-view metadata.

This slice connects runtime-entry frame metadata to deterministic register-view metadata.
It does not capture registers, save registers, restore registers, switch stacks, switch
address spaces, switch CPU context, enter runtime execution, mutate a run queue, read
time, update accounting, dispatch scheduler work, or touch hardware.

## Files

```text
include/latticra/kernel_runtime_entry_register_view.h
src/kernel_runtime_entry_register_view.c
tests/kernel_runtime_entry_register_view.c
tools/kernel_runtime_entry_register_view_report.c
scripts/test-kernel-runtime-entry-register-view.sh
scripts/test-kernel-runtime-entry-register-view-report-runner.sh
.github/workflows/kernel-runtime-entry-register-view.yml
```

## Evidence

The seed report emits a deterministic, no-effect boundary:

```text
register_view_status=runtime-entry-register-view-seed-ready
policy_status=report-only
runtime_entry_frame_status=runtime-entry-frame-seed-ready
runtime_entry_admission_status=runtime-entry-admission-seed-ready
scheduler_run_entry_status=scheduler-run-entry-seed-ready
register_view_count=4
runtime_entry_register_view_allowed=0
runtime_entry_frame_allowed=0
runtime_entry_admission_allowed=0
runtime_entry_allowed=0
context_switch_allowed=0
register_save_allowed=0
register_restore_allowed=0
stack_switch_allowed=0
address_space_switch_allowed=0
hardware_effect_allowed=0
host_effect_allowed=0
```

The first declared register-view record is the kernel report process metadata:

```text
register_view[0].process_label=kernel-report-process-metadata
register_view[0].register_view_class=kernel-report-runtime-entry-register-view
register_view[0].register_view_token=0
register_view[0].frame_token=0
register_view[0].register_view_rank=1
register_view[0].register_slot_count=16
register_view[0].instruction_pointer_declared=1
register_view[0].stack_pointer_declared=1
register_view[0].flags_declared=1
register_view[0].register_view_planned=0
register_view[0].register_capture_planned=0
register_view[0].register_save_allowed=0
register_view[0].register_restore_allowed=0
register_view[0].no_effect=1
```

The seed keeps the runtime boundary explicit: the lifecycle can name the next
metadata point after runtime-entry frame declaration while preserving the denial
of register capture, register save/restore, stack switching, context switching,
runtime entry, scheduler execution, and hardware effects.

## Validation

```text
sh scripts/test-kernel-runtime-entry-register-view.sh
sh scripts/test-kernel-runtime-entry-register-view-report-runner.sh
```
