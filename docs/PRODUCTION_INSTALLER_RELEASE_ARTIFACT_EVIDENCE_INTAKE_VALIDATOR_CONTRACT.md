# Production Installer Release Artifact Evidence Intake Validator Contract

Status: no-effect release-artifact evidence intake validator contract
Evidence level: 10 target, evidence intake validator only
Scope: validate a future production-installer release-artifact evidence bundle without building, signing, publishing, installing, accepting evidence, passing promotion, or mutating a host.

## Purpose

The production-installer release-artifact promotion gate is present and blocked because no tagged, reproducible, signed release artifact evidence exists yet.

This contract adds a no-effect intake validator for the first hard release-artifact evidence bundle. The validator can check file presence, checksum consistency, signature-file evidence, public-key evidence, verification-transcript evidence, reproducibility-transcript evidence, and artifact-integrity review evidence.

It does not accept that evidence, write status, pass the release-artifact promotion gate, or claim production installer readiness.

## Command

```sh
sh scripts/production-installer-release-artifact-evidence-intake.sh \
  --artifact <path> \
  --sha256 <path> \
  --signature <path> \
  --public-key <path> \
  --verification <path> \
  --reproducibility <path> \
  --review <path> \
  --evidence <path>
```

## Current classification

```text
release_artifact_evidence_intake_validator_present=1
release_artifact_evidence_intake_validation_mode=no-effect-validation
release_artifact_candidate_valid=0
release_artifact_checksum_file_present=0
release_artifact_sha256_matches=0
release_artifact_signature_file_present=0
release_public_key_file_present=0
signature_verification_transcript_present=0
reproducibility_transcript_present=0
artifact_integrity_review_present=0
release_artifact_evidence_accepted_by_intake_validator=0
release_artifact_evidence_written_by_intake_validator=0
release_artifact_promotion_allowed_by_intake_validator_alone=0
release_artifact_promotion_gate_passed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
host_mutation_performed=0
```

## Required source records

The validator binds the current blocked release-artifact posture:

```text
production_installer_ready=0
release_artifact_promotion_gate_present=1
release_artifact_promotion_gate_passed=0
artifact_integrity_status_present=1
installer_artifact_checksum_status_present=1
installer_artifact_signature_status_present=1
```

It reads these local records:

```text
docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
docs/PRODUCTION_INSTALLER_ARTIFACT_INTEGRITY_STATUS_CONTRACT.md
docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_PROMOTION_GATE_CONTRACT.md
docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
scripts/production-installer-artifact-integrity-status.sh
scripts/production-installer-release-artifact-promotion-gate.sh
README.md
```

## Candidate requirements

A candidate evidence bundle must include all of the following, and the hash fields must match the supplied local files:

```text
LATTICRA PRODUCTION INSTALLER RELEASE ARTIFACT EVIDENCE
release_artifact_evidence_status=complete
release_artifact_present=1
release_artifact_built_from_tag=1
release_artifact_reproducible=1
release_artifact_sha256_recorded=1
release_artifact_signature_present=1
release_artifact_signature_verified=1
release_public_key_documented=1
signature_verification_documented=1
artifact_integrity_reviewed=1
installer_artifact_reproducible=1
installer_artifact_checksum_recorded=1
installer_artifact_signature_recorded=1
installer_public_key_documented=1
signature_verification_transcript_present=1
reproducibility_transcript_present=1
artifact_integrity_review_present=1
artifact_sha256=<actual-artifact-sha256>
artifact_signature_sha256=<actual-signature-sha256>
release_public_key_sha256=<actual-public-key-sha256>
signature_verification_transcript_sha256=<actual-verification-transcript-sha256>
reproducibility_transcript_sha256=<actual-reproducibility-transcript-sha256>
artifact_integrity_review_sha256=<actual-review-sha256>
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
host_mutation_performed=0
```

The candidate must not contain placeholder values.

The candidate must not claim release-artifact promotion, production installer readiness, Fedora distribution readiness, Fedora approval, daily-driver readiness, immutable Fedora readiness, or host mutation.

## Validator output

For a valid candidate, the no-effect validator prints:

```text
LATTICRA PRODUCTION INSTALLER RELEASE ARTIFACT EVIDENCE INTAKE VALIDATION
intake_validation_status=ok
release_artifact_evidence_intake_validator_present=1
release_artifact_evidence_intake_validation_mode=no-effect-validation
release_artifact_candidate_valid=1
release_artifact_sha256_matches=1
release_artifact_signature_file_present=1
release_public_key_file_present=1
signature_verification_transcript_present=1
reproducibility_transcript_present=1
artifact_integrity_review_present=1
release_artifact_evidence_accepted_by_intake_validator=0
release_artifact_evidence_written_by_intake_validator=0
release_artifact_promotion_allowed_by_intake_validator_alone=0
release_artifact_promotion_gate_passed=0
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
sh scripts/test-production-installer-release-artifact-evidence-intake-validator-contract.sh
```

Expected output:

```text
production_installer_release_artifact_evidence_intake_validator_contract: ok
```

## Next implementation lane

```text
Create a tagged release artifact candidate, collect checksum, signature, public-key, verification, reproducibility, and review evidence, then validate it with the release-artifact evidence intake validator before any promotion review.
```

Production readiness must remain closed until every other production-installer readiness gate is also satisfied.

## Non-claims

This validator is not a production installer.

It is not a generated release artifact, not artifact signing, not cryptographic signature verification by itself, not artifact publication, not artifact promotion, not SBOM review, not install validation, not uninstall validation, not upgrade validation, not rollback validation, not multi-VM validation, not Fedora approval, not Fedora distribution readiness, not daily-driver readiness, not immutable Fedora readiness, not security hardening, not malware prevention, not ransomware prevention, and not OS-replacement readiness.
