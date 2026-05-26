#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-kernel-interrupt-table-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

report_bin="$tmpdir/latticra-kernel-interrupt-table-report"
report_txt="$tmpdir/latticra-kernel-interrupt-table-report.txt"

cc $CFLAGS \
  -Iinclude \
  src/state_lattice.c \
  src/nucleus_preview.c \
  src/nucleus_task.c \
  src/lat_parser.c \
  src/runtime_boundary.c \
  src/system_bootstrap.c \
  src/kernel.c \
  src/kernel_subsystem_registry.c \
  src/kernel_scheduler.c \
  src/kernel_memory_map.c \
  src/kernel_process_table.c \
  src/kernel_syscall_table.c \
  src/kernel_ipc_table.c \
  src/kernel_vfs_namespace.c \
  src/kernel_device_registry.c \
  src/kernel_driver_catalog.c \
  src/kernel_interrupt_table.c \
  tools/kernel_interrupt_table_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"

grep -Fq 'LATTICRA KERNEL INTERRUPT TABLE REPORT' "$report_txt"
grep -Fq 'table_status=interrupt-table-seed-ready' "$report_txt"
grep -Fq 'policy_status=report-only' "$report_txt"
grep -Fq 'driver_catalog_status=driver-catalog-seed-ready' "$report_txt"
grep -Fq 'route_count=4' "$report_txt"
grep -Fq 'interrupt_mask_allowed=0' "$report_txt"
grep -Fq 'interrupt_unmask_allowed=0' "$report_txt"
grep -Fq 'interrupt_dispatch_allowed=0' "$report_txt"
grep -Fq 'interrupt_ack_allowed=0' "$report_txt"
grep -Fq 'dma_allowed=0' "$report_txt"
grep -Fq 'hardware_effect_allowed=0' "$report_txt"
grep -Fq 'host_effect_allowed=0' "$report_txt"
grep -Fq 'route[0].driver_name=console-driver-metadata' "$report_txt"
grep -Fq 'route[0].irq_vector=32' "$report_txt"
grep -Fq 'route[1].route_class=block-interrupt' "$report_txt"
grep -Fq 'route[3].route_class=timer-interrupt' "$report_txt"
grep -Fq 'route[0].connected=0' "$report_txt"
grep -Fq 'route[0].enabled=0' "$report_txt"
grep -Fq 'route[0].no_effect=1' "$report_txt"

printf 'kernel_interrupt_table_report_runner: ok\n'
