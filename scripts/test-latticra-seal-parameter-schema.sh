#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/seal_parameter_schema.c \
  src/seal_agentic_automation_security.c \
  src/seal_status_rollup.c \
  tests/seal_parameter_schema_invariants.c \
  -o /tmp/latticra-seal-parameter-schema-invariants

/tmp/latticra-seal-parameter-schema-invariants
