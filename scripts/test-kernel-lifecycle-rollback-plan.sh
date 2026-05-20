#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'kernel lifecycle rollback plan: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'kernel lifecycle rollback plan: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_file docs/KERNEL_LIFECYCLE_ROLLBACK_PLAN.md
require_file docs/KERNEL_LIFECYCLE_SEED.md
require_file include/latticra/kernel_lifecycle.h
require_file src/kernel_lifecycle.c
require_file scripts/test-kernel-lifecycle.sh

require_contains 'Status: planning and guardrail record' docs/KERNEL_LIFECYCLE_ROLLBACK_PLAN.md
require_contains 'Scope: rollback semantics for the bounded kernel lifecycle sequence.' docs/KERNEL_LIFECYCLE_ROLLBACK_PLAN.md
require_contains 'record the last safe lifecycle state' docs/KERNEL_LIFECYCLE_ROLLBACK_PLAN.md
require_contains 'classify the incomplete transition' docs/KERNEL_LIFECYCLE_ROLLBACK_PLAN.md
require_contains 'preserve the no-external-effect boundary' docs/KERNEL_LIFECYCLE_ROLLBACK_PLAN.md
require_contains 'created -> initialized' docs/KERNEL_LIFECYCLE_ROLLBACK_PLAN.md
require_contains 'initialized -> registry-ready' docs/KERNEL_LIFECYCLE_ROLLBACK_PLAN.md
require_contains 'registry-ready -> scheduler-ready' docs/KERNEL_LIFECYCLE_ROLLBACK_PLAN.md
require_contains 'scheduler-ready -> memory-map-ready' docs/KERNEL_LIFECYCLE_ROLLBACK_PLAN.md
require_contains 'step-limit-reached' docs/KERNEL_LIFECYCLE_ROLLBACK_PLAN.md
require_contains 'external-effect-blocked' docs/KERNEL_LIFECYCLE_ROLLBACK_PLAN.md
require_contains 'rollback_required=1' docs/KERNEL_LIFECYCLE_ROLLBACK_PLAN.md
require_contains 'rollback_performed=0' docs/KERNEL_LIFECYCLE_ROLLBACK_PLAN.md
require_contains 'last_safe_state=registry-ready' docs/KERNEL_LIFECYCLE_ROLLBACK_PLAN.md
require_contains 'external_effect_performed=0' docs/KERNEL_LIFECYCLE_ROLLBACK_PLAN.md
require_contains 'persistence_allowed=0' docs/KERNEL_LIFECYCLE_ROLLBACK_PLAN.md
require_contains 'recovery_authority_allowed=0' docs/KERNEL_LIFECYCLE_ROLLBACK_PLAN.md
require_contains 'runtime_entry_allowed=0' docs/KERNEL_LIFECYCLE_ROLLBACK_PLAN.md
require_contains 'Rollback planning must remain report-only' docs/KERNEL_LIFECYCLE_ROLLBACK_PLAN.md
require_contains 'This plan does not implement rollback.' docs/KERNEL_LIFECYCLE_ROLLBACK_PLAN.md
require_contains 'kernel_lifecycle_rollback_plan: ok' docs/KERNEL_LIFECYCLE_ROLLBACK_PLAN.md

printf 'kernel_lifecycle_rollback_plan: ok\n'
