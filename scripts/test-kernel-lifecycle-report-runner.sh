#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
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
  src/kernel_lifecycle.c \
  tools/kernel_lifecycle_report.c \
  -o /tmp/latticra-kernel-lifecycle-report

/tmp/latticra-kernel-lifecycle-report > /tmp/latticra-kernel-lifecycle-report.txt

grep -Fq 'LATTICRA KERNEL LIFECYCLE REPORT' /tmp/latticra-kernel-lifecycle-report.txt
grep -Fq 'lifecycle_status=lifecycle-complete' /tmp/latticra-kernel-lifecycle-report.txt
grep -Fq 'policy_status=gate-allowed' /tmp/latticra-kernel-lifecycle-report.txt
grep -Fq 'final_state=memory-map-ready' /tmp/latticra-kernel-lifecycle-report.txt
grep -Fq 'step_count=4' /tmp/latticra-kernel-lifecycle-report.txt
grep -Fq 'state_change_count=4' /tmp/latticra-kernel-lifecycle-report.txt
grep -Fq 'lifecycle_complete=1' /tmp/latticra-kernel-lifecycle-report.txt
grep -Fq 'external_effect_performed=0' /tmp/latticra-kernel-lifecycle-report.txt
grep -Fq 'machine_log_count=4' /tmp/latticra-kernel-lifecycle-report.txt
grep -Fq 'evidence_level=10' /tmp/latticra-kernel-lifecycle-report.txt
grep -Fq 'log[0].from=created' /tmp/latticra-kernel-lifecycle-report.txt
grep -Fq 'log[0].to=initialized' /tmp/latticra-kernel-lifecycle-report.txt
grep -Fq 'log[0].status=machine-mutated' /tmp/latticra-kernel-lifecycle-report.txt
grep -Fq 'log[3].from=scheduler-ready' /tmp/latticra-kernel-lifecycle-report.txt
grep -Fq 'log[3].to=memory-map-ready' /tmp/latticra-kernel-lifecycle-report.txt
grep -Fq 'log[3].state_change_performed=1' /tmp/latticra-kernel-lifecycle-report.txt
grep -Fq 'log[3].external_effect_performed=0' /tmp/latticra-kernel-lifecycle-report.txt

printf 'kernel_lifecycle_report_runner: ok\n'
