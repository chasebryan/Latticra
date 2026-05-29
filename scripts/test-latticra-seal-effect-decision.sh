#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-effect-decision.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal effect decision: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_contains 'bounded_string_is' src/seal_effect_decision.c
require_contains 'unterminated gate status' tests/seal_effect_decision_invariants.c
require_contains 'authority effect decision render rejected' tests/seal_effect_decision_invariants.c
require_contains 'flag effect decision render rejected' tests/seal_effect_decision_invariants.c
require_contains 'unterminated capability gate metadata strings -> invalid-gate' docs/LATTICRA_SEAL_EFFECT_DECISION_IMPLEMENTATION.md

$CC $CFLAGS \
  -Iinclude \
  src/seal_effect_decision.c \
  tests/seal_effect_decision_invariants.c \
  -o "$tmpdir/latticra-seal-effect-decision-invariants"

"$tmpdir/latticra-seal-effect-decision-invariants"
