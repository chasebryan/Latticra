#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/seal_capability_metadata.c \
  tests/seal_capability_metadata_report_surface.c \
  -o /tmp/latticra-seal-capability-metadata-report

/tmp/latticra-seal-capability-metadata-report
