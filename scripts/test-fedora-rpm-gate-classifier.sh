#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/fedora_host_install_preflight.c \
  src/fedora_rpm_gate.c \
  tests/fedora_rpm_gate.c \
  -o /tmp/latticra-fedora-rpm-gate

/tmp/latticra-fedora-rpm-gate

printf 'fedora_rpm_gate_classifier: ok\n'
