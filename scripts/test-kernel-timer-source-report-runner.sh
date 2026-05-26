#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-kernel-timer-source-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

report_bin="$tmpdir/latticra-kernel-timer-source-report"
report_txt="$tmpdir/latticra-kernel-timer-source-report.txt"

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
  tools/kernel_timer_source_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"

grep -Fq 'LATTICRA KERNEL TIMER SOURCE REPORT' "$report_txt"
grep -Fq 'timer_status=timer-source-seed-ready' "$report_txt"
grep -Fq 'policy_status=report-only' "$report_txt"
grep -Fq 'interrupt_table_status=interrupt-table-seed-ready' "$report_txt"
grep -Fq 'timer_count=4' "$report_txt"
grep -Fq 'timer_tick_allowed=0' "$report_txt"
grep -Fq 'timer_arm_allowed=0' "$report_txt"
grep -Fq 'timer_disarm_allowed=0' "$report_txt"
grep -Fq 'scheduler_tick_allowed=0' "$report_txt"
grep -Fq 'preemption_allowed=0' "$report_txt"
grep -Fq 'time_read_allowed=0' "$report_txt"
grep -Fq 'hardware_effect_allowed=0' "$report_txt"
grep -Fq 'host_effect_allowed=0' "$report_txt"
grep -Fq 'timer[0].name=kernel-tick-timer-metadata' "$report_txt"
grep -Fq 'timer[0].irq_vector=35' "$report_txt"
grep -Fq 'timer[0].period_ns=10000000' "$report_txt"
grep -Fq 'timer[1].timer_class=monotonic-time-source' "$report_txt"
grep -Fq 'timer[0].armed=0' "$report_txt"
grep -Fq 'timer[0].running=0' "$report_txt"
grep -Fq 'timer[0].no_effect=1' "$report_txt"

printf 'kernel_timer_source_report_runner: ok\n'
