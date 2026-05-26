#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'kernel_preemption: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_file docs/KERNEL_PREEMPTION_SEED.md
require_file .github/workflows/kernel-preemption.yml
require_file scripts/test-kernel-preemption-report-runner.sh

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-kernel-preemption.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM
bin="$tmpdir/latticra-kernel-preemption"

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
  src/kernel_run_queue.c \
  src/kernel_context_switch.c \
  src/kernel_time_accounting.c \
  src/kernel_preemption.c \
  tests/kernel_preemption.c \
  -o "$bin"

"$bin"
