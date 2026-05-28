# Production Installer SBOM Status Contract

Status: no-effect installer SBOM status contract
Evidence level: 10 target, status evidence only
Scope: SBOM status for future production-installer artifacts without generating an SBOM, building, signing, publishing, installing, uninstalling, upgrading, rollback, network access, or host mutation.

## Purpose

The production-installer readiness contract requires an SBOM before Latticra can claim production installer readiness.

The current local artifact manifest is a fixture and records:

```text
artifact_sbom_path=none
artifact_sbom_recorded=0
```

This contract adds a no-effect status command that binds that missing SBOM evidence to the production-installer blocker ledger while keeping every production readiness claim closed.

The paired SBOM evidence intake validator can check a future SBOM evidence bundle, but it does not accept evidence, attach an SBOM to a release artifact, or open promotion.

## Status command

```sh
sh scripts/production-installer-sbom-status.sh
```

## Required prerequisite records

The installer SBOM status binds these prerequisite records:

```text
local_artifact_manifest_fixture_required=1
local_artifact_manifest_fixture_present=1
production_installer_artifact_integrity_status_present=1
production_installer_release_artifact_promotion_gate_present=1
release_artifact_promotion_gate_passed=0
```

## Required status report fields

Every installer SBOM status report must include:

```text
LATTICRA PRODUCTION INSTALLER SBOM STATUS
status_version=1
status_mode=no-effect-installer-sbom-status
production_installer_sbom_status_present=1
installer_sbom_status_present=1
installer_sbom_review_gate_present=1
installer_sbom_status_no_effect=1
artifact_manifest_sbom_path=none
artifact_manifest_sbom_recorded=0
sbom_artifact_path=<recorded>
sbom_artifact_present=0
sbom_format_declared=0
sbom_component_inventory_present=0
sbom_dependency_reviewed=0
sbom_vulnerability_reviewed=0
sbom_license_reviewed=0
sbom_reviewed=0
sbom_evidence_intake_validator_present=1
sbom_evidence_intake_validation_mode=no-effect-validation
sbom_evidence_candidate_valid=0
sbom_evidence_accepted_by_intake_validator=0
sbom_evidence_written_by_intake_validator=0
installer_sbom_promotion_allowed_by_intake_validator_alone=0
installer_sbom_recorded=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

## Current readiness classification

This slice adds SBOM status evidence only:

```text
production_installer_sbom_status_present=1
installer_sbom_status_present=1
installer_sbom_review_gate_present=1
installer_sbom_status_no_effect=1
sbom_artifact_present=0
sbom_format_declared=0
sbom_component_inventory_present=0
sbom_dependency_reviewed=0
sbom_vulnerability_reviewed=0
sbom_license_reviewed=0
sbom_reviewed=0
sbom_evidence_intake_validator_present=1
sbom_evidence_intake_validation_mode=no-effect-validation
sbom_evidence_candidate_valid=0
sbom_evidence_accepted_by_intake_validator=0
sbom_evidence_written_by_intake_validator=0
installer_sbom_promotion_allowed_by_intake_validator_alone=0
installer_sbom_recorded=0
production_installer_ready=0
```

It does not generate, review, sign, publish, or attach an SBOM to a release artifact.

## Required SBOM promotion evidence

Before any SBOM readiness flag can become `1`, a future lane must provide:

```text
sbom_artifact_present=1
sbom_format_declared=1
sbom_component_inventory_present=1
sbom_dependency_reviewed=1
sbom_vulnerability_reviewed=1
sbom_license_reviewed=1
sbom_reviewed=1
installer_sbom_recorded=1
```

## Guard validation

This contract is guarded by:

```sh
sh scripts/test-production-installer-sbom-status-contract.sh
```

Expected output:

```text
production_installer_sbom_status_contract: ok
```

## Next implementation lane

```text
Generate and review a production-installer SBOM for the tagged release artifact candidate.
```

That lane should preserve `production_installer_ready=0` unless every other production-installer readiness gate is also satisfied.

## Non-claims

This status record is not a production installer.

It is not a generated SBOM, not an SBOM review, not a release artifact, not a release checksum, not a detached artifact signature, not a public signing-key record, not signature verification, not artifact reproducibility evidence, not install validation, not uninstall validation, not upgrade validation, not rollback validation, not multi-VM validation, not Fedora approval, not Fedora distribution readiness, not daily-driver readiness, not immutable Fedora readiness, not security hardening, not malware prevention, not ransomware prevention, and not OS-replacement readiness.
