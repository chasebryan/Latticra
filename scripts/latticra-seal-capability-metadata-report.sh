#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-seal-capability-metadata-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/seal_capability_metadata.c \
  tests/seal_capability_metadata_report_surface.c \
  -o "$tmpdir/latticra-seal-capability-metadata-report"

"$tmpdir/latticra-seal-capability-metadata-report"
