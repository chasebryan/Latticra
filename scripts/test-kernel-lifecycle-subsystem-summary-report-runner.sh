#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-kernel-lifecycle-subsystem-summary-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

report_bin="$tmpdir/latticra-kernel-lifecycle-subsystem-summary-report"
report_txt="$tmpdir/latticra-kernel-lifecycle-subsystem-summary-report.txt"

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
  src/kernel_state.c \
  src/kernel_state_machine.c \
  src/kernel_lifecycle.c \
  src/kernel_lifecycle_subsystem_summary.c \
  tools/kernel_lifecycle_subsystem_summary_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"

grep -Fq 'LATTICRA KERNEL LIFECYCLE SUBSYSTEM SUMMARY REPORT' "$report_txt"
grep -Fq 'summary_status=summary-ready' "$report_txt"
grep -Fq 'final_state=interrupt-table-ready' "$report_txt"
grep -Fq 'lifecycle_status=lifecycle-complete' "$report_txt"
grep -Fq 'registry_status=registry-ready' "$report_txt"
grep -Fq 'lifecycle_complete=1' "$report_txt"
grep -Fq 'lifecycle_step_count=11' "$report_txt"
grep -Fq 'lifecycle_state_change_count=11' "$report_txt"
grep -Fq 'lifecycle_state_mutated=1' "$report_txt"
grep -Fq 'external_effect_performed=0' "$report_txt"
grep -Fq 'registry_no_effect=1' "$report_txt"
grep -Fq 'runtime_entry_allowed=0' "$report_txt"
grep -Fq 'scheduler_execution_allowed=0' "$report_txt"
grep -Fq 'memory_allocation_allowed=0' "$report_txt"
grep -Fq 'process_spawn_allowed=0' "$report_txt"
grep -Fq 'syscall_dispatch_allowed=0' "$report_txt"
grep -Fq 'ipc_send_allowed=0' "$report_txt"
grep -Fq 'ipc_receive_allowed=0' "$report_txt"
grep -Fq 'ipc_queue_mutation_allowed=0' "$report_txt"
grep -Fq 'filesystem_lookup_allowed=0' "$report_txt"
grep -Fq 'filesystem_read_allowed=0' "$report_txt"
grep -Fq 'filesystem_write_allowed=0' "$report_txt"
grep -Fq 'namespace_mutation_allowed=0' "$report_txt"
grep -Fq 'device_open_allowed=0' "$report_txt"
grep -Fq 'device_read_allowed=0' "$report_txt"
grep -Fq 'device_write_allowed=0' "$report_txt"
grep -Fq 'driver_probe_allowed=0' "$report_txt"
grep -Fq 'driver_load_allowed=0' "$report_txt"
grep -Fq 'driver_bind_allowed=0' "$report_txt"
grep -Fq 'interrupt_allowed=0' "$report_txt"
grep -Fq 'interrupt_mask_allowed=0' "$report_txt"
grep -Fq 'interrupt_unmask_allowed=0' "$report_txt"
grep -Fq 'interrupt_dispatch_allowed=0' "$report_txt"
grep -Fq 'interrupt_ack_allowed=0' "$report_txt"
grep -Fq 'dma_allowed=0' "$report_txt"
grep -Fq 'hardware_effect_allowed=0' "$report_txt"
grep -Fq 'no_external_effect_chain=1' "$report_txt"
grep -Fq 'entry_count=9' "$report_txt"
grep -Fq 'subsystem[0].name=boot' "$report_txt"
grep -Fq 'subsystem[0].lifecycle_relation=boot-sequence-seeded' "$report_txt"
grep -Fq 'subsystem[1].name=runtime' "$report_txt"
grep -Fq 'subsystem[1].authority_status=runtime-entry-denied' "$report_txt"
grep -Fq 'subsystem[2].lifecycle_relation=scheduler-ready-metadata' "$report_txt"
grep -Fq 'subsystem[2].authority_status=scheduler-execution-denied' "$report_txt"
grep -Fq 'subsystem[3].lifecycle_relation=memory-map-ready' "$report_txt"
grep -Fq 'subsystem[3].authority_status=memory-allocation-denied' "$report_txt"
grep -Fq 'subsystem[4].lifecycle_relation=ipc-table-ready' "$report_txt"
grep -Fq 'subsystem[4].authority_status=process-execution-denied' "$report_txt"
grep -Fq 'subsystem[5].lifecycle_relation=vfs-namespace-ready' "$report_txt"
grep -Fq 'subsystem[6].authority_status=network-denied' "$report_txt"
grep -Fq 'subsystem[6].lifecycle_relation=network-syscall-metadata-ready' "$report_txt"
grep -Fq 'subsystem[7].authority_status=device-denied' "$report_txt"
grep -Fq 'subsystem[7].lifecycle_relation=interrupt-table-ready' "$report_txt"
grep -Fq 'subsystem[8].authority_status=not-production-boundary' "$report_txt"

printf 'kernel_lifecycle_subsystem_summary_report_runner: ok\n'
