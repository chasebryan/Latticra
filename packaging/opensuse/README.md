# openSUSE Packaging Draft

Status: local-only packaging draft

This directory contains openSUSE-oriented packaging experiments and maintenance records for Latticra.

The current spec and `.changes` metadata are a local-only draft used by static guards. They are not an official openSUSE package, not SUSE endorsement evidence, not Open Build Service publication evidence, not a submit-request record, not a local `osc build` result, not a `rpmlint` result, and not package-readiness evidence.

## Where this fits

- Documentation hub: [`../../docs/README.md`](../../docs/README.md)
- openSUSE workflow: [`../../docs/OPENSUSE_DEVELOPER_WORKFLOW.md`](../../docs/OPENSUSE_DEVELOPER_WORKFLOW.md)
- openSUSE readiness plan: [`../../docs/OPENSUSE_READINESS_PLAN.md`](../../docs/OPENSUSE_READINESS_PLAN.md)
- Current status: [`../../docs/status/CURRENT_STATUS.md`](../../docs/status/CURRENT_STATUS.md)

Current guarded files:

```text
packaging/opensuse/README.md
packaging/opensuse/latticra.spec
packaging/opensuse/latticra.changes
docs/OPENSUSE_READINESS_PLAN.md
docs/OPENSUSE_DEVELOPER_WORKFLOW.md
docs/OPENSUSE_LOCAL_RPM_STATIC_VALIDATION.md
docs/OPENSUSE_RPMLINT_OSC_AVAILABILITY.md
docs/OPENSUSE_RPMLINT_STATIC_SPEC_LANE.md
docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md
docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md
docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md
docs/OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md
docs/OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md
docs/OPENSUSE_OBS_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md
docs/OPENSUSE_RPM_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md
docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
scripts/test-opensuse-developer-workflow.sh
scripts/test-opensuse-local-rpm-static-validation.sh
scripts/test-opensuse-rpmlint-osc-availability.sh
scripts/test-opensuse-rpmlint-static-spec-lane.sh
scripts/test-opensuse-rpmlint-findings-classification.sh
scripts/test-opensuse-source-archive-reproducibility-contract.sh
scripts/test-opensuse-source-archive-fixture-lane.sh
scripts/test-opensuse-rpm-topdir-handoff-lane.sh
scripts/test-opensuse-local-rpm-build-gate-contract.sh
scripts/test-opensuse-local-rpm-build-environment-contract.sh
scripts/test-opensuse-rpm-artifact-naming-contract.sh
scripts/test-opensuse-rpm-payload-inspection-contract.sh
scripts/test-opensuse-rpm-install-remove-transcript-contract.sh
scripts/test-opensuse-obs-publication-non-claim-review-contract.sh
scripts/test-opensuse-rpm-validation-promotion-blocker-matrix-contract.sh
scripts/test-opensuse-rpm-build-evidence-intake-denial-contract.sh
.github/workflows/opensuse-developer-workflow.yml
.github/workflows/opensuse-local-rpm-static-validation.yml
.github/workflows/opensuse-rpmlint-osc-availability.yml
.github/workflows/opensuse-rpmlint-static-spec-lane.yml
.github/workflows/opensuse-rpmlint-findings-classification.yml
.github/workflows/opensuse-source-archive-reproducibility-contract.yml
.github/workflows/opensuse-source-archive-fixture-lane.yml
.github/workflows/opensuse-rpm-topdir-handoff-lane.yml
.github/workflows/opensuse-local-rpm-build-gate-contract.yml
.github/workflows/opensuse-local-rpm-build-environment-contract.yml
.github/workflows/opensuse-rpm-artifact-naming-contract.yml
.github/workflows/opensuse-rpm-payload-inspection-contract.yml
.github/workflows/opensuse-rpm-install-remove-transcript-contract.yml
.github/workflows/opensuse-obs-publication-non-claim-review-contract.yml
.github/workflows/opensuse-rpm-validation-promotion-blocker-matrix-contract.yml
.github/workflows/opensuse-rpm-build-evidence-intake-denial-contract.yml
```

The static lane preserves:

```text
local_only_draft=1
opensuse_maintenance_lane_present=1
opensuse_rpmlint_osc_availability_lane_present=1
opensuse_rpmlint_static_spec_lane_present=1
opensuse_rpmlint_findings_classification_present=1
opensuse_source_archive_reproducibility_contract_present=1
opensuse_source_archive_fixture_lane_present=1
opensuse_rpm_topdir_handoff_lane_present=1
opensuse_local_rpm_build_gate_contract_present=1
opensuse_local_rpm_build_environment_contract_present=1
opensuse_rpm_artifact_naming_contract_present=1
opensuse_rpm_payload_inspection_contract_present=1
opensuse_rpm_install_remove_transcript_contract_present=1
opensuse_obs_publication_non_claim_review_contract_present=1
opensuse_rpm_validation_promotion_blocker_matrix_contract_present=1
opensuse_rpm_build_evidence_intake_denial_contract_present=1
temporary_rpm_topdir_handoff_lane_present=1
opensuse_rpm_build_gate_state=closed-no-effect
opensuse_rpm_build_environment_contract_state=specified-no-effect
opensuse_rpm_artifact_naming_contract_state=specified-no-effect
opensuse_rpm_payload_inspection_contract_state=specified-no-effect
opensuse_rpm_install_remove_transcript_contract_state=specified-no-effect
validation_promotion_blocker_matrix_state=blocked-no-effect
build_evidence_intake_denial_state=denied-no-effect
rpm_artifact_naming_contract_present=1
rpm_install_remove_transcript_contract_present=1
obs_publication_non_claim_review_contract_present=1
rpm_validation_promotion_blocker_matrix_contract_present=1
rpm_build_evidence_intake_denial_contract_present=1
publication_non_claim_review_contract_present=1
obs_publication_non_claim_review_present=1
publication_non_claim_review_present=1
payload_inspection_contract_present=1
payload_inspection_contract_state=specified-no-effect
install_remove_transcript_contract_state=specified-no-effect
opensuse_clean_build_environment_documented=1
opensuse_build_environment_provisioned=0
osc_build_environment_provisioned=0
explicit_operator_build_authorization=0
environment_transcript_present=0
rpmbuild_allowed=0
osc_build_allowed=0
spec_cleaner_allowed=0
rpm_artifact_created=0
rpmbuild_run_required=0
rpmbuild_run=0
rpmbuild_ba_run=0
rpmbuild_bb_run=0
rpmbuild_bs_run=0
osc_build_run=0
accepted_rpmlint_transcript_present=0
expected_draft_findings_count_recorded=0
unexpected_findings_count_recorded=0
source_archive_policy_recorded=1
source_archive_transcript_present=1
source_archive_created=1
source_archive_sha256_recorded=1
source_archive_reproducible=1
source_archive_generated_twice=1
source_archive_repeated_sha256_match=1
source_archive_accepted_for_build=0
temporary_rpm_topdir_created=1
temporary_rpm_sources_archive_staged=1
temporary_rpm_specs_spec_staged=1
temporary_rpm_specs_changes_staged=1
temporary_rpm_source_sha256_preserved=1
temporary_rpm_source_listing_preserved=1
rpm_source_artifact_name_pattern_recorded=1
rpm_binary_artifact_name_pattern_recorded=1
rpm_source_package_name=latticra-0.0.0-0.local.src.rpm
rpm_binary_package_name_pattern=latticra-0.0.0-0.local.${RPM_ARCH}.rpm
repository_rpm_artifact_write_allowed=0
source_rpm_artifact_created=0
binary_rpm_artifact_created=0
rpm_artifact_sha256_recorded=0
rpm_payload_expected_bin=/usr/bin/latticra
rpm_payload_expected_doc=/usr/share/doc/packages/latticra/README.md
source_rpm_payload_inspection_run=0
binary_rpm_payload_inspection_run=0
rpm_payload_inspection_run=0
rpm_payload_accepted=0
rpm_install_remove_transcript_present=0
rpm_install_remove_disposable_environment_required=1
rpm_package_install_run=0
rpm_package_remove_run=0
rpm_zypper_install_run=0
rpm_zypper_remove_run=0
rpm_cli_install_run=0
rpm_cli_remove_run=0
rpm_removed_from_host=0
host_install_allowed=0
host_remove_allowed=0
host_mutation_allowed=0
service_state_change_allowed=0
rpm_validation_result_promoted=0
opensuse_rpm_validation_result_promoted=0
opensuse_rpm_validation_promotion_blocked=1
opensuse_platform_build_evidence_accepted=0
opensuse_source_archive_accepted_for_build=0
opensuse_rpmlint_transcript_accepted=0
opensuse_rpm_artifact_created=0
opensuse_payload_inspection_run=0
opensuse_install_remove_transcript_present=0
opensuse_obs_publication_non_claim_review_present=1
rpmlint_run=0
opensuse_build_evidence_intake_allowed=0
opensuse_build_evidence_intake_requested=0
opensuse_build_evidence_intake_denied=1
build_transcript_intake_accepted=0
rpm_build_transcript_intake_accepted=0
opensuse_build_transcript_intake_accepted=0
rpmbuild_evidence_accepted=0
osc_build_evidence_accepted=0
rpmlint_evidence_accepted=0
source_rpm_evidence_accepted=0
binary_rpm_evidence_accepted=0
opensuse_rpmbuild_evidence_accepted=0
opensuse_osc_build_evidence_accepted=0
opensuse_rpmlint_evidence_accepted=0
opensuse_source_rpm_evidence_accepted=0
opensuse_binary_rpm_evidence_accepted=0
rpm_build_lane_opened=0
opensuse_single_platform_build_lane_opened=0
obs_project_created=0
obs_package_created=0
obs_repository_created=0
obs_source_link_created=0
osc_branch_run=0
osc_commit_run=0
osc_submitreq_run=0
osc_request_accepted=0
obs_build_result_claimed=0
spec_cleaner_run=0
rpmlint_package_readiness_claimed=0
package_readiness_claimed=0
opensuse_obs_publication_claimed=0
opensuse_submit_request_claimed=0
opensuse_official_package_claimed=0
suse_endorsement_claimed=0
opensuse_factory_submission_claimed=0
opensuse_factory_acceptance_claimed=0
opensuse_leap_submission_claimed=0
production_readiness_claimed=0
```

The local RPM build environment contract is recorded in [`../../docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md`](../../docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md). It documents the disposable openSUSE build environment requirement while keeping `opensuse_build_environment_provisioned=0`, `explicit_operator_build_authorization=0`, `environment_transcript_present=0`, and all openSUSE build commands disabled.

The RPM artifact naming contract is recorded in [`../../docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md`](../../docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md). It records future `latticra-0.0.0-0.local.src.rpm` and `latticra-0.0.0-0.local.${RPM_ARCH}.rpm` names while keeping `repository_rpm_artifact_write_allowed=0`, `rpm_artifact_created=0`, and `rpm_artifact_sha256_recorded=0`.

The RPM payload inspection contract is recorded in [`../../docs/OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md`](../../docs/OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md). It records expected source RPM and binary RPM payload checks while keeping `rpm_payload_inspection_run=0`, `rpm_payload_accepted=0`, and `rpm_artifact_created=0`.

The RPM install/remove transcript contract is recorded in [`../../docs/OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md`](../../docs/OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md). It records future disposable install/remove evidence while keeping `rpm_install_remove_transcript_present=0`, `rpm_package_install_run=0`, `rpm_package_remove_run=0`, and `host_mutation_allowed=0`.

The OBS publication non-claim review contract is recorded in [`../../docs/OPENSUSE_OBS_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md`](../../docs/OPENSUSE_OBS_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md). It records Open Build Service, submit-request, official-package, and SUSE endorsement non-claims while keeping `obs_project_created=0`, `osc_commit_run=0`, `osc_submitreq_run=0`, and `rpm_validation_result_promoted=0`.

The RPM validation promotion blocker matrix is recorded in [`../../docs/OPENSUSE_RPM_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md`](../../docs/OPENSUSE_RPM_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md). It ties source, `rpmlint`, environment, artifact, payload, install/remove, and OBS non-claim columns together while keeping `opensuse_platform_build_evidence_accepted=0`, `opensuse_rpm_validation_promotion_blocked=1`, and `opensuse_rpm_validation_result_promoted=0`.

The RPM build-evidence intake denial contract is recorded in [`../../docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md`](../../docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md). It refuses `rpmbuild`, `osc build`, `rpmlint`, source RPM, binary RPM, and transcript intake while keeping `opensuse_build_evidence_intake_denied=1`, `opensuse_build_transcript_intake_accepted=0`, and `opensuse_rpmbuild_evidence_accepted=0`.

The draft payload remains intentionally narrow:

```text
/usr/bin/latticra
/usr/share/doc/packages/latticra/README.md
```

The CLI reports no-effect status and disabled runtime behavior.

The `.changes` file records local-only openSUSE maintenance history. It is not accepted Open Build Service history, package submission evidence, or production maintenance evidence.
