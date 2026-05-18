#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/lat_parser.c \
  src/lat_semantic.c \
  tests/lat_semantic_validation_invariants.c \
  -o /tmp/latticra-lat-semantic-validation-invariants

/tmp/latticra-lat-semantic-validation-invariants
