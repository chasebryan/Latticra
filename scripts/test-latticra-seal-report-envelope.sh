#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-report-envelope.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'seal report envelope: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_contains 'bounded_string_is' src/seal_report_envelope.c
require_contains 'unterminated requested envelope status' tests/seal_report_envelope_invariants.c
require_contains 'authority envelope render rejected' tests/seal_report_envelope_invariants.c
require_contains 'ready flag envelope render rejected' tests/seal_report_envelope_invariants.c
require_contains 'unterminated requested envelope -> denied-unknown-envelope without copying caller bytes' docs/LATTICRA_SEAL_REPORT_ENVELOPE_IMPLEMENTATION.md

cc $CFLAGS -Iinclude src/seal_report_envelope.c tests/seal_report_envelope_invariants.c -o "$tmpdir/latticra-seal-report-envelope-invariants"
"$tmpdir/latticra-seal-report-envelope-invariants"
