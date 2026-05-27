#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'opensuse rpm payload inspection contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'opensuse rpm payload inspection contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_no_rpm_artifacts() {
  dir="$1"
  if find "$dir" \( -name '*.rpm' -o -name '*.src.rpm' \) -print | grep -q .; then
    printf 'opensuse rpm payload inspection contract: unexpected RPM artifact under %s\n' "$dir" >&2
    exit 1
  fi
}

contract='docs/OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md'
artifact_contract='docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md'
environment_contract='docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md'
gate_contract='docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md'
install_remove_contract='docs/OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md'
obs_contract='docs/OPENSUSE_OBS_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md'

require_file "$contract"
require_file "$artifact_contract"
require_file "$environment_contract"
require_file "$gate_contract"
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
require_file scripts/test-opensuse-rpm-install-remove-transcript-contract.sh
require_file scripts/test-opensuse-obs-publication-non-claim-review-contract.sh
require_file .github/workflows/opensuse-rpm-payload-inspection-contract.yml
require_file .github/workflows/opensuse-rpm-install-remove-transcript-contract.yml
require_file .github/workflows/opensuse-obs-publication-non-claim-review-contract.yml

require_contains 'Status: active RPM payload inspection contract' "$contract"
require_contains 'documentation-only and static' "$contract"
require_contains 'opensuse_rpm_payload_inspection_contract_present=1' "$contract"
require_contains 'opensuse_rpm_install_remove_transcript_contract_present=1' "$contract"
require_contains 'opensuse_obs_publication_non_claim_review_contract_present=1' "$contract"
require_contains 'rpm_payload_inspection_contract_present=1' "$contract"
require_contains 'obs_publication_non_claim_review_present=1' "$contract"
require_contains 'publication_non_claim_review_present=1' "$contract"
require_contains 'payload_inspection_contract_present=1' "$contract"
require_contains 'opensuse_rpm_payload_inspection_contract_state=specified-no-effect' "$contract"
require_contains 'opensuse_rpm_install_remove_transcript_contract_state=specified-no-effect' "$contract"
require_contains 'payload_inspection_contract_state=specified-no-effect' "$contract"
require_contains 'opensuse_rpm_build_gate_state=closed-no-effect' "$contract"
require_contains 'opensuse_rpm_artifact_naming_contract_state=specified-no-effect' "$contract"
require_contains 'rpm_artifact_created=0' "$contract"
require_contains 'rpm_payload_inspection_run=0' "$contract"
require_contains 'source_rpm_payload_inspection_run=0' "$contract"
require_contains 'binary_rpm_payload_inspection_run=0' "$contract"
require_contains 'rpm_payload_accepted=0' "$contract"
require_contains 'rpm_install_remove_transcript_present=0' "$contract"
require_contains 'rpm_validation_result_promoted=0' "$contract"
require_contains 'rpm_artifact_sha256_recorded=0' "$contract"
require_contains 'rpm_installed_on_host=0' "$contract"
require_contains 'rpm_removed_from_host=0' "$contract"
require_contains 'package_readiness_claimed=0' "$contract"

require_contains 'rpm_payload_cli_path_required=1' "$contract"
require_contains 'rpm_payload_doc_readme_required=1' "$contract"
require_contains 'rpm_payload_service_files_allowed=0' "$contract"
require_contains 'rpm_payload_systemd_units_allowed=0' "$contract"
require_contains 'rpm_payload_init_files_allowed=0' "$contract"
require_contains 'rpm_payload_kernel_files_allowed=0' "$contract"
require_contains 'rpm_payload_privileged_helper_allowed=0' "$contract"
require_contains 'rpm_payload_network_authority_allowed=0' "$contract"
require_contains 'rpm_payload_host_mutation_hooks_allowed=0' "$contract"

require_contains 'source_rpm_expected_spec=packaging/opensuse/latticra.spec' "$contract"
require_contains 'source_rpm_expected_changes=packaging/opensuse/latticra.changes' "$contract"
require_contains 'source_rpm_expected_source_archive=latticra-0.0.0.tar.gz' "$contract"
require_contains 'source_rpm_payload_listing_required=1' "$contract"
require_contains 'source_rpm_metadata_inspection_required=1' "$contract"
require_contains 'source_rpm_unexpected_archive_count=0' "$contract"
require_contains 'rpm2cpio_source_inspection_run=0' "$contract"
require_contains 'source_rpm_metadata_inspection_run=0' "$contract"
require_contains 'rpm_source_package_name=latticra-0.0.0-0.local.src.rpm' "$contract"
require_contains 'source_rpm_payload_listing_sha256' "$contract"

require_contains 'rpm_payload_expected_bin=/usr/bin/latticra' "$contract"
require_contains 'rpm_payload_expected_doc=/usr/share/doc/packages/latticra/README.md' "$contract"
require_contains 'rpm_payload_listing_required=1' "$contract"
require_contains 'rpm_metadata_inspection_required=1' "$contract"
require_contains 'rpm_scriptlet_absence_required=1' "$contract"
require_contains 'rpm_systemd_unit_absence_required=1' "$contract"
require_contains 'rpm_init_script_absence_required=1' "$contract"
require_contains 'rpm_privileged_helper_absence_required=1' "$contract"
require_contains 'rpm_payload_unexpected_file_count=0' "$contract"
require_contains 'rpm_query_payload_inspection_run=0' "$contract"
require_contains 'rpm_query_scriptlet_inspection_run=0' "$contract"
require_contains 'rpm2cpio_binary_listing_run=0' "$contract"
require_contains 'rpm_binary_package_name_pattern=latticra-0.0.0-0.local.${RPM_ARCH}.rpm' "$contract"
require_contains 'binary_rpm_payload_listing_sha256' "$contract"

require_contains 'rpm_artifact_name' "$contract"
require_contains 'payload_listing_sha256' "$contract"
require_contains 'expected_payload_paths_present' "$contract"
require_contains 'unexpected_payload_paths_absent' "$contract"
require_contains 'service_files_absent' "$contract"
require_contains 'systemd_units_absent' "$contract"
require_contains 'scriptlets_absent' "$contract"
require_contains 'privileged_helpers_absent' "$contract"
require_contains 'host_mutation_hooks_absent' "$contract"
require_contains 'environment_identifier' "$contract"
require_contains 'operator_authorization_reference' "$contract"
require_contains 'environment_transcript_present=0' "$contract"
require_contains 'explicit_operator_build_authorization=0' "$contract"
require_contains 'rpm_install_remove_transcript_contract_present=1' "$contract"
require_contains 'obs_publication_non_claim_review_present=1' "$contract"
require_contains 'Add openSUSE RPM build-evidence intake denial review contract' "$contract"
require_contains 'opensuse_rpm_payload_inspection_contract: ok' "$contract"

require_contains "$contract" "$artifact_contract"
require_contains "$contract" "$gate_contract"
require_contains "$install_remove_contract" "$contract"
require_contains "$obs_contract" "$contract"
require_contains "$contract" docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains "$install_remove_contract" docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains "$obs_contract" docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains "$contract" packaging/opensuse/README.md
require_contains "$install_remove_contract" packaging/opensuse/README.md
require_contains "$obs_contract" packaging/opensuse/README.md
require_contains "$contract" README.md
require_contains "$install_remove_contract" README.md
require_contains "$obs_contract" README.md
require_contains 'OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md' docs/README.md
require_contains 'OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md' docs/status/README.md
require_contains 'OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md' docs/README.md
require_contains 'OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md' docs/status/README.md
require_contains 'OPENSUSE_OBS_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md' docs/README.md
require_contains 'OPENSUSE_OBS_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md' docs/status/README.md

require_contains 'opensuse_rpm_payload_inspection_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_rpm_install_remove_transcript_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_obs_publication_non_claim_review_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_rpm_payload_inspection_contract_state=specified-no-effect' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_rpm_install_remove_transcript_contract_state=specified-no-effect' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'payload_inspection_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'payload_inspection_contract_state=specified-no-effect' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'rpm_payload_expected_bin=/usr/bin/latticra' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'rpm_payload_expected_doc=/usr/share/doc/packages/latticra/README.md' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'source_rpm_payload_inspection_run=0' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'binary_rpm_payload_inspection_run=0' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'rpm_payload_accepted=0' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'rpm_install_remove_transcript_present=0' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'obs_publication_non_claim_review_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md

require_contains 'opensuse_rpm_payload_inspection_contract_present=1' packaging/opensuse/README.md
require_contains 'opensuse_rpm_install_remove_transcript_contract_present=1' packaging/opensuse/README.md
require_contains 'opensuse_obs_publication_non_claim_review_contract_present=1' packaging/opensuse/README.md
require_contains 'opensuse_rpm_payload_inspection_contract_state=specified-no-effect' packaging/opensuse/README.md
require_contains 'opensuse_rpm_install_remove_transcript_contract_state=specified-no-effect' packaging/opensuse/README.md
require_contains 'payload_inspection_contract_present=1' packaging/opensuse/README.md
require_contains 'rpm_payload_expected_bin=/usr/bin/latticra' packaging/opensuse/README.md
require_contains 'rpm_payload_expected_doc=/usr/share/doc/packages/latticra/README.md' packaging/opensuse/README.md
require_contains 'rpm_payload_accepted=0' packaging/opensuse/README.md
require_contains 'obs_publication_non_claim_review_present=1' packaging/opensuse/README.md

require_contains 'install -m 0755 build/latticra %{buildroot}%{_bindir}/latticra' packaging/opensuse/latticra.spec
require_contains 'install -m 0644 README.md %{buildroot}%{_docdir}/%{name}/README.md' packaging/opensuse/latticra.spec
require_contains '%{_bindir}/latticra' packaging/opensuse/latticra.spec
require_contains '%doc %{_docdir}/%{name}/README.md' packaging/opensuse/latticra.spec
require_contains 'Open Build Service publication' packaging/opensuse/latticra.changes

require_no_rpm_artifacts packaging/opensuse

require_contains 'Run openSUSE RPM payload inspection contract guard' .github/workflows/opensuse-rpm-payload-inspection-contract.yml
require_contains 'sh scripts/test-opensuse-rpm-payload-inspection-contract.sh' .github/workflows/opensuse-rpm-payload-inspection-contract.yml
require_contains 'Run openSUSE RPM install/remove transcript contract guard' .github/workflows/opensuse-rpm-install-remove-transcript-contract.yml
require_contains 'sh scripts/test-opensuse-rpm-install-remove-transcript-contract.sh' .github/workflows/opensuse-rpm-install-remove-transcript-contract.yml
require_contains 'Run openSUSE OBS publication non-claim review contract guard' .github/workflows/opensuse-obs-publication-non-claim-review-contract.yml
require_contains 'sh scripts/test-opensuse-obs-publication-non-claim-review-contract.sh' .github/workflows/opensuse-obs-publication-non-claim-review-contract.yml

printf 'opensuse_rpm_payload_inspection_contract: ok\n'
