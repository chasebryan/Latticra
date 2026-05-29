#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-signed-receipt-proof-path.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal signed receipt proof path: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_contains 'latticra-seal-signed-receipt-proof-path/0.1' src/seal_signed_receipt_proof_path.c
require_contains 'trust_root_verified = 0u' src/seal_signed_receipt_proof_path.c
require_contains 'revocation_checked = 0u' src/seal_signed_receipt_proof_path.c
require_contains 'proof_path_verified = 0u' src/seal_signed_receipt_proof_path.c
require_contains 'signature_performed = 0u' src/seal_signed_receipt_proof_path.c
require_contains 'network_performed = 0u' src/seal_signed_receipt_proof_path.c
require_contains 'receipt-authority-not-neutral' tests/seal_signed_receipt_proof_path_invariants.c
require_contains 'digest-mismatch' tests/seal_signed_receipt_proof_path_invariants.c
require_contains 'public-key-mismatch' tests/seal_signed_receipt_proof_path_invariants.c

"$CC" $CFLAGS \
  -Iinclude \
  src/seal_verified_receipt_promotion.c \
  src/seal_signing_operation.c \
  src/seal_signed_receipt_proof_path.c \
  tests/seal_signed_receipt_proof_path_invariants.c \
  -o "$tmpdir/latticra-seal-signed-receipt-proof-path-invariants"

"$tmpdir/latticra-seal-signed-receipt-proof-path-invariants"
