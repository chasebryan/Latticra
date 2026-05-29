#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-nucleus-task-execution.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/state_lattice.c \
  src/nucleus_preview.c \
  src/nucleus_task.c \
  tests/nucleus_task_execution_invariants.c \
  -o "$tmpdir/latticra-nucleus-task-execution-invariants"

"$tmpdir/latticra-nucleus-task-execution-invariants"

cc $CFLAGS \
  -Iinclude \
  src/state_lattice.c \
  src/nucleus_preview.c \
  src/nucleus_task.c \
  tests/nucleus_task_report_refinement.c \
  -o "$tmpdir/latticra-nucleus-task-report-refinement"

"$tmpdir/latticra-nucleus-task-report-refinement"

sh scripts/test-nucleus-task-no-effect-report-alignment.sh
sh scripts/test-nucleus-task-report-only-execution-refinement.sh
