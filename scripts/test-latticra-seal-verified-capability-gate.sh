#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS -Iinclude src/seal_verified_capability_gate.c tests/seal_verified_capability_gate_invariants.c -o /tmp/latticra-seal-verified-capability-gate-invariants
/tmp/latticra-seal-verified-capability-gate-invariants
