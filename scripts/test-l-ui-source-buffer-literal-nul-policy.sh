#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/l_ui_parser.c \
  src/l_ui_parser_ast.c \
  src/l_ui_parser_diagnostics.c \
  tests/l_ui_source_buffer_literal_nul_policy_invariants.c \
  -o /tmp/latticra-l-ui-source-buffer-literal-nul-policy-invariants

/tmp/latticra-l-ui-source-buffer-literal-nul-policy-invariants
