#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  fedora-vm-cli-payload-repeatability-publication-receipt.sh --receipt <path>

Validates a supplied Fedora VM CLI payload repeatability publication receipt
candidate. It reads the provided file, rejects missing required markers and
placeholder values, and prints a no-effect validation report. It does not run
the repeatability runner, validate a live transcript, write evidence status,
approve publication, publish repeatability evidence, write or accept a receipt,
build an RPM, install an RPM, remove an RPM, or mutate the host.
USAGE
}

fail() {
  printf 'fedora vm cli payload repeatability publication receipt: %s\n' "$1" >&2
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
  awk -v field="$field" 'index($0, field "=") == 1 { sub(field "=", ""); print; exit }' "$RECEIPT_CANDIDATE"
}

require_field_value() {
  field="$1"
  value="$(field_value "$field")"
  [ -n "$value" ] || fail "missing required field value: $field"
  case "$value" in
    *'<required-after-status-publication>'*|*'<required-after-operator-review>'*|*'<required'*|'<placeholder>'|'')
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

RECEIPT_CANDIDATE=''

while [ "$#" -gt 0 ]; do
  case "$1" in
    --receipt)
      [ "$#" -ge 2 ] || fail "missing value for --receipt" 64
      RECEIPT_CANDIDATE="$2"
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

[ -n "$RECEIPT_CANDIDATE" ] || fail 'missing --receipt path' 64
require_file "$RECEIPT_CANDIDATE"
require_file docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_TEMPLATE.md
require_file docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_VALIDATOR.md
require_file scripts/fedora-vm-cli-payload-repeatability-publication-receipt-template.sh
require_file scripts/fedora-vm-cli-payload-repeatability-publication-review.sh

require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_TEMPLATE.md
require_contains 'publication_receipt_written=1' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_TEMPLATE.md
require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION REVIEW VALIDATION' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_VALIDATOR.md
require_contains 'publication_receipt_template_complete=0' scripts/fedora-vm-cli-payload-repeatability-publication-receipt-template.sh
require_contains 'publication_review_approved_by_validator=0' scripts/fedora-vm-cli-payload-repeatability-publication-review.sh

for marker in \
  'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT' \
  'publication_receipt_status=published' \
  'publication_review_validation_status=ok' \
  'publication_review_candidate_valid=1' \
  'publication_review_reviewed=1' \
  'publication_review_approved_by_validator=0' \
  'operator_publication_review_completed=1' \
  'repeatability_evidence_publication_approved=1' \
  'repeatability_evidence_status_published=1' \
  'evidence_status_written=1' \
  'publication_receipt_written=1' \
  'publication_receipt_attached=1' \
  'cli_payload_repeatability_evidence_present=1' \
  'host_install_ready_for_cli_payload=1' \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0'
do
  require_contains "$marker" "$RECEIPT_CANDIDATE"
done

require_field_pattern publication_receipt_date '^[0-9]{4}-[0-9]{2}-[0-9]{2}$' 'publication receipt date'
require_field_pattern published_status_path '^docs/status/.+[.]md$' 'published status path'
require_field_pattern published_status_checksum '^[0-9A-Fa-f]{64}$' 'published status checksum'
require_field_pattern publication_review_path '^docs/.+[.]md$' 'publication review path'
require_field_pattern publication_review_checksum '^[0-9A-Fa-f]{64}$' 'publication review checksum'
require_field_value publication_receipt_status

cat <<'REPORT'
FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT VALIDATION
receipt_validation_status=ok
fedora_vm_cli_payload_repeatability_publication_receipt_validator_present=1
publication_receipt_validation_mode=no-effect-validation
publication_receipt_candidate_valid=1
publication_receipt_placeholder_values_absent=1
publication_receipt_required_markers_present=1
publication_receipt_value_fields_validated=1
publication_receipt_reviewed=1
candidate_publication_review_validated=1
candidate_repeatability_evidence_status_published=1
candidate_publication_receipt_written=1
publication_receipt_accepted_by_validator=0
publication_receipt_written_by_validator=0
repeatability_evidence_published_by_validator=0
promotion_allowed_by_publication_receipt_validator_alone=0
host_mutation_performed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
REPORT
