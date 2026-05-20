#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora readiness plan: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora readiness plan: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/FEDORA_READINESS_PLAN.md
require_file docs/LICENSE_MIGRATION_PLAN.md
require_file docs/OPEN_ECOSYSTEM_POLICY.md
require_file docs/KERNEL_LIFECYCLE_SEED.md
require_file docs/KERNEL_LIFECYCLE_SUBSYSTEM_SUMMARY.md
require_file docs/KERNEL_LIFECYCLE_ROLLBACK_PLAN.md

require_contains 'Status: planning and compatibility record' docs/FEDORA_READINESS_PLAN.md
require_contains 'preparing Latticra for Fedora-friendly packaging, testing, and community review' docs/FEDORA_READINESS_PLAN.md
require_contains 'without claiming Fedora acceptance, endorsement, official inclusion, or distribution status' docs/FEDORA_READINESS_PLAN.md
require_contains 'Fedora readiness' docs/FEDORA_READINESS_PLAN.md
require_contains 'Fedora packaging readiness' docs/FEDORA_READINESS_PLAN.md
require_contains 'Latticra on Fedora' docs/FEDORA_READINESS_PLAN.md
require_contains 'future package review candidate' docs/FEDORA_READINESS_PLAN.md
require_contains 'official Fedora package' docs/FEDORA_READINESS_PLAN.md
require_contains 'Fedora spin' docs/FEDORA_READINESS_PLAN.md
require_contains 'Fedora remix' docs/FEDORA_READINESS_PLAN.md
require_contains 'Fedora endorsement' docs/FEDORA_READINESS_PLAN.md
require_contains 'Fedora allowed license posture' docs/FEDORA_READINESS_PLAN.md
require_contains 'BuildRequires completeness' docs/FEDORA_READINESS_PLAN.md
require_contains 'mock build readiness' docs/FEDORA_READINESS_PLAN.md
require_contains 'final_state=memory-map-ready' docs/FEDORA_READINESS_PLAN.md
require_contains 'external_effect_performed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'runtime_entry_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'scheduler_execution_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'memory_allocation_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'not bootable' docs/FEDORA_READINESS_PLAN.md
require_contains 'not a Fedora derivative' docs/FEDORA_READINESS_PLAN.md
require_contains 'Phase 1: Fedora build lane' docs/FEDORA_READINESS_PLAN.md
require_contains 'Phase 2: package metadata lane' docs/FEDORA_READINESS_PLAN.md
require_contains 'Phase 3: license and source audit lane' docs/FEDORA_READINESS_PLAN.md
require_contains 'Phase 4: local RPM and mock lane' docs/FEDORA_READINESS_PLAN.md
require_contains 'Phase 5: Fedora review candidate lane' docs/FEDORA_READINESS_PLAN.md
require_contains 'Add Fedora build lane plan' docs/FEDORA_READINESS_PLAN.md
require_contains 'fedora_readiness_plan: ok' docs/FEDORA_READINESS_PLAN.md

printf 'fedora_readiness_plan: ok\n'
