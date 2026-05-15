#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/l_ui_parser.c \
  tests/l_ui_ast_escaped_string_report_invariants.c \
  -o /tmp/latticra-l-ui-ast-escaped-string-report-invariants

/tmp/latticra-l-ui-ast-escaped-string-report-invariants
