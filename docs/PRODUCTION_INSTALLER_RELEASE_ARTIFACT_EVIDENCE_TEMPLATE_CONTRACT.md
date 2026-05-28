# Production Installer Release Artifact Evidence Template Contract

Status: no-effect release-artifact evidence template contract
Evidence level: 10 target, template only
Scope: print the required future production-installer release-artifact evidence bundle shape without creating artifacts, calculating release hashes, signing, verifying signatures, writing evidence files, accepting evidence, passing promotion, publishing, installing, invoking package managers, using network access, or mutating the host.

## Purpose

The release-artifact evidence intake validator can validate a complete future evidence bundle, but the bundle still needs a stable, reviewable shape before a release operator can collect evidence safely.

This contract records a no-effect stdout-only template for that future evidence bundle. It mirrors the validator's required fields and keeps placeholder digest values intentionally invalid until real artifact, signature, public-key, verification, reproducibility, and review files exist.

It does not write the evidence file and does not make a candidate valid.

## Command

```sh
sh scripts/production-installer-release-artifact-evidence-template.sh
```

## Current classification

```text
release_artifact_evidence_template_present=1
release_artifact_evidence_template_mode=no-effect-template
release_artifact_evidence_template_decision=blocked-template-only-no-evidence-write
release_artifact_evidence_template_complete=0
release_artifact_evidence_intake_validator_present=1
release_artifact_evidence_intake_validation_mode=no-effect-validation
release_artifact_candidate_file_present=<observed>
release_artifact_checksum_file_present=<observed>
release_artifact_signature_file_present=<observed>
release_public_key_file_present=<observed>
signature_verification_transcript_file_present=<observed>
reproducibility_transcript_file_present=<observed>
artifact_integrity_review_file_present=<observed>
release_artifact_evidence_written_by_template=0
release_artifact_evidence_accepted_by_template=0
release_artifact_evidence_accepted_by_intake_validator=0
release_artifact_evidence_written_by_intake_validator=0
release_artifact_promotion_allowed_by_intake_validator_alone=0
release_artifact_promotion_gate_passed=0
release_artifact_created=0
source_archive_created=0
rpm_build_invoked=0
rpmbuild_invoked=0
rpm_invoked=0
signature_created=0
artifact_signed=0
signature_verified=0
artifact_published=0
package_manager_invoked=0
network_allowed=0
host_mutation_performed=0
production_installer_ready=0
```

## Required evidence fields

The template must print the same required field names that the intake validator expects:

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
artifact_sha256=<required-artifact-sha256>
artifact_signature_sha256=<required-signature-sha256>
release_public_key_sha256=<required-public-key-sha256>
signature_verification_transcript_sha256=<required-verification-transcript-sha256>
reproducibility_transcript_sha256=<required-reproducibility-transcript-sha256>
artifact_integrity_review_sha256=<required-review-sha256>
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
host_mutation_performed=0
```

The placeholders above must be replaced with real SHA-256 values before the evidence intake validator can pass.

## Required source records

The template binds the current blocked release-artifact posture:

```text
production_installer_ready=0
release_artifact_evidence_intake_validator_present=1
release_artifact_evidence_status=complete
release_artifact_promotion_gate_passed=0
```

## Guard validation

This contract is guarded by:

```sh
sh scripts/test-production-installer-release-artifact-evidence-template-contract.sh
```

Expected output:

```text
production_installer_release_artifact_evidence_template_contract: ok
```

## Next implementation lane

```text
Use the template after a clean tagged release artifact candidate exists, fill real SHA-256 values from the artifact, signature, public key, verification transcript, reproducibility transcript, and review files, then validate the completed evidence bundle with the intake validator.
```

Production readiness must remain closed until every other production-installer readiness gate is also satisfied.

## Non-claims

This template is not a release artifact, not a checksum record, not artifact signing, not signature verification, not evidence acceptance, not evidence writing, not artifact publication, not artifact promotion, not SBOM review, not install validation, not uninstall validation, not upgrade validation, not rollback validation, not recovery validation, not multi-VM validation, not Fedora approval, not Fedora distribution readiness, not daily-driver readiness, not immutable Fedora readiness, not host mutation, and not production installer readiness.
