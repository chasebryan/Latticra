#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-runtime-handoff-evaluation.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal runtime handoff evaluation: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_contains 'bounded_string_is' src/seal_runtime_handoff_evaluation.c
require_contains 'unterminated requested handoff status' tests/seal_runtime_handoff_evaluation_invariants.c
require_contains 'authority evaluation render rejected' tests/seal_runtime_handoff_evaluation_invariants.c
require_contains 'eligible flag evaluation render rejected' tests/seal_runtime_handoff_evaluation_invariants.c
require_contains 'unterminated requested handoff -> denied-unknown-handoff without copying caller bytes' docs/LATTICRA_SEAL_RUNTIME_HANDOFF_EVALUATION_IMPLEMENTATION.md

cc $CFLAGS -Iinclude src/seal_runtime_handoff_evaluation.c tests/seal_runtime_handoff_evaluation_invariants.c -o "$tmpdir/latticra-seal-runtime-handoff-evaluation-invariants"
"$tmpdir/latticra-seal-runtime-handoff-evaluation-invariants"
