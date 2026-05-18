#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/lat_parser.c \
  src/lat_semantic.c \
  src/lir.c \
  src/lat_to_lir.c \
  tests/lat_specific_lir_refinement_invariants.c \
  -o /tmp/latticra-lat-specific-lir-refinement-invariants

/tmp/latticra-lat-specific-lir-refinement-invariants
