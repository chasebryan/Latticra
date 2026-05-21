#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/seal_verification_policy.c \
  tests/seal_verification_policy_invariants.c \
  -o /tmp/latticra-seal-verification-policy-invariants

/tmp/latticra-seal-verification-policy-invariants
