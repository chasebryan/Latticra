#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-seal-agentic-automation-security-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/seal_agentic_automation_security.c \
  src/seal_status_rollup.c \
  tests/seal_agentic_automation_security_report_surface.c \
  -o "$tmpdir/latticra-seal-agentic-automation-security-report"

"$tmpdir/latticra-seal-agentic-automation-security-report"
