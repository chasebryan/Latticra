#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-kernel-lifecycle-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

report_bin="$tmpdir/latticra-kernel-lifecycle-report"
report_txt="$tmpdir/latticra-kernel-lifecycle-report.txt"

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
  src/kernel_state.c \
  src/kernel_state_machine.c \
  src/kernel_lifecycle.c \
  tools/kernel_lifecycle_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"

grep -Fq 'LATTICRA KERNEL LIFECYCLE REPORT' "$report_txt"
grep -Fq 'lifecycle_status=lifecycle-complete' "$report_txt"
grep -Fq 'policy_status=gate-allowed' "$report_txt"
grep -Fq 'final_state=context-switch-ready' "$report_txt"
grep -Fq 'step_count=15' "$report_txt"
grep -Fq 'state_change_count=15' "$report_txt"
grep -Fq 'lifecycle_complete=1' "$report_txt"
grep -Fq 'external_effect_performed=0' "$report_txt"
grep -Fq 'machine_log_count=15' "$report_txt"
grep -Fq 'evidence_level=10' "$report_txt"
grep -Fq 'log[0].from=created' "$report_txt"
grep -Fq 'log[0].to=initialized' "$report_txt"
grep -Fq 'log[0].status=machine-mutated' "$report_txt"
grep -Fq 'log[4].from=memory-map-ready' "$report_txt"
grep -Fq 'log[4].to=process-table-ready' "$report_txt"
grep -Fq 'log[5].from=process-table-ready' "$report_txt"
grep -Fq 'log[5].to=syscall-table-ready' "$report_txt"
grep -Fq 'log[6].from=syscall-table-ready' "$report_txt"
grep -Fq 'log[6].to=ipc-table-ready' "$report_txt"
grep -Fq 'log[7].from=ipc-table-ready' "$report_txt"
grep -Fq 'log[7].to=vfs-namespace-ready' "$report_txt"
grep -Fq 'log[7].state_change_performed=1' "$report_txt"
grep -Fq 'log[7].external_effect_performed=0' "$report_txt"
grep -Fq 'log[8].from=vfs-namespace-ready' "$report_txt"
grep -Fq 'log[8].to=device-registry-ready' "$report_txt"
grep -Fq 'log[8].state_change_performed=1' "$report_txt"
grep -Fq 'log[8].external_effect_performed=0' "$report_txt"
grep -Fq 'log[9].from=device-registry-ready' "$report_txt"
grep -Fq 'log[9].to=driver-catalog-ready' "$report_txt"
grep -Fq 'log[9].state_change_performed=1' "$report_txt"
grep -Fq 'log[9].external_effect_performed=0' "$report_txt"
grep -Fq 'log[10].from=driver-catalog-ready' "$report_txt"
grep -Fq 'log[10].to=interrupt-table-ready' "$report_txt"
grep -Fq 'log[10].state_change_performed=1' "$report_txt"
grep -Fq 'log[10].external_effect_performed=0' "$report_txt"
grep -Fq 'log[11].from=interrupt-table-ready' "$report_txt"
grep -Fq 'log[11].to=timer-source-ready' "$report_txt"
grep -Fq 'log[11].state_change_performed=1' "$report_txt"
grep -Fq 'log[11].external_effect_performed=0' "$report_txt"
grep -Fq 'log[12].from=timer-source-ready' "$report_txt"
grep -Fq 'log[12].to=scheduler-tick-ready' "$report_txt"
grep -Fq 'log[12].state_change_performed=1' "$report_txt"
grep -Fq 'log[12].external_effect_performed=0' "$report_txt"
grep -Fq 'log[13].from=scheduler-tick-ready' "$report_txt"
grep -Fq 'log[13].to=run-queue-ready' "$report_txt"
grep -Fq 'log[13].state_change_performed=1' "$report_txt"
grep -Fq 'log[13].external_effect_performed=0' "$report_txt"
grep -Fq 'log[14].from=run-queue-ready' "$report_txt"
grep -Fq 'log[14].to=context-switch-ready' "$report_txt"
grep -Fq 'log[14].state_change_performed=1' "$report_txt"
grep -Fq 'log[14].external_effect_performed=0' "$report_txt"

printf 'kernel_lifecycle_report_runner: ok\n'
