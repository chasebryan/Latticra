#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/l_ui_parser.c \
  tests/l_ui_parser_fixture_integration.c \
  -o /tmp/latticra-l-ui-parser-fixture-integration

/tmp/latticra-l-ui-parser-fixture-integration
