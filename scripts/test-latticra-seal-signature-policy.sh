#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/seal_signature_policy.c \
  tests/seal_signature_policy_invariants.c \
  -o /tmp/latticra-seal-signature-policy-invariants

/tmp/latticra-seal-signature-policy-invariants
