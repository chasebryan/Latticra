#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-nucleus-task-no-effect-report-alignment.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/state_lattice.c \
  src/nucleus_preview.c \
  src/nucleus_task.c \
  tests/nucleus_task_no_effect_report_alignment.c \
  -o "$tmpdir/latticra-nucleus-task-no-effect-report-alignment"

"$tmpdir/latticra-nucleus-task-no-effect-report-alignment"
