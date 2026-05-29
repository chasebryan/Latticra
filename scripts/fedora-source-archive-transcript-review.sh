#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  fedora-source-archive-transcript-review.sh --transcript <path>

Validates a supplied Fedora source archive reproducibility transcript
candidate. It reads the provided file, rejects missing required markers and
placeholder values, and prints a no-effect review report. It does not create
a source archive, run archive commands, run `rpmbuild`, run `mock`, create RPM
artifacts, accept source archive evidence, install packages, or mutate the host.
USAGE
}

fail() {
  printf 'fedora source archive transcript review: %s\n' "$1" >&2
  exit "${2:-1}"
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file" 66
}

require_contains() {
  pattern="$1"
  file="$2"
  grep -Fq -- "$pattern" "$file" || fail "missing required pattern in $file: $pattern"
}

require_absent() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    fail "unexpected pattern in $file: $pattern"
  fi
}

field_value() {
  field="$1"
  awk -v field="$field" 'index($0, field "=") == 1 { sub(field "=", ""); print; exit }' "$TRANSCRIPT_CANDIDATE"
}

reject_placeholders() {
  file="$1"
  if grep -Eq -- '<required|<placeholder>|TODO|TBD' "$file"; then
    fail "placeholder value is not acceptable in transcript candidate"
  fi
}

require_field_value() {
  field="$1"
  value="$(field_value "$field")"
  [ -n "$value" ] || fail "missing required field value: $field"
  case "$value" in
    *'<required'*|*'<placeholder>'*|*TODO*|*TBD*|'')
      fail "placeholder value is not acceptable for: $field"
      ;;
  esac
}

require_field_pattern() {
  field="$1"
  pattern="$2"
  description="$3"
  value="$(field_value "$field")"
  [ -n "$value" ] || fail "missing required field value: $field"
  printf '%s\n' "$value" | grep -Eq -- "$pattern" ||
    fail "invalid $description for $field: $value"
}

TRANSCRIPT_CANDIDATE=''

while [ "$#" -gt 0 ]; do
  case "$1" in
    --transcript)
      [ "$#" -ge 2 ] || fail "missing value for --transcript" 64
      TRANSCRIPT_CANDIDATE="$2"
      shift 2
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      fail "unknown argument: $1" 64
      ;;
  esac
done

[ -n "$TRANSCRIPT_CANDIDATE" ] || fail 'missing --transcript path' 64
require_file "$TRANSCRIPT_CANDIDATE"
require_file docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_file docs/status/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT_STATUS.md
require_file docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_file docs/FEDORA_RPMLINT_FINDINGS_CLASSIFICATION.md
require_file docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md
require_file packaging/fedora/latticra.spec
require_file README.md

require_contains 'fedora_source_archive_reproducibility_contract_present=1' docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'source_archive_transcript_present=0' docs/status/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT_STATUS.md
require_contains 'refuse symlink entries' docs/FEDORA_SOURCE_ARCHIVE_FIXTURE_LANE.md
require_contains 'fedora_rpmlint_findings_classification_present=1' docs/FEDORA_RPMLINT_FINDINGS_CLASSIFICATION.md
require_contains 'source_archive_accepted_for_build=0' docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md
require_contains 'Source0:        %{name}-%{version}.tar.gz' packaging/fedora/latticra.spec
require_contains 'Fedora source archive reproducibility contract is present' README.md

for marker in \
  'FEDORA SOURCE ARCHIVE REPRODUCIBILITY TRANSCRIPT' \
  'source_archive_transcript_present=1' \
  'source_archive_name_matches_source0=1' \
  'source_archive_root_matches_autosetup=1' \
  'source_archive_sha256_recorded=1' \
  'source_archive_generated_twice=1' \
  'source_archive_repeated_sha256_match=1' \
  'source_archive_contains_spec=1' \
  'source_archive_contains_readme=1' \
  'source_archive_excludes_git_dir=1' \
  'source_archive_excludes_nested_archives=1' \
  'source_archive_excludes_build_outputs=1' \
  'source_archive_excludes_rpm_artifacts=1' \
  'source_archive_symlink_policy_checked=1' \
  'source_archive_path_safety_checked=1' \
  'license_expression_reviewed=1' \
  'package_notice_obligations_reviewed=1' \
  'fedora_rpmlint_findings_classification_present=1' \
  'accepted_rpmlint_transcript_present=1' \
  'source_archive_reproducible=1' \
  'source_archive_accepted_for_build=0' \
  'rpmbuild_run=0' \
  'mock_build_run=0' \
  'rpm_artifact_created=0' \
  'fedora_package_review_ready=0' \
  'fedora_distribution_ready=0' \
  'production_installer_ready=0' \
  'host_mutation_performed=0'
do
  require_contains "$marker" "$TRANSCRIPT_CANDIDATE"
done

reject_placeholders "$TRANSCRIPT_CANDIDATE"

require_field_value source_tree_revision
require_field_value source_archive_command
require_field_pattern source_archive_name '^latticra-0[.]0[.]0[.]tar[.]gz$' 'source archive name'
require_field_pattern source_archive_root '^latticra-0[.]0[.]0/$' 'source archive root'
require_field_pattern source_archive_size_bytes '^[1-9][0-9]*$' 'source archive size'
require_field_pattern source_archive_sha256 '^[0-9a-f]{64}$' 'source archive sha256'
require_field_pattern source_archive_entry_count '^[1-9][0-9]*$' 'source archive entry count'

for forbidden_claim in \
  'source_archive_accepted_for_build=1' \
  'rpmbuild_run=1' \
  'mock_build_run=1' \
  'rpm_artifact_created=1' \
  'fedora_package_review_ready=1' \
  'fedora_distribution_ready=1' \
  'production_installer_ready=1' \
  'host_mutation_performed=1'
do
  require_absent "$forbidden_claim" "$TRANSCRIPT_CANDIDATE"
done

cat <<'REPORT'
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
REPORT
