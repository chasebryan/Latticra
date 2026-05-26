# macOS Local Candidate Asset Probe Status

Status: no-effect local candidate asset probe status
Date: 2026-05-25 CDT
Scope: status checkpoint after adding the macOS local Panel executable and icon candidate asset probe.

## Summary

Latticra now has a no-effect macOS local candidate asset probe.

The probe checks caller-supplied local Panel executable and icon candidates for dry-run writer input readiness. It is now linked to the macOS dry-run writer candidate integration and closed macOS commit gate contract, which compare the probe decision with the writer dry-run decision while keeping all writes disabled. The probe reports missing files, disallowed paths, non-executable Panel candidates, unsupported icon formats, and ready dry-run inputs without building, downloading, signing, notarizing, copying, writing app bundle files, mutating the host, or granting authority.

## Status Fields

```text
macos_local_candidate_asset_probe_present=1
macos_local_candidate_asset_probe_guard_present=1
macos_dry_run_writer_candidate_integration_present=1
macos_commit_gate_contract_present=1
macos_verification_transcript_contract_present=1
local_panel_executable_candidate_probe=1
local_icon_candidate_probe=1
panel_candidate_executable_check_present=1
panel_candidate_readable_check_present=1
icon_candidate_format_check_present=1
icon_candidate_readable_check_present=1
asset_probe_ready_decision_present=1
build_performed=0
panel_build_performed=0
icon_conversion_performed=0
download_performed=0
copy_performed=0
signing_performed=0
notarization_performed=0
app_bundle_write_performed=0
info_plist_write_performed=0
app_executable_write_performed=0
app_icon_write_performed=0
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

## Public Meaning

The careful public meaning is:

```text
Latticra can report whether caller-supplied local Panel executable and icon candidates are usable dry-run inputs.
```

That does not mean Latticra has a macOS installer, commit-capable app bundle writer, app bundle, signed build, notarized build, launchd integration, Keychain integration, Endpoint Security integration, System Extension integration, privileged helper, or production security capability.

## Guard Validation

This status record is guarded by:

```sh
sh scripts/test-macos-local-candidate-asset-probe.sh
```

Expected output:

```text
macos_local_candidate_asset_probe: ok
```

## Next Recommended Lane

```text
Add a macOS reset/uninstall live-implementation plan contract that maps future effect-authorized execution phases while deletion remains disabled.
```

## Non-Claims

This status record is not macOS install evidence, app bundle evidence, signed app evidence, notarization evidence, launchd evidence, Keychain evidence, Secure Enclave evidence, sandbox evidence, TCC approval evidence, Endpoint Security evidence, System Extension evidence, Network Extension evidence, privileged helper evidence, malware prevention, ransomware prevention, production readiness, Apple platform approval, or runtime authority.
