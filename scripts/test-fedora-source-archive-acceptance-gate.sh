#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora source archive acceptance gate: %s\n' "$1" >&2
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

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    fail "missing required output pattern: $pattern"
  fi
}

doc='docs/FEDORA_SOURCE_ARCHIVE_ACCEPTANCE_GATE.md'
status='docs/status/FEDORA_SOURCE_ARCHIVE_ACCEPTANCE_GATE_STATUS.md'
index='docs/status/README.md'
readme='README.md'
script='scripts/fedora-source-archive-acceptance-gate.sh'
test_script='scripts/test-fedora-source-archive-acceptance-gate.sh'
contract='docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md'
contract_status='docs/status/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT_STATUS.md'
transcript_validator='docs/FEDORA_SOURCE_ARCHIVE_TRANSCRIPT_REVIEW_VALIDATOR.md'
transcript_validator_status='docs/status/FEDORA_SOURCE_ARCHIVE_TRANSCRIPT_REVIEW_VALIDATOR_STATUS.md'
transcript_validator_script='scripts/fedora-source-archive-transcript-review.sh'
accepted_status_template='docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_TEMPLATE.md'
accepted_status_template_status='docs/status/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_TEMPLATE_STATUS.md'
accepted_status_template_script='scripts/fedora-source-archive-accepted-evidence-status-template.sh'
accepted_status_template_test='scripts/test-fedora-source-archive-accepted-evidence-status-template.sh'
accepted_status_review_validator='docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_REVIEW_VALIDATOR.md'
accepted_status_review_validator_status='docs/status/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_REVIEW_VALIDATOR_STATUS.md'
accepted_status_review_validator_script='scripts/fedora-source-archive-accepted-evidence-status-review.sh'
accepted_status_review_validator_test='scripts/test-fedora-source-archive-accepted-evidence-status-review-validator.sh'
accepted_evidence_acceptance_gate='docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_ACCEPTANCE_GATE.md'
accepted_evidence_acceptance_gate_status='docs/status/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_ACCEPTANCE_GATE_STATUS.md'
accepted_evidence_acceptance_gate_script='scripts/fedora-source-archive-accepted-evidence-acceptance-gate.sh'
accepted_evidence_acceptance_gate_test='scripts/test-fedora-source-archive-accepted-evidence-acceptance-gate.sh'
matrix='docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md'
matrix_status='docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md'
matrix_script='scripts/fedora-production-readiness-evidence-matrix.sh'
matrix_test='scripts/test-fedora-production-readiness-evidence-matrix.sh'
spec='packaging/fedora/latticra.spec'
workflow='.github/workflows/fedora-source-archive-acceptance-gate.yml'

for file in \
  "$doc" \
  "$status" \
  "$index" \
  "$readme" \
  "$script" \
  "$test_script" \
  "$contract" \
  "$contract_status" \
  "$transcript_validator" \
  "$transcript_validator_status" \
  "$transcript_validator_script" \
  "$accepted_status_template" \
  "$accepted_status_template_status" \
  "$accepted_status_template_script" \
  "$accepted_status_template_test" \
  "$accepted_status_review_validator" \
  "$accepted_status_review_validator_status" \
  "$accepted_status_review_validator_script" \
  "$accepted_status_review_validator_test" \
  "$accepted_evidence_acceptance_gate" \
  "$accepted_evidence_acceptance_gate_status" \
  "$accepted_evidence_acceptance_gate_script" \
  "$accepted_evidence_acceptance_gate_test" \
  "$matrix" \
  "$matrix_status" \
  "$matrix_script" \
  "$matrix_test" \
  "$spec" \
  "$workflow"
do
  require_file "$file"
done

sh -n "$script"
sh -n "$test_script"

require_contains 'Status: no-effect source archive acceptance gate' "$doc"
require_contains 'fedora_source_archive_acceptance_gate_present=1' "$doc"
require_contains 'source_archive_acceptance_gate_mode=no-effect-gate' "$doc"
require_contains 'source_archive_transcript_review_report_valid=0' "$doc"
require_contains 'source_archive_acceptance_requested=0' "$doc"
require_contains 'source_archive_accepted_by_acceptance_gate=0' "$doc"
require_contains 'source_archive_written_by_acceptance_gate=0' "$doc"
require_contains 'source_archive_accepted_for_build_by_acceptance_gate_alone=0' "$doc"
require_contains 'fedora_source_archive_accepted_evidence_status_template_present=1' "$doc"
require_contains 'fedora_source_archive_accepted_evidence_status_review_validator_present=1' "$doc"
require_contains 'source_archive_accepted_evidence_status_written=0' "$doc"
require_contains 'source_archive_accepted_for_build=0' "$doc"
require_contains 'fedora_mock_build_input_opened=0' "$doc"
require_contains 'sh scripts/fedora-source-archive-acceptance-gate.sh --transcript-review <path>' "$doc"
require_contains 'sh scripts/test-fedora-source-archive-acceptance-gate.sh' "$doc"

require_contains 'FEDORA SOURCE ARCHIVE ACCEPTANCE GATE' "$script"
require_contains 'source_archive_acceptance_gate_status=blocked' "$script"
require_contains 'source_archive_transcript_review_report_valid=1' "$script"
require_contains 'source_archive_accepted_by_acceptance_gate=0' "$script"
require_contains 'source_archive_written_by_acceptance_gate=0' "$script"
require_contains 'source_archive_accepted_for_build_by_acceptance_gate_alone=0' "$script"
require_contains 'source_archive_accepted_for_build=0' "$script"
require_contains 'fedora_mock_build_input_opened=0' "$script"
require_contains 'placeholder value is not acceptable' "$script"
require_absent 'sudo ' "$script"
require_absent 'rpmbuild ' "$script"
require_absent 'rpm -Uvh' "$script"
require_absent 'rpm -e' "$script"
require_absent 'dnf ' "$script"
require_absent 'curl ' "$script"
require_absent 'wget ' "$script"

for current_field in \
  'fedora_source_archive_acceptance_gate_present=1' \
  'source_archive_acceptance_gate_mode=no-effect-gate' \
  'source_archive_transcript_review_report_valid=0' \
  'source_archive_acceptance_requested=0' \
  'source_archive_transcript_candidate_valid=0' \
  'source_archive_transcript_reviewed=0' \
  'candidate_source_archive_transcript_present=0' \
  'candidate_source_archive_reproducible=0' \
  'candidate_source_archive_repeated_sha256_match=0' \
  'candidate_source_archive_rpmlint_prerequisite_present=0' \
  'source_archive_accepted_by_acceptance_gate=0' \
  'source_archive_written_by_acceptance_gate=0' \
  'source_archive_accepted_for_build_by_acceptance_gate_alone=0' \
  'fedora_source_archive_accepted_evidence_status_template_present=1' \
  'fedora_source_archive_accepted_evidence_status_review_validator_present=1' \
  'fedora_source_archive_accepted_evidence_acceptance_gate_present=1' \
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
  require_contains "$current_field" "$doc"
  require_contains "$current_field" "$status"
  require_contains "$current_field" "$index"
  require_contains "$current_field" "$readme"
  require_contains "$current_field" "$matrix"
done

for review_field in \
  'FEDORA SOURCE ARCHIVE TRANSCRIPT REVIEW VALIDATION' \
  'source_archive_transcript_review_status=ok' \
  'source_archive_transcript_candidate_valid=1' \
  'source_archive_transcript_required_markers_present=1' \
  'source_archive_transcript_placeholder_values_absent=1' \
  'source_archive_transcript_value_fields_validated=1' \
  'candidate_source_archive_transcript_present=1' \
  'candidate_source_archive_reproducible=1' \
  'candidate_source_archive_repeated_sha256_match=1' \
  'candidate_source_archive_rpmlint_prerequisite_present=1' \
  'source_archive_transcript_reviewed=1' \
  'source_archive_accepted_by_transcript_validator=0' \
  'source_archive_written_by_transcript_validator=0' \
  'source_archive_accepted_for_build_by_transcript_validator_alone=0' \
  'source_archive_accepted_for_build=0' \
  'rpmbuild_run=0' \
  'mock_build_run=0' \
  'rpm_artifact_created=0' \
  'fedora_package_review_ready=0' \
  'fedora_distribution_ready=0' \
  'production_installer_ready=0' \
  'host_mutation_performed=0'
do
  require_contains "$review_field" "$doc"
  require_contains "$review_field" "$script"
done

require_contains 'fedora_source_archive_reproducibility_contract_present=1' "$contract"
require_contains 'source_archive_transcript_present=0' "$contract_status"
require_contains 'fedora_source_archive_transcript_review_validator_present=1' "$transcript_validator"
require_contains 'source_archive_accepted_for_build_by_transcript_validator_alone=0' "$transcript_validator_status"
require_contains 'source_archive_accepted_for_build_by_transcript_validator_alone=0' "$transcript_validator_script"
require_contains 'fedora_source_archive_accepted_evidence_status_template_present=1' "$accepted_status_template"
require_contains 'source_archive_accepted_evidence_status_template_complete=0' "$accepted_status_template_status"
require_contains 'source_archive_accepted_evidence_status_template_complete=0' "$accepted_status_template_script"
require_contains 'fedora_source_archive_accepted_evidence_status_template: ok' "$accepted_status_template_test"
require_contains 'fedora_source_archive_accepted_evidence_status_review_validator_present=1' "$accepted_status_review_validator"
require_contains 'source_archive_accepted_evidence_status_candidate_valid=0' "$accepted_status_review_validator_status"
require_contains 'source_archive_accepted_evidence_status_candidate_valid=1' "$accepted_status_review_validator_script"
require_contains 'fedora_source_archive_accepted_evidence_status_review_validator: ok' "$accepted_status_review_validator_test"
require_contains 'fedora_source_archive_accepted_evidence_acceptance_gate_present=1' "$accepted_evidence_acceptance_gate"
require_contains 'fedora_source_archive_accepted_evidence_acceptance_gate_present=1' "$accepted_evidence_acceptance_gate_status"
require_contains 'fedora_source_archive_accepted_evidence_acceptance_gate_present=1' "$accepted_evidence_acceptance_gate_script"
require_contains 'fedora_source_archive_accepted_evidence_acceptance_gate: ok' "$accepted_evidence_acceptance_gate_test"
require_contains 'fedora_source_archive_acceptance_gate_present=1' "$matrix_script"
require_contains 'fedora_source_archive_acceptance_gate_present=1' "$matrix_status"
require_contains 'fedora_source_archive_acceptance_gate_present=1' "$matrix_test"
require_contains 'Source0:        %{name}-%{version}.tar.gz' "$spec"

require_contains 'FEDORA_SOURCE_ARCHIVE_ACCEPTANCE_GATE_STATUS.md' "$index"
require_contains 'Current Fedora source archive acceptance gate checkpoint' "$index"
require_contains 'The Fedora source archive acceptance gate is present but does not accept source archive evidence' "$index"
require_contains 'docs/FEDORA_SOURCE_ARCHIVE_ACCEPTANCE_GATE.md' "$readme"
require_contains 'docs/status/FEDORA_SOURCE_ARCHIVE_ACCEPTANCE_GATE_STATUS.md' "$readme"
require_contains 'The Fedora source archive acceptance gate is present' "$readme"

require_contains 'name: Fedora Source Archive Acceptance Gate' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-source-archive-acceptance-gate.sh' "$workflow"
require_absent 'sh scripts/fedora-source-archive-acceptance-gate.sh --transcript-review' "$workflow"

require_contains 'sh ./scripts/test-fedora-source-archive-acceptance-gate.sh' 'Makefile'
require_contains 'fedora-source-archive-acceptance-gate:' 'Makefile'

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-fedora-source-archive-acceptance-gate.XXXXXX")"
trap 'rm -rf "$tmp"' EXIT INT HUP TERM

valid="$tmp/valid.transcript-review"
placeholder="$tmp/placeholder.transcript-review"

cat >"$valid" <<'VALID_TRANSCRIPT_REVIEW'
FEDORA SOURCE ARCHIVE TRANSCRIPT REVIEW VALIDATION
source_archive_transcript_review_status=ok
fedora_source_archive_transcript_review_validator_present=1
source_archive_transcript_review_mode=no-effect-validation
source_archive_transcript_candidate_valid=1
source_archive_transcript_required_markers_present=1
source_archive_transcript_placeholder_values_absent=1
source_archive_transcript_value_fields_validated=1
candidate_source_archive_transcript_present=1
candidate_source_archive_reproducible=1
candidate_source_archive_repeated_sha256_match=1
candidate_source_archive_rpmlint_prerequisite_present=1
source_archive_transcript_reviewed=1
source_archive_accepted_by_transcript_validator=0
source_archive_written_by_transcript_validator=0
source_archive_accepted_for_build_by_transcript_validator_alone=0
source_archive_accepted_for_build=0
rpmbuild_run=0
mock_build_run=0
rpm_artifact_created=0
fedora_package_review_ready=0
fedora_distribution_ready=0
production_installer_ready=0
host_mutation_performed=0
VALID_TRANSCRIPT_REVIEW

cat >"$placeholder" <<'PLACEHOLDER_TRANSCRIPT_REVIEW'
FEDORA SOURCE ARCHIVE TRANSCRIPT REVIEW VALIDATION
source_archive_transcript_review_status=ok
fedora_source_archive_transcript_review_validator_present=1
source_archive_transcript_review_mode=no-effect-validation
source_archive_transcript_candidate_valid=1
source_archive_transcript_required_markers_present=1
source_archive_transcript_placeholder_values_absent=1
source_archive_transcript_value_fields_validated=1
candidate_source_archive_transcript_present=1
candidate_source_archive_reproducible=1
candidate_source_archive_repeated_sha256_match=1
candidate_source_archive_rpmlint_prerequisite_present=1
source_archive_transcript_reviewed=1
source_archive_accepted_by_transcript_validator=0
source_archive_written_by_transcript_validator=0
source_archive_accepted_for_build_by_transcript_validator_alone=0
source_archive_accepted_for_build=0
rpmbuild_run=0
mock_build_run=0
rpm_artifact_created=0
fedora_package_review_ready=0
fedora_distribution_ready=0
production_installer_ready=0
host_mutation_performed=0
operator_acceptance_reference=<required-after-source-archive-operator-review>
PLACEHOLDER_TRANSCRIPT_REVIEW

output=$(sh "$script" --transcript-review "$valid")
require_output_contains "$output" 'FEDORA SOURCE ARCHIVE ACCEPTANCE GATE'
require_output_contains "$output" 'source_archive_acceptance_gate_status=blocked'
require_output_contains "$output" 'source_archive_transcript_review_report_valid=1'
require_output_contains "$output" 'source_archive_transcript_candidate_valid=1'
require_output_contains "$output" 'source_archive_transcript_reviewed=1'
require_output_contains "$output" 'candidate_source_archive_reproducible=1'
require_output_contains "$output" 'source_archive_acceptance_requested=0'
require_output_contains "$output" 'source_archive_accepted_by_acceptance_gate=0'
require_output_contains "$output" 'source_archive_written_by_acceptance_gate=0'
require_output_contains "$output" 'source_archive_accepted_for_build_by_acceptance_gate_alone=0'
require_output_contains "$output" 'source_archive_accepted_for_build=0'
require_output_contains "$output" 'fedora_mock_build_input_opened=0'
require_output_contains "$output" 'host_mutation_performed=0'

if sh "$script" --transcript-review "$placeholder" >/dev/null 2>&1; then
  fail 'placeholder transcript review report unexpectedly passed source archive acceptance gate'
fi

printf 'fedora_source_archive_acceptance_gate: ok\n'
