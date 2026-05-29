#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-l-ui-rendering.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/l_ui_parser.c \
  src/l_ui_parser_ast.c \
  src/l_ui_parser_diagnostics.c \
  src/l_ui_parser_semantic.c \
  src/lir.c \
  src/l_ui_renderer.c \
  tests/l_ui_rendering_invariants.c \
  -o "$tmpdir/latticra-l-ui-rendering-invariants"

"$tmpdir/latticra-l-ui-rendering-invariants"
