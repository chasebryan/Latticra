#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-fedora-live-snapshot-adapter.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/fedora_host_install_preflight.c \
  src/fedora_install_preflight_snapshot.c \
  src/fedora_live_snapshot_adapter.c \
  tests/fedora_live_snapshot_adapter.c \
  -o "$tmpdir/latticra-fedora-live-snapshot-adapter"

"$tmpdir/latticra-fedora-live-snapshot-adapter"

printf 'fedora_live_snapshot_adapter: ok\n'
