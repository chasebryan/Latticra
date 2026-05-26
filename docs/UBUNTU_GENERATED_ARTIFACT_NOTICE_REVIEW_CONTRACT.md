# Ubuntu Generated-Artifact Notice Review Contract

Status: no-effect generated-artifact notice review contract
Scope: define generated-artifact notice evidence required before the Ubuntu local deb notice review can be promoted.

## Purpose

This contract turns the Ubuntu local deb generated-artifact notice blocker into a concrete review checklist.

It does not build artifacts, inspect a built deb, decide notice obligations, create a `NOTICE` file, update `packaging/ubuntu/debian/copyright`, publish a package, submit to Ubuntu, or provide legal advice.

## Current Inputs

```text
package_scope=local-deb-draft
binary_payload=usr/bin/latticra
binary_payload_source=src/latticra_cli.c
doc_payload=usr/share/doc/latticra/README.md
doc_payload_source=README.md
generated_artifact_notice_policy_present=1
ubuntu_package_notice_inventory_present=1
ubuntu_package_notice_inventory_report_present=1
ubuntu_doc_payload_license_review_contract_present=1
ubuntu_third_party_material_review_contract_present=1
ubuntu_notice_file_decision_contract_present=1
ubuntu_debian_copyright_notice_mapping_contract_present=1
ubuntu_package_notice_review_contract_present=1
deb_artifact_created=0
package_build_performed=0
package_publish_performed=0
```

The current Ubuntu local deb draft has packaging metadata only. No deb artifact, changes file, build log, or installed package payload has been produced for notice review.

## Required Review Before Promotion

```text
generated_artifact_notice_reviewed=1
generated_artifact_notice_requirements_recorded=1
binary_payload_generation_path_reviewed=1
doc_payload_generation_path_reviewed=1
deb_artifact_notice_requirements_recorded=1
changes_file_notice_requirements_recorded=1
build_log_notice_requirements_recorded=1
installed_payload_notice_requirements_recorded=1
generated_artifact_missing_notice_entries=0
```

## Current Decision

```text
ubuntu_generated_artifact_notice_review_contract_present=1
ubuntu_generated_artifact_notice_review_status=blocked-pending-generated-artifact-notice-review
generated_artifact_notice_reviewed=0
generated_artifact_notice_requirements_recorded=0
binary_payload_generation_path_reviewed=0
doc_payload_generation_path_reviewed=0
deb_artifact_notice_requirements_recorded=0
changes_file_notice_requirements_recorded=0
build_log_notice_requirements_recorded=0
installed_payload_notice_requirements_recorded=0
generated_artifact_missing_notice_entries=0
deb_artifact_created=0
package_build_performed=0
package_publish_performed=0
ubuntu_package_notice_review_unblocked=0
ubuntu_package_license_review_unblocked=0
ubuntu_lintian_static_metadata_unblocked=0
ubuntu_local_deb_build_transcript_unblocked=0
```

## Relationship To Notice Review

The Ubuntu package notice review may not be promoted until generated-artifact notice requirements are reviewed for the current local deb payload and any future build artifacts.

The NOTICE file decision remains separate, but it must also be resolved before the Ubuntu package notice review can be promoted.

The Debian copyright notice mapping remains separate, but it must also be resolved before the Ubuntu package notice review can be promoted.

This contract is scoped to the Ubuntu local deb draft. It is not evidence that an artifact exists, that an artifact is distributable, or that release notices are complete.

## Non-Claims

This contract is not legal advice. It does not claim generated-artifact notice compliance, Ubuntu archive readiness, PPA readiness, Canonical endorsement, package publication readiness, production installer readiness, or release readiness.

## Validation

Run:

```sh
sh scripts/test-ubuntu-generated-artifact-notice-review-contract.sh
```

Expected output:

```text
ubuntu_generated_artifact_notice_review_contract: ok
```
