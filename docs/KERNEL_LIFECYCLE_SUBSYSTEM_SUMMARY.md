# Kernel Lifecycle Subsystem Summary

Status: controlled lifecycle-to-subsystem summary with nucleus-first coupling
Scope: report-only integration between the kernel lifecycle runner, kernel subsystem registry, and nucleus-kernel coupling gate.

## Purpose

This slice connects three existing evidence surfaces:

```text
kernel lifecycle runner
kernel subsystem registry
nucleus-kernel coupling gate
```

The lifecycle runner can move a local in-memory kernel state machine from `created` to `runtime-entry-recovery-audit-observation-view-ready` through gated internal state changes.

The subsystem registry exposes boot, runtime, scheduler, memory, process, filesystem, network, device, and security subsystem posture.

The nucleus-kernel coupling gate requires a no-effect nucleus task plan before
the summary may claim OS-readiness metadata.

The summary combines those surfaces into one deterministic report so the project can answer:

```text
Which kernel subsystems are lifecycle-ready?
Which subsystems still deny authority?
Did the nucleus approve only no-effect coupling evidence?
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
runtime-entry-recovery-audit-observation-view-ready
```

That produces:

```text
summary_status=summary-ready
final_state=runtime-entry-recovery-audit-observation-view-ready
lifecycle_complete=1
lifecycle_step_count=46
lifecycle_state_change_count=46
external_effect_performed=0
registry_no_effect=1
nucleus_coupling_status=nucleus-kernel-coupling-ready
os_readiness_status=os-metadata-ready
nucleus_coupling_ready=1
nucleus_no_effect_chain_ok=1
no_external_effect_chain=1
```

## Subsystem posture

Expected readiness examples:

```text
boot -> boot-sequence-seeded
scheduler -> scheduler-run-entry-ready
runtime -> runtime-entry-recovery-audit-observation-view-ready
memory -> memory-map-ready
process -> ipc-table-ready
filesystem -> vfs-namespace-ready
network -> network-syscall-metadata-ready
device -> interrupt-table-ready
security -> security-not-production-boundary
```

Authority remains denied:

```text
runtime_entry_recovery_audit_observation_view_allowed=0
runtime_entry_recovery_closeout_observation_view_allowed=0
runtime_entry_recovery_plan_observation_view_allowed=0
runtime_entry_recovery_disposition_observation_view_allowed=0
runtime_entry_recovery_outcome_observation_view_allowed=0
runtime_entry_recovery_boundary_observation_view_allowed=0
runtime_entry_persistence_boundary_observation_view_allowed=0
runtime_entry_quiescent_return_observation_view_allowed=0
runtime_entry_idle_return_observation_view_allowed=0
runtime_entry_process_return_observation_view_allowed=0
runtime_entry_scheduler_return_observation_view_allowed=0
runtime_entry_post_resume_observation_view_allowed=0
runtime_entry_user_mode_resume_view_allowed=0
runtime_entry_syscall_exit_view_allowed=0
runtime_entry_syscall_return_view_allowed=0
runtime_entry_syscall_dispatch_view_allowed=0
runtime_entry_syscall_gate_view_allowed=0
runtime_entry_privilege_level_view_allowed=0
runtime_entry_address_space_view_allowed=0
runtime_entry_stack_view_allowed=0
runtime_entry_register_view_allowed=0
runtime_entry_frame_allowed=0
runtime_entry_admission_allowed=0
runtime_entry_allowed=0
persistence_boundary_observation_allowed=0
persistence_boundary_allowed=0
persistence_commit_allowed=0
recovery_boundary_observation_allowed=0
recovery_boundary_allowed=0
recovery_plan_allowed=0
recovery_plan_observation_allowed=0
recovery_disposition_allowed=0
recovery_disposition_observation_allowed=0
recovery_outcome_allowed=0
recovery_outcome_observation_allowed=0
recovery_audit_allowed=0
recovery_audit_observation_allowed=0
recovery_closeout_allowed=0
recovery_closeout_observation_allowed=0
quiescent_return_observation_allowed=0
quiescent_return_allowed=0
quiescent_state_read_allowed=0
scheduler_execution_allowed=0
scheduler_selection_allowed=0
scheduler_dispatch_allowed=0
scheduler_handoff_allowed=0
scheduler_activation_allowed=0
scheduler_run_entry_allowed=0
memory_allocation_allowed=0
process_spawn_allowed=0
syscall_dispatch_allowed=0
ipc_send_allowed=0
ipc_receive_allowed=0
ipc_queue_mutation_allowed=0
filesystem_lookup_allowed=0
filesystem_read_allowed=0
filesystem_write_allowed=0
namespace_mutation_allowed=0
device_open_allowed=0
device_read_allowed=0
device_write_allowed=0
driver_probe_allowed=0
driver_load_allowed=0
driver_bind_allowed=0
interrupt_allowed=0
interrupt_mask_allowed=0
interrupt_unmask_allowed=0
interrupt_dispatch_allowed=0
interrupt_ack_allowed=0
timer_tick_allowed=0
timer_arm_allowed=0
timer_disarm_allowed=0
scheduler_tick_allowed=0
run_queue_mutation_allowed=0
enqueue_allowed=0
dequeue_allowed=0
dispatch_allowed=0
context_switch_allowed=0
register_save_allowed=0
register_restore_allowed=0
stack_switch_allowed=0
address_space_switch_allowed=0
preemption_allowed=0
time_accounting_allowed=0
time_read_allowed=0
cpu_usage_write_allowed=0
quota_update_allowed=0
scheduler_credit_update_allowed=0
process_wake_allowed=0
persistence_allowed=0
recovery_authority_allowed=0
dma_allowed=0
hardware_effect_allowed=0
nucleus_boot_allowed=0
nucleus_runtime_entry_allowed=0
nucleus_scheduler_run_entry_allowed=0
nucleus_context_switch_allowed=0
nucleus_register_save_allowed=0
nucleus_register_restore_allowed=0
nucleus_host_effect_allowed=0
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

This is a summary/reporting slice only. It does not expand kernel authority,
enter runtime, perform a context switch, save or restore registers, or claim
product readiness.

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
default request targets runtime-entry-recovery-audit-observation-view-ready
summary reaches runtime-entry-recovery-audit-observation-view-ready
summary marks boot/scheduler/memory/process/filesystem as lifecycle-ready metadata
runtime recovery-audit-observation-view metadata is ready while runtime remains not entered
runtime entry recovery-audit observation view, recovery-closeout observation view, recovery-outcome observation view, recovery-disposition observation view, recovery-plan observation view, recovery-boundary observation view, persistence-boundary observation view, quiescent-return observation view, idle-return observation view, process-return observation view, scheduler-return observation view, post-resume observation view, user-mode-resume view, syscall-exit view, syscall-return view, syscall-dispatch view, syscall-gate view, privilege-level view, address-space view, stack view, register view, frame, admission, and runtime entry remain denied
nucleus-kernel coupling reports os-metadata-ready only with no-effect evidence
nucleus boot, runtime entry, scheduler run entry, context switch, register save, register restore, and host effect remain denied
scheduler execution remains denied
memory allocation remains denied
process spawn remains denied
syscall dispatch remains denied
IPC send, receive, and queue mutation remain denied
filesystem lookup, read, write, and namespace mutation remain denied
device open, read, write, driver probe, driver load, driver bind, interrupt mask, interrupt unmask, interrupt dispatch, interrupt ack, timer tick, timer arm, timer disarm, scheduler tick, scheduler selection, scheduler dispatch, scheduler handoff, scheduler activation, scheduler run-entry, run queue mutation, enqueue, dequeue, dispatch, context switch, register save, register restore, stack switch, address space switch, preemption, time accounting, time read, CPU usage write, quota update, scheduler credit update, process wake, DMA, and hardware effect remain denied
network and device authority remain denied
limited lifecycle summary reports incomplete readiness
external_effect_performed=0 remains true
```

## Non-claims

This slice does not make Latticra bootable, runnable as an operating system, product-ready, or authority-expanded.

## Next possible lane

A later slice may add recovery-audit-review observation metadata, virtual device binding metadata, scheduler-to-timer handoff metadata, or define a production-authority contract. Those should remain report-only unless a separate authority contract is introduced first.
