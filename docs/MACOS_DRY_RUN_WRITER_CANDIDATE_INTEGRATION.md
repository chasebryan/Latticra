# macOS Dry-Run Writer Candidate Integration

Status: no-effect macOS dry-run writer candidate integration
Date: 2026-05-25 CDT
Scope: bridge the local candidate asset probe to the macOS app bundle writer dry-run without enabling writes.

## Purpose

This integration runs the macOS local candidate asset probe and the app bundle writer dry-run with the same caller-supplied Panel executable and icon inputs.

It records whether:

```text
asset_probe_decision=ready-for-dry-run-writer-inputs
writer_dry_run_decision=ready-for-future-commit-gate
commit_user_local_managed_artifacts=0
```

Only when all three stay true does the integration report:

```text
integration_decision=ready-for-future-commit-gate-no-effect
```

That result is still not a real commit gate opening. It means the no-effect checks agree that the supplied local candidates can be carried to the macOS commit gate contract, which remains closed. The macOS verification transcript contract defines the future evidence required after writes, but no transcript evidence exists yet.

## Command

```sh
sh scripts/macos-dry-run-writer-candidate-integration.sh \
  --panel-executable <local-executable> \
  --icon <local-icon-file>
```

The command writes only a deterministic report to stdout.

## Report Fields

The report starts with:

```text
MACOS DRY RUN WRITER CANDIDATE INTEGRATION
integration_status=ok
integration_mode=macos-dry-run-writer-candidate-integration
```

It must include:

```text
asset_probe_script=<repo>/scripts/macos-local-candidate-asset-probe.sh
writer_dry_run_script=<repo>/scripts/macos-app-bundle-writer-dry-run.sh
asset_probe_decision=<decision>
writer_dry_run_decision=<decision>
writer_phase_5_status=<status>
asset_probe_ready=<0-or-1>
writer_dry_run_ready=<0-or-1>
authority_boundary_preserved=<0-or-1>
candidate_flow_ready=<0-or-1>
integration_decision=<decision>
commit_user_local_managed_artifacts=0
app_bundle_write_performed=0
host_mutation_performed=0
network_performed=0
```

## Decisions

The integration may report:

```text
blocked-asset-probe-not-ready
blocked-writer-dry-run-not-ready
blocked-authority-boundary-widened
ready-for-future-commit-gate-no-effect
```

If the writer dry-run would otherwise accept an icon file that the local candidate asset probe rejects, the integration remains blocked by the probe:

```text
asset_probe_decision=blocked-unsupported-icon-candidate
integration_decision=blocked-asset-probe-not-ready
```

## Authority Boundary

The integration preserves:

```text
build_performed=0
download_performed=0
copy_performed=0
signing_performed=0
notarization_performed=0
commit_user_local_managed_artifacts=0
app_bundle_write_performed=0
info_plist_write_performed=0
app_executable_write_performed=0
app_icon_write_performed=0
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

## Validation

This integration is guarded by:

```sh
sh scripts/test-macos-dry-run-writer-candidate-integration.sh
```

Expected output:

```text
macos_dry_run_writer_candidate_integration: ok
```

## Non-Claims

This integration is not macOS installation, macOS app bundle evidence, signed app evidence, notarization evidence, launchd evidence, Keychain evidence, Secure Enclave evidence, sandbox evidence, TCC approval evidence, Endpoint Security evidence, System Extension evidence, Network Extension evidence, privileged helper evidence, malware prevention, ransomware prevention, production readiness, Apple platform approval, or runtime authority.

## Previous Recommended Lane

```text
Add a macOS reset/uninstall evidence-bundle contract that groups implementation-gate, operator-intent, receipt, absence, planner, and classifier evidence before any live execution.
```

## Next Recommended Lane

```text
Add a macOS reset/uninstall live-runner acceptance-denial transcript contract that records the closed acceptance gate without dispatching effects.
```
