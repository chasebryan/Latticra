#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/seal_guarded_allowlist.c \
  tests/seal_guarded_allowlist_invariants.c \
  -o /tmp/latticra-seal-guarded-allowlist-invariants

/tmp/latticra-seal-guarded-allowlist-invariants
