# macOS Reset/Uninstall Receipt-Schema Contract

Status: no-effect macOS reset/uninstall receipt-schema contract
Date: 2026-05-25 CDT
Scope: contract for future reset/uninstall receipts stored outside the removed prefix.

## Purpose

This contract defines the receipt schema that a future macOS reset/uninstall implementation must use when recording reset or uninstall evidence.

It is contract-only. It does not write receipts, delete files, remove directories, inspect post-removal state, mutate host state, open the network, or claim reset/uninstall implementation.

## Command

```sh
sh scripts/macos-reset-uninstall-receipt-schema-contract.sh
```

The command writes only a deterministic report to stdout.

## Current Decision

The current receipt-schema posture is:

```text
macos_reset_uninstall_receipt_schema_contract_present=1
macos_reset_uninstall_implementation_gate_contract_present=1
reset_uninstall_live_run_allowed=0
operator_reset_uninstall_intent_evidence_present=0
receipt_schema_contract_state=defined-no-effect
receipt_schema_contract_decision=contract-defined-receipt-not-written
receipt_schema_required=1
reset_uninstall_receipt_evidence_present=0
reset_receipt_evidence_present=0
receipt_schema_evidence_present=0
reset_receipt_write_performed=0
receipt_write_performed=0
receipt_written=0
```

## Required Inputs

A future reset/uninstall receipt must bind to the existing no-effect macOS reset/uninstall chain:

```text
macos_reset_uninstall_absence_report_contract_present=1
macos_reset_uninstall_dry_run_planner_present=1
reset_uninstall_dry_run_planner_transcript_present=1
macos_reset_uninstall_live_target_classifier_present=1
macos_reset_uninstall_dry_run_contract_present=1
macos_verification_transcript_contract_present=1
absence_report_evidence_present=0
reset_uninstall_dry_run_evidence_present=0
```

## Receipt Location

The future receipt must live outside the removed application-support prefix:

```text
app_support_prefix_target=$HOME/Library/Application Support/Latticra
app_bundle_target=$HOME/Applications/Latticra Panel.app
cli_wrapper_target=$HOME/.local/bin/latticra-panel
reset_receipts_dir_target=$HOME/Library/Application Support/Latticra Reset Receipts
reset_receipt_path_future=$HOME/Library/Application Support/Latticra Reset Receipts/reset-uninstall-receipt.json
absence_report_path_future=$HOME/Library/Application Support/Latticra Reset Receipts/absence-report.txt
receipt_must_be_outside_removed_prefix=1
removed_prefix_must_not_contain_receipt=1
```

## Schema Fields

The future receipt format is:

```text
receipt_format=json
receipt_schema_version=macos-reset-uninstall-receipt/1
receipt_digest_algorithm=sha256
receipt_operation_values=reset,uninstall
```

The future receipt must include:

```text
receipt_field_schema_version_required=1
receipt_field_operation_required=1
receipt_field_host_identity_required=1
receipt_field_architecture_required=1
receipt_field_started_at_required=1
receipt_field_completed_at_required=1
receipt_field_planner_transcript_digest_required=1
receipt_field_live_classifier_digest_required=1
receipt_field_absence_report_path_required=1
receipt_field_target_actions_required=1
receipt_field_removed_managed_targets_required=1
receipt_field_preserved_unmanaged_targets_required=1
receipt_field_authority_denials_required=1
receipt_field_no_network_required=1
receipt_field_no_root_required=1
```

## Phases

The future receipt-schema phases are:

```text
receipt_schema_phase_1=consume_dry_run_planner_transcript
receipt_schema_phase_2=consume_absence_report_contract
receipt_schema_phase_3=validate_outside_removed_prefix_path
receipt_schema_phase_4=record_target_action_summary
receipt_schema_phase_5=record_authority_denials
receipt_schema_phase_6=write_reset_uninstall_receipt
receipt_schema_phase_6_status=disabled
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
sh scripts/test-macos-reset-uninstall-receipt-schema-contract.sh
```

Expected output:

```text
macos_reset_uninstall_receipt_schema_contract: ok
```

## Non-Claims

This contract is not macOS reset evidence, macOS uninstall evidence, macOS install evidence, macOS app bundle evidence, receipt evidence, absence verification evidence, signed app evidence, notarization evidence, launchd evidence, Keychain evidence, Secure Enclave evidence, sandbox evidence, TCC approval evidence, Endpoint Security evidence, System Extension evidence, Network Extension evidence, privileged helper evidence, malware prevention, ransomware prevention, production readiness, Apple platform approval, or runtime authority.

## Next Recommended Lane

```text
Add a macOS reset/uninstall operator-intent contract for explicit future live reset/uninstall approval evidence.
```
