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
  src/kernel_lifecycle_subsystem_summary.c \
  tools/kernel_lifecycle_subsystem_summary_report.c \
  -o /tmp/latticra-kernel-lifecycle-subsystem-summary-report

/tmp/latticra-kernel-lifecycle-subsystem-summary-report > /tmp/latticra-kernel-lifecycle-subsystem-summary-report.txt

grep -Fq 'LATTICRA KERNEL LIFECYCLE SUBSYSTEM SUMMARY REPORT' /tmp/latticra-kernel-lifecycle-subsystem-summary-report.txt
grep -Fq 'summary_status=summary-ready' /tmp/latticra-kernel-lifecycle-subsystem-summary-report.txt
grep -Fq 'final_state=memory-map-ready' /tmp/latticra-kernel-lifecycle-subsystem-summary-report.txt
grep -Fq 'lifecycle_status=lifecycle-complete' /tmp/latticra-kernel-lifecycle-subsystem-summary-report.txt
grep -Fq 'registry_status=registry-ready' /tmp/latticra-kernel-lifecycle-subsystem-summary-report.txt
grep -Fq 'lifecycle_complete=1' /tmp/latticra-kernel-lifecycle-subsystem-summary-report.txt
grep -Fq 'lifecycle_step_count=4' /tmp/latticra-kernel-lifecycle-subsystem-summary-report.txt
grep -Fq 'lifecycle_state_change_count=4' /tmp/latticra-kernel-lifecycle-subsystem-summary-report.txt
grep -Fq 'lifecycle_state_mutated=1' /tmp/latticra-kernel-lifecycle-subsystem-summary-report.txt
grep -Fq 'external_effect_performed=0' /tmp/latticra-kernel-lifecycle-subsystem-summary-report.txt
grep -Fq 'registry_no_effect=1' /tmp/latticra-kernel-lifecycle-subsystem-summary-report.txt
grep -Fq 'runtime_entry_allowed=0' /tmp/latticra-kernel-lifecycle-subsystem-summary-report.txt
grep -Fq 'scheduler_execution_allowed=0' /tmp/latticra-kernel-lifecycle-subsystem-summary-report.txt
grep -Fq 'memory_allocation_allowed=0' /tmp/latticra-kernel-lifecycle-subsystem-summary-report.txt
grep -Fq 'no_external_effect_chain=1' /tmp/latticra-kernel-lifecycle-subsystem-summary-report.txt
grep -Fq 'entry_count=9' /tmp/latticra-kernel-lifecycle-subsystem-summary-report.txt
grep -Fq 'subsystem[0].name=boot' /tmp/latticra-kernel-lifecycle-subsystem-summary-report.txt
grep -Fq 'subsystem[0].lifecycle_relation=boot-sequence-seeded' /tmp/latticra-kernel-lifecycle-subsystem-summary-report.txt
grep -Fq 'subsystem[1].name=runtime' /tmp/latticra-kernel-lifecycle-subsystem-summary-report.txt
grep -Fq 'subsystem[1].authority_status=runtime-entry-denied' /tmp/latticra-kernel-lifecycle-subsystem-summary-report.txt
grep -Fq 'subsystem[2].lifecycle_relation=scheduler-ready-metadata' /tmp/latticra-kernel-lifecycle-subsystem-summary-report.txt
grep -Fq 'subsystem[2].authority_status=scheduler-execution-denied' /tmp/latticra-kernel-lifecycle-subsystem-summary-report.txt
grep -Fq 'subsystem[3].lifecycle_relation=memory-map-ready' /tmp/latticra-kernel-lifecycle-subsystem-summary-report.txt
grep -Fq 'subsystem[3].authority_status=memory-allocation-denied' /tmp/latticra-kernel-lifecycle-subsystem-summary-report.txt
grep -Fq 'subsystem[6].authority_status=network-denied' /tmp/latticra-kernel-lifecycle-subsystem-summary-report.txt
grep -Fq 'subsystem[7].authority_status=device-denied' /tmp/latticra-kernel-lifecycle-subsystem-summary-report.txt
grep -Fq 'subsystem[8].authority_status=not-production-boundary' /tmp/latticra-kernel-lifecycle-subsystem-summary-report.txt

printf 'kernel_lifecycle_subsystem_summary_report_runner: ok\n'
