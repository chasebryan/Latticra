#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-tri-plane-transition.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM
bin="$tmpdir/latticra-tri-plane-transition-invariants"

cc $CFLAGS \
  -Iinclude \
  src/state_lattice.c \
  src/tri_plane_transition.c \
  tests/tri_plane_transition_invariants.c \
  -o "$bin"

"$bin"
