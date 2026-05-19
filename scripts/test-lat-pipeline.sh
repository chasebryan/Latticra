#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/lat_parser.c \
  src/lat_semantic.c \
  src/lir.c \
  src/lat_to_lir.c \
  src/lat_pipeline.c \
  tests/lat_pipeline_invariants.c \
  -o /tmp/latticra-lat-pipeline-invariants

/tmp/latticra-lat-pipeline-invariants

cc $CFLAGS \
  -Iinclude \
  src/lat_parser.c \
  src/lat_semantic.c \
  src/lir.c \
  src/lat_to_lir.c \
  src/lat_pipeline.c \
  tests/lat_pipeline_hardening_invariants.c \
  -o /tmp/latticra-lat-pipeline-hardening-invariants

/tmp/latticra-lat-pipeline-hardening-invariants

cc $CFLAGS \
  -Iinclude \
  src/lat_parser.c \
  src/lat_semantic.c \
  src/lir.c \
  src/lat_to_lir.c \
  src/lat_pipeline.c \
  tests/lat_pipeline_report_refinement.c \
  -o /tmp/latticra-lat-pipeline-report-refinement

/tmp/latticra-lat-pipeline-report-refinement
