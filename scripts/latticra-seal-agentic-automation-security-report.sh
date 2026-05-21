#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/seal_agentic_automation_security.c \
  src/seal_status_rollup.c \
  tests/seal_agentic_automation_security_report_surface.c \
  -o /tmp/latticra-seal-agentic-automation-security-report

/tmp/latticra-seal-agentic-automation-security-report
