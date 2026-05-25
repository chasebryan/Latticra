#!/usr/bin/env sh
set -eu

: "${CC:=cc}"
: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror}"

$CC $CFLAGS -Iinclude src/seal_signer_handoff.c tests/seal_signer_handoff_invariants.c -o /tmp/latticra-seal-signer-handoff-invariants
/tmp/latticra-seal-signer-handoff-invariants
