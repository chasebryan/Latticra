#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-l-ui-semantic-validation.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/l_ui_parser.c \
  src/l_ui_parser_ast.c \
  src/l_ui_parser_diagnostics.c \
  src/l_ui_parser_semantic.c \
  tests/l_ui_semantic_validation_invariants.c \
  -o "$tmpdir/latticra-l-ui-semantic-validation-invariants"

"$tmpdir/latticra-l-ui-semantic-validation-invariants"
