#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/l_ui_parser.c \
  src/l_ui_parser_ast.c \
  tests/l_ui_ast_source_backed_text_invariants.c \
  -o /tmp/latticra-l-ui-ast-source-backed-text-invariants

/tmp/latticra-l-ui-ast-source-backed-text-invariants
