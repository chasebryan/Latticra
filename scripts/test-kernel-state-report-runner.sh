#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

cc $CFLAGS \
  -Iinclude \
  src/state_lattice.c \
  src/nucleus_preview.c \
  src/nucleus_task.c \
  src/runtime_boundary.c \
  src/system_bootstrap.c \
  src/kernel.c \
  src/kernel_subsystem_registry.c \
  src/kernel_scheduler.c \
  src/kernel_memory_map.c \
  src/kernel_state.c \
  tools/kernel_state_report.c \
  -o /tmp/latticra-kernel-state-report

/tmp/latticra-kernel-state-report > /tmp/latticra-kernel-state-report.txt

grep -Fq 'LATTICRA KERNEL STATE REPORT' /tmp/latticra-kernel-state-report.txt
grep -Fq 'state_status=changed' /tmp/latticra-kernel-state-report.txt
grep -Fq 'gate_status=allow' /tmp/latticra-kernel-state-report.txt
grep -Fq 'transition_status=transition-applied' /tmp/latticra-kernel-state-report.txt
grep -Fq 'effect_status=in-memory-state-change' /tmp/latticra-kernel-state-report.txt
grep -Fq 'previous_state=created' /tmp/latticra-kernel-state-report.txt
grep -Fq 'next_state=initialized' /tmp/latticra-kernel-state-report.txt
grep -Fq 'state_change_performed=1' /tmp/latticra-kernel-state-report.txt
grep -Fq 'external_effect_performed=0' /tmp/latticra-kernel-state-report.txt
grep -Fq 'denied=0' /tmp/latticra-kernel-state-report.txt

printf 'kernel_state_report_runner: ok\n'
