#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-fedora-rpm-gate-classifier.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/fedora_host_install_preflight.c \
  src/fedora_rpm_gate.c \
  tests/fedora_rpm_gate.c \
  -o "$tmpdir/latticra-fedora-rpm-gate"

"$tmpdir/latticra-fedora-rpm-gate"

printf 'fedora_rpm_gate_classifier: ok\n'
