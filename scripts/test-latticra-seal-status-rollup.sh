#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/seal_status_rollup.c \
  tests/seal_status_rollup_invariants.c \
  -o /tmp/latticra-seal-status-rollup-invariants

/tmp/latticra-seal-status-rollup-invariants
