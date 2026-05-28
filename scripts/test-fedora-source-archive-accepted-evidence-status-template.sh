#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora source archive accepted evidence status template: %s\n' "$1" >&2
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

doc='docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_TEMPLATE.md'
status='docs/status/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_TEMPLATE_STATUS.md'
index='docs/status/README.md'
readme='README.md'
script='scripts/fedora-source-archive-accepted-evidence-status-template.sh'
test_script='scripts/test-fedora-source-archive-accepted-evidence-status-template.sh'
contract='docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md'
transcript_validator='docs/FEDORA_SOURCE_ARCHIVE_TRANSCRIPT_REVIEW_VALIDATOR.md'
acceptance_gate='docs/FEDORA_SOURCE_ARCHIVE_ACCEPTANCE_GATE.md'
acceptance_gate_status='docs/status/FEDORA_SOURCE_ARCHIVE_ACCEPTANCE_GATE_STATUS.md'
acceptance_gate_script='scripts/fedora-source-archive-acceptance-gate.sh'
transcript_validator_script='scripts/fedora-source-archive-transcript-review.sh'
review_validator='docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_REVIEW_VALIDATOR.md'
review_validator_status='docs/status/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_REVIEW_VALIDATOR_STATUS.md'
review_validator_script='scripts/fedora-source-archive-accepted-evidence-status-review.sh'
review_validator_test='scripts/test-fedora-source-archive-accepted-evidence-status-review-validator.sh'
accepted_evidence_acceptance_gate='docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_ACCEPTANCE_GATE.md'
accepted_evidence_acceptance_gate_status='docs/status/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_ACCEPTANCE_GATE_STATUS.md'
accepted_evidence_acceptance_gate_script='scripts/fedora-source-archive-accepted-evidence-acceptance-gate.sh'
accepted_evidence_acceptance_gate_test='scripts/test-fedora-source-archive-accepted-evidence-acceptance-gate.sh'
matrix='docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md'
matrix_status='docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md'
matrix_script='scripts/fedora-production-readiness-evidence-matrix.sh'
matrix_test='scripts/test-fedora-production-readiness-evidence-matrix.sh'
spec='packaging/fedora/latticra.spec'
workflow='.github/workflows/fedora-source-archive-accepted-evidence-status-template.yml'

for file in \
  "$doc" \
  "$status" \
  "$index" \
  "$readme" \
  "$script" \
  "$test_script" \
  "$contract" \
  "$transcript_validator" \
  "$acceptance_gate" \
  "$acceptance_gate_status" \
  "$acceptance_gate_script" \
  "$transcript_validator_script" \
  "$review_validator" \
  "$review_validator_status" \
  "$review_validator_script" \
  "$review_validator_test" \
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

require_contains 'Status: no-effect source archive accepted evidence status template' "$doc"
require_contains 'future accepted source archive evidence status shape' "$doc"
require_contains 'It does not validate a live source archive transcript.' "$doc"
require_contains 'It does not write source archive evidence status.' "$doc"
require_contains 'It does not accept source archive evidence.' "$doc"
require_contains 'It does not open source archive evidence as mock build input.' "$doc"
require_contains 'sh scripts/fedora-source-archive-accepted-evidence-status-template.sh' "$doc"
require_contains 'sh scripts/test-fedora-source-archive-accepted-evidence-status-template.sh' "$doc"

for current_field in \
  'fedora_source_archive_acceptance_gate_present=1' \
  'fedora_source_archive_accepted_evidence_status_template_present=1' \
  'fedora_source_archive_accepted_evidence_status_review_validator_present=1' \
  'fedora_source_archive_accepted_evidence_acceptance_gate_present=1' \
  'source_archive_accepted_evidence_status_template_mode=no-effect-template' \
  'source_archive_accepted_evidence_status_template_decision=blocked-template-only-no-status-write' \
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
  'source_archive_transcript_attached=0' \
  'source_archive_transcript_review_report_attached=0' \
  'source_archive_acceptance_gate_report_attached=0' \
  'source_archive_acceptance_gate_reviewed=0' \
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

for future_field in \
  'FEDORA SOURCE ARCHIVE ACCEPTED EVIDENCE STATUS' \
  'Status: source archive evidence status alignment' \
  'Date: <required-from-operator-review-date>' \
  'source=operator Fedora source archive reproducibility transcript and acceptance gate report' \
  'source_archive_transcript_path=<required-from-operator-attachment>' \
  'source_archive_transcript_review_report_path=<required-from-operator-attachment>' \
  'source_archive_acceptance_gate_report_path=<required-from-operator-attachment>' \
  'source_tree_revision=<required-from-reviewed-source-archive-transcript>' \
  'source_archive_command=<required-from-reviewed-source-archive-transcript>' \
  'source_archive_name=latticra-0.0.0.tar.gz' \
  'source_archive_root=latticra-0.0.0/' \
  'source_archive_size_bytes=<required-from-reviewed-source-archive-transcript>' \
  'source_archive_sha256=<required-from-reviewed-source-archive-transcript>' \
  'source_archive_entry_count=<required-from-reviewed-source-archive-transcript>' \
  'source_archive_transcript_present=1' \
  'source_archive_transcript_candidate_valid=1' \
  'source_archive_transcript_reviewed=1' \
  'source_archive_transcript_review_report_valid=1' \
  'source_archive_acceptance_gate_reviewed=1' \
  'source_archive_name_matches_source0=1' \
  'source_archive_root_matches_autosetup=1' \
  'source_archive_reproducible=1' \
  'source_archive_repeated_sha256_match=1' \
  'source_archive_path_safety_checked=1' \
  'source_archive_symlink_policy_checked=1' \
  'fedora_rpmlint_findings_classification_present=1' \
  'accepted_rpmlint_transcript_present=1' \
  'source_archive_accepted_evidence_status_written=1' \
  'source_archive_accepted_evidence_present=1' \
  'source_archive_accepted=1' \
  'source_archive_accepted_for_build=1' \
  'fedora_mock_build_input_opened=1' \
  'rpmbuild_run=0' \
  'mock_build_run=0' \
  'rpm_artifact_created=0' \
  'fedora_package_review_ready=0' \
  'fedora_distribution_ready=0' \
  'production_installer_ready=0' \
  'host_mutation_performed=0'
do
  require_contains "$future_field" "$doc"
done

require_contains 'Status: source-archive-accepted-evidence-status-template/status alignment' "$status"
require_contains 'Date: 2026-05-27' "$status"
require_contains 'does not attach, write, or accept source archive evidence' "$status"
require_contains 'does not open source archive evidence as mock build input' "$status"
require_contains 'Add a Fedora RPM build-evidence intake denial disposition closeout archive gate review disposition closeout archive gate review contract' "$status"

require_contains 'FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_TEMPLATE_STATUS.md' "$index"
require_contains 'Current Fedora source archive accepted evidence status template checkpoint' "$index"
require_contains 'The Fedora source archive accepted evidence status template is present but does not write, accept, or open source archive evidence' "$index"

require_contains 'docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_TEMPLATE.md' "$readme"
require_contains 'docs/status/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_TEMPLATE_STATUS.md' "$readme"
require_contains 'The Fedora source archive accepted evidence status template is present' "$readme"
require_contains 'The Fedora source archive accepted evidence status review validator is present' "$readme"

require_contains 'fedora_source_archive_reproducibility_contract_present=1' "$contract"
require_contains 'fedora_source_archive_transcript_review_validator_present=1' "$transcript_validator"
require_contains 'fedora_source_archive_acceptance_gate_present=1' "$acceptance_gate"
require_contains 'fedora_source_archive_accepted_evidence_status_review_validator_present=1' "$review_validator"
require_contains 'source_archive_accepted_evidence_status_candidate_valid=0' "$review_validator_status"
require_contains 'source_archive_accepted_evidence_status_candidate_valid=1' "$review_validator_script"
require_contains 'fedora_source_archive_accepted_evidence_status_review_validator: ok' "$review_validator_test"
require_contains 'fedora_source_archive_accepted_evidence_acceptance_gate_present=1' "$accepted_evidence_acceptance_gate"
require_contains 'fedora_source_archive_accepted_evidence_acceptance_gate_present=1' "$accepted_evidence_acceptance_gate_status"
require_contains 'fedora_source_archive_accepted_evidence_acceptance_gate_present=1' "$accepted_evidence_acceptance_gate_script"
require_contains 'fedora_source_archive_accepted_evidence_acceptance_gate: ok' "$accepted_evidence_acceptance_gate_test"
require_contains 'source_archive_accepted_for_build_by_acceptance_gate_alone=0' "$acceptance_gate_status"
require_contains 'source_archive_accepted_for_build_by_acceptance_gate_alone=0' "$acceptance_gate_script"
require_contains 'source_archive_accepted_for_build_by_transcript_validator_alone=0' "$transcript_validator_script"
require_contains 'fedora_source_archive_accepted_evidence_status_template_present=1' "$matrix_script"
require_contains 'fedora_source_archive_accepted_evidence_status_template_present=1' "$matrix_status"
require_contains 'fedora_source_archive_accepted_evidence_status_template_present=1' "$matrix_test"
require_contains 'Source0:        %{name}-%{version}.tar.gz' "$spec"

require_contains 'FEDORA SOURCE ARCHIVE ACCEPTED EVIDENCE STATUS TEMPLATE' "$script"
require_contains 'template_status=ok' "$script"
require_contains 'source_archive_accepted_evidence_status_template_decision=blocked-template-only-no-status-write' "$script"
require_contains 'source_archive_accepted_evidence_status_written=0' "$script"
require_contains 'source_archive_accepted_evidence_present=0' "$script"
require_contains 'source_archive_accepted_for_build=0' "$script"
require_contains 'fedora_mock_build_input_opened=0' "$script"
require_absent 'sudo ' "$script"
require_absent 'rpmbuild ' "$script"
require_absent 'rpm -Uvh' "$script"
require_absent 'rpm -e' "$script"
require_absent 'dnf ' "$script"
require_absent 'curl ' "$script"
require_absent 'wget ' "$script"

require_contains 'name: Fedora Source Archive Accepted Evidence Status Template' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-source-archive-accepted-evidence-status-template.sh' "$workflow"
require_absent 'sh scripts/fedora-source-archive-accepted-evidence-status-template.sh' "$workflow"

require_contains 'sh ./scripts/test-fedora-source-archive-accepted-evidence-status-template.sh' 'Makefile'
require_contains 'fedora-source-archive-accepted-evidence-status-template:' 'Makefile'

output=$(sh "$script")
require_output_contains "$output" 'FEDORA SOURCE ARCHIVE ACCEPTED EVIDENCE STATUS TEMPLATE'
require_output_contains "$output" 'template_status=ok'
require_output_contains "$output" 'fedora_source_archive_accepted_evidence_status_template_present=1'
require_output_contains "$output" 'source_archive_accepted_evidence_status_template_mode=no-effect-template'
require_output_contains "$output" 'source_archive_accepted_evidence_status_template_decision=blocked-template-only-no-status-write'
require_output_contains "$output" 'source_archive_accepted_evidence_status_written=0'
require_output_contains "$output" 'source_archive_accepted_evidence_present=0'
require_output_contains "$output" 'source_archive_accepted_for_build=0'
require_output_contains "$output" 'fedora_mock_build_input_opened=0'
require_output_contains "$output" '[required_prior_review]'
require_output_contains "$output" 'source_archive_acceptance_gate_reviewed=1'
require_output_contains "$output" '[future_accepted_evidence_status_record]'
require_output_contains "$output" 'FEDORA SOURCE ARCHIVE ACCEPTED EVIDENCE STATUS'
require_output_contains "$output" 'source_archive_sha256=<required-from-reviewed-source-archive-transcript>'
require_output_contains "$output" 'source_archive_accepted_evidence_status_written=1'
require_output_contains "$output" 'source_archive_accepted_evidence_present=1'
require_output_contains "$output" 'source_archive_accepted_for_build=1'
require_output_contains "$output" 'fedora_mock_build_input_opened=1'
require_output_contains "$output" 'rpmbuild_run=0'
require_output_contains "$output" 'mock_build_run=0'

printf 'fedora_source_archive_accepted_evidence_status_template: ok\n'
