#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-signer-handoff.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal signer handoff: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_contains 'bounded_string_is' src/seal_signer_handoff.c
require_contains 'unterminated requested signer handoff status' tests/seal_signer_handoff_invariants.c
require_contains 'authority signer handoff render rejected' tests/seal_signer_handoff_invariants.c
require_contains 'ready flag signer handoff render rejected' tests/seal_signer_handoff_invariants.c
require_contains 'unterminated requested signer handoff -> denied-signer-handoff without copying caller bytes' docs/LATTICRA_SEAL_SIGNER_HANDOFF_IMPLEMENTATION.md

$CC $CFLAGS -Iinclude src/seal_signer_handoff.c tests/seal_signer_handoff_invariants.c -o "$tmpdir/latticra-seal-signer-handoff-invariants"
"$tmpdir/latticra-seal-signer-handoff-invariants"
