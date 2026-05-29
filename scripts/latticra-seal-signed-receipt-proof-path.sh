#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-seal-signed-receipt-proof-path.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

"$CC" $CFLAGS \
  -Iinclude \
  src/seal_verified_receipt_promotion.c \
  src/seal_signing_operation.c \
  src/seal_signed_receipt_proof_path.c \
  tests/seal_signed_receipt_proof_path_surface.c \
  -o "$tmpdir/latticra-seal-signed-receipt-proof-path"

"$tmpdir/latticra-seal-signed-receipt-proof-path"
