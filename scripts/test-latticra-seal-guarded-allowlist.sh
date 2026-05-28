#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-guarded-allowlist.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal guarded allowlist: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_contains 'bounded_string_is' src/seal_guarded_allowlist.c
require_contains 'unterminated tool status' tests/seal_guarded_allowlist_invariants.c
require_contains 'authority result render rejected' tests/seal_guarded_allowlist_invariants.c
require_contains 'unterminated input strings fail closed before copy' docs/LATTICRA_SEAL_GUARDED_ALLOWLIST_IMPLEMENTATION.md

cc $CFLAGS \
  -Iinclude \
  src/seal_guarded_allowlist.c \
  tests/seal_guarded_allowlist_invariants.c \
  -o "$tmpdir/latticra-seal-guarded-allowlist-invariants"

"$tmpdir/latticra-seal-guarded-allowlist-invariants"
