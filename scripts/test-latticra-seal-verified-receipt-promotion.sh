#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS -Iinclude src/seal_verified_receipt_promotion.c tests/seal_verified_receipt_promotion_invariants.c -o /tmp/latticra-seal-verified-receipt-promotion-invariants
/tmp/latticra-seal-verified-receipt-promotion-invariants
