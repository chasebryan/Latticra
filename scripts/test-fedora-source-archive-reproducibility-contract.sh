#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora source archive reproducibility contract: %s\n' "$1" >&2
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

doc='docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md'
status='docs/status/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT_STATUS.md'
index='docs/status/README.md'
readme='README.md'
fixture='docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md'
fixture_test='scripts/test-fedora-source-archive-fixture-lane.sh'
transcript_validator='docs/FEDORA_SOURCE_ARCHIVE_TRANSCRIPT_REVIEW_VALIDATOR.md'
transcript_validator_script='scripts/fedora-source-archive-transcript-review.sh'
transcript_validator_test='scripts/test-fedora-source-archive-transcript-review-validator.sh'
acceptance_gate='docs/FEDORA_SOURCE_ARCHIVE_ACCEPTANCE_GATE.md'
acceptance_gate_script='scripts/fedora-source-archive-acceptance-gate.sh'
acceptance_gate_test='scripts/test-fedora-source-archive-acceptance-gate.sh'
accepted_status_template='docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_TEMPLATE.md'
accepted_status_template_script='scripts/fedora-source-archive-accepted-evidence-status-template.sh'
accepted_status_template_test='scripts/test-fedora-source-archive-accepted-evidence-status-template.sh'
accepted_status_review_validator='docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_REVIEW_VALIDATOR.md'
accepted_status_review_validator_script='scripts/fedora-source-archive-accepted-evidence-status-review.sh'
accepted_status_review_validator_test='scripts/test-fedora-source-archive-accepted-evidence-status-review-validator.sh'
accepted_evidence_acceptance_gate='docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_ACCEPTANCE_GATE.md'
accepted_evidence_acceptance_gate_script='scripts/fedora-source-archive-accepted-evidence-acceptance-gate.sh'
accepted_evidence_acceptance_gate_test='scripts/test-fedora-source-archive-accepted-evidence-acceptance-gate.sh'
rpmlint_classification='docs/FEDORA_RPMLINT_FINDINGS_CLASSIFICATION.md'
rpmlint_status='docs/status/FEDORA_RPMLINT_FINDINGS_CLASSIFICATION_STATUS.md'
matrix='docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md'
matrix_status='docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md'
matrix_script='scripts/fedora-production-readiness-evidence-matrix.sh'
matrix_test='scripts/test-fedora-production-readiness-evidence-matrix.sh'
spec='packaging/fedora/latticra.spec'
workflow='.github/workflows/fedora-source-archive-reproducibility-contract.yml'

for file in \
  "$doc" \
  "$status" \
  "$index" \
  "$readme" \
  "$fixture" \
  "$fixture_test" \
  "$transcript_validator" \
  "$transcript_validator_script" \
  "$transcript_validator_test" \
  "$acceptance_gate" \
  "$acceptance_gate_script" \
  "$acceptance_gate_test" \
  "$accepted_status_template" \
  "$accepted_status_template_script" \
  "$accepted_status_template_test" \
  "$accepted_status_review_validator" \
  "$accepted_status_review_validator_script" \
  "$accepted_status_review_validator_test" \
  "$accepted_evidence_acceptance_gate" \
  "$accepted_evidence_acceptance_gate_script" \
  "$accepted_evidence_acceptance_gate_test" \
  "$rpmlint_classification" \
  "$rpmlint_status" \
  "$matrix" \
  "$matrix_status" \
  "$matrix_script" \
  "$matrix_test" \
  "$spec" \
  "$workflow"
do
  require_file "$file"
done

sh -n scripts/test-fedora-source-archive-reproducibility-contract.sh

require_contains 'Status: active source archive reproducibility contract' "$doc"
require_contains 'Source0:        %{name}-%{version}.tar.gz' "$doc"
require_contains '%autosetup -n %{name}-%{version}' "$doc"
require_contains 'source_archive_name=latticra-0.0.0.tar.gz' "$doc"
require_contains 'source_archive_root=latticra-0.0.0/' "$doc"
require_contains 'source_archive_generated_twice' "$doc"
require_contains 'source_archive_repeated_sha256_match' "$doc"
require_contains 'source_archive_excludes_git_dir' "$doc"
require_contains 'source_archive_excludes_nested_archives' "$doc"
require_contains 'source_archive_symlink_policy_checked' "$doc"
require_contains 'fedora_source_archive_reproducibility_contract_present=1' "$doc"
require_contains 'source_archive_transcript_present=0' "$doc"
require_contains 'source_archive_created_by_contract=0' "$doc"
require_contains 'source_archive_reproducible=0' "$doc"
require_contains 'source_archive_accepted_for_build=0' "$doc"
require_contains 'fedora_source_archive_transcript_review_validator_present=1' "$doc"
require_contains 'fedora_source_archive_acceptance_gate_present=1' "$doc"
require_contains 'fedora_source_archive_accepted_evidence_status_template_present=1' "$doc"
require_contains 'fedora_source_archive_accepted_evidence_status_review_validator_present=1' "$doc"
require_contains 'fedora_source_archive_accepted_evidence_acceptance_gate_present=1' "$doc"
require_contains 'source_archive_accepted_by_transcript_validator=0' "$doc"
require_contains 'source_archive_accepted_by_acceptance_gate=0' "$doc"
require_contains 'source_archive_accepted_evidence_status_written=0' "$doc"
require_contains 'source_archive_accepted_by_accepted_evidence_acceptance_gate=0' "$doc"
require_contains 'rpmbuild_run=0' "$doc"
require_contains 'mock_build_run=0' "$doc"
require_contains 'rpm_artifact_created=0' "$doc"
require_contains 'fedora_package_review_ready=0' "$doc"
require_contains 'fedora_distribution_ready=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'Add a Fedora RPM install/remove transcript contract' "$doc"
require_contains 'fedora_source_archive_reproducibility_contract: ok' "$doc"

for current_field in \
  'fedora_source_archive_reproducibility_contract_present=1' \
  'fedora_source_archive_transcript_review_validator_present=1' \
  'fedora_source_archive_acceptance_gate_present=1' \
  'fedora_source_archive_accepted_evidence_status_template_present=1' \
  'fedora_source_archive_accepted_evidence_status_review_validator_present=1' \
  'fedora_source_archive_accepted_evidence_acceptance_gate_present=1' \
  'fedora_rpmlint_findings_classification_present=1' \
  'fedora_source_archive_fixture_lane_present=1' \
  'source_archive_policy_recorded=1' \
  'source_archive_name_expected=latticra-0.0.0.tar.gz' \
  'source_archive_root_expected=latticra-0.0.0/' \
  'source_archive_matches_source0_required=1' \
  'source_archive_matches_autosetup_required=1' \
  'source_archive_transcript_present=0' \
  'source_archive_transcript_candidate_valid=0' \
  'source_archive_transcript_reviewed=0' \
  'source_archive_accepted_by_transcript_validator=0' \
  'source_archive_written_by_transcript_validator=0' \
  'source_archive_accepted_for_build_by_transcript_validator_alone=0' \
  'source_archive_acceptance_gate_mode=no-effect-gate' \
  'source_archive_transcript_review_report_valid=0' \
  'source_archive_acceptance_requested=0' \
  'source_archive_accepted_by_acceptance_gate=0' \
  'source_archive_written_by_acceptance_gate=0' \
  'source_archive_accepted_for_build_by_acceptance_gate_alone=0' \
  'source_archive_accepted_evidence_status_template_mode=no-effect-template' \
  'source_archive_accepted_evidence_status_template_complete=0' \
  'source_archive_accepted_evidence_status_review_mode=no-effect-validation' \
  'source_archive_accepted_evidence_status_candidate_valid=0' \
  'source_archive_accepted_evidence_status_reviewed=0' \
  'source_archive_accepted_evidence_status_accepted_by_validator=0' \
  'source_archive_accepted_evidence_status_written_by_validator=0' \
  'source_archive_accepted_for_build_by_status_validator_alone=0' \
  'fedora_mock_build_input_opened_by_status_validator_alone=0' \
  'source_archive_accepted_evidence_acceptance_gate_mode=no-effect-gate' \
  'source_archive_accepted_evidence_status_review_report_valid=0' \
  'source_archive_accepted_evidence_acceptance_requested=0' \
  'source_archive_accepted_by_accepted_evidence_acceptance_gate=0' \
  'source_archive_accepted_evidence_status_written_by_acceptance_gate=0' \
  'source_archive_accepted_for_build_by_acceptance_gate_alone=0' \
  'fedora_mock_build_input_opened_by_acceptance_gate_alone=0' \
  'source_archive_accepted_evidence_status_written=0' \
  'source_archive_accepted_evidence_present=0' \
  'source_archive_accepted=0' \
  'source_archive_created_by_contract=0' \
  'source_archive_sha256_recorded=0' \
  'source_archive_reproducible=0' \
  'source_archive_accepted_for_build=0' \
  'fedora_mock_build_input_opened=0' \
  'rpmbuild_run=0' \
  'mock_build_run=0' \
  'rpm_artifact_created=0' \
  'fedora_package_review_ready=0' \
  'fedora_distribution_ready=0' \
  'production_installer_ready=0' \
  'host_mutation_performed=0'
do
  require_contains "$current_field" "$status"
  require_contains "$current_field" "$index"
  require_contains "$current_field" "$readme"
  require_contains "$current_field" "$matrix"
done

require_contains 'docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md' "$fixture"
require_contains 'fedora_source_archive_transcript_review_validator_present=1' "$transcript_validator"
require_contains 'source_archive_accepted_for_build_by_transcript_validator_alone=0' "$transcript_validator_script"
require_contains 'fedora_source_archive_transcript_review_validator: ok' "$transcript_validator_test"
require_contains 'fedora_source_archive_acceptance_gate_present=1' "$acceptance_gate"
require_contains 'source_archive_accepted_for_build_by_acceptance_gate_alone=0' "$acceptance_gate_script"
require_contains 'fedora_source_archive_acceptance_gate: ok' "$acceptance_gate_test"
require_contains 'fedora_source_archive_accepted_evidence_status_template_present=1' "$accepted_status_template"
require_contains 'source_archive_accepted_evidence_status_template_complete=0' "$accepted_status_template_script"
require_contains 'fedora_source_archive_accepted_evidence_status_template: ok' "$accepted_status_template_test"
require_contains 'fedora_source_archive_accepted_evidence_status_review_validator_present=1' "$accepted_status_review_validator"
require_contains 'source_archive_accepted_evidence_status_candidate_valid=1' "$accepted_status_review_validator_script"
require_contains 'fedora_source_archive_accepted_evidence_status_review_validator: ok' "$accepted_status_review_validator_test"
require_contains 'fedora_source_archive_accepted_evidence_acceptance_gate_present=1' "$accepted_evidence_acceptance_gate"
require_contains 'fedora_source_archive_accepted_evidence_acceptance_gate_present=1' "$accepted_evidence_acceptance_gate_script"
require_contains 'fedora_source_archive_accepted_evidence_acceptance_gate: ok' "$accepted_evidence_acceptance_gate_test"
require_contains 'docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md' "$rpmlint_classification"
require_contains 'fedora_source_archive_reproducibility_contract_present=1' "$rpmlint_status"
require_contains 'fedora_source_archive_reproducibility_contract_present=1' "$matrix_script"
require_contains 'fedora_source_archive_reproducibility_contract_present=1' "$matrix_status"
require_contains 'fedora_source_archive_reproducibility_contract_present=1' "$matrix_test"
require_contains 'docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md' "$readme"
require_contains 'docs/status/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT_STATUS.md' "$readme"
require_contains 'Current Fedora source archive reproducibility contract checkpoint' "$index"
require_contains 'The Fedora source archive reproducibility contract is present but does not accept source archive evidence' "$index"

require_contains 'Source0:        %{name}-%{version}.tar.gz' "$spec"
require_contains '%autosetup -n %{name}-%{version}' "$spec"

require_contains 'name: Fedora Source Archive Reproducibility Contract' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-source-archive-reproducibility-contract.sh' "$workflow"
require_absent 'sh scripts/test-fedora-source-archive-fixture-lane.sh' "$workflow"

require_contains 'sh ./scripts/test-fedora-source-archive-reproducibility-contract.sh' 'Makefile'
require_contains 'fedora-source-archive-reproducibility-contract:' 'Makefile'

printf 'fedora_source_archive_reproducibility_contract: ok\n'
