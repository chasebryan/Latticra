#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-lat-language-grammar.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/lat_parser.c \
  tests/lat_language_grammar_invariants.c \
  -o "$tmpdir/latticra-lat-language-grammar-invariants"

"$tmpdir/latticra-lat-language-grammar-invariants"
