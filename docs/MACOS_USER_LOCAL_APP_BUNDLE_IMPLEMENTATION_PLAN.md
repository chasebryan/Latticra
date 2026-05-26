# macOS User-Local App Bundle Implementation Plan

Status: no-effect macOS user-local app bundle implementation plan
Date: 2026-05-25 CDT
Scope: writer phases, failure behavior, reset/uninstall sequencing, verification commands, and guard tests before any app bundle writer exists.

## Purpose

This plan defines how a future macOS user-local Latticra Panel app bundle writer should be implemented.

It follows the macOS user-local app bundle contract and remains no-effect planning. It does not create an app bundle, write Application Support files, install wrappers, mutate shell profiles, build the Panel, use launchd, access Keychain, request TCC permissions, use Endpoint Security, use System Extensions, use Network Extensions, open the network, or grant runtime authority.

## Required Inputs

A future writer must require these inputs before any write path is enabled:

```text
macos_build_platform_probe_present=1
macos_dry_run_plan_adapter_present=1
macos_user_local_app_bundle_contract_present=1
path_guard_status=allowed-user-local-dry-run
dry_run_allowed=1
application_support_prefix=$HOME/Library/Application Support/Latticra
app_bundle=$HOME/Applications/Latticra Panel.app
cli_bin=$HOME/.local/bin
```

The writer must fail closed if any input is missing or if a path expands outside the user-local allowlist.

## Writer Phase Plan

The future writer must use explicit phases:

```text
phase_1=validate_macos_host_and_toolchain_probe
phase_2=validate_user_local_paths_and_contract
phase_3=inspect_existing_targets_for_managed_markers
phase_4=stage_app_bundle_manifest_and_infoplist
phase_5=stage_panel_executable_and_icon_inputs
phase_6=stage_application_support_layout
phase_7=stage_cli_wrappers
phase_8=commit_user_local_managed_artifacts
phase_9=write_receipts_and_measurements
phase_10=run_verification_transcript
```

The first implementation slice should support report-only phase rendering before enabling commit behavior:

```text
phase_report_only=1
commit_user_local_managed_artifacts=0
```

## Phase Requirements

Phase 1 must record:

```text
macos_host_detected=<0-or-1>
host_arch=<architecture>
clang_probe_recorded=<0-or-1>
rust_probe_recorded=1
panel_build_ready=<0-or-1>
c_test_build_ready=<0-or-1>
```

Phase 2 must re-run path guards and refuse:

```text
/Applications
/Library
/System
/usr/local
/opt/homebrew
LaunchDaemons
system LaunchAgents
kernel extension paths
system extension paths
network extension paths
privileged helper paths
```

Phase 3 must preserve any existing target that lacks both markers:

```text
LATTICRA_INSTALLER_MANAGED=1
LATTICRA_MACOS_USER_LOCAL_APP_BUNDLE=1
```

Phase 4 must render an Info.plist plan with:

```text
CFBundleIdentifier=systems.latticra.panel
CFBundleExecutable=latticra-panel
CFBundlePackageType=APPL
NSHighResolutionCapable=true
```

Phase 5 must require a local Panel executable candidate and icon candidate before real writes. The macOS dry-run writer candidate integration proves this phase can become ready in dry-run only when the local candidate asset probe and writer dry-run agree. It must not download, build, sign, notarize, or generate network-dependent assets.

The macOS commit gate contract keeps Phase 8 closed until a future managed-write implementation, reset/uninstall implementation, and verification transcript evidence exist. The macOS verification transcript contract now defines the required evidence shape, but no verification transcript evidence exists yet.

Phase 6 must stage:

```text
MANAGED_BY_LATTICRA
etc/latticra/installer-config.toml
etc/latticra/macos-plan.txt
lib/latticra/payload-manifest.txt
receipts/
```

Phase 7 must stage wrappers only under:

```text
$HOME/.local/bin
```

Phase 8 may commit only after all staged files have passed validation and only if every existing target is either absent or managed by Latticra.

Phase 9 must write receipts after successful managed writes and must record all authority-denial fields.

Phase 10 must run the verification transcript and fail if any required transcript line is missing.

## Failure Behavior

The future writer must fail closed:

```text
unsafe_path_detected -> block_before_write
unmanaged_existing_app_bundle -> preserve_and_block
unmanaged_existing_wrapper -> preserve_and_block
missing_panel_executable -> block_before_write
missing_icon_asset -> block_before_write
missing_contract_marker -> block_before_write
receipt_write_failure -> report_failure_without_claiming_install_verified
verification_failure -> report_failure_without_claiming_install_verified
```

Failure must not trigger:

```text
sudo
network_download
homebrew_install
shell_profile_mutation
launchagent_install
keychain_write
tcc_prompt
endpoint_security_activation
system_extension_activation
privileged_helper_install
```

## Reset And Uninstall Sequencing

Future reset/uninstall must use these phases:

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

Reset/uninstall must preserve:

```text
user_logs
user_caches
shell_profiles
Keychain_items
LaunchAgents
Login_Items
Homebrew_files
/Applications
/Library
/System
/usr/local
/opt/homebrew
```

## Verification Commands

The implementation plan is guarded by:

```sh
sh scripts/test-macos-user-local-app-bundle-implementation-plan.sh
```

When a future writer exists, the minimum verification set should include:

```sh
sh scripts/macos-build-platform-probe.sh
sh scripts/macos-dry-run-plan-adapter.sh
sh scripts/test-macos-user-local-app-bundle-contract.sh
sh scripts/test-macos-user-local-app-bundle-implementation-plan.sh
```

Future writer-specific tests must cover:

```text
default dry-run phase rendering
unsafe path blocked before write
unmanaged app bundle preserved
unmanaged CLI wrapper preserved
missing executable blocks before write
missing icon blocks before write
receipt fields complete
verification transcript complete
reset dry-run preserves unmanaged targets
uninstall receipt outside removed prefix
```

## Current Plan Status

```text
macos_user_local_app_bundle_implementation_plan_present=1
macos_app_bundle_writer_present=0
macos_app_bundle_writer_dry_run_present=1
macos_local_candidate_asset_probe_present=1
macos_dry_run_writer_candidate_integration_present=1
macos_commit_gate_contract_present=1
macos_verification_transcript_contract_present=1
macos_app_bundle_created=0
macos_install_verified=0
macos_reset_uninstall_implemented=0
macos_verification_transcript_present=0
application_support_write_performed=0
app_bundle_write_performed=0
cli_wrapper_write_performed=0
host_mutation_performed=0
network_performed=0
```

## Non-Claims

This plan is not macOS installation, macOS app bundle evidence, signed app evidence, notarization evidence, launchd evidence, Keychain evidence, Secure Enclave evidence, sandbox evidence, TCC approval evidence, Endpoint Security evidence, System Extension evidence, Network Extension evidence, privileged helper evidence, malware prevention, ransomware prevention, production readiness, or Apple platform approval.

## Next Recommended Lane

```text
Add a macOS reset/uninstall absence-report contract that defines post-removal verification evidence before any reset/uninstall implementation.
```
