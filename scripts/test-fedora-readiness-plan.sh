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
require_file scripts/test-fedora-build-lane.sh
require_file .github/workflows/fedora-build-lane.yml
require_file .github/workflows/compat-linux.yml
require_file packaging/fedora/latticra.spec
require_file packaging/fedora/README.md
require_file scripts/test-fedora-spec-static.sh
require_file .github/workflows/fedora-spec-static.yml
require_file scripts/test-fedora-local-rpm-static-validation.sh
require_file .github/workflows/fedora-local-rpm-static-validation.yml
require_file scripts/test-fedora-rpmlint-static-spec-lane.sh
require_file .github/workflows/fedora-rpmlint-static-spec-lane.yml

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
require_contains 'final_state=scheduler-credit-ready' docs/FEDORA_READINESS_PLAN.md
require_contains 'external_effect_performed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'runtime_entry_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'scheduler_execution_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'memory_allocation_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'process_spawn_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'syscall_dispatch_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'ipc_send_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'ipc_receive_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'ipc_queue_mutation_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'filesystem_lookup_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'filesystem_read_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'filesystem_write_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'namespace_mutation_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'device_open_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'device_read_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'device_write_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'driver_probe_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'driver_load_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'driver_bind_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'interrupt_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'interrupt_mask_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'interrupt_unmask_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'interrupt_dispatch_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'interrupt_ack_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'timer_tick_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'timer_arm_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'timer_disarm_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'scheduler_tick_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'run_queue_mutation_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'enqueue_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'dequeue_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'dispatch_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'context_switch_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'register_save_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'register_restore_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'stack_switch_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'address_space_switch_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'preemption_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'time_accounting_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'time_read_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'cpu_usage_write_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'quota_update_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'scheduler_credit_update_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'process_wake_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'dma_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'hardware_effect_allowed=0' docs/FEDORA_READINESS_PLAN.md
require_contains 'not bootable' docs/FEDORA_READINESS_PLAN.md
require_contains 'not a Fedora derivative' docs/FEDORA_READINESS_PLAN.md
require_contains 'Phase 1: Fedora build lane' docs/FEDORA_READINESS_PLAN.md
require_contains 'Phase 2: package metadata lane' docs/FEDORA_READINESS_PLAN.md
require_contains 'Phase 3: license and source audit lane' docs/FEDORA_READINESS_PLAN.md
require_contains 'Phase 4: local RPM and mock lane' docs/FEDORA_READINESS_PLAN.md
require_contains 'Phase 5: Fedora review candidate lane' docs/FEDORA_READINESS_PLAN.md
require_contains 'Current guarded files:' docs/FEDORA_READINESS_PLAN.md
require_contains '.github/workflows/fedora-build-lane.yml' docs/FEDORA_READINESS_PLAN.md
require_contains 'scripts/test-fedora-spec-static.sh' docs/FEDORA_READINESS_PLAN.md
require_contains '.github/workflows/fedora-spec-static.yml' docs/FEDORA_READINESS_PLAN.md
require_contains 'Keep the Fedora build/spec-static compatibility aliases aligned' docs/FEDORA_READINESS_PLAN.md
require_contains 'fedora_readiness_plan: ok' docs/FEDORA_READINESS_PLAN.md

printf 'fedora_readiness_plan: ok\n'
