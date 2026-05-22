#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/seal_capability_metadata.c \
  tests/seal_capability_metadata_invariants.c \
  -o /tmp/latticra-seal-capability-metadata-invariants

/tmp/latticra-seal-capability-metadata-invariants
