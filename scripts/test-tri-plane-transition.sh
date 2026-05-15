#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/state_lattice.c \
  src/tri_plane_transition.c \
  tests/tri_plane_transition_invariants.c \
  -o /tmp/latticra-tri-plane-transition-invariants

/tmp/latticra-tri-plane-transition-invariants
