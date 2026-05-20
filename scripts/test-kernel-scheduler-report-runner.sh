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
  tools/kernel_scheduler_report.c \
  -o /tmp/latticra-kernel-scheduler-report

/tmp/latticra-kernel-scheduler-report > /tmp/latticra-kernel-scheduler-report.txt

grep -Fq 'LATTICRA KERNEL SCHEDULER REPORT' /tmp/latticra-kernel-scheduler-report.txt
grep -Fq 'scheduler_status=scheduler-seed-ready' /tmp/latticra-kernel-scheduler-report.txt
grep -Fq 'policy_status=report-only' /tmp/latticra-kernel-scheduler-report.txt
grep -Fq 'registry_status=registry-ready' /tmp/latticra-kernel-scheduler-report.txt
grep -Fq 'slot_count=3' /tmp/latticra-kernel-scheduler-report.txt
grep -Fq 'slot[0].label=idle-metadata' /tmp/latticra-kernel-scheduler-report.txt
grep -Fq 'slot[0].selection_status=not-selected' /tmp/latticra-kernel-scheduler-report.txt
grep -Fq 'no_effect=1' /tmp/latticra-kernel-scheduler-report.txt

printf 'kernel_scheduler_report_runner: ok\n'
