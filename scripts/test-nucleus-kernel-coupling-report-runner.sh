#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-nucleus-kernel-coupling-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

report_bin="$tmpdir/latticra-nucleus-kernel-coupling-report"
report_txt="$tmpdir/latticra-nucleus-kernel-coupling-report.txt"

cc $CFLAGS \
  -Iinclude \
  src/state_lattice.c \
  src/nucleus_preview.c \
  src/nucleus_task.c \
  src/nucleus_task_plan.c \
  src/lat_parser.c \
  src/runtime_boundary.c \
  src/system_bootstrap.c \
  src/kernel.c \
  src/kernel_subsystem_registry.c \
  src/kernel_scheduler.c \
  src/kernel_memory_map.c \
  src/kernel_process_table.c \
  src/kernel_syscall_table.c \
  src/kernel_ipc_table.c \
  src/kernel_vfs_namespace.c \
  src/kernel_device_registry.c \
  src/kernel_driver_catalog.c \
  src/kernel_interrupt_table.c \
  src/kernel_timer_source.c \
  src/kernel_scheduler_tick.c \
  src/kernel_run_queue.c \
  src/kernel_context_switch.c \
  src/kernel_time_accounting.c \
  src/kernel_preemption.c \
  src/kernel_scheduler_credit.c \
  src/kernel_scheduler_selection.c \
  src/kernel_scheduler_dispatch.c \
  src/kernel_scheduler_handoff.c \
  src/kernel_scheduler_activation.c \
  src/kernel_scheduler_run_entry.c \
  src/kernel_runtime_entry_admission.c \
  src/kernel_runtime_entry_frame.c \
  src/kernel_runtime_entry_register_view.c \
  src/kernel_runtime_entry_stack_view.c \
  src/kernel_runtime_entry_address_space_view.c \
  src/kernel_runtime_entry_privilege_level_view.c \
  src/kernel_runtime_entry_syscall_gate_view.c \
  src/kernel_runtime_entry_syscall_dispatch_view.c \
  src/kernel_runtime_entry_syscall_return_view.c \
  src/kernel_runtime_entry_syscall_exit_view.c \
  src/kernel_runtime_entry_user_mode_resume_view.c \
  src/kernel_runtime_entry_post_resume_observation_view.c \
  src/kernel_runtime_entry_scheduler_return_observation_view.c \
  src/kernel_runtime_entry_process_return_observation_view.c \
  src/kernel_runtime_entry_idle_return_observation_view.c \
  src/kernel_runtime_entry_quiescent_return_observation_view.c \
  src/kernel_runtime_entry_persistence_boundary_observation_view.c \
  src/kernel_runtime_entry_recovery_boundary_observation_view.c \
  src/kernel_runtime_entry_recovery_plan_observation_view.c \
  src/kernel_runtime_entry_recovery_disposition_observation_view.c \
  src/kernel_runtime_entry_recovery_outcome_observation_view.c \
  src/kernel_runtime_entry_recovery_closeout_observation_view.c \
  src/kernel_runtime_entry_recovery_audit_observation_view.c \
  src/kernel_runtime_entry_recovery_audit_review_observation_view.c \
  src/kernel_runtime_entry_recovery_audit_review_disposition_observation_view.c \
  src/kernel_runtime_entry_recovery_audit_review_disposition_review_observation_view.c \
  src/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view.c \
  src/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view.c \
  src/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view.c \
  src/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view.c \
  src/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view.c \
  src/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_archive_gate_observation_view.c \
  src/kernel_state.c \
  src/kernel_state_machine.c \
  src/kernel_lifecycle.c \
  src/nucleus_kernel_coupling.c \
  tools/nucleus_kernel_coupling_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"

grep -Fq 'LATTICRA NUCLEUS KERNEL COUPLING REPORT' "$report_txt"
grep -Fq 'classification=report-only-ready' "$report_txt"
grep -Fq 'reason=ok' "$report_txt"
grep -Fq 'readiness_status=nucleus-kernel-coupling-ready' "$report_txt"
grep -Fq 'os_readiness_status=os-metadata-ready' "$report_txt"
grep -Fq 'nucleus_plan_status=allow-no-effect-sequence' "$report_txt"
grep -Fq 'kernel_registry_status=registry-ready' "$report_txt"
grep -Fq 'kernel_status=initialized-report-only' "$report_txt"
grep -Fq 'kernel_lifecycle_status=lifecycle-complete' "$report_txt"
grep -Fq 'kernel_lifecycle_final_state=runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout-archive-gate-observation-view-ready' "$report_txt"
grep -Fq 'runtime_register_view_status=runtime-entry-register-view-seed-ready' "$report_txt"
grep -Fq 'runtime_entry_frame_status=runtime-entry-frame-seed-ready' "$report_txt"
grep -Fq 'scheduler_run_entry_status=scheduler-run-entry-seed-ready' "$report_txt"
grep -Fq 'runtime_process_return_observation_view_status=runtime-entry-process-return-observation-view-seed-ready' "$report_txt"
grep -Fq 'runtime_scheduler_return_observation_view_status=runtime-entry-scheduler-return-observation-view-seed-ready' "$report_txt"
grep -Fq 'runtime_post_resume_observation_view_status=runtime-entry-post-resume-observation-view-seed-ready' "$report_txt"
grep -Fq 'runtime_user_mode_resume_view_status=runtime-entry-user-mode-resume-view-seed-ready' "$report_txt"
grep -Fq 'runtime_idle_return_observation_view_status=runtime-entry-idle-return-observation-view-seed-ready' "$report_txt"
grep -Fq 'runtime_quiescent_return_observation_view_status=runtime-entry-quiescent-return-observation-view-seed-ready' "$report_txt"
grep -Fq 'runtime_persistence_boundary_observation_view_status=runtime-entry-persistence-boundary-observation-view-seed-ready' "$report_txt"
grep -Fq 'runtime_recovery_boundary_observation_view_status=runtime-entry-recovery-boundary-observation-view-seed-ready' "$report_txt"
grep -Fq 'runtime_recovery_plan_observation_view_status=runtime-entry-recovery-plan-observation-view-seed-ready' "$report_txt"
grep -Fq 'runtime_recovery_disposition_observation_view_status=runtime-entry-recovery-disposition-observation-view-seed-ready' "$report_txt"
grep -Fq 'runtime_recovery_outcome_observation_view_status=runtime-entry-recovery-outcome-observation-view-seed-ready' "$report_txt"
grep -Fq 'runtime_recovery_closeout_observation_view_status=runtime-entry-recovery-closeout-observation-view-seed-ready' "$report_txt"
grep -Fq 'runtime_recovery_audit_observation_view_status=runtime-entry-recovery-audit-observation-view-seed-ready' "$report_txt"
grep -Fq 'runtime_recovery_audit_review_observation_view_status=runtime-entry-recovery-audit-review-observation-view-seed-ready' "$report_txt"
grep -Fq 'runtime_recovery_audit_review_disposition_observation_view_status=runtime-entry-recovery-audit-review-disposition-observation-view-seed-ready' "$report_txt"
grep -Fq 'runtime_recovery_audit_review_disposition_review_observation_view_status=runtime-entry-recovery-audit-review-disposition-review-observation-view-seed-ready' "$report_txt"
grep -Fq 'runtime_recovery_audit_review_disposition_review_closeout_observation_view_status=runtime-entry-recovery-audit-review-disposition-review-closeout-observation-view-seed-ready' "$report_txt"
grep -Fq 'runtime_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_status=runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-observation-view-seed-ready' "$report_txt"
grep -Fq 'runtime_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_status=runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-observation-view-seed-ready' "$report_txt"
grep -Fq 'runtime_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_status=runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-observation-view-seed-ready' "$report_txt"
grep -Fq 'runtime_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_status=runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout-observation-view-seed-ready' "$report_txt"
grep -Fq 'runtime_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_archive_gate_observation_view_status=runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout-archive-gate-observation-view-seed-ready' "$report_txt"
grep -Fq 'task_count=1' "$report_txt"
grep -Fq 'accepted_task_count=1' "$report_txt"
grep -Fq 'blocked_task_count=0' "$report_txt"
grep -Fq 'subsystem_count=9' "$report_txt"
grep -Fq 'lifecycle_step_count=55' "$report_txt"
grep -Fq 'lifecycle_state_change_count=55' "$report_txt"
grep -Fq 'register_view_count=4' "$report_txt"
grep -Fq 'process_return_observation_view_count=4' "$report_txt"
grep -Fq 'scheduler_return_observation_view_count=4' "$report_txt"
grep -Fq 'post_resume_observation_view_count=4' "$report_txt"
grep -Fq 'user_mode_resume_view_count=4' "$report_txt"
grep -Fq 'idle_return_observation_view_count=4' "$report_txt"
grep -Fq 'quiescent_return_observation_view_count=4' "$report_txt"
grep -Fq 'persistence_boundary_observation_view_count=4' "$report_txt"
grep -Fq 'recovery_boundary_observation_view_count=4' "$report_txt"
grep -Fq 'recovery_plan_observation_view_count=4' "$report_txt"
grep -Fq 'recovery_disposition_observation_view_count=4' "$report_txt"
grep -Fq 'recovery_outcome_observation_view_count=4' "$report_txt"
grep -Fq 'recovery_closeout_observation_view_count=4' "$report_txt"
grep -Fq 'recovery_audit_observation_view_count=4' "$report_txt"
grep -Fq 'recovery_audit_review_observation_view_count=4' "$report_txt"
grep -Fq 'recovery_audit_review_disposition_observation_view_count=4' "$report_txt"
grep -Fq 'recovery_audit_review_disposition_review_observation_view_count=4' "$report_txt"
grep -Fq 'recovery_audit_review_disposition_review_closeout_observation_view_count=4' "$report_txt"
grep -Fq 'recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_count=4' "$report_txt"
grep -Fq 'recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_count=4' "$report_txt"
grep -Fq 'recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_count=4' "$report_txt"
grep -Fq 'recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_count=4' "$report_txt"
grep -Fq 'recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_archive_gate_observation_view_count=4' "$report_txt"
grep -Fq 'prerequisites_satisfied=1' "$report_txt"
grep -Fq 'no_effect_chain_ok=1' "$report_txt"
grep -Fq 'lifecycle_complete=1' "$report_txt"
grep -Fq 'report_only=1' "$report_txt"
grep -Fq 'execution_allowed=0' "$report_txt"
grep -Fq 'network_allowed=0' "$report_txt"
grep -Fq 'boot_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_allowed=0' "$report_txt"
grep -Fq 'scheduler_run_entry_allowed=0' "$report_txt"
grep -Fq 'context_switch_allowed=0' "$report_txt"
grep -Fq 'register_save_allowed=0' "$report_txt"
grep -Fq 'register_restore_allowed=0' "$report_txt"
grep -Fq 'runtime_process_return_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_scheduler_return_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_post_resume_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_idle_return_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_quiescent_return_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_persistence_boundary_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_recovery_boundary_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_recovery_plan_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_recovery_disposition_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_recovery_outcome_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_recovery_closeout_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_recovery_audit_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_recovery_audit_review_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_recovery_audit_review_disposition_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_recovery_audit_review_disposition_review_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_recovery_audit_review_disposition_review_closeout_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_archive_gate_observation_view_allowed=0' "$report_txt"
grep -Fq 'scheduler_return_observation_allowed=0' "$report_txt"
grep -Fq 'process_return_observation_allowed=0' "$report_txt"
grep -Fq 'process_return_allowed=0' "$report_txt"
grep -Fq 'idle_return_observation_allowed=0' "$report_txt"
grep -Fq 'idle_return_allowed=0' "$report_txt"
grep -Fq 'idle_state_read_allowed=0' "$report_txt"
grep -Fq 'quiescent_return_observation_allowed=0' "$report_txt"
grep -Fq 'quiescent_return_allowed=0' "$report_txt"
grep -Fq 'quiescent_state_read_allowed=0' "$report_txt"
grep -Fq 'persistence_boundary_observation_allowed=0' "$report_txt"
grep -Fq 'persistence_boundary_allowed=0' "$report_txt"
grep -Fq 'persistence_commit_allowed=0' "$report_txt"
grep -Fq 'recovery_boundary_observation_allowed=0' "$report_txt"
grep -Fq 'recovery_boundary_allowed=0' "$report_txt"
grep -Fq 'recovery_plan_allowed=0' "$report_txt"
grep -Fq 'recovery_plan_observation_allowed=0' "$report_txt"
grep -Fq 'recovery_disposition_allowed=0' "$report_txt"
grep -Fq 'recovery_disposition_observation_allowed=0' "$report_txt"
grep -Fq 'recovery_outcome_allowed=0' "$report_txt"
grep -Fq 'recovery_outcome_observation_allowed=0' "$report_txt"
grep -Fq 'recovery_closeout_allowed=0' "$report_txt"
grep -Fq 'recovery_closeout_observation_allowed=0' "$report_txt"
grep -Fq 'recovery_audit_allowed=0' "$report_txt"
grep -Fq 'recovery_audit_observation_allowed=0' "$report_txt"
grep -Fq 'recovery_audit_review_allowed=0' "$report_txt"
grep -Fq 'recovery_audit_review_observation_allowed=0' "$report_txt"
grep -Fq 'recovery_audit_review_disposition_allowed=0' "$report_txt"
grep -Fq 'recovery_audit_review_disposition_observation_allowed=0' "$report_txt"
grep -Fq 'recovery_audit_review_disposition_review_allowed=0' "$report_txt"
grep -Fq 'recovery_audit_review_disposition_review_observation_allowed=0' "$report_txt"
grep -Fq 'recovery_audit_review_disposition_review_closeout_allowed=0' "$report_txt"
grep -Fq 'recovery_audit_review_disposition_review_closeout_observation_allowed=0' "$report_txt"
grep -Fq 'recovery_audit_review_disposition_review_closeout_archive_gate_allowed=0' "$report_txt"
grep -Fq 'recovery_audit_review_disposition_review_closeout_archive_gate_observation_allowed=0' "$report_txt"
grep -Fq 'recovery_audit_review_disposition_review_closeout_archive_gate_review_allowed=0' "$report_txt"
grep -Fq 'recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_allowed=0' "$report_txt"
grep -Fq 'recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_allowed=0' "$report_txt"
grep -Fq 'recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_allowed=0' "$report_txt"
grep -Fq 'recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_allowed=0' "$report_txt"
grep -Fq 'recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_allowed=0' "$report_txt"
grep -Fq 'recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_archive_gate_allowed=0' "$report_txt"
grep -Fq 'recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_archive_gate_observation_allowed=0' "$report_txt"
grep -Fq 'process_state_read_allowed=0' "$report_txt"
grep -Fq 'scheduler_execution_allowed=0' "$report_txt"
grep -Fq 'scheduler_dispatch_allowed=0' "$report_txt"
grep -Fq 'run_queue_mutation_allowed=0' "$report_txt"
grep -Fq 'process_wake_allowed=0' "$report_txt"
grep -Fq 'host_effect_allowed=0' "$report_txt"
grep -Fq 'evidence_level=58' "$report_txt"

printf 'nucleus_kernel_coupling_report_runner: ok\n'
