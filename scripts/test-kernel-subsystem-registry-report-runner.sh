#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-kernel-subsystem-registry-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

report_bin="$tmpdir/latticra-kernel-subsystem-registry-report"
report_txt="$tmpdir/latticra-kernel-subsystem-registry-report.txt"

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
  tools/kernel_subsystem_registry_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"

grep -Fq 'LATTICRA KERNEL SUBSYSTEM REGISTRY REPORT' "$report_txt"
grep -Fq 'registry_status=registry-ready' "$report_txt"
grep -Fq 'kernel_status=initialized-report-only' "$report_txt"
grep -Fq 'entry_count=9' "$report_txt"
grep -Fq 'subsystem[0].name=boot' "$report_txt"
grep -Fq 'subsystem[2].name=scheduler' "$report_txt"
grep -Fq 'subsystem[3].name=memory' "$report_txt"
grep -Fq 'subsystem[8].name=security' "$report_txt"
grep -Fq 'no_effect=1' "$report_txt"

printf 'kernel_subsystem_registry_report_runner: ok\n'
