#!/usr/bin/env sh
set -eu

: "${CFLAGS:=-std=c99 -Wall -Wextra -Werror -pedantic}"

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-kernel-scheduler-credit-report.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

report_bin="$tmpdir/latticra-kernel-scheduler-credit-report"
report_txt="$tmpdir/latticra-kernel-scheduler-credit-report.txt"

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
  tools/kernel_scheduler_credit_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"

grep -Fq 'LATTICRA KERNEL SCHEDULER CREDIT REPORT' "$report_txt"
grep -Fq 'credit_status=scheduler-credit-seed-ready' "$report_txt"
grep -Fq 'policy_status=report-only' "$report_txt"
grep -Fq 'preemption_status=preemption-seed-ready' "$report_txt"
grep -Fq 'time_accounting_status=time-accounting-seed-ready' "$report_txt"
grep -Fq 'context_switch_status=context-switch-seed-ready' "$report_txt"
grep -Fq 'run_queue_status=run-queue-seed-ready' "$report_txt"
grep -Fq 'scheduler_tick_status=scheduler-tick-seed-ready' "$report_txt"
grep -Fq 'timer_source_status=timer-source-seed-ready' "$report_txt"
grep -Fq 'credit_count=4' "$report_txt"
grep -Fq 'scheduler_credit_update_allowed=0' "$report_txt"
grep -Fq 'quota_update_allowed=0' "$report_txt"
grep -Fq 'cpu_usage_write_allowed=0' "$report_txt"
grep -Fq 'time_accounting_allowed=0' "$report_txt"
grep -Fq 'time_read_allowed=0' "$report_txt"
grep -Fq 'preemption_allowed=0' "$report_txt"
grep -Fq 'context_switch_allowed=0' "$report_txt"
grep -Fq 'dispatch_allowed=0' "$report_txt"
grep -Fq 'run_queue_mutation_allowed=0' "$report_txt"
grep -Fq 'process_wake_allowed=0' "$report_txt"
grep -Fq 'hardware_effect_allowed=0' "$report_txt"
grep -Fq 'host_effect_allowed=0' "$report_txt"
grep -Fq 'credit[0].process_label=kernel-report-process-metadata' "$report_txt"
grep -Fq 'credit[0].credit_class=kernel-report-scheduler-credit' "$report_txt"
grep -Fq 'credit[0].remaining_budget_ns=10000000' "$report_txt"
grep -Fq 'credit[0].scheduler_credit_ns=10000000' "$report_txt"
grep -Fq 'credit[0].quota_credit_ns=10000000' "$report_txt"
grep -Fq 'credit[0].credit_update_requested=0' "$report_txt"
grep -Fq 'credit[0].computed=0' "$report_txt"
grep -Fq 'credit[0].queued=0' "$report_txt"
grep -Fq 'credit[0].persisted=0' "$report_txt"
grep -Fq 'credit[0].no_effect=1' "$report_txt"

printf 'kernel_scheduler_credit_report_runner: ok\n'
