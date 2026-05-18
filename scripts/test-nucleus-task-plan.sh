#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/state_lattice.c \
  src/nucleus_preview.c \
  src/nucleus_task.c \
  src/nucleus_task_plan.c \
  tests/nucleus_task_plan_invariants.c \
  -o /tmp/latticra-nucleus-task-plan-invariants

/tmp/latticra-nucleus-task-plan-invariants
