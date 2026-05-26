#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-runtime-boundary.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

for test_file in tests/runtime_boundary_*.c; do
  test_name=$(basename "$test_file" .c)
  test_bin="$tmpdir/$test_name"

  cc $CFLAGS -Wno-unused-function \
    -Iinclude \
    src/lat_parser.c \
    src/runtime_boundary.c \
    src/runtime_boundary_domain_matrix.c \
    src/runtime_boundary_domain_matrix_eval.c \
    src/runtime_boundary_domain_matrix_report.c \
    src/nucleus_task.c \
    src/nucleus_preview.c \
    src/state_lattice.c \
    "$test_file" \
    -o "$test_bin"

  "$test_bin"
done
