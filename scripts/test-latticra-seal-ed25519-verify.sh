#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS -Iinclude src/seal_ed25519_verify.c tests/seal_ed25519_verify_invariants.c -lcrypto -o /tmp/latticra-seal-ed25519-verify-invariants
/tmp/latticra-seal-ed25519-verify-invariants
