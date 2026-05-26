#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-report-envelope.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS -Iinclude src/seal_report_envelope.c tests/seal_report_envelope_invariants.c -o "$tmpdir/latticra-seal-report-envelope-invariants"
"$tmpdir/latticra-seal-report-envelope-invariants"
