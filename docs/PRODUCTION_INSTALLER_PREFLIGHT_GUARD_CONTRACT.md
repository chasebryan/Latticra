# Production Installer Preflight Guard Contract

Status: no-effect guard contract
Evidence level: 10 target, no-effect preflight guard
Scope: executable preflight guard for future production-installer evaluation without install, uninstall, upgrade, rollback, publish, or host mutation authority.

## Purpose

The production-installer readiness contract requires a preflight guard before any installer can be recommended for general use.

This contract reconciles the existing Fedora host install preflight evidence with the production-installer gate by adding a higher-level no-effect guard.

The guard is executable and deterministic, but it only emits a report.

It does not install, uninstall, upgrade, rollback, publish, sign, fetch from the network, change boot configuration, change services, change SELinux policy, load kernel modules, or mutate host state.

## Guard command

```sh
sh scripts/production-installer-preflight-guard.sh supported-disposable-fedora
sh scripts/production-installer-preflight-guard.sh supported-disposable-fedora fixtures/artifact/local-artifact-manifest.txt plan-preview-present
```

The guard accepts named fixture scenarios:

```text
supported-disposable-fedora
non-fedora-host
immutable-fedora-host
network-required
missing-artifact-manifest
missing-operator-consent
```

## Required prerequisites

The production-installer preflight guard binds these prerequisite records:

```text
fedora_host_install_preflight_prerequisite_present=1
fedora_host_install_preflight_reused=1
local_artifact_manifest_fixture_required=1
local_artifact_manifest_fixture_present=1
artifact_manifest_fixture_path=fixtures/artifact/local-artifact-manifest.txt
```

The Fedora host preflight classifier remains the host-specific input. This guard is the production-installer boundary that joins host classification, artifact manifest evidence, operator consent, target support, and blocked-effect posture.

## Required guard report fields

Every preflight guard report must include:

```text
LATTICRA PRODUCTION INSTALLER PREFLIGHT GUARD
guard_version=1
guard_mode=no-effect-classifier
installer_preflight_guard_present=1
installer_preflight_blocks_unsupported_targets=1
fedora_host_install_preflight_reused=1
artifact_manifest_path=<recorded>
artifact_manifest_present=<0-or-1>
target_supported=<0-or-1>
unsupported_target_blocked=<0-or-1>
operator_consent_present=<0-or-1>
installer_install_plan_preview_present=<0-or-1>
preflight_passed=<0-or-1>
install_candidate=<0-or-1>
install_performed=0
host_mutation_performed=0
network_allowed=0
root_required_to_classify=0
no_effect=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

The standalone supported fixture still reports `preflight_passed=0` unless a no-effect plan preview is bound to the guard.

## Supported target boundary

The only supported fixture target at this stage is:

```text
supported_target_family=fedora-disposable-vm
supported_target_mutable_fedora_only=1
supported_target_local_only=1
supported_target_requires_artifact_manifest=1
supported_target_requires_operator_consent=1
```

This preserves the existing distinction between the bounded disposable-VM CLI payload and production host readiness.

## Blocked scenarios

The preflight guard must block unsupported or incomplete scenarios before any installer authority can be considered:

```text
blocked_target_non_fedora=1
blocked_target_immutable_fedora=1
blocked_target_network_required=1
blocked_target_missing_artifact_manifest=1
blocked_target_missing_operator_consent=1
blocked_target_missing_install_plan_preview=1
```

## Current readiness classification

The current guard posture remains no-effect while the preview lane is present:

```text
installer_preflight_guard_present=1
installer_preflight_blocks_unsupported_targets=1
installer_preflight_guard_no_effect=1
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
sh scripts/test-production-installer-preflight-guard-contract.sh
```

Expected output:

```text
production_installer_preflight_guard_contract: ok
```

## Next implementation lane

```text
Promote fixture-only artifact integrity status to tagged release artifact checksum and signature evidence.
```

That lane should keep the guard no-effect and preserve `production_installer_ready=0`.

## Non-claims

This guard is not a production installer.

It is not an installer artifact, not a release artifact, not artifact signing, not SBOM review, not install validation, not uninstall validation, not upgrade validation, not rollback validation, not multi-VM validation, not Fedora approval, not Fedora distribution readiness, not daily-driver readiness, not immutable Fedora readiness, not security hardening, not malware prevention, not ransomware prevention, and not OS-replacement readiness.
