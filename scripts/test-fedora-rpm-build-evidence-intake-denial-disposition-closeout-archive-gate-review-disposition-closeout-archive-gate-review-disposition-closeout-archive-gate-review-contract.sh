#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora rpm build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review contract: %s\n' "$1" >&2
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

doc='docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_CONTRACT.md'
status='docs/status/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_CONTRACT_STATUS.md'
index='docs/status/README.md'
docs_readme='docs/README.md'
readme='README.md'
packaging_readme='packaging/fedora/README.md'
test_script='scripts/test-fedora-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-contract.sh'
workflow='.github/workflows/fedora-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-contract.yml'
predecessor_doc='docs/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT.md'
predecessor_status='docs/status/FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_CONTRACT_STATUS.md'
predecessor_test='scripts/test-fedora-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-contract.sh'
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
  "$predecessor_doc" \
  "$predecessor_status" \
  "$predecessor_test" \
  "$matrix" \
  "$matrix_status" \
  "$matrix_script" \
  "$matrix_test" \
  "$spec"
do
  require_file "$file"
done

sh -n "$test_script"

require_contains 'Status: active RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review contract' "$doc"
require_contains 'documentation-only and static' "$doc"
require_contains 'uphold-closed-archive-gate' "$doc"

for current_field in \
  'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_contract_present=1' \
  'rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_contract_present=1' \
  'build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_state=reviewed-upheld-no-effect' \
  'denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_present=1' \
  'denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_state=reviewed-upheld-no-effect' \
  'denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_decision=uphold-closed-archive-gate' \
  'fedora_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_present=1' \
  'fedora_build_evidence_intake_denial_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_reviewed=1' \
  'fedora_denial_archive_allowed=0' \
  'fedora_denial_archive_record_write_allowed=0' \
  'fedora_denial_archive_record_written=0' \
  'fedora_denial_re_request_allowed=0' \
  'fedora_build_evidence_intake_allowed=0' \
  'fedora_build_evidence_intake_denied=1' \
  'fedora_platform_build_evidence_accepted=0' \
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

require_contains 'FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_CONTRACT.md' "$docs_readme"
require_contains 'FEDORA_RPM_BUILD_EVIDENCE_INTAKE_DENIAL_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_DISPOSITION_CLOSEOUT_ARCHIVE_GATE_REVIEW_CONTRACT_STATUS.md' "$index"
require_contains 'Current Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review disposition closeout archive gate review contract checkpoint' "$index"
require_contains "$doc" "$readme"
require_contains "$status" "$readme"
require_contains "$doc" "$packaging_readme"
require_contains "$test_script" "$packaging_readme"
require_contains "$workflow" "$packaging_readme"

require_contains "$doc" "$predecessor_doc"
require_contains "$status" "$predecessor_doc"
require_contains "$test_script" "$predecessor_doc"
require_contains "$workflow" "$predecessor_doc"
require_contains "$doc" "$predecessor_status"
require_contains "$status" "$predecessor_status"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_contract_present=1' "$predecessor_test"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_contract_present=1' "$matrix_script"
require_contains 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_contract_present=1' "$matrix_test"

require_contains 'Name:           latticra' "$spec"
require_no_rpm_artifacts packaging/fedora

require_contains 'name: Fedora RPM Evidence Denial Archive Gate Review Disposition Closeout Archive Gate Review' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-contract.sh' "$workflow"
require_absent 'fedpkg' "$workflow"
require_absent 'koji' "$workflow"
require_absent 'bodhi' "$workflow"
require_absent 'copr-cli' "$workflow"
require_absent 'bugzilla' "$workflow"
require_absent 'dnf ' "$workflow"
require_absent 'rpm -' "$workflow"
require_absent 'rpmbuild ' "$workflow"
require_absent 'mock -r' "$workflow"

require_contains 'sh ./scripts/test-fedora-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-contract.sh' 'Makefile'
require_contains 'fedora-rpm-build-evidence-intake-denial-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-disposition-closeout-archive-gate-review-contract:' 'Makefile'

printf 'fedora_rpm_build_evidence_intake_denial_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_disposition_closeout_archive_gate_review_contract: ok\n'
