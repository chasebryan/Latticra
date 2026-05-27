#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nucleus_kernel_coupling: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_file docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_file include/latticra/nucleus_kernel_coupling.h
require_file src/nucleus_kernel_coupling.c
require_file tests/nucleus_kernel_coupling.c
require_file scripts/test-nucleus-kernel-coupling-report-runner.sh

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-nucleus-kernel-coupling.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM
bin="$tmpdir/latticra-nucleus-kernel-coupling"

cc $CFLAGS \
  -Iinclude \
  src/state_lattice.c \
  src/nucleus_preview.c \
  src/nucleus_task.c \
  src/nucleus_task_plan.c \
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
  src/kernel_scheduler_credit.c \
  src/kernel_scheduler_selection.c \
  src/kernel_scheduler_dispatch.c \
  src/kernel_scheduler_handoff.c \
  src/kernel_scheduler_activation.c \
  src/kernel_scheduler_run_entry.c \
  src/kernel_runtime_entry_admission.c \
  src/kernel_runtime_entry_frame.c \
  src/kernel_runtime_entry_register_view.c \
  src/nucleus_kernel_coupling.c \
  tests/nucleus_kernel_coupling.c \
  -o "$bin"

"$bin"
