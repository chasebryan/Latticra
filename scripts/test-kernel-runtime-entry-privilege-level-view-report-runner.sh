#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-kernel-runtime-entry-privilege-level-view-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

report_bin="$tmpdir/latticra-kernel-runtime-entry-privilege-level-view-report"
report_txt="$tmpdir/latticra-kernel-runtime-entry-privilege-level-view-report.txt"

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
  tools/kernel_runtime_entry_privilege_level_view_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"

grep -Fq 'LATTICRA KERNEL RUNTIME ENTRY PRIVILEGE LEVEL VIEW REPORT' "$report_txt"
grep -Fq 'privilege_level_view_status=runtime-entry-privilege-level-view-seed-ready' "$report_txt"
grep -Fq 'policy_status=report-only' "$report_txt"
grep -Fq 'runtime_entry_address_space_view_status=runtime-entry-address-space-view-seed-ready' "$report_txt"
grep -Fq 'runtime_entry_stack_view_status=runtime-entry-stack-view-seed-ready' "$report_txt"
grep -Fq 'privilege_level_view_count=4' "$report_txt"
grep -Fq 'runtime_entry_privilege_level_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_address_space_view_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_allowed=0' "$report_txt"
grep -Fq 'privilege_transition_allowed=0' "$report_txt"
grep -Fq 'syscall_gate_allowed=0' "$report_txt"
grep -Fq 'interrupt_return_allowed=0' "$report_txt"
grep -Fq 'hardware_effect_allowed=0' "$report_txt"
grep -Fq 'host_effect_allowed=0' "$report_txt"
grep -Fq 'privilege_level_view[0].process_label=kernel-report-process-metadata' "$report_txt"
grep -Fq 'privilege_level_view[0].privilege_level_view_class=kernel-report-runtime-entry-privilege-level-view' "$report_txt"
grep -Fq 'privilege_level_view[0].privilege_level=0' "$report_txt"
grep -Fq 'privilege_level_view[0].ring_number=0' "$report_txt"
grep -Fq 'privilege_level_view[0].capability_slot_count=4' "$report_txt"
grep -Fq 'privilege_level_view[0].privilege_boundary_declared=1' "$report_txt"
grep -Fq 'privilege_level_view[0].syscall_gate_declared=1' "$report_txt"
grep -Fq 'privilege_level_view[0].privilege_transition_planned=0' "$report_txt"
grep -Fq 'privilege_level_view[0].syscall_gate_planned=0' "$report_txt"
grep -Fq 'privilege_level_view[0].interrupt_return_planned=0' "$report_txt"
grep -Fq 'privilege_level_view[0].runtime_entry_privilege_level_view_allowed=0' "$report_txt"
grep -Fq 'privilege_level_view[0].privilege_transition_allowed=0' "$report_txt"
grep -Fq 'privilege_level_view[0].no_effect=1' "$report_txt"

printf 'kernel_runtime_entry_privilege_level_view_report_runner: ok\n'
