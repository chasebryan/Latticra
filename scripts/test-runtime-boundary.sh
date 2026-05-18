#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

for test_file in tests/runtime_boundary_*.c; do
  test_name=$(basename "$test_file" .c)
  cc $CFLAGS \
    -Iinclude \
    src/runtime_boundary.c \
    src/nucleus_task_plan.c \
    src/nucleus_task.c \
    src/nucleus_preview.c \
    src/state_lattice.c \
    "$test_file" \
    -o "/tmp/latticra-$test_name"

  "/tmp/latticra-$test_name"
done
