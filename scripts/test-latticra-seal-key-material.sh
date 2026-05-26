#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-key-material.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

$CC $CFLAGS -Iinclude src/seal_key_handling.c src/seal_key_material.c tests/seal_key_material_invariants.c -o "$tmpdir/latticra-seal-key-material-invariants"
"$tmpdir/latticra-seal-key-material-invariants"
