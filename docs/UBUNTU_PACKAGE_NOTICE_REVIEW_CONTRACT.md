# Ubuntu Package Notice Review Contract

Status: no-effect notice and documentation-license review contract
Scope: define notice, attribution, and documentation-license evidence required before Ubuntu package license promotion.

## Purpose

This contract defines the missing notice and documentation-license review layer for the Ubuntu local deb draft.

It does not create a `NOTICE` file, decide the documentation license, change `packaging/ubuntu/debian/copyright`, publish a package, create a PPA, submit to Ubuntu, or provide legal advice.

## Current Inputs

```text
license_policy_present=1
license_migration_plan_present=1
third_party_material_policy_present=1
generated_artifact_notice_policy_present=1
ubuntu_package_notice_inventory_present=1
ubuntu_package_notice_inventory_report_present=1
ubuntu_doc_payload_license_review_contract_present=1
ubuntu_doc_payload_license_review_status=blocked-pending-formal-doc-license-decision
third_party_material_inventory_recorded=1
notice_file_present=0
documentation_license_decision_present=0
```

The current Ubuntu package draft intends to include:

```text
binary_payload=usr/bin/latticra
binary_payload_source=src/latticra_cli.c
doc_payload=usr/share/doc/latticra/README.md
doc_payload_source=README.md
```

## Required Notice Review Before License Promotion

```text
doc_payload_license_decision_recorded=1
doc_payload_license_compatible_with_package=1
third_party_material_inventory_reviewed=1
third_party_material_missing_entries=0
generated_artifact_notice_reviewed=1
notice_file_decision_recorded=1
debian_copyright_notice_mapping_reviewed=1
trademark_notice_boundary_recorded=1
release_artifact_notice_requirements_recorded=1
```

## Current Decision

```text
ubuntu_package_notice_review_contract_present=1
ubuntu_package_notice_review_status=blocked-pending-doc-license-and-notice-review
ubuntu_package_notice_inventory_present=1
ubuntu_package_notice_inventory_report_present=1
ubuntu_doc_payload_license_review_contract_present=1
ubuntu_doc_payload_license_review_status=blocked-pending-formal-doc-license-decision
doc_payload_license_reviewed=0
doc_payload_license_unresolved=1
doc_payload_license_decision_recorded=0
third_party_material_inventory_recorded=1
third_party_material_inventory_reviewed=0
generated_artifact_notice_reviewed=0
third_party_notice_reviewed=0
notice_file_decision_recorded=0
debian_copyright_notice_mapping_reviewed=0
ubuntu_package_license_review_unblocked=0
ubuntu_lintian_static_metadata_unblocked=0
ubuntu_local_deb_build_transcript_unblocked=0
```

## Relationship To License Review

The Ubuntu package license review contract may record candidate expressions, but it must remain blocked until this notice review contract is promoted by a reviewed documentation-license and notice decision.

The Ubuntu package notice inventory report records current payload facts and open notice obligations, but it does not unblock this review by itself.

The Ubuntu doc payload license review contract records the unresolved `README.md` documentation-license decision required before this notice review can be promoted.

## Non-Claims

This contract is not legal advice. It does not claim license-compliance completion, Ubuntu archive readiness, PPA readiness, Canonical endorsement, production installer readiness, package publication readiness, or release readiness.

## Validation

Run:

```sh
sh scripts/test-ubuntu-package-notice-review-contract.sh
```

Expected output:

```text
ubuntu_package_notice_review_contract: ok
```
