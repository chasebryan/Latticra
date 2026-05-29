#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-verified-receipt-promotion.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS -Iinclude src/seal_verified_receipt_promotion.c tests/seal_verified_receipt_promotion_invariants.c -o "$tmpdir/latticra-seal-verified-receipt-promotion-invariants"
"$tmpdir/latticra-seal-verified-receipt-promotion-invariants"
