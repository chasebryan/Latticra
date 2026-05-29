#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-kernel-runtime-entry-recovery-outcome-observation-view-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

report_bin="$tmpdir/latticra-kernel-runtime-entry-recovery-outcome-observation-view-report"
report_txt="$tmpdir/latticra-kernel-runtime-entry-recovery-outcome-observation-view-report.txt"

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
  tools/kernel_runtime_entry_recovery_outcome_observation_view_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"

grep -Fq 'LATTICRA KERNEL RUNTIME ENTRY RECOVERY OUTCOME OBSERVATION VIEW REPORT' "$report_txt"
grep -Fq 'recovery_outcome_observation_view_status=runtime-entry-recovery-outcome-observation-view-seed-ready' "$report_txt"
grep -Fq 'policy_status=report-only' "$report_txt"
grep -Fq 'runtime_entry_recovery_disposition_observation_view_status=runtime-entry-recovery-disposition-observation-view-seed-ready' "$report_txt"
grep -Fq 'runtime_entry_recovery_plan_observation_view_status=runtime-entry-recovery-plan-observation-view-seed-ready' "$report_txt"
grep -Fq 'runtime_entry_recovery_boundary_observation_view_status=runtime-entry-recovery-boundary-observation-view-seed-ready' "$report_txt"
grep -Fq 'runtime_entry_persistence_boundary_observation_view_status=runtime-entry-persistence-boundary-observation-view-seed-ready' "$report_txt"
grep -Fq 'runtime_entry_quiescent_return_observation_view_status=runtime-entry-quiescent-return-observation-view-seed-ready' "$report_txt"
grep -Fq 'runtime_entry_idle_return_observation_view_status=runtime-entry-idle-return-observation-view-seed-ready' "$report_txt"
grep -Fq 'runtime_entry_process_return_observation_view_status=runtime-entry-process-return-observation-view-seed-ready' "$report_txt"
grep -Fq 'recovery_outcome_observation_view_count=4' "$report_txt"
grep -Fq 'runtime_entry_recovery_outcome_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_recovery_disposition_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_recovery_plan_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_recovery_boundary_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_persistence_boundary_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_quiescent_return_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_idle_return_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_process_return_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_allowed=0' "$report_txt"
grep -Fq 'recovery_outcome_observation_allowed=0' "$report_txt"
grep -Fq 'recovery_outcome_allowed=0' "$report_txt"
grep -Fq 'recovery_disposition_observation_allowed=0' "$report_txt"
grep -Fq 'recovery_disposition_allowed=0' "$report_txt"
grep -Fq 'recovery_plan_observation_allowed=0' "$report_txt"
grep -Fq 'recovery_plan_allowed=0' "$report_txt"
grep -Fq 'recovery_boundary_observation_allowed=0' "$report_txt"
grep -Fq 'recovery_boundary_allowed=0' "$report_txt"
grep -Fq 'persistence_boundary_observation_allowed=0' "$report_txt"
grep -Fq 'persistence_boundary_allowed=0' "$report_txt"
grep -Fq 'persistence_commit_allowed=0' "$report_txt"
grep -Fq 'persistence_allowed=0' "$report_txt"
grep -Fq 'recovery_authority_allowed=0' "$report_txt"
grep -Fq 'scheduler_execution_allowed=0' "$report_txt"
grep -Fq 'scheduler_dispatch_allowed=0' "$report_txt"
grep -Fq 'context_switch_allowed=0' "$report_txt"
grep -Fq 'run_queue_mutation_allowed=0' "$report_txt"
grep -Fq 'process_wake_allowed=0' "$report_txt"
grep -Fq 'hardware_effect_allowed=0' "$report_txt"
grep -Fq 'host_effect_allowed=0' "$report_txt"
grep -Fq 'evidence_level=47' "$report_txt"
grep -Fq 'recovery_outcome_observation_view[0].process_label=kernel-report-process-metadata' "$report_txt"
grep -Fq 'recovery_outcome_observation_view[0].recovery_outcome_observation_view_class=kernel-report-runtime-entry-recovery-outcome-observation-view' "$report_txt"
grep -Fq 'recovery_outcome_observation_view[0].recovery_outcome_observation_view_token=0' "$report_txt"
grep -Fq 'recovery_outcome_observation_view[0].recovery_disposition_observation_view_token=0' "$report_txt"
grep -Fq 'recovery_outcome_observation_view[0].recovery_plan_observation_view_token=0' "$report_txt"
grep -Fq 'recovery_outcome_observation_view[0].recovery_disposition_observation_slot=13312' "$report_txt"
grep -Fq 'recovery_outcome_observation_view[0].recovery_outcome_observation_slot=14336' "$report_txt"
grep -Fq 'recovery_outcome_observation_view[0].recovery_disposition_slot=34' "$report_txt"
grep -Fq 'recovery_outcome_observation_view[0].recovery_outcome_slot=35' "$report_txt"
grep -Fq 'recovery_outcome_observation_view[0].recovery_outcome_observation_declared=1' "$report_txt"
grep -Fq 'recovery_outcome_observation_view[0].recovery_outcome_observation_planned=0' "$report_txt"
grep -Fq 'recovery_outcome_observation_view[0].runtime_entry_recovery_outcome_observation_view_allowed=0' "$report_txt"
grep -Fq 'recovery_outcome_observation_view[0].recovery_outcome_observation_allowed=0' "$report_txt"
grep -Fq 'recovery_outcome_observation_view[0].recovery_outcome_allowed=0' "$report_txt"
grep -Fq 'recovery_outcome_observation_view[0].recovery_disposition_observation_allowed=0' "$report_txt"
grep -Fq 'recovery_outcome_observation_view[0].no_effect=1' "$report_txt"

printf 'kernel_runtime_entry_recovery_outcome_observation_view_report_runner: ok\n'
