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
  tools/kernel_memory_map_report.c \
  -o /tmp/latticra-kernel-memory-map-report

/tmp/latticra-kernel-memory-map-report > /tmp/latticra-kernel-memory-map-report.txt

grep -Fq 'LATTICRA KERNEL MEMORY MAP REPORT' /tmp/latticra-kernel-memory-map-report.txt
grep -Fq 'map_status=memory-map-seed-ready' /tmp/latticra-kernel-memory-map-report.txt
grep -Fq 'policy_status=report-only' /tmp/latticra-kernel-memory-map-report.txt
grep -Fq 'scheduler_status=scheduler-seed-ready' /tmp/latticra-kernel-memory-map-report.txt
grep -Fq 'region_count=4' /tmp/latticra-kernel-memory-map-report.txt
grep -Fq 'mapping_allowed=0' /tmp/latticra-kernel-memory-map-report.txt
grep -Fq 'write_allowed=0' /tmp/latticra-kernel-memory-map-report.txt
grep -Fq 'execute_allowed=0' /tmp/latticra-kernel-memory-map-report.txt
grep -Fq 'region[0].label=kernel-text-metadata' /tmp/latticra-kernel-memory-map-report.txt
grep -Fq 'region[3].label=kernel-report-metadata' /tmp/latticra-kernel-memory-map-report.txt
grep -Fq 'no_effect=1' /tmp/latticra-kernel-memory-map-report.txt

printf 'kernel_memory_map_report_runner: ok\n'
