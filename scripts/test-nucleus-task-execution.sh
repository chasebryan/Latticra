#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/state_lattice.c \
  src/nucleus_preview.c \
  src/nucleus_task.c \
  tests/nucleus_task_execution_invariants.c \
  -o /tmp/latticra-nucleus-task-execution-invariants

/tmp/latticra-nucleus-task-execution-invariants

cc $CFLAGS \
  -Iinclude \
  src/state_lattice.c \
  src/nucleus_preview.c \
  src/nucleus_task.c \
  tests/nucleus_task_report_refinement.c \
  -o /tmp/latticra-nucleus-task-report-refinement

/tmp/latticra-nucleus-task-report-refinement
