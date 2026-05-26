#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-l-ui-source-buffer-literal-nul-policy.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/l_ui_parser.c \
  src/l_ui_parser_ast.c \
  src/l_ui_parser_diagnostics.c \
  tests/l_ui_source_buffer_literal_nul_policy_invariants.c \
  -o "$tmpdir/latticra-l-ui-source-buffer-literal-nul-policy-invariants"

"$tmpdir/latticra-l-ui-source-buffer-literal-nul-policy-invariants"
