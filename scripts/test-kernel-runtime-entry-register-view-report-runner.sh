#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-kernel-runtime-entry-register-view-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

report_bin="$tmpdir/latticra-kernel-runtime-entry-register-view-report"
report_txt="$tmpdir/latticra-kernel-runtime-entry-register-view-report.txt"

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
  tools/kernel_runtime_entry_register_view_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"

grep -Fq 'LATTICRA KERNEL RUNTIME ENTRY REGISTER VIEW REPORT' "$report_txt"
grep -Fq 'register_view_status=runtime-entry-register-view-seed-ready' "$report_txt"
grep -Fq 'policy_status=report-only' "$report_txt"
grep -Fq 'runtime_entry_frame_status=runtime-entry-frame-seed-ready' "$report_txt"
grep -Fq 'runtime_entry_admission_status=runtime-entry-admission-seed-ready' "$report_txt"
grep -Fq 'scheduler_run_entry_status=scheduler-run-entry-seed-ready' "$report_txt"
grep -Fq 'register_view_count=4' "$report_txt"
grep -Fq 'runtime_entry_register_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_frame_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_allowed=0' "$report_txt"
grep -Fq 'context_switch_allowed=0' "$report_txt"
grep -Fq 'register_save_allowed=0' "$report_txt"
grep -Fq 'register_restore_allowed=0' "$report_txt"
grep -Fq 'stack_switch_allowed=0' "$report_txt"
grep -Fq 'address_space_switch_allowed=0' "$report_txt"
grep -Fq 'hardware_effect_allowed=0' "$report_txt"
grep -Fq 'host_effect_allowed=0' "$report_txt"
grep -Fq 'register_view[0].process_label=kernel-report-process-metadata' "$report_txt"
grep -Fq 'register_view[0].register_view_class=kernel-report-runtime-entry-register-view' "$report_txt"
grep -Fq 'register_view[0].register_view_rank=1' "$report_txt"
grep -Fq 'register_view[0].register_slot_count=16' "$report_txt"
grep -Fq 'register_view[0].instruction_pointer_declared=1' "$report_txt"
grep -Fq 'register_view[0].stack_pointer_declared=1' "$report_txt"
grep -Fq 'register_view[0].flags_declared=1' "$report_txt"
grep -Fq 'register_view[0].register_view_planned=0' "$report_txt"
grep -Fq 'register_view[0].register_capture_planned=0' "$report_txt"
grep -Fq 'register_view[0].register_save_allowed=0' "$report_txt"
grep -Fq 'register_view[0].register_restore_allowed=0' "$report_txt"
grep -Fq 'register_view[0].no_effect=1' "$report_txt"

printf 'kernel_runtime_entry_register_view_report_runner: ok\n'
