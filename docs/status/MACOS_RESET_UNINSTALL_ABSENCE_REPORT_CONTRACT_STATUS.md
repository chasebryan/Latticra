# macOS Reset/Uninstall Absence-Report Contract Status

Status: no-effect reset/uninstall absence-report contract status
Date: 2026-05-25 CDT
Scope: status checkpoint after adding the macOS reset/uninstall absence-report contract.

## Summary

Latticra now has a no-effect macOS reset/uninstall absence-report contract.

The contract defines the required future evidence for post-removal managed-target absence, unmanaged-target preservation, receipt linkage, planner linkage, and authority-denial lines. It does not delete files, write reports, write receipts, mutate host state, or claim reset/uninstall implementation.

## Status Fields

```text
macos_reset_uninstall_absence_report_contract_present=1
macos_reset_uninstall_receipt_schema_contract_present=1
macos_reset_uninstall_implementation_gate_contract_present=1
macos_reset_uninstall_operator_intent_contract_present=1
macos_reset_uninstall_effect_authorization_contract_present=1
macos_reset_uninstall_evidence_bundle_contract_present=1
macos_reset_uninstall_live_implementation_plan_contract_present=1
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
macos_reset_uninstall_absence_report_contract_guard_present=1
macos_reset_uninstall_dry_run_planner_present=1
macos_reset_uninstall_live_target_classifier_present=1
macos_reset_uninstall_dry_run_contract_present=1
macos_reset_uninstall_receipt_schema_contract_present=1
macos_reset_uninstall_implementation_gate_contract_present=1
macos_reset_uninstall_operator_intent_contract_present=1
macos_reset_uninstall_effect_authorization_contract_present=1
macos_reset_uninstall_evidence_bundle_contract_present=1
macos_reset_uninstall_live_implementation_plan_contract_present=1
live_implementation_plan_contract_state=defined-no-effect
live_reset_uninstall_implementation_present=0
evidence_bundle_contract_state=defined-no-effect
evidence_bundle_complete=0
reset_uninstall_evidence_bundle_complete=0
effect_authorization_contract_state=closed-no-effect
reset_uninstall_effect_authorized=0
reset_uninstall_live_run_allowed=0
operator_reset_uninstall_intent_evidence_present=0
absence_report_contract_state=defined-no-effect
absence_report_required=1
absence_report_evidence_present=0
absence_report_run_performed=0
absence_report_written=0
app_bundle_absence_required_if_managed=1
app_support_absence_required_if_managed=1
cli_wrapper_absence_required_if_managed=1
unmanaged_target_preservation_evidence_required=1
reset_receipts_dir_preservation_required=1
reset_receipt_reference_required=1
reset_receipt_evidence_present=0
reset_uninstall_receipt_evidence_present=0
planner_transcript_reference_required=1
live_classifier_reference_required=1
macos_reset_uninstall_implemented=0
reset_uninstall_implementation_present=0
managed_wrapper_removal_performed=0
managed_app_bundle_removal_performed=0
managed_application_support_removal_performed=0
reset_receipt_write_performed=0
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
Latticra has a no-effect macOS reset/uninstall absence-report contract for future post-removal evidence.
```

That does not mean Latticra has a macOS reset implementation, uninstall implementation, installer, commit-capable app bundle writer, verified app bundle, signed build, notarized build, launchd integration, Keychain integration, Endpoint Security integration, System Extension integration, privileged helper, or production security capability.

## Guard Validation

This status record is guarded by:

```sh
sh scripts/test-macos-reset-uninstall-absence-report-contract.sh
```

Expected output:

```text
macos_reset_uninstall_absence_report_contract: ok
```

## Next Recommended Lane

```text
Add a macOS reset/uninstall live-execution preflight contract that proves the live implementation plan still cannot delete until all evidence gates are satisfied.
```

## Non-Claims

This status record is not macOS reset evidence, macOS uninstall evidence, macOS install evidence, app bundle evidence, absence verification evidence, signed app evidence, notarization evidence, launchd evidence, Keychain evidence, Secure Enclave evidence, sandbox evidence, TCC approval evidence, Endpoint Security evidence, System Extension evidence, Network Extension evidence, privileged helper evidence, malware prevention, ransomware prevention, production readiness, Apple platform approval, or runtime authority.
