#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-kernel-state-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

report_bin="$tmpdir/latticra-kernel-state-report"
report_txt="$tmpdir/latticra-kernel-state-report.txt"

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
  tools/kernel_state_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"

grep -Fq 'LATTICRA KERNEL STATE REPORT' "$report_txt"
grep -Fq 'state_status=changed' "$report_txt"
grep -Fq 'gate_status=allow' "$report_txt"
grep -Fq 'transition_status=transition-applied' "$report_txt"
grep -Fq 'effect_status=in-memory-state-change' "$report_txt"
grep -Fq 'previous_state=created' "$report_txt"
grep -Fq 'next_state=initialized' "$report_txt"
grep -Fq 'state_change_performed=1' "$report_txt"
grep -Fq 'external_effect_performed=0' "$report_txt"
grep -Fq 'network_allowed=0' "$report_txt"
grep -Fq 'syscall_network_allowed=0' "$report_txt"
grep -Fq 'ipc_network_allowed=0' "$report_txt"
grep -Fq 'denied=0' "$report_txt"

printf 'kernel_state_report_runner: ok\n'
