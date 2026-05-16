#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/lat_parser.c \
  tests/lat_language_grammar_invariants.c \
  -o /tmp/latticra-lat-language-grammar-invariants

/tmp/latticra-lat-language-grammar-invariants
