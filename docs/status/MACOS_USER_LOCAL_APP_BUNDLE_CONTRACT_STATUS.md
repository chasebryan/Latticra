# macOS User-Local App Bundle Contract Status

Status: app bundle contract status
Date: 2026-05-25 CDT
Scope: status checkpoint after adding the macOS user-local app bundle contract.

## Summary

Latticra now has a macOS user-local app bundle contract.

The contract defines exact future app bundle files, Info.plist requirements, Application Support files, CLI wrapper managed markers, receipt requirements, reset/uninstall behavior, and verification transcript requirements before any app bundle writer exists.

This is contract/status work only. It does not create an app bundle, install wrappers, write Application Support files, mutate shell profiles, use launchd, access Keychain, request TCC permissions, use Endpoint Security, use System Extensions, use Network Extensions, open the network, or grant platform authority.

## Status Fields

```text
macos_user_local_app_bundle_contract_present=1
macos_user_local_app_bundle_implementation_plan_present=1
macos_app_bundle_writer_dry_run_present=1
macos_app_bundle_writer_alignment_present=1
macos_app_bundle_exact_files_recorded=1
macos_info_plist_requirements_recorded=1
macos_application_support_files_recorded=1
macos_cli_wrapper_markers_recorded=1
macos_receipt_requirements_recorded=1
macos_reset_uninstall_contract_recorded=1
macos_verification_transcript_requirements_recorded=1
macos_app_bundle_writer_present=0
macos_app_bundle_created=0
macos_install_verified=0
macos_reset_uninstall_implemented=0
macos_verification_transcript_present=0
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
production_installer_ready=0
```

## Public Meaning

The careful public meaning is:

```text
Latticra has a contract for a future managed user-local macOS app bundle lane.
```

That does not mean Latticra has a macOS installer, app bundle, signed build, notarized build, launchd integration, Keychain integration, Endpoint Security integration, System Extension integration, privileged helper, or production security capability.

## Guard Validation

This status record is guarded by:

```sh
sh scripts/test-macos-user-local-app-bundle-contract.sh
```

Expected output:

```text
macos_user_local_app_bundle_contract: ok
```

## Next Recommended Lane

```text
Add a no-effect macOS app bundle writer dry-run prototype that emits the planned phase report, validates unsafe paths, and keeps commit_user_local_managed_artifacts=0.
```

## Non-Claims

This status record is not macOS install evidence, app bundle evidence, signed app evidence, notarization evidence, launchd evidence, Keychain evidence, Secure Enclave evidence, sandbox evidence, TCC approval evidence, Endpoint Security evidence, System Extension evidence, Network Extension evidence, privileged helper evidence, malware prevention, ransomware prevention, production readiness, or Apple platform approval.
