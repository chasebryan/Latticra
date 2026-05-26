#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'kernel lifecycle status alignment: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'kernel lifecycle status alignment: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_file docs/status/README.md
require_file docs/KERNEL_LIFECYCLE_SEED.md
require_file docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_file docs/KERNEL_LIFECYCLE_ROLLBACK_PLAN.md
require_file scripts/test-kernel-lifecycle.sh
require_file scripts/test-kernel-lifecycle-report-runner.sh
require_file scripts/test-kernel-ipc-table.sh
require_file scripts/test-kernel-ipc-table-report-runner.sh
require_file .github/workflows/kernel-ipc-table.yml
require_file scripts/test-kernel-vfs-namespace.sh
require_file scripts/test-kernel-vfs-namespace-report-runner.sh
require_file .github/workflows/kernel-vfs-namespace.yml
require_file scripts/test-kernel-device-registry.sh
require_file scripts/test-kernel-device-registry-report-runner.sh
require_file .github/workflows/kernel-device-registry.yml
require_file scripts/test-kernel-driver-catalog.sh
require_file scripts/test-kernel-driver-catalog-report-runner.sh
require_file .github/workflows/kernel-driver-catalog.yml
require_file scripts/test-kernel-interrupt-table.sh
require_file scripts/test-kernel-interrupt-table-report-runner.sh
require_file .github/workflows/kernel-interrupt-table.yml
require_file scripts/test-kernel-timer-source.sh
require_file scripts/test-kernel-timer-source-report-runner.sh
require_file .github/workflows/kernel-timer-source.yml
require_file scripts/test-kernel-scheduler-tick.sh
require_file scripts/test-kernel-scheduler-tick-report-runner.sh
require_file .github/workflows/kernel-scheduler-tick.yml
require_file scripts/test-kernel-process-table.sh
require_file scripts/test-kernel-process-table-report-runner.sh
require_file .github/workflows/kernel-process-table.yml
require_file scripts/test-kernel-syscall-table.sh
require_file scripts/test-kernel-syscall-table-report-runner.sh
require_file .github/workflows/kernel-syscall-table.yml
require_file scripts/test-kernel-lifecycle-subsystem-summary.sh
require_file scripts/test-kernel-lifecycle-subsystem-summary-report-runner.sh
require_file scripts/test-kernel-lifecycle-rollback-plan.sh

require_contains 'Status: status alignment record' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'PR #170 — kernel lifecycle report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'PR #171 — kernel lifecycle subsystem summary' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'PR #172 — kernel lifecycle rollback plan' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel lifecycle report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel IPC table guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel IPC table report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel VFS namespace guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel VFS namespace report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel device registry guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel device registry report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel driver catalog guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel driver catalog report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel interrupt table guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel interrupt table report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel timer source guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel timer source report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel scheduler tick guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel scheduler tick report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel process table guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel process table report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel syscall table guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel syscall table report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel lifecycle subsystem summary' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel lifecycle rollback plan' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'final_state=scheduler-tick-ready' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'external_effect_performed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'no_external_effect_chain=1' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'scheduler_execution_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'memory_allocation_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'process_spawn_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'syscall_dispatch_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'ipc_send_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'ipc_receive_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'ipc_queue_mutation_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'filesystem_lookup_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'filesystem_read_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'filesystem_write_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'namespace_mutation_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'device_open_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'device_read_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'device_write_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'driver_probe_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'driver_load_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'driver_bind_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'interrupt_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'interrupt_mask_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'interrupt_unmask_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'interrupt_dispatch_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'interrupt_ack_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'timer_tick_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'timer_arm_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'timer_disarm_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'scheduler_tick_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'run_queue_mutation_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'context_switch_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'preemption_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'time_accounting_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'time_read_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'process_wake_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'dma_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'hardware_effect_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'Add no-effect rollback classifier' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-ipc-table.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-vfs-namespace.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-device-registry.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-driver-catalog.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-interrupt-table.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-timer-source.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-scheduler-tick.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-process-table.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-syscall-table.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md

require_contains 'KERNEL_LIFECYCLE_EVIDENCE_STATUS.md' docs/status/README.md
require_contains 'Current kernel lifecycle checkpoint' docs/status/README.md
require_contains 'kernel IPC table guard' docs/status/README.md
require_contains 'kernel IPC table report runner' docs/status/README.md
require_contains 'kernel VFS namespace guard' docs/status/README.md
require_contains 'kernel VFS namespace report runner' docs/status/README.md
require_contains 'kernel device registry guard' docs/status/README.md
require_contains 'kernel device registry report runner' docs/status/README.md
require_contains 'kernel driver catalog guard' docs/status/README.md
require_contains 'kernel driver catalog report runner' docs/status/README.md
require_contains 'kernel interrupt table guard' docs/status/README.md
require_contains 'kernel interrupt table report runner' docs/status/README.md
require_contains 'kernel timer source guard' docs/status/README.md
require_contains 'kernel timer source report runner' docs/status/README.md
require_contains 'kernel scheduler tick guard' docs/status/README.md
require_contains 'kernel scheduler tick report runner' docs/status/README.md
require_contains 'kernel process table guard' docs/status/README.md
require_contains 'kernel process table report runner' docs/status/README.md
require_contains 'kernel syscall table guard' docs/status/README.md
require_contains 'kernel syscall table report runner' docs/status/README.md
require_contains 'final_state=scheduler-tick-ready' docs/status/README.md
require_contains 'external_effect_performed=0' docs/status/README.md
require_contains 'runtime_entry_allowed=0' docs/status/README.md
require_contains 'scheduler_execution_allowed=0' docs/status/README.md
require_contains 'memory_allocation_allowed=0' docs/status/README.md
require_contains 'process_spawn_allowed=0' docs/status/README.md
require_contains 'syscall_dispatch_allowed=0' docs/status/README.md
require_contains 'ipc_send_allowed=0' docs/status/README.md
require_contains 'ipc_receive_allowed=0' docs/status/README.md
require_contains 'ipc_queue_mutation_allowed=0' docs/status/README.md
require_contains 'filesystem_lookup_allowed=0' docs/status/README.md
require_contains 'filesystem_read_allowed=0' docs/status/README.md
require_contains 'filesystem_write_allowed=0' docs/status/README.md
require_contains 'namespace_mutation_allowed=0' docs/status/README.md
require_contains 'device_open_allowed=0' docs/status/README.md
require_contains 'device_read_allowed=0' docs/status/README.md
require_contains 'device_write_allowed=0' docs/status/README.md
require_contains 'driver_probe_allowed=0' docs/status/README.md
require_contains 'driver_load_allowed=0' docs/status/README.md
require_contains 'driver_bind_allowed=0' docs/status/README.md
require_contains 'interrupt_allowed=0' docs/status/README.md
require_contains 'interrupt_mask_allowed=0' docs/status/README.md
require_contains 'interrupt_unmask_allowed=0' docs/status/README.md
require_contains 'interrupt_dispatch_allowed=0' docs/status/README.md
require_contains 'interrupt_ack_allowed=0' docs/status/README.md
require_contains 'timer_tick_allowed=0' docs/status/README.md
require_contains 'timer_arm_allowed=0' docs/status/README.md
require_contains 'timer_disarm_allowed=0' docs/status/README.md
require_contains 'scheduler_tick_allowed=0' docs/status/README.md
require_contains 'run_queue_mutation_allowed=0' docs/status/README.md
require_contains 'context_switch_allowed=0' docs/status/README.md
require_contains 'preemption_allowed=0' docs/status/README.md
require_contains 'time_accounting_allowed=0' docs/status/README.md
require_contains 'time_read_allowed=0' docs/status/README.md
require_contains 'process_wake_allowed=0' docs/status/README.md
require_contains 'dma_allowed=0' docs/status/README.md
require_contains 'hardware_effect_allowed=0' docs/status/README.md
require_contains 'sh scripts/test-kernel-ipc-table.sh' .github/workflows/kernel-ipc-table.yml
require_contains 'sh scripts/test-kernel-ipc-table-report-runner.sh' .github/workflows/kernel-ipc-table.yml
require_contains 'sh scripts/test-kernel-vfs-namespace.sh' .github/workflows/kernel-vfs-namespace.yml
require_contains 'sh scripts/test-kernel-vfs-namespace-report-runner.sh' .github/workflows/kernel-vfs-namespace.yml
require_contains 'sh scripts/test-kernel-device-registry.sh' .github/workflows/kernel-device-registry.yml
require_contains 'sh scripts/test-kernel-device-registry-report-runner.sh' .github/workflows/kernel-device-registry.yml
require_contains 'sh scripts/test-kernel-driver-catalog.sh' .github/workflows/kernel-driver-catalog.yml
require_contains 'sh scripts/test-kernel-driver-catalog-report-runner.sh' .github/workflows/kernel-driver-catalog.yml
require_contains 'sh scripts/test-kernel-interrupt-table.sh' .github/workflows/kernel-interrupt-table.yml
require_contains 'sh scripts/test-kernel-interrupt-table-report-runner.sh' .github/workflows/kernel-interrupt-table.yml
require_contains 'sh scripts/test-kernel-timer-source.sh' .github/workflows/kernel-timer-source.yml
require_contains 'sh scripts/test-kernel-timer-source-report-runner.sh' .github/workflows/kernel-timer-source.yml
require_contains 'sh scripts/test-kernel-scheduler-tick.sh' .github/workflows/kernel-scheduler-tick.yml
require_contains 'sh scripts/test-kernel-scheduler-tick-report-runner.sh' .github/workflows/kernel-scheduler-tick.yml
require_contains 'sh scripts/test-kernel-process-table.sh' .github/workflows/kernel-process-table.yml
require_contains 'sh scripts/test-kernel-process-table-report-runner.sh' .github/workflows/kernel-process-table.yml
require_contains 'sh scripts/test-kernel-syscall-table.sh' .github/workflows/kernel-syscall-table.yml
require_contains 'sh scripts/test-kernel-syscall-table-report-runner.sh' .github/workflows/kernel-syscall-table.yml

printf 'kernel_lifecycle_status_alignment: ok\n'
