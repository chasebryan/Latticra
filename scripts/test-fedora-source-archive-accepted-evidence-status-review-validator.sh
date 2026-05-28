#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora source archive accepted evidence status review validator: %s\n' "$1" >&2
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

doc='docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_REVIEW_VALIDATOR.md'
status='docs/status/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_REVIEW_VALIDATOR_STATUS.md'
index='docs/status/README.md'
readme='README.md'
script='scripts/fedora-source-archive-accepted-evidence-status-review.sh'
test_script='scripts/test-fedora-source-archive-accepted-evidence-status-review-validator.sh'
template='docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_TEMPLATE.md'
template_status='docs/status/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_TEMPLATE_STATUS.md'
template_script='scripts/fedora-source-archive-accepted-evidence-status-template.sh'
acceptance_gate='docs/FEDORA_SOURCE_ARCHIVE_ACCEPTANCE_GATE.md'
contract='docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md'
acceptance_gate_script='scripts/fedora-source-archive-acceptance-gate.sh'
matrix='docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md'
matrix_status='docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md'
matrix_script='scripts/fedora-production-readiness-evidence-matrix.sh'
matrix_test='scripts/test-fedora-production-readiness-evidence-matrix.sh'
accepted_evidence_acceptance_gate='docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_ACCEPTANCE_GATE.md'
accepted_evidence_acceptance_gate_status='docs/status/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_ACCEPTANCE_GATE_STATUS.md'
accepted_evidence_acceptance_gate_script='scripts/fedora-source-archive-accepted-evidence-acceptance-gate.sh'
accepted_evidence_acceptance_gate_test='scripts/test-fedora-source-archive-accepted-evidence-acceptance-gate.sh'
spec='packaging/fedora/latticra.spec'
workflow='.github/workflows/fedora-source-archive-accepted-evidence-status-review-validator.yml'

for file in \
  "$doc" \
  "$status" \
  "$index" \
  "$readme" \
  "$script" \
  "$test_script" \
  "$template" \
  "$template_status" \
  "$template_script" \
  "$acceptance_gate" \
  "$contract" \
  "$acceptance_gate_script" \
  "$matrix" \
  "$matrix_status" \
  "$matrix_script" \
  "$matrix_test" \
  "$accepted_evidence_acceptance_gate" \
  "$accepted_evidence_acceptance_gate_status" \
  "$accepted_evidence_acceptance_gate_script" \
  "$accepted_evidence_acceptance_gate_test" \
  "$spec" \
  "$workflow"
do
  require_file "$file"
done

sh -n "$script"
sh -n "$test_script"

require_contains 'Status: no-effect source archive accepted evidence status review validator' "$doc"
require_contains 'fedora_source_archive_accepted_evidence_status_review_validator_present=1' "$doc"
require_contains 'source_archive_accepted_evidence_status_review_mode=no-effect-validation' "$doc"
require_contains 'source_archive_accepted_evidence_status_candidate_valid=0' "$doc"
require_contains 'source_archive_accepted_evidence_status_accepted_by_validator=0' "$doc"
require_contains 'source_archive_accepted_evidence_status_written_by_validator=0' "$doc"
require_contains 'source_archive_accepted_for_build_by_status_validator_alone=0' "$doc"
require_contains 'fedora_mock_build_input_opened_by_status_validator_alone=0' "$doc"
require_contains 'sh scripts/fedora-source-archive-accepted-evidence-status-review.sh --status <path>' "$doc"
require_contains 'sh scripts/test-fedora-source-archive-accepted-evidence-status-review-validator.sh' "$doc"

require_contains 'FEDORA SOURCE ARCHIVE ACCEPTED EVIDENCE STATUS REVIEW' "$script"
require_contains 'source_archive_accepted_evidence_status_candidate_valid=1' "$script"
require_contains 'source_archive_accepted_evidence_status_placeholder_values_absent=1' "$script"
require_contains 'source_archive_accepted_evidence_status_required_markers_present=1' "$script"
require_contains 'source_archive_accepted_evidence_status_value_fields_validated=1' "$script"
require_contains 'source_archive_accepted_evidence_status_accepted_by_validator=0' "$script"
require_contains 'source_archive_accepted_evidence_status_written_by_validator=0' "$script"
require_contains 'source_archive_accepted_for_build_by_status_validator_alone=0' "$script"
require_contains 'fedora_mock_build_input_opened_by_status_validator_alone=0' "$script"
require_contains 'placeholder value is not acceptable' "$script"
require_absent 'sudo ' "$script"
require_absent 'rpmbuild ' "$script"
require_absent 'rpm -Uvh' "$script"
require_absent 'rpm -e' "$script"
require_absent 'dnf ' "$script"
require_absent 'curl ' "$script"
require_absent 'wget ' "$script"

for current_field in \
  'fedora_source_archive_accepted_evidence_status_template_present=1' \
  'fedora_source_archive_accepted_evidence_status_review_validator_present=1' \
  'fedora_source_archive_accepted_evidence_acceptance_gate_present=1' \
  'source_archive_accepted_evidence_status_review_mode=no-effect-validation' \
  'source_archive_accepted_evidence_status_candidate_valid=0' \
  'source_archive_accepted_evidence_status_required_markers_present=0' \
  'source_archive_accepted_evidence_status_placeholder_values_absent=0' \
  'source_archive_accepted_evidence_status_value_fields_validated=0' \
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

for future_field in \
  'FEDORA SOURCE ARCHIVE ACCEPTED EVIDENCE STATUS' \
  'Status: source archive evidence status alignment' \
  'source=operator Fedora source archive reproducibility transcript and acceptance gate report' \
  'source_archive_name=latticra-0.0.0.tar.gz' \
  'source_archive_root=latticra-0.0.0/' \
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
  require_contains "$future_field" "$script"
done

require_contains 'Status: source-archive-accepted-evidence-status-review-validator/status alignment' "$status"
require_contains 'Date: 2026-05-27' "$status"
require_contains 'does not attach, write, or accept source archive evidence' "$status"
require_contains 'does not open source archive evidence as mock build input by itself' "$status"
require_contains 'Add a Fedora RPM install/remove transcript contract' "$status"

require_contains 'FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_REVIEW_VALIDATOR_STATUS.md' "$index"
require_contains 'Current Fedora source archive accepted evidence status review validator checkpoint' "$index"
require_contains 'The Fedora source archive accepted evidence status review validator is present but does not write, accept, or open source archive evidence' "$index"

require_contains 'docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_REVIEW_VALIDATOR.md' "$readme"
require_contains 'docs/status/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_REVIEW_VALIDATOR_STATUS.md' "$readme"
require_contains 'The Fedora source archive accepted evidence status review validator is present' "$readme"

require_contains 'FEDORA SOURCE ARCHIVE ACCEPTED EVIDENCE STATUS' "$template"
require_contains 'fedora_source_archive_accepted_evidence_status_template_present=1' "$template_status"
require_contains 'FEDORA SOURCE ARCHIVE ACCEPTED EVIDENCE STATUS TEMPLATE' "$template_script"
require_contains 'fedora_source_archive_acceptance_gate_present=1' "$acceptance_gate"
require_contains 'fedora_source_archive_reproducibility_contract_present=1' "$contract"
require_contains 'source_archive_accepted_for_build_by_acceptance_gate_alone=0' "$acceptance_gate_script"
require_contains 'fedora_source_archive_accepted_evidence_status_review_validator_present=1' "$matrix_script"
require_contains 'fedora_source_archive_accepted_evidence_status_review_validator_present=1' "$matrix_status"
require_contains 'fedora_source_archive_accepted_evidence_status_review_validator_present=1' "$matrix_test"
require_contains 'fedora_source_archive_accepted_evidence_acceptance_gate_present=1' "$accepted_evidence_acceptance_gate"
require_contains 'fedora_source_archive_accepted_evidence_acceptance_gate_present=1' "$accepted_evidence_acceptance_gate_status"
require_contains 'fedora_source_archive_accepted_evidence_acceptance_gate_present=1' "$accepted_evidence_acceptance_gate_script"
require_contains 'fedora_source_archive_accepted_evidence_acceptance_gate: ok' "$accepted_evidence_acceptance_gate_test"
require_contains 'Source0:        %{name}-%{version}.tar.gz' "$spec"

require_contains 'name: Fedora Source Archive Accepted Evidence Status Review Validator' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-source-archive-accepted-evidence-status-review-validator.sh' "$workflow"
require_absent 'sh scripts/fedora-source-archive-accepted-evidence-status-review.sh --status' "$workflow"

require_contains 'sh ./scripts/test-fedora-source-archive-accepted-evidence-status-review-validator.sh' 'Makefile'
require_contains 'fedora-source-archive-accepted-evidence-status-review-validator:' 'Makefile'

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-fedora-source-archive-accepted-status-review.XXXXXX")"
trap 'rm -rf "$tmp"' EXIT INT HUP TERM

valid="$tmp/valid.status"
placeholder="$tmp/placeholder.status"

cat >"$valid" <<'VALID_STATUS'
FEDORA SOURCE ARCHIVE ACCEPTED EVIDENCE STATUS
Status: source archive evidence status alignment
Date: 2026-05-27
source=operator Fedora source archive reproducibility transcript and acceptance gate report
source_archive_transcript_path=docs/status/evidence/fedora-source-archive-transcript-2026-05-27.txt
source_archive_transcript_review_report_path=docs/status/evidence/fedora-source-archive-transcript-review-2026-05-27.txt
source_archive_acceptance_gate_report_path=docs/status/evidence/fedora-source-archive-acceptance-gate-2026-05-27.txt
source_tree_revision=0123456789abcdef0123456789abcdef01234567
source_archive_command=git ls-files plus deterministic tar and gzip
source_archive_name=latticra-0.0.0.tar.gz
source_archive_root=latticra-0.0.0/
source_archive_size_bytes=123456
source_archive_sha256=0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef
source_archive_entry_count=100
source_archive_transcript_present=1
source_archive_transcript_candidate_valid=1
source_archive_transcript_reviewed=1
source_archive_transcript_review_report_valid=1
source_archive_acceptance_gate_reviewed=1
source_archive_name_matches_source0=1
source_archive_root_matches_autosetup=1
source_archive_reproducible=1
source_archive_repeated_sha256_match=1
source_archive_path_safety_checked=1
source_archive_symlink_policy_checked=1
fedora_rpmlint_findings_classification_present=1
accepted_rpmlint_transcript_present=1
source_archive_accepted_evidence_status_written=1
source_archive_accepted_evidence_present=1
source_archive_accepted=1
source_archive_accepted_for_build=1
fedora_mock_build_input_opened=1
rpmbuild_run=0
mock_build_run=0
rpm_artifact_created=0
fedora_package_review_ready=0
fedora_distribution_ready=0
production_installer_ready=0
host_mutation_performed=0
VALID_STATUS

cat >"$placeholder" <<'PLACEHOLDER_STATUS'
FEDORA SOURCE ARCHIVE ACCEPTED EVIDENCE STATUS
Status: source archive evidence status alignment
Date: <required-from-operator-review-date>
source=operator Fedora source archive reproducibility transcript and acceptance gate report
source_archive_transcript_path=<required-from-operator-attachment>
source_archive_transcript_review_report_path=docs/status/evidence/fedora-source-archive-transcript-review-2026-05-27.txt
source_archive_acceptance_gate_report_path=docs/status/evidence/fedora-source-archive-acceptance-gate-2026-05-27.txt
source_tree_revision=<required-from-reviewed-source-archive-transcript>
source_archive_command=git ls-files plus deterministic tar and gzip
source_archive_name=latticra-0.0.0.tar.gz
source_archive_root=latticra-0.0.0/
source_archive_size_bytes=123456
source_archive_sha256=0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef
source_archive_entry_count=100
source_archive_transcript_present=1
source_archive_transcript_candidate_valid=1
source_archive_transcript_reviewed=1
source_archive_transcript_review_report_valid=1
source_archive_acceptance_gate_reviewed=1
source_archive_name_matches_source0=1
source_archive_root_matches_autosetup=1
source_archive_reproducible=1
source_archive_repeated_sha256_match=1
source_archive_path_safety_checked=1
source_archive_symlink_policy_checked=1
fedora_rpmlint_findings_classification_present=1
accepted_rpmlint_transcript_present=1
source_archive_accepted_evidence_status_written=1
source_archive_accepted_evidence_present=1
source_archive_accepted=1
source_archive_accepted_for_build=1
fedora_mock_build_input_opened=1
rpmbuild_run=0
mock_build_run=0
rpm_artifact_created=0
fedora_package_review_ready=0
fedora_distribution_ready=0
production_installer_ready=0
host_mutation_performed=0
PLACEHOLDER_STATUS

output=$(sh "$script" --status "$valid")
require_output_contains "$output" 'FEDORA SOURCE ARCHIVE ACCEPTED EVIDENCE STATUS REVIEW'
require_output_contains "$output" 'review_status=ok'
require_output_contains "$output" 'source_archive_accepted_evidence_status_candidate_valid=1'
require_output_contains "$output" 'source_archive_accepted_evidence_status_placeholder_values_absent=1'
require_output_contains "$output" 'source_archive_accepted_evidence_status_required_markers_present=1'
require_output_contains "$output" 'source_archive_accepted_evidence_status_value_fields_validated=1'
require_output_contains "$output" 'candidate_source_archive_accepted_evidence_status_written=1'
require_output_contains "$output" 'candidate_source_archive_accepted_for_build=1'
require_output_contains "$output" 'candidate_fedora_mock_build_input_opened=1'
require_output_contains "$output" 'source_archive_accepted_evidence_status_accepted_by_validator=0'
require_output_contains "$output" 'source_archive_accepted_evidence_status_written_by_validator=0'
require_output_contains "$output" 'source_archive_accepted_for_build_by_status_validator_alone=0'
require_output_contains "$output" 'fedora_mock_build_input_opened_by_status_validator_alone=0'
require_output_contains "$output" 'host_mutation_performed=0'

if sh "$script" --status "$placeholder" >/dev/null 2>&1; then
  fail 'placeholder source archive accepted evidence status unexpectedly passed review'
fi

printf 'fedora_source_archive_accepted_evidence_status_review_validator: ok\n'
