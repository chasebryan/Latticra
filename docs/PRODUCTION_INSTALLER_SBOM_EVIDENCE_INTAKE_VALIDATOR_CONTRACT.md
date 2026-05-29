# Production Installer SBOM Evidence Intake Validator Contract

Status: no-effect SBOM evidence intake validator contract
Evidence level: 10 target, evidence intake validator only
Scope: validate a future production-installer SBOM evidence bundle without generating, accepting, publishing, attaching, promoting, installing, or mutating a host.

## Purpose

The production-installer SBOM status is present and blocked because no generated and reviewed SBOM evidence exists for a tagged release artifact candidate.

This contract adds a no-effect intake validator for the future SBOM evidence bundle. The paired template prints the expected bundle shape, and the validator checks local SBOM shape markers, dependency-review evidence, vulnerability-review evidence, license-review evidence, final SBOM-review evidence, and hash consistency between the supplied files and the evidence manifest.

It does not accept the evidence, write status, attach an SBOM to a release artifact, pass the release-artifact promotion gate, or claim production installer readiness.

## Command

```sh
sh scripts/production-installer-sbom-evidence-intake.sh \
  --sbom <path> \
  --dependency-review <path> \
  --vulnerability-review <path> \
  --license-review <path> \
  --review <path> \
  --evidence <path>
```

## Current classification

```text
sbom_evidence_intake_validator_present=1
sbom_evidence_intake_validation_mode=no-effect-validation
sbom_evidence_template_present=1
sbom_evidence_template_complete=0
sbom_evidence_candidate_valid=0
sbom_artifact_file_present=0
sbom_artifact_sha256_recorded=0
sbom_dependency_review_present=0
sbom_vulnerability_review_present=0
sbom_license_review_present=0
sbom_review_present=0
sbom_evidence_accepted_by_intake_validator=0
sbom_evidence_written_by_intake_validator=0
installer_sbom_promotion_allowed_by_intake_validator_alone=0
release_artifact_promotion_gate_passed=0
installer_sbom_recorded=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
host_mutation_performed=0
```

## Required source records

The validator binds the current blocked SBOM posture:

```text
production_installer_ready=0
release_artifact_promotion_gate_passed=0
production_installer_sbom_status_present=1
installer_sbom_status_present=1
installer_sbom_recorded=0
```

It reads these local records:

```text
docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
docs/PRODUCTION_INSTALLER_SBOM_STATUS_CONTRACT.md
docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_PROMOTION_GATE_CONTRACT.md
docs/PRODUCTION_INSTALLER_SBOM_EVIDENCE_TEMPLATE_CONTRACT.md
docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
scripts/production-installer-sbom-status.sh
README.md
```

## Candidate requirements

A candidate evidence bundle must include all of the following, and the hash fields must match the supplied local files:

```text
LATTICRA PRODUCTION INSTALLER SBOM EVIDENCE
sbom_evidence_status=complete
sbom_artifact_present=1
sbom_format_declared=1
sbom_format=spdx-json
sbom_component_inventory_present=1
sbom_dependency_reviewed=1
sbom_vulnerability_reviewed=1
sbom_license_reviewed=1
sbom_reviewed=1
installer_sbom_recorded=1
sbom_artifact_sha256=<actual-sbom-sha256>
sbom_dependency_review_sha256=<actual-dependency-review-sha256>
sbom_vulnerability_review_sha256=<actual-vulnerability-review-sha256>
sbom_license_review_sha256=<actual-license-review-sha256>
sbom_review_sha256=<actual-sbom-review-sha256>
release_artifact_promotion_gate_passed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
host_mutation_performed=0
```

The validator accepts SPDX JSON or CycloneDX JSON shape markers. The candidate must not contain placeholder values.

The candidate must not claim SBOM evidence acceptance, installer SBOM promotion, release-artifact promotion, production installer readiness, Fedora distribution readiness, Fedora approval, daily-driver readiness, immutable Fedora readiness, or host mutation.

## Validator output

For a valid candidate, the no-effect validator prints:

```text
LATTICRA PRODUCTION INSTALLER SBOM EVIDENCE INTAKE VALIDATION
intake_validation_status=ok
sbom_evidence_intake_validator_present=1
sbom_evidence_intake_validation_mode=no-effect-validation
sbom_evidence_candidate_valid=1
sbom_artifact_file_present=1
sbom_artifact_sha256_recorded=1
candidate_sbom_format=<detected>
candidate_sbom_format_declared=1
candidate_sbom_component_inventory_present=1
candidate_sbom_dependency_reviewed=1
candidate_sbom_vulnerability_reviewed=1
candidate_sbom_license_reviewed=1
candidate_sbom_reviewed=1
candidate_installer_sbom_recorded=1
sbom_evidence_accepted_by_intake_validator=0
sbom_evidence_written_by_intake_validator=0
installer_sbom_promotion_allowed_by_intake_validator_alone=0
release_artifact_promotion_gate_passed=0
installer_sbom_recorded=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
host_mutation_performed=0
```

## Guard validation

This contract is guarded by:

```sh
sh scripts/test-production-installer-sbom-evidence-intake-validator-contract.sh
```

Expected output:

```text
production_installer_sbom_evidence_intake_validator_contract: ok
```

## Next implementation lane

```text
Generate a production-installer SBOM for a tagged release artifact candidate, review dependency, vulnerability, and license evidence, then validate the bundle with the SBOM evidence intake validator before any promotion review.
```

Production readiness must remain closed until every other production-installer readiness gate is also satisfied.

## Non-claims

This validator is not a production installer.

It is not a generated SBOM, not SBOM acceptance, not artifact signing, not artifact publication, not artifact promotion, not install validation, not uninstall validation, not upgrade validation, not rollback validation, not multi-VM validation, not Fedora approval, not Fedora distribution readiness, not daily-driver readiness, not immutable Fedora readiness, not security hardening, not malware prevention, not ransomware prevention, and not OS-replacement readiness.
