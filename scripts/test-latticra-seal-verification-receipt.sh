#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/seal_verification_receipt.c \
  tests/seal_verification_receipt_invariants.c \
  -o /tmp/latticra-seal-verification-receipt-invariants

/tmp/latticra-seal-verification-receipt-invariants
