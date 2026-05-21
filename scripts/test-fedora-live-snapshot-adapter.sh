#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/fedora_host_install_preflight.c \
  src/fedora_install_preflight_snapshot.c \
  src/fedora_live_snapshot_adapter.c \
  tests/fedora_live_snapshot_adapter.c \
  -o /tmp/latticra-fedora-live-snapshot-adapter

/tmp/latticra-fedora-live-snapshot-adapter

printf 'fedora_live_snapshot_adapter: ok\n'
