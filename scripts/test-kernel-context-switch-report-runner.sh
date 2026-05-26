#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-kernel-context-switch-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

report_bin="$tmpdir/latticra-kernel-context-switch-report"
report_txt="$tmpdir/latticra-kernel-context-switch-report.txt"

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
  tools/kernel_context_switch_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"

grep -Fq 'LATTICRA KERNEL CONTEXT SWITCH REPORT' "$report_txt"
grep -Fq 'switch_status=context-switch-seed-ready' "$report_txt"
grep -Fq 'policy_status=report-only' "$report_txt"
grep -Fq 'run_queue_status=run-queue-seed-ready' "$report_txt"
grep -Fq 'scheduler_tick_status=scheduler-tick-seed-ready' "$report_txt"
grep -Fq 'timer_source_status=timer-source-seed-ready' "$report_txt"
grep -Fq 'switch_count=4' "$report_txt"
grep -Fq 'context_switch_allowed=0' "$report_txt"
grep -Fq 'register_save_allowed=0' "$report_txt"
grep -Fq 'register_restore_allowed=0' "$report_txt"
grep -Fq 'stack_switch_allowed=0' "$report_txt"
grep -Fq 'address_space_switch_allowed=0' "$report_txt"
grep -Fq 'dispatch_allowed=0' "$report_txt"
grep -Fq 'run_queue_mutation_allowed=0' "$report_txt"
grep -Fq 'preemption_allowed=0' "$report_txt"
grep -Fq 'time_accounting_allowed=0' "$report_txt"
grep -Fq 'process_wake_allowed=0' "$report_txt"
grep -Fq 'hardware_effect_allowed=0' "$report_txt"
grep -Fq 'host_effect_allowed=0' "$report_txt"
grep -Fq 'switch[0].from_process_label=idle-process-metadata' "$report_txt"
grep -Fq 'switch[0].to_process_label=kernel-report-process-metadata' "$report_txt"
grep -Fq 'switch[0].switch_class=idle-to-kernel-report-context-switch' "$report_txt"
grep -Fq 'switch[0].prepared=0' "$report_txt"
grep -Fq 'switch[0].selected=0' "$report_txt"
grep -Fq 'switch[0].committed=0' "$report_txt"
grep -Fq 'switch[0].no_effect=1' "$report_txt"

printf 'kernel_context_switch_report_runner: ok\n'
