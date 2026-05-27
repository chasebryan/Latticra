# Ubuntu PPA Archive Publication Gate Contract

Status: no-effect PPA/archive publication gate contract
Scope: evidence schema for future Ubuntu PPA upload or Ubuntu archive submission review.

## Purpose

This contract defines the evidence required before any future Ubuntu PPA upload, Launchpad build, Ubuntu archive submission, or publication-readiness claim can be accepted.

It does not run `debsign`, `dput`, `dpkg-buildpackage`, `debuild`, `lintian`, `sbuild`, or `pbuilder`. It does not create a source package, sign artifacts, upload to Launchpad, create a PPA, submit to Ubuntu, publish a package, or claim archive readiness.

## Required Inputs

```text
ubuntu_package_notice_promotion_gate_contract_present=1
ubuntu_package_license_promotion_gate_contract_present=1
ubuntu_lintian_static_metadata_contract_present=1
ubuntu_local_deb_build_transcript_acceptance_gate_contract_present=1
ubuntu_local_deb_install_remove_evidence_contract_present=1
ubuntu_source_package_evidence_contract_present=1
ubuntu_source_package_evidence_unblocked=1
ubuntu_upload_signing_authority_evidence_contract_present=1
ubuntu_upload_signing_authority_evidence_unblocked=1
ubuntu_install_remove_evidence_unblocked=1
local_deb_build_transcript_accepted=1
deb_artifact_created=1
deb_artifact_digest_recorded=1
```

## Required Evidence Before Publication Promotion

```text
source_package_created=1
source_package_digest_recorded=1
dsc_digest_recorded=1
changes_file_digest_recorded=1
upload_target_recorded=1
upload_authority_reviewed=1
debsign_command_recorded=1
signature_fingerprint_recorded=1
dput_command_recorded=1
upload_exit_status_recorded=1
launchpad_build_log_recorded=1
launchpad_build_result_reviewed=1
publication_non_claims_reviewed=1
ubuntu_publication_gate_unblocked=1
```

## Current State

```text
ubuntu_ppa_archive_publication_gate_contract_present=1
ubuntu_ppa_archive_publication_gate_status=blocked-pending-install-remove-evidence
ubuntu_source_package_evidence_contract_present=1
ubuntu_source_package_evidence_status=blocked-pending-accepted-build-transcript
ubuntu_source_package_evidence_unblocked=0
ubuntu_upload_signing_authority_evidence_contract_present=1
ubuntu_upload_signing_authority_evidence_status=blocked-pending-source-package-evidence
ubuntu_upload_signing_authority_evidence_unblocked=0
ubuntu_install_remove_evidence_unblocked=0
local_deb_build_transcript_accepted=0
deb_artifact_created=0
deb_artifact_digest_recorded=0
source_package_created=0
source_package_digest_recorded=0
dsc_digest_recorded=0
changes_file_digest_recorded=0
upload_target_recorded=0
upload_authority_reviewed=0
debsign_command_recorded=0
signature_fingerprint_recorded=0
dput_command_recorded=0
upload_exit_status_recorded=0
launchpad_build_log_recorded=0
launchpad_build_result_reviewed=0
publication_non_claims_reviewed=0
ubuntu_publication_gate_unblocked=0
ppa_created=0
ppa_claimed=0
launchpad_upload_run=0
ubuntu_archive_submission_claimed=0
ubuntu_archive_ready=0
ubuntu_publication_ready=0
production_installer_ready=0
root_installer_ready=0
```

## Relationship To Install Remove Evidence

The Ubuntu source package evidence contract, upload/signing authority evidence contract, and local deb install/remove evidence contract must be unblocked before this publication gate can advance. Publication evidence is downstream of notice, license, lintian/static metadata, build transcript acceptance, source package evidence, payload review, install evidence, remove evidence, upload authority, signing evidence, Launchpad evidence, and non-claim review.

This contract is intentionally closed today. It records the future evidence shape without signing artifacts, uploading artifacts, creating a PPA, submitting to Ubuntu, or publishing a package.

## Non-Claims

This contract does not claim PPA readiness, Launchpad build success, Ubuntu archive readiness, Ubuntu upload rights, Ubuntu sponsorship, Canonical endorsement, package publication readiness, production installer readiness, daily-driver readiness, root installer readiness, or release readiness.

## Validation

Run:

```sh
sh scripts/test-ubuntu-ppa-archive-publication-gate-contract.sh
```

Expected output:

```text
ubuntu_ppa_archive_publication_gate_contract: ok
```
