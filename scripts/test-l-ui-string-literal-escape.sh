#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/l_ui_parser.c \
  src/l_ui_parser_ast.c \
  tests/l_ui_string_literal_escape_invariants.c \
  -o /tmp/latticra-l-ui-string-literal-escape-invariants

/tmp/latticra-l-ui-string-literal-escape-invariants
