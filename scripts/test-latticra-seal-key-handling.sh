#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror}"

$CC $CFLAGS -Iinclude src/seal_key_handling.c tests/seal_key_handling_invariants.c -o /tmp/latticra-seal-key-handling-invariants
/tmp/latticra-seal-key-handling-invariants
