#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/l_ui_parser.c \
  src/l_ui_parser_ast.c \
  src/l_ui_parser_diagnostics.c \
  tests/l_ui_ast_length_carrying_string_storage_invariants.c \
  -o /tmp/latticra-l-ui-ast-length-carrying-string-storage-invariants

/tmp/latticra-l-ui-ast-length-carrying-string-storage-invariants
