#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-signer-invocation.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

$CC $CFLAGS -Iinclude src/seal_signer_invocation.c tests/seal_signer_invocation_invariants.c -o "$tmpdir/latticra-seal-signer-invocation-invariants"
"$tmpdir/latticra-seal-signer-invocation-invariants"
