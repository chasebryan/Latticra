#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'kernel_scheduler_tick: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_file docs/KERNEL_SCHEDULER_TICK_SEED.md
require_file .github/workflows/kernel-scheduler-tick.yml
require_file scripts/test-kernel-scheduler-tick-report-runner.sh

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-kernel-scheduler-tick.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM
bin="$tmpdir/latticra-kernel-scheduler-tick"

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
  src/kernel_timer_source.c \
  src/kernel_scheduler_tick.c \
  tests/kernel_scheduler_tick.c \
  -o "$bin"

"$bin"
