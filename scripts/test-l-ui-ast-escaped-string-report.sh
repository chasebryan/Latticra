#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-l-ui-ast-escaped-string-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/l_ui_parser.c \
  tests/l_ui_ast_escaped_string_report_invariants.c \
  -o "$tmpdir/latticra-l-ui-ast-escaped-string-report-invariants"

"$tmpdir/latticra-l-ui-ast-escaped-string-report-invariants"
