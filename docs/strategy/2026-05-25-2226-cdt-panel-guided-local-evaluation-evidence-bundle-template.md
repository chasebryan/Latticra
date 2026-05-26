# Latticra Panel-Guided Local Evaluation Evidence Bundle Template

Status: draft evidence-bundle template
Created: 2026-05-25 22:26 CDT
Decision: template only
Promotion decision: no product-readiness promotion recommended
Scope: evidence bundle structure for future Panel-guided local evaluation review.

## Purpose

This template defines the evidence bundle that would be required before Panel-guided local evaluation can be reviewed as a bounded public-readiness workflow.

It does not claim any evidence has been captured. It defines the future bundle shape only.

## Source checklist

This template follows:

```text
docs/strategy/2026-05-25-2157-cdt-panel-guided-local-evaluation-acceptance-checklist.md
```

The source workflow remains:

```text
Evaluate Latticra locally through Latticra Panel without granting runtime authority.
```

## Bundle header

```text
bundle name:
created:
review status: not_started|blocked|partial_evidence|evidence_ready_for_review|rejected
target evaluator:
evaluated platform:
repository commit:
workflow packet:
acceptance checklist:
review owner:
```

`accepted_for_estimate_review` must not be used until a reviewer confirms that all required evidence exists and the non-claim, public-entrypoint, and estimate-impact reviews are present.

## Evidence manifest

Required manifest fields:

```text
status_entry_record:
non_claim_entry_record:
platform_prerequisite_record:
launch_record:
dry_run_first_record:
plan_output_record:
dry_run_validation_record:
receipt_record:
engine_log_record:
embedded_console_record:
reset_or_uninstall_record:
failure_state_record:
known_limitations_record:
support_boundary_record:
non_claim_review_record:
guard_or_test_record:
public_entrypoint_review_record:
estimate_impact_review_record:
```

Each record should be a path, transcript id, status document, or explicit `missing` label.

## Status and non-claim entry record

Required fields:

```text
status_surface_reference:
estimate_surface_reference:
non_claim_surface_reference:
runtime_authority_denial_visible=0|1
effect_execution_denial_visible=0|1
product_readiness_limitation_visible=0|1
security_hardening_limitation_visible=0|1
evaluator_review_note:
record_status: missing|partial|complete
```

## Platform prerequisite record

Required fields:

```text
platform_identified:
platform_version:
rust_toolchain_status:
cargo_status:
make_status:
gui_dependency_status:
local_path_status:
network_required=0
root_required=0
unsupported_platform=0|1
missing_dependency_labels:
manual_review_required=0|1
record_status: missing|partial|complete
```

## Launch record

Required fields:

```text
launch_command:
launch_result:
fallback_command:
panel_available=0|1
fallback_available=0|1
runtime_authority_granted=0
network_authority_granted=0
root_authority_granted=0
effect_authority_granted=0
record_status: missing|partial|complete
```

## Dry-run-first record

Required fields:

```text
dry_run_enabled=1
dry_run_required_before_guarded_writes=1
local_write_planned=0|1
local_write_performed=0|1
runtime_authority_granted=0
effect_execution_performed=0
network_authority_granted=0
root_authority_required=0
production_ready=0
manual_review_required=1
record_status: missing|partial|complete
```

## Plan output record

Required fields:

```text
plan_generated=0|1
plan_reviewable=0|1
planned_artifact_paths_visible=0|1
planned_local_writes_visible=0|1
planned_runtime_effects_visible=0|1
planned_network_effects_visible=0|1
denied_authority_visible=0|1
dry_run_artifacts_identified=0|1
user_local_artifacts_identified=0|1
runtime_effects_identified=0|1
host_effects_identified=0|1
external_effects_identified=0|1
record_status: missing|partial|complete
```

## Dry-run validation record

Required fields:

```text
dry_run_started=0|1
dry_run_completed=0|1
dry_run_failed=0|1
failure_reason_visible=0|1
hidden_mutation_detected=0
effect_execution_performed=0
network_behavior_performed=0
runtime_authority_granted=0
remediation_or_manual_review_note:
record_status: missing|partial|complete
```

## Receipt and log records

Receipt fields:

```text
receipt_expected=0|1
receipt_available=0|1
receipt_path_visible=0|1
receipt_review_note:
record_status: missing|partial|complete
```

Engine log fields:

```text
engine_log_expected=0|1
engine_log_available=0|1
engine_log_path_visible=0|1
engine_log_review_note:
record_status: missing|partial|complete
```

Embedded console fields:

```text
embedded_console_status_available=0|1
embedded_console_status_summary:
record_status: missing|partial|complete
```

## Reset or uninstall record

Required fields:

```text
reset_available=0|1
uninstall_or_cleanup_available=0|1
reset_dry_run_available=0|1
cleanup_scope_visible=0|1
local_artifact_scope_visible=0|1
local_artifacts_created=0|1
cleanup_required=0|1
reset_failed=0|1
reset_failed_label_available=0|1
record_status: missing|partial|complete
```

## Failure-state record

Required failure labels:

```text
unsupported_platform:
missing_rust_toolchain:
missing_gui_dependency:
panel_launch_failed:
plan_generation_failed:
dry_run_failed:
receipt_missing:
log_missing:
reset_failed:
operator_cancelled:
manual_review_blocked:
```

For every failure label, record:

```text
runtime_authority_granted=0
network_authority_granted=0
hidden_mutation_detected=0
remediation_or_manual_review_note:
```

## Known limitations record

Required visible limitations:

```text
not_a_production_installer=1
not_a_daily_driver_product=1
not_a_security_boundary=1
not_malware_prevention=1
not_ransomware_prevention=1
not_fedora_approved=1
not_ubuntu_package_readiness=1
not_macos_app_readiness=1
not_operating_system_replacement=1
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

Guard or test reference:

```text
guard_or_test_reference_present=0|1
guard_or_test_path:
guard_or_test_result:
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
guard_or_test_reference_present=1
public_entrypoint_review_present=1
estimate_impact_review_present=1
claim_expansion_detected=0
```

This template result:

```text
bundle_complete=0
estimate_change_recommended=0
public_entrypoint_change_recommended=0
reason=this file defines the future bundle shape only
```

## Non-claims

This template does not provide workflow evidence, product readiness, Panel readiness, installer readiness, runtime behavior, effect execution, capability enforcement, cryptographic authority, signing authority, host behavior, network behavior, model execution, tool execution, shell execution, security hardening, malware prevention, ransomware prevention, sandboxing, operating-system behavior, or production support.

It records an evidence-bundle structure only.
