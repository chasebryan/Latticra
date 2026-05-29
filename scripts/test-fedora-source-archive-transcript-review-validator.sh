#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora source archive transcript review validator: %s\n' "$1" >&2
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

doc='docs/FEDORA_SOURCE_ARCHIVE_TRANSCRIPT_REVIEW_VALIDATOR.md'
status='docs/status/FEDORA_SOURCE_ARCHIVE_TRANSCRIPT_REVIEW_VALIDATOR_STATUS.md'
index='docs/status/README.md'
readme='README.md'
script='scripts/fedora-source-archive-transcript-review.sh'
test_script='scripts/test-fedora-source-archive-transcript-review-validator.sh'
contract='docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md'
contract_status='docs/status/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT_STATUS.md'
fixture='docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md'
rpmlint_classification='docs/FEDORA_RPMLINT_FINDINGS_CLASSIFICATION.md'
matrix='docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md'
matrix_status='docs/status/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX_STATUS.md'
matrix_script='scripts/fedora-production-readiness-evidence-matrix.sh'
matrix_test='scripts/test-fedora-production-readiness-evidence-matrix.sh'
spec='packaging/fedora/latticra.spec'
workflow='.github/workflows/fedora-source-archive-transcript-review-validator.yml'

for file in \
  "$doc" \
  "$status" \
  "$index" \
  "$readme" \
  "$script" \
  "$test_script" \
  "$contract" \
  "$contract_status" \
  "$fixture" \
  "$rpmlint_classification" \
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

require_contains 'Status: no-effect source archive transcript review validator' "$doc"
require_contains 'fedora_source_archive_transcript_review_validator_present=1' "$doc"
require_contains 'source_archive_transcript_review_mode=no-effect-validation' "$doc"
require_contains 'source_archive_transcript_candidate_valid=0' "$doc"
require_contains 'source_archive_accepted_by_transcript_validator=0' "$doc"
require_contains 'source_archive_written_by_transcript_validator=0' "$doc"
require_contains 'source_archive_accepted_for_build_by_transcript_validator_alone=0' "$doc"
require_contains 'sh scripts/fedora-source-archive-transcript-review.sh --transcript <path>' "$doc"
require_contains 'sh scripts/test-fedora-source-archive-transcript-review-validator.sh' "$doc"

require_contains 'FEDORA SOURCE ARCHIVE TRANSCRIPT REVIEW VALIDATION' "$script"
require_contains 'source_archive_transcript_review_status=ok' "$script"
require_contains 'source_archive_transcript_candidate_valid=1' "$script"
require_contains 'source_archive_transcript_placeholder_values_absent=1' "$script"
require_contains 'source_archive_transcript_required_markers_present=1' "$script"
require_contains 'source_archive_transcript_value_fields_validated=1' "$script"
require_contains 'source_archive_accepted_by_transcript_validator=0' "$script"
require_contains 'source_archive_written_by_transcript_validator=0' "$script"
require_contains 'source_archive_accepted_for_build_by_transcript_validator_alone=0' "$script"
require_contains 'placeholder value is not acceptable' "$script"
require_absent 'sudo ' "$script"
require_absent 'dnf ' "$script"
require_absent 'curl ' "$script"
require_absent 'wget ' "$script"
require_absent 'rpm -Uvh' "$script"
require_absent 'rpm -e' "$script"

for current_field in \
  'fedora_source_archive_transcript_review_validator_present=1' \
  'source_archive_transcript_review_mode=no-effect-validation' \
  'source_archive_transcript_candidate_valid=0' \
  'source_archive_transcript_required_markers_present=0' \
  'source_archive_transcript_placeholder_values_absent=0' \
  'source_archive_transcript_value_fields_validated=0' \
  'source_archive_transcript_reviewed=0' \
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
  require_contains "$current_field" "$doc"
  require_contains "$current_field" "$status"
  require_contains "$current_field" "$index"
  require_contains "$current_field" "$readme"
  require_contains "$current_field" "$matrix"
done

for future_marker in \
  'FEDORA SOURCE ARCHIVE REPRODUCIBILITY TRANSCRIPT' \
  'source_archive_transcript_present=1' \
  'source_archive_name_matches_source0=1' \
  'source_archive_root_matches_autosetup=1' \
  'source_archive_sha256_recorded=1' \
  'source_archive_generated_twice=1' \
  'source_archive_repeated_sha256_match=1' \
  'source_archive_excludes_git_dir=1' \
  'source_archive_excludes_nested_archives=1' \
  'source_archive_excludes_build_outputs=1' \
  'source_archive_excludes_rpm_artifacts=1' \
  'source_archive_symlink_policy_checked=1' \
  'source_archive_path_safety_checked=1' \
  'accepted_rpmlint_transcript_present=1' \
  'source_archive_reproducible=1'
do
  require_contains "$future_marker" "$doc"
  require_contains "$future_marker" "$script"
done

require_contains 'fedora_source_archive_reproducibility_contract_present=1' "$contract"
require_contains 'source_archive_transcript_present=0' "$contract_status"
require_contains 'refuse symlink entries' "$fixture"
require_contains 'fedora_rpmlint_findings_classification_present=1' "$rpmlint_classification"
require_contains 'source_archive_accepted_for_build=0' "$matrix"
require_contains 'fedora_source_archive_transcript_review_validator_present=1' "$matrix_script"
require_contains 'fedora_source_archive_transcript_review_validator_present=1' "$matrix_status"
require_contains 'fedora_source_archive_transcript_review_validator_present=1' "$matrix_test"
require_contains 'Source0:        %{name}-%{version}.tar.gz' "$spec"

require_contains 'FEDORA_SOURCE_ARCHIVE_TRANSCRIPT_REVIEW_VALIDATOR_STATUS.md' "$index"
require_contains 'Current Fedora source archive transcript review validator checkpoint' "$index"
require_contains 'The Fedora source archive transcript review validator is present but does not accept source archive evidence' "$index"
require_contains 'docs/FEDORA_SOURCE_ARCHIVE_TRANSCRIPT_REVIEW_VALIDATOR.md' "$readme"
require_contains 'docs/status/FEDORA_SOURCE_ARCHIVE_TRANSCRIPT_REVIEW_VALIDATOR_STATUS.md' "$readme"
require_contains 'The Fedora source archive transcript review validator is present' "$readme"

require_contains 'name: Fedora Source Archive Transcript Review Validator' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-source-archive-transcript-review-validator.sh' "$workflow"
require_absent 'sh scripts/fedora-source-archive-transcript-review.sh' "$workflow"

require_contains 'sh ./scripts/test-fedora-source-archive-transcript-review-validator.sh' 'Makefile'
require_contains 'fedora-source-archive-transcript-review-validator:' 'Makefile'

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-fedora-source-archive-transcript-review.XXXXXX")"
trap 'rm -rf "$tmp"' EXIT INT HUP TERM

valid="$tmp/valid.transcript"
placeholder="$tmp/placeholder.transcript"

cat >"$valid" <<'VALID_TRANSCRIPT'
FEDORA SOURCE ARCHIVE REPRODUCIBILITY TRANSCRIPT
source_tree_revision=0123456789abcdef0123456789abcdef01234567
source_archive_command=git ls-files plus deterministic tar and gzip
source_archive_name=latticra-0.0.0.tar.gz
source_archive_root=latticra-0.0.0/
source_archive_size_bytes=123456
source_archive_sha256=0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef
source_archive_entry_count=100
source_archive_transcript_present=1
source_archive_name_matches_source0=1
source_archive_root_matches_autosetup=1
source_archive_sha256_recorded=1
source_archive_generated_twice=1
source_archive_repeated_sha256_match=1
source_archive_contains_spec=1
source_archive_contains_readme=1
source_archive_excludes_git_dir=1
source_archive_excludes_nested_archives=1
source_archive_excludes_build_outputs=1
source_archive_excludes_rpm_artifacts=1
source_archive_symlink_policy_checked=1
source_archive_path_safety_checked=1
license_expression_reviewed=1
package_notice_obligations_reviewed=1
fedora_rpmlint_findings_classification_present=1
accepted_rpmlint_transcript_present=1
source_archive_reproducible=1
source_archive_accepted_for_build=0
rpmbuild_run=0
mock_build_run=0
rpm_artifact_created=0
fedora_package_review_ready=0
fedora_distribution_ready=0
production_installer_ready=0
host_mutation_performed=0
VALID_TRANSCRIPT

cat >"$placeholder" <<'PLACEHOLDER_TRANSCRIPT'
FEDORA SOURCE ARCHIVE REPRODUCIBILITY TRANSCRIPT
source_tree_revision=<required-after-source-archive-run>
source_archive_command=git ls-files plus deterministic tar and gzip
source_archive_name=latticra-0.0.0.tar.gz
source_archive_root=latticra-0.0.0/
source_archive_size_bytes=123456
source_archive_sha256=0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef
source_archive_entry_count=100
source_archive_transcript_present=1
source_archive_name_matches_source0=1
source_archive_root_matches_autosetup=1
source_archive_sha256_recorded=1
source_archive_generated_twice=1
source_archive_repeated_sha256_match=1
source_archive_contains_spec=1
source_archive_contains_readme=1
source_archive_excludes_git_dir=1
source_archive_excludes_nested_archives=1
source_archive_excludes_build_outputs=1
source_archive_excludes_rpm_artifacts=1
source_archive_symlink_policy_checked=1
source_archive_path_safety_checked=1
license_expression_reviewed=1
package_notice_obligations_reviewed=1
fedora_rpmlint_findings_classification_present=1
accepted_rpmlint_transcript_present=1
source_archive_reproducible=1
source_archive_accepted_for_build=0
rpmbuild_run=0
mock_build_run=0
rpm_artifact_created=0
fedora_package_review_ready=0
fedora_distribution_ready=0
production_installer_ready=0
host_mutation_performed=0
PLACEHOLDER_TRANSCRIPT

output=$(sh "$script" --transcript "$valid")
require_output_contains "$output" 'FEDORA SOURCE ARCHIVE TRANSCRIPT REVIEW VALIDATION'
require_output_contains "$output" 'source_archive_transcript_review_status=ok'
require_output_contains "$output" 'source_archive_transcript_candidate_valid=1'
require_output_contains "$output" 'source_archive_transcript_required_markers_present=1'
require_output_contains "$output" 'source_archive_transcript_placeholder_values_absent=1'
require_output_contains "$output" 'source_archive_transcript_value_fields_validated=1'
require_output_contains "$output" 'candidate_source_archive_transcript_present=1'
require_output_contains "$output" 'candidate_source_archive_reproducible=1'
require_output_contains "$output" 'source_archive_accepted_by_transcript_validator=0'
require_output_contains "$output" 'source_archive_written_by_transcript_validator=0'
require_output_contains "$output" 'source_archive_accepted_for_build_by_transcript_validator_alone=0'
require_output_contains "$output" 'source_archive_accepted_for_build=0'
require_output_contains "$output" 'rpmbuild_run=0'
require_output_contains "$output" 'mock_build_run=0'
require_output_contains "$output" 'rpm_artifact_created=0'
require_output_contains "$output" 'host_mutation_performed=0'

if sh "$script" --transcript "$placeholder" >/dev/null 2>&1; then
  fail 'placeholder Fedora source archive transcript unexpectedly passed validation'
fi

printf 'fedora_source_archive_transcript_review_validator: ok\n'
