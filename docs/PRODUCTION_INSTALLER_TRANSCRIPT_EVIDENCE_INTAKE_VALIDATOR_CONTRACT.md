# Production Installer Transcript Evidence Intake Validator Contract

Status: no-effect transcript evidence intake validator contract
Evidence level: 10 target, evidence intake validator only
Scope: validate a future production-installer dry-run transcript evidence bundle without installing, uninstalling, invoking a package manager, accepting evidence, passing promotion, or mutating a host.

## Purpose

The production-installer transcript status is present and blocked because no reviewed production-installer dry-run install, uninstall, or post-removal absence transcript evidence exists for a tagged release artifact candidate.

This contract adds a no-effect intake validator for that future transcript evidence bundle. The paired template prints the expected bundle shape, and the validator checks local transcript markers, install-review evidence, uninstall-review evidence, post-removal absence review evidence, and hash consistency between the supplied files and the evidence manifest.

It does not accept the evidence, write status, pass the release-artifact promotion gate, or claim production installer readiness.

## Command

```sh
sh scripts/production-installer-transcript-evidence-intake.sh \
  --install <path> \
  --uninstall <path> \
  --absence <path> \
  --install-review <path> \
  --uninstall-review <path> \
  --absence-review <path> \
  --evidence <path>
```

## Current classification

```text
transcript_evidence_intake_validator_present=1
transcript_evidence_intake_validation_mode=no-effect-validation
transcript_evidence_template_present=1
transcript_evidence_template_complete=0
transcript_evidence_candidate_valid=0
install_transcript_file_present=0
uninstall_transcript_file_present=0
post_removal_absence_transcript_file_present=0
install_transcript_sha256_recorded=0
uninstall_transcript_sha256_recorded=0
post_removal_absence_transcript_sha256_recorded=0
install_transcript_review_present=0
uninstall_transcript_review_present=0
post_removal_absence_review_present=0
transcript_evidence_accepted_by_intake_validator=0
transcript_evidence_written_by_intake_validator=0
installer_transcript_promotion_allowed_by_intake_validator_alone=0
release_artifact_promotion_gate_passed=0
installer_install_transcript_recorded=0
installer_uninstall_transcript_recorded=0
installer_post_removal_absence_verified=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
host_mutation_performed=0
```

## Required source records

The validator binds the current blocked transcript posture:

```text
production_installer_ready=0
release_artifact_promotion_gate_passed=0
production_installer_transcript_status_present=1
installer_transcript_status_present=1
installer_install_transcript_recorded=0
installer_uninstall_transcript_recorded=0
installer_post_removal_absence_verified=0
```

It reads these local records:

```text
docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
docs/PRODUCTION_INSTALLER_TRANSCRIPT_STATUS_CONTRACT.md
docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_PROMOTION_GATE_CONTRACT.md
docs/PRODUCTION_INSTALLER_TRANSCRIPT_EVIDENCE_TEMPLATE_CONTRACT.md
docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
scripts/production-installer-transcript-status.sh
README.md
```

## Candidate requirements

A candidate evidence bundle must include all of the following, and the hash fields must match the supplied local files:

```text
LATTICRA PRODUCTION INSTALLER TRANSCRIPT EVIDENCE
transcript_evidence_status=complete
production_installer_dry_run_performed=1
install_transcript_present=1
uninstall_transcript_present=1
post_removal_absence_transcript_present=1
install_transcript_reviewed=1
uninstall_transcript_reviewed=1
post_removal_absence_reviewed=1
installer_install_transcript_recorded=1
installer_uninstall_transcript_recorded=1
installer_post_removal_absence_verified=1
install_transcript_sha256=<actual-install-transcript-sha256>
uninstall_transcript_sha256=<actual-uninstall-transcript-sha256>
post_removal_absence_transcript_sha256=<actual-absence-transcript-sha256>
install_transcript_review_sha256=<actual-install-review-sha256>
uninstall_transcript_review_sha256=<actual-uninstall-review-sha256>
post_removal_absence_review_sha256=<actual-absence-review-sha256>
install_performed=0
uninstall_performed=0
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

The install transcript must identify itself as `LATTICRA PRODUCTION INSTALLER DRY RUN INSTALL TRANSCRIPT`.

The uninstall transcript must identify itself as `LATTICRA PRODUCTION INSTALLER DRY RUN UNINSTALL TRANSCRIPT`.

The absence transcript must identify itself as `LATTICRA PRODUCTION INSTALLER DRY RUN POST-REMOVAL ABSENCE TRANSCRIPT`.

The candidate must not contain placeholder values.

The candidate must not claim transcript evidence acceptance, installer transcript promotion, release-artifact promotion, production installer readiness, Fedora distribution readiness, Fedora approval, daily-driver readiness, immutable Fedora readiness, package-manager invocation, install execution, uninstall execution, network access, or host mutation.

## Validator output

For a valid candidate, the no-effect validator prints:

```text
LATTICRA PRODUCTION INSTALLER TRANSCRIPT EVIDENCE INTAKE VALIDATION
intake_validation_status=ok
transcript_evidence_intake_validator_present=1
transcript_evidence_intake_validation_mode=no-effect-validation
transcript_evidence_candidate_valid=1
install_transcript_file_present=1
uninstall_transcript_file_present=1
post_removal_absence_transcript_file_present=1
install_transcript_sha256_recorded=1
uninstall_transcript_sha256_recorded=1
post_removal_absence_transcript_sha256_recorded=1
candidate_production_installer_dry_run_performed=1
candidate_install_transcript_reviewed=1
candidate_uninstall_transcript_reviewed=1
candidate_post_removal_absence_reviewed=1
candidate_installer_install_transcript_recorded=1
candidate_installer_uninstall_transcript_recorded=1
candidate_installer_post_removal_absence_verified=1
transcript_evidence_accepted_by_intake_validator=0
transcript_evidence_written_by_intake_validator=0
installer_transcript_promotion_allowed_by_intake_validator_alone=0
release_artifact_promotion_gate_passed=0
installer_install_transcript_recorded=0
installer_uninstall_transcript_recorded=0
installer_post_removal_absence_verified=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
install_performed=0
uninstall_performed=0
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0
```

## Guard validation

This contract is guarded by:

```sh
sh scripts/test-production-installer-transcript-evidence-intake-validator-contract.sh
```

Expected output:

```text
production_installer_transcript_evidence_intake_validator_contract: ok
```

## Next implementation lane

```text
Run a disposable Fedora VM production-installer dry-run, review install, uninstall, and post-removal absence transcript evidence, then validate the bundle with the transcript evidence intake validator before any promotion review.
```

Production readiness must remain closed until every other production-installer readiness gate is also satisfied.

## Non-claims

This validator is not a production installer.

It is not install evidence acceptance, not uninstall evidence acceptance, not post-removal absence evidence acceptance, not package-manager execution, not host mutation, not release artifact evidence, not SBOM review, not artifact promotion, not upgrade validation, not rollback validation, not multi-VM validation, not Fedora approval, not Fedora distribution readiness, not daily-driver readiness, not immutable Fedora readiness, not security hardening, not malware prevention, not ransomware prevention, and not OS-replacement readiness.
