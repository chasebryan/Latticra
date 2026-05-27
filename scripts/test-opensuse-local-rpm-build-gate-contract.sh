#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'opensuse local rpm build gate contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'opensuse local rpm build gate contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_no_rpm_artifacts() {
  dir="$1"
  if find "$dir" \( -name '*.rpm' -o -name '*.src.rpm' \) -print | grep -q .; then
    printf 'opensuse local rpm build gate contract: unexpected RPM artifact under %s\n' "$dir" >&2
    exit 1
  fi
}

contract='docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md'
environment_contract='docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md'
artifact_contract='docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md'
payload_contract='docs/OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md'
install_remove_contract='docs/OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md'
obs_contract='docs/OPENSUSE_OBS_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md'

require_file "$contract"
require_file "$environment_contract"
require_file "$artifact_contract"
require_file "$payload_contract"
require_file "$install_remove_contract"
require_file "$obs_contract"
require_file docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_file docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_file docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_file docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_file docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_file docs/README.md
require_file docs/status/README.md
require_file packaging/opensuse/README.md
require_file packaging/opensuse/latticra.spec
require_file packaging/opensuse/latticra.changes
require_file README.md
require_file scripts/test-opensuse-local-rpm-build-environment-contract.sh
require_file scripts/test-opensuse-rpm-artifact-naming-contract.sh
require_file scripts/test-opensuse-rpm-payload-inspection-contract.sh
require_file scripts/test-opensuse-rpm-install-remove-transcript-contract.sh
require_file scripts/test-opensuse-obs-publication-non-claim-review-contract.sh
require_file .github/workflows/opensuse-local-rpm-build-gate-contract.yml
require_file .github/workflows/opensuse-local-rpm-build-environment-contract.yml
require_file .github/workflows/opensuse-rpm-artifact-naming-contract.yml
require_file .github/workflows/opensuse-rpm-payload-inspection-contract.yml
require_file .github/workflows/opensuse-rpm-install-remove-transcript-contract.yml
require_file .github/workflows/opensuse-obs-publication-non-claim-review-contract.yml

require_contains 'Status: active local RPM build evidence gate contract' "$contract"
require_contains 'documentation-only and static' "$contract"
require_contains 'opensuse_local_rpm_build_gate_contract_present=1' "$contract"
require_contains 'opensuse_rpm_install_remove_transcript_contract_present=1' "$contract"
require_contains 'opensuse_obs_publication_non_claim_review_contract_present=1' "$contract"
require_contains 'opensuse_rpm_build_gate_state=closed-no-effect' "$contract"
require_contains 'rpmbuild_allowed=0' "$contract"
require_contains 'osc_build_allowed=0' "$contract"
require_contains 'spec_cleaner_allowed=0' "$contract"
require_contains 'rpmbuild_run=0' "$contract"
require_contains 'rpmbuild_ba_run=0' "$contract"
require_contains 'rpmbuild_bb_run=0' "$contract"
require_contains 'rpmbuild_bs_run=0' "$contract"
require_contains 'osc_build_run=0' "$contract"
require_contains 'spec_cleaner_run=0' "$contract"
require_contains 'source_rpm_artifact_created=0' "$contract"
require_contains 'binary_rpm_artifact_created=0' "$contract"
require_contains 'rpm_artifact_created=0' "$contract"
require_contains 'rpm_install_remove_transcript_present=0' "$contract"
require_contains 'rpm_validation_result_promoted=0' "$contract"
require_contains 'rpm_installed_on_host=0' "$contract"
require_contains 'rpm_removed_from_host=0' "$contract"
require_contains 'obs_publication_claimed=0' "$contract"
require_contains 'package_readiness_claimed=0' "$contract"

require_contains 'opensuse_rpm_topdir_handoff_lane_present=1' "$contract"
require_contains 'opensuse_rpm_payload_inspection_contract_present=1' "$contract"
require_contains 'temporary_rpm_topdir_handoff_lane_passed=1' "$contract"
require_contains 'opensuse_source_archive_fixture_lane_present=1' "$contract"
require_contains 'temporary_rpm_source_sha256_preserved=1' "$contract"
require_contains 'temporary_rpm_source_listing_preserved=1' "$contract"
require_contains 'temporary_rpm_source0_name_matched=1' "$contract"
require_contains 'temporary_rpm_autosetup_root_matched=1' "$contract"
require_contains 'source_archive_accepted_for_build=1' "$contract"
require_contains 'accepted_rpmlint_transcript_present=1' "$contract"
require_contains 'unexpected_findings_count=0' "$contract"
require_contains 'license_expression_reviewed=1' "$contract"
require_contains 'package_notice_obligations_reviewed=1' "$contract"
require_contains 'buildrequires_reviewed=1' "$contract"
require_contains 'spec_cleaner_review_present=1' "$contract"
require_contains 'open_build_service_non_claim_review_present=1' "$contract"

require_contains 'opensuse_clean_build_environment_documented=1' "$contract"
require_contains 'opensuse_target_distribution_documented=1' "$contract"
require_contains 'rpmbuild_toolchain_versions_recorded=1' "$contract"
require_contains 'osc_build_environment_documented=1' "$contract"
require_contains 'explicit_operator_build_authorization=1' "$contract"
require_contains 'disposable_validation_environment=1' "$contract"
require_contains 'rpm_artifact_naming_contract_present=1' "$contract"
require_contains 'rpm_payload_inspection_contract_present=1' "$contract"
require_contains 'rpm_install_remove_transcript_contract_present=1' "$contract"
require_contains 'obs_publication_non_claim_review_present=1' "$contract"
require_contains "$environment_contract" "$contract"
require_contains "$artifact_contract" "$contract"
require_contains "$payload_contract" "$contract"
require_contains "$install_remove_contract" "$contract"
require_contains "$obs_contract" "$contract"
require_contains 'Add openSUSE RPM build-evidence intake denial review contract' "$contract"
require_contains 'opensuse_local_rpm_build_gate_contract: ok' "$contract"

require_contains "$contract" docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_contains "$environment_contract" docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_contains "$contract" docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains "$environment_contract" docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains "$artifact_contract" docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains "$payload_contract" docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains "$install_remove_contract" docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains "$obs_contract" docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains "$contract" packaging/opensuse/README.md
require_contains "$environment_contract" packaging/opensuse/README.md
require_contains "$artifact_contract" packaging/opensuse/README.md
require_contains "$payload_contract" packaging/opensuse/README.md
require_contains "$install_remove_contract" packaging/opensuse/README.md
require_contains "$obs_contract" packaging/opensuse/README.md
require_contains "$contract" README.md
require_contains "$environment_contract" README.md
require_contains "$artifact_contract" README.md
require_contains "$payload_contract" README.md
require_contains "$install_remove_contract" README.md
require_contains "$obs_contract" README.md
require_contains 'OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md' docs/README.md
require_contains 'OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md' docs/status/README.md
require_contains 'OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md' docs/README.md
require_contains 'OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md' docs/status/README.md
require_contains 'OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md' docs/README.md
require_contains 'OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md' docs/status/README.md
require_contains 'OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md' docs/README.md
require_contains 'OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md' docs/status/README.md
require_contains 'OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md' docs/README.md
require_contains 'OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md' docs/status/README.md
require_contains 'OPENSUSE_OBS_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md' docs/README.md
require_contains 'OPENSUSE_OBS_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md' docs/status/README.md

require_contains 'opensuse_local_rpm_build_gate_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_local_rpm_build_environment_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_rpm_artifact_naming_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_rpm_payload_inspection_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_rpm_install_remove_transcript_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_obs_publication_non_claim_review_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_rpm_build_gate_state=closed-no-effect' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_rpm_build_environment_contract_state=specified-no-effect' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_rpm_artifact_naming_contract_state=specified-no-effect' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_rpm_payload_inspection_contract_state=specified-no-effect' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_rpm_install_remove_transcript_contract_state=specified-no-effect' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'rpmbuild_allowed=0' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'osc_build_allowed=0' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'spec_cleaner_allowed=0' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'rpmbuild_run=0' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'rpmbuild_ba_run=0' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'rpmbuild_bb_run=0' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'rpmbuild_bs_run=0' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'osc_build_run=0' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'source_rpm_artifact_created=0' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'binary_rpm_artifact_created=0' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'rpm_install_remove_transcript_present=0' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'obs_publication_non_claim_review_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md

require_contains 'opensuse_local_rpm_build_gate_contract_present=1' packaging/opensuse/README.md
require_contains 'opensuse_local_rpm_build_environment_contract_present=1' packaging/opensuse/README.md
require_contains 'opensuse_rpm_artifact_naming_contract_present=1' packaging/opensuse/README.md
require_contains 'opensuse_rpm_payload_inspection_contract_present=1' packaging/opensuse/README.md
require_contains 'opensuse_rpm_install_remove_transcript_contract_present=1' packaging/opensuse/README.md
require_contains 'opensuse_obs_publication_non_claim_review_contract_present=1' packaging/opensuse/README.md
require_contains 'opensuse_rpm_build_gate_state=closed-no-effect' packaging/opensuse/README.md
require_contains 'opensuse_rpm_build_environment_contract_state=specified-no-effect' packaging/opensuse/README.md
require_contains 'opensuse_rpm_artifact_naming_contract_state=specified-no-effect' packaging/opensuse/README.md
require_contains 'opensuse_rpm_payload_inspection_contract_state=specified-no-effect' packaging/opensuse/README.md
require_contains 'opensuse_rpm_install_remove_transcript_contract_state=specified-no-effect' packaging/opensuse/README.md
require_contains 'rpmbuild_allowed=0' packaging/opensuse/README.md
require_contains 'osc_build_allowed=0' packaging/opensuse/README.md
require_contains 'spec_cleaner_allowed=0' packaging/opensuse/README.md
require_contains 'rpmbuild_run=0' packaging/opensuse/README.md
require_contains 'osc_build_run=0' packaging/opensuse/README.md
require_contains 'source_rpm_artifact_created=0' packaging/opensuse/README.md
require_contains 'binary_rpm_artifact_created=0' packaging/opensuse/README.md
require_contains 'obs_publication_non_claim_review_present=1' packaging/opensuse/README.md

require_contains 'License:        AGPL-3.0-or-later AND CC-BY-4.0' packaging/opensuse/latticra.spec
require_contains 'BuildRequires:  gcc' packaging/opensuse/latticra.spec
require_contains 'BuildRequires:  make' packaging/opensuse/latticra.spec
require_contains 'Open Build Service publication' packaging/opensuse/latticra.changes

require_no_rpm_artifacts packaging/opensuse

require_contains 'Run openSUSE local RPM build gate contract guard' .github/workflows/opensuse-local-rpm-build-gate-contract.yml
require_contains 'sh scripts/test-opensuse-local-rpm-build-gate-contract.sh' .github/workflows/opensuse-local-rpm-build-gate-contract.yml
require_contains 'Run openSUSE local RPM build environment contract guard' .github/workflows/opensuse-local-rpm-build-environment-contract.yml
require_contains 'sh scripts/test-opensuse-local-rpm-build-environment-contract.sh' .github/workflows/opensuse-local-rpm-build-environment-contract.yml
require_contains 'Run openSUSE RPM artifact naming contract guard' .github/workflows/opensuse-rpm-artifact-naming-contract.yml
require_contains 'sh scripts/test-opensuse-rpm-artifact-naming-contract.sh' .github/workflows/opensuse-rpm-artifact-naming-contract.yml
require_contains 'Run openSUSE RPM payload inspection contract guard' .github/workflows/opensuse-rpm-payload-inspection-contract.yml
require_contains 'sh scripts/test-opensuse-rpm-payload-inspection-contract.sh' .github/workflows/opensuse-rpm-payload-inspection-contract.yml
require_contains 'Run openSUSE RPM install/remove transcript contract guard' .github/workflows/opensuse-rpm-install-remove-transcript-contract.yml
require_contains 'sh scripts/test-opensuse-rpm-install-remove-transcript-contract.sh' .github/workflows/opensuse-rpm-install-remove-transcript-contract.yml
require_contains 'Run openSUSE OBS publication non-claim review contract guard' .github/workflows/opensuse-obs-publication-non-claim-review-contract.yml
require_contains 'sh scripts/test-opensuse-obs-publication-non-claim-review-contract.sh' .github/workflows/opensuse-obs-publication-non-claim-review-contract.yml

printf 'opensuse_local_rpm_build_gate_contract: ok\n'
