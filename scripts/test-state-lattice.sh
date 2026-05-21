#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-state-lattice.XXXXXX")"
bin="$tmpdir/latticra-state-lattice-invariants"

cc $CFLAGS \
  -Iinclude \
  src/state_lattice.c \
  tests/state_lattice_invariants.c \
  -o "$bin"

"$bin"
