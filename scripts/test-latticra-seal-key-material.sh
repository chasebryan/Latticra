#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-key-material.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal key material: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_contains 'bounded_string_is' src/seal_key_material.c
require_contains 'unterminated requested key material status' tests/seal_key_material_invariants.c
require_contains 'authority key material render rejected' tests/seal_key_material_invariants.c
require_contains 'ready flag key material render rejected' tests/seal_key_material_invariants.c
require_contains 'unterminated requested key material -> denied-key-material without copying caller bytes' docs/LATTICRA_SEAL_KEY_MATERIAL_IMPLEMENTATION.md

$CC $CFLAGS -Iinclude src/seal_key_handling.c src/seal_key_material.c tests/seal_key_material_invariants.c -o "$tmpdir/latticra-seal-key-material-invariants"
"$tmpdir/latticra-seal-key-material-invariants"
