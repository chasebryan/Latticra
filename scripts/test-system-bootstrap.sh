#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-system-bootstrap.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM
bin="$tmpdir/latticra-system-bootstrap"

cc $CFLAGS \
  -Iinclude \
  src/state_lattice.c \
  src/nucleus_preview.c \
  src/nucleus_task.c \
  src/lat_parser.c \
  src/runtime_boundary.c \
  src/system_bootstrap.c \
  tests/system_bootstrap.c \
  -o "$bin"

"$bin"
