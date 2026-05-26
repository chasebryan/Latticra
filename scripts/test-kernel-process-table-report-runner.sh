#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-kernel-process-table-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

report_bin="$tmpdir/latticra-kernel-process-table-report"
report_txt="$tmpdir/latticra-kernel-process-table-report.txt"

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
  tools/kernel_process_table_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"

grep -Fq 'LATTICRA KERNEL PROCESS TABLE REPORT' "$report_txt"
grep -Fq 'table_status=process-table-seed-ready' "$report_txt"
grep -Fq 'policy_status=report-only' "$report_txt"
grep -Fq 'memory_map_status=memory-map-seed-ready' "$report_txt"
grep -Fq 'scheduler_status=scheduler-seed-ready' "$report_txt"
grep -Fq 'process_count=4' "$report_txt"
grep -Fq 'process_spawn_allowed=0' "$report_txt"
grep -Fq 'context_switch_allowed=0' "$report_txt"
grep -Fq 'signal_delivery_allowed=0' "$report_txt"
grep -Fq 'address_space_mutation_allowed=0' "$report_txt"
grep -Fq 'process[0].label=idle-process-metadata' "$report_txt"
grep -Fq 'process[0].authority_status=spawn-denied' "$report_txt"
grep -Fq 'process[0].spawned=0' "$report_txt"
grep -Fq 'no_effect=1' "$report_txt"

printf 'kernel_process_table_report_runner: ok\n'
