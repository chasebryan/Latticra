# Fedora RPM Build-Evidence Intake Denial Review Contract

Status: active RPM build-evidence intake denial review contract
Scope: define review of denied Fedora RPM build-evidence intake while the package validation promotion blocker matrix is closed.

## Purpose

This contract records the no-effect review of denied Fedora RPM build-evidence intake.

The goal is narrow: a denied build-evidence intake request cannot be re-requested, reopened, summarized as accepted, or used to open a Fedora build lane while the package validation promotion blocker matrix remains blocked.

This contract is documentation-only and static. It does not run `rpmbuild`, run `mock`, run `rpmlint`, run `dnf`, run `fedpkg`, run `koji`, run `bodhi`, request build evidence, re-request denied evidence, accept build evidence, create RPM artifacts, inspect RPM artifacts, install packages, remove packages, publish packages, submit Latticra to Fedora, promote validation results, or claim package readiness.

## Current Denial Review State

```text
fedora_rpm_build_evidence_intake_denial_review_contract_present=1
fedora_rpm_build_evidence_intake_denial_contract_present=1
fedora_package_validation_promotion_blocker_matrix_contract_present=1
rpm_build_evidence_intake_denial_review_contract_present=1
build_evidence_intake_denial_review_state=reviewed-upheld-no-effect
build_evidence_intake_denial_state=denied-no-effect
validation_promotion_blocker_matrix_state=blocked-no-effect
fedora_package_validation_promotion_blocker_matrix_state=blocked-no-effect
fedora_mock_build_gate_state=closed-no-effect
denial_review_required_before_re_request=1
denial_review_present=1
denial_review_decision=uphold-denial
denial_re_request_allowed=0
fedora_denial_re_request_allowed=0
fedora_build_evidence_intake_allowed=0
fedora_build_evidence_intake_denied=1
fedora_platform_build_evidence_accepted=0
build_transcript_intake_accepted=0
rpm_build_transcript_intake_accepted=0
fedora_build_transcript_intake_accepted=0
rpm_build_lane_opened=0
fedora_single_platform_build_lane_opened=0
source_archive_accepted_for_build=0
accepted_rpmlint_transcript_present=0
environment_transcript_present=0
explicit_operator_build_authorization=0
source_rpm_artifact_created=0
binary_rpm_artifact_created=0
rpm_artifact_created=0
rpm_artifact_sha256_recorded=0
rpm_payload_accepted=0
rpm_install_remove_transcript_present=0
fedora_package_review_non_claim_present=1
fedora_package_validation_result_promoted=0
rpm_validation_result_promoted=0
package_validation_result_promoted=0
package_readiness_claimed=0
production_installer_ready=0
root_installer_ready=0
host_mutation_performed=0
```

## Review Record Requirements

A future denial review record must bind the review to the denied intake request:

```text
build_evidence_intake_request_identifier
build_evidence_denial_reference
denial_review_identifier
fedora_target_distribution
requested_build_evidence_kind
requested_build_command
submitted_transcript_reference
validation_promotion_blocker_matrix_reference
denial_review_decision
denial_review_reason
denial_review_reviewer
status_page_update_reference
operator_authorization_reference
```

The only current review decision allowed by this contract is `uphold-denial`.

## Fedora Denial Review

Current Fedora RPM build-evidence intake denial review upholds denial:

```text
fedora_build_evidence_intake_denial_review_present=1
fedora_build_evidence_intake_denial_upheld=1
fedora_denial_re_request_allowed=0
fedora_build_evidence_intake_allowed=0
fedora_build_evidence_intake_denied=1
fedora_build_transcript_intake_accepted=0
fedora_platform_build_evidence_accepted=0
fedora_rpmbuild_evidence_accepted=0
fedora_mock_build_evidence_accepted=0
fedora_mock_buildsrpm_evidence_accepted=0
fedora_rpmlint_evidence_accepted=0
fedora_source_rpm_evidence_accepted=0
fedora_binary_rpm_evidence_accepted=0
rpmbuild_run=0
rpmbuild_ba_run=0
rpmbuild_bb_run=0
rpmbuild_bs_run=0
mock_build_run=0
mock_buildsrpm_run=0
rpmlint_run=0
dnf_builddep_run=0
fedpkg_run=0
koji_run=0
bodhi_run=0
fedora_package_review_request_created=0
fedora_koji_build_run=0
fedora_bodhi_update_created=0
fedora_rawhide_submission_claimed=0
fedora_official_package_claimed=0
fedora_package_validation_result_promoted=0
fedora_distribution_ready=0
```

Fedora build, lint, artifact, payload, install/remove, package review, dist-git, Koji, Bodhi, Rawhide, and official-package evidence remains denied, unaccepted, and unusable as build-lane opening evidence.

## Current Blockers

Denial review remains an upheld no-effect denial under this blocker state:

```text
validation_promotion_blocker_matrix_state=blocked-no-effect
source_archive_accepted_for_build=0
accepted_rpmlint_transcript_present=0
environment_transcript_present=0
explicit_operator_build_authorization=0
source_rpm_artifact_created=0
binary_rpm_artifact_created=0
rpm_artifact_created=0
rpm_artifact_sha256_recorded=0
rpm_payload_accepted=0
rpm_install_remove_transcript_present=0
fedora_platform_build_evidence_accepted=0
fedora_package_validation_result_promoted=0
rpm_validation_result_promoted=0
denial_re_request_allowed=0
```

## Command Boundary

This contract does not:

```text
run rpmbuild
run mock
run rpmlint
run dnf
run fedpkg
run koji
run bodhi
run copr-cli
request build evidence
re-request build evidence
accept build evidence
create RPM artifacts
inspect RPM artifacts
install RPM packages
remove RPM packages
create a Fedora Bugzilla review ticket
create a Fedora package review request
create a Fedora dist-git repository
create a Koji build
create a Bodhi update
publish RPM artifacts
submit Latticra to Fedora
promote Fedora validation results
claim package readiness
claim Fedora distribution readiness
claim production readiness
```

## Relationship To Existing Lanes

This contract depends on:

```text
docs/FEDORA_RPMLINT_FINDINGS_CLASSIFICATION.md
docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
docs/FEDORA_SOURCE_ARCHIVE_MOCK_BUILD_INPUT_HANDOFF_CONTRACT.md
docs/FEDORA_LOCAL_MOCK_BUILD_GATE_CONTRACT.md
docs/FEDORA_LOCAL_MOCK_BUILD_ENVIRONMENT_CONTRACT.md
docs/FEDORA_RPM_ARTIFACT_NAMING_CONTRACT.md
docs/FEDORA_RPM_PAYLOAD_INSPECTION_CONTRACT.md
docs/FEDORA_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md
docs/FEDORA_PACKAGE_REVIEW_NON_CLAIM_CONTRACT.md
docs/FEDORA_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md
docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md
docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md
```

The local mock-build gate remains closed. This denial review contract only records that the denied intake state was reviewed and upheld while the blocker matrix remains closed.

Completed follow-on Fedora RPM build-evidence intake denial disposition contract:

```text
docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CONTRACT.md
scripts/test-fedora-rpm-build-evidence-intake-denial-disposition-contract.sh
.github/workflows/fedora-rpm-build-evidence-intake-denial-disposition-contract.yml
```

## Validation

This contract is guarded by:

```sh
sh scripts/test-fedora-rpm-build-evidence-intake-denial-review-contract.sh
```

Expected output:

```text
fedora_rpm_build_evidence_intake_denial_review_contract: ok
```

## Next Recommended Lane

```text
Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract before any reviewed archive gate disposition closeout archive gate can be relaxed or re-requested.
```

## Non-claims

This contract is not Fedora build evidence, not `mock` evidence, not `rpmlint` evidence, not RPM artifact evidence, not Fedora package review evidence, not Bugzilla evidence, not reviewer approval, not dist-git evidence, not Koji evidence, not Bodhi evidence, not Rawhide evidence, not official package evidence, not Fedora approval, not Fedora distribution readiness, not production installer readiness, not host mutation, and not production readiness.
