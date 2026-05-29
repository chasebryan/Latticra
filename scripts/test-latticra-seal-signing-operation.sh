#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-signing-operation.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal signing operation: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_contains 'bounded_string_is' src/seal_signing_operation.c
require_contains 'bounded_string_empty' src/seal_signing_operation.c
require_contains 'unterminated requested signing operation status' tests/seal_signing_operation_invariants.c
require_contains 'authority signing operation render rejected' tests/seal_signing_operation_invariants.c
require_contains 'ready flag signing operation render rejected' tests/seal_signing_operation_invariants.c
require_contains 'absent crypto gate authority status' tests/seal_signing_operation_invariants.c
require_contains 'absent crypto gate stale render rejected' tests/seal_signing_operation_invariants.c
require_contains 'unterminated requested signing operation -> denied-signing-operation without copying caller bytes' docs/LATTICRA_SEAL_SIGNING_OPERATION_IMPLEMENTATION.md
require_contains 'stale crypto graduation evidence when the gate-present flag is unset' docs/LATTICRA_SEAL_SIGNING_OPERATION_IMPLEMENTATION.md

$CC $CFLAGS -Iinclude src/seal_signing_operation.c tests/seal_signing_operation_invariants.c -o "$tmpdir/latticra-seal-signing-operation-invariants"
"$tmpdir/latticra-seal-signing-operation-invariants"
