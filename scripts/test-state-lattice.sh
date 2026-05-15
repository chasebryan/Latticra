#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/state_lattice.c \
  tests/state_lattice_invariants.c \
  -o /tmp/latticra-state-lattice-invariants

/tmp/latticra-state-lattice-invariants
