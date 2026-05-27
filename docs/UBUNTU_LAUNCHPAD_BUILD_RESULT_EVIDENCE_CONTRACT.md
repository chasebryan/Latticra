# Ubuntu Launchpad Build Result Evidence Contract

Status: no-effect Launchpad build result evidence contract
Scope: evidence schema for future Launchpad upload result and build result review.

## Purpose

This contract defines the evidence required before any future Launchpad build result can be treated as Ubuntu publication input.

It does not run `dput`, `debsign`, `launchpad`, `dpkg-source`, `dpkg-buildpackage`, `debuild`, `lintian`, `sbuild`, or `pbuilder`. It does not upload to Launchpad, create a PPA, submit to Ubuntu, publish a package, or claim archive readiness.

## Required Inputs

```text
ubuntu_source_package_evidence_contract_present=1
ubuntu_source_package_evidence_unblocked=1
ubuntu_upload_signing_authority_evidence_contract_present=1
ubuntu_upload_signing_authority_evidence_unblocked=1
source_package_created=1
source_package_digest_recorded=1
dsc_digest_recorded=1
changes_file_digest_recorded=1
upload_target_recorded=1
upload_authority_reviewed=1
signature_fingerprint_recorded=1
```

## Required Evidence Before Publication Input Promotion

```text
upload_exit_status_recorded=1
source_package_uploaded=1
launchpad_upload_url_recorded=1
launchpad_build_log_recorded=1
launchpad_build_result_recorded=1
launchpad_build_result_reviewed=1
launchpad_binary_artifact_listing_recorded=1
launchpad_expected_findings_classified=1
launchpad_unexpected_findings_classified=1
launchpad_publication_non_claims_reviewed=1
ubuntu_launchpad_build_result_evidence_unblocked=1
```

## Current State

```text
ubuntu_launchpad_build_result_evidence_contract_present=1
ubuntu_launchpad_build_result_evidence_status=blocked-pending-upload-signing-authority-evidence
ubuntu_upload_signing_authority_evidence_unblocked=0
ubuntu_source_package_evidence_unblocked=0
source_package_created=0
source_package_uploaded=0
upload_exit_status_recorded=0
launchpad_upload_run=0
launchpad_upload_url_recorded=0
launchpad_build_log_recorded=0
launchpad_build_result_recorded=0
launchpad_build_result_reviewed=0
launchpad_binary_artifact_listing_recorded=0
launchpad_expected_findings_classified=0
launchpad_unexpected_findings_classified=0
launchpad_publication_non_claims_reviewed=0
ubuntu_launchpad_build_result_evidence_unblocked=0
ppa_created=0
ppa_claimed=0
ubuntu_archive_submission_claimed=0
ubuntu_archive_ready=0
ubuntu_publication_ready=0
production_installer_ready=0
root_installer_ready=0
```

## Relationship To Publication

The Ubuntu PPA/archive publication gate must not unblock until this Launchpad build result evidence contract is unblocked alongside source package evidence, upload/signing authority evidence, install/remove evidence, and non-claim review.

This contract is intentionally closed today. It records the future Launchpad upload URL, build log, build result, binary artifact listing, findings classification, and publication non-claim review shape without running upload commands or publishing artifacts.

## Non-Claims

This contract does not claim upload success, Launchpad build success, PPA readiness, Ubuntu archive readiness, Ubuntu upload rights, Ubuntu sponsorship, Canonical endorsement, package publication readiness, production installer readiness, daily-driver readiness, root installer readiness, or release readiness.

## Validation

Run:

```sh
sh scripts/test-ubuntu-launchpad-build-result-evidence-contract.sh
```

Expected output:

```text
ubuntu_launchpad_build_result_evidence_contract: ok
```
