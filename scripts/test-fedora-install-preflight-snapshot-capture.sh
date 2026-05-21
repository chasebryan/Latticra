#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/fedora_host_install_preflight.c \
  src/fedora_install_preflight_snapshot.c \
  tests/fedora_install_preflight_snapshot.c \
  -o /tmp/latticra-fedora-install-preflight-snapshot

/tmp/latticra-fedora-install-preflight-snapshot

printf 'fedora_install_preflight_snapshot_capture: ok\n'
