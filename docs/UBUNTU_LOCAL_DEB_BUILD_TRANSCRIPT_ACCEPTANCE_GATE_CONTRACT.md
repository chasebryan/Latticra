# Ubuntu Local Deb Build Transcript Acceptance Gate Contract

Status: no-effect local deb build transcript acceptance gate contract
Scope: aggregate the evidence required before a future Ubuntu local deb build transcript can be accepted.

## Purpose

This contract turns the Ubuntu local deb build transcript acceptance boundary into a single guarded gate.

It does not run `dpkg-buildpackage`, `debuild`, `lintian`, `sbuild`, or `pbuilder`. It does not create, install, publish, upload, or accept a deb package.

## Required Inputs

```text
ubuntu_local_deb_build_transcript_contract_present=1
ubuntu_lintian_static_metadata_contract_present=1
ubuntu_package_license_promotion_gate_contract_present=1
ubuntu_lintian_static_metadata_unblocked=1
ubuntu_local_deb_build_transcript_unblocked=1
```

## Required Evidence Before Acceptance

```text
ubuntu_local_deb_build_transcript_present=1
transcript_header_reviewed=1
tooling_evidence_reviewed=1
package_evidence_reviewed=1
build_evidence_reviewed=1
payload_evidence_reviewed=1
non_claims_reviewed=1
deb_artifact_digest_recorded=1
changes_file_digest_recorded=1
build_log_digest_recorded=1
lintian_output_digest_recorded=1
expected_draft_findings_classified=1
unexpected_findings_classified=1
build_transcript_acceptance_gate_unblocked=1
local_deb_build_transcript_accepted=1
```

## Current Gate State

```text
ubuntu_local_deb_build_transcript_acceptance_gate_contract_present=1
ubuntu_local_deb_build_transcript_acceptance_gate_status=blocked-pending-lintian-static-metadata-and-build-transcript
ubuntu_local_deb_build_transcript_present=0
build_transcript_acceptance_gate_open=0
build_transcript_acceptance_gate_unblocked=0
local_deb_build_transcript_accepted=0
transcript_header_reviewed=0
tooling_evidence_reviewed=0
package_evidence_reviewed=0
build_evidence_reviewed=0
payload_evidence_reviewed=0
non_claims_reviewed=0
deb_artifact_created=0
deb_artifact_installed=0
deb_installed_on_host=0
deb_removed_from_host=0
ubuntu_lintian_static_metadata_unblocked=0
ubuntu_local_deb_build_transcript_unblocked=0
ubuntu_local_deb_install_remove_evidence_contract_present=1
ubuntu_local_deb_install_remove_evidence_status=blocked-pending-accepted-build-transcript
ppa_claimed=0
ubuntu_archive_ready=0
production_installer_ready=0
```

## Relationship To Build Evidence

The Ubuntu local deb build transcript contract defines the fields a future transcript must contain. This gate records the separate acceptance decision for that transcript after lintian/static metadata and package license promotion have been reviewed.

This contract is intentionally closed today. It is not evidence that a build transcript exists, that a deb artifact exists, or that a package is installable.

The Ubuntu local deb install/remove evidence contract remains separate and blocked until a reviewed local deb build transcript is accepted.

## Non-Claims

This contract does not claim build success, lintian success, install success, Debian Policy compliance, Ubuntu archive readiness, PPA readiness, Canonical endorsement, package publication readiness, production installer readiness, or release readiness.

## Validation

Run:

```sh
sh scripts/test-ubuntu-local-deb-build-transcript-acceptance-gate-contract.sh
```

Expected output:

```text
ubuntu_local_deb_build_transcript_acceptance_gate_contract: ok
```
