# Ubuntu Package Notice Review Contract

Status: no-effect notice review contract
Scope: define notice, attribution, and package evidence required before Ubuntu package license promotion.

## Purpose

This contract defines the remaining notice review layer for the Ubuntu local deb draft.

It does not create a `NOTICE` file, publish a package, create a PPA, submit to Ubuntu, or provide legal advice.

## Current Inputs

```text
license_policy_present=1
license_migration_plan_present=1
third_party_material_policy_present=1
generated_artifact_notice_policy_present=1
ubuntu_package_notice_inventory_present=1
ubuntu_package_notice_inventory_report_present=1
ubuntu_doc_payload_license_review_contract_present=1
ubuntu_doc_payload_license_review_status=resolved-cc-by-4.0
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
third_party_material_inventory_recorded=1
notice_file_present=0
documentation_license_decision_present=1
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
notice_file_required_decision_recorded=1
notice_file_content_requirements_recorded=1
notice_file_decision_recorded=1
debian_copyright_notice_mapping_reviewed=1
debian_copyright_binary_payload_mapping_reviewed=1
debian_copyright_doc_payload_mapping_reviewed=1
debian_copyright_third_party_notice_mapping_reviewed=1
debian_copyright_generated_artifact_notice_mapping_reviewed=1
debian_copyright_notice_file_mapping_reviewed=1
debian_copyright_trademark_notice_boundary_reviewed=1
debian_copyright_license_ref_replaced_or_justified=1
trademark_notice_boundary_recorded=1
trademark_policy_applied_to_package_notice=1
package_description_endorsement_boundary_reviewed=1
documentation_trademark_boundary_reviewed=1
canonical_endorsement_boundary_reviewed=1
project_identity_downstream_use_boundary_recorded=1
release_artifact_notice_requirements_recorded=1
source_package_notice_requirements_recorded=1
release_notes_notice_requirements_recorded=1
```

## Current Decision

```text
ubuntu_package_notice_review_contract_present=1
ubuntu_package_notice_review_status=blocked-pending-notice-review
ubuntu_package_notice_inventory_present=1
ubuntu_package_notice_inventory_report_present=1
ubuntu_doc_payload_license_review_contract_present=1
ubuntu_doc_payload_license_review_status=resolved-cc-by-4.0
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
doc_payload_license_reviewed=1
doc_payload_license_unresolved=0
doc_payload_license_decision_recorded=1
third_party_material_inventory_recorded=1
third_party_material_inventory_reviewed=0
third_party_notice_requirements_recorded=0
generated_artifact_notice_reviewed=0
generated_artifact_notice_requirements_recorded=0
third_party_notice_reviewed=0
notice_file_present=0
notice_file_decision_recorded=0
notice_file_required_decision_recorded=0
notice_file_content_requirements_recorded=0
debian_copyright_notice_mapping_reviewed=0
debian_copyright_binary_payload_mapping_reviewed=0
debian_copyright_doc_payload_mapping_reviewed=1
debian_copyright_third_party_notice_mapping_reviewed=0
debian_copyright_generated_artifact_notice_mapping_reviewed=0
debian_copyright_notice_file_mapping_reviewed=0
debian_copyright_trademark_notice_boundary_reviewed=0
debian_copyright_license_ref_replaced_or_justified=1
trademark_notice_boundary_recorded=0
trademark_policy_applied_to_package_notice=0
package_description_endorsement_boundary_reviewed=0
documentation_trademark_boundary_reviewed=0
canonical_endorsement_boundary_reviewed=0
project_identity_downstream_use_boundary_recorded=0
release_artifact_notice_requirements_recorded=0
source_package_notice_requirements_recorded=0
release_notes_notice_requirements_recorded=0
ubuntu_package_license_review_unblocked=1
ubuntu_lintian_static_metadata_unblocked=0
ubuntu_local_deb_build_transcript_unblocked=0
```

## Relationship To License Review

The Ubuntu package license review contract records the accepted package expression. Package promotion remains blocked until this notice review contract is promoted by a reviewed notice decision.

The Ubuntu package notice inventory report records current payload facts and open notice obligations, but it does not unblock this review by itself.

The Ubuntu doc payload license review contract records the resolved `README.md` CC-BY-4.0 documentation-license decision required before this notice review can be promoted.

The Ubuntu third-party material review contract records the source, license, compatibility, and notice-requirement evidence required before this notice review can be promoted.

The Ubuntu generated-artifact notice review contract records the generated payload, build artifact, changes-file, build-log, and installed-payload notice evidence required before this notice review can be promoted.

The Ubuntu NOTICE file decision contract records the reviewed decision required before a package can claim NOTICE obligations are satisfied.

The Ubuntu Debian copyright notice mapping contract records the reviewed mapping required before package notice obligations can be represented in `packaging/ubuntu/debian/copyright`.

The Ubuntu trademark notice boundary contract records the reviewed project-identity and endorsement boundary required before package notice obligations can be promoted.

The Ubuntu release artifact notice requirements contract records the reviewed source-package, deb-artifact, changes-file, build-log, installed-payload, and release-notes notice requirements required before package notice obligations can be promoted.

The Ubuntu package notice promotion gate aggregates these prerequisites before package license promotion can proceed.

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
