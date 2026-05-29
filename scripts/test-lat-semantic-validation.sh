#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-lat-semantic-validation.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/lat_parser.c \
  src/lat_semantic.c \
  tests/lat_semantic_validation_invariants.c \
  -o "$tmpdir/latticra-lat-semantic-validation-invariants"

"$tmpdir/latticra-lat-semantic-validation-invariants"

cc $CFLAGS \
  -Iinclude \
  src/lat_parser.c \
  src/lat_semantic.c \
  tests/lat_semantic_diagnostics_refinement.c \
  -o "$tmpdir/latticra-lat-semantic-diagnostics-refinement"

"$tmpdir/latticra-lat-semantic-diagnostics-refinement"
