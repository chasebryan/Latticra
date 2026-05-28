#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora rpm build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition contract: %s\n' "$1" >&2
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

doc='docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CONTRACT.md'
status='docs/status/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CONTRACT_STATUS.md'
index='docs/status/README.md'
docs_readme='docs/README.md'
readme='README.md'
packaging_readme='packaging/fedora/README.md'
test_script='scripts/test-fedora-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-contract.sh'
workflow='.github/workflows/fedora-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-contract.yml'
review_doc='docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_CONTRACT.md'
review_status='docs/status/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_CONTRACT_STATUS.md'
review_test='scripts/test-fedora-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-contract.sh'
review_workflow='.github/workflows/fedora-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-contract.yml'
archive_gate_doc='docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md'
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
  "$archive_gate_doc" \
  "$matrix" \
  "$matrix_status" \
  "$matrix_script" \
  "$matrix_test" \
  "$spec"
do
  require_file "$file"
done

sh -n "$test_script"

require_contains 'Status: active RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition contract' "$doc"
require_contains 'documentation-only and static' "$doc"
require_contains 'dispose-upheld-closeout-archive-gate-review' "$doc"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_contract_present=1' "$doc"
require_contains 'rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_contract_present=1' "$doc"
require_contains 'build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_state=disposed-upheld-no-effect' "$doc"
require_contains 'denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_present=1' "$doc"
require_contains 'denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_state=disposed-upheld-no-effect' "$doc"
require_contains 'denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_decision=dispose-upheld-closeout-archive-gate-review' "$doc"
require_contains 'fedora_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_present=1' "$doc"
require_contains 'fedora_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposed=1' "$doc"
require_contains 'fedora_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_reviewed=1' "$doc"
require_contains 'fedora_denial_archive_record_write_allowed=0' "$doc"
require_contains 'fedora_build_evidence_intake_allowed=0' "$doc"
require_contains 'fedora_platform_build_evidence_accepted=0' "$doc"
require_contains 'rpm_build_lane_opened=0' "$doc"
require_contains 'package_readiness_claimed=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"

for current_field in \
  'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_contract_present=1' \
  'rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_contract_present=1' \
  'build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_state=disposed-upheld-no-effect' \
  'denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_present=1' \
  'denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_state=disposed-upheld-no-effect' \
  'denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_decision=dispose-upheld-closeout-archive-gate-review' \
  'denial_archive_gate_review_disposition_closeout_archive_gate_review_state=reviewed-upheld-no-effect' \
  'denial_archive_gate_review_disposition_closeout_archive_gate_state=closed-no-effect' \
  'denial_archive_allowed=0' \
  'denial_archive_record_write_allowed=0' \
  'denial_archive_record_written=0' \
  'denial_re_request_allowed=0' \
  'fedora_denial_archive_allowed=0' \
  'fedora_denial_archive_record_write_allowed=0' \
  'fedora_denial_archive_record_written=0' \
  'fedora_denial_re_request_allowed=0' \
  'fedora_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_present=1' \
  'fedora_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposed=1' \
  'fedora_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_reviewed=1' \
  'fedora_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_closed=1' \
  'fedora_build_evidence_intake_denial_archive_gate_review_disposition_closed_out=1' \
  'fedora_build_evidence_intake_denial_archive_gate_review_disposed=1' \
  'fedora_build_evidence_intake_denial_archived=0' \
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
  require_contains "$current_field" "$packaging_readme"
  require_contains "$current_field" "$matrix"
  require_contains "$current_field" "$matrix_status"
done

require_contains 'FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CONTRACT.md' "$docs_readme"
require_contains 'FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CONTRACT_STATUS.md' "$index"
require_contains 'Current Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition contract checkpoint' "$index"
require_contains "$doc" "$readme"
require_contains "$status" "$readme"
require_contains "$doc" "$packaging_readme"
require_contains "$test_script" "$packaging_readme"
require_contains "$workflow" "$packaging_readme"

require_contains "$doc" "$review_doc"
require_contains "$status" "$review_doc"
require_contains "$test_script" "$review_doc"
require_contains "$workflow" "$review_doc"
require_contains "$doc" "$review_status"
require_contains "$status" "$review_status"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_contract_present=1' "$review_test"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_contract_present=1' "$matrix_script"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_contract_present=1' "$matrix_test"

require_contains 'Name:           latticra' "$spec"
require_no_rpm_artifacts packaging/fedora

require_contains 'name: Fedora RPM Evidence Denial Archive Gate Review Disposition' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-contract.sh' "$workflow"
require_absent 'fedpkg' "$workflow"
require_absent 'koji' "$workflow"
require_absent 'bodhi' "$workflow"
require_absent 'copr-cli' "$workflow"
require_absent 'bugzilla' "$workflow"
require_absent 'dnf ' "$workflow"
require_absent 'rpm -' "$workflow"
require_absent 'rpmbuild ' "$workflow"
require_absent 'mock -r' "$workflow"

require_contains 'sh ./scripts/test-fedora-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-contract.sh' 'Makefile'
require_contains 'fedora-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-contract:' 'Makefile'

printf 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_contract: ok\n'
