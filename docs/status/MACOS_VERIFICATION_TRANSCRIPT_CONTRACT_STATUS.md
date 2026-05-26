# macOS Verification Transcript Contract Status

Status: no-effect verification transcript contract status
Date: 2026-05-25 CDT
Scope: status checkpoint after adding the macOS verification transcript contract.

## Summary

Latticra now has a no-effect macOS verification transcript contract.

The contract defines the exact post-write evidence a future user-local app bundle writer must emit before any status can claim `macos_install_verified=1`. It does not write a transcript, verify an install, create an app bundle, mutate host state, or grant authority.

## Status Fields

```text
macos_verification_transcript_contract_present=1
macos_verification_transcript_contract_guard_present=1
macos_commit_gate_contract_present=1
macos_reset_uninstall_dry_run_contract_present=1
macos_reset_uninstall_live_target_classifier_present=1
verification_transcript_contract_state=defined-no-effect
verification_transcript_contract_decision=contract-defined-evidence-not-present
verification_transcript_required=1
verification_transcript_evidence_present=0
macos_install_verified=0
commit_user_local_managed_artifacts=0
managed_write_implementation_present=0
reset_uninstall_implementation_present=0
host_os_macos_recorded_required=1
architecture_recorded_required=1
managed_app_bundle_present_required=1
info_plist_present_required=1
app_executable_digest_required=1
icon_asset_digest_required=1
application_support_marker_required=1
cli_wrapper_marker_required=1
receipt_completeness_required=1
authority_denial_fields_required=1
candidate_integration_ready_required=1
commit_gate_closed_until_evidence_required=1
reset_uninstall_dry_run_required=1
macos_reset_uninstall_dry_run_planner_present=1
reset_uninstall_dry_run_planner_transcript_present=1
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
reset_uninstall_dry_run_evidence_present=0
absence_report_evidence_present=0
unmanaged_target_preservation_required=1
seal_report_only_output_required=1
lat_or_lir_no_effect_probe_required=1
verification_transcript_run_performed=0
verification_transcript_written=0
application_support_write_performed=0
app_bundle_write_performed=0
receipt_write_performed=0
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
Latticra has a no-effect contract for the future macOS user-local install verification transcript.
```

That does not mean Latticra has a macOS installer, commit-capable app bundle writer, verified app bundle, signed build, notarized build, launchd integration, Keychain integration, Endpoint Security integration, System Extension integration, privileged helper, or production security capability.

## Guard Validation

This status record is guarded by:

```sh
sh scripts/test-macos-verification-transcript-contract.sh
```

Expected output:

```text
macos_verification_transcript_contract: ok
```

## Next Recommended Lane

```text
Add a macOS reset/uninstall live-runner acceptance-denial disposition review contract that reviews the no-effect disposition without opening dispatch or deletion.
```

## Non-Claims

This status record is not macOS install evidence, app bundle evidence, signed app evidence, notarization evidence, launchd evidence, Keychain evidence, Secure Enclave evidence, sandbox evidence, TCC approval evidence, Endpoint Security evidence, System Extension evidence, Network Extension evidence, privileged helper evidence, malware prevention, ransomware prevention, production readiness, Apple platform approval, or runtime authority.
