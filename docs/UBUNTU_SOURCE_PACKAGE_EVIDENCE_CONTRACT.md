# Ubuntu Source Package Evidence Contract

Status: no-effect source package evidence contract
Scope: evidence schema for a future reviewed Ubuntu source package transcript.

## Purpose

This contract defines the evidence required before a future Ubuntu source package can be treated as publication input.

It does not run `dpkg-source`, `dpkg-buildpackage -S`, `debuild -S`, `debsign`, `dput`, `lintian`, `sbuild`, or `pbuilder`. It does not create a source package, sign artifacts, upload to Launchpad, create a PPA, submit to Ubuntu, publish a package, or claim archive readiness.

## Required Inputs

```text
ubuntu_package_notice_promotion_gate_contract_present=1
ubuntu_package_license_promotion_gate_contract_present=1
ubuntu_lintian_static_metadata_contract_present=1
ubuntu_local_deb_build_transcript_acceptance_gate_contract_present=1
local_deb_build_transcript_accepted=1
```

## Required Evidence Before Promotion

```text
source_package_build_environment_recorded=1
dpkg_source_command_recorded=1
dpkg_buildpackage_source_command_recorded=1
source_package_created=1
source_package_name_recorded=1
source_package_digest_recorded=1
dsc_path_recorded=1
dsc_digest_recorded=1
changes_file_path_recorded=1
changes_file_digest_recorded=1
orig_tarball_path_recorded=1
orig_tarball_digest_recorded=1
debian_source_format_verified=1
source_package_payload_reviewed=1
source_package_notice_requirements_reviewed=1
ubuntu_source_package_evidence_unblocked=1
```

## Current State

```text
ubuntu_source_package_evidence_contract_present=1
ubuntu_source_package_evidence_status=blocked-pending-accepted-build-transcript
local_deb_build_transcript_accepted=0
source_package_build_environment_recorded=0
dpkg_source_command_recorded=0
dpkg_buildpackage_source_command_recorded=0
dpkg_source_run=0
dpkg_buildpackage_source_run=0
source_package_created=0
source_package_name_recorded=0
source_package_digest_recorded=0
dsc_path_recorded=0
dsc_digest_recorded=0
changes_file_path_recorded=0
changes_file_digest_recorded=0
orig_tarball_path_recorded=0
orig_tarball_digest_recorded=0
debian_source_format_verified=0
source_package_payload_reviewed=0
source_package_notice_requirements_reviewed=0
ubuntu_source_package_evidence_unblocked=0
debsign_command_recorded=0
dput_command_recorded=0
launchpad_upload_run=0
source_package_uploaded=0
ubuntu_upload_signing_authority_evidence_contract_present=1
ubuntu_upload_signing_authority_evidence_status=blocked-pending-source-package-evidence
ubuntu_upload_signing_authority_evidence_unblocked=0
ppa_claimed=0
ubuntu_archive_ready=0
ubuntu_publication_ready=0
production_installer_ready=0
root_installer_ready=0
```

## Relationship To Publication

The Ubuntu PPA/archive publication gate must not unblock until this source package evidence contract is unblocked alongside install/remove evidence, upload authority, signing evidence, Launchpad evidence, and non-claim review.

This contract is intentionally closed today. It records the future source package evidence shape without creating, signing, uploading, or publishing artifacts.

The Ubuntu upload/signing authority evidence contract is downstream of this contract and remains blocked until source package evidence is unblocked.

## Non-Claims

This contract does not claim source package creation, source package correctness, source package upload readiness, PPA readiness, Launchpad build success, Ubuntu archive readiness, Ubuntu sponsorship, Canonical endorsement, package publication readiness, production installer readiness, daily-driver readiness, root installer readiness, or release readiness.

## Validation

Run:

```sh
sh scripts/test-ubuntu-source-package-evidence-contract.sh
```

Expected output:

```text
ubuntu_source_package_evidence_contract: ok
```
