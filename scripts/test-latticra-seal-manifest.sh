#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/seal_manifest.c \
  tests/seal_manifest_invariants.c \
  -o /tmp/latticra-seal-manifest-invariants

/tmp/latticra-seal-manifest-invariants
