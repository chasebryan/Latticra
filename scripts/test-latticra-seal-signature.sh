#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/seal_signature.c \
  tests/seal_signature_invariants.c \
  -o /tmp/latticra-seal-signature-invariants

/tmp/latticra-seal-signature-invariants
