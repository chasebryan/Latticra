# Latticra Console Read-Only Host Inventory Acceptance Checklist

Status: draft acceptance checklist
Created: 2026-05-26 17:32 CDT
Decision: checklist only
Promotion decision: no Console, host-inventory, host-adapter, product-readiness, runtime, security, or OS-base promotion recommended
Scope: acceptance criteria for future Console read-only host-inventory evaluator workflow evidence.

## Purpose

This checklist defines the conditions that must be satisfied before the Console read-only host-inventory evaluator workflow can be treated as reviewable.

It does not claim the evidence exists yet. It defines how future evidence should be reviewed.

## Source workflow

This checklist follows:

```text
docs/strategy/2026-05-26-1707-cdt-console-read-only-host-inventory-workflow-packet.md
```

The selected workflow is:

```text
contract_only_console_host_inventory_evaluator_workflow
```

The rejected workflow is:

```text
live_host_inventory_capture
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
local_operator_scope=1
nontechnical_user_scope=0
production_operator_scope=0
daily_driver_scope=0
security_reliance_scope=0
```

Required reviewer question:

```text
Can the intended evaluator understand that this is a contract-only Console
host-inventory review, not a live host scan or production product workflow?
```

## Required source entry

Acceptance requires visible entry into:

```text
current_project_status
current_estimate_posture
Console_foundation_record
Console_status_record
Console_host_inventory_contract
Console_host_adapter_contract
Console_receipt_request_contract
runtime_boundary_binding
Seal_capability_label_binding
```

Required evidence fields:

```text
status_surface_reference:
foundation_record_reference:
status_record_reference:
workflow_packet_reference:
reviewer_note:
```

## Required contract identity

Acceptance requires evidence that the host-inventory surface is contract-only:

```text
contract_profile=lc-host-inventory-v0
contract_status=metadata-only
required_before_host_embedding=1
host_adapter_present=0
inventory_schema_status=planned
inventory_performed=0
inventory_artifact_present=0
inventory_receipt_required=1
operator_consent_required=1
runtime_boundary_required=1
seal_capability_labels_required=1
promotion_gate=host_inventory_contract_receipt_before_host_adapter
```

Required reviewer question:

```text
Can the evaluator identify the difference between an inventory contract and an
inventory artifact?
```

## Required command-surface clarity

Acceptance requires the future evidence bundle to identify intended command surfaces without running them as part of this checklist:

```text
latticra_console_report host-inventory
latticra-lc host-inventory
latticra_console_report host-adapter
latticra-lc host-adapter
latticra_console_report receipt-request
latticra-lc receipt-request
```

Required evidence fields:

```text
command_surface_listed=1
commands_run_by_this_checklist=0
command_output_attached=0|1
command_output_source:
```

If command output is attached later, it must be produced by a separate explicit evidence-capture request.

## Required allowed-scope visibility

Acceptance requires the planned future inventory scope to be visible and narrow:

```text
allowed_future_scope=os_family,kernel_version,cpu_arch,memory_class,filesystem_roots,user_scope,prefix_scope
```

Required reviewer question:

```text
Can the evaluator tell that the planned inventory is limited to host posture
metadata rather than file contents, secrets, network state, or process behavior?
```

## Required excluded-scope visibility

Acceptance requires excluded scope to be visible:

```text
excluded_future_scope=secrets,private_files,network_scan,process_launch,kernel_change,system_mutation
```

Required denial labels:

```text
secrets_allowed=0
private_file_read_allowed=0
network_scan_allowed=0
process_launch_allowed=0
kernel_change_allowed=0
system_mutation_allowed=0
```

## Required no-effect authority floor

Acceptance requires all current authority-denial fields to remain visible:

```text
host_probe_allowed=0
host_process_launch_allowed=0
host_file_read_allowed=0
host_file_write_allowed=0
host_mutation_allowed=0
network_allowed=0
runtime_enforcement_allowed=0
boot_allowed=0
seal_capability_grants_authority=0
```

Failure to show any denial field should produce:

```text
blocked_missing_authority_floor
```

## Required receipt boundary

Acceptance requires the receipt path to stay metadata-only:

```text
receipt_request_contract_status=metadata-only-contract
receipt_request_contract_present=1
receipt_payload_schema_present=1
receipt_payload_artifact_draft_present=1
receipt_payload_artifact_review_present=1
receipt_payload_materialization_plan_present=1
draft_review_receipt_present=0
materialization_preconditions_met=0
materialization_allowed=0
payload_artifact_present=0
payload_materialized=0
seal_signature_request_ready=0
seal_signature_request_present=0
seal_signing_authority_present=0
receipt_written=0
receipt_signed=0
```

Required reviewer question:

```text
Can the evaluator see that receipt planning exists while signed receipt
authority and payload materialization remain unavailable?
```

## Required host-adapter gate

Acceptance requires host-adapter progression to remain blocked:

```text
host_adapter_contract_status=metadata-only-contract
host_adapter_contract_present=1
host_adapter_enabled=0
host_adapter_present=0
host_adapter_loaded=0
host_embedding_contract_required=1
read_only_host_inventory_contract_required=1
host_embedding_contract_receipt_required=1
host_inventory_contract_receipt_required=1
receipt_required_before_host_adapter=1
promotion_gate=host_adapter_contract_receipts_and_inventory
```

The checklist must reject any evidence that treats a host-inventory contract as permission to enable the host adapter.

## Required failure-state coverage

Acceptance requires declared handling for:

```text
source_record_missing
host_inventory_contract_missing
host_inventory_contract_ambiguous
denial_field_missing
excluded_scope_missing
receipt_boundary_missing
host_adapter_gate_missing
command_output_missing
command_output_implies_live_scan
public_text_overclaims_inventory
estimate_change_requested_without_evidence
manual_review_required
```

## Required non-claim visibility

Acceptance requires the evidence package to preserve these non-claims:

```text
live_host_inventory_claim=0
host_probe_claim=0
host_file_read_claim=0
host_file_write_claim=0
host_mutation_claim=0
network_scan_claim=0
host_adapter_claim=0
runtime_enforcement_claim=0
boot_claim=0
security_hardening_claim=0
product_readiness_claim=0
production_support_claim=0
```

## Acceptance decision

The checklist may return `evidence_ready_for_review` only if:

```text
source_entry_visible=1
contract_identity_visible=1
command_surface_clarity=1
allowed_scope_visible=1
excluded_scope_visible=1
authority_floor_visible=1
receipt_boundary_visible=1
host_adapter_gate_visible=1
failure_states_declared=1
non_claims_visible=1
commands_run_by_this_checklist=0
live_host_inventory_performed=0
estimate_change_recommended=0
product_readiness_promotion_recommended=0
```

The checklist must return `rejected` if:

```text
host_probe_performed=1
host_file_read_performed=1
host_file_write_performed=1
host_mutation_performed=1
network_scan_performed=1
host_adapter_enabled=1
receipt_signed=1
public_claim_overstates_inventory=1
```

## Recommended next planning move

Recommended next planning move:

```text
begin the Tier 2 Nucleus effect-contract and runtime-denial gate planning package
```

Reason:

```text
the acceptance criteria, evidence bundle shape, non-claim review shape, and
public-entrypoint review shape, estimate-impact review shape, and review
package index now define what must be reviewed and the completion checkpoint
closes the package; the next useful planning lane is the Tier 2 Nucleus
effect-boundary package
```

## Non-claims

This checklist does not run Console, run `latticra-lc`, run `latticra_console_report`, inspect a host, probe a host, read host files, write host files, scan a network, launch a host process, mutate a host, create an inventory artifact, create a receipt, request a signature, sign a receipt, enable a host adapter, enforce runtime policy, boot hardware, validate product readiness, update estimates, update public entry points, harden security, prevent malware, prevent ransomware, provide sandboxing, provide operating-system behavior, or provide production support.

It records acceptance criteria only.
