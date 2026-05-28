# Fedora Package Review Non-Claim Contract

Status: no-effect package review non-claim contract
Scope: define Fedora package review, dist-git, Koji, Bodhi, official-package, and Fedora endorsement non-claims without submitting or publishing packages.

## Purpose

This contract records the Fedora package review non-claim evidence required before any future Fedora RPM validation result can be promoted.

The goal is narrow: future Fedora package validation evidence must remain clearly local-only unless a separate, explicit Fedora package review lane records the required Bugzilla review, reviewer approval, dist-git, Koji, Bodhi, Rawhide, maintainer, and acceptance evidence.

This contract is documentation-only and static.

It does not run `fedpkg`.

It does not run `koji`.

It does not run `bodhi`.

It does not create a Fedora Bugzilla review ticket.

It does not create Fedora dist-git repositories.

It does not submit Latticra to Fedora.

It does not publish RPM artifacts.

It does not install packages.

It does not remove packages.

It does not claim package readiness.

```text
fedora_package_review_non_claim_contract_present=1
fedora_rpm_install_remove_transcript_contract_present=1
package_review_non_claim_contract_present=1
package_review_non_claim_present=1
fedora_package_review_non_claim_present=1
fedora_package_review_non_claim_contract_state=specified-no-effect
package_review_non_claim_state=specified-no-effect
install_remove_transcript_contract_state=specified-no-effect
payload_inspection_contract_state=specified-no-effect
fedora_mock_build_gate_state=closed-no-effect
rpm_validation_result_promoted=0
rpm_artifact_created=0
rpm_artifact_published=0
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
fedora_packager_sponsor_claimed=0
fedora_endorsement_claimed=0
fedora_package_review_ready=0
fedora_distribution_ready=0
package_readiness_claimed=0
production_installer_ready=0
root_installer_ready=0
host_mutation_performed=0
```

## Package Review Non-Claims

Future Fedora validation promotion must preserve these current non-claims:

```text
fedora_package_review_non_claim_required=1
fedora_package_review_non_claim_present=1
fedora_package_review_bug_created=0
fedora_bugzilla_review_ticket_created=0
fedora_package_review_request_created=0
fedora_package_review_approved=0
fedora_reviewer_approval_recorded=0
fedora_scm_request_created=0
fedora_dist_git_repo_created=0
fedora_package_repository_created=0
fedora_koji_build_run=0
fedora_bodhi_update_created=0
fedora_rawhide_submission_claimed=0
fedora_rawhide_acceptance_claimed=0
fedora_official_package_claimed=0
fedora_endorsement_claimed=0
```

The Fedora RPM draft remains local-only. A future Fedora package review, dist-git, Koji, Bodhi, Rawhide, or repository publication lane must be separate from local build, payload, install/remove, and package review non-claim evidence.

## Promotion Review Boundary

A future Fedora RPM validation promotion review must record:

```text
rpm_validation_result_identifier
fedora_target_distribution
source_archive_sha256
source_rpm_artifact_sha256
binary_rpm_artifact_sha256
payload_inspection_transcript_sha256
install_remove_transcript_sha256
fedora_package_review_non_claim_reviewer
fedora_package_review_non_claim_review_date
non_claimed_fedora_review_targets
non_claimed_fedora_distribution_targets
status_page_update_reference
operator_authorization_reference
```

That review may only promote a validation result as local validation evidence. It must not convert local evidence into Fedora package review evidence, Fedora dist-git evidence, Koji evidence, Bodhi evidence, Rawhide evidence, official-package evidence, Fedora endorsement evidence, production installer evidence, or release readiness.

## Current Blockers

Fedora package validation promotion remains blocked because the current repository still has:

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
fedora_package_review_ready=0
```

## Command Boundary

This contract does not:

```text
run fedpkg
run koji
run bodhi
run copr-cli
create a Fedora Bugzilla review ticket
create a Fedora package review request
create a Fedora dist-git repository
create a Fedora package repository
create a Koji build
create a Bodhi update
submit Latticra to Fedora
claim Fedora Rawhide acceptance
claim official Fedora package status
claim Fedora endorsement
create RPM artifacts
publish RPM artifacts
install Latticra on a host
remove Latticra from a host
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
docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md
docs/FEDORA_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md
```

The local mock-build gate remains closed. This package review non-claim contract only records that local Fedora package validation evidence must remain non-submitted and non-official until a separate Fedora package review lane exists.

## Validation

This contract is guarded by:

```sh
sh scripts/test-fedora-package-review-non-claim-contract.sh
```

Expected output:

```text
fedora_package_review_non_claim_contract: ok
```

## Completed Follow-On Lane

```text
docs/FEDORA_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md
scripts/test-fedora-package-validation-promotion-blocker-matrix-contract.sh
.github/workflows/fedora-package-validation-promotion-blocker-matrix-contract.yml
```

That lane records the current Fedora package validation promotion blocker matrix without accepting build evidence or promoting package readiness.

## Next Recommended Lane

```text
Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract before any reviewed archive gate disposition closeout archive gate can be relaxed or re-requested.
```

## Non-claims

This contract is not Fedora package review evidence, not Bugzilla evidence, not reviewer approval, not dist-git evidence, not Koji evidence, not Bodhi evidence, not Rawhide evidence, not official package evidence, not Fedora approval, not Fedora distribution readiness, not production installer readiness, not host mutation, and not production readiness.
