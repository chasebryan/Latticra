#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora rpm build-evidence intake denial disposition closeout archive gate review disposition contract: %s\n' "$1" >&2
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

doc='docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CONTRACT.md'
status='docs/status/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CONTRACT_STATUS.md'
index='docs/status/README.md'
docs_readme='docs/README.md'
readme='README.md'
packaging_readme='packaging/fedora/README.md'
test_script='scripts/test-fedora-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-contract.sh'
workflow='.github/workflows/fedora-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-contract.yml'
review_disposition_closeout_doc='docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_CONTRACT.md'
review_disposition_closeout_status='docs/status/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_CONTRACT_STATUS.md'
review_disposition_closeout_test='scripts/test-fedora-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-contract.sh'
review_disposition_closeout_workflow='.github/workflows/fedora-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-contract.yml'
archive_gate_review_doc='docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_CONTRACT.md'
archive_gate_review_status='docs/status/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_CONTRACT_STATUS.md'
archive_gate_review_test='scripts/test-fedora-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-contract.sh'
archive_gate_doc='docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md'
closeout_doc='docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_CONTRACT.md'
disposition_doc='docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CONTRACT.md'
review_doc='docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_REVIEW_CONTRACT.md'
denial_doc='docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md'
blocker_doc='docs/FEDORA_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md'
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
  "$review_disposition_closeout_doc" \
  "$review_disposition_closeout_status" \
  "$review_disposition_closeout_test" \
  "$review_disposition_closeout_workflow" \
  "$archive_gate_review_doc" \
  "$archive_gate_review_status" \
  "$archive_gate_review_test" \
  "$archive_gate_doc" \
  "$closeout_doc" \
  "$disposition_doc" \
  "$review_doc" \
  "$denial_doc" \
  "$blocker_doc" \
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

require_contains 'Status: active RPM build-evidence intake denial disposition closeout archive gate review disposition contract' "$doc"
require_contains 'documentation-only and static' "$doc"
require_contains 'write archive records' "$doc"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_contract_present=1' "$doc"
require_contains 'rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_contract_present=1' "$doc"
require_contains 'build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_state=disposed-upheld-no-effect' "$doc"
require_contains 'build_evidence_intake_denial_disposition_closeout_archive_gate_review_state=reviewed-upheld-no-effect' "$doc"
require_contains 'build_evidence_intake_denial_disposition_closeout_archive_gate_state=closed-no-effect' "$doc"
require_contains 'denial_archive_gate_review_disposition_present=1' "$doc"
require_contains 'denial_archive_gate_review_disposition_state=disposed-upheld-no-effect' "$doc"
require_contains 'denial_archive_gate_review_disposition_decision=dispose-upheld-closed-archive-gate-review' "$doc"
require_contains 'denial_archive_gate_review_present=1' "$doc"
require_contains 'denial_archive_gate_review_state=reviewed-upheld-no-effect' "$doc"
require_contains 'denial_archive_gate_present=1' "$doc"
require_contains 'denial_archive_gate_state=closed-no-effect' "$doc"
require_contains 'denial_archive_record_write_allowed=0' "$doc"
require_contains 'denial_archive_record_written=0' "$doc"
require_contains 'fedora_denial_archive_record_write_allowed=0' "$doc"
require_contains 'fedora_denial_archive_record_written=0' "$doc"
require_contains 'fedora_build_evidence_intake_denial_archive_gate_review_disposition_present=1' "$doc"
require_contains 'fedora_build_evidence_intake_denial_archive_gate_review_disposed=1' "$doc"
require_contains 'fedora_build_evidence_intake_denial_archive_gate_review_present=1' "$doc"
require_contains 'fedora_build_evidence_intake_denial_archive_gate_reviewed=1' "$doc"
require_contains 'fedora_build_evidence_intake_denial_archive_gate_closed=1' "$doc"
require_contains 'fedora_build_evidence_intake_denial_archived=0' "$doc"
require_contains 'fedora_build_evidence_intake_allowed=0' "$doc"
require_contains 'fedora_build_evidence_intake_denied=1' "$doc"
require_contains 'fedora_platform_build_evidence_accepted=0' "$doc"
require_contains 'build_transcript_intake_accepted=0' "$doc"
require_contains 'rpm_build_transcript_intake_accepted=0' "$doc"
require_contains 'fedora_build_transcript_intake_accepted=0' "$doc"
require_contains 'rpm_build_lane_opened=0' "$doc"
require_contains 'fedora_single_platform_build_lane_opened=0' "$doc"
require_contains 'source_rpm_artifact_created=0' "$doc"
require_contains 'binary_rpm_artifact_created=0' "$doc"
require_contains 'rpm_artifact_created=0' "$doc"
require_contains 'fedora_package_review_non_claim_present=1' "$doc"
require_contains 'fedora_package_validation_result_promoted=0' "$doc"
require_contains 'package_readiness_claimed=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"

for current_field in \
  'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_contract_present=1' \
  'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_contract_present=1' \
  'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_contract_present=1' \
  'fedora_rpm_build_evidence_intake_denial_disposition_closeout_contract_present=1' \
  'fedora_rpm_build_evidence_intake_denial_disposition_contract_present=1' \
  'fedora_rpm_build_evidence_intake_denial_review_contract_present=1' \
  'fedora_rpm_build_evidence_intake_denial_contract_present=1' \
  'fedora_package_validation_promotion_blocker_matrix_contract_present=1' \
  'rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_contract_present=1' \
  'rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_contract_present=1' \
  'rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_contract_present=1' \
  'rpm_build_evidence_intake_denial_disposition_closeout_contract_present=1' \
  'rpm_build_evidence_intake_denial_disposition_contract_present=1' \
  'build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_state=disposed-upheld-no-effect' \
  'build_evidence_intake_denial_disposition_closeout_archive_gate_review_state=reviewed-upheld-no-effect' \
  'build_evidence_intake_denial_disposition_closeout_archive_gate_state=closed-no-effect' \
  'build_evidence_intake_denial_disposition_closeout_state=closed-out-upheld-no-effect' \
  'build_evidence_intake_denial_disposition_state=closed-upheld-no-effect' \
  'build_evidence_intake_denial_review_state=reviewed-upheld-no-effect' \
  'build_evidence_intake_denial_state=denied-no-effect' \
  'validation_promotion_blocker_matrix_state=blocked-no-effect' \
  'fedora_package_validation_promotion_blocker_matrix_state=blocked-no-effect' \
  'fedora_mock_build_gate_state=closed-no-effect' \
  'denial_archive_gate_review_disposition_present=1' \
  'denial_archive_gate_review_disposition_state=disposed-upheld-no-effect' \
  'denial_archive_gate_review_disposition_decision=dispose-upheld-closed-archive-gate-review' \
  'denial_archive_gate_review_present=1' \
  'denial_archive_gate_review_state=reviewed-upheld-no-effect' \
  'denial_archive_gate_review_decision=uphold-closed-archive-gate' \
  'denial_archive_gate_present=1' \
  'denial_archive_gate_state=closed-no-effect' \
  'denial_archive_gate_decision=deny-archive-and-re-request' \
  'denial_disposition_closeout_present=1' \
  'denial_disposition_closeout_decision=closeout-upheld-denial' \
  'denial_disposition_present=1' \
  'denial_disposition_decision=close-upheld-denial' \
  'denial_review_present=1' \
  'denial_review_decision=uphold-denial' \
  'denial_closed=1' \
  'denial_archived=0' \
  'denial_archive_allowed=0' \
  'denial_archive_record_write_allowed=0' \
  'denial_archive_record_written=0' \
  'denial_re_request_allowed=0' \
  'fedora_denial_archive_allowed=0' \
  'fedora_denial_archive_record_write_allowed=0' \
  'fedora_denial_archive_record_written=0' \
  'fedora_denial_re_request_allowed=0' \
  'fedora_build_evidence_intake_allowed=0' \
  'fedora_build_evidence_intake_denied=1' \
  'fedora_platform_build_evidence_accepted=0' \
  'rpm_build_lane_opened=0' \
  'source_archive_accepted_for_build=0' \
  'explicit_operator_build_authorization=0' \
  'rpm_artifact_created=0' \
  'rpm_payload_accepted=0' \
  'rpm_install_remove_transcript_present=0' \
  'fedora_package_review_non_claim_present=1' \
  'fedora_package_validation_result_promoted=0' \
  'rpm_validation_result_promoted=0' \
  'package_validation_result_promoted=0' \
  'package_readiness_claimed=0' \
  'production_installer_ready=0' \
  'host_mutation_performed=0'
do
  require_contains "$current_field" "$doc"
  require_contains "$current_field" "$status"
  require_contains "$current_field" "$index"
  require_contains "$current_field" "$readme"
  require_contains "$current_field" "$matrix"
done

for disposition_field in \
  'denial_archive_gate_review_disposition_identifier' \
  'denial_archive_gate_review_reference' \
  'denial_archive_gate_reference' \
  'denial_disposition_closeout_reference' \
  'denial_disposition_reference' \
  'denial_review_reference' \
  'build_evidence_denial_reference' \
  'build_evidence_intake_request_identifier' \
  'fedora_target_distribution' \
  'requested_build_evidence_kind' \
  'requested_build_command' \
  'submitted_transcript_reference' \
  'validation_promotion_blocker_matrix_reference' \
  'denial_archive_gate_review_disposition_decision' \
  'denial_archive_gate_review_disposition_reason' \
  'denial_archive_gate_review_disposition_reviewer' \
  'archive_record_write_authorization_reference' \
  'dispose-upheld-closed-archive-gate-review' \
  'fedora_build_evidence_intake_denial_archive_gate_review_disposition_present=1' \
  'fedora_build_evidence_intake_denial_archive_gate_review_disposed=1' \
  'fedora_build_evidence_intake_denial_archive_gate_review_present=1' \
  'fedora_build_evidence_intake_denial_archive_gate_reviewed=1' \
  'fedora_build_evidence_intake_denial_archive_gate_present=1' \
  'fedora_build_evidence_intake_denial_archive_gate_closed=1' \
  'fedora_build_evidence_intake_denial_disposition_closeout_present=1' \
  'fedora_build_evidence_intake_denial_closed_out=1' \
  'fedora_build_evidence_intake_denial_archived=0' \
  'fedora_denial_archive_allowed=0' \
  'fedora_denial_archive_record_write_allowed=0' \
  'fedora_denial_archive_record_written=0' \
  'fedora_denial_re_request_allowed=0' \
  'fedora_build_transcript_intake_accepted=0' \
  'fedora_rpmbuild_evidence_accepted=0' \
  'fedora_mock_build_evidence_accepted=0' \
  'fedora_mock_buildsrpm_evidence_accepted=0' \
  'fedora_rpmlint_evidence_accepted=0' \
  'fedora_source_rpm_evidence_accepted=0' \
  'fedora_binary_rpm_evidence_accepted=0' \
  'rpmbuild_run=0' \
  'mock_build_run=0' \
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
  require_contains "$disposition_field" "$doc"
done

require_contains 'Status: rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition/status alignment' "$status"
require_contains 'Date: 2026-05-28' "$status"
require_contains 'archive gate review disposition records the reviewed Fedora build-evidence intake denial archive gate as disposed' "$status"
require_contains 'write archive records' "$status"
require_contains 'Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract before any reviewed archive gate disposition closeout archive gate can be relaxed or re-requested.' "$status"

require_contains 'FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CONTRACT_STATUS.md' "$index"
require_contains 'Current Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition contract checkpoint' "$index"
require_contains 'The Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition contract is present and records the reviewed archive gate as disposed while archive-record writes and re-request authority remain closed' "$index"

require_contains 'FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CONTRACT.md' "$docs_readme"
require_contains 'docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CONTRACT.md' "$readme"
require_contains 'docs/status/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CONTRACT_STATUS.md' "$readme"
require_contains 'The Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition contract is present' "$readme"

require_contains 'docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CONTRACT.md' "$packaging_readme"
require_contains 'scripts/test-fedora-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-contract.sh' "$packaging_readme"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_contract_present=1' "$packaging_readme"
require_contains 'build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_state=disposed-upheld-no-effect' "$packaging_readme"
require_contains 'denial_archive_gate_review_disposition_present=1' "$packaging_readme"
require_contains 'denial_archive_gate_review_disposition_decision=dispose-upheld-closed-archive-gate-review' "$packaging_readme"

require_contains "$review_disposition_closeout_doc" "$doc"
require_contains "$review_disposition_closeout_status" "$doc"
require_contains "$review_disposition_closeout_test" "$doc"
require_contains "$review_disposition_closeout_workflow" "$doc"
require_contains "$review_disposition_closeout_doc" "$status"
require_contains "$review_disposition_closeout_status" "$status"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_contract_present=1' "$review_disposition_closeout_doc"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_contract_present=1' "$review_disposition_closeout_status"
require_contains "$doc" "$archive_gate_review_doc"
require_contains "$status" "$archive_gate_review_doc"
require_contains "$test_script" "$archive_gate_review_doc"
require_contains "$workflow" "$archive_gate_review_doc"
require_contains "$doc" "$archive_gate_review_status"
require_contains "$status" "$archive_gate_review_status"
require_contains 'Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract before any reviewed archive gate disposition closeout archive gate can be relaxed or re-requested.' "$archive_gate_review_doc"
require_contains 'Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract before any reviewed archive gate disposition closeout archive gate can be relaxed or re-requested.' "$archive_gate_review_status"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_contract_present=1' "$archive_gate_review_test"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_contract_present=1' "$matrix"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_contract_present=1' "$matrix_script"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_contract_present=1' "$matrix_status"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_contract_present=1' "$matrix_test"

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
  "$denial_doc" \
  "$review_doc" \
  "$disposition_doc" \
  "$closeout_doc" \
  "$archive_gate_doc" \
  "$archive_gate_review_doc" \
  "$matrix"
do
  require_contains "$dependency" "$doc"
done

require_contains 'Name:           latticra' "$spec"
require_no_rpm_artifacts packaging/fedora

require_contains 'name: Fedora RPM Evidence Denial Gate Review Disposition' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-contract.sh' "$workflow"
require_absent 'fedpkg' "$workflow"
require_absent 'koji' "$workflow"
require_absent 'bodhi' "$workflow"
require_absent 'copr-cli' "$workflow"
require_absent 'bugzilla' "$workflow"
require_absent 'dnf ' "$workflow"
require_absent 'rpm -' "$workflow"
require_absent 'rpmbuild ' "$workflow"
require_absent 'mock -r' "$workflow"

require_contains 'sh ./scripts/test-fedora-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-contract.sh' 'Makefile'
require_contains 'fedora-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-contract:' 'Makefile'

printf 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_contract: ok\n'
