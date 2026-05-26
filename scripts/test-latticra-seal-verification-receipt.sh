#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-verification-receipt.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/seal_verification_receipt.c \
  tests/seal_verification_receipt_invariants.c \
  -o "$tmpdir/latticra-seal-verification-receipt-invariants"

"$tmpdir/latticra-seal-verification-receipt-invariants"
