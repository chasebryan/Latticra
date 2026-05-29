# Production Installer Artifact Integrity Status Contract

Status: no-effect artifact-integrity status contract
Evidence level: 10 target, status evidence only
Scope: checksum and signature status for future production-installer artifacts without building, signing, publishing, installing, uninstalling, upgrading, rollback, network access, or host mutation.

## Purpose

The production-installer readiness contract requires a release artifact checksum, release artifact signature, documented public key, and signature-verification procedure before Latticra can claim production installer readiness.

The current local artifact manifest is a fixture, not a generated release artifact. Its `artifact_sha256` field is intentionally a placeholder and its `artifact_signature` is `none`.

This contract adds a no-effect status command that measures the fixture manifest itself, records the missing release-artifact integrity evidence, and keeps the production readiness claim closed.

## Status command

```sh
sh scripts/production-installer-artifact-integrity-status.sh
```

## Required prerequisite records

The artifact-integrity status binds these prerequisite records:

```text
local_artifact_manifest_fixture_required=1
local_artifact_manifest_fixture_present=1
artifact_manifest_fixture_path=fixtures/artifact/local-artifact-manifest.txt
production_installer_preflight_guard_present=1
installer_install_plan_preview_present=1
```

## Required status report fields

Every artifact-integrity status report must include:

```text
LATTICRA PRODUCTION INSTALLER ARTIFACT INTEGRITY STATUS
status_version=1
status_mode=no-effect-artifact-integrity-review
artifact_integrity_status_present=1
installer_artifact_checksum_status_present=1
installer_artifact_signature_status_present=1
fixture_manifest_sha256_recorded=1
fixture_manifest_sha256=<recorded>
fixture_manifest_artifact_sha256_field=fixture-placeholder-not-release-checksum
fixture_manifest_artifact_signature_field=none
release_artifact_present=0
release_artifact_sha256_recorded=0
release_artifact_signature_present=0
release_artifact_signature_verified=0
installer_artifact_reproducible=0
installer_artifact_checksum_recorded=0
installer_artifact_signature_recorded=0
installer_public_key_documented=0
signature_verification_documented=0
installer_sbom_recorded=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

## Current readiness classification

This slice adds status evidence only:

```text
artifact_integrity_status_present=1
installer_artifact_checksum_status_present=1
installer_artifact_signature_status_present=1
fixture_manifest_sha256_recorded=1
release_artifact_present=0
installer_artifact_reproducible=0
installer_artifact_checksum_recorded=0
installer_artifact_signature_recorded=0
installer_public_key_documented=0
signature_verification_documented=0
production_installer_ready=0
```

It does not close the production-installer checksum or signature gates.

## Required promotion evidence

Before any checksum or signature readiness flag can become `1`, a future lane must provide:

```text
release_artifact_present=1
release_artifact_built_from_tag=1
release_artifact_reproducible=1
release_artifact_sha256_recorded=1
release_artifact_signature_present=1
release_artifact_signature_verified=1
release_public_key_documented=1
signature_verification_documented=1
artifact_integrity_reviewed=1
```

## Guard validation

This contract is guarded by:

```sh
sh scripts/test-production-installer-artifact-integrity-status-contract.sh
```

Expected output:

```text
production_installer_artifact_integrity_status_contract: ok
```

## Next implementation lane

```text
Run the release-artifact promotion gate against a tagged release artifact candidate and collect checksum, signature, public-key, verification, reproducibility, and review evidence.
```

That lane should preserve `production_installer_ready=0` unless every other production-installer readiness gate is also satisfied.

## Non-claims

This status record is not a production installer.

It is not a generated release artifact, not a release checksum, not a detached artifact signature, not a public signing-key record, not signature verification, not artifact reproducibility evidence, not SBOM review, not install validation, not uninstall validation, not upgrade validation, not rollback validation, not multi-VM validation, not Fedora approval, not Fedora distribution readiness, not daily-driver readiness, not immutable Fedora readiness, not security hardening, not malware prevention, not ransomware prevention, and not OS-replacement readiness.
