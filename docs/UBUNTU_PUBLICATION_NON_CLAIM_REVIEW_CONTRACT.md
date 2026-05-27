# Ubuntu Publication Non-Claim Review Contract

Status: no-effect publication non-claim review contract
Scope: evidence schema for future Ubuntu PPA/archive publication claim review.

## Purpose

This contract defines the non-claim evidence required before any future Ubuntu PPA/archive publication gate can treat Launchpad build-result evidence as publication input.

It does not run `dput`, `debsign`, `launchpad`, `dpkg-source`, `dpkg-buildpackage`, `debuild`, `lintian`, `sbuild`, or `pbuilder`. It does not upload to Launchpad, create a PPA, submit to Ubuntu, publish a package, or claim archive readiness.

## Required Inputs

```text
ubuntu_source_package_evidence_contract_present=1
ubuntu_source_package_evidence_unblocked=1
ubuntu_upload_signing_authority_evidence_contract_present=1
ubuntu_upload_signing_authority_evidence_unblocked=1
ubuntu_launchpad_build_result_evidence_contract_present=1
ubuntu_launchpad_build_result_evidence_unblocked=1
source_package_uploaded=1
upload_exit_status_recorded=1
launchpad_upload_url_recorded=1
launchpad_build_log_recorded=1
launchpad_build_result_recorded=1
launchpad_build_result_reviewed=1
launchpad_binary_artifact_listing_recorded=1
launchpad_expected_findings_classified=1
launchpad_unexpected_findings_classified=1
```

## Required Evidence Before Publication Gate Promotion

```text
publication_scope_recorded=1
publication_target_type_recorded=1
publication_claims_reviewed=1
ppa_claim_absence_reviewed=1
ubuntu_archive_claim_absence_reviewed=1
canonical_endorsement_absence_reviewed=1
sponsorship_claim_absence_reviewed=1
production_installer_claim_absence_reviewed=1
root_installer_claim_absence_reviewed=1
publication_readiness_non_claims_reviewed=1
publication_non_claims_reviewed=1
ubuntu_publication_non_claim_review_unblocked=1
```

## Current State

```text
ubuntu_publication_non_claim_review_contract_present=1
ubuntu_publication_non_claim_review_status=blocked-pending-launchpad-build-result-evidence
ubuntu_launchpad_build_result_evidence_unblocked=0
ubuntu_upload_signing_authority_evidence_unblocked=0
ubuntu_source_package_evidence_unblocked=0
source_package_uploaded=0
upload_exit_status_recorded=0
launchpad_upload_url_recorded=0
launchpad_build_log_recorded=0
launchpad_build_result_recorded=0
launchpad_build_result_reviewed=0
launchpad_binary_artifact_listing_recorded=0
launchpad_expected_findings_classified=0
launchpad_unexpected_findings_classified=0
publication_scope_recorded=0
publication_target_type_recorded=0
publication_claims_reviewed=0
ppa_claim_absence_reviewed=0
ubuntu_archive_claim_absence_reviewed=0
canonical_endorsement_absence_reviewed=0
sponsorship_claim_absence_reviewed=0
production_installer_claim_absence_reviewed=0
root_installer_claim_absence_reviewed=0
publication_readiness_non_claims_reviewed=0
publication_non_claims_reviewed=0
ubuntu_publication_non_claim_review_unblocked=0
ubuntu_ppa_archive_publication_promotion_blocker_matrix_contract_present=1
publication_promotion_blocker_matrix_state=blocked-no-effect
ubuntu_publication_promotion_blocker_matrix_unblocked=0
ppa_created=0
ppa_claimed=0
ubuntu_archive_submission_claimed=0
ubuntu_archive_ready=0
ubuntu_publication_ready=0
canonical_endorsement_claimed=0
production_installer_ready=0
root_installer_ready=0
```

## Relationship To Publication

The Ubuntu PPA/archive publication promotion blocker matrix is downstream of this contract and is recorded in `docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md`. The Ubuntu PPA/archive publication gate must not unblock until this publication non-claim review contract is unblocked alongside source package evidence, upload/signing authority evidence, Launchpad build result evidence, install/remove evidence, and package review gates.

This contract is intentionally closed today. It records the future publication-claim review shape without running upload commands, creating publication targets, or publishing artifacts.

## Non-Claims

This contract does not claim PPA readiness, Launchpad build success, Ubuntu archive readiness, Ubuntu upload rights, Ubuntu sponsorship, Canonical endorsement, package publication readiness, production installer readiness, daily-driver readiness, root installer readiness, or release readiness.

## Validation

Run:

```sh
sh scripts/test-ubuntu-publication-non-claim-review-contract.sh
```

Expected output:

```text
ubuntu_publication_non_claim_review_contract: ok
```
