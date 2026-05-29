#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  fedora-vm-cli-payload-repeatability-transcript-review.sh --transcript <path>

Validates a supplied Fedora VM CLI payload repeatability transcript candidate.
It reads the provided file, rejects missing required markers and placeholder
values, and prints a no-effect review report. It does not run the repeatability
runner, build a package, install a package, remove a package, write evidence
status, or mutate the host.
USAGE
}

fail() {
  printf 'fedora vm cli payload repeatability transcript review: %s\n' "$1" >&2
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
  awk -v field="$field" 'index($0, field "=") == 1 { sub(field "=", ""); print; exit }' "$TRANSCRIPT"
}

require_field_value() {
  field="$1"
  value="$(field_value "$field")"
  [ -n "$value" ] || fail "missing required field value: $field"
  case "$value" in
    *'<required-from-real-run>'*|*'<required'*|'<placeholder>'|'')
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

TRANSCRIPT=''

while [ "$#" -gt 0 ]; do
  case "$1" in
    --transcript)
      [ "$#" -ge 2 ] || fail "missing value for --transcript" 64
      TRANSCRIPT="$2"
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

[ -n "$TRANSCRIPT" ] || fail 'missing --transcript path' 64
require_file "$TRANSCRIPT"
require_file docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CAPTURE_TEMPLATE.md
require_file docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_REVIEW_GATE.md
require_file scripts/run-fedora-vm-cli-payload-repeatability-lane.sh

for marker in \
  'FEDORA VM CLI PAYLOAD REPEATABILITY TRANSCRIPT' \
  'transcript_kind=disposable-vm-cli-payload-repeatability' \
  'transcript_version=1' \
  'operator_review_required=1' \
  'repeatability_transcript_recorded_after_real_run=1' \
  'prior_cli_payload_evidence_recorded=1' \
  'prior_validated_package=latticra-0.0.0-0.1.local.fc44.x86_64.rpm' \
  'prior_validated_payload=/usr/bin/latticra' \
  'prior_validated_payload=/usr/share/doc/latticra/README.md' \
  'prior_disposable_vm_cli_validation_completed=1' \
  'prior_host_install_ready_for_cli_payload=1' \
  'prior_evidence_level=9' \
  'FEDORA VM CLI PAYLOAD REPEATABILITY LANE' \
  'validation_status=ok' \
  'repeatability_validation_status=ok' \
  'source_tree_revision_recorded=1' \
  'fedora_os_release_recorded=1' \
  'fedora_kernel_version_recorded=1' \
  'spec_checksum_recorded=1' \
  'source_archive_checksum_recorded=1' \
  'rpm_nevra_recorded=1' \
  'package_name=latticra' \
  'package_version=0.0.0' \
  'rpm_payload_listing_recorded=1' \
  'rpm_payload_matches_expected_cli_surfaces=1' \
  'unexpected_runtime_surface_absent=1' \
  'cli_status_output_recorded=1' \
  'cli_version_output_recorded=1' \
  'cli_report_output_recorded=1' \
  'cli_invalid_command_exit_recorded=1' \
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
  'fedora_vm_cli_payload_repeatability_lane: ok'
do
  require_contains "$marker" "$TRANSCRIPT"
done

require_field_pattern source_tree_revision '^[0-9A-Fa-f]{40,64}$' 'source tree revision'
require_field_value fedora_kernel_version
require_field_pattern spec_checksum '^[0-9A-Fa-f]{64}$' 'spec checksum'
require_field_pattern source_archive_checksum '^[0-9A-Fa-f]{64}$' 'source archive checksum'
require_field_pattern rpm_nevra '^latticra-0\.0\.0-.+[.][^.]+$' 'RPM NEVRA'

cat <<REPORT
FEDORA VM CLI PAYLOAD REPEATABILITY TRANSCRIPT REVIEW
review_status=ok
fedora_vm_cli_payload_repeatability_transcript_review_validator_present=1
repeatability_transcript_review_mode=no-effect-validation
repeatability_transcript_candidate_valid=1
repeatability_transcript_placeholder_values_absent=1
repeatability_transcript_required_markers_present=1
repeatability_transcript_value_fields_validated=1
repeatability_transcript_reviewed=1
repeatability_transcript_accepted=0
evidence_status_written=0
promotion_allowed_by_validator_alone=0
second_disposable_vm_cli_validation_completed=0
cli_payload_repeatability_evidence_present=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
REPORT
