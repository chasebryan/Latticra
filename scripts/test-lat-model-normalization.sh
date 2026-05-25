#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/lat_parser.c \
  src/lat_semantic.c \
  src/lat_model.c \
  tests/lat_model_normalization_invariants.c \
  -o /tmp/latticra-lat-model-normalization-invariants

/tmp/latticra-lat-model-normalization-invariants
