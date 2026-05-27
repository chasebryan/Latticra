#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'opensuse obs publication non-claim review contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'opensuse obs publication non-claim review contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_no_rpm_artifacts() {
  dir="$1"
  if find "$dir" \( -name '*.rpm' -o -name '*.src.rpm' \) -print | grep -q .; then
    printf 'opensuse obs publication non-claim review contract: unexpected RPM artifact under %s\n' "$dir" >&2
    exit 1
  fi
}

contract='docs/OPENSUSE_OBS_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md'
install_remove_contract='docs/OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md'
payload_contract='docs/OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md'
artifact_contract='docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md'
environment_contract='docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md'
gate_contract='docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md'

require_file "$contract"
require_file "$install_remove_contract"
require_file "$payload_contract"
require_file "$artifact_contract"
require_file "$environment_contract"
require_file "$gate_contract"
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
require_file .github/workflows/opensuse-obs-publication-non-claim-review-contract.yml

require_contains 'Status: active OBS publication non-claim review contract' "$contract"
require_contains 'documentation-only and static' "$contract"
require_contains 'opensuse_obs_publication_non_claim_review_contract_present=1' "$contract"
require_contains 'obs_publication_non_claim_review_contract_present=1' "$contract"
require_contains 'publication_non_claim_review_contract_present=1' "$contract"
require_contains 'obs_publication_non_claim_review_present=1' "$contract"
require_contains 'publication_non_claim_review_present=1' "$contract"
require_contains 'opensuse_rpm_build_gate_state=closed-no-effect' "$contract"
require_contains 'payload_inspection_contract_state=specified-no-effect' "$contract"
require_contains 'install_remove_transcript_contract_state=specified-no-effect' "$contract"
require_contains 'rpm_validation_result_promoted=0' "$contract"
require_contains 'rpm_artifact_created=0' "$contract"
require_contains 'rpm_artifact_published=0' "$contract"
require_contains 'obs_project_created=0' "$contract"
require_contains 'obs_package_created=0' "$contract"
require_contains 'obs_repository_created=0' "$contract"
require_contains 'obs_source_link_created=0' "$contract"
require_contains 'osc_branch_run=0' "$contract"
require_contains 'osc_commit_run=0' "$contract"
require_contains 'osc_submitreq_run=0' "$contract"
require_contains 'osc_request_accepted=0' "$contract"
require_contains 'obs_build_result_claimed=0' "$contract"
require_contains 'opensuse_obs_publication_claimed=0' "$contract"
require_contains 'opensuse_submit_request_claimed=0' "$contract"
require_contains 'opensuse_official_package_claimed=0' "$contract"
require_contains 'suse_endorsement_claimed=0' "$contract"
require_contains 'opensuse_factory_submission_claimed=0' "$contract"
require_contains 'opensuse_factory_acceptance_claimed=0' "$contract"
require_contains 'opensuse_leap_submission_claimed=0' "$contract"
require_contains 'opensuse_distribution_ready=0' "$contract"
require_contains 'package_readiness_claimed=0' "$contract"

require_contains 'obs_publication_non_claim_review_required=1' "$contract"
require_contains 'obs_publication_non_claim_review_present=1' "$contract"
require_contains 'obs_source_upload_run=0' "$contract"
require_contains 'osc_add_run=0' "$contract"
require_contains 'rpm_validation_result_identifier' "$contract"
require_contains 'opensuse_target_distribution' "$contract"
require_contains 'source_archive_sha256' "$contract"
require_contains 'source_rpm_artifact_sha256' "$contract"
require_contains 'binary_rpm_artifact_sha256' "$contract"
require_contains 'payload_inspection_transcript_sha256' "$contract"
require_contains 'install_remove_transcript_sha256' "$contract"
require_contains 'obs_publication_non_claim_reviewer' "$contract"
require_contains 'non_claimed_obs_targets' "$contract"
require_contains 'non_claimed_submit_request_targets' "$contract"
require_contains 'status_page_update_reference' "$contract"
require_contains 'operator_authorization_reference' "$contract"
require_contains 'source_archive_accepted_for_build=0' "$contract"
require_contains 'accepted_rpmlint_transcript_present=0' "$contract"
require_contains 'rpm_payload_accepted=0' "$contract"
require_contains 'rpm_install_remove_transcript_present=0' "$contract"
require_contains 'explicit_operator_build_authorization=0' "$contract"
require_contains 'Add openSUSE RPM build-evidence intake denial contract' "$contract"
require_contains 'opensuse_obs_publication_non_claim_review_contract: ok' "$contract"

require_contains "$contract" "$install_remove_contract"
require_contains "$contract" "$payload_contract"
require_contains "$contract" "$artifact_contract"
require_contains "$contract" "$environment_contract"
require_contains "$contract" "$gate_contract"
require_contains "$contract" docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains "$contract" packaging/opensuse/README.md
require_contains "$contract" README.md
require_contains 'OPENSUSE_OBS_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md' docs/README.md
require_contains 'OPENSUSE_OBS_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md' docs/status/README.md

require_contains 'opensuse_obs_publication_non_claim_review_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'obs_publication_non_claim_review_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'obs_publication_non_claim_review_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'publication_non_claim_review_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'rpm_validation_result_promoted=0' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'obs_project_created=0' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'obs_package_created=0' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'osc_commit_run=0' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'osc_submitreq_run=0' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'osc_request_accepted=0' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_submit_request_claimed=0' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md

require_contains 'opensuse_obs_publication_non_claim_review_contract_present=1' packaging/opensuse/README.md
require_contains 'obs_publication_non_claim_review_contract_present=1' packaging/opensuse/README.md
require_contains 'obs_publication_non_claim_review_present=1' packaging/opensuse/README.md
require_contains 'publication_non_claim_review_present=1' packaging/opensuse/README.md
require_contains 'rpm_validation_result_promoted=0' packaging/opensuse/README.md
require_contains 'obs_project_created=0' packaging/opensuse/README.md
require_contains 'obs_package_created=0' packaging/opensuse/README.md
require_contains 'osc_commit_run=0' packaging/opensuse/README.md
require_contains 'osc_submitreq_run=0' packaging/opensuse/README.md
require_contains 'opensuse_submit_request_claimed=0' packaging/opensuse/README.md

require_contains 'Open Build Service publication' packaging/opensuse/latticra.changes
require_no_rpm_artifacts packaging/opensuse

require_contains 'Run openSUSE OBS publication non-claim review contract guard' .github/workflows/opensuse-obs-publication-non-claim-review-contract.yml
require_contains 'sh scripts/test-opensuse-obs-publication-non-claim-review-contract.sh' .github/workflows/opensuse-obs-publication-non-claim-review-contract.yml

printf 'opensuse_obs_publication_non_claim_review_contract: ok\n'
