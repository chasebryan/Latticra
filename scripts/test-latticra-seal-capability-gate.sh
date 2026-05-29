#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-capability-gate.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal capability gate: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_contains 'bounded_string_is' src/seal_capability_gate.c
require_contains 'unterminated receipt status' tests/seal_capability_gate_invariants.c
require_contains 'authority capability gate render rejected' tests/seal_capability_gate_invariants.c
require_contains 'flag capability gate render rejected' tests/seal_capability_gate_invariants.c
require_contains 'unterminated requested scope -> invalid-scope without copying caller bytes' docs/LATTICRA_SEAL_CAPABILITY_GATE_IMPLEMENTATION.md

$CC $CFLAGS \
  -Iinclude \
  src/seal_capability_gate.c \
  tests/seal_capability_gate_invariants.c \
  -o "$tmpdir/latticra-seal-capability-gate-invariants"

"$tmpdir/latticra-seal-capability-gate-invariants"
