# Ubuntu Package License Promotion Gate Contract

Status: no-effect package license promotion gate contract
Scope: aggregate the Ubuntu package license prerequisites that must be reviewed before lintian/static metadata or local deb build transcript evidence can advance.

## Purpose

This contract turns the Ubuntu package license promotion boundary into a single guarded gate.

It does not promote the license review, relicense files, update `packaging/ubuntu/debian/copyright`, run lintian, build a package, publish a package, submit to Ubuntu, or provide legal advice.

## Required Inputs

```text
license_policy_present=1
license_migration_plan_present=1
ubuntu_package_notice_promotion_gate_contract_present=1
ubuntu_package_notice_review_contract_present=1
ubuntu_package_license_review_contract_present=1
```

## Required Gate Before Promotion

```text
root_license_state_reviewed=1
cli_payload_spdx_reviewed=1
doc_payload_license_reviewed=1
documentation_license_decision_present=1
third_party_notice_reviewed=1
debian_copyright_format_reviewed=1
candidate_expression_accepted=1
packaging_license_expression_updated=1
license_expression_reviewed=1
license_expression_unresolved=0
ubuntu_lintian_static_metadata_unblocked=1
ubuntu_local_deb_build_transcript_unblocked=1
```

## Current Gate State

```text
ubuntu_package_license_promotion_gate_contract_present=1
ubuntu_package_license_promotion_gate_status=blocked-pending-package-license-prerequisites
ubuntu_package_notice_promotion_gate_contract_present=1
ubuntu_package_notice_promotion_gate_status=blocked-pending-package-notice-prerequisites
ubuntu_package_license_review_contract_present=1
ubuntu_package_license_review_status=blocked-pending-formal-review
ubuntu_lintian_static_metadata_contract_present=1
ubuntu_lintian_static_metadata_status=blocked-pending-package-license-promotion
ubuntu_package_notice_review_unblocked=0
ubuntu_package_license_review_unblocked=0
license_expression_candidate_recorded=1
license_expression_reviewed=0
license_expression_unresolved=1
packaging_license_expression_updated=0
ubuntu_lintian_static_metadata_unblocked=0
ubuntu_local_deb_build_transcript_unblocked=0
```

## Relationship To Lintian And Build Evidence

The Ubuntu static metadata lint lane and local deb build transcript evidence may not advance until this gate records that the package notice gate is unblocked, the package license review is complete, the packaging license expression is updated, and license expression review is no longer unresolved.

The Ubuntu lintian static metadata contract records the next evidence schema while keeping lintian execution blocked behind this gate.

This gate is a coordination record for the current local deb draft. It is not a package publication claim or a compliance certification.

## Non-Claims

This contract is not legal advice. It does not claim license-compliance completion, Ubuntu archive readiness, PPA readiness, Canonical endorsement, package publication readiness, production installer readiness, or release readiness.

## Validation

Run:

```sh
sh scripts/test-ubuntu-package-license-promotion-gate-contract.sh
```

Expected output:

```text
ubuntu_package_license_promotion_gate_contract: ok
```
