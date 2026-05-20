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
require_file scripts/test-kernel-lifecycle-subsystem-summary.sh
require_file scripts/test-kernel-lifecycle-subsystem-summary-report-runner.sh
require_file scripts/test-kernel-lifecycle-rollback-plan.sh

require_contains 'Status: status alignment record' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'PR #170 — kernel lifecycle report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'PR #171 — kernel lifecycle subsystem summary' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'PR #172 — kernel lifecycle rollback plan' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel lifecycle report runner' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel lifecycle subsystem summary' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'kernel lifecycle rollback plan' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'final_state=memory-map-ready' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'external_effect_performed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'no_external_effect_chain=1' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'runtime_entry_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'scheduler_execution_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'memory_allocation_allowed=0' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md
require_contains 'Add no-effect rollback classifier' docs/status/KERNEL_LIFECYCLE_EVIDENCE_STATUS.md

require_contains 'KERNEL_LIFECYCLE_EVIDENCE_STATUS.md' docs/status/README.md
require_contains 'Current kernel lifecycle checkpoint' docs/status/README.md
require_contains 'final_state=memory-map-ready' docs/status/README.md
require_contains 'external_effect_performed=0' docs/status/README.md
require_contains 'runtime_entry_allowed=0' docs/status/README.md
require_contains 'scheduler_execution_allowed=0' docs/status/README.md
require_contains 'memory_allocation_allowed=0' docs/status/README.md

printf 'kernel_lifecycle_status_alignment: ok\n'
