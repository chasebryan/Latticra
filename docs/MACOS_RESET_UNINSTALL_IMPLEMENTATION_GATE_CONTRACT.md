# macOS Reset/Uninstall Implementation-Gate Contract

Status: no-effect macOS reset/uninstall implementation-gate contract
Date: 2026-05-25 CDT
Scope: contract for keeping future reset/uninstall live activity closed until all required macOS evidence exists.

## Purpose

This contract defines the gate that a future macOS reset/uninstall implementation must pass before live managed-target removal or receipt writing can be considered.

It is contract-only. It does not delete files, remove directories, write receipts, write absence reports, mutate host state, open the network, or claim reset/uninstall implementation.

## Command

```sh
sh scripts/macos-reset-uninstall-implementation-gate-contract.sh
```

The command writes only a deterministic report to stdout.

## Current Decision

The current implementation-gate posture is:

```text
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
implementation_gate_contract_state=closed-no-effect
implementation_gate_state=closed-no-effect
implementation_gate_decision=blocked-missing-reset-uninstall-evidence
implementation_gate_required=1
implementation_gate_open=0
reset_uninstall_live_run_allowed=0
reset_uninstall_deletion_enabled=0
managed_target_removal_allowed=0
managed_target_deletion_enabled=0
reset_uninstall_receipt_write_enabled=0
```

## Required Evidence

The gate stays closed until the reset/uninstall chain has all required evidence:

```text
macos_reset_uninstall_receipt_schema_contract_present=1
macos_reset_uninstall_absence_report_contract_present=1
macos_reset_uninstall_dry_run_planner_present=1
reset_uninstall_dry_run_planner_transcript_present=1
macos_reset_uninstall_live_target_classifier_present=1
macos_reset_uninstall_dry_run_contract_present=1
macos_verification_transcript_contract_present=1
macos_commit_gate_contract_present=1
reset_uninstall_dry_run_evidence_present=0
reset_uninstall_receipt_evidence_present=0
reset_receipt_evidence_present=0
receipt_schema_evidence_present=0
absence_report_evidence_present=0
operator_reset_uninstall_intent_evidence_present=0
operator_explicit_reset_uninstall_intent_observed=0
```

## Target Scope

The future gate must bind evidence to the known user-local macOS targets:

```text
app_support_prefix_target=$HOME/Library/Application Support/Latticra
app_bundle_target=$HOME/Applications/Latticra Panel.app
cli_wrapper_target=$HOME/.local/bin/latticra-panel
reset_receipts_dir_target=$HOME/Library/Application Support/Latticra Reset Receipts
reset_receipt_path_future=$HOME/Library/Application Support/Latticra Reset Receipts/reset-uninstall-receipt.json
absence_report_path_future=$HOME/Library/Application Support/Latticra Reset Receipts/absence-report.txt
```

## Gate Requirements

The future gate requires:

```text
managed_target_classification_required=1
live_target_classifier_evidence_required=1
dry_run_planner_transcript_required=1
receipt_schema_required=1
reset_uninstall_receipt_evidence_required=1
absence_report_contract_required=1
absence_report_evidence_required=1
operator_explicit_reset_uninstall_intent_required=1
operator_intent_must_name_operation=1
operator_intent_must_name_target_scope=1
operator_intent_must_acknowledge_managed_targets_only=1
operator_intent_must_acknowledge_no_unmanaged_removal=1
operator_intent_must_acknowledge_receipt_path=1
```

The gate conditions are:

```text
gate_condition_receipt_schema_contract_present=required
gate_condition_absence_report_contract_present=required
gate_condition_dry_run_planner_transcript_present=required
gate_condition_live_target_classifier_present=required
gate_condition_operator_intent_evidence_present=required
gate_condition_no_unmanaged_targets=required
gate_condition_no_unsafe_paths=required
gate_condition_receipt_outside_removed_prefix=required
gate_condition_no_network=required
gate_condition_no_root=required
```

## Phases

The future implementation-gate phases are:

```text
implementation_gate_phase_1=consume_live_target_classifier
implementation_gate_phase_2=consume_dry_run_planner_transcript
implementation_gate_phase_3=validate_receipt_schema_and_absence_contract
implementation_gate_phase_4=validate_operator_intent
implementation_gate_phase_5=authorize_future_reset_uninstall_implementation
implementation_gate_phase_6=run_live_reset_uninstall
implementation_gate_phase_1_status=contract-only
implementation_gate_phase_2_status=contract-only
implementation_gate_phase_3_status=contract-only
implementation_gate_phase_4_status=contract-only
implementation_gate_phase_5_status=disabled
implementation_gate_phase_6_status=disabled
```

## Authority Boundary

This contract preserves:

```text
reset_uninstall_implementation_present=0
macos_reset_uninstall_implemented=0
managed_marker_required=1
unmanaged_target_preservation_required=1
receipt_outside_removed_prefix_required=1
absence_report_required=1
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
sh scripts/test-macos-reset-uninstall-implementation-gate-contract.sh
```

Expected output:

```text
macos_reset_uninstall_implementation_gate_contract: ok
```

## Non-Claims

This contract is not macOS reset evidence, macOS uninstall evidence, macOS install evidence, macOS app bundle evidence, receipt evidence, absence verification evidence, operator approval evidence, signed app evidence, notarization evidence, launchd evidence, Keychain evidence, Secure Enclave evidence, sandbox evidence, TCC approval evidence, Endpoint Security evidence, System Extension evidence, Network Extension evidence, privileged helper evidence, malware prevention, ransomware prevention, production readiness, Apple platform approval, or runtime authority.

## Previous Recommended Lane

```text
Add a macOS reset/uninstall evidence-bundle contract that groups implementation-gate, operator-intent, receipt, absence, planner, and classifier evidence before any live execution.
```

## Next Recommended Lane

```text
Add a macOS reset/uninstall live-runner acceptance-denial transcript contract that records the closed acceptance gate without dispatching effects.
```
