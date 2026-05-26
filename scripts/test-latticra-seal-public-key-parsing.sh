#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-public-key-parsing.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

$CC $CFLAGS -Iinclude src/seal_key_handling.c src/seal_key_material.c src/seal_public_key_parsing.c tests/seal_public_key_parsing_invariants.c -o "$tmpdir/latticra-seal-public-key-parsing-invariants"
"$tmpdir/latticra-seal-public-key-parsing-invariants"
