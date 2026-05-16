#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/l_ui_parser.c \
  src/l_ui_parser_ast.c \
  src/l_ui_parser_diagnostics.c \
  src/l_ui_parser_semantic.c \
  tests/l_ui_semantic_validation_invariants.c \
  -o /tmp/latticra-l-ui-semantic-validation-invariants

/tmp/latticra-l-ui-semantic-validation-invariants
