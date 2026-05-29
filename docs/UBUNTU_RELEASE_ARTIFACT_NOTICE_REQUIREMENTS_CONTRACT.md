# Ubuntu Release Artifact Notice Requirements Contract

Status: no-effect release artifact notice requirements contract
Scope: define release-artifact notice evidence required before the Ubuntu package notice review can be promoted.

## Purpose

This contract turns the Ubuntu local deb release-artifact notice blocker into a concrete review checklist.

It does not build a deb, create a `.changes` file, create a build log, install a package, publish a package, create release notes, submit to Ubuntu, or provide legal advice.

## Current Inputs

```text
package_scope=local-deb-draft
binary_payload=usr/bin/latticra
binary_payload_source=src/latticra_cli.c
doc_payload=usr/share/doc/latticra/README.md
doc_payload_source=README.md
deb_artifact_created=0
changes_file_created=0
build_log_created=0
package_installed_for_notice_review=0
package_publish_performed=0
ubuntu_package_notice_inventory_present=1
ubuntu_doc_payload_license_review_contract_present=1
ubuntu_third_party_material_review_contract_present=1
ubuntu_generated_artifact_notice_review_contract_present=1
ubuntu_notice_file_decision_contract_present=1
ubuntu_debian_copyright_notice_mapping_contract_present=1
ubuntu_trademark_notice_boundary_contract_present=1
ubuntu_package_notice_review_contract_present=1
```

The current Ubuntu local deb draft has no release artifact, no `.changes` file, no build log, and no installed payload evidence for release-artifact notice review.

## Required Requirements Before Promotion

```text
release_artifact_notice_requirements_recorded=1
source_package_notice_requirements_recorded=1
deb_artifact_notice_requirements_recorded=1
changes_file_notice_requirements_recorded=1
build_log_notice_requirements_recorded=1
installed_payload_notice_requirements_recorded=1
release_notes_notice_requirements_recorded=1
release_artifact_missing_notice_entries=0
```

## Current Decision

```text
ubuntu_release_artifact_notice_requirements_contract_present=1
ubuntu_release_artifact_notice_requirements_status=blocked-pending-release-artifact-notice-requirements
release_artifact_notice_requirements_recorded=0
source_package_notice_requirements_recorded=0
deb_artifact_notice_requirements_recorded=0
changes_file_notice_requirements_recorded=0
build_log_notice_requirements_recorded=0
installed_payload_notice_requirements_recorded=0
release_notes_notice_requirements_recorded=0
release_artifact_missing_notice_entries=0
ubuntu_package_notice_review_unblocked=0
ubuntu_package_license_review_unblocked=1
ubuntu_lintian_static_metadata_unblocked=0
ubuntu_local_deb_build_transcript_unblocked=0
```

## Relationship To Notice Review

The Ubuntu package notice review may not be promoted until release-artifact notice requirements are reviewed for the source package, deb artifact, `.changes` file, build log, installed payload, and any release notes or publication material.

This contract is scoped to the Ubuntu local deb draft. It is not evidence that any artifact exists, that any artifact is distributable, or that release notices are complete.

## Non-Claims

This contract is not legal advice. It does not claim release-artifact notice compliance, generated-artifact notice compliance, license-compliance completion, Ubuntu archive readiness, PPA readiness, Canonical endorsement, package publication readiness, production installer readiness, or release readiness.

## Validation

Run:

```sh
sh scripts/test-ubuntu-release-artifact-notice-requirements-contract.sh
```

Expected output:

```text
ubuntu_release_artifact_notice_requirements_contract: ok
```
