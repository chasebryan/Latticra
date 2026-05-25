#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/seal_crypto_verify_backend.c \
  tests/seal_crypto_verify_backend_invariants.c \
  -o /tmp/latticra-seal-crypto-verify-backend-invariants

/tmp/latticra-seal-crypto-verify-backend-invariants
