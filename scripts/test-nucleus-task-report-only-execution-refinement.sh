#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-nucleus-task-report-only-execution-refinement.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/state_lattice.c \
  src/nucleus_preview.c \
  src/nucleus_task.c \
  tests/nucleus_task_report_only_execution_refinement.c \
  -o "$tmpdir/latticra-nucleus-task-report-only-execution-refinement"

"$tmpdir/latticra-nucleus-task-report-only-execution-refinement"
