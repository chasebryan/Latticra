# macOS App Bundle Writer Dry-Run Prototype

Status: no-effect macOS app bundle writer dry-run prototype
Date: 2026-05-25 CDT
Scope: executable phase-report prototype for the future macOS user-local app bundle writer.

## Purpose

This prototype emits the writer-shaped phase report from the macOS user-local app bundle implementation plan.

It validates planned user-local paths, inspects existing targets for Latticra managed markers, checks whether optional local Panel executable and icon candidates are present, and reports the phase decision. It does not create an app bundle, write Application Support files, install wrappers, mutate shell profiles, build the Panel, use launchd, access Keychain, request TCC permissions, use Endpoint Security, use System Extensions, use Network Extensions, open the network, or grant runtime authority.

The macOS local candidate asset probe is the no-effect readiness check that can supply those optional executable and icon candidates. The macOS dry-run writer candidate integration then runs the probe and this writer dry-run together to prove that accepted inputs can move the writer decision to `ready-for-future-commit-gate` while `commit_user_local_managed_artifacts=0`. The macOS commit gate contract keeps that future gate closed, and the macOS verification transcript contract defines the exact post-write evidence required before install verification can be claimed.

## Command

```sh
sh scripts/macos-app-bundle-writer-dry-run.sh
```

Optional candidate inputs:

```sh
sh scripts/macos-app-bundle-writer-dry-run.sh \
  --panel-executable <local-executable> \
  --icon <local-icon-file>
```

## Report Fields

The report starts with:

```text
MACOS APP BUNDLE WRITER DRY RUN
dry_run_status=ok
phase_report_only=1
```

It must include:

```text
path_guard_status=allowed-user-local-dry-run
unsafe_path_detected=0
phase_1=validate_macos_host_and_toolchain_probe
phase_2=validate_user_local_paths_and_contract
phase_3=inspect_existing_targets_for_managed_markers
phase_4=stage_app_bundle_manifest_and_infoplist
phase_5=stage_panel_executable_and_icon_inputs
phase_6=stage_application_support_layout
phase_7=stage_cli_wrappers
phase_8=commit_user_local_managed_artifacts
phase_8_status=disabled
phase_9=write_receipts_and_measurements
phase_9_status=disabled
phase_10=run_verification_transcript
phase_10_status=not-run
commit_user_local_managed_artifacts=0
```

If no executable or icon candidate is supplied, the default dry-run may report:

```text
dry_run_decision=blocked-missing-panel-executable
```

That is expected. The dry-run writer is allowed to report readiness gaps, but it must not fill them by building, downloading, generating, signing, or writing files.

## Candidate Integration

The writer dry-run can be paired with the candidate probe by running:

```sh
sh scripts/macos-dry-run-writer-candidate-integration.sh \
  --panel-executable <local-executable> \
  --icon <local-icon-file>
```

When both checks agree and all write flags remain disabled, the integration reports:

```text
asset_probe_decision=ready-for-dry-run-writer-inputs
writer_dry_run_decision=ready-for-future-commit-gate
integration_decision=ready-for-future-commit-gate-no-effect
commit_user_local_managed_artifacts=0
```

## Blocked Paths

Unsafe path inputs must be blocked before write:

```sh
sh scripts/macos-app-bundle-writer-dry-run.sh --app-bundle /Applications/Latticra.app
```

Expected fields:

```text
path_guard_status=blocked-unsafe-user-local-path
unsafe_path_detected=1
dry_run_decision=blocked-unsafe-path
commit_user_local_managed_artifacts=0
app_bundle_write_performed=0
host_mutation_performed=0
```

## Managed Marker Inspection

Existing targets are classified as:

```text
absent
managed
unmanaged-preserve-and-block
```

The dry-run prototype must report unmanaged targets as blocked and preserved:

```text
unmanaged_existing_target=1
dry_run_decision=blocked-unmanaged-existing-target
```

It must not remove, overwrite, rename, chmod, or repair unmanaged targets.

## Authority Boundary

The dry-run prototype must always preserve:

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
root_authority=0
launchagent_authority=0
keychain_authority=0
tcc_bypass_authority=0
endpoint_security_authority=0
system_extension_authority=0
network_extension_authority=0
privileged_helper_authority=0
production_installer_ready=0
```

## Validation

This prototype is guarded by:

```sh
sh scripts/test-macos-app-bundle-writer-dry-run.sh
```

Expected output:

```text
macos_app_bundle_writer_dry_run: ok
```

## Non-Claims

This prototype is not macOS installation, macOS app bundle evidence, signed app evidence, notarization evidence, launchd evidence, Keychain evidence, Secure Enclave evidence, sandbox evidence, TCC approval evidence, Endpoint Security evidence, System Extension evidence, Network Extension evidence, privileged helper evidence, malware prevention, ransomware prevention, production readiness, or Apple platform approval.

## Previous Recommended Lane

```text
Add a macOS reset/uninstall evidence-bundle contract that groups implementation-gate, operator-intent, receipt, absence, planner, and classifier evidence before any live execution.
```

## Next Recommended Lane

```text
Add a macOS reset/uninstall live-runner acceptance-denial disposition closeout audit review disposition contract that records the reviewed no-effect closeout audit as a no-effect disposition without opening dispatch or deletion.
```
