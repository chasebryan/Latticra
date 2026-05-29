#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-signing-authorization.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal signing authorization: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_contains 'bounded_string_is' src/seal_signing_authorization.c
require_contains 'unterminated requested signing authorization status' tests/seal_signing_authorization_invariants.c
require_contains 'authority authorization render rejected' tests/seal_signing_authorization_invariants.c
require_contains 'ready flag authorization render rejected' tests/seal_signing_authorization_invariants.c
require_contains 'unterminated requested signing authorization -> denied-authorization-request without copying caller bytes' docs/LATTICRA_SEAL_SIGNING_AUTHORIZATION_IMPLEMENTATION.md

$CC $CFLAGS -Iinclude src/seal_signing_authorization.c tests/seal_signing_authorization_invariants.c -o "$tmpdir/latticra-seal-signing-authorization-invariants"
"$tmpdir/latticra-seal-signing-authorization-invariants"
