#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS -Wno-unused-function \
  -Iinclude \
  src/runtime_boundary.c \
  src/runtime_boundary_domain_matrix.c \
  src/runtime_boundary_domain_matrix_report.c \
  src/nucleus_task.c \
  src/nucleus_preview.c \
  src/state_lattice.c \
  tests/runtime_boundary_domain_matrix_report_integration.c \
  -o /tmp/latticra-rbdm-report-integration

/tmp/latticra-rbdm-report-integration
