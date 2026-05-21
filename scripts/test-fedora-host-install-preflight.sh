#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/fedora_host_install_preflight.c \
  tests/fedora_host_install_preflight.c \
  -o /tmp/latticra-fedora-host-install-preflight

/tmp/latticra-fedora-host-install-preflight

printf 'fedora_host_install_preflight: ok\n'
