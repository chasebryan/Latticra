#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-verified-capability-gate.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS -Iinclude src/seal_verified_capability_gate.c tests/seal_verified_capability_gate_invariants.c -o "$tmpdir/latticra-seal-verified-capability-gate-invariants"
"$tmpdir/latticra-seal-verified-capability-gate-invariants"
