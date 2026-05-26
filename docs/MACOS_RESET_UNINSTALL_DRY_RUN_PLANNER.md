# macOS Reset/Uninstall Dry-Run Planner

Status: no-effect macOS reset/uninstall dry-run planner
Date: 2026-05-25 CDT
Scope: dry-run reset/uninstall transcript planner built from the live-target classifier.

## Purpose

This planner consumes the macOS reset/uninstall live-target classifier and turns its target states into a reset/uninstall dry-run transcript.

It is report-only. It does not delete files, remove directories, write receipts, mutate host state, run absence verification, open the network, or claim reset/uninstall implementation.

The macOS reset/uninstall absence-report contract now defines the post-removal evidence shape that this planner hands off to.

The macOS reset/uninstall absence-report contract now defines the future evidence shape for the planner's absence-report phase.

## Command

```sh
sh scripts/macos-reset-uninstall-dry-run-planner.sh
```

The command writes only a deterministic report to stdout.

## Inputs

The planner consumes:

```text
scripts/macos-reset-uninstall-live-target-classifier.sh
macos_reset_uninstall_live_target_classifier_present=1
target_states_recorded=1
```

The same guarded user-local targets are accepted as optional arguments:

```text
--app-support-prefix
--app-bundle
--cli-wrapper
--reset-receipts-dir
```

Unsafe target paths are reported and blocked before any dry-run action is planned.

## Decisions

The planner can report:

```text
reset_uninstall_dry_run_planner_decision=ready-no-targets-observed-no-effect
reset_uninstall_dry_run_planner_decision=planned-managed-target-removal-no-effect
reset_uninstall_dry_run_planner_decision=blocked-unmanaged-targets-preserve-no-effect
reset_uninstall_dry_run_planner_decision=blocked-unsafe-path-no-effect
```

Managed targets become `would-remove-*` dry-run actions only when no unmanaged target blocks the plan. Unmanaged targets are preserved and block managed removal planning.

## Example Fields

```text
macos_reset_uninstall_dry_run_planner_present=1
planner_report_only=1
dry_run_transcript_present=1
reset_uninstall_dry_run_planner_transcript_present=1
planner_consumes_live_target_classifier=1
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
app_bundle_target_state=managed
app_bundle_dry_run_action=would-remove-managed-app-bundle
cli_wrapper_dry_run_action=would-remove-managed-wrapper
reset_receipt_dry_run_action=would-write-reset-uninstall-receipt-outside-removed-prefix
absence_report_dry_run_action=would-emit-verification-absence-report-no-effect
planned_removal_count=report-runtime
reset_uninstall_dry_run_evidence_present=0
absence_report_evidence_present=0
macos_reset_uninstall_implemented=0
```

## Phases

The dry-run transcript records:

```text
dry_run_phase_1=consume_live_target_classifier
dry_run_phase_2=validate_user_local_targets
dry_run_phase_3=plan_unmanaged_target_preservation
dry_run_phase_4=plan_managed_wrapper_removal
dry_run_phase_5=plan_managed_app_bundle_removal
dry_run_phase_6=plan_managed_application_support_removal
dry_run_phase_7=plan_receipt_write_outside_removed_prefix
dry_run_phase_8=plan_verification_absence_report
```

## Authority Boundary

This planner preserves:

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

This planner is guarded by:

```sh
sh scripts/test-macos-reset-uninstall-dry-run-planner.sh
```

Expected output:

```text
macos_reset_uninstall_dry_run_planner: ok
```

## Non-Claims

This planner is not macOS reset evidence, macOS uninstall evidence, macOS install evidence, macOS app bundle evidence, signed app evidence, notarization evidence, launchd evidence, Keychain evidence, Secure Enclave evidence, sandbox evidence, TCC approval evidence, Endpoint Security evidence, System Extension evidence, Network Extension evidence, privileged helper evidence, malware prevention, ransomware prevention, production readiness, Apple platform approval, or runtime authority.

## Previous Recommended Lane

```text
Add a macOS reset/uninstall evidence-bundle contract that groups implementation-gate, operator-intent, receipt, absence, planner, and classifier evidence before any live execution.
```

## Next Recommended Lane

```text
Add a macOS reset/uninstall live-runner acceptance-denial disposition review contract that reviews the no-effect disposition without opening dispatch or deletion.
```
