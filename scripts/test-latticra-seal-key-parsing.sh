#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-key-parsing.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal key parsing: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_contains 'bounded_string_is' src/seal_key_parsing.c
require_contains 'unterminated predecessor public key parsing status' tests/seal_key_parsing_invariants.c
require_contains 'authority key parsing render rejected' tests/seal_key_parsing_invariants.c
require_contains 'ready flag key parsing render rejected' tests/seal_key_parsing_invariants.c
require_contains 'unterminated predecessor public-key parsing strings -> invalid-predecessor without copying predecessor strings' docs/LATTICRA_SEAL_FUTURE_KEY_PARSING_IMPLEMENTATION.md

$CC $CFLAGS -Iinclude src/seal_key_handling.c src/seal_key_material.c src/seal_public_key_parsing.c src/seal_key_parsing.c tests/seal_key_parsing_invariants.c -o "$tmpdir/latticra-seal-key-parsing-invariants"
"$tmpdir/latticra-seal-key-parsing-invariants"
