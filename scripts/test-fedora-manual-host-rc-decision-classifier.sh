#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-fedora-manual-host-rc-decision-classifier.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/fedora_manual_host_rc_decision.c \
  tests/fedora_manual_host_rc_decision.c \
  -o "$tmpdir/latticra-fedora-manual-host-rc-decision"

"$tmpdir/latticra-fedora-manual-host-rc-decision"

printf 'fedora_manual_host_rc_decision_classifier: ok\n'
