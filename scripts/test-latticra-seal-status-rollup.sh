#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-status-rollup.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/seal_status_rollup.c \
  tests/seal_status_rollup_invariants.c \
  -o "$tmpdir/latticra-seal-status-rollup-invariants"

"$tmpdir/latticra-seal-status-rollup-invariants"
