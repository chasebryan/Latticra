#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/lat_parser.c \
  src/lat_semantic.c \
  src/lat_model.c \
  src/lir.c \
  src/lat_to_lir.c \
  tests/lat_to_lir_clause_metadata_refinement.c \
  -o /tmp/latticra-lat-to-lir-clause-metadata-refinement

/tmp/latticra-lat-to-lir-clause-metadata-refinement
