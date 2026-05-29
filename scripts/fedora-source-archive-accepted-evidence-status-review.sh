#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  fedora-source-archive-accepted-evidence-status-review.sh --status <path>

Validates a supplied Fedora source archive accepted evidence status candidate.
It reads the provided file, rejects missing required markers and placeholder
values, and prints a no-effect review report. It does not create a source
archive, validate a live transcript, write evidence status, accept source
archive evidence, open mock build input, run RPM builds, install packages, or
mutate the host.
USAGE
}

fail() {
  printf 'fedora source archive accepted evidence status review: %s\n' "$1" >&2
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

field_value() {
  field="$1"
  awk -v field="$field" 'index($0, field "=") == 1 { sub(field "=", ""); print; exit }' "$STATUS_CANDIDATE"
}

reject_placeholders() {
  file="$1"
  if grep -Eq -- '<required|<placeholder>|TODO|TBD' "$file"; then
    fail "placeholder value is not acceptable in source archive accepted evidence status candidate"
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

require_date_field() {
  value="$(awk 'index($0, "Date: ") == 1 { sub("Date: ", ""); print; exit }' "$STATUS_CANDIDATE")"
  [ -n "$value" ] || fail 'missing required Date field'
  case "$value" in
    *'<required'*|*'<placeholder>'*|*TODO*|*TBD*|'')
      fail 'placeholder value is not acceptable for: Date'
      ;;
  esac
  printf '%s\n' "$value" | grep -Eq '^[0-9]{4}-[0-9]{2}-[0-9]{2}$' ||
    fail "invalid date for Date: $value"
}

STATUS_CANDIDATE=''

while [ "$#" -gt 0 ]; do
  case "$1" in
    --status)
      [ "$#" -ge 2 ] || fail "missing value for --status" 64
      STATUS_CANDIDATE="$2"
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

[ -n "$STATUS_CANDIDATE" ] || fail 'missing --status path' 64
require_file "$STATUS_CANDIDATE"
require_file docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_TEMPLATE.md
require_file docs/status/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_TEMPLATE_STATUS.md
require_file docs/FEDORA_SOURCE_ARCHIVE_ACCEPTANCE_GATE.md
require_file docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_file scripts/fedora-source-archive-accepted-evidence-status-template.sh
require_file scripts/fedora-source-archive-acceptance-gate.sh
require_file docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md
require_file packaging/fedora/latticra.spec
require_file README.md

require_contains 'FEDORA SOURCE ARCHIVE ACCEPTED EVIDENCE STATUS' docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_TEMPLATE.md
require_contains 'source_archive_accepted_evidence_status_written=1' docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_TEMPLATE.md
require_contains 'source_archive_accepted_evidence_status_template_complete=0' docs/status/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_TEMPLATE_STATUS.md
require_contains 'source_archive_accepted_for_build_by_acceptance_gate_alone=0' docs/FEDORA_SOURCE_ARCHIVE_ACCEPTANCE_GATE.md
require_contains 'fedora_source_archive_reproducibility_contract_present=1' docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'FEDORA SOURCE ARCHIVE ACCEPTED EVIDENCE STATUS TEMPLATE' scripts/fedora-source-archive-accepted-evidence-status-template.sh
require_contains 'source_archive_accepted_for_build_by_acceptance_gate_alone=0' scripts/fedora-source-archive-acceptance-gate.sh
require_contains 'source_archive_accepted_for_build=0' docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md
require_contains 'Source0:        %{name}-%{version}.tar.gz' packaging/fedora/latticra.spec
require_contains 'Fedora source archive accepted evidence status template is present' README.md

for marker in \
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
  require_contains "$marker" "$STATUS_CANDIDATE"
done

reject_placeholders "$STATUS_CANDIDATE"
require_date_field
require_field_value source_archive_transcript_path
require_field_value source_archive_transcript_review_report_path
require_field_value source_archive_acceptance_gate_report_path
require_field_pattern source_tree_revision '^[0-9A-Fa-f]{40,64}$' 'source tree revision'
require_field_value source_archive_command
require_field_pattern source_archive_name '^latticra-0[.]0[.]0[.]tar[.]gz$' 'source archive name'
require_field_pattern source_archive_root '^latticra-0[.]0[.]0/$' 'source archive root'
require_field_pattern source_archive_size_bytes '^[1-9][0-9]*$' 'source archive size'
require_field_pattern source_archive_sha256 '^[0-9a-f]{64}$' 'source archive sha256'
require_field_pattern source_archive_entry_count '^[1-9][0-9]*$' 'source archive entry count'

cat <<'REPORT'
FEDORA SOURCE ARCHIVE ACCEPTED EVIDENCE STATUS REVIEW
review_status=ok
fedora_source_archive_accepted_evidence_status_review_validator_present=1
source_archive_accepted_evidence_status_review_mode=no-effect-validation
source_archive_accepted_evidence_status_candidate_valid=1
source_archive_accepted_evidence_status_required_markers_present=1
source_archive_accepted_evidence_status_placeholder_values_absent=1
source_archive_accepted_evidence_status_value_fields_validated=1
source_archive_accepted_evidence_status_reviewed=1
candidate_source_archive_accepted_evidence_status_written=1
candidate_source_archive_accepted_evidence_present=1
candidate_source_archive_accepted_for_build=1
candidate_fedora_mock_build_input_opened=1
source_archive_accepted_evidence_status_accepted_by_validator=0
source_archive_accepted_evidence_status_written_by_validator=0
source_archive_accepted_for_build_by_status_validator_alone=0
fedora_mock_build_input_opened_by_status_validator_alone=0
rpmbuild_run=0
mock_build_run=0
rpm_artifact_created=0
fedora_package_review_ready=0
fedora_distribution_ready=0
production_installer_ready=0
host_mutation_performed=0
REPORT
