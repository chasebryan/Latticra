#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-kernel-syscall-table-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

report_bin="$tmpdir/latticra-kernel-syscall-table-report"
report_txt="$tmpdir/latticra-kernel-syscall-table-report.txt"

cc $CFLAGS \
  -Iinclude \
  src/state_lattice.c \
  src/nucleus_preview.c \
  src/nucleus_task.c \
  src/runtime_boundary.c \
  src/system_bootstrap.c \
  src/kernel.c \
  src/kernel_subsystem_registry.c \
  src/kernel_scheduler.c \
  src/kernel_memory_map.c \
  src/kernel_process_table.c \
  src/kernel_syscall_table.c \
  tools/kernel_syscall_table_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"

grep -Fq 'LATTICRA KERNEL SYSCALL TABLE REPORT' "$report_txt"
grep -Fq 'table_status=syscall-table-seed-ready' "$report_txt"
grep -Fq 'policy_status=report-only' "$report_txt"
grep -Fq 'process_table_status=process-table-seed-ready' "$report_txt"
grep -Fq 'memory_map_status=memory-map-seed-ready' "$report_txt"
grep -Fq 'call_count=8' "$report_txt"
grep -Fq 'syscall_dispatch_allowed=0' "$report_txt"
grep -Fq 'host_effect_allowed=0' "$report_txt"
grep -Fq 'file_io_allowed=0' "$report_txt"
grep -Fq 'network_allowed=0' "$report_txt"
grep -Fq 'call[0].name=yield' "$report_txt"
grep -Fq 'call[1].name=spawn_process' "$report_txt"
grep -Fq 'call[7].authority_status=network-io-denied' "$report_txt"
grep -Fq 'call[0].implemented=0' "$report_txt"
grep -Fq 'no_effect=1' "$report_txt"

printf 'kernel_syscall_table_report_runner: ok\n'
