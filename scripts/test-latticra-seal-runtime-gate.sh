#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/seal_runtime_gate.c \
  src/seal_policy_decision.c \
  src/seal_signed_request.c \
  src/seal_request_freshness.c \
  src/seal_parameter_schema.c \
  src/seal_agentic_automation_security.c \
  src/seal_status_rollup.c \
  tests/seal_runtime_gate_invariants.c \
  -o /tmp/latticra-seal-runtime-gate-invariants

/tmp/latticra-seal-runtime-gate-invariants
