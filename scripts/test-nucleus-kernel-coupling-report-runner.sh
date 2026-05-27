#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-nucleus-kernel-coupling-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

report_bin="$tmpdir/latticra-nucleus-kernel-coupling-report"
report_txt="$tmpdir/latticra-nucleus-kernel-coupling-report.txt"

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
  tools/nucleus_kernel_coupling_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"

grep -Fq 'LATTICRA NUCLEUS KERNEL COUPLING REPORT' "$report_txt"
grep -Fq 'classification=report-only-ready' "$report_txt"
grep -Fq 'reason=ok' "$report_txt"
grep -Fq 'readiness_status=nucleus-kernel-coupling-ready' "$report_txt"
grep -Fq 'os_readiness_status=os-metadata-ready' "$report_txt"
grep -Fq 'nucleus_plan_status=allow-no-effect-sequence' "$report_txt"
grep -Fq 'kernel_registry_status=registry-ready' "$report_txt"
grep -Fq 'kernel_status=initialized-report-only' "$report_txt"
grep -Fq 'runtime_register_view_status=runtime-entry-register-view-seed-ready' "$report_txt"
grep -Fq 'runtime_entry_frame_status=runtime-entry-frame-seed-ready' "$report_txt"
grep -Fq 'scheduler_run_entry_status=scheduler-run-entry-seed-ready' "$report_txt"
grep -Fq 'task_count=1' "$report_txt"
grep -Fq 'accepted_task_count=1' "$report_txt"
grep -Fq 'blocked_task_count=0' "$report_txt"
grep -Fq 'subsystem_count=9' "$report_txt"
grep -Fq 'register_view_count=4' "$report_txt"
grep -Fq 'prerequisites_satisfied=1' "$report_txt"
grep -Fq 'no_effect_chain_ok=1' "$report_txt"
grep -Fq 'report_only=1' "$report_txt"
grep -Fq 'execution_allowed=0' "$report_txt"
grep -Fq 'network_allowed=0' "$report_txt"
grep -Fq 'boot_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_allowed=0' "$report_txt"
grep -Fq 'scheduler_run_entry_allowed=0' "$report_txt"
grep -Fq 'context_switch_allowed=0' "$report_txt"
grep -Fq 'register_save_allowed=0' "$report_txt"
grep -Fq 'register_restore_allowed=0' "$report_txt"
grep -Fq 'host_effect_allowed=0' "$report_txt"
grep -Fq 'evidence_level=30' "$report_txt"

printf 'nucleus_kernel_coupling_report_runner: ok\n'
