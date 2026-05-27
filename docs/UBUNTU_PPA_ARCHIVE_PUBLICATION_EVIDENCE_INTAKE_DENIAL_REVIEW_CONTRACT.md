# Ubuntu PPA Archive Publication Evidence Intake Denial Review Contract

Status: no-effect publication evidence intake denial review contract
Scope: define review of denied Ubuntu PPA/archive publication evidence intake while the publication promotion blocker matrix is closed.

## Purpose

This contract records the no-effect review of denied Ubuntu PPA/archive publication evidence intake.

The goal is narrow: a denied publication-evidence intake request cannot be re-requested, reopened, summarized as accepted, or used to open Ubuntu PPA/archive publication evidence while the publication promotion blocker matrix remains blocked.

This contract is documentation-only and static. It does not run `dpkg-buildpackage`, `debuild`, `lintian`, `sbuild`, `pbuilder`, `debsign`, `dput`, or Launchpad commands. It does not request publication evidence, re-request denied evidence, accept publication evidence, create package artifacts, upload to Launchpad, create a PPA, submit to Ubuntu, publish packages, promote publication results, or claim package readiness.

## Current Denial Review State

```text
ubuntu_ppa_archive_publication_evidence_intake_denial_review_contract_present=1
ubuntu_publication_evidence_intake_denial_review_contract_present=1
publication_evidence_intake_denial_review_state=reviewed-upheld-no-effect
publication_evidence_intake_denial_state=denied-no-effect
publication_promotion_blocker_matrix_state=blocked-no-effect
ubuntu_ppa_archive_publication_gate_state=closed-no-effect
denial_review_required_before_re_request=1
publication_evidence_denial_review_present=1
publication_evidence_denial_review_decision=uphold-denial
publication_evidence_denial_re_request_allowed=0
ubuntu_publication_evidence_intake_allowed=0
ubuntu_publication_evidence_intake_requested=0
ubuntu_publication_evidence_intake_denied=1
ubuntu_publication_evidence_intake_denial_upheld=1
ubuntu_platform_publication_evidence_accepted=0
publication_transcript_intake_accepted=0
ppa_creation_evidence_accepted=0
launchpad_publication_evidence_accepted=0
ubuntu_archive_submission_evidence_accepted=0
publication_result_evidence_accepted=0
publication_result_promoted=0
ubuntu_publication_result_promoted=0
ubuntu_publication_ready=0
package_readiness_claimed=0
production_installer_ready=0
root_installer_ready=0
```

## Review Record Requirements

A future denial review record must bind the review to the denied intake request:

```text
publication_evidence_intake_request_identifier
publication_evidence_denial_reference
denial_review_identifier
ubuntu_target_series
requested_publication_evidence_kind
requested_publication_action
submitted_publication_transcript_reference
source_package_digest
dsc_digest
changes_file_digest
launchpad_upload_url
launchpad_build_result_reference
publication_promotion_blocker_matrix_reference
denial_review_decision
denial_review_reason
denial_review_reviewer
status_page_update_reference
operator_authorization_reference
```

The only current review decision allowed by this contract is `uphold-denial`.

## Ubuntu Denial Review

Current Ubuntu PPA/archive publication evidence intake denial review upholds denial:

```text
ubuntu_publication_evidence_intake_denial_review_present=1
ubuntu_publication_evidence_intake_denial_upheld=1
ubuntu_publication_denial_re_request_allowed=0
ubuntu_publication_evidence_intake_allowed=0
ubuntu_publication_evidence_intake_denied=1
ubuntu_publication_transcript_intake_accepted=0
ubuntu_platform_publication_evidence_accepted=0
ubuntu_ppa_creation_evidence_accepted=0
ubuntu_launchpad_publication_evidence_accepted=0
ubuntu_archive_submission_evidence_accepted=0
ubuntu_publication_result_evidence_accepted=0
debsign_run=0
dput_run=0
launchpad_upload_run=0
ppa_created=0
ppa_claimed=0
ubuntu_archive_submission_claimed=0
ubuntu_publication_result_promoted=0
ubuntu_publication_ready=0
```

Ubuntu PPA creation, archive submission, Launchpad publication, publication transcript, publication result, and package readiness evidence remains denied, unaccepted, and unusable as publication evidence.

## Current Blockers

Denial review remains an upheld no-effect denial under this blocker state:

```text
publication_promotion_blocker_matrix_state=blocked-no-effect
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
ubuntu_publication_result_promoted=0
publication_evidence_denial_re_request_allowed=0
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
request publication evidence
re-request publication evidence
accept publication evidence
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
docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md
docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_CONTRACT.md
docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md
```

The Ubuntu PPA/archive publication gate remains closed. This denial review contract only records that the denied intake state was reviewed and upheld while the publication promotion blocker matrix remains closed.

## Next Slice

Recommended next slice:

```text
Add an Ubuntu publication evidence intake denial disposition contract before any reviewed denial can be closed or re-requested.
```

That future lane should close the upheld denial without accepting Ubuntu publication evidence or opening PPA/archive publication promotion.

## Validation

Run:

```sh
sh scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-review-contract.sh
```

Expected output:

```text
ubuntu_ppa_archive_publication_evidence_intake_denial_review_contract: ok
```
