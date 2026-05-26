#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-l-ui-parser-fixture-integration.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/l_ui_parser.c \
  tests/l_ui_parser_fixture_integration.c \
  -o "$tmpdir/latticra-l-ui-parser-fixture-integration"

"$tmpdir/latticra-l-ui-parser-fixture-integration"
