#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-measurement.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/seal_measurement.c \
  tests/seal_measurement_invariants.c \
  -o "$tmpdir/latticra-seal-measurement-invariants"

"$tmpdir/latticra-seal-measurement-invariants"

cc $CFLAGS \
  -Iinclude \
  src/seal_report.c \
  tests/seal_report_invariants.c \
  -o "$tmpdir/latticra-seal-report-invariants"

"$tmpdir/latticra-seal-report-invariants"
