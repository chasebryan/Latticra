# Latticra v1.0.0 Evidence Blocker Audit Contract

Status: no-effect v1.0.0 evidence blocker audit contract
Evidence level: evidence-blocker decomposition only
Scope: decompose the evidence blockers that keep the v1.0.0 release readiness gate closed across release artifact, SBOM, transcript, lifecycle, recovery, and multi-VM evidence intake records.

## Purpose

The v1.0.0 release readiness gate reports a compact `v1_release_evidence_blocker_count`. That keeps the top-level release decision readable, but it can hide which concrete evidence inputs are still missing before a release can be considered.

This audit gives those evidence blockers one executable no-effect decomposition. It reads existing status records and reports the missing artifact, checksum, signature, SBOM, transcript, lifecycle, recovery, and multi-VM evidence fields that keep the evidence portion of the v1.0.0 gate blocked.

It does not create release artifacts, generate SBOMs, run VMs, invoke package managers, write evidence, accept evidence, pass promotion, install packages, publish releases, or mutate the host.

## Command

```sh
sh scripts/latticra-v1-evidence-blocker-audit.sh
```

## Current classification

```text
v1_evidence_blocker_audit_present=1
v1_evidence_blocker_audit_mode=no-effect-evidence-blocker-decomposition
v1_evidence_blocker_audit_passed=0
v1_evidence_detail_blocker_count=<observed>
v1_evidence_detail_blockers=<observed>
release_artifact_promotion_gate_passed=<observed>
release_artifact_present=<observed>
release_artifact_built_from_tag=<observed>
release_artifact_reproducible=<observed>
release_artifact_sha256_recorded=<observed>
release_artifact_signature_present=<observed>
release_artifact_signature_verified=<observed>
release_artifact_evidence_accepted_by_intake_validator=<observed>
sbom_artifact_file_present=<observed>
sbom_dependency_review_present=<observed>
sbom_vulnerability_review_present=<observed>
sbom_license_review_present=<observed>
sbom_evidence_accepted_by_intake_validator=<observed>
install_transcript_file_present=<observed>
uninstall_transcript_file_present=<observed>
post_removal_absence_transcript_file_present=<observed>
transcript_evidence_accepted_by_intake_validator=<observed>
upgrade_transcript_file_present=<observed>
rollback_transcript_file_present=<observed>
reinstall_transcript_file_present=<observed>
lifecycle_evidence_accepted_by_intake_validator=<observed>
recovery_runbook_file_present=<observed>
failure_mode_register_file_present=<observed>
recovery_drill_transcript_file_present=<observed>
rollback_drill_transcript_file_present=<observed>
operator_recovery_receipt_file_present=<observed>
recovery_evidence_accepted_by_intake_validator=<observed>
fresh_vm_validation_file_present=<observed>
repeat_vm_validation_file_present=<observed>
existing_install_validation_file_present=<observed>
remove_reinstall_validation_file_present=<observed>
unsupported_target_validation_file_present=<observed>
non_root_cli_validation_file_present=<observed>
root_boundary_validation_file_present=<observed>
checksum_verification_file_present=<observed>
package_signature_verification_file_present=<observed>
multi_vm_evidence_accepted_by_intake_validator=<observed>
```

The current detail blocker vocabulary includes `release_artifact_missing`, `release_artifact_signature_not_verified`, `release_artifact_evidence_not_accepted`, `sbom_artifact_file_missing`, `sbom_evidence_not_accepted`, `install_transcript_file_missing`, `transcript_evidence_not_accepted`, `upgrade_transcript_file_missing`, `lifecycle_evidence_not_accepted`, `recovery_runbook_file_missing`, `recovery_evidence_not_accepted`, `fresh_vm_validation_file_missing`, and `multi_vm_evidence_not_accepted`.

## Required Source Records

```text
docs/status/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_CANDIDATE_PREFLIGHT_STATUS.md
docs/status/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_EVIDENCE_INTAKE_VALIDATOR_STATUS.md
docs/status/PRODUCTION_INSTALLER_SBOM_EVIDENCE_INTAKE_VALIDATOR_STATUS.md
docs/status/PRODUCTION_INSTALLER_TRANSCRIPT_EVIDENCE_INTAKE_VALIDATOR_STATUS.md
docs/status/PRODUCTION_INSTALLER_LIFECYCLE_EVIDENCE_INTAKE_VALIDATOR_STATUS.md
docs/status/PRODUCTION_INSTALLER_RECOVERY_EVIDENCE_INTAKE_VALIDATOR_STATUS.md
docs/status/PRODUCTION_INSTALLER_MULTI_VM_EVIDENCE_INTAKE_VALIDATOR_STATUS.md
```

## Pass Requirements

This audit may report `v1_evidence_blocker_audit_passed=1` only after future reviewed records close all evidence detail blockers. In particular:

```text
release_artifact_promotion_gate_passed=1
release_artifact_present=1
release_artifact_built_from_tag=1
release_artifact_reproducible=1
release_artifact_sha256_recorded=1
release_artifact_signature_verified=1
release_artifact_evidence_accepted_by_intake_validator=1
sbom_evidence_accepted_by_intake_validator=1
transcript_evidence_accepted_by_intake_validator=1
lifecycle_evidence_accepted_by_intake_validator=1
recovery_evidence_accepted_by_intake_validator=1
multi_vm_evidence_accepted_by_intake_validator=1
```

The audit must not infer evidence acceptance from templates, placeholders, fixture records, or validator presence alone.

## Validation

```sh
sh scripts/test-latticra-v1-evidence-blocker-audit-contract.sh
```

## Non-Claims

This contract is not evidence acceptance, not a v1.0.0 release candidate, not release artifact promotion, not production installer readiness, not Fedora distribution readiness, not Nadia production readiness, not production cryptography, not runtime authority, and not permission to publish a release.
