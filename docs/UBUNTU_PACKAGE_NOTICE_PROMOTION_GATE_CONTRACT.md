# Ubuntu Package Notice Promotion Gate Contract

Status: no-effect package notice promotion gate contract
Scope: aggregate the Ubuntu package notice prerequisites that must be reviewed before package license promotion can proceed.

## Purpose

This contract turns the Ubuntu package notice promotion boundary into a single guarded gate.

It does not promote the notice review, decide licenses, create a `NOTICE` file, update Debian copyright metadata, build a package, publish a package, submit to Ubuntu, or provide legal advice.

## Required Inputs

```text
ubuntu_doc_payload_license_review_contract_present=1
ubuntu_third_party_material_review_contract_present=1
ubuntu_generated_artifact_notice_review_contract_present=1
ubuntu_notice_file_decision_contract_present=1
ubuntu_debian_copyright_notice_mapping_contract_present=1
ubuntu_trademark_notice_boundary_contract_present=1
ubuntu_release_artifact_notice_requirements_contract_present=1
ubuntu_package_notice_review_contract_present=1
```

## Required Gate Before Promotion

```text
doc_payload_license_decision_recorded=1
third_party_material_inventory_reviewed=1
generated_artifact_notice_reviewed=1
notice_file_decision_recorded=1
debian_copyright_notice_mapping_reviewed=1
trademark_notice_boundary_recorded=1
release_artifact_notice_requirements_recorded=1
ubuntu_package_notice_review_unblocked=1
ubuntu_package_license_review_unblocked=1
```

## Current Gate State

```text
ubuntu_package_notice_promotion_gate_contract_present=1
ubuntu_package_notice_promotion_gate_status=blocked-pending-package-notice-prerequisites
doc_payload_license_decision_recorded=1
third_party_material_inventory_reviewed=0
generated_artifact_notice_reviewed=0
notice_file_decision_recorded=0
debian_copyright_notice_mapping_reviewed=0
trademark_notice_boundary_recorded=0
release_artifact_notice_requirements_recorded=0
ubuntu_package_notice_review_unblocked=0
ubuntu_package_license_review_unblocked=1
ubuntu_lintian_static_metadata_unblocked=0
ubuntu_local_deb_build_transcript_unblocked=0
```

## Relationship To Package License Review

The Ubuntu package license review may not advance until this gate records that all package notice prerequisites are reviewed and the package notice review is unblocked.

This gate is a coordination record for the current local deb draft. It is not a package publication claim or a compliance certification.

## Non-Claims

This contract is not legal advice. It does not claim NOTICE compliance, license-compliance completion, Ubuntu archive readiness, PPA readiness, Canonical endorsement, package publication readiness, production installer readiness, or release readiness.

## Validation

Run:

```sh
sh scripts/test-ubuntu-package-notice-promotion-gate-contract.sh
```

Expected output:

```text
ubuntu_package_notice_promotion_gate_contract: ok
```
