# Latticra Console Read-Only Host Inventory Evidence Bundle Template

Status: draft evidence-bundle template
Created: 2026-05-26 17:36 CDT
Decision: template only
Promotion decision: no Console, host-inventory, host-adapter, product-readiness, runtime, security, or OS-base promotion recommended
Scope: evidence bundle structure for future Console read-only host-inventory evaluator workflow review.

## Purpose

This template defines the evidence bundle that would be required before the Console read-only host-inventory evaluator workflow can be reviewed.

It does not claim any evidence has been captured. It defines the future bundle shape only.

## Source checklist

This template follows:

```text
docs/strategy/2026-05-26-1732-cdt-console-read-only-host-inventory-acceptance-checklist.md
```

The source workflow remains:

```text
contract_only_console_host_inventory_evaluator_workflow
```

The rejected workflow remains:

```text
live_host_inventory_capture
```

## Bundle header

```text
bundle name:
created:
review status: not_started|blocked|partial_evidence|evidence_ready_for_review|accepted_for_non_claim_review|accepted_for_public_entrypoint_review|accepted_for_estimate_review|rejected
target evaluator:
evaluated platform:
repository commit:
workflow packet:
acceptance checklist:
evidence bundle template:
review owner:
```

`accepted_for_estimate_review` must not be used until a reviewer confirms that all required evidence exists and the non-claim, public-entrypoint, and estimate-impact reviews are present.

## Evidence manifest

Required manifest fields:

```text
status_entry_record:
console_foundation_record:
console_status_record:
host_inventory_contract_record:
host_adapter_contract_record:
receipt_boundary_record:
command_surface_record:
allowed_scope_record:
excluded_scope_record:
authority_floor_record:
host_adapter_gate_record:
failure_state_record:
known_limitations_record:
support_boundary_record:
non_claim_review_record:
public_entrypoint_review_record:
estimate_impact_review_record:
```

Each record should be a path, transcript id, status document, or explicit `missing` label.

## Status and source-entry record

Required fields:

```text
status_surface_reference:
estimate_surface_reference:
Console_foundation_record_reference:
Console_status_record_reference:
workflow_packet_reference:
acceptance_checklist_reference:
contract_only_workflow_visible=0|1
live_inventory_rejected_visible=0|1
product_readiness_limitation_visible=0|1
security_hardening_limitation_visible=0|1
evaluator_review_note:
record_status: missing|partial|complete
```

## Contract identity record

Required fields:

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
contract_review_note:
record_status: missing|partial|complete
```

The record must distinguish the inventory contract from any future inventory artifact.

## Command surface record

Required fields:

```text
command_surface_listed=0|1
latticra_console_report_host_inventory_listed=0|1
latticra_lc_host_inventory_listed=0|1
latticra_console_report_host_adapter_listed=0|1
latticra_lc_host_adapter_listed=0|1
latticra_console_report_receipt_request_listed=0|1
latticra_lc_receipt_request_listed=0|1
commands_run_by_this_bundle=0
command_output_attached=0|1
command_output_source:
command_surface_review_note:
record_status: missing|partial|complete
```

If command output is attached later, it must come from a separate explicit evidence-capture request.

## Allowed-scope record

Required fields:

```text
allowed_future_scope_visible=0|1
os_family_scope_visible=0|1
kernel_version_scope_visible=0|1
cpu_arch_scope_visible=0|1
memory_class_scope_visible=0|1
filesystem_roots_scope_visible=0|1
user_scope_visible=0|1
prefix_scope_visible=0|1
host_posture_metadata_only=0|1
allowed_scope_review_note:
record_status: missing|partial|complete
```

## Excluded-scope record

Required fields:

```text
excluded_future_scope_visible=0|1
secrets_allowed=0
private_file_read_allowed=0
network_scan_allowed=0
process_launch_allowed=0
kernel_change_allowed=0
system_mutation_allowed=0
excluded_scope_review_note:
record_status: missing|partial|complete
```

## Authority-floor record

Required fields:

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
authority_floor_review_note:
record_status: missing|partial|complete
```

Any missing denial field should block the bundle with:

```text
blocked_missing_authority_floor
```

## Receipt boundary record

Required fields:

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
receipt_boundary_review_note:
record_status: missing|partial|complete
```

## Host-adapter gate record

Required fields:

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
host_adapter_gate_review_note:
record_status: missing|partial|complete
```

The bundle must reject evidence that treats the host-inventory contract as permission to enable the host adapter.

## Failure-state record

Required failure labels:

```text
source_record_missing:
host_inventory_contract_missing:
host_inventory_contract_ambiguous:
denial_field_missing:
excluded_scope_missing:
receipt_boundary_missing:
host_adapter_gate_missing:
command_output_missing:
command_output_implies_live_scan:
public_text_overclaims_inventory:
estimate_change_requested_without_evidence:
manual_review_required:
```

For every failure label, record:

```text
host_probe_performed=0
host_file_read_performed=0
host_file_write_performed=0
host_mutation_performed=0
network_scan_performed=0
host_adapter_enabled=0
receipt_signed=0
remediation_or_manual_review_note:
```

## Known limitations record

Required visible limitations:

```text
not_live_host_inventory=1
not_host_probe=1
not_file_reader=1
not_network_scanner=1
not_host_adapter=1
not_runtime_enforcement=1
not_boot_behavior=1
not_a_production_product=1
not_a_security_boundary=1
not_security_hardening=1
not_malware_prevention=1
not_ransomware_prevention=1
record_status: missing|partial|complete
```

## Support boundary record

Required fields:

```text
supported_evaluator:
supported_platforms_for_this_evidence:
unsupported_platforms:
known_setup_limits:
known_runtime_limits:
documentation_issue_path:
security_issue_path:
record_status: missing|partial|complete
```

## Review gate records

Non-claim review:

```text
non_claim_review_present=0|1
non_claim_review_path:
claim_expansion_detected=0|1
```

Public-entrypoint review:

```text
public_entrypoint_review_present=0|1
README_update_required=0|1
STATUS_update_required=0|1
CURRENT_STATUS_update_required=0|1
project_notes_update_required=0|1
announcement_review_required=0|1
```

Estimate-impact review:

```text
estimate_impact_review_present=0|1
estimate_change_recommended=0|1
reason:
```

## Bundle completeness rule

The bundle is complete only if:

```text
all_required_records_present=1
all_required_records_complete=1
non_claim_review_present=1
public_entrypoint_review_present=1
estimate_impact_review_present=1
claim_expansion_detected=0
commands_run_by_this_bundle=0
live_host_inventory_performed=0
host_probe_performed=0
host_file_read_performed=0
host_file_write_performed=0
host_mutation_performed=0
network_scan_performed=0
host_adapter_enabled=0
receipt_signed=0
```

This template result:

```text
bundle_complete=0
estimate_change_recommended=0
public_entrypoint_change_recommended=0
reason=this file defines the future bundle shape only
```

## Recommended next planning move

Recommended next planning move:

```text
begin the Tier 2 Nucleus effect-contract and runtime-denial gate planning package
```

Reason:

```text
the evidence bundle, non-claim review, and public-entrypoint review shapes are
now joined by the estimate-impact review shape and review package index; the
completion checkpoint closes this package, and the next useful planning lane is
the Tier 2 Nucleus effect-boundary package
```

## Non-claims

This template does not provide workflow evidence, run Console, run `latticra-lc`, run `latticra_console_report`, inspect a host, probe a host, read host files, write host files, scan a network, launch a host process, mutate a host, create an inventory artifact, create a receipt, request a signature, sign a receipt, enable a host adapter, enforce runtime policy, boot hardware, validate product readiness, update estimates, update public entry points, harden security, prevent malware, prevent ransomware, provide sandboxing, provide operating-system behavior, or provide production support.

It records an evidence-bundle structure only.
