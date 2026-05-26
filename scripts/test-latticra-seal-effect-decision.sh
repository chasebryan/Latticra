#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-effect-decision.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/seal_effect_decision.c \
  tests/seal_effect_decision_invariants.c \
  -o "$tmpdir/latticra-seal-effect-decision-invariants"

"$tmpdir/latticra-seal-effect-decision-invariants"
