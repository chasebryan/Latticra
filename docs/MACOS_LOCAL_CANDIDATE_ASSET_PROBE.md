# macOS Local Candidate Asset Probe

Status: no-effect macOS local candidate asset probe
Date: 2026-05-25 CDT
Scope: local Panel executable and icon candidate checks before any macOS app bundle writer can become commit-capable.

## Purpose

This probe checks caller-supplied local asset candidates for the macOS app bundle dry-run lane.

It follows the writer alignment requirement:

```text
local_panel_executable_candidate_probe=1
local_icon_candidate_probe=1
```

The probe does not build, download, sign, notarize, copy, write app bundle files, mutate host state, open the network, or grant authority.

The macOS dry-run writer candidate integration consumes this probe's ready decision and compares it with the app bundle writer dry-run decision. The integration remains no-effect and keeps `commit_user_local_managed_artifacts=0`. The macOS commit gate contract then keeps the writer path closed until future implementation and verification evidence exist.

## Command

```sh
sh scripts/macos-local-candidate-asset-probe.sh --panel-executable <file> --icon <file>
```

The command writes only a deterministic report to stdout.

## Report Fields

The default report includes:

```text
MACOS LOCAL CANDIDATE ASSET PROBE
probe_status=ok
probe_mode=macos-local-candidate-asset-probe
panel_executable_candidate=<path-or-none>
panel_candidate_supplied=<0-or-1>
panel_candidate_path_status=<allowed-or-blocked>
panel_candidate_present=<0-or-1>
panel_candidate_file=<0-or-1>
panel_candidate_executable=<0-or-1>
panel_candidate_readable=<0-or-1>
panel_executable_candidate_supplied=<0-or-1>
panel_executable_candidate_path_status=<allowed-or-blocked>
panel_executable_candidate_present=<0-or-1>
panel_executable_candidate_file=<0-or-1>
panel_executable_candidate_executable=<0-or-1>
panel_executable_candidate_readable=<0-or-1>
icon_candidate=<path-or-none>
icon_candidate_supplied=<0-or-1>
icon_candidate_path_status=<allowed-or-blocked>
icon_candidate_present=<0-or-1>
icon_candidate_file=<0-or-1>
icon_candidate_readable=<0-or-1>
icon_candidate_format=<icns-png-svg-ico-or-none>
icon_candidate_supported_format=<0-or-1>
icon_candidate_icns_ready=<0-or-1>
local_panel_executable_candidate_probe=1
local_icon_candidate_probe=1
asset_probe_decision=<decision>
```

## Decisions

The probe may report:

```text
blocked-missing-panel-executable-candidate
blocked-disallowed-panel-candidate-path
blocked-panel-candidate-not-file
blocked-panel-candidate-not-executable
blocked-panel-candidate-not-readable
blocked-missing-icon-candidate
blocked-disallowed-icon-candidate-path
blocked-icon-candidate-not-file
blocked-icon-candidate-not-readable
blocked-unsupported-icon-candidate
ready-for-dry-run-writer-inputs
```

`ready-for-dry-run-writer-inputs` means only that the supplied local files are usable as inputs to the dry-run writer report. It is not app bundle evidence, install evidence, signing evidence, notarization evidence, or verification-transcript evidence.

## Authority Boundary

The probe preserves:

```text
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

## Validation

This probe is guarded by:

```sh
sh scripts/test-macos-local-candidate-asset-probe.sh
```

Expected output:

```text
macos_local_candidate_asset_probe: ok
```

The bridge to the writer dry-run is guarded by:

```sh
sh scripts/test-macos-dry-run-writer-candidate-integration.sh
```

## Non-Claims

This probe is not macOS installation, macOS app bundle evidence, signed app evidence, notarization evidence, launchd evidence, Keychain evidence, Secure Enclave evidence, sandbox evidence, TCC approval evidence, Endpoint Security evidence, System Extension evidence, Network Extension evidence, privileged helper evidence, malware prevention, ransomware prevention, production readiness, Apple platform approval, or runtime authority.

## Next Recommended Lane

```text
Add a macOS verification transcript contract that defines exact post-write evidence before any user-local install can be called verified.
```
