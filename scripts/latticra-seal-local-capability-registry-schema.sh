#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-seal-local-capability-registry-schema.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/seal_local_capability_registry_schema.c \
  tests/seal_local_capability_registry_schema_surface.c \
  -o "$tmpdir/latticra-seal-local-capability-registry-schema"

"$tmpdir/latticra-seal-local-capability-registry-schema"
