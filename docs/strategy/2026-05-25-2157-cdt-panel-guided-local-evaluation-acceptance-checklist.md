# Latticra Panel-Guided Local Evaluation Acceptance Checklist

Status: draft acceptance checklist
Created: 2026-05-25 21:57 CDT
Decision: checklist only
Promotion decision: no product-readiness promotion recommended
Scope: acceptance criteria for future Panel-guided local evaluation evidence.

## Purpose

This checklist defines the evidence needed before the Panel-guided local evaluation workflow can be treated as a bounded public-readiness workflow.

It does not claim the evidence exists yet. It defines how future evidence should be reviewed.

## Source workflow

This checklist follows:

```text
docs/strategy/2026-05-25-2137-cdt-panel-guided-local-evaluation-workflow-packet.md
```

The source workflow is:

```text
Evaluate Latticra locally through Latticra Panel without granting runtime authority.
```

## Review result labels

Use one result label when applying this checklist:

```text
not_started
blocked
partial_evidence
evidence_ready_for_review
accepted_for_estimate_review
rejected
```

This checklist alone cannot produce `accepted_for_estimate_review`; that result requires actual transcript, guard, or workflow evidence.

## Required evaluator boundary

Acceptance requires:

```text
target_evaluator_named=1
technical_evaluator_scope=1
nontechnical_user_scope=0
production_operator_scope=0
daily_driver_scope=0
security_reliance_scope=0
```

Required reviewer question:

```text
Can the intended evaluator understand that this is a local evaluation workflow, not a production product?
```

## Required status and non-claim entry

Acceptance requires visible entry into:

```text
current project status
current estimate posture
public non-claims
runtime authority denial
effect execution denial
product-readiness limitation
security-hardening limitation
```

Required evidence:

```text
status_surface_reference:
non_claim_surface_reference:
evaluator_acknowledgement_or_review_note:
```

## Required prerequisite check

Acceptance requires a platform prerequisite check for the evaluated platform.

Minimum prerequisite labels:

```text
platform_identified
rust_toolchain_status
cargo_status
make_status
gui_dependency_status
local_path_status
network_required=0
root_required=0
```

Failure states must include:

```text
unsupported_platform
missing_rust_toolchain
missing_gui_dependency
manual_review_required
```

## Required launch evidence

Acceptance requires evidence that the evaluator can reach the Panel entry point or a documented fallback.

Required evidence:

```text
launch_command:
launch_result:
fallback_command:
panel_available=0|1
fallback_available=0|1
```

The launch path must not grant:

```text
runtime authority
network authority
root authority
effect authority
```

## Required dry-run-first evidence

Acceptance requires the workflow to prove dry-run-first posture.

Required labels:

```text
dry_run_enabled=1
dry_run_required_before_guarded_writes=1
runtime_authority_granted=0
effect_execution_performed=0
network_authority_granted=0
root_authority_required=0
production_ready=0
manual_review_required=1
```

Required reviewer question:

```text
Can the evaluator tell, before proceeding, whether any local write is planned?
```

## Required plan evidence

Acceptance requires a plan output or plan-equivalent evidence record.

Required evidence:

```text
plan_generated=1
plan_reviewable=1
planned_artifact_paths_visible=1
planned_local_writes_visible=1
planned_runtime_effects_visible=1
planned_network_effects_visible=1
denied_authority_visible=1
```

The plan must distinguish:

```text
dry-run artifacts
user-local artifacts
runtime effects
host effects
external effects
```

## Required dry-run validation evidence

Acceptance requires a dry-run validation transcript or equivalent record.

Required evidence:

```text
dry_run_started=1
dry_run_completed=0|1
dry_run_failed=0|1
failure_reason_visible=1
hidden_mutation_detected=0
effect_execution_performed=0
network_behavior_performed=0
runtime_authority_granted=0
```

If the dry-run fails, acceptance requires a visible failure label and remediation or manual-review note.

## Required receipt and log evidence

Acceptance requires receipt and log visibility when the workflow says they should exist.

Required evidence:

```text
receipt_expected=0|1
receipt_available=0|1
receipt_path_visible=0|1
engine_log_expected=0|1
engine_log_available=0|1
engine_log_path_visible=0|1
embedded_console_status_available=0|1
```

Failure states must include:

```text
receipt_missing
log_missing
manual_review_required
```

## Required reset or uninstall evidence

Acceptance requires a reset, cleanup, or uninstall path appropriate to the workflow evidence.

Required evidence:

```text
reset_available=1
uninstall_or_cleanup_available=1
reset_dry_run_available=1
cleanup_scope_visible=1
local_artifact_scope_visible=1
reset_failed_label_available=1
```

If no local artifacts are created, the workflow must state:

```text
local_artifacts_created=0
cleanup_required=0
```

## Required failure-state coverage

Acceptance requires examples or declared handling for:

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

Every failure state must preserve:

```text
no runtime authority
no network authority
no hidden mutation
visible remediation or manual-review note
```

## Required known limitations

Acceptance requires visible limitations:

```text
not a production installer
not a daily-driver product
not a security boundary
not malware prevention
not ransomware prevention
not a Fedora-approved package
not an Ubuntu package-readiness claim
not a macOS app-readiness claim
not an operating-system replacement
```

## Required support boundary

Acceptance requires a support boundary:

```text
supported_evaluator:
supported_platforms_for_this_evidence:
unsupported_platforms:
known_setup_limits:
known_runtime_limits:
where_to_report_documentation_issues:
where_to_report_security_issues:
```

## Required evidence bundle

Before estimate review, collect:

```text
workflow acceptance checklist result
platform prerequisite record
dry-run transcript
plan output example
receipt or receipt-like evidence
engine log example
embedded console status example
reset or uninstall transcript
failure-state examples
known limitations note
support boundary note
non-claim review
guard or test reference
```

## Estimate-impact gate

Estimate review may be considered only if:

```text
workflow_completed_by_target_evaluator=1
evidence_bundle_complete=1
guard_or_test_reference_present=1
non_claim_review_present=1
public_entrypoint_review_present=1
```

Checklist result:

```text
estimate_change_recommended=no
reason=this checklist defines acceptance criteria only
```

## Public-entrypoint gate

Public entrypoint review may be considered only if actual workflow evidence exists.

Checklist result:

```text
README_update_required=no
STATUS_update_required=no
CURRENT_STATUS_update_required=no
project_notes_update_required=no
announcement_review_required=no
reason=no capability posture changes in this checklist
```

## Non-claims

This checklist does not implement product readiness, Panel readiness, installer readiness, runtime behavior, effect execution, capability enforcement, cryptographic authority, signing authority, host behavior, network behavior, model execution, tool execution, shell execution, security hardening, malware prevention, ransomware prevention, sandboxing, operating-system behavior, or production support.

It records acceptance criteria only.
