#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-kernel-device-registry-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

report_bin="$tmpdir/latticra-kernel-device-registry-report"
report_txt="$tmpdir/latticra-kernel-device-registry-report.txt"

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
  tools/kernel_device_registry_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"

grep -Fq 'LATTICRA KERNEL DEVICE REGISTRY REPORT' "$report_txt"
grep -Fq 'registry_status=device-registry-seed-ready' "$report_txt"
grep -Fq 'policy_status=report-only' "$report_txt"
grep -Fq 'vfs_namespace_status=vfs-namespace-seed-ready' "$report_txt"
grep -Fq 'ipc_table_status=ipc-table-seed-ready' "$report_txt"
grep -Fq 'syscall_table_status=syscall-table-seed-ready' "$report_txt"
grep -Fq 'process_table_status=process-table-seed-ready' "$report_txt"
grep -Fq 'memory_map_status=memory-map-seed-ready' "$report_txt"
grep -Fq 'device_count=4' "$report_txt"
grep -Fq 'device_open_allowed=0' "$report_txt"
grep -Fq 'device_read_allowed=0' "$report_txt"
grep -Fq 'device_write_allowed=0' "$report_txt"
grep -Fq 'driver_bind_allowed=0' "$report_txt"
grep -Fq 'hardware_effect_allowed=0' "$report_txt"
grep -Fq 'host_effect_allowed=0' "$report_txt"
grep -Fq 'device[0].path=/dev/console' "$report_txt"
grep -Fq 'device[1].class=block-device' "$report_txt"
grep -Fq 'device[3].label=clock-device-metadata' "$report_txt"
grep -Fq 'device[0].registered=0' "$report_txt"
grep -Fq 'no_effect=1' "$report_txt"

printf 'kernel_device_registry_report_runner: ok\n'
