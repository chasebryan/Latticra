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
require_file README.md
require_file STATUS.md
require_file docs/status/CURRENT_STATUS.md
require_file docs/FOUNDATION_INDEX.md
require_file docs/KERNEL_LIFECYCLE_SEED.md
require_file docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_file docs/KERNEL_PREEMPTION_SEED.md
require_file docs/KERNEL_SCHEDULER_CREDIT_SEED.md
require_file docs/KERNEL_SCHEDULER_SELECTION_SEED.md
require_file docs/KERNEL_SCHEDULER_DISPATCH_SEED.md
require_file docs/KERNEL_SCHEDULER_HANDOFF_SEED.md
require_file docs/KERNEL_SCHEDULER_ACTIVATION_SEED.md
require_file docs/KERNEL_SCHEDULER_RUN_ENTRY_SEED.md
require_file docs/KERNEL_RUNTIME_ENTRY_ADMISSION_SEED.md
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
require_file scripts/test-kernel-run-queue.sh
require_file scripts/test-kernel-run-queue-report-runner.sh
require_file .github/workflows/kernel-run-queue.yml
require_file scripts/test-kernel-context-switch.sh
require_file scripts/test-kernel-context-switch-report-runner.sh
require_file .github/workflows/kernel-context-switch.yml
require_file scripts/test-kernel-time-accounting.sh
require_file scripts/test-kernel-time-accounting-report-runner.sh
require_file .github/workflows/kernel-time-accounting.yml
require_file scripts/test-kernel-preemption.sh
require_file scripts/test-kernel-preemption-report-runner.sh
require_file .github/workflows/kernel-preemption.yml
require_file scripts/test-kernel-scheduler-credit.sh
require_file scripts/test-kernel-scheduler-credit-report-runner.sh
require_file .github/workflows/kernel-scheduler-credit.yml
require_file scripts/test-kernel-scheduler-selection.sh
require_file scripts/test-kernel-scheduler-selection-report-runner.sh
require_file .github/workflows/kernel-scheduler-selection.yml
require_file scripts/test-kernel-scheduler-dispatch.sh
require_file scripts/test-kernel-scheduler-dispatch-report-runner.sh
require_file .github/workflows/kernel-scheduler-dispatch.yml
require_file scripts/test-kernel-scheduler-handoff.sh
require_file scripts/test-kernel-scheduler-handoff-report-runner.sh
require_file .github/workflows/kernel-scheduler-handoff.yml
require_file scripts/test-kernel-scheduler-activation.sh
require_file scripts/test-kernel-scheduler-activation-report-runner.sh
require_file .github/workflows/kernel-scheduler-activation.yml
require_file scripts/test-kernel-scheduler-run-entry.sh
require_file scripts/test-kernel-scheduler-run-entry-report-runner.sh
require_file .github/workflows/kernel-scheduler-run-entry.yml
require_file scripts/test-kernel-runtime-entry-admission.sh
require_file scripts/test-kernel-runtime-entry-admission-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-admission.yml
require_file docs/KERNEL_RUNTIME_ENTRY_FRAME_SEED.md
require_file include/latticra/kernel_runtime_entry_frame.h
require_file src/kernel_runtime_entry_frame.c
require_file tests/kernel_runtime_entry_frame.c
require_file tools/kernel_runtime_entry_frame_report.c
require_file scripts/test-kernel-runtime-entry-frame.sh
require_file scripts/test-kernel-runtime-entry-frame-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-frame.yml
require_file docs/KERNEL_RUNTIME_ENTRY_REGISTER_VIEW_SEED.md
require_file include/latticra/kernel_runtime_entry_register_view.h
require_file src/kernel_runtime_entry_register_view.c
require_file tests/kernel_runtime_entry_register_view.c
require_file tools/kernel_runtime_entry_register_view_report.c
require_file scripts/test-kernel-runtime-entry-register-view.sh
require_file scripts/test-kernel-runtime-entry-register-view-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-register-view.yml
require_file docs/KERNEL_RUNTIME_ENTRY_STACK_VIEW_SEED.md
require_file include/latticra/kernel_runtime_entry_stack_view.h
require_file src/kernel_runtime_entry_stack_view.c
require_file tests/kernel_runtime_entry_stack_view.c
require_file tools/kernel_runtime_entry_stack_view_report.c
require_file scripts/test-kernel-runtime-entry-stack-view.sh
require_file scripts/test-kernel-runtime-entry-stack-view-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-stack-view.yml
require_file docs/KERNEL_RUNTIME_ENTRY_ADDRESS_SPACE_VIEW_SEED.md
require_file include/latticra/kernel_runtime_entry_address_space_view.h
require_file src/kernel_runtime_entry_address_space_view.c
require_file tests/kernel_runtime_entry_address_space_view.c
require_file tools/kernel_runtime_entry_address_space_view_report.c
require_file scripts/test-kernel-runtime-entry-address-space-view.sh
require_file scripts/test-kernel-runtime-entry-address-space-view-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-address-space-view.yml
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
require_contains 'kernel run queue guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel run queue report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel context switch guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel context switch report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel time accounting guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel time accounting report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel preemption guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel preemption report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel scheduler credit guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel scheduler credit report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel scheduler selection guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel scheduler selection report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel scheduler dispatch guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel scheduler dispatch report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel scheduler handoff guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel scheduler handoff report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel scheduler activation guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel scheduler activation report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel scheduler run-entry guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel scheduler run-entry report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry admission guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry admission report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry frame guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry frame report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry register-view guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry register-view report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry stack-view guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry stack-view report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry address-space-view guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry address-space-view report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel process table guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel process table report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel syscall table guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel syscall table report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel lifecycle subsystem summary' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel lifecycle rollback plan' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'final_state=runtime-entry-address-space-view-ready' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'external_effect_performed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'no_external_effect_chain=1' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_address_space_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_stack_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_register_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_frame_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_admission_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'scheduler_execution_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'scheduler_selection_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'scheduler_dispatch_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'scheduler_handoff_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'scheduler_activation_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'scheduler_run_entry_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
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
require_contains 'enqueue_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'dequeue_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'dispatch_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'context_switch_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'register_save_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'register_restore_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'stack_switch_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'address_space_switch_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'preemption_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'time_accounting_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'time_read_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'cpu_usage_write_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'quota_update_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'scheduler_credit_update_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'process_wake_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'dma_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'hardware_effect_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'Add no-effect runtime entry privilege-level view classifier' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-ipc-table.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-vfs-namespace.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-device-registry.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-driver-catalog.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-interrupt-table.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-timer-source.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-scheduler-tick.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-run-queue.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-context-switch.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-time-accounting.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-preemption.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-scheduler-credit.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-scheduler-selection.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-scheduler-dispatch.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-scheduler-handoff.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-scheduler-activation.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-scheduler-run-entry.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-admission.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-frame.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-register-view.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-stack-view.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
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
require_contains 'kernel run queue guard' docs/status/README.md
require_contains 'kernel run queue report runner' docs/status/README.md
require_contains 'kernel context switch guard' docs/status/README.md
require_contains 'kernel context switch report runner' docs/status/README.md
require_contains 'kernel time accounting guard' docs/status/README.md
require_contains 'kernel time accounting report runner' docs/status/README.md
require_contains 'kernel preemption guard' docs/status/README.md
require_contains 'kernel preemption report runner' docs/status/README.md
require_contains 'kernel scheduler credit guard' docs/status/README.md
require_contains 'kernel scheduler credit report runner' docs/status/README.md
require_contains 'kernel scheduler selection guard' docs/status/README.md
require_contains 'kernel scheduler selection report runner' docs/status/README.md
require_contains 'kernel scheduler dispatch guard' docs/status/README.md
require_contains 'kernel scheduler dispatch report runner' docs/status/README.md
require_contains 'kernel scheduler handoff guard' docs/status/README.md
require_contains 'kernel scheduler handoff report runner' docs/status/README.md
require_contains 'kernel scheduler activation guard' docs/status/README.md
require_contains 'kernel scheduler activation report runner' docs/status/README.md
require_contains 'kernel scheduler run-entry guard' docs/status/README.md
require_contains 'kernel scheduler run-entry report runner' docs/status/README.md
require_contains 'kernel runtime entry admission guard' docs/status/README.md
require_contains 'kernel runtime entry admission report runner' docs/status/README.md
require_contains 'kernel runtime entry frame guard' docs/status/README.md
require_contains 'kernel runtime entry frame report runner' docs/status/README.md
require_contains 'kernel runtime entry register-view guard' docs/status/README.md
require_contains 'kernel runtime entry register-view report runner' docs/status/README.md
require_contains 'kernel runtime entry stack-view guard' docs/status/README.md
require_contains 'kernel runtime entry stack-view report runner' docs/status/README.md
require_contains 'kernel runtime entry address-space-view guard' docs/status/README.md
require_contains 'kernel runtime entry address-space-view report runner' docs/status/README.md
require_contains 'kernel process table guard' docs/status/README.md
require_contains 'kernel process table report runner' docs/status/README.md
require_contains 'kernel syscall table guard' docs/status/README.md
require_contains 'kernel syscall table report runner' docs/status/README.md
require_contains 'final_state=runtime-entry-address-space-view-ready' docs/status/README.md
require_contains 'external_effect_performed=0' docs/status/README.md
require_contains 'runtime_entry_address_space_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_stack_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_register_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_frame_allowed=0' docs/status/README.md
require_contains 'runtime_entry_admission_allowed=0' docs/status/README.md
require_contains 'runtime_entry_allowed=0' docs/status/README.md
require_contains 'scheduler_execution_allowed=0' docs/status/README.md
require_contains 'scheduler_selection_allowed=0' docs/status/README.md
require_contains 'scheduler_dispatch_allowed=0' docs/status/README.md
require_contains 'scheduler_handoff_allowed=0' docs/status/README.md
require_contains 'scheduler_activation_allowed=0' docs/status/README.md
require_contains 'scheduler_run_entry_allowed=0' docs/status/README.md
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
require_contains 'enqueue_allowed=0' docs/status/README.md
require_contains 'dequeue_allowed=0' docs/status/README.md
require_contains 'dispatch_allowed=0' docs/status/README.md
require_contains 'context_switch_allowed=0' docs/status/README.md
require_contains 'register_save_allowed=0' docs/status/README.md
require_contains 'register_restore_allowed=0' docs/status/README.md
require_contains 'stack_switch_allowed=0' docs/status/README.md
require_contains 'address_space_switch_allowed=0' docs/status/README.md
require_contains 'preemption_allowed=0' docs/status/README.md
require_contains 'time_accounting_allowed=0' docs/status/README.md
require_contains 'time_read_allowed=0' docs/status/README.md
require_contains 'cpu_usage_write_allowed=0' docs/status/README.md
require_contains 'quota_update_allowed=0' docs/status/README.md
require_contains 'scheduler_credit_update_allowed=0' docs/status/README.md
require_contains 'process_wake_allowed=0' docs/status/README.md
require_contains 'dma_allowed=0' docs/status/README.md
require_contains 'hardware_effect_allowed=0' docs/status/README.md
require_contains 'Add no-effect runtime entry privilege-level view classifier' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-admission.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-frame.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-register-view.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-stack-view.yml' docs/status/README.md
require_contains '| Kernel lifecycle evidence | No-effect kernel lifecycle path reaches `runtime-entry-address-space-view-ready` with guarded scheduler run-entry, runtime-entry admission, frame, register-view, stack-view, and address-space-view metadata' README.md
require_contains 'kernel_lifecycle_evidence_status_present=1' README.md
require_contains 'kernel_run_queue_guard_present=1' README.md
require_contains 'kernel_context_switch_guard_present=1' README.md
require_contains 'kernel_time_accounting_guard_present=1' README.md
require_contains 'kernel_preemption_guard_present=1' README.md
require_contains 'kernel_scheduler_credit_guard_present=1' README.md
require_contains 'kernel_scheduler_selection_guard_present=1' README.md
require_contains 'kernel_scheduler_dispatch_guard_present=1' README.md
require_contains 'kernel_scheduler_handoff_guard_present=1' README.md
require_contains 'kernel_scheduler_activation_guard_present=1' README.md
require_contains 'kernel_scheduler_run_entry_guard_present=1' README.md
require_contains 'kernel_runtime_entry_admission_guard_present=1' README.md
require_contains 'kernel_runtime_entry_frame_guard_present=1' README.md
require_contains 'kernel_runtime_entry_register_view_guard_present=1' README.md
require_contains 'kernel_runtime_entry_stack_view_guard_present=1' README.md
require_contains 'kernel_runtime_entry_address_space_view_guard_present=1' README.md
require_contains 'kernel_process_table_guard_present=1' README.md
require_contains 'kernel_syscall_table_guard_present=1' README.md
require_contains 'final_state=runtime-entry-address-space-view-ready' README.md
require_contains 'runtime_entry_address_space_view_allowed=0' README.md
require_contains 'runtime_entry_stack_view_allowed=0' README.md
require_contains 'runtime_entry_register_view_allowed=0' README.md
require_contains 'runtime_entry_frame_allowed=0' README.md
require_contains 'runtime_entry_admission_allowed=0' README.md
require_contains 'runtime_entry_allowed=0' README.md
require_contains 'scheduler_selection_allowed=0' README.md
require_contains 'scheduler_dispatch_allowed=0' README.md
require_contains 'scheduler_handoff_allowed=0' README.md
require_contains 'scheduler_activation_allowed=0' README.md
require_contains 'scheduler_run_entry_allowed=0' README.md
require_contains 'process_spawn_allowed=0' README.md
require_contains 'syscall_dispatch_allowed=0' README.md
require_contains 'run_queue_mutation_allowed=0' README.md
require_contains 'dispatch_allowed=0' README.md
require_contains 'context_switch_allowed=0' README.md
require_contains 'time_accounting_allowed=0' README.md
require_contains 'preemption_allowed=0' README.md
require_contains 'scheduler_credit_update_allowed=0' README.md
require_contains 'hardware_effect_allowed=0' README.md
require_contains 'docs/KERNEL_RUN_QUEUE_SEED.md' README.md
require_contains 'docs/KERNEL_SCHEDULER_DISPATCH_SEED.md' README.md
require_contains 'docs/KERNEL_SCHEDULER_HANDOFF_SEED.md' README.md
require_contains 'docs/KERNEL_SCHEDULER_ACTIVATION_SEED.md' README.md
require_contains 'docs/KERNEL_SCHEDULER_RUN_ENTRY_SEED.md' README.md
require_contains 'docs/KERNEL_RUNTIME_ENTRY_ADMISSION_SEED.md' README.md
require_contains 'docs/KERNEL_RUNTIME_ENTRY_FRAME_SEED.md' README.md
require_contains 'docs/KERNEL_RUNTIME_ENTRY_REGISTER_VIEW_SEED.md' README.md
require_contains 'docs/KERNEL_RUNTIME_ENTRY_STACK_VIEW_SEED.md' README.md
require_contains 'docs/KERNEL_RUNTIME_ENTRY_ADDRESS_SPACE_VIEW_SEED.md' README.md
require_contains 'docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md' README.md
require_contains 'Latest kernel lifecycle evidence status note: 2026-05-26 CDT' STATUS.md
require_contains 'Kernel run queue seed' STATUS.md
require_contains 'Kernel context switch seed' STATUS.md
require_contains 'Kernel time accounting seed' STATUS.md
require_contains 'Kernel preemption seed' STATUS.md
require_contains 'Kernel scheduler credit seed' STATUS.md
require_contains 'Kernel scheduler selection seed' STATUS.md
require_contains 'Kernel scheduler dispatch seed' STATUS.md
require_contains 'Kernel scheduler handoff seed' STATUS.md
require_contains 'Kernel scheduler activation seed' STATUS.md
require_contains 'Kernel scheduler run-entry seed' STATUS.md
require_contains 'Kernel runtime entry admission seed' STATUS.md
require_contains 'Kernel runtime entry frame seed' STATUS.md
require_contains 'Kernel runtime entry register-view seed' STATUS.md
require_contains 'Kernel runtime entry stack-view seed' STATUS.md
require_contains 'Kernel runtime entry address-space-view seed' STATUS.md
require_contains 'Kernel lifecycle rollback plan' STATUS.md
require_contains 'Latest kernel lifecycle evidence status note: 2026-05-26 CDT' docs/status/CURRENT_STATUS.md
require_contains 'Kernel run queue seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel context switch seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel time accounting seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel preemption seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel scheduler credit seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel scheduler selection seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel scheduler dispatch seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel scheduler handoff seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel scheduler activation seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel scheduler run-entry seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel runtime entry admission seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel runtime entry frame seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel runtime entry register-view seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel runtime entry stack-view seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel runtime entry address-space-view seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel lifecycle rollback plan' docs/status/CURRENT_STATUS.md
require_contains 'status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUN_QUEUE_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_CONTEXT_SWITCH_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_TIME_ACCOUNTING_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_PREEMPTION_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_SCHEDULER_CREDIT_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_SCHEDULER_SELECTION_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_SCHEDULER_DISPATCH_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_SCHEDULER_HANDOFF_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_SCHEDULER_ACTIVATION_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_SCHEDULER_RUN_ENTRY_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_ADMISSION_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_FRAME_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_REGISTER_VIEW_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_STACK_VIEW_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_ADDRESS_SPACE_VIEW_SEED.md' docs/FOUNDATION_INDEX.md
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
require_contains 'sh scripts/test-kernel-run-queue.sh' .github/workflows/kernel-run-queue.yml
require_contains 'sh scripts/test-kernel-run-queue-report-runner.sh' .github/workflows/kernel-run-queue.yml
require_contains 'sh scripts/test-kernel-context-switch.sh' .github/workflows/kernel-context-switch.yml
require_contains 'sh scripts/test-kernel-context-switch-report-runner.sh' .github/workflows/kernel-context-switch.yml
require_contains 'sh scripts/test-kernel-time-accounting.sh' .github/workflows/kernel-time-accounting.yml
require_contains 'sh scripts/test-kernel-time-accounting-report-runner.sh' .github/workflows/kernel-time-accounting.yml
require_contains 'sh scripts/test-kernel-preemption.sh' .github/workflows/kernel-preemption.yml
require_contains 'sh scripts/test-kernel-preemption-report-runner.sh' .github/workflows/kernel-preemption.yml
require_contains 'sh scripts/test-kernel-scheduler-credit.sh' .github/workflows/kernel-scheduler-credit.yml
require_contains 'sh scripts/test-kernel-scheduler-credit-report-runner.sh' .github/workflows/kernel-scheduler-credit.yml
require_contains 'sh scripts/test-kernel-scheduler-selection.sh' .github/workflows/kernel-scheduler-selection.yml
require_contains 'sh scripts/test-kernel-scheduler-selection-report-runner.sh' .github/workflows/kernel-scheduler-selection.yml
require_contains 'sh scripts/test-kernel-scheduler-dispatch.sh' .github/workflows/kernel-scheduler-dispatch.yml
require_contains 'sh scripts/test-kernel-scheduler-dispatch-report-runner.sh' .github/workflows/kernel-scheduler-dispatch.yml
require_contains 'sh scripts/test-kernel-scheduler-handoff.sh' .github/workflows/kernel-scheduler-handoff.yml
require_contains 'sh scripts/test-kernel-scheduler-handoff-report-runner.sh' .github/workflows/kernel-scheduler-handoff.yml
require_contains 'sh scripts/test-kernel-scheduler-activation.sh' .github/workflows/kernel-scheduler-activation.yml
require_contains 'sh scripts/test-kernel-scheduler-activation-report-runner.sh' .github/workflows/kernel-scheduler-activation.yml
require_contains 'sh scripts/test-kernel-scheduler-run-entry.sh' .github/workflows/kernel-scheduler-run-entry.yml
require_contains 'sh scripts/test-kernel-scheduler-run-entry-report-runner.sh' .github/workflows/kernel-scheduler-run-entry.yml
require_contains 'sh scripts/test-kernel-runtime-entry-admission.sh' .github/workflows/kernel-runtime-entry-admission.yml
require_contains 'sh scripts/test-kernel-runtime-entry-admission-report-runner.sh' .github/workflows/kernel-runtime-entry-admission.yml
require_contains 'sh scripts/test-kernel-runtime-entry-frame.sh' .github/workflows/kernel-runtime-entry-frame.yml
require_contains 'sh scripts/test-kernel-runtime-entry-frame-report-runner.sh' .github/workflows/kernel-runtime-entry-frame.yml
require_contains 'sh scripts/test-kernel-runtime-entry-register-view.sh' .github/workflows/kernel-runtime-entry-register-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-register-view-report-runner.sh' .github/workflows/kernel-runtime-entry-register-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-stack-view.sh' .github/workflows/kernel-runtime-entry-stack-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-stack-view-report-runner.sh' .github/workflows/kernel-runtime-entry-stack-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-address-space-view.sh' .github/workflows/kernel-runtime-entry-address-space-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-address-space-view-report-runner.sh' .github/workflows/kernel-runtime-entry-address-space-view.yml
require_contains 'sh scripts/test-kernel-process-table.sh' .github/workflows/kernel-process-table.yml
require_contains 'sh scripts/test-kernel-process-table-report-runner.sh' .github/workflows/kernel-process-table.yml
require_contains 'sh scripts/test-kernel-syscall-table.sh' .github/workflows/kernel-syscall-table.yml
require_contains 'sh scripts/test-kernel-syscall-table-report-runner.sh' .github/workflows/kernel-syscall-table.yml

printf 'kernel_lifecycle_status_alignment: ok\n'
