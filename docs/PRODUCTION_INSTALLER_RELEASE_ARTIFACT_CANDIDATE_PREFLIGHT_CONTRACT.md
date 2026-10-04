# Production Installer Release Artifact Candidate Preflight Contract

Status: no-effect release-artifact candidate preflight contract
Evidence level: 10 target, preflight evidence only
Scope: local readiness report for creating a future tagged production-installer release artifact candidate without building, signing, verifying, publishing, installing, invoking a package manager, network access, or host mutation.

## Purpose

The first production-installer evidence lane requires a tagged release artifact candidate with checksum, signature, public-key, verification, reproducibility, and review evidence.

The current repository has a release-artifact promotion gate and release-artifact evidence intake validator, but no generated tagged release artifact candidate and no accepted signing or verification evidence.

This preflight records whether the local environment has the minimum visible inputs for that future lane: tag visibility, tracked worktree cleanliness, archive/checksum tooling, RPM build/query tooling, GPG visibility, and an explicit signing identity reference.

It does not create a source archive, build an RPM, sign an artifact, verify a signature, accept evidence, pass promotion, or claim production installer readiness.

## Command

```sh
sh scripts/production-installer-release-artifact-candidate-preflight.sh \
  --tag v0.2.0edge \
  --artifact-path artifacts/release/latticra-production-installer.rpm \
  --signing-key-fingerprint none
```

## Current classification

```text
release_artifact_candidate_preflight_present=1
release_artifact_candidate_preflight_mode=no-effect-build-signing-readiness
release_artifact_candidate_preflight_no_effect=1
release_artifact_candidate_preflight_passed=0
release_artifact_candidate_inputs_satisfied=0
release_artifact_candidate_blocker_count=<observed>
release_artifact_candidate_blockers=<observed-or-none>
release_artifact_candidate_tag_blocked=<observed>
release_artifact_candidate_parent_dir_blocked=<observed>
release_artifact_candidate_tracked_worktree_blocked=<observed>
release_artifact_candidate_toolchain_blocked=<observed>
release_artifact_candidate_git_blocked=<observed>
release_artifact_candidate_tar_blocked=<observed>
release_artifact_candidate_gzip_blocked=<observed>
release_artifact_candidate_rpmbuild_blocked=<observed>
release_artifact_candidate_rpm_blocked=<observed>
release_artifact_candidate_gpg_blocked=<observed>
release_artifact_candidate_sha256_tool_blocked=<observed>
release_artifact_candidate_signing_identity_reference_blocked=<observed>
release_artifact_candidate_tag_exists=<observed>
release_artifact_candidate_tag_available=<observed>
release_worktree_cleanliness_audit_present=1
release_worktree_cleanliness_required_for_release_candidate=1
release_artifact_candidate_tracked_worktree_clean=<observed>
release_worktree_tracked_worktree_clean=<observed>
release_worktree_tracked_dirty_count=<observed>
release_artifact_candidate_parent_dir_exists=1
release_toolchain_availability_audit_present=1
release_toolchain_required_for_release_candidate=1
release_toolchain_ready=<observed>
release_artifact_build_tool_available=<observed>
release_artifact_query_tool_available=<observed>
rpmbuild_available=<observed>
rpm_available=<observed>
gpg_available=<observed>
sha256_tool_available=<observed>
signing_identity_reference_present=0
signing_identity_reference_format_valid=0
release_signing_identity_reference_validator_present=1
release_artifact_signing_identity_reference_format_valid=0
release_artifact_present=0
release_artifact_built_from_tag=0
release_artifact_reproducible=0
release_artifact_sha256_recorded=0
release_artifact_signature_present=0
release_artifact_signature_verified=0
release_public_key_documented=0
signature_verification_documented=0
artifact_integrity_reviewed=0
checksum_recorded=0
release_artifact_evidence_accepted=0
release_artifact_evidence_written=0
release_artifact_evidence_accepted_by_intake_validator=0
release_artifact_evidence_written_by_intake_validator=0
release_artifact_promotion_allowed_by_intake_validator_alone=0
release_artifact_promotion_gate_passed=0
production_installer_ready=0
host_mutation_performed=0
```

## Required source records

The preflight binds the current blocked release-artifact posture:

```text
production_installer_ready=0
release_artifact_promotion_gate_present=1
release_artifact_promotion_gate_passed=0
release_artifact_evidence_intake_validator_present=1
release_artifact_present=0
release_artifact_built_from_tag=0
release_artifact_signature_verified=0
```

It reads these local records:

```text
docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_STAGING_DIRECTORY_CONTRACT.md
docs/PRODUCTION_INSTALLER_RELEASE_WORKTREE_CLEANLINESS_AUDIT_CONTRACT.md
docs/PRODUCTION_INSTALLER_RELEASE_TOOLCHAIN_AVAILABILITY_AUDIT_CONTRACT.md
docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_PROMOTION_GATE_CONTRACT.md
docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md
docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
artifacts/release/README.md
README.md
```

## Preflight pass requirements

The preflight may report `release_artifact_candidate_preflight_passed=1` only when all of these are true:

```text
release_artifact_candidate_tag_exists=1
release_artifact_candidate_tag_available=1
release_artifact_candidate_parent_dir_exists=1
release_worktree_cleanliness_audit_present=1
release_worktree_cleanliness_required_for_release_candidate=1
release_artifact_candidate_tracked_worktree_clean=1
release_worktree_tracked_worktree_clean=1
tracked_worktree_clean=1
release_toolchain_ready=1
git_available=1
tar_available=1
gzip_available=1
rpmbuild_available=1
rpm_available=1
gpg_available=1
sha256_tool_available=1
signing_identity_reference_present=1
signing_identity_reference_format_valid=1
release_artifact_candidate_blocker_count=0
release_artifact_candidate_blockers=none
```

The preflight still must not create, build, sign, verify, publish, install, or mutate anything.

## Required report fields

Every release artifact candidate preflight report must include:

```text
LATTICRA PRODUCTION INSTALLER RELEASE ARTIFACT CANDIDATE PREFLIGHT
preflight_status=ok
release_artifact_candidate_preflight_present=1
release_artifact_candidate_preflight_mode=no-effect-build-signing-readiness
release_artifact_candidate_preflight_no_effect=1
release_artifact_candidate_preflight_passed=<0-or-1>
release_artifact_candidate_inputs_satisfied=<0-or-1>
release_artifact_candidate_blocker_count=<observed>
release_artifact_candidate_blockers=<observed-or-none>
release_artifact_candidate_tag_blocked=<0-or-1>
release_artifact_candidate_parent_dir_blocked=<0-or-1>
release_artifact_candidate_tracked_worktree_blocked=<0-or-1>
release_artifact_candidate_toolchain_blocked=<0-or-1>
release_artifact_candidate_git_blocked=<0-or-1>
release_artifact_candidate_tar_blocked=<0-or-1>
release_artifact_candidate_gzip_blocked=<0-or-1>
release_artifact_candidate_rpmbuild_blocked=<0-or-1>
release_artifact_candidate_rpm_blocked=<0-or-1>
release_artifact_candidate_gpg_blocked=<0-or-1>
release_artifact_candidate_sha256_tool_blocked=<0-or-1>
release_artifact_candidate_signing_identity_reference_blocked=<0-or-1>
release_artifact_candidate_tag=<recorded>
release_artifact_candidate_tag_exists=<0-or-1>
release_artifact_candidate_tag_available=<0-or-1>
release_artifact_candidate_tag_commit=<recorded-or-missing>
release_artifact_candidate_path=<recorded>
release_artifact_candidate_artifact_path=<recorded>
release_artifact_candidate_parent_dir=<recorded>
release_artifact_candidate_parent_dir_exists=<0-or-1>
release_worktree_cleanliness_audit_present=1
release_worktree_cleanliness_required_for_release_candidate=1
release_artifact_candidate_tracked_worktree_clean=<0-or-1>
release_artifact_candidate_tracked_dirty_count=<observed>
release_worktree_tracked_worktree_clean=<0-or-1>
release_worktree_tracked_dirty_count=<observed>
tracked_worktree_clean=<0-or-1>
tracked_worktree_dirty_count=<observed>
release_toolchain_availability_audit_present=1
release_toolchain_required_for_release_candidate=1
release_toolchain_ready=<0-or-1>
release_artifact_build_tool_available=<0-or-1>
release_artifact_query_tool_available=<0-or-1>
rpmbuild_available=<0-or-1>
rpm_available=<0-or-1>
gpg_available=<0-or-1>
sha256_tool_available=<0-or-1>
release_signing_identity_reference_validator_present=1
signing_identity_reference_present=<0-or-1>
signing_identity_reference_format_valid=<0-or-1>
release_signing_identity_reference_validator_present=1
release_artifact_present=0
release_artifact_built_from_tag=0
release_artifact_reproducible=0
release_artifact_sha256_recorded=0
release_artifact_signature_present=0
release_artifact_signature_verified=0
release_artifact_promotion_gate_passed=0
production_installer_ready=0
checksum_recorded=0
release_artifact_evidence_accepted=0
release_artifact_evidence_written=0
source_archive_created=0
release_artifact_created=0
rpm_build_invoked=0
rpmbuild_invoked=0
rpm_invoked=0
signature_created=0
artifact_signed=0
signature_verified=0
artifact_published=0
install_performed=0
package_manager_invoked=0
network_allowed=0
host_mutation_performed=0
```

## Guard validation

This contract is guarded by:

```sh
sh scripts/test-production-installer-release-artifact-candidate-preflight-contract.sh
```

Expected output:

```text
production_installer_release_artifact_candidate_preflight_contract: ok
```

## Next implementation lane

```text
Satisfy the release-artifact candidate preflight with a clean tracked worktree, RPM build/query tooling, checksum tooling, GPG visibility, and an explicit signing identity reference before creating a tagged production-installer release artifact candidate.
```

Production readiness must remain closed until every other production-installer readiness gate is also satisfied.

## Non-claims

This preflight is not a production installer.

It is not a generated release artifact, not a release checksum, not artifact signing, not signature verification, not artifact publication, not artifact promotion, not SBOM review, not install validation, not uninstall validation, not upgrade validation, not rollback validation, not recovery validation, not multi-VM validation, not Fedora approval, not Fedora distribution readiness, not daily-driver readiness, not immutable Fedora readiness, not security hardening, not malware prevention, not ransomware prevention, and not OS-replacement readiness.
