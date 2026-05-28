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
require_file docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
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
require_file docs/KERNEL_RUNTIME_ENTRY_PRIVILEGE_LEVEL_VIEW_SEED.md
require_file include/latticra/kernel_runtime_entry_privilege_level_view.h
require_file src/kernel_runtime_entry_privilege_level_view.c
require_file tests/kernel_runtime_entry_privilege_level_view.c
require_file tools/kernel_runtime_entry_privilege_level_view_report.c
require_file scripts/test-kernel-runtime-entry-privilege-level-view.sh
require_file scripts/test-kernel-runtime-entry-privilege-level-view-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-privilege-level-view.yml
require_file docs/KERNEL_RUNTIME_ENTRY_SYSCALL_GATE_VIEW_SEED.md
require_file include/latticra/kernel_runtime_entry_syscall_gate_view.h
require_file src/kernel_runtime_entry_syscall_gate_view.c
require_file tests/kernel_runtime_entry_syscall_gate_view.c
require_file tools/kernel_runtime_entry_syscall_gate_view_report.c
require_file scripts/test-kernel-runtime-entry-syscall-gate-view.sh
require_file scripts/test-kernel-runtime-entry-syscall-gate-view-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-syscall-gate-view.yml
require_file docs/KERNEL_RUNTIME_ENTRY_SYSCALL_DISPATCH_VIEW_SEED.md
require_file include/latticra/kernel_runtime_entry_syscall_dispatch_view.h
require_file src/kernel_runtime_entry_syscall_dispatch_view.c
require_file tests/kernel_runtime_entry_syscall_dispatch_view.c
require_file tools/kernel_runtime_entry_syscall_dispatch_view_report.c
require_file scripts/test-kernel-runtime-entry-syscall-dispatch-view.sh
require_file scripts/test-kernel-runtime-entry-syscall-dispatch-view-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-syscall-dispatch-view.yml
require_file docs/KERNEL_RUNTIME_ENTRY_SYSCALL_RETURN_VIEW_SEED.md
require_file include/latticra/kernel_runtime_entry_syscall_return_view.h
require_file src/kernel_runtime_entry_syscall_return_view.c
require_file tests/kernel_runtime_entry_syscall_return_view.c
require_file tools/kernel_runtime_entry_syscall_return_view_report.c
require_file scripts/test-kernel-runtime-entry-syscall-return-view.sh
require_file scripts/test-kernel-runtime-entry-syscall-return-view-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-syscall-return-view.yml
require_file docs/KERNEL_RUNTIME_ENTRY_SYSCALL_EXIT_VIEW_SEED.md
require_file include/latticra/kernel_runtime_entry_syscall_exit_view.h
require_file src/kernel_runtime_entry_syscall_exit_view.c
require_file tests/kernel_runtime_entry_syscall_exit_view.c
require_file tools/kernel_runtime_entry_syscall_exit_view_report.c
require_file scripts/test-kernel-runtime-entry-syscall-exit-view.sh
require_file scripts/test-kernel-runtime-entry-syscall-exit-view-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-syscall-exit-view.yml
require_file docs/KERNEL_RUNTIME_ENTRY_USER_MODE_RESUME_VIEW_SEED.md
require_file include/latticra/kernel_runtime_entry_user_mode_resume_view.h
require_file src/kernel_runtime_entry_user_mode_resume_view.c
require_file tests/kernel_runtime_entry_user_mode_resume_view.c
require_file tools/kernel_runtime_entry_user_mode_resume_view_report.c
require_file scripts/test-kernel-runtime-entry-user-mode-resume-view.sh
require_file scripts/test-kernel-runtime-entry-user-mode-resume-view-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-user-mode-resume-view.yml
require_file docs/KERNEL_RUNTIME_ENTRY_POST_RESUME_OBSERVATION_VIEW_SEED.md
require_file include/latticra/kernel_runtime_entry_post_resume_observation_view.h
require_file src/kernel_runtime_entry_post_resume_observation_view.c
require_file tests/kernel_runtime_entry_post_resume_observation_view.c
require_file tools/kernel_runtime_entry_post_resume_observation_view_report.c
require_file scripts/test-kernel-runtime-entry-post-resume-observation-view.sh
require_file scripts/test-kernel-runtime-entry-post-resume-observation-view-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-post-resume-observation-view.yml
require_file docs/KERNEL_RUNTIME_ENTRY_SCHEDULER_RETURN_OBSERVATION_VIEW_SEED.md
require_file include/latticra/kernel_runtime_entry_scheduler_return_observation_view.h
require_file src/kernel_runtime_entry_scheduler_return_observation_view.c
require_file tests/kernel_runtime_entry_scheduler_return_observation_view.c
require_file tools/kernel_runtime_entry_scheduler_return_observation_view_report.c
require_file scripts/test-kernel-runtime-entry-scheduler-return-observation-view.sh
require_file scripts/test-kernel-runtime-entry-scheduler-return-observation-view-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-scheduler-return-observation-view.yml
require_file docs/KERNEL_RUNTIME_ENTRY_PROCESS_RETURN_OBSERVATION_VIEW_SEED.md
require_file include/latticra/kernel_runtime_entry_process_return_observation_view.h
require_file src/kernel_runtime_entry_process_return_observation_view.c
require_file tests/kernel_runtime_entry_process_return_observation_view.c
require_file tools/kernel_runtime_entry_process_return_observation_view_report.c
require_file scripts/test-kernel-runtime-entry-process-return-observation-view.sh
require_file scripts/test-kernel-runtime-entry-process-return-observation-view-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-process-return-observation-view.yml
require_file docs/KERNEL_RUNTIME_ENTRY_IDLE_RETURN_OBSERVATION_VIEW_SEED.md
require_file include/latticra/kernel_runtime_entry_idle_return_observation_view.h
require_file src/kernel_runtime_entry_idle_return_observation_view.c
require_file tests/kernel_runtime_entry_idle_return_observation_view.c
require_file tools/kernel_runtime_entry_idle_return_observation_view_report.c
require_file scripts/test-kernel-runtime-entry-idle-return-observation-view.sh
require_file scripts/test-kernel-runtime-entry-idle-return-observation-view-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-idle-return-observation-view.yml
require_file docs/KERNEL_RUNTIME_ENTRY_QUIESCENT_RETURN_OBSERVATION_VIEW_SEED.md
require_file include/latticra/kernel_runtime_entry_quiescent_return_observation_view.h
require_file src/kernel_runtime_entry_quiescent_return_observation_view.c
require_file tests/kernel_runtime_entry_quiescent_return_observation_view.c
require_file tools/kernel_runtime_entry_quiescent_return_observation_view_report.c
require_file scripts/test-kernel-runtime-entry-quiescent-return-observation-view.sh
require_file scripts/test-kernel-runtime-entry-quiescent-return-observation-view-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-quiescent-return-observation-view.yml
require_file docs/KERNEL_RUNTIME_ENTRY_PERSISTENCE_BOUNDARY_OBSERVATION_VIEW_SEED.md
require_file include/latticra/kernel_runtime_entry_persistence_boundary_observation_view.h
require_file src/kernel_runtime_entry_persistence_boundary_observation_view.c
require_file tests/kernel_runtime_entry_persistence_boundary_observation_view.c
require_file tools/kernel_runtime_entry_persistence_boundary_observation_view_report.c
require_file scripts/test-kernel-runtime-entry-persistence-boundary-observation-view.sh
require_file scripts/test-kernel-runtime-entry-persistence-boundary-observation-view-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-persistence-boundary-observation-view.yml
require_file docs/KERNEL_RUNTIME_ENTRY_RECOVERY_BOUNDARY_OBSERVATION_VIEW_SEED.md
require_file include/latticra/kernel_runtime_entry_recovery_boundary_observation_view.h
require_file src/kernel_runtime_entry_recovery_boundary_observation_view.c
require_file tests/kernel_runtime_entry_recovery_boundary_observation_view.c
require_file tools/kernel_runtime_entry_recovery_boundary_observation_view_report.c
require_file scripts/test-kernel-runtime-entry-recovery-boundary-observation-view.sh
require_file scripts/test-kernel-runtime-entry-recovery-boundary-observation-view-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-recovery-boundary-observation-view.yml
require_file docs/KERNEL_RUNTIME_ENTRY_RECOVERY_PLAN_OBSERVATION_VIEW_SEED.md
require_file include/latticra/kernel_runtime_entry_recovery_plan_observation_view.h
require_file src/kernel_runtime_entry_recovery_plan_observation_view.c
require_file tests/kernel_runtime_entry_recovery_plan_observation_view.c
require_file tools/kernel_runtime_entry_recovery_plan_observation_view_report.c
require_file scripts/test-kernel-runtime-entry-recovery-plan-observation-view.sh
require_file scripts/test-kernel-runtime-entry-recovery-plan-observation-view-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-recovery-plan-observation-view.yml
require_file docs/KERNEL_RUNTIME_ENTRY_RECOVERY_DISPOSITION_OBSERVATION_VIEW_SEED.md
require_file include/latticra/kernel_runtime_entry_recovery_disposition_observation_view.h
require_file src/kernel_runtime_entry_recovery_disposition_observation_view.c
require_file tests/kernel_runtime_entry_recovery_disposition_observation_view.c
require_file tools/kernel_runtime_entry_recovery_disposition_observation_view_report.c
require_file scripts/test-kernel-runtime-entry-recovery-disposition-observation-view.sh
require_file scripts/test-kernel-runtime-entry-recovery-disposition-observation-view-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-recovery-disposition-observation-view.yml
require_file docs/KERNEL_RUNTIME_ENTRY_RECOVERY_OUTCOME_OBSERVATION_VIEW_SEED.md
require_file include/latticra/kernel_runtime_entry_recovery_outcome_observation_view.h
require_file src/kernel_runtime_entry_recovery_outcome_observation_view.c
require_file tests/kernel_runtime_entry_recovery_outcome_observation_view.c
require_file tools/kernel_runtime_entry_recovery_outcome_observation_view_report.c
require_file scripts/test-kernel-runtime-entry-recovery-outcome-observation-view.sh
require_file scripts/test-kernel-runtime-entry-recovery-outcome-observation-view-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-recovery-outcome-observation-view.yml
require_file docs/KERNEL_RUNTIME_ENTRY_RECOVERY_CLOSEOUT_OBSERVATION_VIEW_SEED.md
require_file include/latticra/kernel_runtime_entry_recovery_closeout_observation_view.h
require_file src/kernel_runtime_entry_recovery_closeout_observation_view.c
require_file tests/kernel_runtime_entry_recovery_closeout_observation_view.c
require_file tools/kernel_runtime_entry_recovery_closeout_observation_view_report.c
require_file scripts/test-kernel-runtime-entry-recovery-closeout-observation-view.sh
require_file scripts/test-kernel-runtime-entry-recovery-closeout-observation-view-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-recovery-closeout-observation-view.yml
require_file docs/KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_OBSERVATION_VIEW_SEED.md
require_file include/latticra/kernel_runtime_entry_recovery_audit_observation_view.h
require_file src/kernel_runtime_entry_recovery_audit_observation_view.c
require_file tests/kernel_runtime_entry_recovery_audit_observation_view.c
require_file tools/kernel_runtime_entry_recovery_audit_observation_view_report.c
require_file scripts/test-kernel-runtime-entry-recovery-audit-observation-view.sh
require_file scripts/test-kernel-runtime-entry-recovery-audit-observation-view-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-recovery-audit-observation-view.yml
require_file docs/KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_OBSERVATION_VIEW_SEED.md
require_file include/latticra/kernel_runtime_entry_recovery_audit_review_observation_view.h
require_file src/kernel_runtime_entry_recovery_audit_review_observation_view.c
require_file tests/kernel_runtime_entry_recovery_audit_review_observation_view.c
require_file tools/kernel_runtime_entry_recovery_audit_review_observation_view_report.c
require_file scripts/test-kernel-runtime-entry-recovery-audit-review-observation-view.sh
require_file scripts/test-kernel-runtime-entry-recovery-audit-review-observation-view-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-recovery-audit-review-observation-view.yml
require_file docs/KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_OBSERVATION_VIEW_SEED.md
require_file include/latticra/kernel_runtime_entry_recovery_audit_review_disposition_observation_view.h
require_file src/kernel_runtime_entry_recovery_audit_review_disposition_observation_view.c
require_file tests/kernel_runtime_entry_recovery_audit_review_disposition_observation_view.c
require_file tools/kernel_runtime_entry_recovery_audit_review_disposition_observation_view_report.c
require_file scripts/test-kernel-runtime-entry-recovery-audit-review-disposition-observation-view.sh
require_file scripts/test-kernel-runtime-entry-recovery-audit-review-disposition-observation-view-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-observation-view.yml
require_file docs/KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_OBSERVATION_VIEW_SEED.md
require_file include/latticra/kernel_runtime_entry_recovery_audit_review_disposition_review_observation_view.h
require_file src/kernel_runtime_entry_recovery_audit_review_disposition_review_observation_view.c
require_file tests/kernel_runtime_entry_recovery_audit_review_disposition_review_observation_view.c
require_file tools/kernel_runtime_entry_recovery_audit_review_disposition_review_observation_view_report.c
require_file scripts/test-kernel-runtime-entry-recovery-audit-review-disposition-review-observation-view.sh
require_file scripts/test-kernel-runtime-entry-recovery-audit-review-disposition-review-observation-view-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-review-observation-view.yml
require_file docs/KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_OBSERVATION_VIEW_SEED.md
require_file include/latticra/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view.h
require_file src/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view.c
require_file tests/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view.c
require_file tools/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_report.c
require_file scripts/test-kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-observation-view.sh
require_file scripts/test-kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-observation-view-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-observation-view.yml
require_file docs/KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_ARCHIVE_GATE_OBSERVATION_VIEW_SEED.md
require_file include/latticra/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view.h
require_file src/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view.c
require_file tests/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view.c
require_file tools/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_report.c
require_file scripts/test-kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-observation-view.sh
require_file scripts/test-kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-observation-view-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-observation-view.yml
require_file docs/KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_ARCHIVE_GATE_REVIEW_OBSERVATION_VIEW_SEED.md
require_file include/latticra/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view.h
require_file src/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view.c
require_file tests/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view.c
require_file tools/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_report.c
require_file scripts/test-kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-observation-view.sh
require_file scripts/test-kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-observation-view-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-observation-view.yml
require_file docs/KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_OBSERVATION_VIEW_SEED.md
require_file include/latticra/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view.h
require_file src/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view.c
require_file tests/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view.c
require_file tools/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_report.c
require_file scripts/test-kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-observation-view.sh
require_file scripts/test-kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-observation-view-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-observation-view.yml
require_file docs/KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_OBSERVATION_VIEW_SEED.md
require_file include/latticra/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view.h
require_file src/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view.c
require_file tests/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view.c
require_file tools/kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_report.c
require_file scripts/test-kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout-observation-view.sh
require_file scripts/test-kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout-observation-view-report-runner.sh
require_file .github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout-observation-view.yml
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
require_contains 'kernel runtime entry privilege-level-view guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry privilege-level-view report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry syscall-gate-view guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry syscall-gate-view report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry syscall-dispatch-view guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry syscall-dispatch-view report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry syscall-return-view guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry syscall-return-view report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry syscall-exit-view guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry syscall-exit-view report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry user-mode-resume-view guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry user-mode-resume-view report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry post-resume-observation-view guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry post-resume-observation-view report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry scheduler-return-observation-view guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry scheduler-return-observation-view report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry process-return-observation-view guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry process-return-observation-view report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry idle-return-observation-view guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry idle-return-observation-view report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry quiescent-return-observation-view guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry quiescent-return-observation-view report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry persistence-boundary-observation-view guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry persistence-boundary-observation-view report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry recovery-boundary-observation-view guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry recovery-boundary-observation-view report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry recovery-plan-observation-view guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry recovery-plan-observation-view report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry recovery-disposition-observation-view guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry recovery-disposition-observation-view report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel process table guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel process table report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel syscall table guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel syscall table report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel lifecycle subsystem summary' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel lifecycle rollback plan' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'final_state=runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout-observation-view-ready' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'external_effect_performed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'no_external_effect_chain=1' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_recovery_disposition_observation_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_recovery_boundary_observation_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_recovery_plan_observation_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_persistence_boundary_observation_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_quiescent_return_observation_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_idle_return_observation_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_process_return_observation_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_scheduler_return_observation_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_post_resume_observation_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_user_mode_resume_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_syscall_exit_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_syscall_return_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_syscall_dispatch_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_syscall_gate_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_privilege_level_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_address_space_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_stack_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_register_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_frame_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_admission_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'recovery_boundary_observation_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'recovery_boundary_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'recovery_plan_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'recovery_plan_observation_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'recovery_disposition_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'recovery_disposition_observation_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_recovery_outcome_observation_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_recovery_closeout_observation_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_recovery_audit_observation_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_recovery_audit_review_observation_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'recovery_outcome_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'recovery_outcome_observation_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'recovery_closeout_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'recovery_closeout_observation_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'recovery_audit_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'recovery_audit_observation_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'recovery_audit_review_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'recovery_audit_review_observation_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'persistence_boundary_observation_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'persistence_boundary_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'persistence_commit_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
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
require_contains 'kernel runtime entry recovery-outcome-observation-view guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry recovery-outcome-observation-view report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry recovery-closeout-observation-view guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry recovery-closeout-observation-view report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry recovery-audit-observation-view guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry recovery-audit-observation-view report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry recovery-audit-review-observation-view guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry recovery-audit-review-observation-view report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry recovery-audit-review-disposition-observation-view guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry recovery-audit-review-disposition-observation-view report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry recovery-audit-review-disposition-review-observation-view guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry recovery-audit-review-disposition-review-observation-view report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry recovery-audit-review-disposition-review-closeout-observation-view guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry recovery-audit-review-disposition-review-closeout-observation-view report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry recovery-audit-review-disposition-review-closeout-archive-gate-observation-view guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry recovery-audit-review-disposition-review-closeout-archive-gate-observation-view report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry recovery-audit-review-disposition-review-closeout-archive-gate-review-observation-view guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry recovery-audit-review-disposition-review-closeout-archive-gate-review-observation-view report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-observation-view guard' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel runtime entry recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-observation-view report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_recovery_audit_review_disposition_observation_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_recovery_audit_review_disposition_review_observation_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'recovery_audit_review_disposition_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'recovery_audit_review_disposition_observation_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'recovery_audit_review_disposition_review_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'recovery_audit_review_disposition_review_observation_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'recovery_audit_review_disposition_review_closeout_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'recovery_audit_review_disposition_review_closeout_observation_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_observation_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_review_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'Add the next no-effect kernel runtime authority evidence after the recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout observation terminal' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout archive-gate observation evidence report-only' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
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
require_contains '.github/workflows/kernel-runtime-entry-address-space-view.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-privilege-level-view.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-syscall-gate-view.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-syscall-dispatch-view.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-syscall-return-view.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-syscall-exit-view.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-user-mode-resume-view.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-post-resume-observation-view.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-scheduler-return-observation-view.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-process-return-observation-view.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-idle-return-observation-view.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-quiescent-return-observation-view.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-persistence-boundary-observation-view.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-recovery-boundary-observation-view.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-recovery-plan-observation-view.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-recovery-disposition-observation-view.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-recovery-outcome-observation-view.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-recovery-closeout-observation-view.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-recovery-audit-observation-view.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-recovery-audit-review-observation-view.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-observation-view.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-review-observation-view.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-observation-view.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-observation-view.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-observation-view.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-observation-view.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains '.github/workflows/kernel-runtime-entry-recovery-plan-observation-view.yml' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
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
require_contains 'kernel runtime entry privilege-level-view guard' docs/status/README.md
require_contains 'kernel runtime entry privilege-level-view report runner' docs/status/README.md
require_contains 'kernel runtime entry syscall-gate-view guard' docs/status/README.md
require_contains 'kernel runtime entry syscall-gate-view report runner' docs/status/README.md
require_contains 'kernel runtime entry syscall-dispatch-view guard' docs/status/README.md
require_contains 'kernel runtime entry syscall-dispatch-view report runner' docs/status/README.md
require_contains 'kernel runtime entry syscall-return-view guard' docs/status/README.md
require_contains 'kernel runtime entry syscall-return-view report runner' docs/status/README.md
require_contains 'kernel runtime entry syscall-exit-view guard' docs/status/README.md
require_contains 'kernel runtime entry syscall-exit-view report runner' docs/status/README.md
require_contains 'kernel runtime entry user-mode-resume-view guard' docs/status/README.md
require_contains 'kernel runtime entry user-mode-resume-view report runner' docs/status/README.md
require_contains 'kernel runtime entry post-resume-observation-view guard' docs/status/README.md
require_contains 'kernel runtime entry post-resume-observation-view report runner' docs/status/README.md
require_contains 'kernel runtime entry scheduler-return-observation-view guard' docs/status/README.md
require_contains 'kernel runtime entry scheduler-return-observation-view report runner' docs/status/README.md
require_contains 'kernel runtime entry process-return-observation-view guard' docs/status/README.md
require_contains 'kernel runtime entry process-return-observation-view report runner' docs/status/README.md
require_contains 'kernel runtime entry idle-return-observation-view guard' docs/status/README.md
require_contains 'kernel runtime entry idle-return-observation-view report runner' docs/status/README.md
require_contains 'kernel runtime entry quiescent-return-observation-view guard' docs/status/README.md
require_contains 'kernel runtime entry quiescent-return-observation-view report runner' docs/status/README.md
require_contains 'kernel runtime entry persistence-boundary-observation-view guard' docs/status/README.md
require_contains 'kernel runtime entry persistence-boundary-observation-view report runner' docs/status/README.md
require_contains 'kernel runtime entry recovery-boundary-observation-view guard' docs/status/README.md
require_contains 'kernel runtime entry recovery-boundary-observation-view report runner' docs/status/README.md
require_contains 'kernel runtime entry recovery-plan-observation-view guard' docs/status/README.md
require_contains 'kernel runtime entry recovery-plan-observation-view report runner' docs/status/README.md
require_contains 'kernel runtime entry recovery-disposition-observation-view guard' docs/status/README.md
require_contains 'kernel runtime entry recovery-disposition-observation-view report runner' docs/status/README.md
require_contains 'kernel runtime entry recovery-outcome-observation-view guard' docs/status/README.md
require_contains 'kernel runtime entry recovery-outcome-observation-view report runner' docs/status/README.md
require_contains 'kernel runtime entry recovery-closeout-observation-view guard' docs/status/README.md
require_contains 'kernel runtime entry recovery-closeout-observation-view report runner' docs/status/README.md
require_contains 'kernel runtime entry recovery-audit-observation-view guard' docs/status/README.md
require_contains 'kernel runtime entry recovery-audit-observation-view report runner' docs/status/README.md
require_contains 'kernel runtime entry recovery-audit-review-observation-view guard' docs/status/README.md
require_contains 'kernel runtime entry recovery-audit-review-observation-view report runner' docs/status/README.md
require_contains 'kernel runtime entry recovery-audit-review-disposition-observation-view guard' docs/status/README.md
require_contains 'kernel runtime entry recovery-audit-review-disposition-observation-view report runner' docs/status/README.md
require_contains 'kernel runtime entry recovery-audit-review-disposition-review-observation-view guard' docs/status/README.md
require_contains 'kernel runtime entry recovery-audit-review-disposition-review-observation-view report runner' docs/status/README.md
require_contains 'kernel runtime entry recovery-audit-review-disposition-review-closeout-observation-view guard' docs/status/README.md
require_contains 'kernel runtime entry recovery-audit-review-disposition-review-closeout-observation-view report runner' docs/status/README.md
require_contains 'kernel runtime entry recovery-audit-review-disposition-review-closeout-archive-gate-observation-view guard' docs/status/README.md
require_contains 'kernel runtime entry recovery-audit-review-disposition-review-closeout-archive-gate-observation-view report runner' docs/status/README.md
require_contains 'kernel runtime entry recovery-audit-review-disposition-review-closeout-archive-gate-review-observation-view guard' docs/status/README.md
require_contains 'kernel runtime entry recovery-audit-review-disposition-review-closeout-archive-gate-review-observation-view report runner' docs/status/README.md
require_contains 'kernel runtime entry recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-observation-view guard' docs/status/README.md
require_contains 'kernel runtime entry recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-observation-view report runner' docs/status/README.md
require_contains 'kernel process table guard' docs/status/README.md
require_contains 'kernel process table report runner' docs/status/README.md
require_contains 'kernel syscall table guard' docs/status/README.md
require_contains 'kernel syscall table report runner' docs/status/README.md
require_contains 'final_state=runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout-observation-view-ready' docs/status/README.md
require_contains 'external_effect_performed=0' docs/status/README.md
require_contains 'no_external_effect_chain=1' docs/status/README.md
require_contains 'runtime_entry_recovery_disposition_observation_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_recovery_outcome_observation_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_recovery_closeout_observation_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_recovery_audit_observation_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_recovery_audit_review_observation_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_recovery_boundary_observation_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_recovery_plan_observation_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_persistence_boundary_observation_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_quiescent_return_observation_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_idle_return_observation_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_process_return_observation_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_scheduler_return_observation_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_post_resume_observation_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_user_mode_resume_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_syscall_exit_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_syscall_return_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_syscall_dispatch_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_syscall_gate_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_privilege_level_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_address_space_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_stack_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_register_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_frame_allowed=0' docs/status/README.md
require_contains 'runtime_entry_admission_allowed=0' docs/status/README.md
require_contains 'runtime_entry_allowed=0' docs/status/README.md
require_contains 'recovery_boundary_observation_allowed=0' docs/status/README.md
require_contains 'recovery_boundary_allowed=0' docs/status/README.md
require_contains 'recovery_plan_allowed=0' docs/status/README.md
require_contains 'recovery_plan_observation_allowed=0' docs/status/README.md
require_contains 'recovery_disposition_allowed=0' docs/status/README.md
require_contains 'recovery_disposition_observation_allowed=0' docs/status/README.md
require_contains 'recovery_outcome_allowed=0' docs/status/README.md
require_contains 'recovery_outcome_observation_allowed=0' docs/status/README.md
require_contains 'recovery_closeout_allowed=0' docs/status/README.md
require_contains 'recovery_closeout_observation_allowed=0' docs/status/README.md
require_contains 'recovery_audit_allowed=0' docs/status/README.md
require_contains 'recovery_audit_observation_allowed=0' docs/status/README.md
require_contains 'recovery_audit_review_allowed=0' docs/status/README.md
require_contains 'recovery_audit_review_observation_allowed=0' docs/status/README.md
require_contains 'persistence_boundary_observation_allowed=0' docs/status/README.md
require_contains 'persistence_boundary_allowed=0' docs/status/README.md
require_contains 'persistence_commit_allowed=0' docs/status/README.md
require_contains 'quiescent_return_observation_allowed=0' docs/status/README.md
require_contains 'quiescent_return_allowed=0' docs/status/README.md
require_contains 'quiescent_state_read_allowed=0' docs/status/README.md
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
require_contains 'persistence_allowed=0' docs/status/README.md
require_contains 'recovery_authority_allowed=0' docs/status/README.md
require_contains 'dma_allowed=0' docs/status/README.md
require_contains 'hardware_effect_allowed=0' docs/status/README.md
require_contains 'runtime_entry_recovery_audit_review_disposition_observation_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_recovery_audit_review_disposition_review_observation_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_allowed=0' docs/status/README.md
require_contains 'runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_allowed=0' docs/status/README.md
require_contains 'recovery_audit_review_disposition_allowed=0' docs/status/README.md
require_contains 'recovery_audit_review_disposition_observation_allowed=0' docs/status/README.md
require_contains 'recovery_audit_review_disposition_review_allowed=0' docs/status/README.md
require_contains 'recovery_audit_review_disposition_review_observation_allowed=0' docs/status/README.md
require_contains 'recovery_audit_review_disposition_review_closeout_allowed=0' docs/status/README.md
require_contains 'recovery_audit_review_disposition_review_closeout_observation_allowed=0' docs/status/README.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_allowed=0' docs/status/README.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_observation_allowed=0' docs/status/README.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_review_allowed=0' docs/status/README.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_allowed=0' docs/status/README.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_allowed=0' docs/status/README.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_allowed=0' docs/status/README.md
require_contains 'Add the next no-effect kernel runtime authority evidence after the recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout observation terminal' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-admission.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-frame.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-register-view.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-stack-view.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-address-space-view.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-privilege-level-view.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-syscall-gate-view.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-syscall-dispatch-view.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-syscall-return-view.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-syscall-exit-view.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-user-mode-resume-view.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-post-resume-observation-view.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-scheduler-return-observation-view.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-process-return-observation-view.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-idle-return-observation-view.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-quiescent-return-observation-view.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-persistence-boundary-observation-view.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-recovery-boundary-observation-view.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-recovery-disposition-observation-view.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-recovery-outcome-observation-view.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-recovery-closeout-observation-view.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-recovery-audit-observation-view.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-recovery-audit-review-observation-view.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-observation-view.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-review-observation-view.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-observation-view.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-observation-view.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-observation-view.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-observation-view.yml' docs/status/README.md
require_contains '.github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout-observation-view.yml' docs/status/README.md
require_contains '| Kernel lifecycle evidence | No-effect kernel lifecycle, nucleus coupling, and subsystem summary reach `runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout-observation-view-ready`; recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout observation evidence remains report-only' README.md
require_contains '[runtime entry recovery-audit-review-disposition-observation-view seed](docs/KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_OBSERVATION_VIEW_SEED.md)' README.md
require_contains '[runtime entry recovery-audit-review-disposition-review-observation-view seed](docs/KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_OBSERVATION_VIEW_SEED.md)' README.md
require_contains '[runtime entry recovery-audit-review-disposition-review-closeout-observation-view seed](docs/KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_OBSERVATION_VIEW_SEED.md)' README.md
require_contains '[runtime entry recovery-audit-review-disposition-review-closeout-archive-gate-observation-view seed](docs/KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_ARCHIVE_GATE_OBSERVATION_VIEW_SEED.md)' README.md
require_contains '[runtime entry recovery-audit-review-disposition-review-closeout-archive-gate-review-observation-view seed](docs/KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_ARCHIVE_GATE_REVIEW_OBSERVATION_VIEW_SEED.md)' README.md
require_contains '[runtime entry recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-observation-view seed](docs/KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_OBSERVATION_VIEW_SEED.md)' README.md
require_contains '[runtime entry recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout-observation-view seed](docs/KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_OBSERVATION_VIEW_SEED.md)' README.md
require_contains '[nucleus kernel coupling readiness](docs/NUCLEUS_KERNEL_COUPLING_READINESS.md)' README.md
require_contains 'kernel_lifecycle_final_state=runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout-observation-view-ready' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'runtime_recovery_audit_observation_view_status=runtime-entry-recovery-audit-observation-view-seed-ready' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'runtime_recovery_audit_review_observation_view_status=runtime-entry-recovery-audit-review-observation-view-seed-ready' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'runtime_recovery_audit_review_disposition_observation_view_status=runtime-entry-recovery-audit-review-disposition-observation-view-seed-ready' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'runtime_recovery_audit_review_disposition_review_observation_view_status=runtime-entry-recovery-audit-review-disposition-review-observation-view-seed-ready' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'runtime_recovery_audit_review_disposition_review_closeout_observation_view_status=runtime-entry-recovery-audit-review-disposition-review-closeout-observation-view-seed-ready' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'runtime_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_status=runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-observation-view-seed-ready' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'runtime_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_status=runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-observation-view-seed-ready' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'runtime_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_status=runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-observation-view-seed-ready' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'runtime_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_status=runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout-observation-view-seed-ready' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'lifecycle_step_count=54' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'lifecycle_state_change_count=54' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'recovery_audit_observation_view_count=4' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'recovery_audit_review_observation_view_count=4' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'recovery_audit_review_disposition_observation_view_count=4' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'recovery_audit_review_disposition_review_observation_view_count=4' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'recovery_audit_review_disposition_review_closeout_observation_view_count=4' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_count=4' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_count=4' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_count=4' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_count=4' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'runtime_recovery_audit_observation_view_allowed=0' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'runtime_recovery_audit_review_observation_view_allowed=0' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'runtime_recovery_audit_review_disposition_observation_view_allowed=0' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'runtime_recovery_audit_review_disposition_review_observation_view_allowed=0' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'runtime_recovery_audit_review_disposition_review_closeout_observation_view_allowed=0' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'runtime_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_allowed=0' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'runtime_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_allowed=0' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'runtime_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_allowed=0' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'runtime_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_allowed=0' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'recovery_audit_allowed=0' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'recovery_audit_observation_allowed=0' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'recovery_audit_review_allowed=0' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'recovery_audit_review_observation_allowed=0' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'recovery_audit_review_disposition_allowed=0' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'recovery_audit_review_disposition_observation_allowed=0' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'recovery_audit_review_disposition_review_allowed=0' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'recovery_audit_review_disposition_review_observation_allowed=0' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'recovery_audit_review_disposition_review_closeout_allowed=0' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'recovery_audit_review_disposition_review_closeout_observation_allowed=0' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_allowed=0' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_observation_allowed=0' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_review_allowed=0' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_allowed=0' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_allowed=0' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_allowed=0' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_allowed=0' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_allowed=0' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
require_contains 'evidence_level=57' docs/NUCLEUS_KERNEL_COUPLING_READINESS.md
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
require_contains 'kernel_runtime_entry_privilege_level_view_guard_present=1' README.md
require_contains 'kernel_runtime_entry_syscall_gate_view_guard_present=1' README.md
require_contains 'kernel_runtime_entry_syscall_dispatch_view_guard_present=1' README.md
require_contains 'kernel_runtime_entry_syscall_return_view_guard_present=1' README.md
require_contains 'kernel_runtime_entry_syscall_exit_view_guard_present=1' README.md
require_contains 'kernel_runtime_entry_user_mode_resume_view_guard_present=1' README.md
require_contains 'kernel_runtime_entry_post_resume_observation_view_guard_present=1' README.md
require_contains 'kernel_runtime_entry_scheduler_return_observation_view_guard_present=1' README.md
require_contains 'kernel_runtime_entry_process_return_observation_view_guard_present=1' README.md
require_contains 'kernel_runtime_entry_idle_return_observation_view_guard_present=1' README.md
require_contains 'kernel_runtime_entry_quiescent_return_observation_view_guard_present=1' README.md
require_contains 'kernel_runtime_entry_persistence_boundary_observation_view_guard_present=1' README.md
require_contains 'kernel_runtime_entry_recovery_boundary_observation_view_guard_present=1' README.md
require_contains 'kernel_runtime_entry_recovery_plan_observation_view_guard_present=1' README.md
require_contains 'kernel_runtime_entry_recovery_disposition_observation_view_guard_present=1' README.md
require_contains 'kernel_runtime_entry_recovery_outcome_observation_view_guard_present=1' README.md
require_contains 'kernel_runtime_entry_recovery_closeout_observation_view_guard_present=1' README.md
require_contains 'kernel_runtime_entry_recovery_audit_observation_view_guard_present=1' README.md
require_contains 'kernel_runtime_entry_recovery_audit_review_observation_view_guard_present=1' README.md
require_contains 'kernel_runtime_entry_recovery_audit_review_disposition_observation_view_guard_present=1' README.md
require_contains 'kernel_runtime_entry_recovery_audit_review_disposition_review_observation_view_guard_present=1' README.md
require_contains 'kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_guard_present=1' README.md
require_contains 'kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_guard_present=1' README.md
require_contains 'kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_guard_present=1' README.md
require_contains 'kernel_runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_guard_present=1' README.md
require_contains 'kernel_process_table_guard_present=1' README.md
require_contains 'kernel_syscall_table_guard_present=1' README.md
require_contains 'final_state=runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout-observation-view-ready' README.md
require_contains 'runtime_entry_recovery_disposition_observation_view_allowed=0' README.md
require_contains 'runtime_entry_recovery_outcome_observation_view_allowed=0' README.md
require_contains 'runtime_entry_recovery_closeout_observation_view_allowed=0' README.md
require_contains 'runtime_entry_recovery_audit_observation_view_allowed=0' README.md
require_contains 'runtime_entry_recovery_audit_review_observation_view_allowed=0' README.md
require_contains 'runtime_entry_recovery_audit_review_disposition_observation_view_allowed=0' README.md
require_contains 'runtime_entry_recovery_audit_review_disposition_review_observation_view_allowed=0' README.md
require_contains 'runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_allowed=0' README.md
require_contains 'runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_allowed=0' README.md
require_contains 'runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_allowed=0' README.md
require_contains 'runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_allowed=0' README.md
require_contains 'runtime_entry_recovery_plan_observation_view_allowed=0' README.md
require_contains 'runtime_entry_recovery_boundary_observation_view_allowed=0' README.md
require_contains 'runtime_entry_recovery_plan_observation_view_allowed=0' README.md
require_contains 'runtime_entry_persistence_boundary_observation_view_allowed=0' README.md
require_contains 'runtime_entry_quiescent_return_observation_view_allowed=0' README.md
require_contains 'runtime_entry_idle_return_observation_view_allowed=0' README.md
require_contains 'runtime_entry_process_return_observation_view_allowed=0' README.md
require_contains 'runtime_entry_scheduler_return_observation_view_allowed=0' README.md
require_contains 'runtime_entry_post_resume_observation_view_allowed=0' README.md
require_contains 'runtime_entry_user_mode_resume_view_allowed=0' README.md
require_contains 'runtime_entry_syscall_exit_view_allowed=0' README.md
require_contains 'runtime_entry_syscall_return_view_allowed=0' README.md
require_contains 'runtime_entry_syscall_dispatch_view_allowed=0' README.md
require_contains 'runtime_entry_syscall_gate_view_allowed=0' README.md
require_contains 'runtime_entry_privilege_level_view_allowed=0' README.md
require_contains 'runtime_entry_address_space_view_allowed=0' README.md
require_contains 'runtime_entry_stack_view_allowed=0' README.md
require_contains 'runtime_entry_register_view_allowed=0' README.md
require_contains 'runtime_entry_frame_allowed=0' README.md
require_contains 'runtime_entry_admission_allowed=0' README.md
require_contains 'runtime_entry_allowed=0' README.md
require_contains 'recovery_boundary_observation_allowed=0' README.md
require_contains 'recovery_boundary_allowed=0' README.md
require_contains 'recovery_plan_allowed=0' README.md
require_contains 'recovery_plan_observation_allowed=0' README.md
require_contains 'recovery_disposition_allowed=0' README.md
require_contains 'recovery_disposition_observation_allowed=0' README.md
require_contains 'recovery_outcome_allowed=0' README.md
require_contains 'recovery_outcome_observation_allowed=0' README.md
require_contains 'recovery_closeout_allowed=0' README.md
require_contains 'recovery_closeout_observation_allowed=0' README.md
require_contains 'recovery_audit_allowed=0' README.md
require_contains 'recovery_audit_observation_allowed=0' README.md
require_contains 'recovery_audit_review_allowed=0' README.md
require_contains 'recovery_audit_review_observation_allowed=0' README.md
require_contains 'recovery_audit_review_disposition_allowed=0' README.md
require_contains 'recovery_audit_review_disposition_observation_allowed=0' README.md
require_contains 'recovery_audit_review_disposition_review_allowed=0' README.md
require_contains 'recovery_audit_review_disposition_review_observation_allowed=0' README.md
require_contains 'recovery_audit_review_disposition_review_closeout_allowed=0' README.md
require_contains 'recovery_audit_review_disposition_review_closeout_observation_allowed=0' README.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_allowed=0' README.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_observation_allowed=0' README.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_review_allowed=0' README.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_allowed=0' README.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_allowed=0' README.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_allowed=0' README.md
require_contains 'persistence_boundary_observation_allowed=0' README.md
require_contains 'persistence_boundary_allowed=0' README.md
require_contains 'persistence_commit_allowed=0' README.md
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
require_contains 'docs/KERNEL_RUNTIME_ENTRY_PRIVILEGE_LEVEL_VIEW_SEED.md' README.md
require_contains 'docs/KERNEL_RUNTIME_ENTRY_SYSCALL_GATE_VIEW_SEED.md' README.md
require_contains 'docs/KERNEL_RUNTIME_ENTRY_SYSCALL_DISPATCH_VIEW_SEED.md' README.md
require_contains 'docs/KERNEL_RUNTIME_ENTRY_SYSCALL_RETURN_VIEW_SEED.md' README.md
require_contains 'docs/KERNEL_RUNTIME_ENTRY_SYSCALL_EXIT_VIEW_SEED.md' README.md
require_contains 'docs/KERNEL_RUNTIME_ENTRY_USER_MODE_RESUME_VIEW_SEED.md' README.md
require_contains 'docs/KERNEL_RUNTIME_ENTRY_POST_RESUME_OBSERVATION_VIEW_SEED.md' README.md
require_contains 'docs/KERNEL_RUNTIME_ENTRY_SCHEDULER_RETURN_OBSERVATION_VIEW_SEED.md' README.md
require_contains 'docs/KERNEL_RUNTIME_ENTRY_PROCESS_RETURN_OBSERVATION_VIEW_SEED.md' README.md
require_contains 'docs/KERNEL_RUNTIME_ENTRY_IDLE_RETURN_OBSERVATION_VIEW_SEED.md' README.md
require_contains 'docs/KERNEL_RUNTIME_ENTRY_PERSISTENCE_BOUNDARY_OBSERVATION_VIEW_SEED.md' README.md
require_contains 'docs/KERNEL_RUNTIME_ENTRY_RECOVERY_BOUNDARY_OBSERVATION_VIEW_SEED.md' README.md
require_contains 'docs/KERNEL_RUNTIME_ENTRY_RECOVERY_PLAN_OBSERVATION_VIEW_SEED.md' README.md
require_contains 'docs/KERNEL_RUNTIME_ENTRY_RECOVERY_DISPOSITION_OBSERVATION_VIEW_SEED.md' README.md
require_contains 'docs/KERNEL_RUNTIME_ENTRY_RECOVERY_OUTCOME_OBSERVATION_VIEW_SEED.md' README.md
require_contains 'docs/KERNEL_RUNTIME_ENTRY_RECOVERY_CLOSEOUT_OBSERVATION_VIEW_SEED.md' README.md
require_contains 'docs/KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_OBSERVATION_VIEW_SEED.md' README.md
require_contains 'docs/KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_OBSERVATION_VIEW_SEED.md' README.md
require_contains 'docs/KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_OBSERVATION_VIEW_SEED.md' README.md
require_contains 'docs/KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_OBSERVATION_VIEW_SEED.md' README.md
require_contains 'docs/KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_OBSERVATION_VIEW_SEED.md' README.md
require_contains 'docs/KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_ARCHIVE_GATE_OBSERVATION_VIEW_SEED.md' README.md
require_contains 'docs/KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_ARCHIVE_GATE_REVIEW_OBSERVATION_VIEW_SEED.md' README.md
require_contains 'docs/KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_OBSERVATION_VIEW_SEED.md' README.md
require_contains 'docs/KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_OBSERVATION_VIEW_SEED.md' README.md
require_contains 'docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md' README.md
require_contains 'Latest kernel lifecycle evidence status note: 2026-05-27 CDT' STATUS.md
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
require_contains 'Kernel runtime entry privilege-level-view seed' STATUS.md
require_contains 'Kernel runtime entry syscall-gate-view seed' STATUS.md
require_contains 'Kernel runtime entry syscall-dispatch-view seed' STATUS.md
require_contains 'Kernel runtime entry syscall-return-view seed' STATUS.md
require_contains 'Kernel runtime entry syscall-exit-view seed' STATUS.md
require_contains 'Kernel runtime entry user-mode-resume-view seed' STATUS.md
require_contains 'Kernel runtime entry post-resume-observation-view seed' STATUS.md
require_contains 'Kernel runtime entry scheduler-return-observation-view seed' STATUS.md
require_contains 'Kernel runtime entry process-return-observation-view seed' STATUS.md
require_contains 'Kernel runtime entry idle-return-observation-view seed' STATUS.md
require_contains 'Kernel runtime entry quiescent-return-observation-view seed' STATUS.md
require_contains 'Kernel runtime entry persistence-boundary-observation-view seed' STATUS.md
require_contains 'Kernel runtime entry recovery-boundary-observation-view seed' STATUS.md
require_contains 'Kernel runtime entry recovery-plan-observation-view seed' STATUS.md
require_contains 'Kernel runtime entry recovery-disposition-observation-view seed' STATUS.md
require_contains 'Kernel runtime entry recovery-outcome-observation-view seed' STATUS.md
require_contains 'Kernel runtime entry recovery-closeout-observation-view seed' STATUS.md
require_contains 'Kernel runtime entry recovery-audit-observation-view seed' STATUS.md
require_contains 'Kernel runtime entry recovery-audit-review-observation-view seed' STATUS.md
require_contains 'Kernel runtime entry recovery-audit-review-disposition-observation-view seed' STATUS.md
require_contains 'Kernel runtime entry recovery-audit-review-disposition-review-observation-view seed' STATUS.md
require_contains 'Kernel runtime entry recovery-audit-review-disposition-review-closeout-observation-view seed' STATUS.md
require_contains 'Kernel runtime entry recovery-audit-review-disposition-review-closeout-archive-gate-observation-view seed' STATUS.md
require_contains 'Kernel runtime entry recovery-audit-review-disposition-review-closeout-archive-gate-review-observation-view seed' STATUS.md
require_contains 'Kernel runtime entry recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-observation-view seed' STATUS.md
require_contains 'Kernel lifecycle rollback plan' STATUS.md
require_contains 'Latest kernel lifecycle evidence status note: 2026-05-27 CDT' docs/status/CURRENT_STATUS.md
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
require_contains 'Kernel runtime entry privilege-level-view seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel runtime entry syscall-gate-view seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel runtime entry syscall-dispatch-view seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel runtime entry syscall-return-view seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel runtime entry syscall-exit-view seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel runtime entry user-mode-resume-view seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel runtime entry post-resume-observation-view seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel runtime entry scheduler-return-observation-view seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel runtime entry process-return-observation-view seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel runtime entry idle-return-observation-view seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel runtime entry quiescent-return-observation-view seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel runtime entry persistence-boundary-observation-view seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel runtime entry recovery-boundary-observation-view seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel runtime entry recovery-plan-observation-view seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel runtime entry recovery-disposition-observation-view seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel runtime entry recovery-outcome-observation-view seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel runtime entry recovery-closeout-observation-view seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel runtime entry recovery-audit-observation-view seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel runtime entry recovery-audit-review-observation-view seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel runtime entry recovery-audit-review-disposition-observation-view seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel runtime entry recovery-audit-review-disposition-review-observation-view seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel runtime entry recovery-audit-review-disposition-review-closeout-observation-view seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel runtime entry recovery-audit-review-disposition-review-closeout-archive-gate-observation-view seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel runtime entry recovery-audit-review-disposition-review-closeout-archive-gate-review-observation-view seed' docs/status/CURRENT_STATUS.md
require_contains 'Kernel runtime entry recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-observation-view seed' docs/status/CURRENT_STATUS.md
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
require_contains 'KERNEL_RUNTIME_ENTRY_PRIVILEGE_LEVEL_VIEW_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_SYSCALL_GATE_VIEW_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_SYSCALL_DISPATCH_VIEW_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_SYSCALL_RETURN_VIEW_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_SYSCALL_EXIT_VIEW_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_USER_MODE_RESUME_VIEW_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_POST_RESUME_OBSERVATION_VIEW_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_SCHEDULER_RETURN_OBSERVATION_VIEW_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_PROCESS_RETURN_OBSERVATION_VIEW_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_IDLE_RETURN_OBSERVATION_VIEW_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_QUIESCENT_RETURN_OBSERVATION_VIEW_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_PERSISTENCE_BOUNDARY_OBSERVATION_VIEW_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_RECOVERY_BOUNDARY_OBSERVATION_VIEW_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_RECOVERY_PLAN_OBSERVATION_VIEW_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_RECOVERY_DISPOSITION_OBSERVATION_VIEW_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_RECOVERY_OUTCOME_OBSERVATION_VIEW_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_RECOVERY_CLOSEOUT_OBSERVATION_VIEW_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_OBSERVATION_VIEW_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_OBSERVATION_VIEW_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_OBSERVATION_VIEW_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_OBSERVATION_VIEW_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_OBSERVATION_VIEW_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_ARCHIVE_GATE_OBSERVATION_VIEW_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_ARCHIVE_GATE_REVIEW_OBSERVATION_VIEW_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_OBSERVATION_VIEW_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'KERNEL_RUNTIME_ENTRY_RECOVERY_AUDIT_REVIEW_DISPOSITION_REVIEW_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_OBSERVATION_VIEW_SEED.md' docs/FOUNDATION_INDEX.md
require_contains 'runtime-entry-quiescent-return-observation-view-ready' docs/KERNEL_LIFECYCLE_SEED.md
require_contains 'runtime-entry-persistence-boundary-observation-view-ready' docs/KERNEL_LIFECYCLE_SEED.md
require_contains 'runtime-entry-recovery-closeout-observation-view-ready' docs/KERNEL_LIFECYCLE_SEED.md
require_contains 'runtime-entry-recovery-audit-observation-view-ready' docs/KERNEL_LIFECYCLE_SEED.md
require_contains 'runtime-entry-recovery-audit-review-disposition-observation-view-ready' docs/KERNEL_LIFECYCLE_SEED.md
require_contains 'runtime-entry-recovery-disposition-observation-view-ready -> runtime-entry-recovery-outcome-observation-view-ready' docs/KERNEL_LIFECYCLE_SEED.md
require_contains 'runtime-entry-recovery-outcome-observation-view-ready -> runtime-entry-recovery-closeout-observation-view-ready' docs/KERNEL_LIFECYCLE_SEED.md
require_contains 'runtime-entry-recovery-closeout-observation-view-ready -> runtime-entry-recovery-audit-observation-view-ready' docs/KERNEL_LIFECYCLE_SEED.md
require_contains 'runtime-entry-recovery-audit-observation-view-ready -> runtime-entry-recovery-audit-review-observation-view-ready' docs/KERNEL_LIFECYCLE_SEED.md
require_contains 'runtime-entry-recovery-audit-review-observation-view-ready -> runtime-entry-recovery-audit-review-disposition-observation-view-ready' docs/KERNEL_LIFECYCLE_SEED.md
require_contains 'runtime-entry-recovery-audit-review-disposition-observation-view-ready -> runtime-entry-recovery-audit-review-disposition-review-observation-view-ready' docs/KERNEL_LIFECYCLE_SEED.md
require_contains 'runtime-entry-recovery-audit-review-disposition-review-observation-view-ready -> runtime-entry-recovery-audit-review-disposition-review-closeout-observation-view-ready' docs/KERNEL_LIFECYCLE_SEED.md
require_contains 'runtime-entry-recovery-audit-review-disposition-review-closeout-observation-view-ready -> runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-observation-view-ready' docs/KERNEL_LIFECYCLE_SEED.md
require_contains 'runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-observation-view-ready -> runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-observation-view-ready' docs/KERNEL_LIFECYCLE_SEED.md
require_contains 'runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-observation-view-ready -> runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-observation-view-ready' docs/KERNEL_LIFECYCLE_SEED.md
require_contains 'runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-observation-view-ready -> runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout-observation-view-ready' docs/KERNEL_LIFECYCLE_SEED.md
require_contains 'state_change_count=54' docs/KERNEL_LIFECYCLE_SEED.md
require_contains 'machine_log_count=54' docs/KERNEL_LIFECYCLE_SEED.md
require_contains 'runtime_entry_recovery_outcome_observation_view_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'runtime_entry_recovery_audit_review_disposition_review_closeout_observation_view_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_observation_view_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_view_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_view_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'runtime_entry_recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_view_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'runtime_entry_recovery_audit_review_disposition_review_observation_view_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'runtime_entry_recovery_audit_review_disposition_observation_view_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'runtime_entry_recovery_audit_review_observation_view_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'runtime_entry_recovery_audit_observation_view_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'runtime_entry_recovery_closeout_observation_view_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'runtime_entry_recovery_disposition_observation_view_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'runtime_entry_recovery_boundary_observation_view_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'runtime_entry_recovery_plan_observation_view_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'runtime_entry_persistence_boundary_observation_view_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'runtime_entry_quiescent_return_observation_view_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'runtime_entry_idle_return_observation_view_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'runtime_entry_process_return_observation_view_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'runtime_entry_scheduler_return_observation_view_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'runtime_entry_post_resume_observation_view_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'recovery_boundary_observation_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'recovery_boundary_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'recovery_plan_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'recovery_plan_observation_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'recovery_disposition_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'recovery_disposition_observation_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'recovery_outcome_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'recovery_outcome_observation_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'recovery_audit_review_disposition_review_closeout_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'recovery_audit_review_disposition_review_closeout_observation_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_observation_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_review_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_review_observation_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_observation_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'recovery_audit_review_disposition_review_closeout_archive_gate_review_disposition_closeout_observation_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'recovery_audit_review_disposition_review_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'recovery_audit_review_disposition_review_observation_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'recovery_audit_review_disposition_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'recovery_audit_review_disposition_observation_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'recovery_audit_review_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'recovery_audit_review_observation_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'recovery_audit_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'recovery_audit_observation_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'recovery_closeout_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'recovery_closeout_observation_allowed=0' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_contains 'runtime -> runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-closeout-observation-view-ready' docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
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
require_contains 'sh scripts/test-kernel-runtime-entry-privilege-level-view.sh' .github/workflows/kernel-runtime-entry-privilege-level-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-privilege-level-view-report-runner.sh' .github/workflows/kernel-runtime-entry-privilege-level-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-syscall-gate-view.sh' .github/workflows/kernel-runtime-entry-syscall-gate-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-syscall-gate-view-report-runner.sh' .github/workflows/kernel-runtime-entry-syscall-gate-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-syscall-dispatch-view.sh' .github/workflows/kernel-runtime-entry-syscall-dispatch-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-syscall-dispatch-view-report-runner.sh' .github/workflows/kernel-runtime-entry-syscall-dispatch-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-syscall-return-view.sh' .github/workflows/kernel-runtime-entry-syscall-return-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-syscall-return-view-report-runner.sh' .github/workflows/kernel-runtime-entry-syscall-return-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-syscall-exit-view.sh' .github/workflows/kernel-runtime-entry-syscall-exit-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-syscall-exit-view-report-runner.sh' .github/workflows/kernel-runtime-entry-syscall-exit-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-user-mode-resume-view.sh' .github/workflows/kernel-runtime-entry-user-mode-resume-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-user-mode-resume-view-report-runner.sh' .github/workflows/kernel-runtime-entry-user-mode-resume-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-post-resume-observation-view.sh' .github/workflows/kernel-runtime-entry-post-resume-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-post-resume-observation-view-report-runner.sh' .github/workflows/kernel-runtime-entry-post-resume-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-scheduler-return-observation-view.sh' .github/workflows/kernel-runtime-entry-scheduler-return-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-scheduler-return-observation-view-report-runner.sh' .github/workflows/kernel-runtime-entry-scheduler-return-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-process-return-observation-view.sh' .github/workflows/kernel-runtime-entry-process-return-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-process-return-observation-view-report-runner.sh' .github/workflows/kernel-runtime-entry-process-return-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-idle-return-observation-view.sh' .github/workflows/kernel-runtime-entry-idle-return-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-idle-return-observation-view-report-runner.sh' .github/workflows/kernel-runtime-entry-idle-return-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-quiescent-return-observation-view.sh' .github/workflows/kernel-runtime-entry-quiescent-return-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-quiescent-return-observation-view-report-runner.sh' .github/workflows/kernel-runtime-entry-quiescent-return-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-persistence-boundary-observation-view.sh' .github/workflows/kernel-runtime-entry-persistence-boundary-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-persistence-boundary-observation-view-report-runner.sh' .github/workflows/kernel-runtime-entry-persistence-boundary-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-recovery-boundary-observation-view.sh' .github/workflows/kernel-runtime-entry-recovery-boundary-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-recovery-boundary-observation-view-report-runner.sh' .github/workflows/kernel-runtime-entry-recovery-boundary-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-recovery-plan-observation-view.sh' .github/workflows/kernel-runtime-entry-recovery-plan-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-recovery-plan-observation-view-report-runner.sh' .github/workflows/kernel-runtime-entry-recovery-plan-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-recovery-disposition-observation-view.sh' .github/workflows/kernel-runtime-entry-recovery-disposition-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-recovery-disposition-observation-view-report-runner.sh' .github/workflows/kernel-runtime-entry-recovery-disposition-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-recovery-outcome-observation-view.sh' .github/workflows/kernel-runtime-entry-recovery-outcome-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-recovery-outcome-observation-view-report-runner.sh' .github/workflows/kernel-runtime-entry-recovery-outcome-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-recovery-closeout-observation-view.sh' .github/workflows/kernel-runtime-entry-recovery-closeout-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-recovery-closeout-observation-view-report-runner.sh' .github/workflows/kernel-runtime-entry-recovery-closeout-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-recovery-audit-observation-view.sh' .github/workflows/kernel-runtime-entry-recovery-audit-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-recovery-audit-observation-view-report-runner.sh' .github/workflows/kernel-runtime-entry-recovery-audit-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-recovery-audit-review-observation-view.sh' .github/workflows/kernel-runtime-entry-recovery-audit-review-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-recovery-audit-review-observation-view-report-runner.sh' .github/workflows/kernel-runtime-entry-recovery-audit-review-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-recovery-audit-review-disposition-observation-view.sh' .github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-recovery-audit-review-disposition-observation-view-report-runner.sh' .github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-recovery-audit-review-disposition-review-observation-view.sh' .github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-review-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-recovery-audit-review-disposition-review-observation-view-report-runner.sh' .github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-review-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-observation-view.sh' .github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-observation-view-report-runner.sh' .github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-observation-view.sh' .github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-observation-view-report-runner.sh' .github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-observation-view.sh' .github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-observation-view-report-runner.sh' .github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-observation-view.sh' .github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-observation-view.yml
require_contains 'sh scripts/test-kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-observation-view-report-runner.sh' .github/workflows/kernel-runtime-entry-recovery-audit-review-disposition-review-closeout-archive-gate-review-disposition-observation-view.yml
require_contains 'sh scripts/test-kernel-process-table.sh' .github/workflows/kernel-process-table.yml
require_contains 'sh scripts/test-kernel-process-table-report-runner.sh' .github/workflows/kernel-process-table.yml
require_contains 'sh scripts/test-kernel-syscall-table.sh' .github/workflows/kernel-syscall-table.yml
require_contains 'sh scripts/test-kernel-syscall-table-report-runner.sh' .github/workflows/kernel-syscall-table.yml

printf 'kernel_lifecycle_status_alignment: ok\n'
