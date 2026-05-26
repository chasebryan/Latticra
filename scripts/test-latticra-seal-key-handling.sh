#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-key-handling.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

$CC $CFLAGS -Iinclude src/seal_key_handling.c tests/seal_key_handling_invariants.c -o "$tmpdir/latticra-seal-key-handling-invariants"
"$tmpdir/latticra-seal-key-handling-invariants"
