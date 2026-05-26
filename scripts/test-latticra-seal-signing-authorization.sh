#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-signing-authorization.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

$CC $CFLAGS -Iinclude src/seal_signing_authorization.c tests/seal_signing_authorization_invariants.c -o "$tmpdir/latticra-seal-signing-authorization-invariants"
"$tmpdir/latticra-seal-signing-authorization-invariants"
