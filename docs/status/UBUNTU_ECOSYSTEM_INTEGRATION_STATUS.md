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
ubuntu_package_license_review_status=resolved-license-expression-recorded
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
ubuntu_package_notice_promotion_gate_contract_present=1
ubuntu_package_notice_promotion_gate_status=blocked-pending-package-notice-prerequisites
ubuntu_package_license_promotion_gate_contract_present=1
ubuntu_package_license_promotion_gate_status=blocked-pending-package-notice-prerequisites
ubuntu_lintian_static_metadata_contract_present=1
ubuntu_lintian_static_metadata_status=blocked-pending-package-license-promotion
ubuntu_local_deb_build_transcript_acceptance_gate_contract_present=1
ubuntu_local_deb_build_transcript_acceptance_gate_status=blocked-pending-lintian-static-metadata-and-build-transcript
ubuntu_local_deb_install_remove_evidence_contract_present=1
ubuntu_local_deb_install_remove_evidence_status=blocked-pending-accepted-build-transcript
ubuntu_source_package_evidence_contract_present=1
ubuntu_source_package_evidence_status=blocked-pending-accepted-build-transcript
ubuntu_upload_signing_authority_evidence_contract_present=1
ubuntu_upload_signing_authority_evidence_status=blocked-pending-source-package-evidence
ubuntu_launchpad_build_result_evidence_contract_present=1
ubuntu_launchpad_build_result_evidence_status=blocked-pending-upload-signing-authority-evidence
ubuntu_publication_non_claim_review_contract_present=1
ubuntu_publication_non_claim_review_status=blocked-pending-launchpad-build-result-evidence
ubuntu_ppa_archive_publication_promotion_blocker_matrix_contract_present=1
ubuntu_publication_promotion_blocker_matrix_contract_present=1
publication_promotion_blocker_matrix_state=blocked-no-effect
ubuntu_ppa_archive_publication_evidence_intake_denial_contract_present=1
ubuntu_publication_evidence_intake_denial_contract_present=1
ubuntu_ppa_archive_publication_evidence_intake_denial_review_contract_present=1
ubuntu_publication_evidence_intake_denial_review_contract_present=1
publication_evidence_intake_denial_state=denied-no-effect
publication_evidence_intake_denial_review_state=reviewed-upheld-no-effect
publication_evidence_denial_review_present=1
publication_evidence_denial_review_decision=uphold-denial
publication_evidence_denial_re_request_allowed=0
ubuntu_publication_evidence_intake_allowed=0
ubuntu_publication_evidence_intake_requested=0
ubuntu_publication_evidence_intake_denied=1
ubuntu_publication_evidence_intake_denial_upheld=1
ubuntu_publication_transcript_intake_accepted=0
ubuntu_ppa_creation_evidence_accepted=0
ubuntu_launchpad_publication_evidence_accepted=0
ubuntu_archive_submission_evidence_accepted=0
ubuntu_ppa_archive_publication_gate_contract_present=1
ubuntu_ppa_archive_publication_gate_status=blocked-pending-install-remove-evidence
ubuntu_package_notice_review_contract_present=1
ubuntu_package_notice_review_status=blocked-pending-notice-review
license_expression_candidate_recorded=1
license_expression_reviewed=1
license_expression_unresolved=0
documentation_license_decision_present=1
doc_payload_license_reviewed=1
doc_payload_license_unresolved=0
doc_payload_license_decision_recorded=1
debian_copyright_doc_payload_mapping_reviewed=1
debian_copyright_binary_payload_mapping_reviewed=0
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
deb_removed_from_host=0
lintian_static_metadata_run=0
lintian_static_metadata_findings_classified=0
lintian_expected_draft_findings_classified=0
lintian_unexpected_findings_classified=0
build_transcript_acceptance_gate_open=0
build_transcript_acceptance_gate_unblocked=0
local_deb_build_transcript_accepted=0
transcript_header_reviewed=0
tooling_evidence_reviewed=0
package_evidence_reviewed=0
build_evidence_reviewed=0
payload_evidence_reviewed=0
non_claims_reviewed=0
install_remove_test_environment_recorded=0
install_command_recorded=0
install_exit_status_recorded=0
installed_payload_listing_recorded=0
usr_bin_latticra_installed=0
status_command_after_install_recorded=0
remove_command_recorded=0
remove_exit_status_recorded=0
post_remove_absence_checked=0
residual_payload_reviewed=0
install_remove_findings_classified=0
host_mutation_scope_reviewed=0
ubuntu_install_remove_evidence_unblocked=0
source_package_created=0
source_package_build_environment_recorded=0
dpkg_source_command_recorded=0
dpkg_buildpackage_source_command_recorded=0
dpkg_source_run=0
dpkg_buildpackage_source_run=0
source_package_name_recorded=0
source_package_digest_recorded=0
dsc_path_recorded=0
dsc_digest_recorded=0
changes_file_path_recorded=0
upload_target_recorded=0
upload_target_kind_recorded=0
upload_authority_reviewed=0
launchpad_account_recorded=0
ppa_or_archive_target_reviewed=0
orig_tarball_path_recorded=0
orig_tarball_digest_recorded=0
debian_source_format_verified=0
source_package_payload_reviewed=0
source_package_notice_requirements_reviewed=0
ubuntu_source_package_evidence_unblocked=0
gpg_signing_key_fingerprint_recorded=0
upload_command_non_claims_reviewed=0
ubuntu_upload_signing_authority_evidence_unblocked=0
ubuntu_launchpad_build_result_evidence_unblocked=0
debsign_command_recorded=0
signature_fingerprint_recorded=0
dput_command_recorded=0
upload_exit_status_recorded=0
launchpad_upload_url_recorded=0
launchpad_build_log_recorded=0
launchpad_build_result_recorded=0
launchpad_build_result_reviewed=0
launchpad_binary_artifact_listing_recorded=0
launchpad_expected_findings_classified=0
launchpad_unexpected_findings_classified=0
launchpad_publication_non_claims_reviewed=0
publication_scope_recorded=0
publication_target_type_recorded=0
publication_claims_reviewed=0
ppa_claim_absence_reviewed=0
ubuntu_archive_claim_absence_reviewed=0
canonical_endorsement_absence_reviewed=0
sponsorship_claim_absence_reviewed=0
production_installer_claim_absence_reviewed=0
root_installer_claim_absence_reviewed=0
publication_readiness_non_claims_reviewed=0
publication_non_claims_reviewed=0
ubuntu_publication_non_claim_review_unblocked=0
ubuntu_publication_promotion_blocker_matrix_unblocked=0
ubuntu_publication_promotion_blocked=1
ubuntu_platform_publication_evidence_accepted=0
publication_transcript_intake_accepted=0
ppa_creation_evidence_accepted=0
launchpad_publication_evidence_accepted=0
ubuntu_archive_submission_evidence_accepted=0
ubuntu_publication_result_promoted=0
ubuntu_publication_gate_unblocked=0
ppa_created=0
launchpad_upload_run=0
source_package_uploaded=0
ubuntu_archive_submission_claimed=0
ubuntu_publication_ready=0
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
packaging_license_expression_updated=1
ubuntu_package_license_review_unblocked=1
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
docs/UBUNTU_PACKAGE_LICENSE_PROMOTION_GATE_CONTRACT.md
docs/UBUNTU_LINTIAN_STATIC_METADATA_CONTRACT.md
docs/UBUNTU_PACKAGE_NOTICE_REVIEW_CONTRACT.md
docs/UBUNTU_PACKAGE_LICENSE_REVIEW_CONTRACT.md
docs/UBUNTU_LOCAL_DEB_BUILD_TRANSCRIPT_CONTRACT.md
docs/UBUNTU_LOCAL_DEB_BUILD_TRANSCRIPT_ACCEPTANCE_GATE_CONTRACT.md
docs/UBUNTU_LOCAL_DEB_INSTALL_REMOVE_EVIDENCE_CONTRACT.md
docs/UBUNTU_SOURCE_PACKAGE_EVIDENCE_CONTRACT.md
docs/UBUNTU_UPLOAD_SIGNING_AUTHORITY_EVIDENCE_CONTRACT.md
docs/UBUNTU_LAUNCHPAD_BUILD_RESULT_EVIDENCE_CONTRACT.md
docs/UBUNTU_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md
docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md
docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_CONTRACT.md
docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_EVIDENCE_INTAKE_DENIAL_REVIEW_CONTRACT.md
docs/UBUNTU_PPA_ARCHIVE_PUBLICATION_GATE_CONTRACT.md
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
scripts/test-ubuntu-package-license-promotion-gate-contract.sh
scripts/test-ubuntu-lintian-static-metadata-contract.sh
scripts/test-ubuntu-package-notice-review-contract.sh
scripts/test-ubuntu-package-license-review-contract.sh
scripts/test-ubuntu-local-deb-build-transcript-contract.sh
scripts/test-ubuntu-local-deb-build-transcript-acceptance-gate-contract.sh
scripts/test-ubuntu-local-deb-install-remove-evidence-contract.sh
scripts/test-ubuntu-source-package-evidence-contract.sh
scripts/test-ubuntu-upload-signing-authority-evidence-contract.sh
scripts/test-ubuntu-launchpad-build-result-evidence-contract.sh
scripts/test-ubuntu-publication-non-claim-review-contract.sh
scripts/test-ubuntu-ppa-archive-publication-promotion-blocker-matrix-contract.sh
scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-contract.sh
scripts/test-ubuntu-ppa-archive-publication-evidence-intake-denial-review-contract.sh
scripts/test-ubuntu-ppa-archive-publication-gate-contract.sh
.github/workflows/ubuntu-package-notice-inventory.yml
.github/workflows/ubuntu-doc-payload-license-review-contract.yml
.github/workflows/ubuntu-third-party-material-review-contract.yml
.github/workflows/ubuntu-generated-artifact-notice-review-contract.yml
.github/workflows/ubuntu-notice-file-decision-contract.yml
.github/workflows/ubuntu-debian-copyright-notice-mapping-contract.yml
.github/workflows/ubuntu-trademark-notice-boundary-contract.yml
.github/workflows/ubuntu-release-artifact-notice-requirements-contract.yml
.github/workflows/ubuntu-package-notice-promotion-gate-contract.yml
.github/workflows/ubuntu-package-license-promotion-gate-contract.yml
.github/workflows/ubuntu-lintian-static-metadata-contract.yml
.github/workflows/ubuntu-package-notice-review-contract.yml
.github/workflows/ubuntu-local-deb-build-transcript-acceptance-gate-contract.yml
.github/workflows/ubuntu-local-deb-install-remove-evidence-contract.yml
.github/workflows/ubuntu-source-package-evidence-contract.yml
.github/workflows/ubuntu-upload-signing-authority-evidence-contract.yml
.github/workflows/ubuntu-launchpad-build-result-evidence-contract.yml
.github/workflows/ubuntu-publication-non-claim-review-contract.yml
.github/workflows/ubuntu-ppa-archive-publication-promotion-blocker-matrix-contract.yml
.github/workflows/ubuntu-ppa-archive-publication-evidence-intake-denial-contract.yml
.github/workflows/ubuntu-ppa-archive-publication-evidence-intake-denial-review-contract.yml
.github/workflows/ubuntu-ppa-archive-publication-gate-contract.yml
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

The local deb build transcript contract is intentionally blocked from evidence promotion until notice, lintian, build, and install/remove evidence gates are satisfied.

The Ubuntu package license review contract now records the current source facts, accepts the AGPL-3.0-or-later plus CC-BY-4.0 payload expression, and maps it into the local Debian copyright draft while broader notice review remains blocked.

The Ubuntu doc payload license review contract records that `README.md` is included in the local deb documentation payload under CC-BY-4.0.

The Ubuntu third-party material review contract records that source, license, compatibility, and notice-requirement records still need formal review before package notice promotion.

The Ubuntu generated-artifact notice review contract records that generated-artifact notice requirements still need formal review before any deb artifact or build evidence can promote package notice status.

The Ubuntu NOTICE file decision contract records that the package still needs a reviewed decision about whether a `NOTICE` file is required and how it would be mapped into the local deb payload.

The Ubuntu Debian copyright notice mapping contract records that the local deb payload still needs a reviewed mapping into `packaging/ubuntu/debian/copyright` before package notice promotion.

The Ubuntu trademark notice boundary contract records that package metadata still needs a reviewed trademark, project-identity, and endorsement boundary before package notice promotion.

The Ubuntu release artifact notice requirements contract records that source package, deb artifact, `.changes`, build-log, installed-payload, and release-notes notice requirements still need review before package notice promotion.

The Ubuntu package notice promotion gate records the aggregate blocked state across all package notice prerequisites before package license promotion can proceed.

The Ubuntu package license promotion gate records the aggregate blocked state across package notice and package license prerequisites before lintian/static metadata or build transcript evidence can proceed.

The Ubuntu lintian static metadata contract records the future lintian/static metadata evidence shape while keeping lintian execution and build transcript evidence blocked.

The Ubuntu local deb build transcript acceptance gate records that no future local build transcript can be accepted until lintian/static metadata, package license promotion, transcript evidence, payload evidence, and non-claims are reviewed.

The Ubuntu local deb install/remove evidence contract records the future install/remove evidence shape while keeping package install commands, package remove commands, host mutation, and install/remove evidence promotion blocked.

The Ubuntu source package evidence contract records the future `.dsc`, source package, `.changes`, and digest evidence shape while keeping `dpkg-source`, source package creation, signing, upload, and publication blocked.

The Ubuntu upload/signing authority evidence contract records the future upload target, Launchpad account, signing key, `debsign`, and `dput` evidence shape while keeping signing, upload, and publication blocked.

The Ubuntu Launchpad build result evidence contract records the future Launchpad upload URL, build log, build result, binary artifact listing, findings classification, and publication non-claim review shape while keeping Launchpad upload, build-result promotion, and publication blocked.

The Ubuntu publication non-claim review contract records the future PPA, Ubuntu archive, sponsorship, Canonical endorsement, production installer, and root installer non-claim review shape while keeping publication promotion blocked.

The Ubuntu PPA/archive publication promotion blocker matrix records the aggregate blocked state across package review, local build, install/remove, source package, upload/signing, Launchpad build result, and publication non-claim columns before publication evidence can be accepted.

The Ubuntu publication evidence intake denial contract records that PPA creation, archive submission, Launchpad publication evidence, and publication transcript intake remain denied while the publication promotion blocker matrix is closed.

The Ubuntu publication evidence intake denial review contract records that the denial is reviewed and upheld while publication evidence re-requests remain blocked.

The Ubuntu PPA/archive publication gate records the future upload, signing, Launchpad, and archive-submission evidence shape while keeping `debsign`, `dput`, PPA creation, Launchpad upload, Ubuntu archive submission, and publication readiness blocked.

The Ubuntu package notice inventory records the current local-deb draft payload facts without promoting the review. The Ubuntu package notice review contract records the remaining notice obligations that must be settled before package promotion can proceed.

## Next Recommended Lane

```text
Review the Ubuntu publication evidence intake denial disposition before any reviewed PPA/archive publication evidence denial can be closed or re-requested.
```
