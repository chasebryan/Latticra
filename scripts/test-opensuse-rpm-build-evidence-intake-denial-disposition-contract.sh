#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'opensuse rpm build-evidence intake denial disposition contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'opensuse rpm build-evidence intake denial disposition contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_no_rpm_artifacts() {
  dir="$1"
  if find "$dir" \( -name '*.rpm' -o -name '*.src.rpm' \) -print | grep -q .; then
    printf 'opensuse rpm build-evidence intake denial disposition contract: unexpected RPM artifact under %s\n' "$dir" >&2
    exit 1
  fi
}

contract='docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CONTRACT.md'
closeout_contract='docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_CONTRACT.md'
review_contract='docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_REVIEW_CONTRACT.md'
denial_contract='docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md'
matrix_contract='docs/OPENSUSE_RPM_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md'
obs_contract='docs/OPENSUSE_OBS_PUBLICATION_NON_CLAIM_REVIEW_CONTRACT.md'
install_remove_contract='docs/OPENSUSE_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md'
payload_contract='docs/OPENSUSE_RPM_PAYLOAD_INSPECTION_CONTRACT.md'
artifact_contract='docs/OPENSUSE_RPM_ARTIFACT_NAMING_CONTRACT.md'
environment_contract='docs/OPENSUSE_LOCAL_RPM_BUILD_ENVIRONMENT_CONTRACT.md'
gate_contract='docs/OPENSUSE_LOCAL_RPM_BUILD_GATE_CONTRACT.md'

require_file "$contract"
require_file "$closeout_contract"
require_file "$review_contract"
require_file "$denial_contract"
require_file "$matrix_contract"
require_file "$obs_contract"
require_file "$install_remove_contract"
require_file "$payload_contract"
require_file "$artifact_contract"
require_file "$environment_contract"
require_file "$gate_contract"
require_file docs/OPENSUSE_RPMLINT_FINDINGS_CLASSIFICATION.md
require_file docs/OPENSUSE_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_file docs/OPENSUSE_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_file docs/OPENSUSE_RPM_TOPDIR_HANDOFF_LANE.md
require_file docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_file docs/README.md
require_file docs/status/README.md
require_file packaging/opensuse/README.md
require_file packaging/opensuse/latticra.spec
require_file packaging/opensuse/latticra.changes
require_file README.md
require_file .github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-contract.yml

require_contains 'Status: active RPM build-evidence intake denial disposition contract' "$contract"
require_contains 'documentation-only and static' "$contract"
require_contains 'opensuse_rpm_build_evidence_intake_denial_disposition_contract_present=1' "$contract"
require_contains 'rpm_build_evidence_intake_denial_disposition_contract_present=1' "$contract"
require_contains 'build_evidence_intake_denial_disposition_state=closed-upheld-no-effect' "$contract"
require_contains 'build_evidence_intake_denial_review_state=reviewed-upheld-no-effect' "$contract"
require_contains 'build_evidence_intake_denial_state=denied-no-effect' "$contract"
require_contains 'validation_promotion_blocker_matrix_state=blocked-no-effect' "$contract"
require_contains 'opensuse_rpm_build_gate_state=closed-no-effect' "$contract"
require_contains 'denial_disposition_present=1' "$contract"
require_contains 'denial_disposition_decision=close-upheld-denial' "$contract"
require_contains 'denial_review_present=1' "$contract"
require_contains 'denial_review_decision=uphold-denial' "$contract"
require_contains 'denial_closed=1' "$contract"
require_contains 'denial_re_request_allowed=0' "$contract"
require_contains 'opensuse_build_evidence_intake_allowed=0' "$contract"
require_contains 'opensuse_build_evidence_intake_denied=1' "$contract"
require_contains 'opensuse_platform_build_evidence_accepted=0' "$contract"
require_contains 'build_transcript_intake_accepted=0' "$contract"
require_contains 'rpm_build_transcript_intake_accepted=0' "$contract"
require_contains 'rpm_build_lane_opened=0' "$contract"
require_contains 'opensuse_single_platform_build_lane_opened=0' "$contract"
require_contains 'source_archive_accepted_for_build=0' "$contract"
require_contains 'accepted_rpmlint_transcript_present=0' "$contract"
require_contains 'environment_transcript_present=0' "$contract"
require_contains 'explicit_operator_build_authorization=0' "$contract"
require_contains 'rpm_artifact_created=0' "$contract"
require_contains 'rpm_artifact_sha256_recorded=0' "$contract"
require_contains 'rpm_payload_accepted=0' "$contract"
require_contains 'rpm_install_remove_transcript_present=0' "$contract"
require_contains 'obs_publication_non_claim_review_present=1' "$contract"
require_contains 'rpm_validation_result_promoted=0' "$contract"
require_contains 'opensuse_rpm_validation_result_promoted=0' "$contract"
require_contains 'package_readiness_claimed=0' "$contract"

require_contains 'denial_disposition_identifier' "$contract"
require_contains 'denial_review_reference' "$contract"
require_contains 'build_evidence_denial_reference' "$contract"
require_contains 'build_evidence_intake_request_identifier' "$contract"
require_contains 'opensuse_target_distribution' "$contract"
require_contains 'requested_build_evidence_kind' "$contract"
require_contains 'requested_build_command' "$contract"
require_contains 'submitted_transcript_reference' "$contract"
require_contains 'validation_promotion_blocker_matrix_reference' "$contract"
require_contains 'denial_disposition_decision' "$contract"
require_contains 'denial_disposition_reason' "$contract"
require_contains 'denial_disposition_reviewer' "$contract"
require_contains 'close-upheld-denial' "$contract"

require_contains 'opensuse_build_evidence_intake_denial_disposition_present=1' "$contract"
require_contains 'opensuse_build_evidence_intake_denial_closed=1' "$contract"
require_contains 'opensuse_build_evidence_intake_denial_upheld=1' "$contract"
require_contains 'opensuse_denial_re_request_allowed=0' "$contract"
require_contains 'opensuse_build_transcript_intake_accepted=0' "$contract"
require_contains 'opensuse_rpmbuild_evidence_accepted=0' "$contract"
require_contains 'opensuse_osc_build_evidence_accepted=0' "$contract"
require_contains 'opensuse_rpmlint_evidence_accepted=0' "$contract"
require_contains 'opensuse_source_rpm_evidence_accepted=0' "$contract"
require_contains 'opensuse_binary_rpm_evidence_accepted=0' "$contract"
require_contains 'rpmbuild_run=0' "$contract"
require_contains 'rpmbuild_ba_run=0' "$contract"
require_contains 'rpmbuild_bb_run=0' "$contract"
require_contains 'rpmbuild_bs_run=0' "$contract"
require_contains 'osc_build_run=0' "$contract"
require_contains 'rpmlint_run=0' "$contract"
require_contains 'osc_submitreq_run=0' "$contract"
require_contains 'obs_build_result_claimed=0' "$contract"
require_contains 'opensuse_obs_publication_claimed=0' "$contract"

require_contains 're-request build evidence' "$contract"
require_contains 'accept build evidence' "$contract"
require_contains 'docs/OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_REVIEW_CONTRACT.md' "$contract"
require_contains "$closeout_contract" "$contract"
require_contains 'Add openSUSE RPM build-evidence intake denial disposition closeout archive gate review contract' "$contract"
require_contains 'opensuse_rpm_build_evidence_intake_denial_disposition_contract: ok' "$contract"

require_contains "$contract" "$review_contract"
require_contains "$contract" "$denial_contract"
require_contains "$contract" "$matrix_contract"
require_contains "$contract" "$obs_contract"
require_contains "$contract" "$install_remove_contract"
require_contains "$contract" "$payload_contract"
require_contains "$contract" "$artifact_contract"
require_contains "$contract" "$environment_contract"
require_contains "$contract" "$gate_contract"
require_contains "$contract" docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains "$contract" packaging/opensuse/README.md
require_contains "$contract" README.md
require_contains 'OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CONTRACT.md' docs/README.md
require_contains 'OPENSUSE_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CONTRACT.md' docs/status/README.md

require_contains 'opensuse_rpm_build_evidence_intake_denial_disposition_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'rpm_build_evidence_intake_denial_disposition_contract_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'build_evidence_intake_denial_disposition_state=closed-upheld-no-effect' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'denial_closed=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_build_evidence_intake_denial_disposition_present=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_build_evidence_intake_denial_closed=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md
require_contains 'opensuse_build_evidence_intake_denial_upheld=1' docs/status/OPENSUSE_ECOSYSTEM_INTEGRATION_STATUS.md

require_contains 'opensuse_rpm_build_evidence_intake_denial_disposition_contract_present=1' packaging/opensuse/README.md
require_contains 'rpm_build_evidence_intake_denial_disposition_contract_present=1' packaging/opensuse/README.md
require_contains 'build_evidence_intake_denial_disposition_state=closed-upheld-no-effect' packaging/opensuse/README.md
require_contains 'denial_closed=1' packaging/opensuse/README.md
require_contains 'opensuse_build_evidence_intake_denial_disposition_present=1' packaging/opensuse/README.md
require_contains 'opensuse_build_evidence_intake_denial_closed=1' packaging/opensuse/README.md
require_contains 'opensuse_build_evidence_intake_denial_upheld=1' packaging/opensuse/README.md

require_no_rpm_artifacts packaging/opensuse

require_contains 'Run openSUSE RPM build evidence intake denial disposition contract guard' .github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-contract.yml
require_contains 'sh scripts/test-opensuse-rpm-build-evidence-intake-denial-disposition-contract.sh' .github/workflows/opensuse-rpm-build-evidence-intake-denial-disposition-contract.yml

printf 'opensuse_rpm_build_evidence_intake_denial_disposition_contract: ok\n'
