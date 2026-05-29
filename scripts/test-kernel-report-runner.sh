#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-kernel-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

report_bin="$tmpdir/latticra-kernel-report"
report_txt="$tmpdir/latticra-kernel-report.txt"

cc $CFLAGS \
  -Iinclude \
  src/state_lattice.c \
  src/nucleus_preview.c \
  src/nucleus_task.c \
  src/lat_parser.c \
  src/runtime_boundary.c \
  src/system_bootstrap.c \
  src/kernel.c \
  tools/kernel_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"

grep -Fq 'LATTICRA KERNEL REPORT' "$report_txt"
grep -Fq 'kernel_id=latticra-kernel-seed' "$report_txt"
grep -Fq 'kernel_status=initialized-report-only' "$report_txt"
grep -Fq 'boot_status=not-booted' "$report_txt"
grep -Fq 'runtime_status=not-entered' "$report_txt"
grep -Fq 'filesystem_status=disabled' "$report_txt"
grep -Fq 'network_status=disabled' "$report_txt"
grep -Fq 'device_status=disabled' "$report_txt"
grep -Fq 'no_effect=1' "$report_txt"

printf 'kernel_report_runner: ok\n'
