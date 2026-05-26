# macOS Reset/Uninstall Live-Denial Transcript Contract

Status: no-effect macOS reset/uninstall live-denial transcript contract
Date: 2026-05-26 CDT
Scope: contract for recording the failed macOS reset/uninstall live-execution preflight decision without deleting files or writing receipts.

## Purpose

This contract defines the transcript emitted after the live-execution preflight remains blocked. It records why live reset/uninstall execution is denied, while preserving the current no-effect boundary.

It is contract-only. It does not authorize effects, delete files, remove directories, write receipts, write absence reports, mutate host state, open the network, or claim reset/uninstall implementation.

## Command

```sh
sh scripts/macos-reset-uninstall-live-denial-transcript-contract.sh
```

The command writes only a deterministic report to stdout.

## Current Decision

The current live-denial transcript posture is:

```text
macos_reset_uninstall_live_denial_transcript_contract_present=1
macos_reset_uninstall_live_runner_interface_contract_present=1
live_denial_transcript_contract_state=recorded-no-effect
live_denial_transcript_contract_decision=denied-by-preflight-block
live_denial_transcript_required=1
live_denial_transcript_present=1
live_denial_transcript_recorded=1
live_denial_transcript_stdout_only=1
live_denial_transcript_file_write_enabled=0
live_runner_interface_contract_state=defined-no-effect
live_runner_interface_current_preflight_passed=0
live_runner_interface_current_decision=deny
live_runner_interface_dispatch_enabled=0
live_runner_interface_runner_handoff_enabled=0
live_denial_transcript_receipt_write_enabled=0
live_denial_transcript_absence_report_write_enabled=0
live_denial_transcript_preflight_present=1
live_denial_transcript_preflight_passed=0
live_denial_transcript_denial_recorded=1
live_denial_transcript_denial_reason=missing-complete-evidence-bundle-and-effect-authorization
live_denial_transcript_denial_source=macos-reset-uninstall-live-execution-preflight-contract
live_denial_transcript_effect=none
live_denial_transcript_effect_authorization_required=1
live_denial_transcript_effect_authorized=0
reset_uninstall_live_run_allowed=0
reset_uninstall_deletion_enabled=0
managed_target_removal_allowed=0
managed_target_deletion_enabled=0
reset_uninstall_receipt_write_enabled=0
absence_report_write_enabled=0
```

## Preflight Input

The transcript records the failed preflight decision:

```text
macos_reset_uninstall_live_execution_preflight_contract_present=1
live_execution_preflight_contract_state=closed-no-effect
live_execution_preflight_contract_decision=blocked-missing-complete-evidence-bundle-and-effect-authorization
live_execution_preflight_required=1
live_execution_preflight_present=1
live_execution_preflight_passed=0
live_execution_preflight_blocking=1
live_execution_preflight_evidence_present=0
live_execution_preflight_record_write_enabled=0
live_execution_preflight_denial_recorded=1
live_execution_preflight_denial_reason=missing-complete-evidence-bundle-and-effect-authorization
```

The underlying gates remain closed:

```text
macos_reset_uninstall_live_implementation_plan_contract_present=1
live_implementation_plan_contract_state=defined-no-effect
live_implementation_plan_execution_enabled=0
live_implementation_plan_deletion_enabled=0
live_implementation_plan_preflight_present=1
live_implementation_plan_preflight_passed=0
macos_reset_uninstall_evidence_bundle_contract_present=1
evidence_bundle_contract_state=defined-no-effect
reset_uninstall_evidence_bundle_complete=0
evidence_bundle_complete=0
reset_uninstall_evidence_bundle_valid=0
reset_uninstall_evidence_bundle_evidence_present=0
macos_reset_uninstall_effect_authorization_contract_present=1
effect_authorization_contract_state=closed-no-effect
effect_authorization_open=0
reset_uninstall_effect_authorized=0
macos_reset_uninstall_implementation_gate_contract_present=1
implementation_gate_contract_state=closed-no-effect
implementation_gate_open=0
macos_reset_uninstall_operator_intent_contract_present=1
operator_intent_contract_state=defined-no-effect
operator_reset_uninstall_intent_evidence_present=0
operator_explicit_reset_uninstall_intent_observed=0
```

## Target Scope

The transcript remains limited to user-local managed macOS targets and future receipt locations:

```text
app_support_prefix_target=$HOME/Library/Application Support/Latticra
app_bundle_target=$HOME/Applications/Latticra Panel.app
cli_wrapper_target=$HOME/.local/bin/latticra-panel
reset_receipts_dir_target=$HOME/Library/Application Support/Latticra Reset Receipts
reset_receipt_path_future=$HOME/Library/Application Support/Latticra Reset Receipts/reset-uninstall-receipt.json
absence_report_path_future=$HOME/Library/Application Support/Latticra Reset Receipts/absence-report.txt
```

## Transcript Requirements

The transcript requires:

```text
live_denial_transcript_schema_version=macos-reset-uninstall-live-denial-transcript/1
live_denial_transcript_required_input_count=7
live_denial_transcript_observed_input_count=7
live_denial_transcript_requires_live_execution_preflight=1
live_denial_transcript_requires_preflight_denial=1
live_denial_transcript_requires_denial_reason=1
live_denial_transcript_requires_no_receipt_write=1
live_denial_transcript_requires_no_absence_report_write=1
live_denial_transcript_requires_no_deletion=1
live_denial_transcript_requires_no_network=1
live_denial_transcript_requires_no_root=1
live_denial_transcript_condition_preflight_present=required
live_denial_transcript_condition_preflight_passed=must_be_zero_for_denial
live_denial_transcript_condition_denial_reason=required
live_denial_transcript_condition_stdout_only=required
live_denial_transcript_condition_no_receipt_write=required
live_denial_transcript_condition_no_absence_report_write=required
live_denial_transcript_condition_no_deletion=required
live_denial_transcript_condition_no_network=required
live_denial_transcript_condition_no_root=required
```

The current result state is:

```text
live_denial_transcript_result_preflight_present=met
live_denial_transcript_result_preflight_passed=not_met
live_denial_transcript_result_denial_reason=met
live_denial_transcript_result_stdout_only=met
live_denial_transcript_result_no_receipt_write=met
live_denial_transcript_result_no_absence_report_write=met
live_denial_transcript_result_no_deletion=met
live_denial_transcript_result_no_network=met
live_denial_transcript_result_no_root=met
```

## Entries

The transcript entries are:

```text
live_denial_transcript_entry_1=preflight_contract_present
live_denial_transcript_entry_2=preflight_decision_blocked
live_denial_transcript_entry_3=missing_complete_evidence_bundle
live_denial_transcript_entry_4=missing_effect_authorization
live_denial_transcript_entry_5=missing_operator_intent_evidence
live_denial_transcript_entry_6=implementation_gate_closed
live_denial_transcript_entry_7=no_effects_performed
live_denial_transcript_entry_1_status=met
live_denial_transcript_entry_2_status=recorded
live_denial_transcript_entry_3_status=recorded
live_denial_transcript_entry_4_status=recorded
live_denial_transcript_entry_5_status=recorded
live_denial_transcript_entry_6_status=recorded
live_denial_transcript_entry_7_status=recorded
```

## Phases

The transcript phases are mapped but closed:

```text
live_denial_transcript_phase_1=load_preflight_decision
live_denial_transcript_phase_2=render_denial_transcript
live_denial_transcript_phase_3=preserve_no_effect_boundary
live_denial_transcript_phase_4=handoff_to_live_runner_interface
live_denial_transcript_phase_1_status=contract-only
live_denial_transcript_phase_2_status=stdout-only
live_denial_transcript_phase_3_status=enforced-by-zero-authority
live_denial_transcript_phase_4_status=disabled-until-interface-contract
```

## Authority Boundary

This contract preserves:

```text
reset_uninstall_implementation_present=0
macos_reset_uninstall_implemented=0
live_reset_uninstall_runner_present=0
live_reset_uninstall_runner_enabled=0
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
sh scripts/test-macos-reset-uninstall-live-denial-transcript-contract.sh
```

Expected output:

```text
macos_reset_uninstall_live_denial_transcript_contract: ok
```

## Non-Claims

This contract is not macOS reset evidence, macOS uninstall evidence, macOS install evidence, macOS app bundle evidence, live approval evidence, operator approval evidence, effect approval evidence, complete evidence-bundle evidence, live execution evidence, live reset execution, live uninstall execution, receipt evidence, absence verification evidence, signed app evidence, notarization evidence, launchd evidence, Keychain evidence, Secure Enclave evidence, sandbox evidence, TCC approval evidence, Endpoint Security evidence, System Extension evidence, Network Extension evidence, privileged helper evidence, malware prevention, ransomware prevention, production readiness, Apple platform approval, or runtime authority.

## Previous Recommended Lane

```text
Add a macOS reset/uninstall live-denial transcript contract that records the failed preflight decision without deleting files.
```

## Next Recommended Lane

```text
Add a macOS reset/uninstall live-runner denied-dispatch transcript contract that records the no-op runner denial without enabling deletion.
```

Follow-on no-op prototype lane:

```text
Add a macOS reset/uninstall live-runner no-op prototype contract that exercises the denied interface path without deleting files.
```
