#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/state_lattice.c \
  src/nucleus_preview.c \
  src/l_ui_static_report.c \
  tests/l_ui_static_report_invariants.c \
  -o /tmp/latticra-l-ui-static-report-invariants

/tmp/latticra-l-ui-static-report-invariants
