# Ubuntu Upload Signing Authority Evidence Contract

Status: no-effect upload/signing authority evidence contract
Scope: evidence schema for future Ubuntu upload target, signing key, and upload authority review.

## Purpose

This contract defines the evidence required before any future Ubuntu source package upload command can be treated as publication input.

It does not run `debsign`, `dput`, `dpkg-source`, `dpkg-buildpackage -S`, `debuild -S`, `lintian`, `sbuild`, or `pbuilder`. It does not sign artifacts, upload to Launchpad, create a PPA, submit to Ubuntu, publish a package, or claim archive readiness.

## Required Inputs

```text
ubuntu_source_package_evidence_contract_present=1
ubuntu_source_package_evidence_unblocked=1
source_package_created=1
dsc_digest_recorded=1
changes_file_digest_recorded=1
```

## Required Evidence Before Promotion

```text
upload_target_recorded=1
upload_target_kind_recorded=1
upload_authority_reviewed=1
launchpad_account_recorded=1
ppa_or_archive_target_reviewed=1
gpg_signing_key_fingerprint_recorded=1
signature_fingerprint_recorded=1
debsign_command_recorded=1
dput_command_recorded=1
upload_command_non_claims_reviewed=1
ubuntu_upload_signing_authority_evidence_unblocked=1
```

## Current State

```text
ubuntu_upload_signing_authority_evidence_contract_present=1
ubuntu_upload_signing_authority_evidence_status=blocked-pending-source-package-evidence
ubuntu_source_package_evidence_unblocked=0
source_package_created=0
dsc_digest_recorded=0
changes_file_digest_recorded=0
upload_target_recorded=0
upload_target_kind_recorded=0
upload_authority_reviewed=0
launchpad_account_recorded=0
ppa_or_archive_target_reviewed=0
gpg_signing_key_fingerprint_recorded=0
signature_fingerprint_recorded=0
debsign_command_recorded=0
dput_command_recorded=0
upload_command_non_claims_reviewed=0
upload_exit_status_recorded=0
launchpad_upload_run=0
source_package_uploaded=0
ubuntu_upload_signing_authority_evidence_unblocked=0
ppa_created=0
ppa_claimed=0
ubuntu_archive_submission_claimed=0
ubuntu_archive_ready=0
ubuntu_publication_ready=0
production_installer_ready=0
root_installer_ready=0
```

## Relationship To Publication

The Ubuntu PPA/archive publication gate must not unblock until this upload/signing authority evidence contract is unblocked alongside source package evidence, install/remove evidence, Launchpad build evidence, and non-claim review.

This contract is intentionally closed today. It records the future upload authority and signing evidence shape without signing, uploading, or publishing artifacts.

## Non-Claims

This contract does not claim upload authorization, signing authority, source package upload readiness, PPA readiness, Launchpad build success, Ubuntu archive readiness, Ubuntu sponsorship, Canonical endorsement, package publication readiness, production installer readiness, daily-driver readiness, root installer readiness, or release readiness.

## Validation

Run:

```sh
sh scripts/test-ubuntu-upload-signing-authority-evidence-contract.sh
```

Expected output:

```text
ubuntu_upload_signing_authority_evidence_contract: ok
```
