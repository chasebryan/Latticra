#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora rpm build-evidence intake denial contract: %s\n' "$1" >&2
  exit 1
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file"
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    fail "missing required pattern in $file: $pattern"
  fi
}

require_absent() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    fail "unexpected pattern in $file: $pattern"
  fi
}

require_no_rpm_artifacts() {
  dir="$1"
  if find "$dir" \( -name '*.rpm' -o -name '*.src.rpm' \) -print | grep -q .; then
    fail "unexpected RPM artifact under $dir"
  fi
}

doc='docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md'
status='docs/status/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT_STATUS.md'
index='docs/status/README.md'
docs_readme='docs/README.md'
readme='README.md'
packaging_readme='packaging/fedora/README.md'
test_script='scripts/test-fedora-rpm-build-evidence-intake-denial-contract.sh'
workflow='.github/workflows/fedora-rpm-build-evidence-intake-denial-contract.yml'
review_doc='docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_REVIEW_CONTRACT.md'
review_status='docs/status/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_REVIEW_CONTRACT_STATUS.md'
review_test='scripts/test-fedora-rpm-build-evidence-intake-denial-review-contract.sh'
review_workflow='.github/workflows/fedora-rpm-build-evidence-intake-denial-review-contract.yml'
blocker_doc='docs/FEDORA_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md'
blocker_status='docs/status/FEDORA_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT_STATUS.md'
package_review_doc='docs/FEDORA_PACKAGE_REVIEW_NON_CLAIM_CONTRACT.md'
install_remove_doc='docs/FEDORA_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md'
payload_doc='docs/FEDORA_RPM_PAYLOAD_INSPECTION_CONTRACT.md'
artifact_doc='docs/FEDORA_RPM_ARTIFACT_NAMING_CONTRACT.md'
environment_doc='docs/FEDORA_LOCAL_MOCK_BUILD_ENVIRONMENT_CONTRACT.md'
gate_doc='docs/FEDORA_LOCAL_MOCK_BUILD_GATE_CONTRACT.md'
handoff_doc='docs/FEDORA_SOURCE_ARCHIVE_MOCK_BUILD_INPUT_HANDOFF_CONTRACT.md'
source_archive_doc='docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md'
rpmlint_classification='docs/FEDORA_RPMLINT_FINDINGS_CLASSIFICATION.md'
matrix='docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md'
matrix_status='docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md'
matrix_script='scripts/fedora-production-readiness-evidence-matrix.sh'
matrix_test='scripts/test-fedora-production-readiness-evidence-matrix.sh'
spec='packaging/fedora/latticra.spec'

for file in \
  "$doc" \
  "$status" \
  "$index" \
  "$docs_readme" \
  "$readme" \
  "$packaging_readme" \
  "$test_script" \
  "$workflow" \
  "$review_doc" \
  "$review_status" \
  "$review_test" \
  "$review_workflow" \
  "$blocker_doc" \
  "$blocker_status" \
  "$package_review_doc" \
  "$install_remove_doc" \
  "$payload_doc" \
  "$artifact_doc" \
  "$environment_doc" \
  "$gate_doc" \
  "$handoff_doc" \
  "$source_archive_doc" \
  "$rpmlint_classification" \
  "$matrix" \
  "$matrix_status" \
  "$matrix_script" \
  "$matrix_test" \
  "$spec"
do
  require_file "$file"
done

sh -n "$test_script"

require_contains 'Status: active RPM build-evidence intake denial contract' "$doc"
require_contains 'documentation-only and static' "$doc"
require_contains 'fedora_rpm_build_evidence_intake_denial_contract_present=1' "$doc"
require_contains 'fedora_package_validation_promotion_blocker_matrix_contract_present=1' "$doc"
require_contains 'rpm_build_evidence_intake_denial_contract_present=1' "$doc"
require_contains 'build_evidence_intake_denial_state=denied-no-effect' "$doc"
require_contains 'validation_promotion_blocker_matrix_state=blocked-no-effect' "$doc"
require_contains 'fedora_package_validation_promotion_blocker_matrix_state=blocked-no-effect' "$doc"
require_contains 'fedora_mock_build_gate_state=closed-no-effect' "$doc"
require_contains 'fedora_build_evidence_intake_allowed=0' "$doc"
require_contains 'fedora_build_evidence_intake_requested=0' "$doc"
require_contains 'fedora_build_evidence_intake_denied=1' "$doc"
require_contains 'fedora_platform_build_evidence_accepted=0' "$doc"
require_contains 'build_transcript_intake_accepted=0' "$doc"
require_contains 'rpm_build_transcript_intake_accepted=0' "$doc"
require_contains 'fedora_build_transcript_intake_accepted=0' "$doc"
require_contains 'rpmbuild_evidence_accepted=0' "$doc"
require_contains 'mock_build_evidence_accepted=0' "$doc"
require_contains 'mock_buildsrpm_evidence_accepted=0' "$doc"
require_contains 'rpmlint_evidence_accepted=0' "$doc"
require_contains 'source_rpm_evidence_accepted=0' "$doc"
require_contains 'binary_rpm_evidence_accepted=0' "$doc"
require_contains 'fedora_rpmbuild_evidence_accepted=0' "$doc"
require_contains 'fedora_mock_build_evidence_accepted=0' "$doc"
require_contains 'fedora_mock_buildsrpm_evidence_accepted=0' "$doc"
require_contains 'fedora_rpmlint_evidence_accepted=0' "$doc"
require_contains 'fedora_source_rpm_evidence_accepted=0' "$doc"
require_contains 'fedora_binary_rpm_evidence_accepted=0' "$doc"
require_contains 'rpm_build_lane_opened=0' "$doc"
require_contains 'fedora_single_platform_build_lane_opened=0' "$doc"
require_contains 'source_archive_accepted_for_build=0' "$doc"
require_contains 'accepted_rpmlint_transcript_present=0' "$doc"
require_contains 'environment_transcript_present=0' "$doc"
require_contains 'explicit_operator_build_authorization=0' "$doc"
require_contains 'source_rpm_artifact_created=0' "$doc"
require_contains 'binary_rpm_artifact_created=0' "$doc"
require_contains 'rpm_artifact_created=0' "$doc"
require_contains 'rpm_artifact_sha256_recorded=0' "$doc"
require_contains 'rpm_payload_accepted=0' "$doc"
require_contains 'rpm_install_remove_transcript_present=0' "$doc"
require_contains 'fedora_package_review_non_claim_present=1' "$doc"
require_contains 'fedora_package_validation_result_promoted=0' "$doc"
require_contains 'rpm_validation_result_promoted=0' "$doc"
require_contains 'package_validation_result_promoted=0' "$doc"
require_contains 'package_readiness_claimed=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'root_installer_ready=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"

for current_field in \
  'fedora_rpm_build_evidence_intake_denial_contract_present=1' \
  'fedora_package_validation_promotion_blocker_matrix_contract_present=1' \
  'rpm_build_evidence_intake_denial_contract_present=1' \
  'build_evidence_intake_denial_state=denied-no-effect' \
  'validation_promotion_blocker_matrix_state=blocked-no-effect' \
  'fedora_package_validation_promotion_blocker_matrix_state=blocked-no-effect' \
  'fedora_mock_build_gate_state=closed-no-effect' \
  'fedora_build_evidence_intake_allowed=0' \
  'fedora_build_evidence_intake_requested=0' \
  'fedora_build_evidence_intake_denied=1' \
  'fedora_platform_build_evidence_accepted=0' \
  'build_transcript_intake_accepted=0' \
  'rpm_build_transcript_intake_accepted=0' \
  'fedora_build_transcript_intake_accepted=0' \
  'rpmbuild_evidence_accepted=0' \
  'mock_build_evidence_accepted=0' \
  'mock_buildsrpm_evidence_accepted=0' \
  'rpmlint_evidence_accepted=0' \
  'source_rpm_evidence_accepted=0' \
  'binary_rpm_evidence_accepted=0' \
  'fedora_rpmbuild_evidence_accepted=0' \
  'fedora_mock_build_evidence_accepted=0' \
  'fedora_mock_buildsrpm_evidence_accepted=0' \
  'fedora_rpmlint_evidence_accepted=0' \
  'fedora_source_rpm_evidence_accepted=0' \
  'fedora_binary_rpm_evidence_accepted=0' \
  'rpm_build_lane_opened=0' \
  'fedora_single_platform_build_lane_opened=0' \
  'source_archive_accepted_for_build=0' \
  'accepted_rpmlint_transcript_present=0' \
  'environment_transcript_present=0' \
  'explicit_operator_build_authorization=0' \
  'source_rpm_artifact_created=0' \
  'binary_rpm_artifact_created=0' \
  'rpm_artifact_created=0' \
  'rpm_artifact_sha256_recorded=0' \
  'rpm_payload_accepted=0' \
  'rpm_install_remove_transcript_present=0' \
  'fedora_package_review_non_claim_present=1' \
  'fedora_package_validation_result_promoted=0' \
  'rpm_validation_result_promoted=0' \
  'package_validation_result_promoted=0' \
  'package_readiness_claimed=0' \
  'production_installer_ready=0' \
  'root_installer_ready=0' \
  'host_mutation_performed=0'
do
  require_contains "$current_field" "$doc"
  require_contains "$current_field" "$status"
  require_contains "$current_field" "$index"
  require_contains "$current_field" "$readme"
  require_contains "$current_field" "$matrix"
done

for denial_field in \
  'build_evidence_denial_reason=validation-promotion-blocker-matrix-closed' \
  'source_archive_column_state=blocked' \
  'rpmlint_column_state=blocked' \
  'environment_column_state=blocked' \
  'artifact_column_state=blocked' \
  'payload_column_state=blocked' \
  'install_remove_column_state=blocked' \
  'package_review_non_claim_column_state=specified' \
  'fedora_distribution_non_claim_column_state=specified' \
  'promotion_column_state=blocked' \
  'denial_review_required_before_re_request=1' \
  'denial_re_request_allowed=0' \
  'build_evidence_intake_request_identifier' \
  'fedora_target_distribution' \
  'requested_build_evidence_kind' \
  'requested_build_command' \
  'submitted_transcript_reference' \
  'source_archive_sha256' \
  'rpmlint_transcript_reference' \
  'environment_identifier' \
  'operator_authorization_reference' \
  'validation_promotion_blocker_matrix_reference' \
  'denial_decision' \
  'denial_reason' \
  'denial_reviewer' \
  'status_page_update_reference' \
  'rpmbuild_run=0' \
  'rpmbuild_ba_run=0' \
  'rpmbuild_bb_run=0' \
  'rpmbuild_bs_run=0' \
  'mock_build_run=0' \
  'mock_buildsrpm_run=0' \
  'rpmlint_run=0' \
  'dnf_builddep_run=0' \
  'fedpkg_run=0' \
  'koji_run=0' \
  'bodhi_run=0' \
  'fedora_package_review_request_created=0' \
  'fedora_koji_build_run=0' \
  'fedora_bodhi_update_created=0' \
  'fedora_rawhide_submission_claimed=0' \
  'fedora_official_package_claimed=0' \
  'fedora_distribution_ready=0'
do
  require_contains "$denial_field" "$doc"
done

require_contains 'Status: rpm-build-evidence-intake-denial/status alignment' "$status"
require_contains 'Date: 2026-05-28' "$status"
require_contains 'does not run `rpmbuild`, `mock`, `rpmlint`, `dnf`, `fedpkg`, `koji`, `bodhi`, or `copr-cli`' "$status"
require_contains 'does not request build evidence' "$status"
require_contains 'Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract' "$status"
require_contains "$review_doc" "$doc"
require_contains "$review_test" "$doc"
require_contains "$review_workflow" "$doc"
require_contains "$review_doc" "$status"
require_contains "$review_test" "$status"
require_contains "$review_workflow" "$status"

require_contains 'FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT_STATUS.md' "$index"
require_contains 'Current Fedora RPM build-evidence intake denial contract checkpoint' "$index"
require_contains 'The Fedora RPM build-evidence intake denial contract is present and denies any request, receipt, or acceptance of Fedora build evidence while the blocker matrix remains closed' "$index"

require_contains 'FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md' "$docs_readme"
require_contains 'docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md' "$readme"
require_contains 'docs/status/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT_STATUS.md' "$readme"
require_contains 'The Fedora RPM build-evidence intake denial contract is present' "$readme"

require_contains 'docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md' "$packaging_readme"
require_contains 'scripts/test-fedora-rpm-build-evidence-intake-denial-contract.sh' "$packaging_readme"
require_contains 'fedora_rpm_build_evidence_intake_denial_contract_present=1' "$packaging_readme"
require_contains 'build_evidence_intake_denial_state=denied-no-effect' "$packaging_readme"

require_contains "$doc" "$blocker_doc"
require_contains "$doc" "$blocker_status"
require_contains 'Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract before any reviewed archive gate disposition closeout archive gate can be relaxed or re-requested.' "$blocker_doc"
require_contains 'Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract before any reviewed archive gate disposition closeout archive gate can be relaxed or re-requested.' "$blocker_status"
require_contains 'fedora_rpm_build_evidence_intake_denial_contract_present=1' "$matrix_script"
require_contains 'fedora_rpm_build_evidence_intake_denial_contract_present=1' "$matrix_status"
require_contains 'fedora_rpm_build_evidence_intake_denial_contract_present=1' "$matrix_test"

for dependency in \
  "$rpmlint_classification" \
  "$source_archive_doc" \
  "$handoff_doc" \
  "$gate_doc" \
  "$environment_doc" \
  "$artifact_doc" \
  "$payload_doc" \
  "$install_remove_doc" \
  "$package_review_doc" \
  "$blocker_doc" \
  "$matrix"
do
  require_contains "$dependency" "$doc"
done

require_contains 'Name:           latticra' "$spec"
require_no_rpm_artifacts packaging/fedora

require_contains 'name: Fedora RPM Build Evidence Intake Denial Contract' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-rpm-build-evidence-intake-denial-contract.sh' "$workflow"
require_absent 'fedpkg' "$workflow"
require_absent 'koji' "$workflow"
require_absent 'bodhi' "$workflow"
require_absent 'copr-cli' "$workflow"
require_absent 'bugzilla' "$workflow"
require_absent 'dnf ' "$workflow"
require_absent 'rpm -' "$workflow"
require_absent 'rpmbuild ' "$workflow"
require_absent 'mock -r' "$workflow"

require_contains 'sh ./scripts/test-fedora-rpm-build-evidence-intake-denial-contract.sh' 'Makefile'
require_contains 'fedora-rpm-build-evidence-intake-denial-contract:' 'Makefile'

printf 'fedora_rpm_build_evidence_intake_denial_contract: ok\n'
