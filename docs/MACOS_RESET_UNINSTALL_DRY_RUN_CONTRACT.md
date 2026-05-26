# macOS Reset/Uninstall Dry-Run Contract

Status: no-effect macOS reset/uninstall dry-run contract
Date: 2026-05-25 CDT
Scope: contract for managed-target removal order before any future macOS user-local app bundle reset or uninstall can run.

## Purpose

This contract defines how a future macOS reset/uninstall dry-run must order managed-target removal and preserve user files.

It is contract-only. It does not delete files, remove directories, write receipts, mutate host state, run absence verification, or claim reset/uninstall implementation.

The macOS verification transcript contract can require this reset/uninstall dry-run contract as evidence shape. The macOS reset/uninstall live-target classifier can report present, managed, and unmanaged targets, and the macOS reset/uninstall dry-run planner can turn those states into a no-effect transcript. No reset or uninstall evidence exists yet.

## Command

```sh
sh scripts/macos-reset-uninstall-dry-run-contract.sh
```

The command writes only a deterministic report to stdout.

## Current Decision

The current reset/uninstall posture is:

```text
macos_reset_uninstall_dry_run_contract_present=1
reset_uninstall_dry_run_contract_state=defined-no-effect
reset_uninstall_dry_run_decision=contract-defined-removal-not-performed
reset_uninstall_dry_run_evidence_present=0
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
absence_report_evidence_present=0
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
reset_receipt_evidence_present=0
reset_uninstall_receipt_evidence_present=0
macos_reset_uninstall_implemented=0
reset_uninstall_implementation_present=0
```

## Managed Targets

The future dry-run must bind reset/uninstall evidence to these user-local targets:

```text
app_support_prefix_target=$HOME/Library/Application Support/Latticra
app_bundle_target=$HOME/Applications/Latticra Panel.app
cli_wrapper_target=$HOME/.local/bin/latticra-panel
reset_receipts_dir_target=$HOME/Library/Application Support/Latticra Reset Receipts
```

Only targets with Latticra managed markers may be removed by a future implementation:

```text
managed_marker_required=1
unmanaged_target_preservation_required=1
receipt_outside_removed_prefix_required=1
absence_report_required=1
```

## Removal Order

The required reset/uninstall dry-run phases are:

```text
reset_phase_1=validate_user_local_targets
reset_phase_2=inspect_managed_markers
reset_phase_3=preserve_unmanaged_targets
reset_phase_4=remove_managed_wrappers
reset_phase_5=remove_managed_app_bundle
reset_phase_6=remove_managed_application_support_prefix
reset_phase_7=write_reset_or_uninstall_receipt_outside_removed_prefix
reset_phase_8=emit_verification_absence_report
```

In this contract, removal phases remain disabled:

```text
reset_phase_4_status=disabled
reset_phase_5_status=disabled
reset_phase_6_status=disabled
reset_phase_7_status=disabled
reset_phase_8_status=not-run
```

## Preservation Rules

The future reset/uninstall lane must preserve:

```text
preserve_user_logs=1
preserve_user_caches=1
preserve_shell_profiles=1
preserve_keychain_items=1
preserve_launchagents=1
preserve_login_items=1
preserve_homebrew_files=1
preserve_applications_root=1
preserve_library_root=1
preserve_system_root=1
preserve_usr_local=1
preserve_opt_homebrew=1
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

The follow-on macOS reset/uninstall live-target classifier reads the current user-local target set and reports absent, managed, unmanaged-preserve, or unsafe-path states without deleting files.

The macOS reset/uninstall dry-run planner consumes that classifier output and reports planned managed-target actions without deleting files.

This contract is guarded by:

```sh
sh scripts/test-macos-reset-uninstall-dry-run-contract.sh
```

Expected output:

```text
macos_reset_uninstall_dry_run_contract: ok
```

## Non-Claims

This contract is not macOS reset evidence, macOS uninstall evidence, macOS installation, macOS app bundle evidence, signed app evidence, notarization evidence, launchd evidence, Keychain evidence, Secure Enclave evidence, sandbox evidence, TCC approval evidence, Endpoint Security evidence, System Extension evidence, Network Extension evidence, privileged helper evidence, malware prevention, ransomware prevention, production readiness, Apple platform approval, or runtime authority.

## Next Recommended Lane

```text
Add a macOS reset/uninstall live-execution preflight contract that proves the live implementation plan still cannot delete until all evidence gates are satisfied.
```
