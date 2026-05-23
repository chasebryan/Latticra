#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS -Iinclude src/seal_verified_effect_decision.c tests/seal_verified_effect_decision_invariants.c -o /tmp/latticra-seal-verified-effect-decision-invariants
/tmp/latticra-seal-verified-effect-decision-invariants
