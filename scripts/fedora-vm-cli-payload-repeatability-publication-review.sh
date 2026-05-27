#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  fedora-vm-cli-payload-repeatability-publication-review.sh --review <path>

Validates a supplied Fedora VM CLI payload repeatability publication review
candidate. It reads the provided file, rejects missing required markers and
placeholder values, and prints a no-effect validation report. It does not run
the repeatability runner, validate a live transcript, write evidence status,
approve publication by itself, publish repeatability evidence, build an RPM,
install an RPM, remove an RPM, or mutate the host.
USAGE
}

fail() {
  printf 'fedora vm cli payload repeatability publication review: %s\n' "$1" >&2
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
  awk -v field="$field" 'index($0, field "=") == 1 { sub(field "=", ""); print; exit }' "$REVIEW_CANDIDATE"
}

require_field_value() {
  field="$1"
  value="$(field_value "$field")"
  [ -n "$value" ] || fail "missing required field value: $field"
  case "$value" in
    *'<required-after-operator-review>'*|*'<required-after-status-write>'*|*'<required'*|'<placeholder>'|'')
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

REVIEW_CANDIDATE=''

while [ "$#" -gt 0 ]; do
  case "$1" in
    --review)
      [ "$#" -ge 2 ] || fail "missing value for --review" 64
      REVIEW_CANDIDATE="$2"
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

[ -n "$REVIEW_CANDIDATE" ] || fail 'missing --review path' 64
require_file "$REVIEW_CANDIDATE"
require_file docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_TEMPLATE.md
require_file docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_PUBLICATION_GATE.md
require_file docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_REVIEW_VALIDATOR.md
require_file scripts/fedora-vm-cli-payload-repeatability-publication-review-template.sh
require_file scripts/fedora-vm-cli-payload-repeatability-evidence-status-review.sh

require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION REVIEW' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_TEMPLATE.md
require_contains 'operator_publication_review_completed=1' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_TEMPLATE.md
require_contains 'publication gate is present but does not publish repeatability evidence' docs/status/README.md
require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY EVIDENCE STATUS REVIEW' scripts/fedora-vm-cli-payload-repeatability-evidence-status-review.sh

for marker in \
  'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION REVIEW' \
  'publication_review_status=approved-for-publication' \
  'transcript_review_output_attached=1' \
  'evidence_status_review_output_attached=1' \
  'transcript_checksum_matches_status=1' \
  'source_revision_matches_status=1' \
  'status_candidate_validator_passed=1' \
  'publication_gate_reviewed=1' \
  'non_claims_reviewed=1' \
  'operator_publication_review_completed=1' \
  'repeatability_evidence_publication_approved=1' \
  'repeatability_evidence_status_published=1' \
  'evidence_status_written=1' \
  'cli_payload_repeatability_evidence_present=1' \
  'host_install_ready_for_cli_payload=1' \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0'
do
  require_contains "$marker" "$REVIEW_CANDIDATE"
done

require_field_pattern publication_review_date '^[0-9]{4}-[0-9]{2}-[0-9]{2}$' 'publication review date'
require_field_value operator_reviewer
require_field_pattern published_status_path '^docs/status/.+[.]md$' 'published status path'

cat <<'REPORT'
FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION REVIEW VALIDATION
review_validation_status=ok
fedora_vm_cli_payload_repeatability_publication_review_validator_present=1
publication_review_validation_mode=no-effect-validation
publication_review_candidate_valid=1
publication_review_placeholder_values_absent=1
publication_review_required_markers_present=1
publication_review_value_fields_validated=1
publication_review_reviewed=1
candidate_operator_publication_review_completed=1
candidate_repeatability_evidence_publication_approved=1
candidate_repeatability_evidence_status_published=1
publication_review_approved_by_validator=0
evidence_status_written_by_validator=0
repeatability_evidence_published_by_validator=0
promotion_allowed_by_publication_review_validator_alone=0
host_mutation_performed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
REPORT
