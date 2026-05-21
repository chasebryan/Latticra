#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/seal_measurement.c \
  tests/seal_measurement_invariants.c \
  -o /tmp/latticra-seal-measurement-invariants

/tmp/latticra-seal-measurement-invariants

cc $CFLAGS \
  -Iinclude \
  src/seal_report.c \
  tests/seal_report_invariants.c \
  -o /tmp/latticra-seal-report-invariants

/tmp/latticra-seal-report-invariants
