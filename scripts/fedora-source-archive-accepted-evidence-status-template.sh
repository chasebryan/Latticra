#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  fedora-source-archive-accepted-evidence-status-template.sh

Emits a no-effect Fedora source archive accepted evidence status template. It
validates local source records and prints the required future evidence status
fields. It does not create a source archive, validate a live transcript, run
the source archive acceptance gate against a live report, write evidence status,
accept source archive evidence, open mock build input, run RPM builds, install
packages, or mutate the host.
USAGE
}

fail() {
  printf 'fedora source archive accepted evidence status template: %s\n' "$1" >&2
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

while [ "$#" -gt 0 ]; do
  case "$1" in
    -h|--help)
      usage
      exit 0
      ;;
    *)
      fail "unknown argument: $1" 64
      ;;
  esac
done

require_file docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_file docs/FEDORA_SOURCE_ARCHIVE_TRANSCRIPT_REVIEW_VALIDATOR.md
require_file docs/FEDORA_SOURCE_ARCHIVE_ACCEPTANCE_GATE.md
require_file docs/status/FEDORA_SOURCE_ARCHIVE_ACCEPTANCE_GATE_STATUS.md
require_file scripts/fedora-source-archive-transcript-review.sh
require_file scripts/fedora-source-archive-acceptance-gate.sh
require_file docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md
require_file packaging/fedora/latticra.spec
require_file README.md

require_contains 'fedora_source_archive_reproducibility_contract_present=1' docs/FEDORA_SOURCE_ARCHIVE_REPRODUCIBILITY_CONTRACT.md
require_contains 'fedora_source_archive_transcript_review_validator_present=1' docs/FEDORA_SOURCE_ARCHIVE_TRANSCRIPT_REVIEW_VALIDATOR.md
require_contains 'fedora_source_archive_acceptance_gate_present=1' docs/FEDORA_SOURCE_ARCHIVE_ACCEPTANCE_GATE.md
require_contains 'source_archive_accepted_for_build_by_acceptance_gate_alone=0' docs/status/FEDORA_SOURCE_ARCHIVE_ACCEPTANCE_GATE_STATUS.md
require_contains 'source_archive_accepted_for_build_by_acceptance_gate_alone=0' scripts/fedora-source-archive-acceptance-gate.sh
require_contains 'source_archive_accepted_for_build_by_transcript_validator_alone=0' scripts/fedora-source-archive-transcript-review.sh
require_contains 'source_archive_accepted_for_build=0' docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md
require_contains 'fedora_mock_build_input_opened=0' docs/FEDORA_PRODUCTION_READINESS_EVIDENCE_MATRIX.md
require_contains 'Source0:        %{name}-%{version}.tar.gz' packaging/fedora/latticra.spec
require_contains 'Fedora source archive acceptance gate is present' README.md

cat <<'REPORT'
FEDORA SOURCE ARCHIVE ACCEPTED EVIDENCE STATUS TEMPLATE

template_status=ok
fedora_source_archive_accepted_evidence_status_template_present=1
source_archive_accepted_evidence_status_template_mode=no-effect-template
source_archive_accepted_evidence_status_template_decision=blocked-template-only-no-status-write
source_archive_accepted_evidence_status_template_complete=0
source_archive_transcript_attached=0
source_archive_transcript_review_report_attached=0
source_archive_acceptance_gate_report_attached=0
source_archive_acceptance_gate_reviewed=0
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

[required_prior_review]
source_archive_transcript_attached=1
source_archive_transcript_review_report_attached=1
source_archive_acceptance_gate_report_attached=1
source_archive_transcript_candidate_valid=1
source_archive_transcript_reviewed=1
source_archive_transcript_review_report_valid=1
source_archive_acceptance_gate_reviewed=1
source_archive_reproducible=1
source_archive_repeated_sha256_match=1
accepted_rpmlint_transcript_present=1
operator_review_required=1
acceptance_gate_confirmed=1

[future_accepted_evidence_status_record]
FEDORA SOURCE ARCHIVE ACCEPTED EVIDENCE STATUS
Status: source archive evidence status alignment
Date: <required-from-operator-review-date>
source=operator Fedora source archive reproducibility transcript and acceptance gate report
source_archive_transcript_path=<required-from-operator-attachment>
source_archive_transcript_review_report_path=<required-from-operator-attachment>
source_archive_acceptance_gate_report_path=<required-from-operator-attachment>
source_tree_revision=<required-from-reviewed-source-archive-transcript>
source_archive_command=<required-from-reviewed-source-archive-transcript>
source_archive_name=latticra-0.0.0.tar.gz
source_archive_root=latticra-0.0.0/
source_archive_size_bytes=<required-from-reviewed-source-archive-transcript>
source_archive_sha256=<required-from-reviewed-source-archive-transcript>
source_archive_entry_count=<required-from-reviewed-source-archive-transcript>
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

[non_claims]
rpmbuild_run=0
mock_build_run=0
rpm_artifact_created=0
fedora_package_review_ready=0
fedora_distribution_ready=0
production_installer_ready=0
host_mutation_performed=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
REPORT
