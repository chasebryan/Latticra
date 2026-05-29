#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  fedora-source-archive-accepted-evidence-acceptance-gate.sh --status-review <path>

Checks a supplied Fedora source archive accepted evidence status review report
and emits a no-effect acceptance gate report. It does not create a source
archive, validate a live transcript, write evidence status, accept source
archive evidence, open mock build input, run RPM builds, install packages, or
mutate the host.
USAGE
}

fail() {
  printf 'fedora source archive accepted evidence acceptance gate: %s\n' "$1" >&2
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

require_absent_line() {
  pattern="$1"
  file="$2"
  if grep -Fxq -- "$pattern" "$file"; then
    fail "unexpected pattern in $file: $pattern"
  fi
}

reject_placeholders() {
  file="$1"
  if grep -Eq -- '<required|<placeholder>|TODO|TBD' "$file"; then
    fail "placeholder value is not acceptable in source archive accepted evidence status review report"
  fi
}

STATUS_REVIEW_REPORT=''

while [ "$#" -gt 0 ]; do
  case "$1" in
    --status-review)
      [ "$#" -ge 2 ] || fail "missing value for --status-review" 64
      STATUS_REVIEW_REPORT="$2"
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

[ -n "$STATUS_REVIEW_REPORT" ] || fail 'missing --status-review path' 64
require_file "$STATUS_REVIEW_REPORT"
require_file docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_REVIEW_VALIDATOR.md
require_file docs/status/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_REVIEW_VALIDATOR_STATUS.md
require_file scripts/fedora-source-archive-accepted-evidence-status-review.sh
require_file docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_TEMPLATE.md
require_file docs/FEDORA_SOURCE_ARCHIVE_ACCEPTANCE_GATE.md
require_file docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_file docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md
require_file packaging/fedora/latticra.spec
require_file README.md

require_contains 'FEDORA SOURCE ARCHIVE ACCEPTED EVIDENCE STATUS REVIEW' docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_REVIEW_VALIDATOR.md
require_contains 'source_archive_accepted_evidence_status_candidate_valid=0' docs/status/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_REVIEW_VALIDATOR_STATUS.md
require_contains 'source_archive_accepted_evidence_status_candidate_valid=1' scripts/fedora-source-archive-accepted-evidence-status-review.sh
require_contains 'source_archive_accepted_evidence_status_written=1' docs/FEDORA_SOURCE_ARCHIVE_ACCEPTED_EVIDENCE_STATUS_TEMPLATE.md
require_contains 'source_archive_accepted_for_build_by_acceptance_gate_alone=0' docs/FEDORA_SOURCE_ARCHIVE_ACCEPTANCE_GATE.md
require_contains 'fedora_source_archive_reproducibility_contract_present=1' docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'source_archive_accepted_for_build=0' docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md
require_contains 'Source0:        %{name}-%{version}.tar.gz' packaging/fedora/latticra.spec
require_contains 'The Fedora source archive accepted evidence status review validator is present' README.md

for marker in \
  'FEDORA SOURCE ARCHIVE ACCEPTED EVIDENCE STATUS REVIEW' \
  'review_status=ok' \
  'fedora_source_archive_accepted_evidence_status_review_validator_present=1' \
  'source_archive_accepted_evidence_status_review_mode=no-effect-validation' \
  'source_archive_accepted_evidence_status_candidate_valid=1' \
  'source_archive_accepted_evidence_status_required_markers_present=1' \
  'source_archive_accepted_evidence_status_placeholder_values_absent=1' \
  'source_archive_accepted_evidence_status_value_fields_validated=1' \
  'source_archive_accepted_evidence_status_reviewed=1' \
  'candidate_source_archive_accepted_evidence_status_written=1' \
  'candidate_source_archive_accepted_evidence_present=1' \
  'candidate_source_archive_accepted_for_build=1' \
  'candidate_fedora_mock_build_input_opened=1' \
  'source_archive_accepted_evidence_status_accepted_by_validator=0' \
  'source_archive_accepted_evidence_status_written_by_validator=0' \
  'source_archive_accepted_for_build_by_status_validator_alone=0' \
  'fedora_mock_build_input_opened_by_status_validator_alone=0' \
  'rpmbuild_run=0' \
  'mock_build_run=0' \
  'rpm_artifact_created=0' \
  'fedora_package_review_ready=0' \
  'fedora_distribution_ready=0' \
  'production_installer_ready=0' \
  'host_mutation_performed=0'
do
  require_contains "$marker" "$STATUS_REVIEW_REPORT"
done

reject_placeholders "$STATUS_REVIEW_REPORT"

for forbidden_claim in \
  'source_archive_accepted_evidence_status_accepted_by_validator=1' \
  'source_archive_accepted_evidence_status_written_by_validator=1' \
  'source_archive_accepted_for_build_by_status_validator_alone=1' \
  'fedora_mock_build_input_opened_by_status_validator_alone=1' \
  'source_archive_accepted_by_accepted_evidence_acceptance_gate=1' \
  'source_archive_accepted_evidence_status_written_by_acceptance_gate=1' \
  'source_archive_accepted_for_build_by_acceptance_gate_alone=1' \
  'fedora_mock_build_input_opened_by_acceptance_gate_alone=1' \
  'source_archive_accepted_for_build=1' \
  'fedora_mock_build_input_opened=1' \
  'rpmbuild_run=1' \
  'mock_build_run=1' \
  'rpm_artifact_created=1' \
  'fedora_package_review_ready=1' \
  'fedora_distribution_ready=1' \
  'production_installer_ready=1' \
  'host_mutation_performed=1'
do
  require_absent_line "$forbidden_claim" "$STATUS_REVIEW_REPORT"
done

cat <<'REPORT'
FEDORA SOURCE ARCHIVE ACCEPTED EVIDENCE ACCEPTANCE GATE
acceptance_gate_status=blocked
fedora_source_archive_accepted_evidence_acceptance_gate_present=1
source_archive_accepted_evidence_acceptance_gate_mode=no-effect-gate
source_archive_accepted_evidence_status_review_report_valid=1
source_archive_accepted_evidence_status_candidate_valid=1
source_archive_accepted_evidence_status_reviewed=1
candidate_source_archive_accepted_evidence_status_written=1
candidate_source_archive_accepted_evidence_present=1
candidate_source_archive_accepted_for_build=1
candidate_fedora_mock_build_input_opened=1
source_archive_accepted_evidence_acceptance_requested=0
source_archive_accepted_by_accepted_evidence_acceptance_gate=0
source_archive_accepted_evidence_status_written_by_acceptance_gate=0
source_archive_accepted_for_build_by_acceptance_gate_alone=0
fedora_mock_build_input_opened_by_acceptance_gate_alone=0
source_archive_accepted_evidence_status_written=0
source_archive_accepted_evidence_present=0
source_archive_accepted=0
source_archive_accepted_for_build=0
fedora_mock_build_input_opened=0
rpmbuild_run=0
mock_build_run=0
rpm_artifact_created=0
fedora_package_review_ready=0
fedora_distribution_ready=0
production_installer_ready=0
host_mutation_performed=0
REPORT
