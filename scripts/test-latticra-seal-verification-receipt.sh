#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-verification-receipt.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal verification receipt: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_contains 'bounded_string_is' src/seal_verification_receipt.c
require_contains 'unterminated policy status' tests/seal_verification_receipt_invariants.c
require_contains 'authority verification receipt render rejected' tests/seal_verification_receipt_invariants.c
require_contains 'flag verification receipt render rejected' tests/seal_verification_receipt_invariants.c
require_contains 'unterminated verification policy metadata strings -> invalid-policy' docs/LATTICRA_SEAL_VERIFICATION_RECEIPT_IMPLEMENTATION.md

$CC $CFLAGS \
  -Iinclude \
  src/seal_verification_receipt.c \
  tests/seal_verification_receipt_invariants.c \
  -o "$tmpdir/latticra-seal-verification-receipt-invariants"

"$tmpdir/latticra-seal-verification-receipt-invariants"
