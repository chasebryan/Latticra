#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora package review non-claim contract: %s\n' "$1" >&2
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

doc='docs/FEDORA_PACKAGE_REVIEW_NON_CLAIM_CONTRACT.md'
status='docs/status/FEDORA_PACKAGE_REVIEW_NON_CLAIM_CONTRACT_STATUS.md'
index='docs/status/README.md'
docs_readme='docs/README.md'
readme='README.md'
packaging_readme='packaging/fedora/README.md'
test_script='scripts/test-fedora-package-review-non-claim-contract.sh'
workflow='.github/workflows/fedora-package-review-non-claim-contract.yml'
install_remove_doc='docs/FEDORA_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT.md'
install_remove_status='docs/status/FEDORA_RPM_INSTALL_REMOVE_TRANSCRIPT_CONTRACT_STATUS.md'
payload_doc='docs/FEDORA_RPM_PAYLOAD_INSPECTION_CONTRACT.md'
artifact_doc='docs/FEDORA_RPM_ARTIFACT_NAMING_CONTRACT.md'
environment_doc='docs/FEDORA_LOCAL_MOCK_BUILD_ENVIRONMENT_CONTRACT.md'
gate_doc='docs/FEDORA_LOCAL_MOCK_BUILD_GATE_CONTRACT.md'
handoff_doc='docs/FEDORA_SOURCE_ARCHIVE_MOCK_BUILD_INPUT_HANDOFF_CONTRACT.md'
rpmlint_classification='docs/FEDORA_RPMLINT_FINDINGS_CLASSIFICATION.md'
matrix='docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md'
matrix_status='docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md'
matrix_script='scripts/fedora-production-readiness-evidence-matrix.sh'
matrix_test='scripts/test-fedora-production-readiness-evidence-matrix.sh'
blocker_doc='docs/FEDORA_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md'
blocker_status='docs/status/FEDORA_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT_STATUS.md'
blocker_test='scripts/test-fedora-package-validation-promotion-blocker-matrix-contract.sh'
blocker_workflow='.github/workflows/fedora-package-validation-promotion-blocker-matrix-contract.yml'
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
  "$install_remove_doc" \
  "$install_remove_status" \
  "$payload_doc" \
  "$artifact_doc" \
  "$environment_doc" \
  "$gate_doc" \
  "$handoff_doc" \
  "$rpmlint_classification" \
  "$matrix" \
  "$matrix_status" \
  "$matrix_script" \
  "$matrix_test" \
  "$blocker_doc" \
  "$blocker_status" \
  "$blocker_test" \
  "$blocker_workflow" \
  "$spec"
do
  require_file "$file"
done

sh -n "$test_script"

require_contains 'Status: no-effect package review non-claim contract' "$doc"
require_contains 'documentation-only and static' "$doc"
require_contains 'fedora_package_review_non_claim_contract_present=1' "$doc"
require_contains 'fedora_rpm_install_remove_transcript_contract_present=1' "$doc"
require_contains 'package_review_non_claim_contract_present=1' "$doc"
require_contains 'package_review_non_claim_present=1' "$doc"
require_contains 'fedora_package_review_non_claim_present=1' "$doc"
require_contains 'fedora_package_review_non_claim_contract_state=specified-no-effect' "$doc"
require_contains 'package_review_non_claim_state=specified-no-effect' "$doc"
require_contains 'install_remove_transcript_contract_state=specified-no-effect' "$doc"
require_contains 'payload_inspection_contract_state=specified-no-effect' "$doc"
require_contains 'fedora_mock_build_gate_state=closed-no-effect' "$doc"
require_contains 'rpm_validation_result_promoted=0' "$doc"
require_contains 'rpm_artifact_created=0' "$doc"
require_contains 'rpm_artifact_published=0' "$doc"
require_contains 'fedora_package_review_bug_created=0' "$doc"
require_contains 'fedora_bugzilla_review_ticket_created=0' "$doc"
require_contains 'fedora_package_review_request_created=0' "$doc"
require_contains 'fedora_package_review_approved=0' "$doc"
require_contains 'fedora_scm_request_created=0' "$doc"
require_contains 'fedora_dist_git_repo_created=0' "$doc"
require_contains 'fedora_koji_build_run=0' "$doc"
require_contains 'fedora_bodhi_update_created=0' "$doc"
require_contains 'fedora_rawhide_submission_claimed=0' "$doc"
require_contains 'fedora_rawhide_acceptance_claimed=0' "$doc"
require_contains 'fedora_official_package_claimed=0' "$doc"
require_contains 'fedora_packager_sponsor_claimed=0' "$doc"
require_contains 'fedora_endorsement_claimed=0' "$doc"
require_contains 'fedora_package_review_ready=0' "$doc"
require_contains 'fedora_distribution_ready=0' "$doc"
require_contains 'package_readiness_claimed=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'root_installer_ready=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'docs/FEDORA_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md' "$doc"
require_contains 'scripts/test-fedora-package-validation-promotion-blocker-matrix-contract.sh' "$doc"
require_contains '.github/workflows/fedora-package-validation-promotion-blocker-matrix-contract.yml' "$doc"
require_contains 'Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract' "$doc"
require_contains 'fedora_package_review_non_claim_contract: ok' "$doc"

for current_field in \
  'fedora_package_review_non_claim_contract_present=1' \
  'fedora_rpm_install_remove_transcript_contract_present=1' \
  'package_review_non_claim_contract_present=1' \
  'package_review_non_claim_present=1' \
  'fedora_package_review_non_claim_present=1' \
  'fedora_package_review_non_claim_contract_state=specified-no-effect' \
  'package_review_non_claim_state=specified-no-effect' \
  'install_remove_transcript_contract_state=specified-no-effect' \
  'payload_inspection_contract_state=specified-no-effect' \
  'fedora_mock_build_gate_state=closed-no-effect' \
  'rpm_validation_result_promoted=0' \
  'rpm_artifact_created=0' \
  'rpm_artifact_published=0' \
  'fedora_package_review_bug_created=0' \
  'fedora_bugzilla_review_ticket_created=0' \
  'fedora_package_review_request_created=0' \
  'fedora_package_review_approved=0' \
  'fedora_scm_request_created=0' \
  'fedora_dist_git_repo_created=0' \
  'fedora_koji_build_run=0' \
  'fedora_bodhi_update_created=0' \
  'fedora_rawhide_submission_claimed=0' \
  'fedora_rawhide_acceptance_claimed=0' \
  'fedora_official_package_claimed=0' \
  'fedora_packager_sponsor_claimed=0' \
  'fedora_endorsement_claimed=0' \
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

for non_claim_field in \
  'fedora_package_review_non_claim_required=1' \
  'fedora_package_review_non_claim_present=1' \
  'fedora_reviewer_approval_recorded=0' \
  'fedora_package_repository_created=0' \
  'rpm_validation_result_identifier' \
  'fedora_target_distribution' \
  'source_archive_sha256' \
  'source_rpm_artifact_sha256' \
  'binary_rpm_artifact_sha256' \
  'payload_inspection_transcript_sha256' \
  'install_remove_transcript_sha256' \
  'fedora_package_review_non_claim_reviewer' \
  'fedora_package_review_non_claim_review_date' \
  'non_claimed_fedora_review_targets' \
  'non_claimed_fedora_distribution_targets' \
  'status_page_update_reference' \
  'operator_authorization_reference'
do
  require_contains "$non_claim_field" "$doc"
done

require_contains 'Status: package-review-non-claim/status alignment' "$status"
require_contains 'Date: 2026-05-28' "$status"
require_contains 'does not run `fedpkg`, `koji`, `bodhi`' "$status"
require_contains 'does not create Bugzilla tickets' "$status"
require_contains 'docs/FEDORA_PACKAGE_VALIDATION_PROMOTION_BLOCKER_MATRIX_CONTRACT.md' "$status"
require_contains 'Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract' "$status"

require_contains 'FEDORA_PACKAGE_REVIEW_NON_CLAIM_CONTRACT_STATUS.md' "$index"
require_contains 'Current Fedora package review non-claim contract checkpoint' "$index"
require_contains 'The Fedora package review non-claim contract is present but creates no package review tickets' "$index"

require_contains 'FEDORA_PACKAGE_REVIEW_NON_CLAIM_CONTRACT.md' "$docs_readme"
require_contains 'docs/FEDORA_PACKAGE_REVIEW_NON_CLAIM_CONTRACT.md' "$readme"
require_contains 'docs/status/FEDORA_PACKAGE_REVIEW_NON_CLAIM_CONTRACT_STATUS.md' "$readme"
require_contains 'The Fedora package review non-claim contract is present' "$readme"

require_contains 'docs/FEDORA_PACKAGE_REVIEW_NON_CLAIM_CONTRACT.md' "$packaging_readme"
require_contains 'scripts/test-fedora-package-review-non-claim-contract.sh' "$packaging_readme"
require_contains 'fedora_package_review_non_claim_contract_present=1' "$packaging_readme"
require_contains 'fedora_package_review_non_claim_contract_state=specified-no-effect' "$packaging_readme"

require_contains "$doc" "$install_remove_doc"
require_contains "$doc" "$install_remove_status"
require_contains 'fedora_package_review_non_claim_contract_present=1' "$matrix_script"
require_contains 'fedora_package_review_non_claim_contract_present=1' "$matrix_status"
require_contains 'fedora_package_review_non_claim_contract_present=1' "$matrix_test"

require_contains 'Name:           latticra' "$spec"
require_no_rpm_artifacts packaging/fedora

require_contains 'name: Fedora Package Review Non Claim Contract' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-package-review-non-claim-contract.sh' "$workflow"
require_absent 'fedpkg' "$workflow"
require_absent 'koji' "$workflow"
require_absent 'bodhi' "$workflow"
require_absent 'copr-cli' "$workflow"
require_absent 'bugzilla' "$workflow"
require_absent 'dnf ' "$workflow"
require_absent 'rpm -' "$workflow"
require_absent 'rpmbuild ' "$workflow"
require_absent 'mock -r' "$workflow"

require_contains 'sh ./scripts/test-fedora-package-review-non-claim-contract.sh' 'Makefile'
require_contains 'fedora-package-review-non-claim-contract:' 'Makefile'

printf 'fedora_package_review_non_claim_contract: ok\n'
