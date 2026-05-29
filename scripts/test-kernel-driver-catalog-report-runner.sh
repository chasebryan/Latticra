#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-kernel-driver-catalog-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

report_bin="$tmpdir/latticra-kernel-driver-catalog-report"
report_txt="$tmpdir/latticra-kernel-driver-catalog-report.txt"

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
  tools/kernel_driver_catalog_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"

grep -Fq 'LATTICRA KERNEL DRIVER CATALOG REPORT' "$report_txt"
grep -Fq 'catalog_status=driver-catalog-seed-ready' "$report_txt"
grep -Fq 'policy_status=report-only' "$report_txt"
grep -Fq 'device_registry_status=device-registry-seed-ready' "$report_txt"
grep -Fq 'driver_count=4' "$report_txt"
grep -Fq 'driver_probe_allowed=0' "$report_txt"
grep -Fq 'driver_load_allowed=0' "$report_txt"
grep -Fq 'driver_bind_allowed=0' "$report_txt"
grep -Fq 'interrupt_allowed=0' "$report_txt"
grep -Fq 'dma_allowed=0' "$report_txt"
grep -Fq 'hardware_effect_allowed=0' "$report_txt"
grep -Fq 'host_effect_allowed=0' "$report_txt"
grep -Fq 'driver[0].name=console-driver-metadata' "$report_txt"
grep -Fq 'driver[1].device_class=block-device' "$report_txt"
grep -Fq 'driver[3].driver_class=monotonic-clock-driver' "$report_txt"
grep -Fq 'driver[0].loaded=0' "$report_txt"
grep -Fq 'driver[0].bound=0' "$report_txt"
grep -Fq 'driver[0].no_effect=1' "$report_txt"

printf 'kernel_driver_catalog_report_runner: ok\n'
