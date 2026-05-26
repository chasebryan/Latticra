# macOS Reset/Uninstall Absence-Report Contract

Status: no-effect macOS reset/uninstall absence-report contract
Date: 2026-05-25 CDT
Scope: contract for future post-plan absence evidence before any reset/uninstall implementation.

## Purpose

This contract defines the absence-report evidence that a future macOS reset/uninstall implementation must emit after planned managed-target removal.

It is contract-only. It does not delete files, remove directories, inspect post-removal state, write reports, write receipts, mutate host state, open the network, or claim reset/uninstall implementation.

## Command

```sh
sh scripts/macos-reset-uninstall-absence-report-contract.sh
```

The command writes only a deterministic report to stdout.

## Current Decision

The current absence-report posture is:

```text
macos_reset_uninstall_absence_report_contract_present=1
macos_reset_uninstall_receipt_schema_contract_present=1
macos_reset_uninstall_implementation_gate_contract_present=1
macos_reset_uninstall_operator_intent_contract_present=1
macos_reset_uninstall_effect_authorization_contract_present=1
macos_reset_uninstall_evidence_bundle_contract_present=1
macos_reset_uninstall_live_implementation_plan_contract_present=1
macos_reset_uninstall_live_execution_preflight_contract_present=1
macos_reset_uninstall_live_denial_transcript_contract_present=1
macos_reset_uninstall_live_runner_interface_contract_present=1
live_execution_preflight_contract_state=closed-no-effect
live_execution_preflight_passed=0
live_execution_preflight_blocking=1
live_execution_preflight_deletion_enabled=0
live_denial_transcript_contract_state=recorded-no-effect
live_denial_transcript_recorded=1
live_denial_transcript_stdout_only=1
live_denial_transcript_file_write_enabled=0
live_runner_interface_contract_state=defined-no-effect
live_runner_interface_current_preflight_passed=0
live_runner_interface_current_decision=deny
live_runner_interface_dispatch_enabled=0
live_runner_interface_runner_handoff_enabled=0
live_implementation_plan_contract_state=defined-no-effect
live_reset_uninstall_implementation_present=0
evidence_bundle_contract_state=defined-no-effect
evidence_bundle_complete=0
reset_uninstall_evidence_bundle_complete=0
effect_authorization_contract_state=closed-no-effect
effect_authorization_open=0
reset_uninstall_effect_authorized=0
operator_intent_contract_state=defined-no-effect
operator_intent_evidence_written=0
reset_uninstall_live_run_allowed=0
reset_uninstall_deletion_enabled=0
operator_reset_uninstall_intent_evidence_present=0
operator_explicit_reset_uninstall_intent_observed=0
reset_uninstall_receipt_evidence_present=0
reset_receipt_evidence_present=0
absence_report_contract_state=defined-no-effect
absence_report_contract_decision=contract-defined-evidence-not-present
absence_report_required=1
absence_report_evidence_present=0
absence_report_run_performed=0
absence_report_written=0
```

## Required Inputs

A future absence report must bind to the existing no-effect macOS reset/uninstall chain:

```text
macos_reset_uninstall_dry_run_planner_present=1
reset_uninstall_dry_run_planner_transcript_present=1
macos_reset_uninstall_live_target_classifier_present=1
macos_reset_uninstall_dry_run_contract_present=1
macos_reset_uninstall_receipt_schema_contract_present=1
reset_uninstall_receipt_evidence_present=0
reset_receipt_evidence_present=0
macos_reset_uninstall_implementation_gate_contract_present=1
macos_reset_uninstall_operator_intent_contract_present=1
macos_reset_uninstall_effect_authorization_contract_present=1
macos_reset_uninstall_evidence_bundle_contract_present=1
macos_reset_uninstall_live_implementation_plan_contract_present=1
macos_reset_uninstall_live_execution_preflight_contract_present=1
macos_reset_uninstall_live_denial_transcript_contract_present=1
macos_reset_uninstall_live_runner_interface_contract_present=1
live_execution_preflight_contract_state=closed-no-effect
live_execution_preflight_passed=0
live_execution_preflight_blocking=1
live_execution_preflight_deletion_enabled=0
live_denial_transcript_contract_state=recorded-no-effect
live_denial_transcript_recorded=1
live_denial_transcript_stdout_only=1
live_denial_transcript_file_write_enabled=0
live_runner_interface_contract_state=defined-no-effect
live_runner_interface_current_preflight_passed=0
live_runner_interface_current_decision=deny
live_runner_interface_dispatch_enabled=0
live_runner_interface_runner_handoff_enabled=0
live_implementation_plan_contract_state=defined-no-effect
live_reset_uninstall_implementation_present=0
evidence_bundle_contract_state=defined-no-effect
evidence_bundle_complete=0
reset_uninstall_evidence_bundle_complete=0
effect_authorization_contract_state=closed-no-effect
reset_uninstall_effect_authorized=0
reset_uninstall_live_run_allowed=0
operator_reset_uninstall_intent_evidence_present=0
```

## Required Report Lines

The future report must record:

```text
absence_report_line_host_identity_required=1
absence_report_line_architecture_required=1
absence_report_line_operation_required=1
absence_report_line_planner_decision_required=1
absence_report_line_classifier_decision_required=1
absence_report_line_pre_removal_target_states_required=1
absence_report_line_managed_target_paths_required=1
absence_report_line_planned_actions_required=1
absence_report_line_post_removal_absence_required=1
absence_report_line_unmanaged_preservation_required=1
absence_report_line_receipt_path_required=1
absence_report_line_authority_denials_required=1
absence_report_line_no_network_required=1
absence_report_line_no_root_required=1
```

## Target Evidence

The future report must bind evidence to these targets:

```text
app_support_prefix_target=$HOME/Library/Application Support/Latticra
app_bundle_target=$HOME/Applications/Latticra Panel.app
cli_wrapper_target=$HOME/.local/bin/latticra-panel
reset_receipts_dir_target=$HOME/Library/Application Support/Latticra Reset Receipts
absence_report_path_future=$HOME/Library/Application Support/Latticra Reset Receipts/absence-report.txt
absence_report_must_be_outside_removed_prefix=1
```

Managed targets must have absence evidence only when they were planned and actually removed by a future implementation:

```text
app_bundle_absence_required_if_managed=1
app_support_absence_required_if_managed=1
cli_wrapper_absence_required_if_managed=1
unmanaged_target_preservation_evidence_required=1
reset_receipts_dir_preservation_required=1
reset_receipt_reference_required=1
planner_transcript_reference_required=1
live_classifier_reference_required=1
```

The macOS reset/uninstall receipt-schema contract defines the receipt fields that the future absence report must reference.

## Phases

The future absence-report phases are:

```text
absence_report_phase_1=consume_dry_run_planner_transcript
absence_report_phase_2=record_pre_removal_target_states
absence_report_phase_3=record_post_removal_absence_or_preservation
absence_report_phase_4=record_reset_receipt_reference
absence_report_phase_5=record_authority_denials
absence_report_phase_6=write_absence_report
absence_report_phase_6_status=disabled
```

## Authority Boundary

This contract preserves:

```text
managed_wrapper_removal_performed=0
managed_app_bundle_removal_performed=0
managed_application_support_removal_performed=0
reset_receipt_write_performed=0
absence_report_run_performed=0
absence_report_written=0
file_delete_performed=0
directory_delete_performed=0
application_support_write_performed=0
receipt_write_performed=0
app_bundle_write_performed=0
cli_wrapper_write_performed=0
shell_profile_mutation_performed=0
host_mutation_performed=0
network_performed=0
root_authority=0
launchagent_authority=0
keychain_authority=0
tcc_bypass_authority=0
endpoint_security_authority=0
system_extension_authority=0
network_extension_authority=0
privileged_helper_authority=0
runtime_authority_granted=0
production_installer_ready=0
```

## Validation

This contract is guarded by:

```sh
sh scripts/test-macos-reset-uninstall-absence-report-contract.sh
```

Expected output:

```text
macos_reset_uninstall_absence_report_contract: ok
```

## Non-Claims

This contract is not macOS reset evidence, macOS uninstall evidence, macOS install evidence, macOS app bundle evidence, absence verification evidence, signed app evidence, notarization evidence, launchd evidence, Keychain evidence, Secure Enclave evidence, sandbox evidence, TCC approval evidence, Endpoint Security evidence, System Extension evidence, Network Extension evidence, privileged helper evidence, malware prevention, ransomware prevention, production readiness, Apple platform approval, or runtime authority.

## Previous Recommended Lane

```text
Add a macOS reset/uninstall evidence-bundle contract that groups implementation-gate, operator-intent, receipt, absence, planner, and classifier evidence before any live execution.
```

## Next Recommended Lane

```text
Add a macOS reset/uninstall live-runner acceptance-denial disposition review contract that reviews the no-effect disposition without opening dispatch or deletion.
```
