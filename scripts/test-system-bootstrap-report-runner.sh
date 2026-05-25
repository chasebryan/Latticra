#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-system-bootstrap-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

report_bin="$tmpdir/latticra-system-bootstrap-report"
report_txt="$tmpdir/latticra-system-bootstrap-report.txt"

cc $CFLAGS \
  -Iinclude \
  src/state_lattice.c \
  src/nucleus_preview.c \
  src/nucleus_task.c \
  src/runtime_boundary.c \
  src/system_bootstrap.c \
  tools/system_bootstrap_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"

grep -Fq 'LATTICRA SYSTEM BOOTSTRAP REPORT' "$report_txt"
grep -Fq 'bootstrap_id=latticra-system-bootstrap' "$report_txt"
grep -Fq 'system_status=startup-report-ready' "$report_txt"
grep -Fq 'effect_boundary=no-effect' "$report_txt"
grep -Fq 'runtime_entry_status=not-entered' "$report_txt"
grep -Fq 'no_effect=1' "$report_txt"

printf 'system_bootstrap_report_runner: ok\n'
