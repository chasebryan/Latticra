# Kernel Runtime Entry Syscall Dispatch View Seed

Status: controlled runtime-entry syscall-dispatch-view metadata seed
Scope: report-only bridge from runtime-entry syscall-gate-view metadata to declared syscall-dispatch metadata.

This slice connects runtime-entry syscall-gate-view metadata to deterministic syscall-dispatch-view metadata.
It does not dispatch syscalls, copy syscall arguments, execute syscall instructions,
enter syscall handlers, return from syscalls, install syscall gates, change CPU
privilege level, return from interrupts, enter runtime execution, switch address
spaces, write page tables, flush TLBs, update MMU state, switch CPU context,
mutate a run queue, dispatch scheduler work, or touch hardware.

## Files

```text
include/latticra/kernel_runtime_entry_syscall_dispatch_view.h
src/kernel_runtime_entry_syscall_dispatch_view.c
tests/kernel_runtime_entry_syscall_dispatch_view.c
tools/kernel_runtime_entry_syscall_dispatch_view_report.c
scripts/test-kernel-runtime-entry-syscall-dispatch-view.sh
scripts/test-kernel-runtime-entry-syscall-dispatch-view-report-runner.sh
.github/workflows/kernel-runtime-entry-syscall-dispatch-view.yml
```

## Evidence

The seed report emits a deterministic, no-effect boundary:

```text
syscall_dispatch_view_status=runtime-entry-syscall-dispatch-view-seed-ready
policy_status=report-only
runtime_entry_syscall_gate_view_status=runtime-entry-syscall-gate-view-seed-ready
runtime_entry_privilege_level_view_status=runtime-entry-privilege-level-view-seed-ready
runtime_entry_address_space_view_status=runtime-entry-address-space-view-seed-ready
runtime_entry_stack_view_status=runtime-entry-stack-view-seed-ready
runtime_entry_register_view_status=runtime-entry-register-view-seed-ready
runtime_entry_frame_status=runtime-entry-frame-seed-ready
runtime_entry_admission_status=runtime-entry-admission-seed-ready
scheduler_run_entry_status=scheduler-run-entry-seed-ready
syscall_dispatch_view_count=4
runtime_entry_syscall_dispatch_view_allowed=0
runtime_entry_syscall_gate_view_allowed=0
runtime_entry_allowed=0
syscall_gate_allowed=0
syscall_dispatch_allowed=0
syscall_argument_copy_allowed=0
syscall_instruction_allowed=0
syscall_handler_allowed=0
syscall_return_allowed=0
interrupt_return_allowed=0
hardware_effect_allowed=0
host_effect_allowed=0
```

The first declared syscall-dispatch-view record is the kernel report process metadata:

```text
syscall_dispatch_view[0].process_label=kernel-report-process-metadata
syscall_dispatch_view[0].syscall_dispatch_view_class=kernel-report-runtime-entry-syscall-dispatch-view
syscall_dispatch_view[0].syscall_dispatch_view_token=0
syscall_dispatch_view[0].syscall_gate_view_token=0
syscall_dispatch_view[0].syscall_number=512
syscall_dispatch_view[0].gate_vector=128
syscall_dispatch_view[0].handler_slot=0
syscall_dispatch_view[0].dispatch_slot=1024
syscall_dispatch_view[0].argument_count=6
syscall_dispatch_view[0].syscall_dispatch_view_declared=1
syscall_dispatch_view[0].syscall_dispatch_declared=1
syscall_dispatch_view[0].syscall_argument_window_declared=1
syscall_dispatch_view[0].syscall_handler_declared=1
syscall_dispatch_view[0].syscall_return_declared=1
syscall_dispatch_view[0].syscall_dispatch_view_planned=0
syscall_dispatch_view[0].syscall_dispatch_planned=0
syscall_dispatch_view[0].syscall_argument_copy_planned=0
syscall_dispatch_view[0].syscall_handler_planned=0
syscall_dispatch_view[0].runtime_entry_syscall_dispatch_view_allowed=0
syscall_dispatch_view[0].syscall_dispatch_allowed=0
syscall_dispatch_view[0].syscall_argument_copy_allowed=0
syscall_dispatch_view[0].no_effect=1
```

The seed keeps the runtime boundary explicit: the lifecycle can name the next
metadata point after runtime-entry syscall-gate-view declaration while preserving
the denial of syscall dispatch, syscall argument copying, syscall instruction
execution, syscall handler entry, syscall returns, runtime entry, context
switching, scheduler execution, and hardware effects.

## Validation

```text
sh scripts/test-kernel-runtime-entry-syscall-dispatch-view.sh
sh scripts/test-kernel-runtime-entry-syscall-dispatch-view-report-runner.sh
```
