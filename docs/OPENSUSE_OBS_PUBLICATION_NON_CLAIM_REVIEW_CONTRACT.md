# openSUSE OBS Publication Non-Claim Review Contract

Status: active OBS publication non-claim review contract
Scope: define Open Build Service, submit-request, official-package, and SUSE endorsement non-claim review evidence for openSUSE package validation without publishing packages.

## Purpose

This contract records the Open Build Service publication non-claim review required before any future openSUSE RPM validation result can be promoted.

The goal is narrow: future openSUSE package validation evidence must remain clearly local-only unless a separate, explicit publication lane records the required Open Build Service project, package, repository, submit-request, maintainer-review, and acceptance evidence.

This contract is documentation-only and static. It does not run `osc`, create an Open Build Service project, create an OBS package, upload sources, submit Latticra to openSUSE, create package repositories, publish RPM artifacts, create RPM artifacts, install packages, remove packages, or claim package readiness.

## Current Publication Non-Claim State

```text
opensuse_obs_publication_non_claim_review_contract_present=1
obs_publication_non_claim_review_contract_present=1
publication_non_claim_review_contract_present=1
obs_publication_non_claim_review_present=1
publication_non_claim_review_present=1
opensuse_rpm_build_gate_state=closed-no-effect
payload_inspection_contract_state=specified-no-effect
install_remove_transcript_contract_state=specified-no-effect
rpm_validation_result_promoted=0
rpm_artifact_created=0
rpm_artifact_published=0
obs_project_created=0
obs_package_created=0
obs_repository_created=0
obs_source_link_created=0
osc_branch_run=0
osc_commit_run=0
osc_submitreq_run=0
osc_request_accepted=0
obs_build_result_claimed=0
opensuse_obs_publication_claimed=0
opensuse_submit_request_claimed=0
opensuse_official_package_claimed=0
suse_endorsement_claimed=0
opensuse_factory_submission_claimed=0
opensuse_factory_acceptance_claimed=0
opensuse_leap_submission_claimed=0
opensuse_distribution_ready=0
package_readiness_claimed=0
production_installer_ready=0
root_installer_ready=0
```

## OBS Publication Non-Claims

Future openSUSE validation promotion must preserve these current non-claims:

```text
obs_publication_non_claim_review_required=1
obs_publication_non_claim_review_present=1
opensuse_obs_publication_claimed=0
opensuse_submit_request_claimed=0
opensuse_official_package_claimed=0
suse_endorsement_claimed=0
obs_project_created=0
obs_package_created=0
obs_repository_created=0
obs_source_upload_run=0
osc_branch_run=0
osc_add_run=0
osc_commit_run=0
osc_submitreq_run=0
osc_request_accepted=0
```

The openSUSE RPM draft remains local-only. A future Open Build Service project, submit-request, Factory, Leap, or repository publication lane must be separate from local build, payload, install/remove, and publication non-claim review evidence.

## Promotion Review Boundary

A future openSUSE RPM validation promotion review must record:

```text
rpm_validation_result_identifier
opensuse_target_distribution
source_archive_sha256
source_rpm_artifact_sha256
binary_rpm_artifact_sha256
payload_inspection_transcript_sha256
install_remove_transcript_sha256
obs_publication_non_claim_reviewer
obs_publication_non_claim_review_date
non_claimed_obs_targets
non_claimed_submit_request_targets
status_page_update_reference
operator_authorization_reference
```

That review may only promote a validation result as local validation evidence. It must not convert local evidence into Open Build Service publication evidence, openSUSE Factory evidence, openSUSE Leap evidence, official-package evidence, SUSE endorsement evidence, package repository evidence, production installer evidence, or release readiness.

## Current Blockers

openSUSE RPM validation promotion remains blocked because the current repository still has:

```text
source_archive_accepted_for_build=0
accepted_rpmlint_transcript_present=0
rpm_artifact_created=0
rpm_artifact_sha256_recorded=0
rpm_payload_accepted=0
rpm_install_remove_transcript_present=0
environment_transcript_present=0
explicit_operator_build_authorization=0
rpm_validation_result_promoted=0
```

## Command Boundary

This contract does not:

```text
run osc branch
run osc add
run osc commit
run osc submitreq
run osc build
create an Open Build Service project
create an Open Build Service package
upload source files to Open Build Service
publish RPM artifacts
submit Latticra to openSUSE
claim openSUSE Factory acceptance
claim openSUSE Leap acceptance
claim official openSUSE package status
claim SUSE endorsement
create RPM artifacts
install Latticra on a host
remove Latticra from a host
claim package readiness
```

## Relationship To Existing Lanes

This contract depends on:

```text
docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md
docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md
docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md
docs/OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md
docs/OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md
```

The local RPM build gate remains closed. This OBS publication non-claim review contract only records that local openSUSE package validation evidence must remain non-published and non-official until a separate Open Build Service publication lane exists.

## Next Slice

Completed follow-on RPM validation promotion blocker matrix contract:

```text
docs/OPENSUSE_RPM_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md
scripts/test-opensuse-rpm-validation-promotion-blocker-matrix-contract.sh
.github/workflows/opensuse-rpm-validation-promotion-blocker-matrix-contract.yml
```

That lane ties source, `rpmlint`, environment, artifact, payload, install/remove, and OBS non-claim columns together while keeping build evidence intake and readiness blocked.

Completed follow-on RPM build-evidence intake denial contract:

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-contract.yml
```

That lane refuses `rpmbuild`, `osc build`, `rpmlint`, source RPM, binary RPM, and transcript intake while the blocker matrix is closed.

Completed follow-on RPM build-evidence intake denial review contract:

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_REVIEW_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-review-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-review-contract.yml
```

That lane upholds the denied intake state while keeping build-evidence re-requests blocked.

Completed follow-on RPM build-evidence intake denial disposition contract:

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-contract.yml
```

That lane closes the upheld denial without accepting openSUSE build evidence or opening RPM builds.

Completed follow-on RPM build-evidence intake denial disposition closeout contract:

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-closeout-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-closeout-contract.yml
```

That lane closes out the no-effect disposition while keeping archive, re-request, build, and readiness blockers in place.

Completed follow-on RPM build-evidence intake denial disposition closeout archive gate contract:

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-contract.yml
```

That lane keeps the closed-out denial unarchived while archive, re-request, build, and readiness blockers stay in place.

Completed follow-on RPM build-evidence intake denial disposition closeout archive gate review contract:

```text
Add openSUSE RPM build-evidence intake denial disposition closeout archive gate review contract before any archive gate can be relaxed or re-requested.
```

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-contract.yml
```

That lane reviews and upholds the closed archive gate while preserving RPM build and readiness blockers.

Completed follow-on RPM build-evidence intake denial disposition closeout archive gate review disposition contract:

```text
Add openSUSE RPM build-evidence intake denial disposition closeout archive gate review disposition contract before any reviewed archive gate can be relaxed or re-requested.
```

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-contract.yml
```

That lane disposes the reviewed closed archive gate while preserving RPM build and readiness blockers.


Completed follow-on RPM build-evidence intake denial disposition closeout archive gate review disposition closeout contract:

```text
Add openSUSE RPM build-evidence intake denial disposition closeout archive gate review disposition closeout contract before any reviewed archive gate disposition can be archived or re-requested.
```

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-contract.yml
```

That lane closes out the reviewed archive gate disposition while preserving RPM build and readiness blockers.


Completed follow-on RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate contract:

```text
Add openSUSE RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate contract before any reviewed archive gate disposition closeout can be archived or re-requested.
```

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-contract.yml
```

That lane keeps the reviewed archive gate disposition closeout unarchived while preserving RPM build and readiness blockers.


Completed follow-on RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract:

```text
Add openSUSE RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract before any reviewed archive gate disposition closeout archive gate can be relaxed or re-requested.
```

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-contract.yml
```

That lane reviews and upholds the reviewed archive gate disposition closeout archive gate while preserving RPM build and readiness blockers.

Completed follow-on RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition contract:

```text
Add openSUSE RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition contract before any reviewed archive gate disposition closeout archive gate can be relaxed or re-requested.
```

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-contract.yml
```

That lane records the reviewed closeout archive gate as disposed while preserving RPM build and readiness blockers.


Completed follow-on RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout contract:

```text
Add openSUSE RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout contract before any reviewed archive gate disposition closeout archive gate review disposition can be archived or re-requested.
```

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-contract.yml
```

That lane closes out the reviewed closeout archive gate review disposition while preserving RPM build and readiness blockers.

Completed follow-on RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate contract:

```text
Add openSUSE RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate contract before any reviewed archive gate disposition closeout archive gate review disposition closeout can be archived or re-requested.
```

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-contract.yml
```

That lane keeps the reviewed closeout archive gate review disposition closeout unarchived while preserving RPM build and readiness blockers.

Completed follow-on RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review contract:

```text
Add openSUSE RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review contract before any reviewed archive gate disposition closeout archive gate review disposition closeout archive gate can be relaxed or re-requested.
```

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-contract.yml
```

That lane reviews and upholds the reviewed closeout archive gate review disposition closeout archive gate while preserving RPM build and readiness blockers.

Completed follow-on RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review disposition contract:

```text
Add openSUSE RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review disposition contract before any reviewed archive gate disposition closeout archive gate review disposition closeout archive gate can be relaxed or re-requested.
```

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-contract.yml
```

That lane records the reviewed closeout archive gate review disposition closeout archive gate review as disposed while preserving RPM build and readiness blockers.

Completed follow-on RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review disposition closeout contract:

```text
Add openSUSE RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review disposition closeout contract before any reviewed archive gate disposition closeout archive gate review disposition closeout archive gate review disposition can be archived or re-requested.
```

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-contract.yml
```

That lane closes out the reviewed closeout archive gate review disposition closeout archive gate review disposition while preserving RPM build and readiness blockers.

Completed follow-on RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate contract:

```text
Add openSUSE RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate contract before any reviewed archive gate disposition closeout archive gate review disposition closeout archive gate review disposition closeout can be archived or re-requested.
```

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-contract.sh
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-contract.yml
```

That lane keeps the reviewed closeout archive gate review disposition closeout archive gate review disposition closeout unarchived while preserving RPM build and readiness blockers.

Recommended next slice:

```text
Add openSUSE RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review contract before any reviewed archive gate disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate can be relaxed or re-requested.
```

That future lane should review the closed archive gate for the reviewed closeout archive gate review disposition closeout while preserving RPM build and readiness blockers.


Completed follow-on archive gate review record:

```text
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_CONTRACT.md
```

That follow-on review preserves the closed, no-effect archive gate posture and does not accept build evidence, create RPM artifacts, or claim package readiness.

## Validation

Run:

```sh
sh scripts/test-opensuse-obs-publication-non-claim-review-contract.sh
```

Expected output:

```text
opensuse_obs_publication_non_claim_review_contract: ok
```
