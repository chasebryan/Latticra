#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-kernel-runtime-entry-admission-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

report_bin="$tmpdir/latticra-kernel-runtime-entry-admission-report"
report_txt="$tmpdir/latticra-kernel-runtime-entry-admission-report.txt"

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
  src/kernel_scheduler_credit.c \
  src/kernel_scheduler_selection.c \
  src/kernel_scheduler_dispatch.c \
  src/kernel_scheduler_handoff.c \
  src/kernel_scheduler_activation.c \
  src/kernel_scheduler_run_entry.c \
  src/kernel_runtime_entry_admission.c \
  tools/kernel_runtime_entry_admission_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"

grep -Fq 'LATTICRA KERNEL RUNTIME ENTRY ADMISSION REPORT' "$report_txt"
grep -Fq 'admission_status=runtime-entry-admission-seed-ready' "$report_txt"
grep -Fq 'policy_status=report-only' "$report_txt"
grep -Fq 'scheduler_run_entry_status=scheduler-run-entry-seed-ready' "$report_txt"
grep -Fq 'scheduler_activation_status=scheduler-activation-seed-ready' "$report_txt"
grep -Fq 'scheduler_handoff_status=scheduler-handoff-seed-ready' "$report_txt"
grep -Fq 'scheduler_dispatch_status=scheduler-dispatch-seed-ready' "$report_txt"
grep -Fq 'scheduler_selection_status=scheduler-selection-seed-ready' "$report_txt"
grep -Fq 'admission_count=4' "$report_txt"
grep -Fq 'runtime_entry_admission_allowed=0' "$report_txt"
grep -Fq 'runtime_entry_allowed=0' "$report_txt"
grep -Fq 'scheduler_run_entry_allowed=0' "$report_txt"
grep -Fq 'dispatch_allowed=0' "$report_txt"
grep -Fq 'run_queue_mutation_allowed=0' "$report_txt"
grep -Fq 'context_switch_allowed=0' "$report_txt"
grep -Fq 'hardware_effect_allowed=0' "$report_txt"
grep -Fq 'host_effect_allowed=0' "$report_txt"
grep -Fq 'admission[0].process_label=kernel-report-process-metadata' "$report_txt"
grep -Fq 'admission[0].admission_class=kernel-report-runtime-entry-admission' "$report_txt"
grep -Fq 'admission[0].admission_rank=1' "$report_txt"
grep -Fq 'admission[0].admission_declared=1' "$report_txt"
grep -Fq 'admission[0].admission_planned=0' "$report_txt"
grep -Fq 'admission[0].admitted=0' "$report_txt"
grep -Fq 'admission[0].runtime_entry_entered=0' "$report_txt"
grep -Fq 'admission[0].execution_entered=0' "$report_txt"
grep -Fq 'admission[0].no_effect=1' "$report_txt"

printf 'kernel_runtime_entry_admission_report_runner: ok\n'
