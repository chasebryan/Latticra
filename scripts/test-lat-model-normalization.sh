#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-lat-model-normalization.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/lat_parser.c \
  src/lat_semantic.c \
  src/lat_model.c \
  tests/lat_model_normalization_invariants.c \
  -o "$tmpdir/latticra-lat-model-normalization-invariants"

"$tmpdir/latticra-lat-model-normalization-invariants"
