#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/seal_guarded_allowlist.c \
  tests/seal_guarded_allowlist_report_surface.c \
  -o /tmp/latticra-seal-guarded-allowlist-report

/tmp/latticra-seal-guarded-allowlist-report
