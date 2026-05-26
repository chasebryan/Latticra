#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-signer-handoff.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

$CC $CFLAGS -Iinclude src/seal_signer_handoff.c tests/seal_signer_handoff_invariants.c -o "$tmpdir/latticra-seal-signer-handoff-invariants"
"$tmpdir/latticra-seal-signer-handoff-invariants"
