#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/fedora_manual_host_rc_decision.c \
  tests/fedora_manual_host_rc_decision.c \
  -o /tmp/latticra-fedora-manual-host-rc-decision

/tmp/latticra-fedora-manual-host-rc-decision

printf 'fedora_manual_host_rc_decision_classifier: ok\n'
