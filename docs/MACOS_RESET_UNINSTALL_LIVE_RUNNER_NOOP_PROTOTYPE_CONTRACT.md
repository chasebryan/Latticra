# macOS Reset/Uninstall Live-Runner No-Op Prototype Contract

Status: no-effect macOS reset/uninstall live-runner no-op prototype contract
Date: 2026-05-26 CDT
Scope: contract for exercising the denied live-runner interface path without deleting files.

## Purpose

This contract defines a no-op prototype for the future macOS reset/uninstall live runner. It exercises only the denied interface path because the live-execution preflight is still blocked.

It is contract-only. It does not authorize effects, delete files, remove directories, write receipts, write absence reports, mutate host state, open the network, or claim reset/uninstall implementation.

## Command

```sh
sh scripts/macos-reset-uninstall-live-runner-noop-prototype-contract.sh
```

The command writes only a deterministic report to stdout.

## Current Decision

```text
macos_reset_uninstall_live_runner_noop_prototype_contract_present=1
live_runner_noop_prototype_contract_state=executed-no-effect
live_runner_noop_prototype_contract_decision=denied-interface-path-only
live_runner_noop_prototype_invocation_simulated=1
live_runner_noop_prototype_stdout_only=1
live_runner_noop_prototype_dispatch_enabled=0
live_runner_noop_prototype_runner_enabled=0
live_runner_noop_prototype_runner_effect_enabled=0
live_runner_noop_prototype_deletion_enabled=0
live_runner_noop_prototype_receipt_write_enabled=0
live_runner_noop_prototype_absence_report_write_enabled=0
live_runner_noop_prototype_denial_path_exercised=1
live_runner_noop_prototype_accept_path_exercised=0
live_runner_noop_prototype_effect=none
live_runner_noop_prototype_effect_authorized=0
live_runner_noop_prototype_preflight_passed=0
live_runner_noop_prototype_interface_present=1
live_runner_noop_prototype_interface_denial_path_active=1
live_runner_noop_prototype_no_effects_performed=1
reset_uninstall_live_run_allowed=0
reset_uninstall_deletion_enabled=0
```

## Interface Input

```text
macos_reset_uninstall_live_runner_interface_contract_present=1
live_runner_interface_contract_state=defined-no-effect
live_runner_interface_contract_decision=denied-current-preflight-not-passed
live_runner_interface_preflight_passed=0
live_runner_interface_denial_path_active=1
live_runner_interface_invocation_enabled=0
live_runner_interface_deletion_enabled=0
macos_reset_uninstall_live_execution_preflight_contract_present=1
live_execution_preflight_contract_state=closed-no-effect
live_execution_preflight_passed=0
live_execution_preflight_blocking=1
```

## Requirements

```text
live_runner_noop_prototype_schema_version=macos-reset-uninstall-live-runner-noop-prototype/1
live_runner_noop_prototype_requires_runner_interface=1
live_runner_noop_prototype_requires_failed_preflight=1
live_runner_noop_prototype_requires_denial_path=1
live_runner_noop_prototype_requires_denied_interface_path=1
live_runner_noop_prototype_requires_no_dispatch=1
live_runner_noop_prototype_requires_no_deletion=1
live_runner_noop_prototype_requires_no_receipt_write=1
live_runner_noop_prototype_requires_no_absence_report_write=1
live_runner_noop_prototype_requires_no_network=1
live_runner_noop_prototype_requires_no_root=1
live_runner_noop_prototype_result_runner_interface=met
live_runner_noop_prototype_result_failed_preflight=met
live_runner_noop_prototype_result_denial_path=met
live_runner_noop_prototype_result_denied_interface_path=met
live_runner_noop_prototype_result_no_dispatch=met
live_runner_noop_prototype_result_no_deletion=met
live_runner_noop_prototype_result_no_receipt_write=met
live_runner_noop_prototype_result_no_absence_report_write=met
live_runner_noop_prototype_result_no_network=met
live_runner_noop_prototype_result_no_root=met
```

## Phases

```text
live_runner_noop_prototype_phase_1=load_runner_interface
live_runner_noop_prototype_phase_2=exercise_denied_interface_path
live_runner_noop_prototype_phase_3=confirm_no_effect_dispatch
live_runner_noop_prototype_phase_4=handoff_to_denied_dispatch_transcript
live_runner_noop_prototype_phase_5=return_noop_denial
live_runner_noop_prototype_phase_1_status=contract-only
live_runner_noop_prototype_phase_2_status=noop-denial-only
live_runner_noop_prototype_phase_3_status=met
live_runner_noop_prototype_phase_4_status=blocked-no-effect
live_runner_noop_prototype_phase_5_status=stdout-only
```

## Authority Boundary

```text
reset_uninstall_implementation_present=0
macos_reset_uninstall_implemented=0
live_reset_uninstall_runner_present=0
live_reset_uninstall_runner_enabled=0
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
runtime_authority_granted=0
production_installer_ready=0
```

## Validation

```sh
sh scripts/test-macos-reset-uninstall-live-runner-noop-prototype-contract.sh
```

Expected output:

```text
macos_reset_uninstall_live_runner_noop_prototype_contract: ok
```

## Non-Claims

This contract is not macOS reset evidence, macOS uninstall evidence, live reset execution, live uninstall execution, receipt evidence, absence verification evidence, signed app evidence, notarization evidence, launchd evidence, Keychain evidence, Endpoint Security evidence, System Extension evidence, privileged helper evidence, production readiness, Apple platform approval, or runtime authority.

## Previous Recommended Lane

```text
Add a macOS reset/uninstall live-runner no-op prototype contract that exercises the denied interface path without deleting files.
```

## Next Recommended Lane

```text
Add a macOS reset/uninstall live-runner acceptance-denial transcript contract that records the closed acceptance gate without dispatching effects.
```
