#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS -Iinclude src/seal_report_envelope.c tests/seal_report_envelope_invariants.c -o /tmp/latticra-seal-report-envelope-invariants
/tmp/latticra-seal-report-envelope-invariants
