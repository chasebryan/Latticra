#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-kernel-scheduler-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

report_bin="$tmpdir/latticra-kernel-scheduler-report"
report_txt="$tmpdir/latticra-kernel-scheduler-report.txt"

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
  tools/kernel_scheduler_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"

grep -Fq 'LATTICRA KERNEL SCHEDULER REPORT' "$report_txt"
grep -Fq 'scheduler_status=scheduler-seed-ready' "$report_txt"
grep -Fq 'policy_status=report-only' "$report_txt"
grep -Fq 'registry_status=registry-ready' "$report_txt"
grep -Fq 'slot_count=3' "$report_txt"
grep -Fq 'slot[0].label=idle-metadata' "$report_txt"
grep -Fq 'slot[0].selection_status=not-selected' "$report_txt"
grep -Fq 'no_effect=1' "$report_txt"

printf 'kernel_scheduler_report_runner: ok\n'
