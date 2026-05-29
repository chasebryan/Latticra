#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-seal-guarded-allowlist-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/seal_guarded_allowlist.c \
  tests/seal_guarded_allowlist_report_surface.c \
  -o "$tmpdir/latticra-seal-guarded-allowlist-report"

"$tmpdir/latticra-seal-guarded-allowlist-report"
