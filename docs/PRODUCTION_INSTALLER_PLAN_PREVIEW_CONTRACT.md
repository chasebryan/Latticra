# Production Installer Plan Preview Contract

Status: no-effect plan-preview contract
Evidence level: 10 target, no-effect plan preview
Scope: preview-only install plan rendering for future production-installer evaluation without install, uninstall, upgrade, rollback, publish, signing, network, or host mutation authority.

## Purpose

The production-installer readiness contract requires an install-plan preview before any installer can be recommended for general use.

This contract adds a deterministic preview renderer that is bound to the production-installer preflight guard.

The renderer emits the intended review plan for the current local no-effect CLI payload and keeps every effect closed.

It does not install, uninstall, upgrade, rollback, publish, sign, fetch from the network, change boot configuration, change services, change SELinux policy, load kernel modules, write receipts, or mutate host state.

## Preview command

```sh
sh scripts/production-installer-plan-preview.sh supported-disposable-fedora
```

The renderer accepts the same fixture scenarios as the preflight guard:

```text
supported-disposable-fedora
non-fedora-host
immutable-fedora-host
network-required
missing-artifact-manifest
missing-operator-consent
```

## Required prerequisites

The preview renderer binds these prerequisite records:

```text
production_installer_preflight_guard_required=1
production_installer_preflight_guard_present=1
local_artifact_manifest_fixture_required=1
local_artifact_manifest_fixture_present=1
artifact_manifest_fixture_path=fixtures/artifact/local-artifact-manifest.txt
```

## Required preview report fields

Every preview report must include:

```text
LATTICRA PRODUCTION INSTALLER PLAN PREVIEW
plan_preview_version=1
plan_preview_mode=no-effect-renderer
installer_install_plan_preview_present=1
installer_install_plan_preview_no_effect=1
preflight_guard_required=1
preflight_guard_passed=<0-or-1>
preview_decision=<recorded>
plan_entries_rendered=<count>
artifact_manifest_path=<recorded>
planned_payload_entry=/usr/bin/latticra
planned_payload_entry=/usr/share/doc/latticra/README.md
install_performed=0
host_mutation_performed=0
network_allowed=0
receipt_written=0
root_required_to_preview=0
no_effect=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

## Previewed no-effect actions

The supported disposable-Fedora fixture renders these no-effect review entries:

```text
plan_entry=verify-artifact-manifest
plan_entry=validate-no-network-requirement
plan_entry=validate-operator-consent
plan_entry=review-cli-payload-placement
plan_entry=preserve-no-service-boot-kernel-selinux-effects
plan_entry=record-install-transcript-requirement
```

These entries are review intent only. They do not write files or prepare a commit-capable installer.

## Blocked preview scenarios

The renderer must refuse to render an install plan when preflight blocks:

```text
preview_blocks_non_fedora=1
preview_blocks_immutable_fedora=1
preview_blocks_network_required=1
preview_blocks_missing_artifact_manifest=1
preview_blocks_missing_operator_consent=1
```

## Current readiness classification

This slice closes the preview-presence gap only:

```text
installer_preflight_guard_present=1
installer_preflight_blocks_unsupported_targets=1
installer_install_plan_preview_present=1
installer_install_plan_preview_no_effect=1
installer_install_transcript_recorded=0
installer_uninstall_transcript_recorded=0
installer_upgrade_path_validated=0
installer_rollback_path_validated=0
installer_multi_vm_validation_completed=0
production_installer_ready=0
```

## Guard validation

This contract is guarded by:

```sh
sh scripts/test-production-installer-plan-preview-contract.sh
```

Expected output:

```text
production_installer_plan_preview_contract: ok
```

## Next implementation lane

```text
Promote fixture-only artifact integrity status to tagged release artifact checksum and signature evidence.
```

That lane should keep the preview no-effect and preserve `production_installer_ready=0`.

## Non-claims

This preview is not a production installer.

It is not an installer artifact, not a release artifact, not artifact signing, not checksum validation, not SBOM review, not install validation, not uninstall validation, not upgrade validation, not rollback validation, not multi-VM validation, not Fedora approval, not Fedora distribution readiness, not daily-driver readiness, not immutable Fedora readiness, not security hardening, not malware prevention, not ransomware prevention, and not OS-replacement readiness.
