#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/l_ui_parser.c \
  src/l_ui_parser_ast.c \
  src/l_ui_parser_diagnostics.c \
  src/l_ui_parser_semantic.c \
  src/lir.c \
  tests/lir_shape_invariants.c \
  -o /tmp/latticra-lir-shape-invariants

/tmp/latticra-lir-shape-invariants

cc $CFLAGS \
  -Iinclude \
  src/l_ui_parser.c \
  src/l_ui_parser_ast.c \
  src/l_ui_parser_diagnostics.c \
  src/l_ui_parser_semantic.c \
  src/lir.c \
  tests/lir_report_refinement.c \
  -o /tmp/latticra-lir-report-refinement

/tmp/latticra-lir-report-refinement
