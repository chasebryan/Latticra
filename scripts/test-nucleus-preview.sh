#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/nucleus_preview.c \
  tests/nucleus_preview_invariants.c \
  -o /tmp/latticra-nucleus-preview-invariants

/tmp/latticra-nucleus-preview-invariants
