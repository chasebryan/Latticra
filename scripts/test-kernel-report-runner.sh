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
  tools/kernel_report.c \
  -o /tmp/latticra-kernel-report

/tmp/latticra-kernel-report > /tmp/latticra-kernel-report.txt

grep -Fq 'LATTICRA KERNEL REPORT' /tmp/latticra-kernel-report.txt
grep -Fq 'kernel_id=latticra-kernel-seed' /tmp/latticra-kernel-report.txt
grep -Fq 'kernel_status=initialized-report-only' /tmp/latticra-kernel-report.txt
grep -Fq 'boot_status=not-booted' /tmp/latticra-kernel-report.txt
grep -Fq 'runtime_status=not-entered' /tmp/latticra-kernel-report.txt
grep -Fq 'filesystem_status=disabled' /tmp/latticra-kernel-report.txt
grep -Fq 'network_status=disabled' /tmp/latticra-kernel-report.txt
grep -Fq 'device_status=disabled' /tmp/latticra-kernel-report.txt
grep -Fq 'no_effect=1' /tmp/latticra-kernel-report.txt

printf 'kernel_report_runner: ok\n'
