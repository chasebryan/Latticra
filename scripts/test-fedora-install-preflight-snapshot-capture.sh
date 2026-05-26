#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-fedora-install-preflight-snapshot-capture.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/fedora_host_install_preflight.c \
  src/fedora_install_preflight_snapshot.c \
  tests/fedora_install_preflight_snapshot.c \
  -o "$tmpdir/latticra-fedora-install-preflight-snapshot"

"$tmpdir/latticra-fedora-install-preflight-snapshot"

printf 'fedora_install_preflight_snapshot_capture: ok\n'
