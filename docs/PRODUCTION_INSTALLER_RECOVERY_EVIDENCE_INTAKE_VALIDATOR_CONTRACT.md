# Production Installer Recovery Evidence Intake Validator Contract

Status: no-effect recovery evidence intake validator contract
Evidence level: 10 target, evidence intake validator only
Scope: validate a future production-installer recovery and failure-mode evidence bundle without recovering, rolling back, invoking a package manager, accepting evidence, passing promotion, or mutating a host.

## Purpose

The production-installer recovery failure-mode status is present and blocked because no reviewed recovery runbook, failure-mode register, recovery drill transcript, rollback drill transcript, or operator recovery receipt exists for a tagged release artifact candidate.

This contract adds a no-effect intake validator for that future recovery evidence bundle. The validator checks local recovery markers, review evidence, and hash consistency between the supplied files and the evidence manifest.

It does not accept the evidence, write status, pass the release-artifact promotion gate, or claim production installer readiness.

## Command

```sh
sh scripts/production-installer-recovery-evidence-intake.sh \
  --runbook <path> \
  --failure-register <path> \
  --recovery-drill <path> \
  --rollback-drill <path> \
  --operator-receipt <path> \
  --runbook-review <path> \
  --failure-register-review <path> \
  --recovery-drill-review <path> \
  --rollback-drill-review <path> \
  --operator-receipt-review <path> \
  --evidence <path>
```

## Current classification

```text
recovery_evidence_intake_validator_present=1
recovery_evidence_intake_validation_mode=no-effect-validation
recovery_evidence_candidate_valid=0
recovery_runbook_file_present=0
failure_mode_register_file_present=0
recovery_drill_transcript_file_present=0
rollback_drill_transcript_file_present=0
operator_recovery_receipt_file_present=0
recovery_runbook_sha256_recorded=0
failure_mode_register_sha256_recorded=0
recovery_drill_transcript_sha256_recorded=0
rollback_drill_transcript_sha256_recorded=0
operator_recovery_receipt_sha256_recorded=0
recovery_runbook_review_present=0
failure_mode_register_review_present=0
recovery_drill_review_present=0
rollback_drill_review_present=0
operator_recovery_receipt_review_present=0
recovery_evidence_accepted_by_intake_validator=0
recovery_evidence_written_by_intake_validator=0
installer_recovery_promotion_allowed_by_intake_validator_alone=0
release_artifact_promotion_gate_passed=0
installer_failure_mode_documented=0
installer_recovery_runbook_present=0
installer_recovery_runbook_reviewed=0
installer_recovery_drill_validated=0
installer_rollback_drill_validated=0
installer_failure_mode_evidence_recorded=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
host_mutation_performed=0
```

## Required source records

The validator binds the current blocked recovery posture:

```text
production_installer_ready=0
release_artifact_promotion_gate_passed=0
production_installer_recovery_failure_mode_status_present=1
installer_recovery_failure_mode_status_no_effect=1
recovery_runbook_present=0
failure_mode_register_present=0
recovery_drill_transcript_present=0
rollback_drill_transcript_present=0
operator_recovery_receipt_present=0
recovery_runbook_reviewed=0
failure_mode_register_reviewed=0
recovery_drill_reviewed=0
rollback_drill_reviewed=0
operator_recovery_receipt_reviewed=0
installer_failure_mode_documented=0
installer_recovery_runbook_present=0
installer_recovery_runbook_reviewed=0
installer_recovery_drill_validated=0
installer_rollback_drill_validated=0
installer_failure_mode_evidence_recorded=0
```

It reads these local records:

```text
docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
docs/PRODUCTION_INSTALLER_RECOVERY_FAILURE_MODE_STATUS_CONTRACT.md
docs/PRODUCTION_INSTALLER_LIFECYCLE_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md
docs/PRODUCTION_INSTALLER_TRANSCRIPT_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md
docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_PROMOTION_GATE_CONTRACT.md
scripts/production-installer-recovery-failure-mode-status.sh
docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
README.md
```

## Candidate requirements

A candidate evidence bundle must include all of the following, and the hash fields must match the supplied local files:

```text
LATTICRA PRODUCTION INSTALLER RECOVERY EVIDENCE
recovery_evidence_status=complete
recovery_runbook_present=1
failure_mode_register_present=1
recovery_drill_transcript_present=1
rollback_drill_transcript_present=1
operator_recovery_receipt_present=1
recovery_runbook_reviewed=1
failure_mode_register_reviewed=1
recovery_drill_reviewed=1
rollback_drill_reviewed=1
operator_recovery_receipt_reviewed=1
installer_failure_mode_documented=1
installer_recovery_runbook_present=1
installer_recovery_runbook_reviewed=1
installer_recovery_drill_validated=1
installer_rollback_drill_validated=1
installer_failure_mode_evidence_recorded=1
recovery_runbook_sha256=<actual-recovery-runbook-sha256>
failure_mode_register_sha256=<actual-failure-mode-register-sha256>
recovery_drill_transcript_sha256=<actual-recovery-drill-transcript-sha256>
rollback_drill_transcript_sha256=<actual-rollback-drill-transcript-sha256>
operator_recovery_receipt_sha256=<actual-operator-recovery-receipt-sha256>
recovery_runbook_review_sha256=<actual-recovery-runbook-review-sha256>
failure_mode_register_review_sha256=<actual-failure-mode-register-review-sha256>
recovery_drill_review_sha256=<actual-recovery-drill-review-sha256>
rollback_drill_review_sha256=<actual-rollback-drill-review-sha256>
operator_recovery_receipt_review_sha256=<actual-operator-recovery-receipt-review-sha256>
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

The recovery runbook must identify itself as `LATTICRA PRODUCTION INSTALLER RECOVERY RUNBOOK`.

The failure-mode register must identify itself as `LATTICRA PRODUCTION INSTALLER FAILURE-MODE REGISTER`.

The recovery drill transcript must identify itself as `LATTICRA PRODUCTION INSTALLER RECOVERY DRILL TRANSCRIPT`.

The rollback drill transcript must identify itself as `LATTICRA PRODUCTION INSTALLER ROLLBACK DRILL TRANSCRIPT`.

The operator recovery receipt must identify itself as `LATTICRA PRODUCTION INSTALLER OPERATOR RECOVERY RECEIPT`.

The candidate must not contain placeholder values.

The candidate must not claim recovery evidence acceptance, recovery promotion, release-artifact promotion, production installer readiness, Fedora distribution readiness, Fedora approval, daily-driver readiness, immutable Fedora readiness, package-manager invocation, recovery execution, rollback drill execution, network access, or host mutation.

## Validator output

For a valid candidate, the no-effect validator prints:

```text
LATTICRA PRODUCTION INSTALLER RECOVERY EVIDENCE INTAKE VALIDATION
intake_validation_status=ok
recovery_evidence_intake_validator_present=1
recovery_evidence_intake_validation_mode=no-effect-validation
recovery_evidence_candidate_valid=1
recovery_runbook_file_present=1
failure_mode_register_file_present=1
recovery_drill_transcript_file_present=1
rollback_drill_transcript_file_present=1
operator_recovery_receipt_file_present=1
recovery_runbook_sha256_recorded=1
failure_mode_register_sha256_recorded=1
recovery_drill_transcript_sha256_recorded=1
rollback_drill_transcript_sha256_recorded=1
operator_recovery_receipt_sha256_recorded=1
candidate_recovery_runbook_reviewed=1
candidate_failure_mode_register_reviewed=1
candidate_recovery_drill_reviewed=1
candidate_rollback_drill_reviewed=1
candidate_operator_recovery_receipt_reviewed=1
candidate_installer_failure_mode_documented=1
candidate_installer_recovery_runbook_present=1
candidate_installer_recovery_runbook_reviewed=1
candidate_installer_recovery_drill_validated=1
candidate_installer_rollback_drill_validated=1
candidate_installer_failure_mode_evidence_recorded=1
recovery_evidence_accepted_by_intake_validator=0
recovery_evidence_written_by_intake_validator=0
installer_recovery_promotion_allowed_by_intake_validator_alone=0
release_artifact_promotion_gate_passed=0
installer_failure_mode_documented=0
installer_recovery_runbook_present=0
installer_recovery_runbook_reviewed=0
installer_recovery_drill_validated=0
installer_rollback_drill_validated=0
installer_failure_mode_evidence_recorded=0
recovery_performed=0
rollback_drill_performed=0
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
sh scripts/test-production-installer-recovery-evidence-intake-validator-contract.sh
```

Expected output:

```text
production_installer_recovery_evidence_intake_validator_contract: ok
```

## Next implementation lane

```text
Create and review the production-installer recovery runbook, failure-mode register, recovery drill transcript, rollback drill transcript, and operator recovery receipt, then validate the bundle with the recovery evidence intake validator before any promotion review.
```

Production readiness must remain closed until every other production-installer readiness gate is also satisfied.

## Non-claims

This validator is not a production installer.

It is not recovery evidence acceptance, not failure-mode evidence acceptance, not recovery safety, not rollback safety, not package-manager execution, not host mutation, not release artifact evidence, not SBOM review, not artifact promotion, not install evidence, not uninstall evidence, not lifecycle validation, not multi-VM validation, not Fedora approval, not Fedora distribution readiness, not daily-driver readiness, not immutable Fedora readiness, not security hardening, not malware prevention, not ransomware prevention, and not OS-replacement readiness.
