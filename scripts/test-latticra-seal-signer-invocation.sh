#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror}"

$CC $CFLAGS -Iinclude src/seal_signer_invocation.c tests/seal_signer_invocation_invariants.c -o /tmp/latticra-seal-signer-invocation-invariants
/tmp/latticra-seal-signer-invocation-invariants
