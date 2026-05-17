#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/runtime_boundary.c \
  src/nucleus_task.c \
  src/nucleus_preview.c \
  src/state_lattice.c \
  tests/runtime_boundary_invariants.c \
  -o /tmp/latticra-runtime-boundary-invariants

/tmp/latticra-runtime-boundary-invariants
