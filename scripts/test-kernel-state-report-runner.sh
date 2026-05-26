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
grep -Fq 'denied=0' "$report_txt"

printf 'kernel_state_report_runner: ok\n'
