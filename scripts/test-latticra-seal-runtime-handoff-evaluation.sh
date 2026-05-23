#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS -Iinclude src/seal_runtime_handoff_evaluation.c tests/seal_runtime_handoff_evaluation_invariants.c -o /tmp/latticra-seal-runtime-handoff-evaluation-invariants
/tmp/latticra-seal-runtime-handoff-evaluation-invariants
