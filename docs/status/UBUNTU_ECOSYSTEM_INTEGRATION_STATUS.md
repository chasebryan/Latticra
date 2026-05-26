# Ubuntu Ecosystem Integration Status

Status: Ubuntu integration status record
Date: 2026-05-26

## Summary

Latticra now has an Ubuntu-facing compatibility lane for development, Panel prerequisites, and a local-only deb packaging draft.

This is an ecosystem integration checkpoint, not a production readiness claim.

## Current Evidence

```text
ubuntu_build_lane_present=1
ubuntu_developer_workflow_present=1
ubuntu_panel_prerequisites_documented=1
ubuntu_quickstart_documented=1
ubuntu_local_deb_draft_present=1
ubuntu_static_deb_validation_present=1
ubuntu_lintian_availability_present=1
ubuntu_local_deb_build_transcript_contract_present=1
ubuntu_local_deb_build_transcript_present=0
deb_artifact_created=0
deb_installed_on_host=0
ubuntu_package_license_review_contract_present=1
ubuntu_package_license_review_status=blocked-pending-formal-review
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
ubuntu_package_notice_review_contract_present=1
ubuntu_package_notice_review_status=blocked-pending-doc-license-and-notice-review
license_expression_candidate_recorded=1
license_expression_reviewed=0
license_expression_unresolved=1
documentation_license_decision_present=0
doc_payload_license_reviewed=0
doc_payload_license_unresolved=1
doc_payload_license_decision_recorded=0
debian_copyright_doc_payload_mapping_reviewed=0
debian_copyright_binary_payload_mapping_reviewed=0
debian_copyright_third_party_notice_mapping_reviewed=0
debian_copyright_generated_artifact_notice_mapping_reviewed=0
debian_copyright_notice_file_mapping_reviewed=0
debian_copyright_trademark_notice_boundary_reviewed=0
debian_copyright_license_ref_replaced_or_justified=0
trademark_notice_boundary_recorded=0
trademark_policy_applied_to_package_notice=0
package_description_endorsement_boundary_reviewed=0
documentation_trademark_boundary_reviewed=0
canonical_endorsement_boundary_reviewed=0
project_identity_downstream_use_boundary_recorded=0
third_party_material_inventory_recorded=1
third_party_material_inventory_reviewed=0
third_party_material_source_records_present=0
third_party_material_license_records_present=0
third_party_material_compatibility_notes_present=0
generated_artifact_notice_reviewed=0
generated_artifact_notice_requirements_recorded=0
binary_payload_generation_path_reviewed=0
doc_payload_generation_path_reviewed=0
deb_artifact_notice_requirements_recorded=0
changes_file_notice_requirements_recorded=0
build_log_notice_requirements_recorded=0
installed_payload_notice_requirements_recorded=0
release_artifact_notice_requirements_recorded=0
source_package_notice_requirements_recorded=0
release_notes_notice_requirements_recorded=0
third_party_notice_reviewed=0
third_party_notice_requirements_recorded=0
notice_file_present=0
notice_file_decision_recorded=0
notice_file_required_decision_recorded=0
notice_file_content_requirements_recorded=0
notice_file_install_path_reviewed=0
notice_file_packaging_mapping_reviewed=0
notice_file_absence_justification_recorded=0
debian_copyright_notice_mapping_reviewed=0
ubuntu_package_notice_review_unblocked=0
packaging_license_expression_updated=0
ubuntu_package_license_review_unblocked=0
ubuntu_lintian_static_metadata_unblocked=0
ubuntu_local_deb_build_transcript_unblocked=0
ppa_claimed=0
ubuntu_archive_ready=0
canonical_endorsement_claimed=0
production_installer_ready=0
root_installer_ready=0
```

## Guarded Files

```text
docs/UBUNTU_READINESS_PLAN.md
docs/UBUNTU_DEVELOPER_WORKFLOW.md
docs/UBUNTU_LOCAL_DEB_STATIC_VALIDATION.md
docs/UBUNTU_LINTIAN_AVAILABILITY.md
docs/UBUNTU_PACKAGE_NOTICE_INVENTORY.md
docs/UBUNTU_DOC_PAYLOAD_LICENSE_REVIEW_CONTRACT.md
docs/UBUNTU_THIRD_PARTY_MATERIAL_REVIEW_CONTRACT.md
docs/UBUNTU_GENERATED_ARTIFACT_NOTICE_REVIEW_CONTRACT.md
docs/UBUNTU_NOTICE_FILE_DECISION_CONTRACT.md
docs/UBUNTU_DEBIAN_COPYRIGHT_NOTICE_MAPPING_CONTRACT.md
docs/UBUNTU_TRADEMARK_NOTICE_BOUNDARY_CONTRACT.md
docs/UBUNTU_RELEASE_ARTIFACT_NOTICE_REQUIREMENTS_CONTRACT.md
docs/UBUNTU_PACKAGE_NOTICE_PROMOTION_GATE_CONTRACT.md
docs/UBUNTU_PACKAGE_NOTICE_REVIEW_CONTRACT.md
docs/UBUNTU_PACKAGE_LICENSE_REVIEW_CONTRACT.md
docs/UBUNTU_LOCAL_DEB_BUILD_TRANSCRIPT_CONTRACT.md
packaging/ubuntu/README.md
packaging/ubuntu/debian/control
packaging/ubuntu/debian/rules
packaging/ubuntu/debian/changelog
packaging/ubuntu/debian/copyright
packaging/ubuntu/debian/install
packaging/ubuntu/debian/source/format
scripts/test-ubuntu-build-lane.sh
scripts/test-ubuntu-developer-workflow.sh
scripts/test-ubuntu-local-deb-static-validation.sh
scripts/test-ubuntu-lintian-availability.sh
scripts/ubuntu-package-notice-inventory.sh
scripts/test-ubuntu-package-notice-inventory.sh
scripts/test-ubuntu-doc-payload-license-review-contract.sh
scripts/test-ubuntu-third-party-material-review-contract.sh
scripts/test-ubuntu-generated-artifact-notice-review-contract.sh
scripts/test-ubuntu-notice-file-decision-contract.sh
scripts/test-ubuntu-debian-copyright-notice-mapping-contract.sh
scripts/test-ubuntu-trademark-notice-boundary-contract.sh
scripts/test-ubuntu-release-artifact-notice-requirements-contract.sh
scripts/test-ubuntu-package-notice-promotion-gate-contract.sh
scripts/test-ubuntu-package-notice-review-contract.sh
scripts/test-ubuntu-package-license-review-contract.sh
scripts/test-ubuntu-local-deb-build-transcript-contract.sh
.github/workflows/ubuntu-package-notice-inventory.yml
.github/workflows/ubuntu-doc-payload-license-review-contract.yml
.github/workflows/ubuntu-third-party-material-review-contract.yml
.github/workflows/ubuntu-generated-artifact-notice-review-contract.yml
.github/workflows/ubuntu-notice-file-decision-contract.yml
.github/workflows/ubuntu-debian-copyright-notice-mapping-contract.yml
.github/workflows/ubuntu-trademark-notice-boundary-contract.yml
.github/workflows/ubuntu-release-artifact-notice-requirements-contract.yml
.github/workflows/ubuntu-package-notice-promotion-gate-contract.yml
.github/workflows/ubuntu-package-notice-review-contract.yml
```

## Public Entry Points

Ubuntu setup and package posture are now linked from:

```text
README.md
docs/QUICK_START_CHEATSHEET.md
installer/README.md
docs/status/README.md
```

## Current Boundary

The Ubuntu lane does not publish a package, create a PPA, claim Ubuntu archive readiness, install a root service, change systemd, change the kernel, add a privileged helper, grant network authority, or claim production readiness.

The local deb build transcript contract is intentionally blocked from evidence promotion until the package license expression is reviewed.

The Ubuntu package license review contract now records the current source facts and candidate expression, but it keeps packaging metadata at `LicenseRef-Latticra-TBD` until formal review accepts the source and documentation scope.

The Ubuntu doc payload license review contract records that `README.md` is included in the local deb documentation payload while the repository documentation-license decision remains unresolved.

The Ubuntu third-party material review contract records that source, license, compatibility, and notice-requirement records still need formal review before package notice promotion.

The Ubuntu generated-artifact notice review contract records that generated-artifact notice requirements still need formal review before any deb artifact or build evidence can promote package notice status.

The Ubuntu NOTICE file decision contract records that the package still needs a reviewed decision about whether a `NOTICE` file is required and how it would be mapped into the local deb payload.

The Ubuntu Debian copyright notice mapping contract records that the local deb payload still needs a reviewed mapping into `packaging/ubuntu/debian/copyright` before package notice promotion.

The Ubuntu trademark notice boundary contract records that package metadata still needs a reviewed trademark, project-identity, and endorsement boundary before package notice promotion.

The Ubuntu release artifact notice requirements contract records that source package, deb artifact, `.changes`, build-log, installed-payload, and release-notes notice requirements still need review before package notice promotion.

The Ubuntu package notice promotion gate records the aggregate blocked state across all package notice prerequisites before package license promotion can proceed.

The Ubuntu package notice inventory records the current local-deb draft payload facts without promoting the review. The Ubuntu package notice review contract records the unresolved documentation-license and notice obligations that must be settled before the package license review can be promoted.

## Next Recommended Lane

```text
Review the Ubuntu package notice promotion gate contract, then promote the Ubuntu package notice review only after documentation licensing, third-party notices, generated-artifact notices, NOTICE requirements, Debian copyright mapping, trademark boundaries, and release-artifact notices are decided.
```
