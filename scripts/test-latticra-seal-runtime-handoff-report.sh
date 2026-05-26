#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-runtime-handoff-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS -Iinclude src/seal_runtime_handoff_report.c tests/seal_runtime_handoff_report_invariants.c -o "$tmpdir/latticra-seal-runtime-handoff-report-invariants"
"$tmpdir/latticra-seal-runtime-handoff-report-invariants"
