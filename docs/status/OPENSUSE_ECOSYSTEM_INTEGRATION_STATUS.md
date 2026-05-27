# openSUSE Ecosystem Integration Status

Status: openSUSE integration and maintenance status record
Date: 2026-05-26

## Summary

Latticra now has an openSUSE-facing compatibility and maintenance lane for development, Panel prerequisites, and a local-only RPM packaging draft.

This track has the same purpose as the Fedora and Ubuntu tracks, except its scope is openSUSE integration and maintenance.

This is an ecosystem integration checkpoint, not a production readiness claim.

## Current Evidence

```text
opensuse_developer_workflow_present=1
opensuse_panel_prerequisites_documented=1
opensuse_quickstart_documented=1
opensuse_local_rpm_draft_present=1
opensuse_local_rpm_static_validation_present=1
opensuse_changes_file_present=1
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
opensuse_rpm_build_evidence_intake_denial_review_contract_present=1
opensuse_rpm_build_evidence_intake_denial_disposition_contract_present=1
opensuse_rpm_build_evidence_intake_denial_disposition_closeout_contract_present=1
temporary_rpm_topdir_handoff_lane_present=1
opensuse_rpm_build_gate_state=closed-no-effect
opensuse_rpm_build_environment_contract_state=specified-no-effect
opensuse_rpm_artifact_naming_contract_state=specified-no-effect
opensuse_rpm_payload_inspection_contract_state=specified-no-effect
opensuse_rpm_install_remove_transcript_contract_state=specified-no-effect
validation_promotion_blocker_matrix_state=blocked-no-effect
build_evidence_intake_denial_state=denied-no-effect
build_evidence_intake_denial_review_state=reviewed-upheld-no-effect
build_evidence_intake_denial_disposition_state=closed-upheld-no-effect
build_evidence_intake_denial_disposition_closeout_state=closed-out-upheld-no-effect
rpm_artifact_naming_contract_present=1
rpm_install_remove_transcript_contract_present=1
obs_publication_non_claim_review_contract_present=1
rpm_validation_promotion_blocker_matrix_contract_present=1
rpm_build_evidence_intake_denial_contract_present=1
rpm_build_evidence_intake_denial_review_contract_present=1
rpm_build_evidence_intake_denial_disposition_contract_present=1
rpm_build_evidence_intake_denial_disposition_closeout_contract_present=1
publication_non_claim_review_contract_present=1
obs_publication_non_claim_review_present=1
publication_non_claim_review_present=1
payload_inspection_contract_present=1
payload_inspection_contract_state=specified-no-effect
install_remove_transcript_contract_state=specified-no-effect
opensuse_clean_build_environment_documented=1
opensuse_target_distribution_documented=1
osc_build_environment_documented=1
opensuse_build_environment_provisioned=0
osc_build_environment_provisioned=0
explicit_operator_build_authorization=0
disposable_validation_environment_required=1
disposable_validation_environment_provisioned=0
environment_transcript_present=0
rpmbuild_allowed=0
osc_build_allowed=0
spec_cleaner_allowed=0
rpm_artifact_created=0
rpm_installed_on_host=0
rpmbuild_run=0
rpmbuild_ba_run=0
rpmbuild_bb_run=0
rpmbuild_bs_run=0
osc_build_run=0
accepted_rpmlint_transcript_present=0
expected_draft_findings_count_recorded=0
unexpected_findings_count_recorded=0
classification_decision=blocked-pending-reviewed-rpmlint-output
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
rpm_artifact_published=0
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
denial_review_required_before_re_request=1
denial_review_present=1
denial_review_decision=uphold-denial
denial_disposition_present=1
denial_disposition_decision=close-upheld-denial
denial_disposition_closeout_present=1
denial_disposition_closeout_decision=closeout-upheld-denial
denial_closed=1
denial_archived=0
denial_archive_allowed=0
denial_re_request_allowed=0
opensuse_build_evidence_intake_denial_review_present=1
opensuse_build_evidence_intake_denial_upheld=1
opensuse_build_evidence_intake_denial_disposition_present=1
opensuse_build_evidence_intake_denial_closed=1
opensuse_build_evidence_intake_denial_disposition_closeout_present=1
opensuse_build_evidence_intake_denial_closed_out=1
opensuse_build_evidence_intake_denial_archived=0
opensuse_denial_archive_allowed=0
opensuse_denial_re_request_allowed=0
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
opensuse_distribution_ready=0
production_installer_ready=0
daily_driver_install_ready=0
root_installer_ready=0
```

## Guarded Files

```text
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
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_REVIEW_CONTRACT.md
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CONTRACT.md
docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_CONTRACT.md
docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
packaging/opensuse/README.md
packaging/opensuse/latticra.spec
packaging/opensuse/latticra.changes
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
scripts/test-opensuse-rpm-build-evidence-intake-denial-review-contract.sh
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-contract.sh
scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-closeout-contract.sh
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
.github/workflows/opensuse-rpm-build-evidence-intake-denial-review-contract.yml
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-contract.yml
.github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-closeout-contract.yml
```

## Public Entry Points

openSUSE setup and package posture are linked from:

```text
README.md
docs/QUICK_START_CHEATSHEET.md
installer/README.md
docs/status/README.md
```

## Current Boundary

The openSUSE lane does not publish an RPM, create an Open Build Service project, submit Latticra to openSUSE, claim official package readiness, claim SUSE endorsement, install a root service, change systemd, change the kernel, add a privileged helper, grant network authority, or claim production readiness.

The local openSUSE RPM draft records package shape and maintenance posture only. The `.changes` file is a local maintenance record, not accepted Open Build Service submit-request history.

The openSUSE `rpmlint` and `osc` availability lane verifies tooling in an openSUSE environment only. It does not run `rpmlint` against the Latticra spec yet, run `osc build`, create package artifacts, publish to Open Build Service, or install Latticra on a host.

The openSUSE `rpmlint` static spec lane runs `rpmlint` against the local-only openSUSE spec for audit output only. It does not require a clean lint result, create package artifacts, run `osc build`, publish to Open Build Service, install Latticra, or claim package readiness.

The openSUSE `rpmlint` findings classification record separates expected local-only draft findings from unexpected blockers. It does not accept a transcript, clear findings, create artifacts, or promote package readiness.

The openSUSE source archive reproducibility contract records the expected `Source0` archive shape and evidence required before any package build transcript can be accepted.

The openSUSE source archive fixture lane creates two temporary archive fixtures, compares their SHA-256 values, and inspects the archive listing. It does not create persistent source RPM or binary RPM artifacts, run `rpmbuild`, run `osc build`, publish to Open Build Service, or claim package readiness.

The openSUSE RPM topdir handoff lane stages the verified temporary source archive and local-only spec files into a disposable RPM topdir. It does not run `rpmbuild`, run `osc build`, create source RPM or binary RPM artifacts, publish to Open Build Service, or claim package readiness.

The openSUSE local RPM build gate contract keeps `rpmbuild`, `osc build`, `spec-cleaner`, package artifact creation, host installation, and Open Build Service publication blocked until source acceptance, lint classification, license, notice, BuildRequires, environment, authorization, payload inspection, install/remove, and OBS non-claim evidence exists.

The openSUSE local RPM build environment contract documents disposable openSUSE build environment requirements while keeping environment provisioning, operator authorization, `rpmbuild`, `osc build`, `spec-cleaner`, package artifacts, host installation, and Open Build Service publication disabled.

The openSUSE RPM artifact naming contract records future source RPM and binary RPM names and disposable output boundaries while keeping repository RPM artifact writes, checksum claims, artifact creation, host installation, and Open Build Service publication disabled.

The openSUSE RPM payload inspection contract records future source RPM and binary RPM payload inspection evidence while keeping inspection runs, payload acceptance, RPM artifacts, host installation, and Open Build Service publication disabled.

The openSUSE RPM install/remove transcript contract records future disposable install/remove evidence while keeping install/remove runs, host mutation, RPM artifacts, package readiness, and Open Build Service publication disabled.

The openSUSE OBS publication non-claim review contract records Open Build Service, submit-request, official-package, and SUSE endorsement non-claims while keeping OBS actions, package publication, validation promotion, and readiness disabled.

The openSUSE RPM validation promotion blocker matrix is recorded in `docs/OPENSUSE_RPM_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md`. It ties source, `rpmlint`, environment, artifact, payload, install/remove, and OBS non-claim columns together while keeping `opensuse_platform_build_evidence_accepted=0`, `opensuse_rpm_validation_result_promoted=0`, and package readiness disabled.

The openSUSE RPM build-evidence intake denial contract is recorded in `docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md`. It refuses `rpmbuild`, `osc build`, `rpmlint`, source RPM, binary RPM, and transcript intake while keeping `opensuse_build_evidence_intake_denied=1`, `opensuse_build_transcript_intake_accepted=0`, and package readiness disabled.

The openSUSE RPM build-evidence intake denial review contract is recorded in `docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_REVIEW_CONTRACT.md`. It upholds denied build-evidence intake while keeping `denial_re_request_allowed=0`, `opensuse_build_evidence_intake_denial_upheld=1`, and all build evidence unaccepted.

The openSUSE RPM build-evidence intake denial disposition contract is recorded in `docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CONTRACT.md`. It closes the upheld denial while keeping `denial_closed=1`, `opensuse_build_evidence_intake_denial_closed=1`, `opensuse_denial_re_request_allowed=0`, and all openSUSE build evidence unaccepted.

The openSUSE RPM build-evidence intake denial disposition closeout contract is recorded in `docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_CONTRACT.md`. It closes out the disposed denial while keeping `opensuse_build_evidence_intake_denial_closed_out=1`, `opensuse_denial_archive_allowed=0`, `opensuse_denial_re_request_allowed=0`, and all openSUSE build evidence unaccepted.

## Next Recommended Lane

```text
Add openSUSE RPM build-evidence intake denial disposition closeout archive gate contract before any closed-out denial can be archived or re-requested.
```
