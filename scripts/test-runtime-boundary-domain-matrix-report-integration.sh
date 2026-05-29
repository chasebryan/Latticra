#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-rbdm-report-integration.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM
bin="$tmpdir/latticra-rbdm-report-integration"

cc $CFLAGS -Wno-unused-function \
  -Iinclude \
  src/lat_parser.c \
  src/runtime_boundary.c \
  src/runtime_boundary_domain_matrix.c \
  src/runtime_boundary_domain_matrix_report.c \
  src/nucleus_task.c \
  src/nucleus_preview.c \
  src/state_lattice.c \
  tests/runtime_boundary_domain_matrix_report_integration.c \
  -o "$bin"

"$bin"
