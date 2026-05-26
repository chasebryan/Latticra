#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-kernel-ipc-table-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

report_bin="$tmpdir/latticra-kernel-ipc-table-report"
report_txt="$tmpdir/latticra-kernel-ipc-table-report.txt"

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
  tools/kernel_ipc_table_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"

grep -Fq 'LATTICRA KERNEL IPC TABLE REPORT' "$report_txt"
grep -Fq 'table_status=ipc-table-seed-ready' "$report_txt"
grep -Fq 'policy_status=report-only' "$report_txt"
grep -Fq 'syscall_table_status=syscall-table-seed-ready' "$report_txt"
grep -Fq 'process_table_status=process-table-seed-ready' "$report_txt"
grep -Fq 'memory_map_status=memory-map-seed-ready' "$report_txt"
grep -Fq 'port_count=5' "$report_txt"
grep -Fq 'ipc_send_allowed=0' "$report_txt"
grep -Fq 'ipc_receive_allowed=0' "$report_txt"
grep -Fq 'queue_mutation_allowed=0' "$report_txt"
grep -Fq 'endpoint_bind_allowed=0' "$report_txt"
grep -Fq 'host_effect_allowed=0' "$report_txt"
grep -Fq 'port[0].label=kernel-control-port-metadata' "$report_txt"
grep -Fq 'port[2].authority_status=ipc-queue-denied' "$report_txt"
grep -Fq 'port[4].domain=network' "$report_txt"
grep -Fq 'port[0].bound=0' "$report_txt"
grep -Fq 'no_effect=1' "$report_txt"

printf 'kernel_ipc_table_report_runner: ok\n'
