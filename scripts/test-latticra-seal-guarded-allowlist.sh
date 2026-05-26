#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-guarded-allowlist.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/seal_guarded_allowlist.c \
  tests/seal_guarded_allowlist_invariants.c \
  -o "$tmpdir/latticra-seal-guarded-allowlist-invariants"

"$tmpdir/latticra-seal-guarded-allowlist-invariants"
