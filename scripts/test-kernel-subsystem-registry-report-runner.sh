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
  tools/kernel_subsystem_registry_report.c \
  -o /tmp/latticra-kernel-subsystem-registry-report

/tmp/latticra-kernel-subsystem-registry-report > /tmp/latticra-kernel-subsystem-registry-report.txt

grep -Fq 'LATTICRA KERNEL SUBSYSTEM REGISTRY REPORT' /tmp/latticra-kernel-subsystem-registry-report.txt
grep -Fq 'registry_status=registry-ready' /tmp/latticra-kernel-subsystem-registry-report.txt
grep -Fq 'kernel_status=initialized-report-only' /tmp/latticra-kernel-subsystem-registry-report.txt
grep -Fq 'entry_count=9' /tmp/latticra-kernel-subsystem-registry-report.txt
grep -Fq 'subsystem[0].name=boot' /tmp/latticra-kernel-subsystem-registry-report.txt
grep -Fq 'subsystem[2].name=scheduler' /tmp/latticra-kernel-subsystem-registry-report.txt
grep -Fq 'subsystem[3].name=memory' /tmp/latticra-kernel-subsystem-registry-report.txt
grep -Fq 'subsystem[8].name=security' /tmp/latticra-kernel-subsystem-registry-report.txt
grep -Fq 'no_effect=1' /tmp/latticra-kernel-subsystem-registry-report.txt

printf 'kernel_subsystem_registry_report_runner: ok\n'
