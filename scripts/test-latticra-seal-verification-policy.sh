#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-verification-policy.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal verification policy: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_contains 'bounded_string_is' src/seal_verification_policy.c
require_contains 'unterminated public key identity status' tests/seal_verification_policy_invariants.c
require_contains 'authority verification policy render rejected' tests/seal_verification_policy_invariants.c
require_contains 'flag verification policy render rejected' tests/seal_verification_policy_invariants.c
require_contains 'unterminated trust source -> invalid-trust-source without copying caller bytes' docs/LATTICRA_SEAL_VERIFICATION_POLICY_IMPLEMENTATION.md

$CC $CFLAGS \
  -Iinclude \
  src/seal_verification_policy.c \
  tests/seal_verification_policy_invariants.c \
  -o "$tmpdir/latticra-seal-verification-policy-invariants"

"$tmpdir/latticra-seal-verification-policy-invariants"
