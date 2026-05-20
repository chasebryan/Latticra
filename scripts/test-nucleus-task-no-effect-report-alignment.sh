#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/state_lattice.c \
  src/nucleus_preview.c \
  src/nucleus_task.c \
  tests/nucleus_task_no_effect_report_alignment.c \
  -o /tmp/latticra-nucleus-task-no-effect-report-alignment

/tmp/latticra-nucleus-task-no-effect-report-alignment
