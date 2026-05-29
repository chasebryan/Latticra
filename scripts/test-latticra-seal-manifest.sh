#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-manifest.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/seal_manifest.c \
  tests/seal_manifest_invariants.c \
  -o "$tmpdir/latticra-seal-manifest-invariants"

"$tmpdir/latticra-seal-manifest-invariants"
