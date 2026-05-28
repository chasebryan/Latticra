#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-capability-metadata.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra seal capability metadata: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_contains 'bounded_string_is' src/seal_capability_metadata.c
require_contains 'unterminated capability status' tests/seal_capability_metadata_invariants.c
require_contains 'authority result render rejected' tests/seal_capability_metadata_invariants.c
require_contains 'unterminated input strings fail closed before copy' docs/LATTICRA_SEAL_CAPABILITY_METADATA_IMPLEMENTATION.md

cc $CFLAGS \
  -Iinclude \
  src/seal_capability_metadata.c \
  tests/seal_capability_metadata_invariants.c \
  -o "$tmpdir/latticra-seal-capability-metadata-invariants"

"$tmpdir/latticra-seal-capability-metadata-invariants"
