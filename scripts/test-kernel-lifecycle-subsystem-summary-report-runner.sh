#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-kernel-lifecycle-subsystem-summary-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

report_bin="$tmpdir/latticra-kernel-lifecycle-subsystem-summary-report"
report_txt="$tmpdir/latticra-kernel-lifecycle-subsystem-summary-report.txt"

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
  src/nucleus_kernel_coupling.c \
  src/kernel_state.c \
  src/kernel_state_machine.c \
  src/kernel_lifecycle.c \
  src/kernel_lifecycle_subsystem_summary.c \
  tools/kernel_lifecycle_subsystem_summary_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"

grep -Fq 'LATTICRA KERNEL LIFECYCLE SUBSYSTEM SUMMARY REPORT' "$report_txt"
grep -Fq 'summary_status=summary-ready' "$report_txt"
grep -Fq 'final_state=runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout-observation-view-ready' "$report_txt"
grep -Fq 'lifecycle_status=lifecycle-complete' "$report_txt"
grep -Fq 'registry_status=registry-ready' "$report_txt"
grep -Fq 'lifecycle_complete=1' "$report_txt"
grep -Fq 'lifecycle_step_count=54' "$report_txt"
grep -Fq 'lifecycle_state_change_count=54' "$report_txt"
grep -Fq 'lifecycle_state_mutated=1' "$report_txt"
grep -Fq 'external_effect_performed=0' "$report_txt"
grep -Fq 'network_allowed=0' "$report_txt"
grep -Fq 'lifecycle_network_allowed=0' "$report_txt"
grep -Fq 'machine_network_allowed=0' "$report_txt"
grep -Fq 'registry_no_effect=1' "$report_txt"
grep -Fq 'nucleus_coupling_status=nucleus-kernel-coupling-ready' "$report_txt"
grep -Fq 'os_readiness_status=os-metadata-ready' "$report_txt"
grep -Fq 'nucleus_coupling_ready=1' "$report_txt"
grep -Fq 'nucleus_no_effect_chain_ok=1' "$report_txt"
grep -Fq 'nucleus_boot_allowed=0' "$report_txt"
grep -Fq 'nucleus_runtime_entry_allowed=0' "$report_txt"
grep -Fq 'nucleus_scheduler_run_entry_allowed=0' "$report_txt"
grep -Fq 'nucleus_context_switch_allowed=0' "$report_txt"
grep -Fq 'nucleus_register_save_allowed=0' "$report_txt"
grep -Fq 'nucleus_register_restore_allowed=0' "$report_txt"
grep -Fq 'nucleus_host_effect_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_recovery_audit_review_disposition_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_recovery_audit_review_disposition_review_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_recovery_audit_review_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_recovery_audit_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_recovery_closeout_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_recovery_outcome_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_recovery_disposition_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_recovery_plan_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_recovery_boundary_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_persistence_boundary_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_quiescent_return_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_idle_return_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_process_return_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_scheduler_return_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_post_resume_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_user_mode_resume_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_syscall_exit_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_syscall_return_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_syscall_dispatch_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_syscall_gate_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_privilege_level_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_address_space_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_stack_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_register_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_frame_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_admission_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_allowed=0' "$report_txt"
grep -Fq 'recovery_boundary_observation_allowed=0' "$report_txt"
grep -Fq 'recovery_boundary_allowed=0' "$report_txt"
grep -Fq 'recovery_plan_allowed=0' "$report_txt"
grep -Fq 'recovery_plan_observation_allowed=0' "$report_txt"
grep -Fq 'recovery_disposition_allowed=0' "$report_txt"
grep -Fq 'recovery_disposition_observation_allowed=0' "$report_txt"
grep -Fq 'recovery_outcome_allowed=0' "$report_txt"
grep -Fq 'recovery_outcome_observation_allowed=0' "$report_txt"
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
grep -Fq 'recovery_audit_review_allowed=0' "$report_txt"
grep -Fq 'recovery_audit_review_observation_allowed=0' "$report_txt"
grep -Fq 'recovery_audit_allowed=0' "$report_txt"
grep -Fq 'recovery_audit_observation_allowed=0' "$report_txt"
grep -Fq 'recovery_closeout_allowed=0' "$report_txt"
grep -Fq 'recovery_closeout_observation_allowed=0' "$report_txt"
grep -Fq 'persistence_boundary_observation_allowed=0' "$report_txt"
grep -Fq 'persistence_boundary_allowed=0' "$report_txt"
grep -Fq 'persistence_commit_allowed=0' "$report_txt"
grep -Fq 'scheduler_execution_allowed=0' "$report_txt"
grep -Fq 'scheduler_selection_allowed=0' "$report_txt"
grep -Fq 'scheduler_dispatch_allowed=0' "$report_txt"
grep -Fq 'scheduler_handoff_allowed=0' "$report_txt"
grep -Fq 'scheduler_activation_allowed=0' "$report_txt"
grep -Fq 'scheduler_run_entry_allowed=0' "$report_txt"
grep -Fq 'memory_allocation_allowed=0' "$report_txt"
grep -Fq 'process_spawn_allowed=0' "$report_txt"
grep -Fq 'syscall_dispatch_allowed=0' "$report_txt"
grep -Fq 'ipc_send_allowed=0' "$report_txt"
grep -Fq 'ipc_receive_allowed=0' "$report_txt"
grep -Fq 'ipc_queue_mutation_allowed=0' "$report_txt"
grep -Fq 'filesystem_lookup_allowed=0' "$report_txt"
grep -Fq 'filesystem_read_allowed=0' "$report_txt"
grep -Fq 'filesystem_write_allowed=0' "$report_txt"
grep -Fq 'namespace_mutation_allowed=0' "$report_txt"
grep -Fq 'device_open_allowed=0' "$report_txt"
grep -Fq 'device_read_allowed=0' "$report_txt"
grep -Fq 'device_write_allowed=0' "$report_txt"
grep -Fq 'driver_probe_allowed=0' "$report_txt"
grep -Fq 'driver_load_allowed=0' "$report_txt"
grep -Fq 'driver_bind_allowed=0' "$report_txt"
grep -Fq 'interrupt_allowed=0' "$report_txt"
grep -Fq 'interrupt_mask_allowed=0' "$report_txt"
grep -Fq 'interrupt_unmask_allowed=0' "$report_txt"
grep -Fq 'interrupt_dispatch_allowed=0' "$report_txt"
grep -Fq 'interrupt_ack_allowed=0' "$report_txt"
grep -Fq 'timer_tick_allowed=0' "$report_txt"
grep -Fq 'timer_arm_allowed=0' "$report_txt"
grep -Fq 'timer_disarm_allowed=0' "$report_txt"
grep -Fq 'scheduler_tick_allowed=0' "$report_txt"
grep -Fq 'run_queue_mutation_allowed=0' "$report_txt"
grep -Fq 'enqueue_allowed=0' "$report_txt"
grep -Fq 'dequeue_allowed=0' "$report_txt"
grep -Fq 'dispatch_allowed=0' "$report_txt"
grep -Fq 'context_switch_allowed=0' "$report_txt"
grep -Fq 'register_save_allowed=0' "$report_txt"
grep -Fq 'register_restore_allowed=0' "$report_txt"
grep -Fq 'stack_switch_allowed=0' "$report_txt"
grep -Fq 'address_space_switch_allowed=0' "$report_txt"
grep -Fq 'preemption_allowed=0' "$report_txt"
grep -Fq 'time_accounting_allowed=0' "$report_txt"
grep -Fq 'time_read_allowed=0' "$report_txt"
grep -Fq 'cpu_usage_write_allowed=0' "$report_txt"
grep -Fq 'quota_update_allowed=0' "$report_txt"
grep -Fq 'scheduler_credit_update_allowed=0' "$report_txt"
grep -Fq 'process_wake_allowed=0' "$report_txt"
grep -Fq 'dma_allowed=0' "$report_txt"
grep -Fq 'hardware_effect_allowed=0' "$report_txt"
grep -Fq 'no_external_effect_chain=1' "$report_txt"
grep -Fq 'evidence_level=57' "$report_txt"
grep -Fq 'entry_count=9' "$report_txt"
grep -Fq 'subsystem[0].name=boot' "$report_txt"
grep -Fq 'subsystem[0].lifecycle_relation=boot-sequence-seeded' "$report_txt"
grep -Fq 'subsystem[1].name=runtime' "$report_txt"
grep -Fq 'subsystem[1].lifecycle_relation=runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout-observation-view-ready' "$report_txt"
grep -Fq 'subsystem[1].authority_status=runtime-entry-denied' "$report_txt"
grep -Fq 'subsystem[2].lifecycle_relation=scheduler-run-entry-ready' "$report_txt"
grep -Fq 'subsystem[2].authority_status=scheduler-execution-denied' "$report_txt"
grep -Fq 'subsystem[3].lifecycle_relation=memory-map-ready' "$report_txt"
grep -Fq 'subsystem[3].authority_status=memory-allocation-denied' "$report_txt"
grep -Fq 'subsystem[4].lifecycle_relation=ipc-table-ready' "$report_txt"
grep -Fq 'subsystem[4].authority_status=process-execution-denied' "$report_txt"
grep -Fq 'subsystem[5].lifecycle_relation=vfs-namespace-ready' "$report_txt"
grep -Fq 'subsystem[6].authority_status=network-denied' "$report_txt"
grep -Fq 'subsystem[6].lifecycle_relation=network-syscall-metadata-ready' "$report_txt"
grep -Fq 'subsystem[6].network_allowed=0' "$report_txt"
grep -Fq 'subsystem[7].authority_status=device-denied' "$report_txt"
grep -Fq 'subsystem[7].lifecycle_relation=interrupt-table-ready' "$report_txt"
grep -Fq 'subsystem[8].authority_status=not-production-boundary' "$report_txt"

printf 'kernel_lifecycle_subsystem_summary_report_runner: ok\n'
