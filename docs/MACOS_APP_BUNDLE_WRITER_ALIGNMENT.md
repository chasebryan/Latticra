# macOS App Bundle Writer Alignment

Status: macOS app bundle writer contract/status alignment
Date: 2026-05-25 CDT
Scope: align public and status meaning after the no-effect macOS app bundle writer dry-run prototype.

## Purpose

This alignment separates the current no-effect writer-shaped dry-run prototype from any future commit-capable macOS app bundle writer.

The current prototype can render phases, validate user-local paths, inspect existing managed markers, report missing local executable/icon candidates, and block unsafe paths. It cannot create an app bundle, write Application Support files, install wrappers, write receipts, mutate shell profiles, or verify a real install.

The macOS local candidate asset probe remains a no-effect readiness check for caller-supplied Panel executable and icon candidates.

## Current Capability

```text
macos_app_bundle_writer_dry_run_present=1
macos_app_bundle_writer_phase_report_present=1
macos_app_bundle_writer_path_guard_present=1
macos_app_bundle_writer_marker_inspection_present=1
macos_app_bundle_writer_missing_candidate_detection_present=1
macos_app_bundle_writer_commit_disabled=1
```

The current command is:

```sh
sh scripts/macos-app-bundle-writer-dry-run.sh
```

The current expected authority posture is:

```text
phase_report_only=1
commit_user_local_managed_artifacts=0
application_support_write_performed=0
app_bundle_write_performed=0
cli_wrapper_write_performed=0
host_mutation_performed=0
network_performed=0
```

## Explicit Non-Capability

The following must remain false until a separate commit-capable writer contract, implementation, reset/uninstall implementation, and verification evidence exist:

```text
macos_app_bundle_writer_present=0
macos_app_bundle_commit_capable_writer_present=0
macos_app_bundle_created=0
macos_install_verified=0
macos_reset_uninstall_implemented=0
macos_verification_transcript_present=0
```

The dry-run writer must not be described as:

```text
macOS installer
app bundle installer
commit-capable writer
user-local install evidence
app bundle evidence
signed build evidence
notarized build evidence
production installer
security product
```

## Future Commit Gate Requirements

Before any commit-capable writer exists, a future lane must add all of:

```text
local_panel_executable_candidate_probe=1
local_icon_candidate_probe=1
commit_gate_contract=1
reset_uninstall_implementation_plan=1
verification_transcript_contract=1
unsafe_path_negative_tests=1
unmanaged_target_preservation_tests=1
receipt_completeness_tests=1
```

Even then, commit behavior must remain disabled until a separate implementation explicitly changes:

```text
commit_user_local_managed_artifacts=1
```

## Safe Public Wording

A careful public statement is:

```text
Latticra has a no-effect macOS app bundle writer dry-run prototype that renders future writer phases and blocks unsafe paths while keeping all writes disabled.
```

That statement must not be shortened to "Latticra has a macOS app bundle writer" unless the sentence also says "dry-run" and "no-effect."

## Validation

This alignment is guarded by:

```sh
sh scripts/test-macos-app-bundle-writer-alignment.sh
```

Expected output:

```text
macos_app_bundle_writer_alignment: ok
```

## Non-Claims

This alignment is not macOS installation, macOS app bundle evidence, signed app evidence, notarization evidence, launchd evidence, Keychain evidence, Secure Enclave evidence, sandbox evidence, TCC approval evidence, Endpoint Security evidence, System Extension evidence, Network Extension evidence, privileged helper evidence, malware prevention, ransomware prevention, production readiness, or Apple platform approval.

## Next Recommended Lane

```text
Add no-effect integration between the local candidate asset probe and the app bundle writer dry-run so supplied candidates can move the dry-run decision to ready-for-future-commit-gate while still keeping commit_user_local_managed_artifacts=0.
```
