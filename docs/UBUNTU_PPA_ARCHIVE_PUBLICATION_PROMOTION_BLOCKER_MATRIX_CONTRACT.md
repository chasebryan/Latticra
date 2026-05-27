# Ubuntu PPA Archive Publication Promotion Blocker Matrix Contract

Status: no-effect publication promotion blocker matrix contract
Scope: define the blocker matrix for promoting Ubuntu PPA/archive publication evidence without accepting publication evidence.

## Purpose

This contract records the current blocker matrix that prevents any Ubuntu PPA/archive publication result from being promoted.

The goal is narrow: tie the notice, license, lintian/static metadata, build transcript, install/remove evidence, source package evidence, upload/signing evidence, Launchpad build result evidence, and publication non-claim records into one promotion matrix before any Ubuntu publication evidence can be accepted.

This contract is documentation-only and static. It does not run `dpkg-buildpackage`, `debuild`, `lintian`, `sbuild`, `pbuilder`, `debsign`, `dput`, or Launchpad commands. It does not create package artifacts, upload to Launchpad, create a PPA, submit to Ubuntu, publish packages, accept publication evidence, promote publication results, or claim package readiness.

## Current Matrix State

```text
ubuntu_ppa_archive_publication_promotion_blocker_matrix_contract_present=1
ubuntu_publication_promotion_blocker_matrix_contract_present=1
publication_promotion_blocker_matrix_state=blocked-no-effect
ubuntu_ppa_archive_publication_evidence_intake_denial_contract_present=1
ubuntu_publication_evidence_intake_denial_contract_present=1
ubuntu_ppa_archive_publication_evidence_intake_denial_review_contract_present=1
ubuntu_publication_evidence_intake_denial_review_contract_present=1
publication_evidence_intake_denial_state=denied-no-effect
publication_evidence_intake_denial_review_state=reviewed-upheld-no-effect
publication_evidence_denial_review_present=1
publication_evidence_denial_review_decision=uphold-denial
publication_evidence_denial_re_request_allowed=0
ubuntu_publication_evidence_intake_allowed=0
ubuntu_publication_evidence_intake_requested=0
ubuntu_publication_evidence_intake_denied=1
ubuntu_publication_evidence_intake_denial_upheld=1
ubuntu_ppa_archive_publication_gate_state=closed-no-effect
ubuntu_publication_non_claim_review_contract_state=specified-no-effect
local_deb_build_transcript_accepted=0
ubuntu_install_remove_evidence_unblocked=0
ubuntu_source_package_evidence_unblocked=0
ubuntu_upload_signing_authority_evidence_unblocked=0
ubuntu_launchpad_build_result_evidence_unblocked=0
ubuntu_publication_non_claim_review_unblocked=0
source_package_uploaded=0
upload_exit_status_recorded=0
launchpad_build_result_reviewed=0
publication_non_claim_review_present=1
publication_non_claims_reviewed=0
ubuntu_publication_gate_unblocked=0
ubuntu_publication_promotion_blocker_matrix_unblocked=0
publication_result_promoted=0
ubuntu_publication_ready=0
package_readiness_claimed=0
production_installer_ready=0
root_installer_ready=0
```

## Publication Promotion Blocker Matrix

Current promotion state by evidence column:

```text
notice_license_column_state=blocked
lintian_static_metadata_column_state=blocked
local_build_column_state=blocked
install_remove_column_state=blocked
source_package_column_state=blocked
upload_signing_column_state=blocked
launchpad_build_result_column_state=blocked
publication_non_claim_column_state=specified
promotion_column_state=blocked
```

A future publication promotion may not accept any Ubuntu PPA/archive publication evidence unless all required columns are reviewed together:

```text
package_notice_promotion_gate_unblocked=1
package_license_promotion_gate_unblocked=1
ubuntu_lintian_static_metadata_unblocked=1
local_deb_build_transcript_accepted=1
ubuntu_install_remove_evidence_unblocked=1
ubuntu_source_package_evidence_unblocked=1
ubuntu_upload_signing_authority_evidence_unblocked=1
ubuntu_launchpad_build_result_evidence_unblocked=1
ubuntu_publication_non_claim_review_unblocked=1
publication_non_claim_review_present=1
publication_claims_reviewed=1
publication_result_promoted=1
```

Those values are future prerequisites, not current claims. The current matrix remains blocked.

## Ubuntu Publication Promotion Row

Current Ubuntu publication promotion remains blocked:

```text
ubuntu_publication_promotion_blocked=1
ubuntu_publication_promotion_blocker_matrix_unblocked=0
ubuntu_publication_gate_unblocked=0
ubuntu_platform_publication_evidence_accepted=0
ubuntu_publication_result_promoted=0
ubuntu_source_package_evidence_unblocked=0
ubuntu_upload_signing_authority_evidence_unblocked=0
ubuntu_launchpad_build_result_evidence_unblocked=0
ubuntu_publication_non_claim_review_unblocked=0
dpkg_buildpackage_run=0
debuild_run=0
lintian_run=0
debsign_run=0
dput_run=0
launchpad_upload_run=0
ppa_created=0
ppa_claimed=0
ubuntu_archive_submission_claimed=0
ubuntu_archive_ready=0
ubuntu_publication_ready=0
```

Ubuntu package build, lintian, source package, signing, upload, Launchpad, PPA, archive submission, and publication evidence must remain local-only and unpromoted until this matrix opens in a future lane.

## Acceptance Boundary

A future promotion record must bind every accepted Ubuntu publication result to:

```text
platform_under_review
ubuntu_target_series
source_package_contract_reference
source_package_digest
dsc_digest
changes_file_digest
upload_signing_authority_reference
launchpad_build_result_reference
launchpad_upload_url
launchpad_build_log_sha256
launchpad_binary_artifact_listing_sha256
publication_non_claim_review_reference
promotion_reviewer
promotion_decision
promotion_scope
status_page_update_reference
operator_authorization_reference
```

The only permitted future promotion scope from this matrix is Ubuntu publication evidence review. This matrix cannot promote PPA readiness, Ubuntu archive readiness, Canonical endorsement, Ubuntu sponsorship, package repository publication, production installer readiness, or root installer readiness.

## Current Blockers

Ubuntu publication promotion remains blocked under this matrix:

```text
package_notice_promotion_gate_unblocked=0
package_license_promotion_gate_unblocked=0
ubuntu_lintian_static_metadata_unblocked=0
local_deb_build_transcript_accepted=0
ubuntu_install_remove_evidence_unblocked=0
ubuntu_source_package_evidence_unblocked=0
ubuntu_upload_signing_authority_evidence_unblocked=0
ubuntu_launchpad_build_result_evidence_unblocked=0
ubuntu_publication_non_claim_review_unblocked=0
ubuntu_platform_publication_evidence_accepted=0
ubuntu_publication_evidence_intake_allowed=0
ubuntu_publication_evidence_intake_requested=0
ubuntu_publication_evidence_intake_denied=1
publication_evidence_denial_review_present=1
publication_evidence_denial_review_decision=uphold-denial
publication_evidence_denial_re_request_allowed=0
ubuntu_publication_evidence_intake_denial_upheld=1
publication_transcript_intake_accepted=0
ppa_creation_evidence_accepted=0
launchpad_publication_evidence_accepted=0
ubuntu_archive_submission_evidence_accepted=0
ubuntu_publication_result_promoted=0
```

## Command Boundary

This contract does not:

```text
run dpkg-buildpackage
run debuild
run lintian
run sbuild
run pbuilder
run debsign
run dput
run Launchpad commands
create deb artifacts
create source package artifacts
upload packages
create a PPA
submit to Ubuntu
publish packages
promote publication results
claim package readiness
```

## Relationship To Existing Lanes

This contract depends on:

```text
docs/UBUNTU_PACKAGE_NOTICE_PROMOTION_GATE_CONTRACT.md
docs/UBUNTU_PACKAGE_LICENSE_PROMOTION_GATE_CONTRACT.md
docs/UBUNTU_LINTIAN_STATIC_METADATA_CONTRACT.md
docs/UBUNTU_LOCAL_DEB_BUILD_TRANSCRIPT_ACCEPTANCE_GATE_CONTRACT.md
docs/UBUNTU_LOCAL_DEB_INSTALL_REMOVE_EVIDENCE_CONTRACT.md
docs/UBUNTU_SOURCE_PACKAGE_EVIDENCE_CONTRACT.md
docs/UBUNTU_UPLOAD_SIGNING_AUTHORITY_EVIDENCE_CONTRACT.md
docs/UBUNTU_LAUNCHPAD_BUILD_RESULT_EVIDENCE_CONTRACT.md
docs/UBUNTU_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md
docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md
```

The Ubuntu PPA/archive publication gate remains closed. This blocker matrix only records the promotion columns and current blocking values for future Ubuntu publication evidence.

## Completed Follow-On Slice

Publication evidence intake denial is now recorded by:

```text
docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_CONTRACT.md
scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-contract.sh
.github/workflows/ubuntu-ppa-archive-publication-evidence-intake-denial-contract.yml
docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_REVIEW_CONTRACT.md
scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-review-contract.sh
.github/workflows/ubuntu-ppa-archive-publication-evidence-intake-denial-review-contract.yml
```

Those follow-on lanes refuse and review denied PPA creation, archive submission, Launchpad publication evidence, and publication transcript intake while this matrix remains closed.

## Next Slice

Recommended next slice:

```text
Add an Ubuntu publication evidence intake denial disposition contract before any reviewed denial can be closed or re-requested.
```

That future lane should close the upheld denial without accepting Ubuntu publication evidence or opening PPA/archive publication promotion.

## Validation

Run:

```sh
sh scripts/test-ubuntu-ppa-archive-publication-promotion-blocker-matrix-contract.sh
```

Expected output:

```text
ubuntu_ppa_archive_publication_promotion_blocker_matrix_contract: ok
```
