#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-lir-shape.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/l_ui_parser.c \
  src/l_ui_parser_ast.c \
  src/l_ui_parser_diagnostics.c \
  src/l_ui_parser_semantic.c \
  src/lir.c \
  tests/lir_shape_invariants.c \
  -o "$tmpdir/latticra-lir-shape-invariants"

"$tmpdir/latticra-lir-shape-invariants"

cc $CFLAGS \
  -Iinclude \
  src/l_ui_parser.c \
  src/l_ui_parser_ast.c \
  src/l_ui_parser_diagnostics.c \
  src/l_ui_parser_semantic.c \
  src/lir.c \
  tests/lir_report_refinement.c \
  -o "$tmpdir/latticra-lir-report-refinement"

"$tmpdir/latticra-lir-report-refinement"
