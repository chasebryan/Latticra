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
  src/kernel_state_machine.c \
  tools/kernel_state_machine_report.c \
  -o /tmp/latticra-kernel-state-machine-report

/tmp/latticra-kernel-state-machine-report > /tmp/latticra-kernel-state-machine-report.txt

grep -Fq 'LATTICRA KERNEL STATE MACHINE REPORT' /tmp/latticra-kernel-state-machine-report.txt
grep -Fq 'machine_status=initialized' /tmp/latticra-kernel-state-machine-report.txt
grep -Fq 'current_state=initialized' /tmp/latticra-kernel-state-machine-report.txt
grep -Fq 'log_count=1' /tmp/latticra-kernel-state-machine-report.txt
grep -Fq 'state_mutated=1' /tmp/latticra-kernel-state-machine-report.txt
grep -Fq 'external_effect_performed=0' /tmp/latticra-kernel-state-machine-report.txt
grep -Fq 'log[0].from=created' /tmp/latticra-kernel-state-machine-report.txt
grep -Fq 'log[0].to=initialized' /tmp/latticra-kernel-state-machine-report.txt
grep -Fq 'log[0].status=machine-mutated' /tmp/latticra-kernel-state-machine-report.txt
grep -Fq 'log[0].state_change_performed=1' /tmp/latticra-kernel-state-machine-report.txt

printf 'kernel_state_machine_report_runner: ok\n'
