#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror}"

$CC $CFLAGS -Iinclude src/seal_key_handling.c src/seal_key_material.c src/seal_public_key_parsing.c src/seal_key_parsing.c tests/seal_key_parsing_invariants.c -o /tmp/latticra-seal-key-parsing-invariants
/tmp/latticra-seal-key-parsing-invariants
