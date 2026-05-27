# Latticra Nucleus Effect-Contract and Runtime-Denial Acceptance Checklist

Status: draft acceptance checklist
Created: 2026-05-27 02:09 CDT
Decision: checklist only
Promotion decision: no Nucleus execution, runtime, task-execution, product-readiness, security, OS-base, recovery, hardware, boot, or mutation promotion recommended
Scope: acceptance criteria for future Nucleus effect-contract and runtime-denial workflow evidence.

## Purpose

This checklist defines the conditions that must be satisfied before the Nucleus effect-contract and runtime-denial workflow can be treated as reviewable.

It does not claim the evidence exists yet. It defines how future evidence should be reviewed.

## Source workflow

This checklist follows:

```text
docs/strategy/2026-05-26-2134-cdt-nucleus-effect-contract-runtime-denial-workflow-packet.md
```

The selected workflow is:

```text
contract_only_nucleus_effect_request_runtime_denial_workflow
```

Rejected workflows remain:

```text
live_task_execution_prototype
runtime_effect_execution_capture
command_runner_evidence_capture
mutation_capability_probe
operator_confirmation_override_trial
```

## Review result labels

Use one result label when applying this checklist:

```text
not_started
blocked
partial_evidence
evidence_ready_for_review
accepted_for_non_claim_review
accepted_for_public_entrypoint_review
accepted_for_estimate_review
rejected
```

This checklist alone cannot produce `accepted_for_estimate_review`; that result requires actual workflow evidence plus non-claim, public-entrypoint, and estimate-impact review.

## Required evaluator boundary

Acceptance requires:

```text
target_evaluator_named=1
technical_evaluator_scope=1
runtime_developer_scope=1
nontechnical_user_scope=0
production_operator_scope=0
daily_driver_scope=0
security_reliance_scope=0
effect_execution_scope=0
```

Required reviewer question:

```text
Can the intended evaluator understand that this is a contract-only Nucleus
effect-request and runtime-denial review, not task execution or runtime entry?
```

## Required source entry

Acceptance requires visible entry into:

```text
current_project_status
current_estimate_posture
Nucleus_task_execution_contract
Nucleus_task_execution_implementation
Nucleus_no_effect_report_alignment
Nucleus_report_only_execution_refinement
Nucleus_task_plan_implementation
runtime_denial_surface
no_effect_policy_surface
```

Required evidence fields:

```text
status_surface_reference:
task_contract_reference:
implementation_reference:
no_effect_alignment_reference:
report_only_refinement_reference:
task_plan_reference:
workflow_packet_reference:
reviewer_note:
```

## Required current posture

Acceptance requires evidence that current posture remains:

```text
nucleus_real_task_execution_estimate=12_percent
runtime_operating_system_universe_direction_estimate=25_percent
task_classification_surface_present=1
task_report_surface_present=1
task_plan_surface_present=1
report_only_execution_metadata_present=1
execution_status=not-executed
effect_status=report-only
runtime_status=not-entered
report_alignment=no-effect-report-alignment
no_effect_policy=preserved
representation_gate=language-representation-reviewed
```

Required reviewer question:

```text
Can the evaluator identify the difference between classifying an effect request
and executing an effect?
```

## Required request classification

Acceptance requires visible request classification for:

```text
state_report
transition_preview
render_report
lat_validate
lir_validate
authority_check
server_interaction
self_update
recovery_action
hardware_action
boot_action
unknown_request
```

Acceptance requires allowed no-effect requests to stay inside:

```text
state_report_none_or_read=allow-report
transition_preview_none_or_read=allow-preview
render_report_none_or_read=allow-report
lat_validate_none_or_read=allow-validation
lir_validate_none_or_read=allow-validation
authority_check_none_or_read=allow-validation
```

## Required denial and future-gate classification

Acceptance requires future-gated and denied classes to remain visible:

```text
server_interaction=requires-future-gate
self_update=requires-future-gate
recovery_action=requires-future-gate
hardware_action=requires-future-gate
boot_action=requires-future-gate
unknown_request=deny
unknown_effect=deny
local_mutation=deny
host_mutation=deny
network=deny
hardware=deny
boot=deny
recovery=deny
external=deny
```

Failure to show any denial or future-gate label should produce:

```text
blocked_missing_denial_gate
```

## Required authority floor

Acceptance requires all current authority-denial fields to remain visible:

```text
effect_authority_granted=0
task_execution_performed=0
runtime_entered=0
command_execution_allowed=0
lat_execution_allowed=0
lir_execution_allowed=0
file_io_allowed=0
network_allowed=0
state_mutation_allowed=0
server_interaction_allowed=0
self_update_allowed=0
recovery_allowed=0
hardware_allowed=0
boot_allowed=0
operator_confirmation_overrides_policy=0
```

Failure to show any authority-denial field should produce:

```text
blocked_missing_authority_floor
```

## Required report-only metadata

Acceptance requires report-only metadata to remain explicit:

```text
execution_status=not-executed
effect_status=report-only
runtime_status=not-entered
task_execution_performed=0
runtime_entered=0
no_effect_policy=preserved
```

Required reviewer question:

```text
Can the evaluator tell that task reports and task plans describe classified
requests without executing those requests?
```

## Required plan sequencing boundary

Acceptance requires Nucleus task plans to remain sequencing metadata only:

```text
task_plan_surface_present=1
task_plan_executes_tasks=0
task_plan_enters_runtime=0
task_plan_performs_mutation=0
task_plan_launches_commands=0
task_plan_reads_files=0
task_plan_writes_files=0
task_plan_uses_network=0
task_plan_controls_hardware=0
task_plan_boots_hardware=0
```

The checklist must reject evidence that treats a plan as permission to execute.

## Required operator-confirmation boundary

Acceptance requires operator confirmation to remain non-authorizing:

```text
operator_confirmation_present=0|1
operator_confirmation_overrides_policy=0
operator_confirmation_grants_runtime=0
operator_confirmation_grants_mutation=0
operator_confirmation_grants_network=0
operator_confirmation_grants_hardware=0
operator_confirmation_grants_boot=0
```

Any evidence that lets operator confirmation override policy must be rejected.

## Required failure-state coverage

Acceptance requires declared handling for:

```text
source_record_missing
task_contract_missing
classification_surface_missing
no_effect_alignment_missing
report_only_metadata_missing
denial_gate_missing
authority_floor_missing
task_plan_boundary_missing
operator_confirmation_boundary_missing
test_reference_missing
command_output_missing
command_output_implies_execution
public_text_overclaims_runtime
estimate_change_requested_without_evidence
manual_review_required
```

## Required non-claim visibility

Acceptance requires the evidence package to preserve these non-claims:

```text
task_execution_claim=0
effect_execution_claim=0
runtime_entry_claim=0
command_execution_claim=0
lat_execution_claim=0
lir_execution_claim=0
file_io_claim=0
network_claim=0
state_mutation_claim=0
server_interaction_claim=0
self_update_claim=0
recovery_claim=0
hardware_claim=0
boot_claim=0
operator_confirmation_override_claim=0
runtime_authority_claim=0
security_hardening_claim=0
product_readiness_claim=0
production_support_claim=0
```

## Acceptance decision

The checklist may return `evidence_ready_for_review` only if:

```text
source_entry_visible=1
current_posture_visible=1
request_classification_visible=1
denial_and_future_gate_classification_visible=1
authority_floor_visible=1
report_only_metadata_visible=1
plan_sequencing_boundary_visible=1
operator_confirmation_boundary_visible=1
failure_states_declared=1
non_claims_visible=1
commands_run_by_this_checklist=0
task_execution_performed=0
runtime_entered=0
effect_authority_granted=0
estimate_change_recommended=0
product_readiness_promotion_recommended=0
```

The checklist must return `rejected` if:

```text
task_execution_performed=1
runtime_entered=1
effect_authority_granted=1
command_execution_performed=1
file_io_performed=1
network_behavior_performed=1
state_mutation_performed=1
server_interaction_performed=1
self_update_performed=1
recovery_action_performed=1
hardware_action_performed=1
boot_action_performed=1
operator_confirmation_overrides_policy=1
public_claim_overstates_runtime=1
```

## Recommended next planning move

Recommended next planning move:

```text
create the Nucleus effect-contract and runtime-denial evidence bundle template
```

Reason:

```text
the acceptance criteria now define what must be reviewed; the next useful
planning artifact is a reusable bundle shape for future evidence
```

## Non-claims

This checklist does not capture evidence, run tests, run commands, execute Nucleus tasks, enter runtime, execute Lat, execute LIR, read files, write files, scan a network, launch a host process, perform state mutation, perform server interaction, self-update, perform recovery behavior, control hardware, boot hardware, create a receipt, request a signature, sign a receipt, perform a review, update public entry points, change estimates, provide product readiness, provide Nucleus execution readiness, provide runtime authority, enforce capabilities, provide cryptographic authority, provide signing authority, harden security, prevent malware, prevent ransomware, provide sandboxing, provide operating-system behavior, or provide production support.

It records acceptance criteria only.
