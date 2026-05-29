#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-public-key-parsing.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal public-key parsing: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_contains 'bounded_string_is' src/seal_public_key_parsing.c
require_contains 'unterminated requested public key parsing status' tests/seal_public_key_parsing_invariants.c
require_contains 'authority public key parsing render rejected' tests/seal_public_key_parsing_invariants.c
require_contains 'ready flag public key parsing render rejected' tests/seal_public_key_parsing_invariants.c
require_contains 'unterminated requested public key parsing -> denied-public-key-parsing without copying caller bytes' docs/LATTICRA_SEAL_PUBLIC_KEY_PARSING_IMPLEMENTATION.md

$CC $CFLAGS -Iinclude src/seal_key_handling.c src/seal_key_material.c src/seal_public_key_parsing.c tests/seal_public_key_parsing_invariants.c -o "$tmpdir/latticra-seal-public-key-parsing-invariants"
"$tmpdir/latticra-seal-public-key-parsing-invariants"
