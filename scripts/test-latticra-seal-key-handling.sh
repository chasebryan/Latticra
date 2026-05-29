#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-key-handling.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal key handling: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_contains 'bounded_string_is' src/seal_key_handling.c
require_contains 'bounded_string_empty' src/seal_key_handling.c
require_contains 'crypto_graduation_gate_passed == 0u' src/seal_key_handling.c
require_contains 'unterminated requested key handling status' tests/seal_key_handling_invariants.c
require_contains 'authority key handling render rejected' tests/seal_key_handling_invariants.c
require_contains 'ready flag key handling render rejected' tests/seal_key_handling_invariants.c
require_contains 'absent crypto gate authority status' tests/seal_key_handling_invariants.c
require_contains 'absent crypto gate stale render rejected' tests/seal_key_handling_invariants.c
require_contains 'unterminated requested key handling -> denied-key-handling without copying caller bytes' docs/LATTICRA_SEAL_KEY_HANDLING_IMPLEMENTATION.md

$CC $CFLAGS -Iinclude src/seal_key_handling.c tests/seal_key_handling_invariants.c -o "$tmpdir/latticra-seal-key-handling-invariants"
"$tmpdir/latticra-seal-key-handling-invariants"
