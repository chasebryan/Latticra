# Production Installer Release Artifact Promotion Gate Contract

Status: no-effect release-artifact promotion gate contract
Evidence level: 10 target, promotion gate only
Scope: promotion gate for future tagged production-installer artifacts without building, signing, publishing, installing, uninstalling, upgrading, rollback, network access, or host mutation.

## Purpose

The production-installer artifact integrity status records that the current local artifact manifest is a fixture and that no release artifact checksum or signature evidence exists.

This contract adds the next gate: a no-effect promotion decision for a future tagged release artifact.

The gate must refuse promotion until a release artifact, tag binding, reproducible build evidence, checksum, signature, public-key record, signature-verification procedure, and artifact-integrity review all exist.

## Gate command

```sh
sh scripts/production-installer-release-artifact-promotion-gate.sh
```

## Required prerequisite records

The release-artifact promotion gate binds these prerequisite records:

```text
production_installer_artifact_integrity_status_required=1
artifact_integrity_status_present=1
installer_artifact_checksum_status_present=1
installer_artifact_signature_status_present=1
local_artifact_manifest_fixture_present=1
production_installer_preflight_guard_present=1
installer_install_plan_preview_present=1
release_artifact_candidate_preflight_present=1
release_artifact_candidate_preflight_passed=0
release_artifact_candidate_inputs_satisfied=0
```

## Required gate report fields

Every release-artifact promotion report must include:

```text
LATTICRA PRODUCTION INSTALLER RELEASE ARTIFACT PROMOTION GATE
gate_version=1
gate_mode=no-effect-release-artifact-promotion
release_artifact_promotion_gate_present=1
release_artifact_promotion_gate_no_effect=1
release_artifact_promotion_gate_passed=0
release_artifact_promotion_gate_decision=blocked-missing-tagged-release-artifact
release_artifact_candidate_preflight_present=1
release_artifact_candidate_preflight_passed=0
release_artifact_candidate_inputs_satisfied=0
release_artifact_path=<recorded>
release_artifact_present=0
release_artifact_built_from_tag=0
release_artifact_reproducible=0
release_artifact_sha256_recorded=0
release_artifact_signature_present=0
release_artifact_signature_verified=0
release_public_key_documented=0
signature_verification_documented=0
artifact_integrity_reviewed=0
installer_artifact_reproducible=0
installer_artifact_checksum_recorded=0
installer_artifact_signature_recorded=0
installer_public_key_documented=0
production_installer_ready=0
```

## Current readiness classification

This slice adds a promotion gate only:

```text
release_artifact_promotion_gate_present=1
release_artifact_promotion_gate_no_effect=1
release_artifact_promotion_gate_passed=0
release_artifact_promotion_gate_decision=blocked-missing-tagged-release-artifact
release_artifact_candidate_preflight_present=1
release_artifact_candidate_preflight_passed=0
release_artifact_candidate_inputs_satisfied=0
release_artifact_present=0
release_artifact_built_from_tag=0
release_artifact_reproducible=0
release_artifact_sha256_recorded=0
release_artifact_signature_present=0
release_artifact_signature_verified=0
production_installer_ready=0
```

It does not create, build, sign, publish, or verify a release artifact.

## Promotion pass requirements

The gate may pass only when all of these fields are true in a future reviewed evidence bundle:

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
sh scripts/test-production-installer-release-artifact-promotion-gate-contract.sh
```

Expected output:

```text
production_installer_release_artifact_promotion_gate_contract: ok
```

## Next implementation lane

```text
Satisfy the release-artifact candidate preflight before creating a tagged release artifact candidate and collecting checksum, signature, public-key, verification, reproducibility, and review evidence.
```

That lane should preserve `production_installer_ready=0` unless every other production-installer readiness gate is also satisfied.

## Non-claims

This gate is not a production installer.

It is not a generated release artifact, not a release checksum, not a detached artifact signature, not a public signing-key record, not signature verification, not artifact reproducibility evidence, not SBOM review, not install validation, not uninstall validation, not upgrade validation, not rollback validation, not multi-VM validation, not Fedora approval, not Fedora distribution readiness, not daily-driver readiness, not immutable Fedora readiness, not security hardening, not malware prevention, not ransomware prevention, and not OS-replacement readiness.
