#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-signing-operation.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

$CC $CFLAGS -Iinclude src/seal_signing_operation.c tests/seal_signing_operation_invariants.c -o "$tmpdir/latticra-seal-signing-operation-invariants"
"$tmpdir/latticra-seal-signing-operation-invariants"
