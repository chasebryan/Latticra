#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-signature-request.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal signature request: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_contains 'bounded_string_is' src/seal_signature_request.c
require_contains 'unterminated requested signature status' tests/seal_signature_request_invariants.c
require_contains 'authority request render rejected' tests/seal_signature_request_invariants.c
require_contains 'ready flag request render rejected' tests/seal_signature_request_invariants.c
require_contains 'unterminated requested signature -> denied-unknown-signature without copying caller bytes' docs/LATTICRA_SEAL_SIGNATURE_REQUEST_IMPLEMENTATION.md

cc $CFLAGS -Iinclude src/seal_signature_request.c tests/seal_signature_request_invariants.c -o "$tmpdir/latticra-seal-signature-request-invariants"
"$tmpdir/latticra-seal-signature-request-invariants"
