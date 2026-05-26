# macOS README Installer Usage Status

Status: README installer usage alignment status
Date: 2026-05-25 CDT
Scope: status checkpoint after documenting the macOS installer lane in the root README.

## Summary

The root README now documents how to use the current macOS installer lane.

The README section targets macOS infrastructure directly: user-local Application Support, `~/Applications/Latticra Panel.app`, Logs, Caches, Preferences, optional CLI wrappers, app-bundle shape, dry-run commands, local candidate checks, and the closed commit gate. It also states that no macOS app bundle is created, signed, notarized, verified, reset, or uninstalled yet.

## Status Fields

```text
macos_readme_installer_usage_present=1
macos_readme_installer_usage_guard_present=1
macos_installer_targets_macos_infrastructure=1
macos_user_local_paths_documented=1
macos_app_bundle_shape_documented=1
macos_probe_commands_documented=1
macos_candidate_commands_documented=1
macos_commit_gate_command_documented=1
macos_reset_uninstall_dry_run_command_documented=1
macos_reset_uninstall_live_target_classifier_command_documented=1
macos_reset_uninstall_dry_run_planner_command_documented=1
macos_commit_gate_closed_documented=1
macos_reset_uninstall_live_target_classifier_present=1
macos_reset_uninstall_dry_run_planner_present=1
reset_uninstall_dry_run_planner_transcript_present=1
commit_user_local_managed_artifacts=0
macos_app_bundle_commit_capable_writer_present=0
macos_app_bundle_created=0
macos_install_verified=0
app_bundle_write_performed=0
file_delete_performed=0
directory_delete_performed=0
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

## Public Meaning

The careful public meaning is:

```text
The README documents Latticra's current no-effect macOS installer lane and the exact Mac-specific infrastructure it targets.
```

That does not mean Latticra has a macOS installer, commit-capable app bundle writer, app bundle, signed build, notarized build, launchd integration, Keychain integration, Endpoint Security integration, System Extension integration, privileged helper, or production security capability.

## Guard Validation

This status record is guarded by:

```sh
sh scripts/test-macos-readme-installer-usage.sh
```

Expected output:

```text
macos_readme_installer_usage: ok
```

## Next Recommended Lane

```text
Add a macOS reset/uninstall absence-report contract that defines post-removal verification evidence before any reset/uninstall implementation.
```

## Non-Claims

This status record is not macOS install evidence, app bundle evidence, signed app evidence, notarization evidence, launchd evidence, Keychain evidence, Secure Enclave evidence, sandbox evidence, TCC approval evidence, Endpoint Security evidence, System Extension evidence, Network Extension evidence, privileged helper evidence, malware prevention, ransomware prevention, production readiness, Apple platform approval, or runtime authority.
