#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror}"

$CC $CFLAGS -Iinclude src/seal_signing_operation.c tests/seal_signing_operation_invariants.c -o /tmp/latticra-seal-signing-operation-invariants
/tmp/latticra-seal-signing-operation-invariants
