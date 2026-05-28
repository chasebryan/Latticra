#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-kernel-lifecycle-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

report_bin="$tmpdir/latticra-kernel-lifecycle-report"
report_txt="$tmpdir/latticra-kernel-lifecycle-report.txt"

cc $CFLAGS \
  -Iinclude \
  src/state_lattice.c \
  src/nucleus_preview.c \
  src/nucleus_task.c \
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
  src/kernel_state.c \
  src/kernel_state_machine.c \
  src/kernel_lifecycle.c \
  tools/kernel_lifecycle_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"

grep -Fq 'LATTICRA KERNEL LIFECYCLE REPORT' "$report_txt"
grep -Fq 'lifecycle_status=lifecycle-complete' "$report_txt"
grep -Fq 'policy_status=gate-allowed' "$report_txt"
grep -Fq 'final_state=runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-observation-view-ready' "$report_txt"
grep -Fq 'step_count=52' "$report_txt"
grep -Fq 'state_change_count=52' "$report_txt"
grep -Fq 'lifecycle_complete=1' "$report_txt"
grep -Fq 'external_effect_performed=0' "$report_txt"
grep -Fq 'network_allowed=0' "$report_txt"
grep -Fq 'machine_network_allowed=0' "$report_txt"
grep -Fq 'machine_log_count=52' "$report_txt"
grep -Fq 'evidence_level=10' "$report_txt"
grep -Fq 'log[0].from=created' "$report_txt"
grep -Fq 'log[0].to=initialized' "$report_txt"
grep -Fq 'log[0].status=machine-mutated' "$report_txt"
grep -Fq 'log[4].from=memory-map-ready' "$report_txt"
grep -Fq 'log[4].to=process-table-ready' "$report_txt"
grep -Fq 'log[5].from=process-table-ready' "$report_txt"
grep -Fq 'log[5].to=syscall-table-ready' "$report_txt"
grep -Fq 'log[5].network_allowed=0' "$report_txt"
grep -Fq 'log[6].from=syscall-table-ready' "$report_txt"
grep -Fq 'log[6].to=ipc-table-ready' "$report_txt"
grep -Fq 'log[6].network_allowed=0' "$report_txt"
grep -Fq 'log[7].from=ipc-table-ready' "$report_txt"
grep -Fq 'log[7].to=vfs-namespace-ready' "$report_txt"
grep -Fq 'log[7].state_change_performed=1' "$report_txt"
grep -Fq 'log[7].external_effect_performed=0' "$report_txt"
grep -Fq 'log[8].from=vfs-namespace-ready' "$report_txt"
grep -Fq 'log[8].to=device-registry-ready' "$report_txt"
grep -Fq 'log[8].state_change_performed=1' "$report_txt"
grep -Fq 'log[8].external_effect_performed=0' "$report_txt"
grep -Fq 'log[9].from=device-registry-ready' "$report_txt"
grep -Fq 'log[9].to=driver-catalog-ready' "$report_txt"
grep -Fq 'log[9].state_change_performed=1' "$report_txt"
grep -Fq 'log[9].external_effect_performed=0' "$report_txt"
grep -Fq 'log[10].from=driver-catalog-ready' "$report_txt"
grep -Fq 'log[10].to=interrupt-table-ready' "$report_txt"
grep -Fq 'log[10].state_change_performed=1' "$report_txt"
grep -Fq 'log[10].external_effect_performed=0' "$report_txt"
grep -Fq 'log[11].from=interrupt-table-ready' "$report_txt"
grep -Fq 'log[11].to=timer-source-ready' "$report_txt"
grep -Fq 'log[11].state_change_performed=1' "$report_txt"
grep -Fq 'log[11].external_effect_performed=0' "$report_txt"
grep -Fq 'log[12].from=timer-source-ready' "$report_txt"
grep -Fq 'log[12].to=scheduler-tick-ready' "$report_txt"
grep -Fq 'log[12].state_change_performed=1' "$report_txt"
grep -Fq 'log[12].external_effect_performed=0' "$report_txt"
grep -Fq 'log[13].from=scheduler-tick-ready' "$report_txt"
grep -Fq 'log[13].to=run-queue-ready' "$report_txt"
grep -Fq 'log[13].state_change_performed=1' "$report_txt"
grep -Fq 'log[13].external_effect_performed=0' "$report_txt"
grep -Fq 'log[14].from=run-queue-ready' "$report_txt"
grep -Fq 'log[14].to=context-switch-ready' "$report_txt"
grep -Fq 'log[14].state_change_performed=1' "$report_txt"
grep -Fq 'log[14].external_effect_performed=0' "$report_txt"
grep -Fq 'log[15].from=context-switch-ready' "$report_txt"
grep -Fq 'log[15].to=time-accounting-ready' "$report_txt"
grep -Fq 'log[15].state_change_performed=1' "$report_txt"
grep -Fq 'log[15].external_effect_performed=0' "$report_txt"
grep -Fq 'log[16].from=time-accounting-ready' "$report_txt"
grep -Fq 'log[16].to=preemption-ready' "$report_txt"
grep -Fq 'log[16].state_change_performed=1' "$report_txt"
grep -Fq 'log[16].external_effect_performed=0' "$report_txt"
grep -Fq 'log[17].from=preemption-ready' "$report_txt"
grep -Fq 'log[17].to=scheduler-credit-ready' "$report_txt"
grep -Fq 'log[17].state_change_performed=1' "$report_txt"
grep -Fq 'log[17].external_effect_performed=0' "$report_txt"
grep -Fq 'log[18].from=scheduler-credit-ready' "$report_txt"
grep -Fq 'log[18].to=scheduler-selection-ready' "$report_txt"
grep -Fq 'log[18].state_change_performed=1' "$report_txt"
grep -Fq 'log[18].external_effect_performed=0' "$report_txt"
grep -Fq 'log[19].from=scheduler-selection-ready' "$report_txt"
grep -Fq 'log[19].to=scheduler-dispatch-ready' "$report_txt"
grep -Fq 'log[19].state_change_performed=1' "$report_txt"
grep -Fq 'log[19].external_effect_performed=0' "$report_txt"
grep -Fq 'log[20].from=scheduler-dispatch-ready' "$report_txt"
grep -Fq 'log[20].to=scheduler-handoff-ready' "$report_txt"
grep -Fq 'log[20].state_change_performed=1' "$report_txt"
grep -Fq 'log[20].external_effect_performed=0' "$report_txt"
grep -Fq 'log[21].from=scheduler-handoff-ready' "$report_txt"
grep -Fq 'log[21].to=scheduler-activation-ready' "$report_txt"
grep -Fq 'log[21].state_change_performed=1' "$report_txt"
grep -Fq 'log[21].external_effect_performed=0' "$report_txt"
grep -Fq 'log[22].from=scheduler-activation-ready' "$report_txt"
grep -Fq 'log[22].to=scheduler-run-entry-ready' "$report_txt"
grep -Fq 'log[22].state_change_performed=1' "$report_txt"
grep -Fq 'log[22].external_effect_performed=0' "$report_txt"
grep -Fq 'log[23].from=scheduler-run-entry-ready' "$report_txt"
grep -Fq 'log[23].to=runtime-entry-admission-ready' "$report_txt"
grep -Fq 'log[23].state_change_performed=1' "$report_txt"
grep -Fq 'log[23].external_effect_performed=0' "$report_txt"
grep -Fq 'log[24].from=runtime-entry-admission-ready' "$report_txt"
grep -Fq 'log[24].to=runtime-entry-frame-ready' "$report_txt"
grep -Fq 'log[24].state_change_performed=1' "$report_txt"
grep -Fq 'log[24].external_effect_performed=0' "$report_txt"
grep -Fq 'log[25].from=runtime-entry-frame-ready' "$report_txt"
grep -Fq 'log[25].to=runtime-entry-register-view-ready' "$report_txt"
grep -Fq 'log[25].state_change_performed=1' "$report_txt"
grep -Fq 'log[25].external_effect_performed=0' "$report_txt"
grep -Fq 'log[26].from=runtime-entry-register-view-ready' "$report_txt"
grep -Fq 'log[26].to=runtime-entry-stack-view-ready' "$report_txt"
grep -Fq 'log[26].state_change_performed=1' "$report_txt"
grep -Fq 'log[26].external_effect_performed=0' "$report_txt"
grep -Fq 'log[27].from=runtime-entry-stack-view-ready' "$report_txt"
grep -Fq 'log[27].to=runtime-entry-address-space-view-ready' "$report_txt"
grep -Fq 'log[27].state_change_performed=1' "$report_txt"
grep -Fq 'log[27].external_effect_performed=0' "$report_txt"
grep -Fq 'log[28].from=runtime-entry-address-space-view-ready' "$report_txt"
grep -Fq 'log[28].to=runtime-entry-privilege-level-view-ready' "$report_txt"
grep -Fq 'log[28].state_change_performed=1' "$report_txt"
grep -Fq 'log[28].external_effect_performed=0' "$report_txt"
grep -Fq 'log[29].from=runtime-entry-privilege-level-view-ready' "$report_txt"
grep -Fq 'log[29].to=runtime-entry-syscall-gate-view-ready' "$report_txt"
grep -Fq 'log[29].state_change_performed=1' "$report_txt"
grep -Fq 'log[29].external_effect_performed=0' "$report_txt"
grep -Fq 'log[30].from=runtime-entry-syscall-gate-view-ready' "$report_txt"
grep -Fq 'log[30].to=runtime-entry-syscall-dispatch-view-ready' "$report_txt"
grep -Fq 'log[30].state_change_performed=1' "$report_txt"
grep -Fq 'log[30].external_effect_performed=0' "$report_txt"
grep -Fq 'log[31].from=runtime-entry-syscall-dispatch-view-ready' "$report_txt"
grep -Fq 'log[31].to=runtime-entry-syscall-return-view-ready' "$report_txt"
grep -Fq 'log[31].state_change_performed=1' "$report_txt"
grep -Fq 'log[31].external_effect_performed=0' "$report_txt"
grep -Fq 'log[32].from=runtime-entry-syscall-return-view-ready' "$report_txt"
grep -Fq 'log[32].to=runtime-entry-syscall-exit-view-ready' "$report_txt"
grep -Fq 'log[32].state_change_performed=1' "$report_txt"
grep -Fq 'log[32].external_effect_performed=0' "$report_txt"
grep -Fq 'log[33].from=runtime-entry-syscall-exit-view-ready' "$report_txt"
grep -Fq 'log[33].to=runtime-entry-user-mode-resume-view-ready' "$report_txt"
grep -Fq 'log[33].state_change_performed=1' "$report_txt"
grep -Fq 'log[33].external_effect_performed=0' "$report_txt"
grep -Fq 'log[34].from=runtime-entry-user-mode-resume-view-ready' "$report_txt"
grep -Fq 'log[34].to=runtime-entry-post-resume-observation-view-ready' "$report_txt"
grep -Fq 'log[34].state_change_performed=1' "$report_txt"
grep -Fq 'log[34].external_effect_performed=0' "$report_txt"
grep -Fq 'log[35].from=runtime-entry-post-resume-observation-view-ready' "$report_txt"
grep -Fq 'log[35].to=runtime-entry-scheduler-return-observation-view-ready' "$report_txt"
grep -Fq 'log[35].state_change_performed=1' "$report_txt"
grep -Fq 'log[35].external_effect_performed=0' "$report_txt"
grep -Fq 'log[36].from=runtime-entry-scheduler-return-observation-view-ready' "$report_txt"
grep -Fq 'log[36].to=runtime-entry-process-return-observation-view-ready' "$report_txt"
grep -Fq 'log[36].state_change_performed=1' "$report_txt"
grep -Fq 'log[36].external_effect_performed=0' "$report_txt"
grep -Fq 'log[37].from=runtime-entry-process-return-observation-view-ready' "$report_txt"
grep -Fq 'log[37].to=runtime-entry-idle-return-observation-view-ready' "$report_txt"
grep -Fq 'log[37].state_change_performed=1' "$report_txt"
grep -Fq 'log[37].external_effect_performed=0' "$report_txt"
grep -Fq 'log[38].from=runtime-entry-idle-return-observation-view-ready' "$report_txt"
grep -Fq 'log[38].to=runtime-entry-quiescent-return-observation-view-ready' "$report_txt"
grep -Fq 'log[38].state_change_performed=1' "$report_txt"
grep -Fq 'log[38].external_effect_performed=0' "$report_txt"
grep -Fq 'log[39].from=runtime-entry-quiescent-return-observation-view-ready' "$report_txt"
grep -Fq 'log[39].to=runtime-entry-persistence-boundary-observation-view-ready' "$report_txt"
grep -Fq 'log[39].state_change_performed=1' "$report_txt"
grep -Fq 'log[39].external_effect_performed=0' "$report_txt"
grep -Fq 'log[40].from=runtime-entry-persistence-boundary-observation-view-ready' "$report_txt"
grep -Fq 'log[40].to=runtime-entry-recovery-boundary-observation-view-ready' "$report_txt"
grep -Fq 'log[40].state_change_performed=1' "$report_txt"
grep -Fq 'log[40].external_effect_performed=0' "$report_txt"
grep -Fq 'log[41].from=runtime-entry-recovery-boundary-observation-view-ready' "$report_txt"
grep -Fq 'log[41].to=runtime-entry-recovery-plan-observation-view-ready' "$report_txt"
grep -Fq 'log[41].state_change_performed=1' "$report_txt"
grep -Fq 'log[41].external_effect_performed=0' "$report_txt"
grep -Fq 'log[42].from=runtime-entry-recovery-plan-observation-view-ready' "$report_txt"
grep -Fq 'log[42].to=runtime-entry-recovery-disposition-observation-view-ready' "$report_txt"
grep -Fq 'log[42].state_change_performed=1' "$report_txt"
grep -Fq 'log[42].external_effect_performed=0' "$report_txt"
grep -Fq 'log[43].from=runtime-entry-recovery-disposition-observation-view-ready' "$report_txt"
grep -Fq 'log[43].to=runtime-entry-recovery-outcome-observation-view-ready' "$report_txt"
grep -Fq 'log[43].state_change_performed=1' "$report_txt"
grep -Fq 'log[44].from=runtime-entry-recovery-outcome-observation-view-ready' "$report_txt"
grep -Fq 'log[44].to=runtime-entry-recovery-closeout-observation-view-ready' "$report_txt"
grep -Fq 'log[44].state_change_performed=1' "$report_txt"
grep -Fq 'log[44].external_effect_performed=0' "$report_txt"
grep -Fq 'log[45].from=runtime-entry-recovery-closeout-observation-view-ready' "$report_txt"
grep -Fq 'log[45].to=runtime-entry-recovery-audit-observation-view-ready' "$report_txt"
grep -Fq 'log[45].state_change_performed=1' "$report_txt"
grep -Fq 'log[45].external_effect_performed=0' "$report_txt"
grep -Fq 'log[46].from=runtime-entry-recovery-audit-observation-view-ready' "$report_txt"
grep -Fq 'log[46].to=runtime-entry-recovery-audit-review-observation-view-ready' "$report_txt"
grep -Fq 'log[46].state_change_performed=1' "$report_txt"
grep -Fq 'log[46].external_effect_performed=0' "$report_txt"
grep -Fq 'log[47].from=runtime-entry-recovery-audit-review-observation-view-ready' "$report_txt"
grep -Fq 'log[47].to=runtime-entry-recovery-audit-review-disposition-observation-view-ready' "$report_txt"
grep -Fq 'log[47].state_change_performed=1' "$report_txt"
grep -Fq 'log[47].external_effect_performed=0' "$report_txt"
grep -Fq 'log[48].from=runtime-entry-recovery-audit-review-disposition-observation-view-ready' "$report_txt"
grep -Fq 'log[48].to=runtime-entry-recovery-audit-review-disposition-review-observation-view-ready' "$report_txt"
grep -Fq 'log[48].state_change_performed=1' "$report_txt"
grep -Fq 'log[48].external_effect_performed=0' "$report_txt"
grep -Fq 'log[49].from=runtime-entry-recovery-audit-review-disposition-review-observation-view-ready' "$report_txt"
grep -Fq 'log[49].to=runtime-entry-recovery-audit-review-disposition-review-closeout-observation-view-ready' "$report_txt"
grep -Fq 'log[49].state_change_performed=1' "$report_txt"
grep -Fq 'log[49].external_effect_performed=0' "$report_txt"
grep -Fq 'log[50].from=runtime-entry-recovery-audit-review-disposition-review-closeout-observation-view-ready' "$report_txt"
grep -Fq 'log[50].to=runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-observation-view-ready' "$report_txt"
grep -Fq 'log[50].state_change_performed=1' "$report_txt"
grep -Fq 'log[50].external_effect_performed=0' "$report_txt"
grep -Fq 'log[51].from=runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-observation-view-ready' "$report_txt"
grep -Fq 'log[51].to=runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-observation-view-ready' "$report_txt"
grep -Fq 'log[51].state_change_performed=1' "$report_txt"
grep -Fq 'log[51].external_effect_performed=0' "$report_txt"

printf 'kernel_lifecycle_report_runner: ok\n'
