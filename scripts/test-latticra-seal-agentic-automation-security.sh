#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-agentic-automation-security.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/seal_agentic_automation_security.c \
  src/seal_status_rollup.c \
  tests/seal_agentic_automation_security_invariants.c \
  -o "$tmpdir/latticra-seal-agentic-automation-security-invariants"

"$tmpdir/latticra-seal-agentic-automation-security-invariants"
