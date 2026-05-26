#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-l-ui-parser-source-span.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/l_ui_parser.c \
  src/l_ui_parser_diagnostics.c \
  tests/l_ui_parser_source_span_invariants.c \
  -o "$tmpdir/latticra-l-ui-parser-source-span-invariants"

"$tmpdir/latticra-l-ui-parser-source-span-invariants"
