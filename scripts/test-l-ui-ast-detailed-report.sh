#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-l-ui-ast-detailed-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/l_ui_parser.c \
  src/l_ui_parser_ast.c \
  tests/l_ui_parser_ast_detailed_report_invariants.c \
  -o "$tmpdir/latticra-l-ui-ast-detailed-report-invariants"

"$tmpdir/latticra-l-ui-ast-detailed-report-invariants"
