# Ubuntu Package License Review Contract

Status: no-effect package license review contract
Scope: define the exact license-review evidence required before the Ubuntu local deb draft can replace `LicenseRef-Latticra-TBD`.

## Purpose

This contract turns the Ubuntu package license blocker into a concrete review checklist.

It does not change the repository license, relicense files, update `packaging/ubuntu/debian/copyright`, publish a package, create a PPA, submit to Ubuntu, or provide legal advice.

## Current Inputs

```text
root_license_file=LICENSE
root_license_current=Apache-2.0
license_policy_present=1
license_migration_plan_present=1
new_software_direction=AGPL-3.0-or-later
no_silent_relicensing=1
documentation_license_decision_present=0
```

The current no-effect CLI payload input is:

```text
cli_payload_source=src/latticra_cli.c
cli_payload_spdx_present=1
cli_payload_spdx=AGPL-3.0-or-later
```

The current local deb draft also records README documentation as an intended package payload:

```text
doc_payload_source=README.md
doc_payload_license_reviewed=0
doc_payload_license_unresolved=1
```

## Candidate Expressions

These are review candidates, not release claims:

```text
candidate_binary_payload_license=AGPL-3.0-or-later
candidate_doc_payload_license=Apache-2.0-or-docs-decision-pending
candidate_source_package_license=AGPL-3.0-or-later AND Apache-2.0
candidate_expression_recorded=1
candidate_expression_applied_to_packaging=0
```

The candidate expression must not be applied to Ubuntu packaging metadata until a reviewed decision accepts the package source scope, documentation scope, and notice obligations.

The current notice-review dependency is:

```text
ubuntu_package_notice_inventory_present=1
ubuntu_package_notice_inventory_report_present=1
ubuntu_doc_payload_license_review_contract_present=1
ubuntu_doc_payload_license_review_status=blocked-pending-formal-doc-license-decision
ubuntu_third_party_material_review_contract_present=1
ubuntu_third_party_material_review_status=blocked-pending-third-party-material-review
ubuntu_generated_artifact_notice_review_contract_present=1
ubuntu_generated_artifact_notice_review_status=blocked-pending-generated-artifact-notice-review
ubuntu_notice_file_decision_contract_present=1
ubuntu_notice_file_decision_status=blocked-pending-notice-file-decision
ubuntu_debian_copyright_notice_mapping_contract_present=1
ubuntu_debian_copyright_notice_mapping_status=blocked-pending-debian-copyright-notice-mapping
ubuntu_trademark_notice_boundary_contract_present=1
ubuntu_trademark_notice_boundary_status=blocked-pending-trademark-notice-boundary
ubuntu_release_artifact_notice_requirements_contract_present=1
ubuntu_release_artifact_notice_requirements_status=blocked-pending-release-artifact-notice-requirements
ubuntu_package_notice_promotion_gate_contract_present=1
ubuntu_package_notice_promotion_gate_status=blocked-pending-package-notice-prerequisites
ubuntu_package_license_promotion_gate_contract_present=1
ubuntu_package_license_promotion_gate_status=blocked-pending-package-license-prerequisites
ubuntu_package_notice_review_contract_present=1
ubuntu_package_notice_review_status=blocked-pending-doc-license-and-notice-review
ubuntu_package_license_review_unblocked=0
```

## Required Review Before Promotion

```text
root_license_state_reviewed=1
cli_payload_spdx_reviewed=1
doc_payload_license_reviewed=1
documentation_license_decision_present=1
third_party_notice_reviewed=1
debian_copyright_format_reviewed=1
candidate_expression_accepted=1
packaging_license_expression_updated=1
```

## Current Decision

```text
ubuntu_package_license_review_contract_present=1
ubuntu_package_license_review_status=blocked-pending-formal-review
ubuntu_doc_payload_license_review_contract_present=1
ubuntu_doc_payload_license_review_status=blocked-pending-formal-doc-license-decision
ubuntu_third_party_material_review_contract_present=1
ubuntu_third_party_material_review_status=blocked-pending-third-party-material-review
ubuntu_generated_artifact_notice_review_contract_present=1
ubuntu_generated_artifact_notice_review_status=blocked-pending-generated-artifact-notice-review
ubuntu_notice_file_decision_contract_present=1
ubuntu_notice_file_decision_status=blocked-pending-notice-file-decision
ubuntu_debian_copyright_notice_mapping_contract_present=1
ubuntu_debian_copyright_notice_mapping_status=blocked-pending-debian-copyright-notice-mapping
ubuntu_trademark_notice_boundary_contract_present=1
ubuntu_trademark_notice_boundary_status=blocked-pending-trademark-notice-boundary
ubuntu_release_artifact_notice_requirements_contract_present=1
ubuntu_release_artifact_notice_requirements_status=blocked-pending-release-artifact-notice-requirements
ubuntu_package_notice_promotion_gate_contract_present=1
ubuntu_package_notice_promotion_gate_status=blocked-pending-package-notice-prerequisites
ubuntu_package_license_promotion_gate_contract_present=1
ubuntu_package_license_promotion_gate_status=blocked-pending-package-license-prerequisites
ubuntu_package_notice_review_contract_present=1
ubuntu_package_notice_review_status=blocked-pending-doc-license-and-notice-review
license_expression_candidate_recorded=1
license_expression_reviewed=0
license_expression_unresolved=1
packaging_license_expression_updated=0
ubuntu_lintian_static_metadata_unblocked=0
ubuntu_local_deb_build_transcript_unblocked=0
```

## Relationship To Ubuntu Lanes

The Ubuntu lintian availability lane may run because it only proves tool availability.

The Ubuntu static metadata lint lane and local deb build transcript evidence remain blocked until this contract is promoted by a reviewed packaging-license decision.

The Ubuntu package license promotion gate aggregates this contract with the package notice promotion gate before static lint or build transcript evidence can advance.

## Non-Claims

This contract is not legal advice. It does not claim Ubuntu archive readiness, PPA readiness, Canonical endorsement, production installer readiness, package publication readiness, or license-compliance completion.

## Validation

Run:

```sh
sh scripts/test-ubuntu-package-license-review-contract.sh
```

Expected output:

```text
ubuntu_package_license_review_contract: ok
```
