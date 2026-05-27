#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'opensuse rpm install/remove transcript contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'opensuse rpm install/remove transcript contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_absent_file() {
  file="$1"
  if [ -e "$file" ]; then
    printf 'opensuse rpm install/remove transcript contract: unexpected file exists: %s\n' "$file" >&2
    exit 1
  fi
}

require_no_rpm_artifacts() {
  dir="$1"
  if find "$dir" \( -name '*.rpm' -o -name '*.src.rpm' \) -print | grep -q .; then
    printf 'opensuse rpm install/remove transcript contract: unexpected RPM artifact under %s\n' "$dir" >&2
    exit 1
  fi
}

contract='docs/OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md'
payload_contract='docs/OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md'
artifact_contract='docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md'
environment_contract='docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md'
gate_contract='docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md'
obs_contract='docs/OPENSUSE_OBS_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md'

require_file "$contract"
require_file "$payload_contract"
require_file "$artifact_contract"
require_file "$environment_contract"
require_file "$gate_contract"
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
require_file scripts/test-opensuse-obs-publication-non-claim-review-contract.sh
require_file .github/workflows/opensuse-rpm-install-remove-transcript-contract.yml
require_file .github/workflows/opensuse-obs-publication-non-claim-review-contract.yml

require_contains 'Status: active RPM install/remove transcript contract' "$contract"
require_contains 'documentation-only and static' "$contract"
require_contains 'opensuse_rpm_install_remove_transcript_contract_present=1' "$contract"
require_contains 'opensuse_obs_publication_non_claim_review_contract_present=1' "$contract"
require_contains 'rpm_install_remove_transcript_contract_present=1' "$contract"
require_contains 'install_remove_transcript_contract_present=1' "$contract"
require_contains 'obs_publication_non_claim_review_present=1' "$contract"
require_contains 'publication_non_claim_review_present=1' "$contract"
require_contains 'opensuse_rpm_install_remove_transcript_contract_state=specified-no-effect' "$contract"
require_contains 'install_remove_transcript_contract_state=specified-no-effect' "$contract"
require_contains 'opensuse_rpm_build_gate_state=closed-no-effect' "$contract"
require_contains 'payload_inspection_contract_state=specified-no-effect' "$contract"
require_contains 'rpm_install_remove_disposable_environment_required=1' "$contract"
require_contains 'rpm_install_remove_transcript_present=0' "$contract"
require_contains 'rpm_package_install_run=0' "$contract"
require_contains 'rpm_package_remove_run=0' "$contract"
require_contains 'rpm_zypper_install_run=0' "$contract"
require_contains 'rpm_zypper_remove_run=0' "$contract"
require_contains 'rpm_cli_install_run=0' "$contract"
require_contains 'rpm_cli_remove_run=0' "$contract"
require_contains 'rpm_installed_on_host=0' "$contract"
require_contains 'rpm_removed_from_host=0' "$contract"
require_contains 'host_install_allowed=0' "$contract"
require_contains 'host_remove_allowed=0' "$contract"
require_contains 'host_mutation_allowed=0' "$contract"
require_contains 'service_state_change_allowed=0' "$contract"
require_contains 'rpm_artifact_created=0' "$contract"
require_contains 'rpm_payload_accepted=0' "$contract"
require_contains 'rpm_validation_result_promoted=0' "$contract"
require_contains 'package_readiness_claimed=0' "$contract"

require_contains 'rpm_install_remove_transcript_required=1' "$contract"
require_contains 'rpm_payload_post_install_check_required=1' "$contract"
require_contains 'rpm_payload_post_remove_absence_check_required=1' "$contract"
require_contains 'rpm_service_state_change_allowed=0' "$contract"
require_contains 'rpm_systemd_unit_enable_allowed=0' "$contract"
require_contains 'rpm_scriptlet_effect_allowed=0' "$contract"
require_contains 'rpm_kernel_file_allowed=0' "$contract"
require_contains 'rpm_network_authority_allowed=0' "$contract"
require_contains 'rpm_privileged_helper_allowed=0' "$contract"
require_contains 'rpm_binary_package_name_pattern=latticra-0.0.0-0.local.${RPM_ARCH}.rpm' "$contract"
require_contains 'rpm_binary_artifact_sha256' "$contract"
require_contains 'rpm_payload_expected_bin=/usr/bin/latticra' "$contract"
require_contains 'rpm_payload_expected_doc=/usr/share/doc/packages/latticra/README.md' "$contract"

require_contains 'environment_identifier' "$contract"
require_contains 'opensuse_target_distribution' "$contract"
require_contains 'operator_authorization_reference' "$contract"
require_contains 'pre_install_package_state' "$contract"
require_contains 'install_command' "$contract"
require_contains 'install_exit_code' "$contract"
require_contains 'post_install_payload_listing' "$contract"
require_contains 'post_install_cli_no_effect_output' "$contract"
require_contains 'rpm_query_after_install' "$contract"
require_contains 'service_state_after_install' "$contract"
require_contains 'remove_command' "$contract"
require_contains 'remove_exit_code' "$contract"
require_contains 'post_remove_absence_report' "$contract"
require_contains 'post_remove_package_state' "$contract"
require_contains 'scriptlet_effect_review' "$contract"
require_contains 'host_mutation_review' "$contract"
require_contains 'obs_publication_non_claim_review_present=1' "$contract"
require_contains 'Add openSUSE RPM build-evidence intake denial disposition closeout archive gate contract' "$contract"
require_contains 'opensuse_rpm_install_remove_transcript_contract: ok' "$contract"

require_contains "$contract" "$payload_contract"
require_contains "$contract" "$artifact_contract"
require_contains "$contract" "$environment_contract"
require_contains "$contract" "$gate_contract"
require_contains "$obs_contract" "$contract"
require_contains "$contract" docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains "$obs_contract" docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains "$contract" packaging/opensuse/README.md
require_contains "$obs_contract" packaging/opensuse/README.md
require_contains "$contract" README.md
require_contains "$obs_contract" README.md
require_contains 'OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md' docs/README.md
require_contains 'OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md' docs/status/README.md
require_contains 'OPENSUSE_OBS_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md' docs/README.md
require_contains 'OPENSUSE_OBS_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md' docs/status/README.md

require_contains 'opensuse_rpm_install_remove_transcript_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_obs_publication_non_claim_review_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_rpm_install_remove_transcript_contract_state=specified-no-effect' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'obs_publication_non_claim_review_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'rpm_install_remove_transcript_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'install_remove_transcript_contract_state=specified-no-effect' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'rpm_install_remove_transcript_present=0' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'rpm_package_install_run=0' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'rpm_package_remove_run=0' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'rpm_removed_from_host=0' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'host_mutation_allowed=0' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'rpm_validation_result_promoted=0' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md

require_contains 'opensuse_rpm_install_remove_transcript_contract_present=1' packaging/opensuse/README.md
require_contains 'opensuse_obs_publication_non_claim_review_contract_present=1' packaging/opensuse/README.md
require_contains 'opensuse_rpm_install_remove_transcript_contract_state=specified-no-effect' packaging/opensuse/README.md
require_contains 'obs_publication_non_claim_review_present=1' packaging/opensuse/README.md
require_contains 'rpm_install_remove_transcript_contract_present=1' packaging/opensuse/README.md
require_contains 'install_remove_transcript_contract_state=specified-no-effect' packaging/opensuse/README.md
require_contains 'rpm_install_remove_transcript_present=0' packaging/opensuse/README.md
require_contains 'rpm_package_install_run=0' packaging/opensuse/README.md
require_contains 'rpm_package_remove_run=0' packaging/opensuse/README.md
require_contains 'rpm_removed_from_host=0' packaging/opensuse/README.md
require_contains 'host_mutation_allowed=0' packaging/opensuse/README.md
require_contains 'rpm_validation_result_promoted=0' packaging/opensuse/README.md

require_contains 'install -m 0755 build/latticra %{buildroot}%{_bindir}/latticra' packaging/opensuse/latticra.spec
require_contains 'install -m 0644 README.md %{buildroot}%{_docdir}/%{name}/README.md' packaging/opensuse/latticra.spec
require_contains '%{_bindir}/latticra' packaging/opensuse/latticra.spec
require_contains '%doc %{_docdir}/%{name}/README.md' packaging/opensuse/latticra.spec

require_absent_file packaging/opensuse/latticra.service
require_absent_file packaging/opensuse/latticra.init
require_absent_file packaging/opensuse/latticra.tmpfiles
require_no_rpm_artifacts packaging/opensuse

require_contains 'Run openSUSE RPM install/remove transcript contract guard' .github/workflows/opensuse-rpm-install-remove-transcript-contract.yml
require_contains 'sh scripts/test-opensuse-rpm-install-remove-transcript-contract.sh' .github/workflows/opensuse-rpm-install-remove-transcript-contract.yml
require_contains 'Run openSUSE OBS publication non-claim review contract guard' .github/workflows/opensuse-obs-publication-non-claim-review-contract.yml
require_contains 'sh scripts/test-opensuse-obs-publication-non-claim-review-contract.sh' .github/workflows/opensuse-obs-publication-non-claim-review-contract.yml

printf 'opensuse_rpm_install_remove_transcript_contract: ok\n'
