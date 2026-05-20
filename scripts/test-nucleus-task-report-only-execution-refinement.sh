#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/state_lattice.c \
  src/nucleus_preview.c \
  src/nucleus_task.c \
  tests/nucleus_task_report_only_execution_refinement.c \
  -o /tmp/latticra-nucleus-task-report-only-execution-refinement

/tmp/latticra-nucleus-task-report-only-execution-refinement
