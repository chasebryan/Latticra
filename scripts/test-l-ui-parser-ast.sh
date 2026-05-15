#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/l_ui_parser.c \
  src/l_ui_parser_ast.c \
  tests/l_ui_parser_ast_invariants.c \
  -o /tmp/latticra-l-ui-parser-ast-invariants

/tmp/latticra-l-ui-parser-ast-invariants
