#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-seal-operator-receipt-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/seal_capability_metadata.c \
  src/seal_operator_receipt_report.c \
  tests/seal_operator_receipt_report_surface.c \
  -o "$tmpdir/latticra-seal-operator-receipt-report"

"$tmpdir/latticra-seal-operator-receipt-report"
