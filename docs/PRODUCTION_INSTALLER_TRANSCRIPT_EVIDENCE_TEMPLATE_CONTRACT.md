# Production Installer Transcript Evidence Template Contract

Status: no-effect transcript evidence template contract
Evidence level: 10 target, template only
Scope: print the required future production-installer dry-run transcript evidence bundle shape without installing, uninstalling, invoking package managers, calculating transcript hashes, writing evidence files, accepting evidence, passing promotion, using network access, or mutating the host.

## Purpose

The transcript evidence intake validator can validate a complete future dry-run transcript evidence bundle, but the bundle still needs a stable, reviewable shape before a release operator can collect install, uninstall, post-removal absence, and review evidence safely.

This contract records a no-effect stdout-only template for that future evidence bundle. It mirrors the validator's required fields and keeps placeholder digest values intentionally invalid until real dry-run transcript and review files exist.

It does not write the evidence file and does not make a candidate valid.

## Command

```sh
sh scripts/production-installer-transcript-evidence-template.sh
```

## Current classification

```text
transcript_evidence_template_present=1
transcript_evidence_template_mode=no-effect-template
transcript_evidence_template_decision=blocked-template-only-no-evidence-write
transcript_evidence_template_complete=0
transcript_evidence_intake_validator_present=1
transcript_evidence_intake_validation_mode=no-effect-validation
install_transcript_file_present=<observed>
uninstall_transcript_file_present=<observed>
post_removal_absence_transcript_file_present=<observed>
install_transcript_review_file_present=<observed>
uninstall_transcript_review_file_present=<observed>
post_removal_absence_review_file_present=<observed>
transcripts_created_by_template=0
transcript_hashes_calculated_by_template=0
transcript_evidence_written_by_template=0
transcript_evidence_accepted_by_template=0
transcript_evidence_accepted_by_intake_validator=0
transcript_evidence_written_by_intake_validator=0
installer_transcript_promotion_allowed_by_intake_validator_alone=0
release_artifact_promotion_gate_passed=0
installer_install_transcript_recorded=0
installer_uninstall_transcript_recorded=0
installer_post_removal_absence_verified=0
install_performed=0
uninstall_performed=0
package_manager_invoked=0
network_allowed=0
host_mutation_performed=0
production_installer_ready=0
```

## Required transcript markers

The template must print the marker blocks required in future transcript files:

```text
LATTICRA PRODUCTION INSTALLER DRY RUN INSTALL TRANSCRIPT
production_installer_dry_run_performed=1
install_transcript_present=1
install_performed=0
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0

LATTICRA PRODUCTION INSTALLER DRY RUN UNINSTALL TRANSCRIPT
production_installer_dry_run_performed=1
uninstall_transcript_present=1
uninstall_performed=0
package_manager_invoked=0
host_mutation_performed=0
network_allowed=0

LATTICRA PRODUCTION INSTALLER DRY RUN POST-REMOVAL ABSENCE TRANSCRIPT
production_installer_dry_run_performed=1
post_removal_absence_transcript_present=1
post_removal_absence_check_performed=1
post_removal_absence_verified=1
host_mutation_performed=0
network_allowed=0
```

## Required evidence fields

The template must print the same required field names that the intake validator expects:

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
install_transcript_sha256=<required-install-transcript-sha256>
uninstall_transcript_sha256=<required-uninstall-transcript-sha256>
post_removal_absence_transcript_sha256=<required-absence-transcript-sha256>
install_transcript_review_sha256=<required-install-review-sha256>
uninstall_transcript_review_sha256=<required-uninstall-review-sha256>
post_removal_absence_review_sha256=<required-absence-review-sha256>
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

The placeholders above must be replaced with real SHA-256 values before the evidence intake validator can pass.

## Required source records

The template binds the current blocked transcript posture:

```text
production_installer_ready=0
transcript_evidence_intake_validator_present=1
transcript_evidence_status=complete
release_artifact_promotion_gate_passed=0
```

## Guard validation

This contract is guarded by:

```sh
sh scripts/test-production-installer-transcript-evidence-template-contract.sh
```

Expected output:

```text
production_installer_transcript_evidence_template_contract: ok
```

## Next implementation lane

```text
Use the template after a disposable Fedora VM production-installer dry-run exists, fill real SHA-256 values from reviewed install, uninstall, post-removal absence, and review files, then validate the completed evidence bundle with the transcript evidence intake validator.
```

Production readiness must remain closed until every other production-installer readiness gate is also satisfied.

## Non-claims

This template is not install evidence, not uninstall evidence, not post-removal absence evidence, not transcript evidence acceptance, not evidence writing, not package-manager execution, not host mutation, not release artifact evidence, not SBOM review, not artifact promotion, not upgrade validation, not rollback validation, not recovery validation, not multi-VM validation, not Fedora approval, not Fedora distribution readiness, not daily-driver readiness, not immutable Fedora readiness, and not production installer readiness.
