#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-kernel-scheduler-tick-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

report_bin="$tmpdir/latticra-kernel-scheduler-tick-report"
report_txt="$tmpdir/latticra-kernel-scheduler-tick-report.txt"

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
  tools/kernel_scheduler_tick_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"

grep -Fq 'LATTICRA KERNEL SCHEDULER TICK REPORT' "$report_txt"
grep -Fq 'tick_status=scheduler-tick-seed-ready' "$report_txt"
grep -Fq 'policy_status=report-only' "$report_txt"
grep -Fq 'timer_source_status=timer-source-seed-ready' "$report_txt"
grep -Fq 'interrupt_table_status=interrupt-table-seed-ready' "$report_txt"
grep -Fq 'scheduler_status=scheduler-seed-ready' "$report_txt"
grep -Fq 'tick_count=4' "$report_txt"
grep -Fq 'timer_tick_allowed=0' "$report_txt"
grep -Fq 'scheduler_tick_allowed=0' "$report_txt"
grep -Fq 'run_queue_mutation_allowed=0' "$report_txt"
grep -Fq 'context_switch_allowed=0' "$report_txt"
grep -Fq 'preemption_allowed=0' "$report_txt"
grep -Fq 'time_accounting_allowed=0' "$report_txt"
grep -Fq 'time_read_allowed=0' "$report_txt"
grep -Fq 'process_wake_allowed=0' "$report_txt"
grep -Fq 'hardware_effect_allowed=0' "$report_txt"
grep -Fq 'host_effect_allowed=0' "$report_txt"
grep -Fq 'tick[0].timer_name=kernel-tick-timer-metadata' "$report_txt"
grep -Fq 'tick[0].scheduler_slot_label=idle-metadata' "$report_txt"
grep -Fq 'tick[0].process_label=idle-process-metadata' "$report_txt"
grep -Fq 'tick[0].tick_class=scheduler-clock-tick' "$report_txt"
grep -Fq 'tick[0].pending=0' "$report_txt"
grep -Fq 'tick[0].dispatched=0' "$report_txt"
grep -Fq 'tick[0].no_effect=1' "$report_txt"

printf 'kernel_scheduler_tick_report_runner: ok\n'
