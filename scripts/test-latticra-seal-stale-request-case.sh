#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-latticra-seal-stale-request-case.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/seal_runtime_gate.c \
  src/seal_policy_decision.c \
  src/seal_signed_request.c \
  src/seal_request_freshness.c \
  src/seal_parameter_schema.c \
  src/seal_agentic_automation_security.c \
  src/seal_status_rollup.c \
  tests/seal_stale_request_case.c \
  -o "$tmpdir/latticra-seal-stale-request-case"

"$tmpdir/latticra-seal-stale-request-case"
