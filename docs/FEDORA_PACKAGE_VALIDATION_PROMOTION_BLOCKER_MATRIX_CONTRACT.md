# Fedora Package Validation Promotion Blocker Matrix Contract

Status: active package validation promotion blocker matrix contract
Scope: define the blocker matrix for promoting Fedora package validation evidence without accepting build evidence.

## Purpose

This contract records the current blocker matrix that prevents any Fedora package validation result from being promoted.

The goal is narrow: tie the source archive, `rpmlint`, disposable build environment, RPM artifact naming, payload inspection, install/remove transcript, and package review non-claim records into one promotion matrix before any Fedora build evidence can be accepted.

This contract is documentation-only and static. It does not run `rpmbuild`, run `mock`, run `rpmlint`, run `dnf`, run `fedpkg`, run `koji`, run `bodhi`, create RPM artifacts, inspect RPM artifacts, install packages, remove packages, publish packages, submit Latticra to Fedora, promote validation results, or claim package readiness.

## Current Matrix State

```text
fedora_package_validation_promotion_blocker_matrix_contract_present=1
fedora_package_review_non_claim_contract_present=1
package_validation_promotion_blocker_matrix_contract_present=1
package_validation_promotion_blocker_matrix_present=1
validation_promotion_blocker_matrix_state=blocked-no-effect
fedora_package_validation_promotion_blocker_matrix_state=blocked-no-effect
package_validation_promotion_blocker_matrix_state=blocked-no-effect
fedora_mock_build_gate_state=closed-no-effect
package_review_non_claim_state=specified-no-effect
install_remove_transcript_contract_state=specified-no-effect
payload_inspection_contract_state=specified-no-effect
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
fedora_package_review_bug_created=0
fedora_bugzilla_review_ticket_created=0
fedora_package_review_request_created=0
fedora_package_review_approved=0
fedora_scm_request_created=0
fedora_dist_git_repo_created=0
fedora_koji_build_run=0
fedora_bodhi_update_created=0
fedora_rawhide_submission_claimed=0
fedora_rawhide_acceptance_claimed=0
fedora_official_package_claimed=0
fedora_endorsement_claimed=0
fedora_platform_build_evidence_accepted=0
fedora_package_validation_result_promoted=0
rpm_validation_result_promoted=0
package_validation_result_promoted=0
fedora_package_review_ready=0
fedora_distribution_ready=0
package_readiness_claimed=0
production_installer_ready=0
root_installer_ready=0
host_mutation_performed=0
```

## Fedora Promotion Blocker Matrix

Current promotion state by evidence column:

```text
source_archive_column_state=blocked
rpmlint_column_state=blocked
environment_column_state=blocked
artifact_column_state=blocked
payload_column_state=blocked
install_remove_column_state=blocked
package_review_non_claim_column_state=specified
fedora_distribution_non_claim_column_state=specified
promotion_column_state=blocked
```

A future local Fedora validation promotion may not accept any build evidence unless all required columns are reviewed together:

```text
source_archive_accepted_for_build=1
archive_sha256_bound_to_build=1
accepted_rpmlint_transcript_present=1
environment_transcript_present=1
explicit_operator_build_authorization=1
source_rpm_artifact_created=1
binary_rpm_artifact_created=1
rpm_artifact_sha256_recorded=1
rpm_payload_accepted=1
rpm_install_remove_transcript_present=1
fedora_package_review_non_claim_present=1
fedora_package_review_ready=0
fedora_official_package_claimed=0
fedora_platform_build_evidence_accepted=1
fedora_package_validation_result_promoted=1
rpm_validation_result_promoted=1
```

Those values are future prerequisites, not current claims. The current matrix remains blocked.

## Fedora Promotion Row

Current Fedora validation promotion remains blocked:

```text
fedora_package_validation_promotion_blocked=1
fedora_platform_build_evidence_accepted=0
fedora_source_archive_accepted_for_build=0
fedora_rpmlint_transcript_accepted=0
fedora_build_environment_provisioned=0
fedora_mock_build_environment_provisioned=0
fedora_source_rpm_artifact_created=0
fedora_binary_rpm_artifact_created=0
fedora_payload_inspection_run=0
fedora_install_remove_transcript_present=0
fedora_package_review_non_claim_present=1
fedora_package_review_claimed=0
fedora_package_review_bug_created=0
fedora_dist_git_repo_created=0
fedora_koji_build_run=0
fedora_bodhi_update_created=0
fedora_official_package_claimed=0
fedora_package_validation_result_promoted=0
rpmbuild_run=0
mock_build_run=0
mock_buildsrpm_run=0
rpmlint_run=0
dnf_builddep_run=0
fedpkg_run=0
koji_run=0
bodhi_run=0
fedora_distribution_ready=0
```

Fedora `rpmbuild`, `mock`, `rpmlint`, payload, install/remove, package review, dist-git, Koji, Bodhi, Rawhide, and official-package evidence must remain local-only and unpromoted until this matrix opens in a future lane.

## Acceptance Boundary

A future promotion record must bind every accepted Fedora result to:

```text
platform_under_review
fedora_target_distribution
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
fedora_package_review_non_claim_reference
promotion_reviewer
promotion_decision
promotion_scope
status_page_update_reference
operator_authorization_reference
```

The only permitted future promotion scope from this matrix is local Fedora RPM validation evidence. This matrix cannot promote Fedora package review approval, Fedora dist-git, Koji, Bodhi, Rawhide acceptance, official-package status, Fedora endorsement, package repository publication, production installer readiness, or root installer readiness.

## Current Blockers

Fedora package validation promotion remains blocked under this matrix:

```text
source_archive_accepted_for_build=0
accepted_rpmlint_transcript_present=0
environment_transcript_present=0
explicit_operator_build_authorization=0
source_rpm_artifact_created=0
binary_rpm_artifact_created=0
rpm_artifact_sha256_recorded=0
rpm_payload_accepted=0
rpm_install_remove_transcript_present=0
fedora_platform_build_evidence_accepted=0
fedora_package_validation_result_promoted=0
rpm_validation_result_promoted=0
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
docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md
docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md
```

The local mock-build gate remains closed. This blocker matrix only records the promotion columns and current blocking values for future Fedora local validation evidence.

## Validation

This contract is guarded by:

```sh
sh scripts/test-fedora-package-validation-promotion-blocker-matrix-contract.sh
```

Expected output:

```text
fedora_package_validation_promotion_blocker_matrix_contract: ok
```

## Completed Follow-On Lane

```text
docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md
scripts/test-fedora-rpm-build-evidence-intake-denial-contract.sh
.github/workflows/fedora-rpm-build-evidence-intake-denial-contract.yml
```

That lane denies Fedora RPM build-evidence intake while the blocker matrix remains closed.

## Next Recommended Lane

```text
Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract before any reviewed archive gate disposition closeout archive gate can be relaxed or re-requested.
```

## Non-claims

This contract is not Fedora package review evidence, not Bugzilla evidence, not reviewer approval, not dist-git evidence, not Koji evidence, not Bodhi evidence, not Rawhide evidence, not official package evidence, not Fedora approval, not Fedora distribution readiness, not production installer readiness, not host mutation, and not production readiness.
