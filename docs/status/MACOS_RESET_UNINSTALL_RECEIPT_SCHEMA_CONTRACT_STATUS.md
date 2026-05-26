# macOS Reset/Uninstall Receipt-Schema Contract Status

Status: no-effect reset/uninstall receipt-schema contract status
Date: 2026-05-25 CDT
Scope: status checkpoint after adding the macOS reset/uninstall receipt-schema contract.

## Summary

Latticra now has a no-effect macOS reset/uninstall receipt-schema contract.

The contract defines the future reset/uninstall receipt location, schema version, JSON format, digest binding, target-action fields, preserved-target fields, and authority-denial fields. It does not delete files, write receipts, write absence reports, mutate host state, or claim reset/uninstall implementation.

## Status Fields

```text
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
macos_reset_uninstall_receipt_schema_contract_guard_present=1
macos_reset_uninstall_absence_report_contract_present=1
macos_reset_uninstall_dry_run_planner_present=1
macos_reset_uninstall_live_target_classifier_present=1
macos_reset_uninstall_dry_run_contract_present=1
macos_verification_transcript_contract_present=1
receipt_schema_contract_state=defined-no-effect
receipt_schema_required=1
reset_uninstall_receipt_evidence_present=0
reset_receipt_evidence_present=0
receipt_schema_evidence_present=0
reset_receipt_write_performed=0
receipt_write_performed=0
receipt_written=0
receipt_must_be_outside_removed_prefix=1
removed_prefix_must_not_contain_receipt=1
receipt_format=json
receipt_schema_version=macos-reset-uninstall-receipt/1
receipt_digest_algorithm=sha256
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
macos_reset_uninstall_implemented=0
reset_uninstall_implementation_present=0
managed_wrapper_removal_performed=0
managed_app_bundle_removal_performed=0
managed_application_support_removal_performed=0
file_delete_performed=0
directory_delete_performed=0
application_support_write_performed=0
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

## Public Meaning

The careful public meaning is:

```text
Latticra has a no-effect macOS reset/uninstall receipt-schema contract for future reset/uninstall receipts outside the removed prefix.
```

That does not mean Latticra has a macOS reset implementation, uninstall implementation, installer, commit-capable app bundle writer, verified app bundle, signed build, notarized build, launchd integration, Keychain integration, Endpoint Security integration, System Extension integration, privileged helper, or production security capability.

## Guard Validation

This status record is guarded by:

```sh
sh scripts/test-macos-reset-uninstall-receipt-schema-contract.sh
```

Expected output:

```text
macos_reset_uninstall_receipt_schema_contract: ok
```

## Next Recommended Lane

```text
Add a macOS reset/uninstall live-runner denied-dispatch review contract that keeps review-only dispatch denial evidence separate from any effects.
```

## Non-Claims

This status record is not macOS reset evidence, macOS uninstall evidence, macOS install evidence, app bundle evidence, receipt evidence, absence verification evidence, signed app evidence, notarization evidence, launchd evidence, Keychain evidence, Secure Enclave evidence, sandbox evidence, TCC approval evidence, Endpoint Security evidence, System Extension evidence, Network Extension evidence, privileged helper evidence, malware prevention, ransomware prevention, production readiness, Apple platform approval, or runtime authority.
