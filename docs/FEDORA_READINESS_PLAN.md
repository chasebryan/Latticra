# Fedora Readiness Plan

Status: planning and compatibility record
Scope: preparing Latticra for Fedora-friendly packaging, testing, and community review.

## Purpose

This plan prepares Latticra for a future Fedora-facing path without claiming Fedora acceptance, endorsement, official inclusion, or distribution status.

The near-term target is:

```text
Latticra builds cleanly on Fedora Linux.
Latticra can be described honestly as an upstream project preparing for Fedora package review.
Latticra avoids Fedora trademark confusion.
Latticra preserves its current non-claims.
```

## Terminology boundary

Use:

```text
Fedora readiness
Fedora packaging readiness
Fedora compatibility lane
Latticra on Fedora
future package review candidate
```

Avoid claiming:

```text
official Fedora package
Fedora spin
Fedora remix
Fedora edition
Fedora merger
Fedora endorsement
operating-system replacement
```

Those terms require separate Fedora community, packaging, legal, and trademark review.

## Fedora-facing requirements to respect

Before Latticra can be proposed as a package candidate, it should be checked against Fedora package review expectations:

```text
package naming
spec file hygiene
Fedora allowed license posture
accurate License field
license text handling
source archive reproducibility
successful build on supported architectures where claimed
BuildRequires completeness
no bundled system libraries
valid file ownership
valid permissions
rpmlint or equivalent package lint output
mock build readiness
```

## Current Latticra posture

Current Latticra evidence is still early-stage and report-oriented.

Known current posture:

```text
kernel lifecycle evidence exists
final_state=scheduler-run-entry-ready
external_effect_performed=0
runtime_entry_allowed=0
scheduler_execution_allowed=0
scheduler_selection_allowed=0
scheduler_dispatch_allowed=0
scheduler_handoff_allowed=0
scheduler_activation_allowed=0
scheduler_run_entry_allowed=0
memory_allocation_allowed=0
process_spawn_allowed=0
syscall_dispatch_allowed=0
ipc_send_allowed=0
ipc_receive_allowed=0
ipc_queue_mutation_allowed=0
filesystem_lookup_allowed=0
filesystem_read_allowed=0
filesystem_write_allowed=0
namespace_mutation_allowed=0
device_open_allowed=0
device_read_allowed=0
device_write_allowed=0
driver_probe_allowed=0
driver_load_allowed=0
driver_bind_allowed=0
interrupt_allowed=0
interrupt_mask_allowed=0
interrupt_unmask_allowed=0
interrupt_dispatch_allowed=0
interrupt_ack_allowed=0
timer_tick_allowed=0
timer_arm_allowed=0
timer_disarm_allowed=0
scheduler_tick_allowed=0
run_queue_mutation_allowed=0
enqueue_allowed=0
dequeue_allowed=0
dispatch_allowed=0
context_switch_allowed=0
register_save_allowed=0
register_restore_allowed=0
stack_switch_allowed=0
address_space_switch_allowed=0
preemption_allowed=0
time_accounting_allowed=0
time_read_allowed=0
cpu_usage_write_allowed=0
quota_update_allowed=0
scheduler_credit_update_allowed=0
process_wake_allowed=0
dma_allowed=0
hardware_effect_allowed=0
not bootable
not installer-ready
not a Fedora derivative
not a production operating system
```

This makes the first Fedora-facing target a development package or source package candidate, not a distribution, image, spin, remix, or replacement operating system.

## Phase 1: Fedora build lane

The Fedora build/test lane proves the current guarded project foundation compiles with Fedora toolchains.

Current guarded files:

```text
scripts/test-fedora-build-lane.sh
.github/workflows/fedora-build-lane.yml
.github/workflows/compat-linux.yml
```

Initial checks should be conservative:

```text
C compiler available
project C guards compile
kernel lifecycle guards compile
no external authority claims added
```

## Phase 2: package metadata lane

Packaging metadata is present as a local-only draft after the Fedora build lane.

Current guarded files:

```text
packaging/fedora/latticra.spec
packaging/fedora/README.md
scripts/test-fedora-spec-static.sh
.github/workflows/fedora-spec-static.yml
scripts/test-fedora-local-rpm-static-validation.sh
.github/workflows/fedora-local-rpm-static-validation.yml
scripts/test-fedora-rpmlint-static-spec-lane.sh
.github/workflows/fedora-rpmlint-static-spec-lane.yml
```

The first spec should be treated as a local development draft until it passes review.

## Phase 3: license and source audit lane

Before any package submission, verify:

```text
root license state
file-level SPDX state
license text included as needed
third-party material inventory
documentation license decision
trademark and branding boundary
```

This should align with the existing Latticra license migration plan.

## Phase 4: local RPM and mock lane

After package metadata exists, add local package validation:

```text
rpmbuild source package
rpmlint output captured
mock build validated
installed files inspected
uninstall behavior checked
```

This lane should remain local or Copr-oriented until the project is mature enough for review.

## Phase 5: Fedora review candidate lane

Only after the earlier lanes pass should Latticra be described as a Fedora review candidate.

A future review-prep document should include:

```text
upstream URL
source archive URL
package summary
package description
license expression
BuildRequires list
runtime Requires list
rpmlint output
mock build output
known non-claims
```

## Trademark and naming posture

The project should not use Fedora marks in a way that suggests official status.

Preferred naming:

```text
Latticra Fedora readiness
Latticra package draft for Fedora
Latticra on Fedora Linux
```

Avoid naming:

```text
Fedora Latticra
Latticra Fedora Edition
Fedora Latticra OS
Official Fedora Latticra
```

## Non-claims

This plan does not:

```text
submit Latticra to Fedora
create a Fedora package
create a Fedora spin
create a Fedora remix
claim Fedora endorsement
claim Fedora legal approval
claim production readiness
claim operating-system completeness
```

## Recommended next slice

Recommended next slice:

```text
Keep the Fedora build/spec-static compatibility aliases aligned with the local RPM static validation and rpmlint lanes
```

That should preserve the current no-artifact, no-submission, local-only package posture while the later local RPM and mock lanes mature.

## Validation

This planning slice is guarded by:

```sh
sh scripts/test-fedora-readiness-plan.sh
```

Expected output:

```text
fedora_readiness_plan: ok
```
