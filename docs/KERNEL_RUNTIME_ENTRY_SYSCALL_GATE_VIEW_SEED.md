# Kernel Runtime Entry Syscall Gate View Seed

Status: controlled runtime-entry syscall-gate-view metadata seed
Scope: report-only bridge from runtime-entry privilege-level-view metadata to declared syscall-gate metadata.

This slice connects runtime-entry privilege-level-view metadata to deterministic syscall-gate-view metadata.
It does not install syscall gates, dispatch syscalls, execute syscall instructions, enter syscall handlers,
return from syscalls, change CPU privilege level, return from interrupts, enter runtime execution,
switch address spaces, write page tables, flush TLBs, update MMU state, switch CPU context,
mutate a run queue, dispatch scheduler work, or touch hardware.

## Files

```text
include/latticra/kernel_runtime_entry_syscall_gate_view.h
src/kernel_runtime_entry_syscall_gate_view.c
tests/kernel_runtime_entry_syscall_gate_view.c
tools/kernel_runtime_entry_syscall_gate_view_report.c
scripts/test-kernel-runtime-entry-syscall-gate-view.sh
scripts/test-kernel-runtime-entry-syscall-gate-view-report-runner.sh
.github/workflows/kernel-runtime-entry-syscall-gate-view.yml
```

## Evidence

The seed report emits a deterministic, no-effect boundary:

```text
syscall_gate_view_status=runtime-entry-syscall-gate-view-seed-ready
policy_status=report-only
runtime_entry_privilege_level_view_status=runtime-entry-privilege-level-view-seed-ready
runtime_entry_address_space_view_status=runtime-entry-address-space-view-seed-ready
runtime_entry_stack_view_status=runtime-entry-stack-view-seed-ready
runtime_entry_register_view_status=runtime-entry-register-view-seed-ready
runtime_entry_frame_status=runtime-entry-frame-seed-ready
runtime_entry_admission_status=runtime-entry-admission-seed-ready
scheduler_run_entry_status=scheduler-run-entry-seed-ready
syscall_gate_view_count=4
runtime_entry_syscall_gate_view_allowed=0
runtime_entry_privilege_level_view_allowed=0
runtime_entry_allowed=0
privilege_transition_allowed=0
syscall_gate_allowed=0
syscall_dispatch_allowed=0
syscall_instruction_allowed=0
syscall_handler_allowed=0
syscall_return_allowed=0
interrupt_return_allowed=0
hardware_effect_allowed=0
host_effect_allowed=0
```

The first declared syscall-gate-view record is the kernel report process metadata:

```text
syscall_gate_view[0].process_label=kernel-report-process-metadata
syscall_gate_view[0].syscall_gate_view_class=kernel-report-runtime-entry-syscall-gate-view
syscall_gate_view[0].syscall_gate_view_token=0
syscall_gate_view[0].privilege_level_view_token=0
syscall_gate_view[0].privilege_level=0
syscall_gate_view[0].ring_number=0
syscall_gate_view[0].syscall_number=512
syscall_gate_view[0].gate_vector=128
syscall_gate_view[0].handler_slot=0
syscall_gate_view[0].syscall_gate_view_declared=1
syscall_gate_view[0].syscall_number_declared=1
syscall_gate_view[0].syscall_vector_declared=1
syscall_gate_view[0].syscall_handler_declared=1
syscall_gate_view[0].syscall_gate_view_planned=0
syscall_gate_view[0].syscall_dispatch_planned=0
syscall_gate_view[0].syscall_instruction_planned=0
syscall_gate_view[0].syscall_handler_planned=0
syscall_gate_view[0].syscall_return_planned=0
syscall_gate_view[0].runtime_entry_syscall_gate_view_allowed=0
syscall_gate_view[0].syscall_gate_allowed=0
syscall_gate_view[0].syscall_dispatch_allowed=0
syscall_gate_view[0].syscall_instruction_allowed=0
syscall_gate_view[0].syscall_handler_allowed=0
syscall_gate_view[0].syscall_return_allowed=0
syscall_gate_view[0].no_effect=1
```

The seed keeps the runtime boundary explicit: the lifecycle can name the next
metadata point after runtime-entry privilege-level-view declaration while preserving
the denial of syscall gate installation, syscall dispatch, syscall instruction
execution, syscall handler entry, syscall returns, privilege transitions, interrupt
returns, runtime entry, context switching, scheduler execution, and hardware effects.

## Validation

```text
sh scripts/test-kernel-runtime-entry-syscall-gate-view.sh
sh scripts/test-kernel-runtime-entry-syscall-gate-view-report-runner.sh
```
