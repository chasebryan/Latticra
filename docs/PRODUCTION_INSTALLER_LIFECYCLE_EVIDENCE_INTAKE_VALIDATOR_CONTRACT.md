# Production Installer Lifecycle Evidence Intake Validator Contract

Status: no-effect lifecycle evidence intake validator contract
Evidence level: 10 target, evidence intake validator only
Scope: validate a future production-installer lifecycle validation evidence bundle without upgrading, rolling back, reinstalling, invoking a package manager, accepting evidence, passing promotion, or mutating a host.

## Purpose

The production-installer lifecycle validation status is present and blocked because no reviewed production-installer upgrade, rollback, or reinstall idempotence transcript evidence exists for a tagged release artifact candidate.

This contract adds a no-effect intake validator for that future lifecycle evidence bundle. The validator checks local lifecycle transcript markers, upgrade-review evidence, rollback-review evidence, reinstall-review evidence, and hash consistency between the supplied files and the evidence manifest.

It does not accept the evidence, write status, pass the release-artifact promotion gate, or claim production installer readiness.

## Command

```sh
sh scripts/production-installer-lifecycle-evidence-intake.sh \
  --upgrade <path> \
  --rollback <path> \
  --reinstall <path> \
  --upgrade-review <path> \
  --rollback-review <path> \
  --reinstall-review <path> \
  --evidence <path>
```

## Current classification

```text
lifecycle_evidence_intake_validator_present=1
lifecycle_evidence_intake_validation_mode=no-effect-validation
lifecycle_evidence_candidate_valid=0
upgrade_transcript_file_present=0
rollback_transcript_file_present=0
reinstall_transcript_file_present=0
upgrade_transcript_sha256_recorded=0
rollback_transcript_sha256_recorded=0
reinstall_transcript_sha256_recorded=0
upgrade_transcript_review_present=0
rollback_transcript_review_present=0
reinstall_transcript_review_present=0
lifecycle_evidence_accepted_by_intake_validator=0
lifecycle_evidence_written_by_intake_validator=0
installer_lifecycle_promotion_allowed_by_intake_validator_alone=0
release_artifact_promotion_gate_passed=0
installer_upgrade_path_validated=0
installer_rollback_path_validated=0
installer_downgrade_or_rollback_path_validated=0
installer_reinstall_idempotence_validated=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
host_mutation_performed=0
```

## Required source records

The validator binds the current blocked lifecycle posture:

```text
production_installer_ready=0
release_artifact_promotion_gate_passed=0
production_installer_lifecycle_validation_status_present=1
installer_lifecycle_validation_status_no_effect=1
installer_upgrade_path_validated=0
installer_rollback_path_validated=0
installer_downgrade_or_rollback_path_validated=0
installer_reinstall_idempotence_validated=0
```

It reads these local records:

```text
docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
docs/PRODUCTION_INSTALLER_LIFECYCLE_VALIDATION_STATUS_CONTRACT.md
docs/PRODUCTION_INSTALLER_TRANSCRIPT_STATUS_CONTRACT.md
docs/PRODUCTION_INSTALLER_TRANSCRIPT_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md
docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_PROMOTION_GATE_CONTRACT.md
docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
scripts/production-installer-lifecycle-validation-status.sh
README.md
```

## Candidate requirements

A candidate evidence bundle must include all of the following, and the hash fields must match the supplied local files:

```text
LATTICRA PRODUCTION INSTALLER LIFECYCLE EVIDENCE
lifecycle_evidence_status=complete
production_installer_lifecycle_validation_performed=1
installer_upgrade_candidate_present=1
installer_rollback_candidate_present=1
installer_reinstall_candidate_present=1
upgrade_transcript_present=1
rollback_transcript_present=1
reinstall_transcript_present=1
upgrade_transcript_reviewed=1
rollback_transcript_reviewed=1
reinstall_transcript_reviewed=1
installer_upgrade_path_validated=1
installer_rollback_path_validated=1
installer_downgrade_or_rollback_path_validated=1
installer_reinstall_idempotence_validated=1
upgrade_transcript_sha256=<actual-upgrade-transcript-sha256>
rollback_transcript_sha256=<actual-rollback-transcript-sha256>
reinstall_transcript_sha256=<actual-reinstall-transcript-sha256>
upgrade_transcript_review_sha256=<actual-upgrade-review-sha256>
rollback_transcript_review_sha256=<actual-rollback-review-sha256>
reinstall_transcript_review_sha256=<actual-reinstall-review-sha256>
upgrade_performed=0
rollback_performed=0
reinstall_performed=0
package_manager_invoked=0
release_artifact_promotion_gate_passed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
host_mutation_performed=0
network_allowed=0
```

The upgrade transcript must identify itself as `LATTICRA PRODUCTION INSTALLER LIFECYCLE DRY RUN UPGRADE TRANSCRIPT`.

The rollback transcript must identify itself as `LATTICRA PRODUCTION INSTALLER LIFECYCLE DRY RUN ROLLBACK TRANSCRIPT`.

The reinstall transcript must identify itself as `LATTICRA PRODUCTION INSTALLER LIFECYCLE DRY RUN REINSTALL TRANSCRIPT`.

The candidate must not contain placeholder values.

The candidate must not claim lifecycle evidence acceptance, lifecycle promotion, release-artifact promotion, production installer readiness, Fedora distribution readiness, Fedora approval, daily-driver readiness, immutable Fedora readiness, package-manager invocation, upgrade execution, rollback execution, reinstall execution, network access, or host mutation.

## Validator output

For a valid candidate, the no-effect validator prints:

```text
LATTICRA PRODUCTION INSTALLER LIFECYCLE EVIDENCE INTAKE VALIDATION
intake_validation_status=ok
lifecycle_evidence_intake_validator_present=1
lifecycle_evidence_intake_validation_mode=no-effect-validation
lifecycle_evidence_candidate_valid=1
upgrade_transcript_file_present=1
rollback_transcript_file_present=1
reinstall_transcript_file_present=1
upgrade_transcript_sha256_recorded=1
rollback_transcript_sha256_recorded=1
reinstall_transcript_sha256_recorded=1
candidate_production_installer_lifecycle_validation_performed=1
candidate_upgrade_transcript_reviewed=1
candidate_rollback_transcript_reviewed=1
candidate_reinstall_transcript_reviewed=1
candidate_installer_upgrade_path_validated=1
candidate_installer_rollback_path_validated=1
candidate_installer_downgrade_or_rollback_path_validated=1
candidate_installer_reinstall_idempotence_validated=1
lifecycle_evidence_accepted_by_intake_validator=0
lifecycle_evidence_written_by_intake_validator=0
installer_lifecycle_promotion_allowed_by_intake_validator_alone=0
release_artifact_promotion_gate_passed=0
installer_upgrade_path_validated=0
installer_rollback_path_validated=0
installer_downgrade_or_rollback_path_validated=0
installer_reinstall_idempotence_validated=0
upgrade_performed=0
rollback_performed=0
reinstall_performed=0
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
```

## Guard validation

This contract is guarded by:

```sh
sh scripts/test-production-installer-lifecycle-evidence-intake-validator-contract.sh
```

Expected output:

```text
production_installer_lifecycle_evidence_intake_validator_contract: ok
```

## Next implementation lane

```text
Run disposable Fedora VM production-installer lifecycle validation, review upgrade, rollback, and reinstall idempotence transcript evidence, then validate the bundle with the lifecycle evidence intake validator before any promotion review.
```

Production readiness must remain closed until every other production-installer readiness gate is also satisfied.

## Non-claims

This validator is not a production installer.

It is not upgrade evidence acceptance, not rollback evidence acceptance, not reinstall evidence acceptance, not package-manager execution, not host mutation, not release artifact evidence, not SBOM review, not artifact promotion, not install evidence, not uninstall evidence, not multi-VM validation, not Fedora approval, not Fedora distribution readiness, not daily-driver readiness, not immutable Fedora readiness, not security hardening, not malware prevention, not ransomware prevention, and not OS-replacement readiness.
