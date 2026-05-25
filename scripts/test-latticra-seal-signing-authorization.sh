#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror}"

$CC $CFLAGS -Iinclude src/seal_signing_authorization.c tests/seal_signing_authorization_invariants.c -o /tmp/latticra-seal-signing-authorization-invariants
/tmp/latticra-seal-signing-authorization-invariants
