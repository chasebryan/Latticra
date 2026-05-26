#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-capability-gate.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/seal_capability_gate.c \
  tests/seal_capability_gate_invariants.c \
  -o "$tmpdir/latticra-seal-capability-gate-invariants"

"$tmpdir/latticra-seal-capability-gate-invariants"
