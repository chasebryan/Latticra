# Latticra Panel-Guided Local Evaluation Evidence Capture Plan

Status: draft evidence-capture plan
Created: 2026-05-25 22:46 CDT
Decision: capture plan only
Promotion decision: no product-readiness promotion recommended
Scope: future evidence-capture sequence for Panel-guided local evaluation.

## Purpose

This plan defines how future evidence should be captured for the Panel-guided local evaluation evidence bundle.

It does not capture evidence, run commands, implement guards, or change public product-readiness posture.

## Source bundle

This plan follows:

```text
docs/strategy/2026-05-25-2226-cdt-panel-guided-local-evaluation-evidence-bundle-template.md
```

The target workflow remains:

```text
Evaluate Latticra locally through Latticra Panel without granting runtime authority.
```

## Capture posture

The capture sequence must remain:

```text
local
dry-run-first
operator-visible
no-root by default
no-network by default
no runtime authority
no effect execution
no product-readiness claim
```

If any step requires root, network access, runtime authority, hidden mutation, or unreviewed local writes, the capture must stop and be marked `blocked`.

## Capture roles

Required roles:

```text
capture operator:
review owner:
non-claim reviewer:
public-entrypoint reviewer:
estimate-impact reviewer:
```

The same person may hold more than one role, but the evidence bundle must name which role performed each review.

## Capture phases

Use this phase order:

```text
phase_0_scope_lock
phase_1_status_and_non_claim_entry
phase_2_platform_prerequisite_capture
phase_3_panel_launch_capture
phase_4_dry_run_first_capture
phase_5_plan_capture
phase_6_dry_run_validation_capture
phase_7_receipt_log_console_capture
phase_8_reset_or_uninstall_capture
phase_9_failure_state_capture
phase_10_limitations_and_support_capture
phase_11_review_gate_capture
phase_12_bundle_completeness_review
```

Do not skip phases. A skipped phase must be recorded as `missing` or `blocked`.

## Phase 0: Scope Lock

Capture before running any workflow step:

```text
repository commit:
target evaluator:
evaluated platform:
workflow packet path:
acceptance checklist path:
evidence bundle template path:
capture plan path:
```

Required scope assertions:

```text
product_readiness_promotion_requested=0
estimate_change_requested=0
runtime_authority_requested=0
network_authority_requested=0
root_authority_requested=0
effect_execution_requested=0
```

Stop if any assertion cannot be preserved.

## Phase 1: Status And Non-Claim Entry

Capture:

```text
status_surface_reference
estimate_surface_reference
non_claim_surface_reference
runtime_authority_denial_visible
effect_execution_denial_visible
product_readiness_limitation_visible
security_hardening_limitation_visible
```

Stop if the evaluator cannot find current status or non-claims before launch.

## Phase 2: Platform Prerequisite Capture

Capture:

```text
platform identity
Rust toolchain status
Cargo status
Make status
GUI dependency status
local path status
network requirement status
root requirement status
```

Allowed result labels:

```text
complete
partial
blocked
unsupported_platform
missing_dependency
```

Stop if prerequisites imply network or root authority that was not already documented as optional and outside the no-effect workflow.

## Phase 3: Panel Launch Capture

Capture:

```text
launch command
launch result
fallback command
panel availability
fallback availability
authority labels after launch
```

Required authority labels:

```text
runtime_authority_granted=0
network_authority_granted=0
root_authority_granted=0
effect_authority_granted=0
```

Stop if launch behavior grants authority or performs hidden mutation.

## Phase 4: Dry-Run-First Capture

Capture:

```text
dry_run_enabled
dry_run_required_before_guarded_writes
local_write_planned
local_write_performed
manual_review_required
production_ready
```

Required labels:

```text
dry_run_enabled=1
runtime_authority_granted=0
effect_execution_performed=0
network_authority_granted=0
root_authority_required=0
production_ready=0
manual_review_required=1
```

Stop if dry-run posture is ambiguous.

## Phase 5: Plan Capture

Capture plan output or plan-equivalent evidence.

The plan must expose:

```text
planned artifact paths
planned local writes
planned runtime effects
planned network effects
denied authority
dry-run artifacts
user-local artifacts
runtime effects
host effects
external effects
```

Stop if the evaluator cannot distinguish dry-run artifacts from local writes, runtime effects, host effects, or external effects.

## Phase 6: Dry-Run Validation Capture

Capture:

```text
dry_run_started
dry_run_completed
dry_run_failed
failure_reason_visible
hidden_mutation_detected
effect_execution_performed
network_behavior_performed
runtime_authority_granted
remediation_or_manual_review_note
```

Required preservation labels:

```text
hidden_mutation_detected=0
effect_execution_performed=0
network_behavior_performed=0
runtime_authority_granted=0
```

Stop if any preservation label changes.

## Phase 7: Receipt, Log, And Console Capture

Capture:

```text
receipt expectation
receipt availability
receipt path visibility
engine log expectation
engine log availability
engine log path visibility
embedded console status availability
embedded console status summary
```

If any expected record is missing, mark the bundle `partial_evidence` or `blocked`, not complete.

## Phase 8: Reset Or Uninstall Capture

Capture:

```text
reset availability
uninstall or cleanup availability
reset dry-run availability
cleanup scope visibility
local artifact scope visibility
local artifacts created
cleanup required
reset failure label availability
```

Stop if local artifacts are created but no cleanup or reset boundary is visible.

## Phase 9: Failure-State Capture

Capture declared handling for:

```text
unsupported_platform
missing_rust_toolchain
missing_gui_dependency
panel_launch_failed
plan_generation_failed
dry_run_failed
receipt_missing
log_missing
reset_failed
operator_cancelled
manual_review_blocked
```

Each failure state must preserve:

```text
runtime_authority_granted=0
network_authority_granted=0
hidden_mutation_detected=0
remediation_or_manual_review_note_present=1
```

## Phase 10: Limitations And Support Capture

Capture visible limitations:

```text
not a production installer
not a daily-driver product
not a security boundary
not malware prevention
not ransomware prevention
not Fedora approved
not Ubuntu package readiness
not macOS app readiness
not an operating-system replacement
```

Capture support boundary:

```text
supported evaluator
supported platforms for this evidence
unsupported platforms
known setup limits
known runtime limits
documentation issue path
security issue path
```

Stop if limitations are hidden, softened into product claims, or contradicted by the workflow.

## Phase 11: Review Gate Capture

Required reviews:

```text
non-claim review
guard or test reference
public-entrypoint review
estimate-impact review
```

Review constraints:

```text
non_claim_review_present=1
guard_or_test_reference_present=1
public_entrypoint_review_present=1
estimate_impact_review_present=1
claim_expansion_detected=0
```

Do not recommend estimate or public-entrypoint changes from capture evidence alone. Those reviews must explain the decision separately.

## Phase 12: Bundle Completeness Review

The bundle may be marked `evidence_ready_for_review` only when:

```text
all_required_records_present=1
all_required_records_complete=1
all_stop_conditions_cleared=1
non_claim_review_present=1
guard_or_test_reference_present=1
public_entrypoint_review_present=1
estimate_impact_review_present=1
claim_expansion_detected=0
```

This plan result:

```text
evidence_captured=0
bundle_complete=0
estimate_change_recommended=0
public_entrypoint_change_recommended=0
reason=this file defines future capture sequence only
```

## Non-claims

This plan does not capture evidence, implement a guard, validate the Panel workflow, provide product readiness, provide Panel readiness, provide installer readiness, grant runtime authority, execute effects, enforce capabilities, provide cryptographic authority, provide signing authority, perform host behavior, perform network behavior, execute models, execute tools, execute shell behavior, harden security, prevent malware, prevent ransomware, provide sandboxing, provide operating-system behavior, or provide production support.

It records an evidence-capture sequence only.
