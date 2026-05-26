# macOS Commit Gate Contract

Status: no-effect macOS commit gate contract
Date: 2026-05-25 CDT
Scope: closed commit gate for any future macOS user-local managed app bundle writer.

## Purpose

This contract separates dry-run readiness from write authority.

The macOS dry-run writer candidate integration can report:

```text
integration_decision=ready-for-future-commit-gate-no-effect
```

The macOS verification transcript contract and reset/uninstall dry-run contract now define future evidence shapes, but they do not provide write, reset, uninstall, or transcript evidence. That does not open the commit gate. The current and only allowed commit posture remains:

```text
commit_gate_state=closed
commit_user_local_managed_artifacts=0
macos_app_bundle_commit_capable_writer_present=0
```

## Command

```sh
sh scripts/macos-commit-gate-contract.sh
```

The command writes only a deterministic report to stdout.

## Current Gate Decision

The current gate decision is:

```text
commit_gate_decision=blocked-missing-managed-write-implementation
```

The gate stays closed because these future pieces do not exist yet:

```text
managed_write_implementation_present=0
reset_uninstall_implementation_present=0
macos_verification_transcript_contract_present=1
verification_transcript_contract_present=1
verification_transcript_evidence_present=0
macos_reset_uninstall_dry_run_contract_present=1
macos_reset_uninstall_live_target_classifier_present=1
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
```

## Opening Preconditions

Before `commit_user_local_managed_artifacts` may ever become `1`, a later implementation must provide all of:

```text
candidate_flow_ready_required=1
operator_explicit_commit_intent_required=1
managed_write_implementation_present=1
reset_uninstall_implementation_present=1
verification_transcript_contract_present=1
verification_transcript_evidence_present=1
unsafe_path_negative_tests_required=1
unmanaged_target_preservation_tests_required=1
receipt_completeness_tests_required=1
reset_uninstall_dry_run_required=1
verification_transcript_required=1
```

The future implementation must still preserve user-local scope:

```text
root_authority=0
launchagent_authority=0
keychain_authority=0
tcc_bypass_authority=0
endpoint_security_authority=0
system_extension_authority=0
network_extension_authority=0
privileged_helper_authority=0
```

## Authority Boundary

This contract preserves:

```text
commit_user_local_managed_artifacts=0
application_support_write_performed=0
payload_write_performed=0
config_write_performed=0
receipt_write_performed=0
app_bundle_write_performed=0
info_plist_write_performed=0
app_executable_write_performed=0
app_icon_write_performed=0
cli_wrapper_write_performed=0
shell_profile_mutation_performed=0
installer_write_performed=0
host_mutation_performed=0
network_performed=0
production_installer_ready=0
```

## Validation

This contract is guarded by:

```sh
sh scripts/test-macos-commit-gate-contract.sh
```

Expected output:

```text
macos_commit_gate_contract: ok
```

## Non-Claims

This contract is not macOS installation, macOS app bundle evidence, signed app evidence, notarization evidence, launchd evidence, Keychain evidence, Secure Enclave evidence, sandbox evidence, TCC approval evidence, Endpoint Security evidence, System Extension evidence, Network Extension evidence, privileged helper evidence, malware prevention, ransomware prevention, production readiness, Apple platform approval, or runtime authority.

## Next Recommended Lane

```text
Add a macOS reset/uninstall live-runner acceptance-denial disposition closeout audit review disposition contract that records the reviewed no-effect closeout audit as a no-effect disposition without opening dispatch or deletion.
```
