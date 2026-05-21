#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/seal_effect_decision.c \
  tests/seal_effect_decision_invariants.c \
  -o /tmp/latticra-seal-effect-decision-invariants

/tmp/latticra-seal-effect-decision-invariants
