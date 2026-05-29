#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-runtime-handoff-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal runtime handoff report: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_contains 'bounded_string_is' src/seal_runtime_handoff_report.c
require_contains 'unterminated requested report status' tests/seal_runtime_handoff_report_invariants.c
require_contains 'authority report render rejected' tests/seal_runtime_handoff_report_invariants.c
require_contains 'ready flag report render rejected' tests/seal_runtime_handoff_report_invariants.c
require_contains 'unterminated requested report -> denied-unknown-report without copying caller bytes' docs/LATTICRA_SEAL_RUNTIME_HANDOFF_REPORT_IMPLEMENTATION.md

cc $CFLAGS -Iinclude src/seal_runtime_handoff_report.c tests/seal_runtime_handoff_report_invariants.c -o "$tmpdir/latticra-seal-runtime-handoff-report-invariants"
"$tmpdir/latticra-seal-runtime-handoff-report-invariants"
