#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/l_ui_parser.c \
  tests/l_ui_parser_result_report_invariants.c \
  -o /tmp/latticra-l-ui-parser-result-report-invariants

/tmp/latticra-l-ui-parser-result-report-invariants
