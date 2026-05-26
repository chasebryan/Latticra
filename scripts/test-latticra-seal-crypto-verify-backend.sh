#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-crypto-verify-backend.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/seal_crypto_verify_backend.c \
  tests/seal_crypto_verify_backend_invariants.c \
  -o "$tmpdir/latticra-seal-crypto-verify-backend-invariants"

"$tmpdir/latticra-seal-crypto-verify-backend-invariants"
