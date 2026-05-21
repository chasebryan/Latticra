#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/fedora_disposable_vm_effect_gate.c \
  tests/fedora_disposable_vm_effect_gate.c \
  -o /tmp/latticra-fedora-disposable-vm-effect-gate

/tmp/latticra-fedora-disposable-vm-effect-gate

printf 'fedora_disposable_vm_effect_gate_classifier: ok\n'
