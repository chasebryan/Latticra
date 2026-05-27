# openSUSE RPM Validation Promotion Blocker Matrix Contract

Status: active RPM validation promotion blocker matrix contract
Scope: define the blocker matrix for promoting openSUSE RPM validation evidence without accepting build evidence.

## Purpose

This contract records the current blocker matrix that prevents any openSUSE RPM validation result from being promoted.

The goal is narrow: tie the source archive, `rpmlint`, disposable environment, artifact naming, payload inspection, install/remove transcript, and OBS publication non-claim records into one promotion matrix before any openSUSE package build evidence can be accepted.

This contract is documentation-only and static. It does not run `rpmbuild`, run `osc`, run `rpmlint`, create RPM artifacts, inspect RPM artifacts, install packages, remove packages, publish packages, submit Latticra to openSUSE, accept Open Build Service evidence, promote validation results, or claim package readiness.

## Current Matrix State

```text
opensuse_rpm_validation_promotion_blocker_matrix_contract_present=1
rpm_validation_promotion_blocker_matrix_contract_present=1
validation_promotion_blocker_matrix_state=blocked-no-effect
opensuse_rpm_build_gate_state=closed-no-effect
obs_publication_non_claim_review_contract_state=specified-no-effect
source_archive_accepted_for_build=0
accepted_rpmlint_transcript_present=0
environment_transcript_present=0
explicit_operator_build_authorization=0
rpm_artifact_created=0
rpm_artifact_sha256_recorded=0
rpm_payload_accepted=0
rpm_install_remove_transcript_present=0
obs_publication_non_claim_review_present=1
opensuse_platform_build_evidence_accepted=0
rpm_validation_result_promoted=0
opensuse_rpm_validation_result_promoted=0
package_readiness_claimed=0
production_installer_ready=0
root_installer_ready=0
```

## Promotion Blocker Matrix

Current promotion state by evidence column:

```text
source_archive_column_state=blocked
rpmlint_column_state=blocked
environment_column_state=blocked
artifact_column_state=blocked
payload_column_state=blocked
install_remove_column_state=blocked
obs_publication_non_claim_column_state=specified
promotion_column_state=blocked
```

A future local validation promotion may not accept any openSUSE build evidence unless all required columns are reviewed together:

```text
source_archive_accepted_for_build=1
archive_sha256_bound_to_build=1
accepted_rpmlint_transcript_present=1
environment_transcript_present=1
explicit_operator_build_authorization=1
rpm_artifact_created=1
rpm_artifact_sha256_recorded=1
rpm_payload_accepted=1
rpm_install_remove_transcript_present=1
obs_publication_non_claim_review_present=1
opensuse_obs_publication_claimed=0
opensuse_platform_build_evidence_accepted=1
rpm_validation_result_promoted=1
```

Those values are future prerequisites, not current claims. The current matrix remains blocked.

## openSUSE Promotion Row

Current openSUSE validation promotion remains blocked:

```text
opensuse_rpm_validation_promotion_blocked=1
opensuse_platform_build_evidence_accepted=0
opensuse_source_archive_accepted_for_build=0
opensuse_rpmlint_transcript_accepted=0
opensuse_build_environment_provisioned=0
opensuse_rpm_artifact_created=0
opensuse_payload_inspection_run=0
opensuse_install_remove_transcript_present=0
opensuse_obs_publication_non_claim_review_present=1
opensuse_obs_publication_claimed=0
opensuse_submit_request_claimed=0
opensuse_official_package_claimed=0
opensuse_rpm_validation_result_promoted=0
rpmbuild_run=0
osc_build_run=0
rpmlint_run=0
osc_submitreq_run=0
obs_project_created=0
obs_package_created=0
opensuse_distribution_ready=0
```

openSUSE `rpmbuild`, `rpmlint`, `osc build`, payload, install/remove, OBS, submit-request, and official-package evidence must remain local-only and unpromoted until this matrix opens in a future lane.

## Acceptance Boundary

A future promotion record must bind every accepted openSUSE result to:

```text
platform_under_review
opensuse_target_distribution
source_archive_contract_reference
source_archive_sha256
rpmlint_transcript_sha256
environment_transcript_sha256
rpm_source_artifact_name
source_rpm_artifact_sha256
binary_rpm_artifact_name
binary_rpm_artifact_sha256
payload_inspection_transcript_sha256
install_remove_transcript_sha256
obs_publication_non_claim_review_reference
promotion_reviewer
promotion_decision
promotion_scope
status_page_update_reference
operator_authorization_reference
```

The only permitted future promotion scope from this matrix is local openSUSE RPM validation evidence. This matrix cannot promote Open Build Service publication, openSUSE Factory acceptance, openSUSE Leap acceptance, official-package status, SUSE endorsement, package repository publication, production installer readiness, or root installer readiness.

## Current Blockers

openSUSE RPM validation promotion remains blocked under this matrix:

```text
source_archive_accepted_for_build=0
accepted_rpmlint_transcript_present=0
environment_transcript_present=0
explicit_operator_build_authorization=0
rpm_artifact_created=0
rpm_artifact_sha256_recorded=0
rpm_payload_accepted=0
rpm_install_remove_transcript_present=0
opensuse_platform_build_evidence_accepted=0
rpm_validation_result_promoted=0
```

## Command Boundary

This contract does not:

```text
run rpmbuild
run osc build
run rpmlint
run osc branch
run osc commit
run osc submitreq
create RPM artifacts
inspect RPM artifacts
install RPM packages
remove RPM packages
create an Open Build Service project
create an Open Build Service package
publish RPM artifacts
submit Latticra to openSUSE
promote openSUSE validation results
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
docs/OPENSUSE_OBS_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md
```

The local RPM build gate remains closed. This blocker matrix only records the promotion columns and current blocking values for future openSUSE local validation evidence.

## Next Slice

Recommended next slice:

```text
Add openSUSE RPM build-evidence intake denial contract before any local build lane can open.
```

That future lane should define how build evidence intake is refused until the blocker matrix opens, while keeping RPM builds and readiness blocked.

## Validation

Run:

```sh
sh scripts/test-opensuse-rpm-validation-promotion-blocker-matrix-contract.sh
```

Expected output:

```text
opensuse_rpm_validation_promotion_blocker_matrix_contract: ok
```
