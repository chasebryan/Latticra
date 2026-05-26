#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-kernel-memory-map-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

report_bin="$tmpdir/latticra-kernel-memory-map-report"
report_txt="$tmpdir/latticra-kernel-memory-map-report.txt"

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
  tools/kernel_memory_map_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"

grep -Fq 'LATTICRA KERNEL MEMORY MAP REPORT' "$report_txt"
grep -Fq 'map_status=memory-map-seed-ready' "$report_txt"
grep -Fq 'policy_status=report-only' "$report_txt"
grep -Fq 'scheduler_status=scheduler-seed-ready' "$report_txt"
grep -Fq 'region_count=4' "$report_txt"
grep -Fq 'mapping_allowed=0' "$report_txt"
grep -Fq 'write_allowed=0' "$report_txt"
grep -Fq 'execute_allowed=0' "$report_txt"
grep -Fq 'region[0].label=kernel-text-metadata' "$report_txt"
grep -Fq 'region[3].label=kernel-report-metadata' "$report_txt"
grep -Fq 'no_effect=1' "$report_txt"

printf 'kernel_memory_map_report_runner: ok\n'
