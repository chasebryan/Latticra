#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-signer-invocation.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal signer invocation: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_contains 'bounded_string_is' src/seal_signer_invocation.c
require_contains 'bounded_string_empty' src/seal_signer_invocation.c
require_contains 'unterminated requested signer invocation status' tests/seal_signer_invocation_invariants.c
require_contains 'authority signer invocation render rejected' tests/seal_signer_invocation_invariants.c
require_contains 'ready flag signer invocation render rejected' tests/seal_signer_invocation_invariants.c
require_contains 'absent crypto gate authority status' tests/seal_signer_invocation_invariants.c
require_contains 'absent crypto gate stale render rejected' tests/seal_signer_invocation_invariants.c
require_contains 'unterminated requested signer invocation -> denied-signer-invocation without copying caller bytes' docs/LATTICRA_SEAL_SIGNER_INVOCATION_IMPLEMENTATION.md
require_contains 'stale crypto graduation evidence when the gate-present flag is unset' docs/LATTICRA_SEAL_SIGNER_INVOCATION_IMPLEMENTATION.md

$CC $CFLAGS -Iinclude src/seal_signer_invocation.c tests/seal_signer_invocation_invariants.c -o "$tmpdir/latticra-seal-signer-invocation-invariants"
"$tmpdir/latticra-seal-signer-invocation-invariants"
