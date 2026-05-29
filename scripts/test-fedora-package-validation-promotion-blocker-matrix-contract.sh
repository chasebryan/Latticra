#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora package validation promotion blocker matrix contract: %s\n' "$1" >&2
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

doc='docs/FEDORA_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md'
status='docs/status/FEDORA_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT_STATUS.md'
index='docs/status/README.md'
docs_readme='docs/README.md'
readme='README.md'
packaging_readme='packaging/fedora/README.md'
test_script='scripts/test-fedora-package-validation-promotion-blocker-matrix-contract.sh'
workflow='.github/workflows/fedora-package-validation-promotion-blocker-matrix-contract.yml'
package_review_doc='docs/FEDORA_PACKAGE_REVIEW_NON_CLAIM_CONTRACT.md'
package_review_status='docs/status/FEDORA_PACKAGE_REVIEW_NON_CLAIM_CONTRACT_STATUS.md'
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
intake_doc='docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md'
intake_status='docs/status/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT_STATUS.md'
intake_test='scripts/test-fedora-rpm-build-evidence-intake-denial-contract.sh'
intake_workflow='.github/workflows/fedora-rpm-build-evidence-intake-denial-contract.yml'
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
  "$package_review_doc" \
  "$package_review_status" \
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
  "$intake_doc" \
  "$intake_status" \
  "$intake_test" \
  "$intake_workflow" \
  "$spec"
do
  require_file "$file"
done

sh -n "$test_script"

require_contains 'Status: active package validation promotion blocker matrix contract' "$doc"
require_contains 'documentation-only and static' "$doc"
require_contains 'fedora_package_validation_promotion_blocker_matrix_contract_present=1' "$doc"
require_contains 'fedora_package_review_non_claim_contract_present=1' "$doc"
require_contains 'package_validation_promotion_blocker_matrix_contract_present=1' "$doc"
require_contains 'package_validation_promotion_blocker_matrix_present=1' "$doc"
require_contains 'validation_promotion_blocker_matrix_state=blocked-no-effect' "$doc"
require_contains 'fedora_package_validation_promotion_blocker_matrix_state=blocked-no-effect' "$doc"
require_contains 'package_validation_promotion_blocker_matrix_state=blocked-no-effect' "$doc"
require_contains 'fedora_mock_build_gate_state=closed-no-effect' "$doc"
require_contains 'package_review_non_claim_state=specified-no-effect' "$doc"
require_contains 'install_remove_transcript_contract_state=specified-no-effect' "$doc"
require_contains 'payload_inspection_contract_state=specified-no-effect' "$doc"
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
require_contains 'fedora_platform_build_evidence_accepted=0' "$doc"
require_contains 'fedora_package_validation_result_promoted=0' "$doc"
require_contains 'rpm_validation_result_promoted=0' "$doc"
require_contains 'package_validation_result_promoted=0' "$doc"
require_contains 'fedora_package_review_ready=0' "$doc"
require_contains 'fedora_distribution_ready=0' "$doc"
require_contains 'package_readiness_claimed=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'root_installer_ready=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"

for current_field in \
  'fedora_package_validation_promotion_blocker_matrix_contract_present=1' \
  'fedora_package_review_non_claim_contract_present=1' \
  'package_validation_promotion_blocker_matrix_contract_present=1' \
  'package_validation_promotion_blocker_matrix_present=1' \
  'validation_promotion_blocker_matrix_state=blocked-no-effect' \
  'fedora_package_validation_promotion_blocker_matrix_state=blocked-no-effect' \
  'package_validation_promotion_blocker_matrix_state=blocked-no-effect' \
  'fedora_mock_build_gate_state=closed-no-effect' \
  'package_review_non_claim_state=specified-no-effect' \
  'install_remove_transcript_contract_state=specified-no-effect' \
  'payload_inspection_contract_state=specified-no-effect' \
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
  'fedora_platform_build_evidence_accepted=0' \
  'fedora_package_validation_result_promoted=0' \
  'rpm_validation_result_promoted=0' \
  'package_validation_result_promoted=0' \
  'fedora_package_review_ready=0' \
  'fedora_distribution_ready=0' \
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

for blocker_field in \
  'source_archive_column_state=blocked' \
  'rpmlint_column_state=blocked' \
  'environment_column_state=blocked' \
  'artifact_column_state=blocked' \
  'payload_column_state=blocked' \
  'install_remove_column_state=blocked' \
  'package_review_non_claim_column_state=specified' \
  'fedora_distribution_non_claim_column_state=specified' \
  'promotion_column_state=blocked' \
  'archive_sha256_bound_to_build=1' \
  'fedora_official_package_claimed=0' \
  'fedora_package_validation_promotion_blocked=1' \
  'fedora_source_archive_accepted_for_build=0' \
  'fedora_rpmlint_transcript_accepted=0' \
  'fedora_build_environment_provisioned=0' \
  'fedora_mock_build_environment_provisioned=0' \
  'fedora_source_rpm_artifact_created=0' \
  'fedora_binary_rpm_artifact_created=0' \
  'fedora_payload_inspection_run=0' \
  'fedora_install_remove_transcript_present=0' \
  'fedora_package_review_claimed=0' \
  'rpmbuild_run=0' \
  'mock_build_run=0' \
  'mock_buildsrpm_run=0' \
  'rpmlint_run=0' \
  'dnf_builddep_run=0' \
  'fedpkg_run=0' \
  'koji_run=0' \
  'bodhi_run=0' \
  'platform_under_review' \
  'fedora_target_distribution' \
  'source_archive_contract_reference' \
  'source_archive_sha256' \
  'rpmlint_transcript_sha256' \
  'environment_transcript_sha256' \
  'rpm_source_artifact_name' \
  'source_rpm_artifact_sha256' \
  'binary_rpm_artifact_name' \
  'binary_rpm_artifact_sha256' \
  'payload_inspection_transcript_sha256' \
  'install_remove_transcript_sha256' \
  'fedora_package_review_non_claim_reference' \
  'promotion_reviewer' \
  'promotion_decision' \
  'promotion_scope' \
  'status_page_update_reference' \
  'operator_authorization_reference'
do
  require_contains "$blocker_field" "$doc"
done

require_contains 'Status: package-validation-promotion-blocker-matrix/status alignment' "$status"
require_contains 'Date: 2026-05-28' "$status"
require_contains 'does not run `rpmbuild`, `mock`, `rpmlint`, `dnf`, `fedpkg`, `koji`, `bodhi`, or `copr-cli`' "$status"
require_contains 'does not create RPM artifacts' "$status"
require_contains 'docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_CONTRACT.md' "$status"
require_contains 'Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract' "$status"

require_contains 'FEDORA_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT_STATUS.md' "$index"
require_contains 'Current Fedora package validation promotion blocker matrix contract checkpoint' "$index"
require_contains 'The Fedora package validation promotion blocker matrix is present but keeps every Fedora build-evidence and promotion column blocked' "$index"

require_contains 'FEDORA_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md' "$docs_readme"
require_contains 'docs/FEDORA_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md' "$readme"
require_contains 'docs/status/FEDORA_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT_STATUS.md' "$readme"
require_contains 'The Fedora package validation promotion blocker matrix is present' "$readme"

require_contains 'docs/FEDORA_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md' "$packaging_readme"
require_contains 'scripts/test-fedora-package-validation-promotion-blocker-matrix-contract.sh' "$packaging_readme"
require_contains 'fedora_package_validation_promotion_blocker_matrix_contract_present=1' "$packaging_readme"
require_contains 'validation_promotion_blocker_matrix_state=blocked-no-effect' "$packaging_readme"

require_contains "$doc" "$package_review_doc"
require_contains "$doc" "$package_review_status"
require_contains "$intake_doc" "$doc"
require_contains "$intake_test" "$doc"
require_contains "$intake_workflow" "$doc"
require_contains 'Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract before any reviewed archive gate disposition closeout archive gate can be relaxed or re-requested.' "$doc"
require_contains 'Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract before any reviewed archive gate disposition closeout archive gate can be relaxed or re-requested.' "$status"
require_contains 'fedora_package_validation_promotion_blocker_matrix_contract_present=1' "$matrix_script"
require_contains 'fedora_package_validation_promotion_blocker_matrix_contract_present=1' "$matrix_status"
require_contains 'fedora_package_validation_promotion_blocker_matrix_contract_present=1' "$matrix_test"

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
  "$matrix"
do
  require_contains "$dependency" "$doc"
done

require_contains 'Name:           latticra' "$spec"
require_no_rpm_artifacts packaging/fedora

require_contains 'name: Fedora Package Validation Promotion Blocker Matrix Contract' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-package-validation-promotion-blocker-matrix-contract.sh' "$workflow"
require_absent 'fedpkg' "$workflow"
require_absent 'koji' "$workflow"
require_absent 'bodhi' "$workflow"
require_absent 'copr-cli' "$workflow"
require_absent 'bugzilla' "$workflow"
require_absent 'dnf ' "$workflow"
require_absent 'rpm -' "$workflow"
require_absent 'rpmbuild ' "$workflow"
require_absent 'mock -r' "$workflow"

require_contains 'sh ./scripts/test-fedora-package-validation-promotion-blocker-matrix-contract.sh' 'Makefile'
require_contains 'fedora-package-validation-promotion-blocker-matrix-contract:' 'Makefile'

printf 'fedora_package_validation_promotion_blocker_matrix_contract: ok\n'
