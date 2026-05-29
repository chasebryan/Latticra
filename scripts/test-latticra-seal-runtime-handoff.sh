#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-runtime-handoff.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/seal_runtime_handoff.c \
  tests/seal_runtime_handoff_invariants.c \
  -o "$tmpdir/latticra-seal-runtime-handoff-invariants"

"$tmpdir/latticra-seal-runtime-handoff-invariants"
