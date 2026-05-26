#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/test-fedora-disposable-vm-effect-gate-classifier.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

cc $CFLAGS \
  -Iinclude \
  src/fedora_disposable_vm_effect_gate.c \
  tests/fedora_disposable_vm_effect_gate.c \
  -o "$tmpdir/latticra-fedora-disposable-vm-effect-gate"

"$tmpdir/latticra-fedora-disposable-vm-effect-gate"

printf 'fedora_disposable_vm_effect_gate_classifier: ok\n'
