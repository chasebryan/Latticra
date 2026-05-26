# Ubuntu Third-Party Material Review Contract

Status: no-effect third-party material review contract
Scope: define third-party material evidence required before the Ubuntu local deb notice review can be promoted.

## Purpose

This contract turns the Ubuntu local deb third-party material blocker into a concrete review checklist.

It does not add third-party material, decide license compatibility, update `packaging/ubuntu/debian/copyright`, create a `NOTICE` file, build a package, publish a package, submit to Ubuntu, or provide legal advice.

## Current Inputs

```text
package_scope=local-deb-draft
binary_payload=usr/bin/latticra
binary_payload_source=src/latticra_cli.c
doc_payload=usr/share/doc/latticra/README.md
doc_payload_source=README.md
third_party_material_policy_present=1
ubuntu_package_notice_inventory_present=1
ubuntu_package_notice_inventory_report_present=1
ubuntu_doc_payload_license_review_contract_present=1
ubuntu_generated_artifact_notice_review_contract_present=1
ubuntu_package_notice_review_contract_present=1
```

The current inventory records the third-party material posture but does not complete review.

## Required Review Before Promotion

```text
third_party_material_inventory_reviewed=1
third_party_material_missing_entries=0
third_party_material_source_records_present=1
third_party_material_license_records_present=1
third_party_material_compatibility_notes_present=1
binary_payload_third_party_material_reviewed=1
doc_payload_third_party_material_reviewed=1
packaging_metadata_third_party_material_reviewed=1
third_party_notice_requirements_recorded=1
```

## Current Decision

```text
ubuntu_third_party_material_review_contract_present=1
ubuntu_third_party_material_review_status=blocked-pending-third-party-material-review
third_party_material_inventory_recorded=1
third_party_material_inventory_reviewed=0
third_party_material_missing_entries=0
third_party_material_source_records_present=0
third_party_material_license_records_present=0
third_party_material_compatibility_notes_present=0
binary_payload_third_party_material_reviewed=0
doc_payload_third_party_material_reviewed=0
packaging_metadata_third_party_material_reviewed=0
third_party_notice_reviewed=0
third_party_notice_requirements_recorded=0
ubuntu_package_notice_review_unblocked=0
ubuntu_package_license_review_unblocked=0
ubuntu_lintian_static_metadata_unblocked=0
ubuntu_local_deb_build_transcript_unblocked=0
```

## Relationship To Notice Review

The Ubuntu package notice review may not be promoted until third-party material inventory review is complete and any notice requirements are mapped into package metadata.

The generated-artifact notice review remains separate, but it must also be resolved before the Ubuntu package notice review can be promoted.

This contract is scoped to the current Ubuntu local deb draft payload. It is not a repository-wide third-party materials audit.

## Non-Claims

This contract is not legal advice. It does not claim third-party license compliance, Ubuntu archive readiness, PPA readiness, Canonical endorsement, package publication readiness, production installer readiness, or release readiness.

## Validation

Run:

```sh
sh scripts/test-ubuntu-third-party-material-review-contract.sh
```

Expected output:

```text
ubuntu_third_party_material_review_contract: ok
```
