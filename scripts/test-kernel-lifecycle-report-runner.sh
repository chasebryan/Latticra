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
  src/runtime_boundary.c \
  src/system_bootstrap.c \
  src/kernel.c \
  src/kernel_subsystem_registry.c \
  src/kernel_scheduler.c \
  src/kernel_memory_map.c \
  src/kernel_state.c \
  src/kernel_state_machine.c \
  src/kernel_lifecycle.c \
  tools/kernel_lifecycle_report.c \
  -o "$report_bin"

"$report_bin" > "$report_txt"

grep -Fq 'LATTICRA KERNEL LIFECYCLE REPORT' "$report_txt"
grep -Fq 'lifecycle_status=lifecycle-complete' "$report_txt"
grep -Fq 'policy_status=gate-allowed' "$report_txt"
grep -Fq 'final_state=memory-map-ready' "$report_txt"
grep -Fq 'step_count=4' "$report_txt"
grep -Fq 'state_change_count=4' "$report_txt"
grep -Fq 'lifecycle_complete=1' "$report_txt"
grep -Fq 'external_effect_performed=0' "$report_txt"
grep -Fq 'machine_log_count=4' "$report_txt"
grep -Fq 'evidence_level=10' "$report_txt"
grep -Fq 'log[0].from=created' "$report_txt"
grep -Fq 'log[0].to=initialized' "$report_txt"
grep -Fq 'log[0].status=machine-mutated' "$report_txt"
grep -Fq 'log[3].from=scheduler-ready' "$report_txt"
grep -Fq 'log[3].to=memory-map-ready' "$report_txt"
grep -Fq 'log[3].state_change_performed=1' "$report_txt"
grep -Fq 'log[3].external_effect_performed=0' "$report_txt"

printf 'kernel_lifecycle_report_runner: ok\n'
