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
  src/l_ui_renderer.c \
  tests/l_ui_rendering_detailed_report_refinement.c \
  -o /tmp/latticra-l-ui-rendering-detailed-report-refinement

/tmp/latticra-l-ui-rendering-detailed-report-refinement
