# macOS Reset/Uninstall Live-Target Classifier

Status: no-effect macOS reset/uninstall live-target classifier
Date: 2026-05-25 CDT
Scope: read-only classifier for current macOS user-local reset/uninstall targets.

## Purpose

This classifier reports what exists today at the macOS reset/uninstall targets for the macOS reset/uninstall dry-run planner.

It is read-only. It does not delete files, remove directories, write receipts, mutate host state, run absence verification, open the network, or claim reset/uninstall implementation.

## Command

```sh
sh scripts/macos-reset-uninstall-live-target-classifier.sh
```

The command writes only a deterministic report to stdout.

## Target States

The classifier records these target states:

```text
absent
managed
unmanaged-preserve
not-classified-unsafe-path
```

It uses the same managed marker shape as the macOS app-bundle writer dry-run:

```text
LATTICRA_INSTALLER_MANAGED=1
LATTICRA_MACOS_USER_LOCAL_APP_BUNDLE=1
```

Directory targets are managed only when the marker exists at one of these locations:

```text
Contents/Resources/latticra/MANAGED_BY_LATTICRA
MANAGED_BY_LATTICRA
```

File targets are managed only when the file itself contains both marker lines.

## Classified Targets

The live classifier is bound to the current user-local macOS targets:

```text
app_support_prefix_target=$HOME/Library/Application Support/Latticra
app_bundle_target=$HOME/Applications/Latticra Panel.app
cli_wrapper_target=$HOME/.local/bin/latticra-panel
reset_receipts_dir_target=$HOME/Library/Application Support/Latticra Reset Receipts
reset_receipts_dir_preservation=preserve-outside-removed-prefix
```

## Decisions

The classifier can report:

```text
reset_uninstall_live_classifier_decision=ready-no-targets-observed-no-effect
reset_uninstall_live_classifier_decision=ready-managed-targets-observed-no-effect
reset_uninstall_live_classifier_decision=blocked-unmanaged-targets-preserve
reset_uninstall_live_classifier_decision=blocked-unsafe-path
```

An unmanaged target is never overwritten or removed. It is classified as `unmanaged-preserve` and blocks future reset/uninstall progress until an operator resolves it outside this no-effect lane.

## Example Fields

```text
macos_reset_uninstall_live_target_classifier_present=1
classifier_report_only=1
path_guard_status=allowed-user-local-classification
target_states_recorded=1
app_bundle_target_state=managed
app_bundle_target_state=unmanaged-preserve
managed_target_detected=report-runtime
unmanaged_target_detected=report-runtime
reset_uninstall_dry_run_evidence_present=0
macos_reset_uninstall_dry_run_planner_present=1
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
absence_report_evidence_present=0
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
reset_uninstall_effect_authorized=0
reset_uninstall_live_run_allowed=0
operator_reset_uninstall_intent_evidence_present=0
reset_receipt_evidence_present=0
reset_uninstall_receipt_evidence_present=0
macos_reset_uninstall_implemented=0
```

## Authority Boundary

This classifier preserves:

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

This classifier is guarded by:

```sh
sh scripts/test-macos-reset-uninstall-live-target-classifier.sh
```

Expected output:

```text
macos_reset_uninstall_live_target_classifier: ok
```

## Non-Claims

This classifier is not macOS reset evidence, macOS uninstall evidence, macOS install evidence, macOS app bundle evidence, signed app evidence, notarization evidence, launchd evidence, Keychain evidence, Secure Enclave evidence, sandbox evidence, TCC approval evidence, Endpoint Security evidence, System Extension evidence, Network Extension evidence, privileged helper evidence, malware prevention, ransomware prevention, production readiness, Apple platform approval, or runtime authority.

## Previous Recommended Lane

```text
Add a macOS reset/uninstall evidence-bundle contract that groups implementation-gate, operator-intent, receipt, absence, planner, and classifier evidence before any live execution.
```

## Next Recommended Lane

```text
Add a macOS reset/uninstall live-runner acceptance-gate contract that requires passed preflight, complete evidence, and explicit effect authorization before dispatch.
```
