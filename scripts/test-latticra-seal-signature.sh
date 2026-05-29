#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-signature.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/seal_signature.c \
  tests/seal_signature_invariants.c \
  -o "$tmpdir/latticra-seal-signature-invariants"

"$tmpdir/latticra-seal-signature-invariants"
