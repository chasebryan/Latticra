#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  fedora-vm-cli-payload-repeatability-evidence-status-review.sh --status <path>

Validates a supplied Fedora VM CLI payload repeatability evidence status
candidate. It reads the provided file, rejects missing required markers and
placeholder values, and prints a no-effect review report. It does not run the
repeatability runner, validate a live transcript, attach a transcript, write
evidence status, build an RPM, install an RPM, remove an RPM, or mutate the
host.
USAGE
}

fail() {
  printf 'fedora vm cli payload repeatability evidence status review: %s\n' "$1" >&2
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

require_field_value() {
  field="$1"
  value="$(field_value "$field")"
  [ -n "$value" ] || fail "missing required field value: $field"
  case "$value" in
    *'<required-from-real-run>'*|*'<required-from-accepted-review>'*|*'<required-from-operator-attachment>'*|*'<required'*|'<placeholder>'|'')
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
    *'<required'*|'<placeholder>'|'')
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
require_file docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_TEMPLATE.md
require_file docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_ACCEPTANCE_CONTRACT.md
require_file scripts/fedora-vm-cli-payload-repeatability-evidence-status-template.sh

require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY EVIDENCE STATUS' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_TEMPLATE.md
require_contains 'evidence_status_written=1' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_TEMPLATE.md
require_contains 'The acceptance contract alone cannot promote evidence.' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_ACCEPTANCE_CONTRACT.md
require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY EVIDENCE STATUS TEMPLATE' scripts/fedora-vm-cli-payload-repeatability-evidence-status-template.sh

for marker in \
  'FEDORA VM CLI PAYLOAD REPEATABILITY EVIDENCE STATUS' \
  'Status: evidence status alignment' \
  'source=operator disposable Fedora VM repeatability transcript' \
  'transcript_kind=disposable-vm-cli-payload-repeatability' \
  'repeatability_transcript_reviewed=1' \
  'repeatability_transcript_accepted=1' \
  'repeatability_transcript_candidate_valid=1' \
  'repeatability_transcript_placeholder_values_absent=1' \
  'repeatability_transcript_required_markers_present=1' \
  'repeatability_transcript_value_fields_validated=1' \
  'source_tree_revision_recorded=1' \
  'fedora_os_release_recorded=1' \
  'fedora_kernel_version_recorded=1' \
  'spec_checksum_recorded=1' \
  'source_archive_checksum_recorded=1' \
  'rpm_nevra_recorded=1' \
  'rpm_payload_matches_expected_cli_surfaces=1' \
  'validated_cli_mode_still_no_effect=1' \
  'validated_runtime_behavior_still_disabled=1' \
  'validated_non_claims_preserved=1' \
  'rpm_verify_completed=1' \
  'removal_validation_performed=1' \
  'post_removal_absence_verified=1' \
  'second_disposable_vm_cli_validation_completed=1' \
  'cli_payload_repeatability_evidence_present=1' \
  'host_install_ready_for_cli_payload=1' \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0' \
  'evidence_level=9' \
  'evidence_status_written=1'
do
  require_contains "$marker" "$STATUS_CANDIDATE"
done

require_date_field
require_field_value transcript_path
require_field_pattern transcript_checksum '^[0-9A-Fa-f]{64}$' 'transcript checksum'
require_field_pattern source_tree_revision '^[0-9A-Fa-f]{40,64}$' 'source tree revision'
require_field_value fedora_os_release
require_field_value fedora_kernel_version
require_field_pattern spec_checksum '^[0-9A-Fa-f]{64}$' 'spec checksum'
require_field_pattern source_archive_checksum '^[0-9A-Fa-f]{64}$' 'source archive checksum'
require_field_pattern rpm_nevra '^latticra-0\.0\.0-.+[.][^.]+$' 'RPM NEVRA'

cat <<'REPORT'
FEDORA VM CLI PAYLOAD REPEATABILITY EVIDENCE STATUS REVIEW
review_status=ok
fedora_vm_cli_payload_repeatability_evidence_status_review_validator_present=1
repeatability_evidence_status_review_mode=no-effect-validation
repeatability_evidence_status_candidate_valid=1
repeatability_evidence_status_placeholder_values_absent=1
repeatability_evidence_status_required_markers_present=1
repeatability_evidence_status_value_fields_validated=1
repeatability_evidence_status_reviewed=1
candidate_repeatability_transcript_accepted=1
candidate_cli_payload_repeatability_evidence_present=1
candidate_evidence_status_written=1
repeatability_evidence_status_accepted_by_validator=0
evidence_status_written_by_validator=0
promotion_allowed_by_status_validator_alone=0
host_mutation_performed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
REPORT
