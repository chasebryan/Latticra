#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/l_ui_parser.c \
  tests/l_ui_parser_location_invariants.c \
  -o /tmp/latticra-l-ui-parser-location-invariants

/tmp/latticra-l-ui-parser-location-invariants
