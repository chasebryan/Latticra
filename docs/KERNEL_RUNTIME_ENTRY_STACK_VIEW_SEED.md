# Kernel Runtime Entry Stack View Seed

Status: controlled runtime-entry stack-view metadata seed
Scope: report-only bridge from runtime-entry register-view metadata to declared stack-view metadata.

This slice connects runtime-entry register-view metadata to deterministic stack-view metadata.
It does not capture stacks, switch stacks, map stacks, save registers, restore registers,
switch address spaces, switch CPU context, enter runtime execution, mutate a run queue,
read time, update accounting, dispatch scheduler work, or touch hardware.

## Files

```text
include/latticra/kernel_runtime_entry_stack_view.h
src/kernel_runtime_entry_stack_view.c
tests/kernel_runtime_entry_stack_view.c
tools/kernel_runtime_entry_stack_view_report.c
scripts/test-kernel-runtime-entry-stack-view.sh
scripts/test-kernel-runtime-entry-stack-view-report-runner.sh
.github/workflows/kernel-runtime-entry-stack-view.yml
```

## Evidence

The seed report emits a deterministic, no-effect boundary:

```text
stack_view_status=runtime-entry-stack-view-seed-ready
policy_status=report-only
runtime_entry_register_view_status=runtime-entry-register-view-seed-ready
runtime_entry_frame_status=runtime-entry-frame-seed-ready
runtime_entry_admission_status=runtime-entry-admission-seed-ready
scheduler_run_entry_status=scheduler-run-entry-seed-ready
stack_view_count=4
runtime_entry_stack_view_allowed=0
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

The first declared stack-view record is the kernel report process metadata:

```text
stack_view[0].process_label=kernel-report-process-metadata
stack_view[0].stack_view_class=kernel-report-runtime-entry-stack-view
stack_view[0].stack_view_token=0
stack_view[0].register_view_token=0
stack_view[0].frame_token=0
stack_view[0].stack_view_rank=1
stack_view[0].stack_slot_count=4
stack_view[0].stack_window_bytes=4096
stack_view[0].stack_base_declared=1
stack_view[0].stack_pointer_declared=1
stack_view[0].stack_limit_declared=1
stack_view[0].guard_page_declared=1
stack_view[0].stack_view_planned=0
stack_view[0].stack_capture_planned=0
stack_view[0].stack_switch_planned=0
stack_view[0].stack_switch_allowed=0
stack_view[0].no_effect=1
```

The seed keeps the runtime boundary explicit: the lifecycle can name the next
metadata point after runtime-entry register-view declaration while preserving
the denial of stack capture, stack switching, stack mapping, register save/restore,
context switching, runtime entry, scheduler execution, and hardware effects.

## Validation

```text
sh scripts/test-kernel-runtime-entry-stack-view.sh
sh scripts/test-kernel-runtime-entry-stack-view-report-runner.sh
```
