#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-l-ui-static-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/state_lattice.c \
  src/nucleus_preview.c \
  src/l_ui_static_report.c \
  tests/l_ui_static_report_invariants.c \
  -o "$tmpdir/latticra-l-ui-static-report-invariants"

"$tmpdir/latticra-l-ui-static-report-invariants"
