#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-kernel-vfs-namespace-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

report_bin="$tmpdir/latticra-kernel-vfs-namespace-report"
report_txt="$tmpdir/latticra-kernel-vfs-namespace-report.txt"

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
  tools/kernel_vfs_namespace_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"

grep -Fq 'LATTICRA KERNEL VFS NAMESPACE REPORT' "$report_txt"
grep -Fq 'namespace_status=vfs-namespace-seed-ready' "$report_txt"
grep -Fq 'policy_status=report-only' "$report_txt"
grep -Fq 'ipc_table_status=ipc-table-seed-ready' "$report_txt"
grep -Fq 'syscall_table_status=syscall-table-seed-ready' "$report_txt"
grep -Fq 'mount_count=4' "$report_txt"
grep -Fq 'path_lookup_allowed=0' "$report_txt"
grep -Fq 'file_read_allowed=0' "$report_txt"
grep -Fq 'file_write_allowed=0' "$report_txt"
grep -Fq 'namespace_mutation_allowed=0' "$report_txt"
grep -Fq 'host_effect_allowed=0' "$report_txt"
grep -Fq 'mount[0].path=/' "$report_txt"
grep -Fq 'mount[1].path=/proc' "$report_txt"
grep -Fq 'mount[0].authority_status=filesystem-access-denied' "$report_txt"
grep -Fq 'no_effect=1' "$report_txt"

printf 'kernel_vfs_namespace_report_runner: ok\n'
