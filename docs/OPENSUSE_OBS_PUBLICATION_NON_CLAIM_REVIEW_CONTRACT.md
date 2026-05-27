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

Recommended next slice:

```text
Add openSUSE RPM build-evidence intake denial contract before any local build lane can open.
```

That future lane should define how build evidence intake is refused until the blocker matrix opens, while keeping RPM builds and readiness blocked.

## Validation

Run:

```sh
sh scripts/test-opensuse-obs-publication-non-claim-review-contract.sh
```

Expected output:

```text
opensuse_obs_publication_non_claim_review_contract: ok
```
