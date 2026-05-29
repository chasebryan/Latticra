#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-verified-effect-decision.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS -Iinclude src/seal_verified_effect_decision.c tests/seal_verified_effect_decision_invariants.c -o "$tmpdir/latticra-seal-verified-effect-decision-invariants"
"$tmpdir/latticra-seal-verified-effect-decision-invariants"
