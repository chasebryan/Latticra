#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-fedora-host-install-preflight.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/fedora_host_install_preflight.c \
  tests/fedora_host_install_preflight.c \
  -o "$tmpdir/latticra-fedora-host-install-preflight"

"$tmpdir/latticra-fedora-host-install-preflight"

printf 'fedora_host_install_preflight: ok\n'
