# Nucleus Kernel Coupling Readiness

Status: controlled nucleus-first OS-readiness metadata gate
Scope: report-only coupling from the nucleus task plan to kernel subsystem, kernel lifecycle, runtime-entry register-view, scheduler-return observation, post-resume observation, user-mode-resume, process-return observation, idle-return observation, quiescent-return observation, persistence-boundary observation, recovery-boundary observation, recovery-plan observation, recovery-disposition observation, recovery-outcome observation, recovery-closeout observation, and recovery-audit observation evidence.

This slice makes the nucleus the first checkpoint for kernel coupling. It
accepts only an already-allowed no-effect nucleus task plan, a no-effect kernel
subsystem registry, a complete no-effect kernel lifecycle, and a no-effect
runtime observation chain from register-view metadata through recovery-audit
observation metadata. The kernel lifecycle must complete to the recovery-audit
observation endpoint. When all required surfaces are present and clean, it emits
`os_readiness_status=os-metadata-ready`.

The API supports both reviewed-evidence intake and a default evaluator. The
default evaluator assembles the standard no-effect nucleus task plan, kernel
subsystem registry, kernel lifecycle, and runtime recovery-boundary observation
chain with recovery-plan, recovery-disposition, recovery-outcome,
recovery-closeout, and recovery-audit observation before running the same
coupling gate.

This is not bootable OS readiness. It does not boot, enter runtime, dispatch
scheduler work, mutate a run queue, save registers, restore registers, switch
stacks, switch address spaces, write files, open the network, touch devices, or
grant host authority.

## Files

```text
include/latticra/nucleus_kernel_coupling.h
src/nucleus_kernel_coupling.c
tests/nucleus_kernel_coupling.c
tools/nucleus_kernel_coupling_report.c
scripts/test-nucleus-kernel-coupling.sh
scripts/test-nucleus-kernel-coupling-report-runner.sh
docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
```

## Entrypoints

```text
latticra_nucleus_kernel_coupling_default_nucleus_plan
latticra_nucleus_kernel_coupling_evaluate
latticra_nucleus_kernel_coupling_evaluate_default
latticra_nucleus_kernel_coupling_report
```

## Ready Evidence

The ready path requires:

```text
nucleus_plan_status=allow-no-effect-sequence
kernel_registry_status=registry-ready
kernel_status=initialized-report-only
kernel_lifecycle_status=lifecycle-complete
kernel_lifecycle_final_state=runtime-entry-recovery-audit-observation-view-ready
runtime_register_view_status=runtime-entry-register-view-seed-ready
runtime_entry_frame_status=runtime-entry-frame-seed-ready
scheduler_run_entry_status=scheduler-run-entry-seed-ready
runtime_process_return_observation_view_status=runtime-entry-process-return-observation-view-seed-ready
runtime_scheduler_return_observation_view_status=runtime-entry-scheduler-return-observation-view-seed-ready
runtime_post_resume_observation_view_status=runtime-entry-post-resume-observation-view-seed-ready
runtime_user_mode_resume_view_status=runtime-entry-user-mode-resume-view-seed-ready
runtime_idle_return_observation_view_status=runtime-entry-idle-return-observation-view-seed-ready
runtime_quiescent_return_observation_view_status=runtime-entry-quiescent-return-observation-view-seed-ready
runtime_persistence_boundary_observation_view_status=runtime-entry-persistence-boundary-observation-view-seed-ready
runtime_recovery_boundary_observation_view_status=runtime-entry-recovery-boundary-observation-view-seed-ready
runtime_recovery_plan_observation_view_status=runtime-entry-recovery-plan-observation-view-seed-ready
runtime_recovery_disposition_observation_view_status=runtime-entry-recovery-disposition-observation-view-seed-ready
runtime_recovery_outcome_observation_view_status=runtime-entry-recovery-outcome-observation-view-seed-ready
runtime_recovery_closeout_observation_view_status=runtime-entry-recovery-closeout-observation-view-seed-ready
runtime_recovery_audit_observation_view_status=runtime-entry-recovery-audit-observation-view-seed-ready
task_count=1
accepted_task_count=1
blocked_task_count=0
subsystem_count=9
lifecycle_step_count=46
lifecycle_state_change_count=46
register_view_count=4
process_return_observation_view_count=4
scheduler_return_observation_view_count=4
post_resume_observation_view_count=4
user_mode_resume_view_count=4
idle_return_observation_view_count=4
quiescent_return_observation_view_count=4
persistence_boundary_observation_view_count=4
recovery_boundary_observation_view_count=4
recovery_plan_observation_view_count=4
recovery_disposition_observation_view_count=4
recovery_outcome_observation_view_count=4
recovery_closeout_observation_view_count=4
recovery_audit_observation_view_count=4
prerequisites_satisfied=1
no_effect_chain_ok=1
lifecycle_complete=1
evidence_level=49
```

The ready report also keeps all OS-effect flags denied:

```text
report_only=1
execution_allowed=0
mutation_allowed=0
network_allowed=0
server_allowed=0
recovery_allowed=0
hardware_allowed=0
boot_allowed=0
runtime_entry_allowed=0
scheduler_run_entry_allowed=0
context_switch_allowed=0
register_save_allowed=0
register_restore_allowed=0
runtime_process_return_observation_view_allowed=0
runtime_scheduler_return_observation_view_allowed=0
runtime_post_resume_observation_view_allowed=0
runtime_idle_return_observation_view_allowed=0
runtime_quiescent_return_observation_view_allowed=0
runtime_persistence_boundary_observation_view_allowed=0
runtime_recovery_boundary_observation_view_allowed=0
runtime_recovery_plan_observation_view_allowed=0
runtime_recovery_disposition_observation_view_allowed=0
runtime_recovery_outcome_observation_view_allowed=0
runtime_recovery_closeout_observation_view_allowed=0
runtime_recovery_audit_observation_view_allowed=0
scheduler_return_observation_allowed=0
process_return_observation_allowed=0
process_return_allowed=0
idle_return_observation_allowed=0
idle_return_allowed=0
idle_state_read_allowed=0
quiescent_return_observation_allowed=0
quiescent_return_allowed=0
quiescent_state_read_allowed=0
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
recovery_closeout_allowed=0
recovery_closeout_observation_allowed=0
recovery_audit_allowed=0
recovery_audit_observation_allowed=0
process_state_read_allowed=0
scheduler_execution_allowed=0
scheduler_dispatch_allowed=0
run_queue_mutation_allowed=0
process_wake_allowed=0
persistence_allowed=0
recovery_authority_allowed=0
host_effect_allowed=0
```

## Blocked Evidence

The gate blocks when any prerequisite is missing or when any prerequisite stops
being no-effect:

```text
reason=nucleus-plan-missing
reason=nucleus-plan-blocked
reason=kernel-registry-missing
reason=kernel-registry-blocked
reason=kernel-lifecycle-missing
reason=kernel-lifecycle-blocked
reason=runtime-register-view-missing
reason=runtime-register-view-blocked
reason=runtime-process-return-observation-view-missing
reason=runtime-process-return-observation-view-blocked
reason=runtime-idle-return-observation-view-missing
reason=runtime-idle-return-observation-view-blocked
reason=runtime-quiescent-return-observation-view-missing
reason=runtime-quiescent-return-observation-view-blocked
reason=runtime-persistence-boundary-observation-view-missing
reason=runtime-persistence-boundary-observation-view-blocked
reason=runtime-recovery-boundary-observation-view-missing
reason=runtime-recovery-boundary-observation-view-blocked
reason=runtime-recovery-plan-observation-view-missing
reason=runtime-recovery-plan-observation-view-blocked
reason=runtime-recovery-disposition-observation-view-missing
reason=runtime-recovery-disposition-observation-view-blocked
reason=runtime-recovery-outcome-observation-view-missing
reason=runtime-recovery-outcome-observation-view-blocked
reason=runtime-recovery-closeout-observation-view-missing
reason=runtime-recovery-closeout-observation-view-blocked
reason=runtime-recovery-audit-observation-view-missing
reason=runtime-recovery-audit-observation-view-blocked
```

The blocked path remains report-only and does not grant the denied authority.

## Validation

```text
sh scripts/test-nucleus-kernel-coupling.sh
sh scripts/test-nucleus-kernel-coupling-report-runner.sh
```
