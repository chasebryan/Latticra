#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-kernel-runtime-entry-scheduler-return-observation-view-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

report_bin="$tmpdir/latticra-kernel-runtime-entry-scheduler-return-observation-view-report"
report_txt="$tmpdir/latticra-kernel-runtime-entry-scheduler-return-observation-view-report.txt"

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
  tools/kernel_runtime_entry_scheduler_return_observation_view_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"

grep -Fq 'LATTICRA KERNEL RUNTIME ENTRY SCHEDULER RETURN OBSERVATION VIEW REPORT' "$report_txt"
grep -Fq 'scheduler_return_observation_view_status=runtime-entry-scheduler-return-observation-view-seed-ready' "$report_txt"
grep -Fq 'policy_status=report-only' "$report_txt"
grep -Fq 'runtime_entry_post_resume_observation_view_status=runtime-entry-post-resume-observation-view-seed-ready' "$report_txt"
grep -Fq 'runtime_entry_user_mode_resume_view_status=runtime-entry-user-mode-resume-view-seed-ready' "$report_txt"
grep -Fq 'runtime_entry_syscall_exit_view_status=runtime-entry-syscall-exit-view-seed-ready' "$report_txt"
grep -Fq 'runtime_entry_syscall_return_view_status=runtime-entry-syscall-return-view-seed-ready' "$report_txt"
grep -Fq 'runtime_entry_syscall_dispatch_view_status=runtime-entry-syscall-dispatch-view-seed-ready' "$report_txt"
grep -Fq 'runtime_entry_syscall_gate_view_status=runtime-entry-syscall-gate-view-seed-ready' "$report_txt"
grep -Fq 'runtime_entry_privilege_level_view_status=runtime-entry-privilege-level-view-seed-ready' "$report_txt"
grep -Fq 'scheduler_return_observation_view_count=4' "$report_txt"
grep -Fq 'runtime_entry_scheduler_return_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_post_resume_observation_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_user_mode_resume_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_allowed=0' "$report_txt"
grep -Fq 'post_resume_observation_allowed=0' "$report_txt"
grep -Fq 'scheduler_return_observation_allowed=0' "$report_txt"
grep -Fq 'scheduler_return_allowed=0' "$report_txt"
grep -Fq 'scheduler_execution_allowed=0' "$report_txt"
grep -Fq 'scheduler_dispatch_allowed=0' "$report_txt"
grep -Fq 'scheduler_handoff_allowed=0' "$report_txt"
grep -Fq 'scheduler_activation_allowed=0' "$report_txt"
grep -Fq 'scheduler_run_entry_allowed=0' "$report_txt"
grep -Fq 'dispatch_allowed=0' "$report_txt"
grep -Fq 'context_switch_allowed=0' "$report_txt"
grep -Fq 'run_queue_mutation_allowed=0' "$report_txt"
grep -Fq 'instruction_pointer_read_allowed=0' "$report_txt"
grep -Fq 'stack_pointer_read_allowed=0' "$report_txt"
grep -Fq 'cpu_mode_read_allowed=0' "$report_txt"
grep -Fq 'hardware_effect_allowed=0' "$report_txt"
grep -Fq 'host_effect_allowed=0' "$report_txt"
grep -Fq 'scheduler_return_observation_view[0].process_label=kernel-report-process-metadata' "$report_txt"
grep -Fq 'scheduler_return_observation_view[0].scheduler_return_observation_view_class=kernel-report-runtime-entry-scheduler-return-observation-view' "$report_txt"
grep -Fq 'scheduler_return_observation_view[0].scheduler_return_observation_view_token=0' "$report_txt"
grep -Fq 'scheduler_return_observation_view[0].post_resume_observation_view_token=0' "$report_txt"
grep -Fq 'scheduler_return_observation_view[0].resume_slot=4096' "$report_txt"
grep -Fq 'scheduler_return_observation_view[0].observation_slot=5120' "$report_txt"
grep -Fq 'scheduler_return_observation_view[0].scheduler_return_slot=6144' "$report_txt"
grep -Fq 'scheduler_return_observation_view[0].scheduler_return_epoch_slot=17' "$report_txt"
grep -Fq 'scheduler_return_observation_view[0].scheduler_return_reason_slot=18' "$report_txt"
grep -Fq 'scheduler_return_observation_view[0].post_resume_observation_view_declared=1' "$report_txt"
grep -Fq 'scheduler_return_observation_view[0].scheduler_return_observation_view_declared=1' "$report_txt"
grep -Fq 'scheduler_return_observation_view[0].scheduler_return_observation_declared=1' "$report_txt"
grep -Fq 'scheduler_return_observation_view[0].scheduler_return_declared=1' "$report_txt"
grep -Fq 'scheduler_return_observation_view[0].scheduler_return_observation_view_planned=0' "$report_txt"
grep -Fq 'scheduler_return_observation_view[0].scheduler_execution_planned=0' "$report_txt"
grep -Fq 'scheduler_return_observation_view[0].runtime_entry_scheduler_return_observation_view_allowed=0' "$report_txt"
grep -Fq 'scheduler_return_observation_view[0].scheduler_return_observation_allowed=0' "$report_txt"
grep -Fq 'scheduler_return_observation_view[0].no_effect=1' "$report_txt"

printf 'kernel_runtime_entry_scheduler_return_observation_view_report_runner: ok\n'
