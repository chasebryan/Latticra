#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora vm cli payload repeatability publication receipt validator: %s\n' "$1" >&2
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

doc='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_VALIDATOR.md'
status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_VALIDATOR_STATUS.md'
index='docs/status/README.md'
readme='README.md'
script='scripts/fedora-vm-cli-payload-repeatability-publication-receipt.sh'
test_script='scripts/test-fedora-vm-cli-payload-repeatability-publication-receipt-validator.sh'
template='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_TEMPLATE.md'
template_status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_TEMPLATE_STATUS.md'
template_script='scripts/fedora-vm-cli-payload-repeatability-publication-receipt-template.sh'
review_validator='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_VALIDATOR.md'
review_script='scripts/fedora-vm-cli-payload-repeatability-publication-review.sh'
workflow='.github/workflows/fedora-vm-cli-payload-repeatability-publication-receipt-validator.yml'

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
  "$review_validator" \
  "$review_script" \
  "$workflow"
do
  require_file "$file"
done

sh -n "$script"
sh -n "$test_script"

require_contains 'Status: no-effect publication receipt validator' "$doc"
require_contains 'fedora_vm_cli_payload_repeatability_publication_receipt_validator_present=1' "$doc"
require_contains 'publication_receipt_validation_mode=no-effect-validation' "$doc"
require_contains 'publication_receipt_candidate_valid=0' "$doc"
require_contains 'publication_receipt_accepted_by_validator=0' "$doc"
require_contains 'publication_receipt_written_by_validator=0' "$doc"
require_contains 'repeatability_evidence_published_by_validator=0' "$doc"
require_contains 'promotion_allowed_by_publication_receipt_validator_alone=0' "$doc"
require_contains 'sh scripts/fedora-vm-cli-payload-repeatability-publication-receipt.sh --receipt <path>' "$doc"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-publication-receipt-validator.sh' "$doc"

require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT VALIDATION' "$script"
require_contains 'publication_receipt_candidate_valid=1' "$script"
require_contains 'publication_receipt_placeholder_values_absent=1' "$script"
require_contains 'publication_receipt_required_markers_present=1' "$script"
require_contains 'publication_receipt_value_fields_validated=1' "$script"
require_contains 'publication_receipt_accepted_by_validator=0' "$script"
require_contains 'publication_receipt_written_by_validator=0' "$script"
require_contains 'repeatability_evidence_published_by_validator=0' "$script"
require_contains 'promotion_allowed_by_publication_receipt_validator_alone=0' "$script"
require_contains 'placeholder value is not acceptable' "$script"
require_absent 'sudo ' "$script"
require_absent 'rpmbuild ' "$script"
require_absent 'rpm -Uvh' "$script"
require_absent 'rpm -e' "$script"
require_absent 'dnf ' "$script"
require_absent 'curl ' "$script"
require_absent 'wget ' "$script"

for current_field in \
  'fedora_vm_cli_payload_repeatability_publication_receipt_template_present=1' \
  'fedora_vm_cli_payload_repeatability_publication_receipt_validator_present=1' \
  'publication_receipt_validation_mode=no-effect-validation' \
  'publication_receipt_candidate_valid=0' \
  'publication_receipt_reviewed=0' \
  'publication_receipt_accepted_by_validator=0' \
  'publication_receipt_written_by_validator=0' \
  'repeatability_evidence_published_by_validator=0' \
  'promotion_allowed_by_publication_receipt_validator_alone=0' \
  'publication_receipt_written=0' \
  'publication_receipt_attached=0' \
  'operator_publication_review_completed=0' \
  'repeatability_evidence_publication_approved=0' \
  'repeatability_evidence_status_published=0' \
  'repeatability_transcript_accepted=0' \
  'evidence_status_written=0' \
  'second_disposable_vm_cli_validation_completed=0' \
  'cli_payload_repeatability_evidence_present=0' \
  'host_install_ready_for_cli_payload=1' \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0'
do
  require_contains "$current_field" "$doc"
  require_contains "$current_field" "$status"
  require_contains "$current_field" "$index"
  require_contains "$current_field" "$readme"
done

require_contains 'Status: validator/status alignment' "$status"
require_contains 'Date: 2026-05-27' "$status"
require_contains 'does not write or accept a receipt' "$status"
require_contains 'does not publish repeatability evidence' "$status"
require_contains 'Run manual disposable Fedora VM CLI payload repeatability lane, validate transcript and evidence status candidates, validate publication review and receipt candidates, then attach the receipt candidate for operator review' "$status"

require_contains 'FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_VALIDATOR_STATUS.md' "$index"
require_contains 'Current Fedora VM CLI payload repeatability publication receipt validator checkpoint' "$index"
require_contains 'publication receipt validator is present but does not accept a receipt or publish repeatability evidence' "$index"

require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_VALIDATOR.md' "$readme"
require_contains 'docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_VALIDATOR_STATUS.md' "$readme"
require_contains 'The repeatability publication receipt validator is present' "$readme"
require_contains 'does not accept a receipt or publish evidence' "$readme"

require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT' "$template"
require_contains 'fedora_vm_cli_payload_repeatability_publication_receipt_template_present=1' "$template_status"
require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT TEMPLATE' "$template_script"
require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION REVIEW VALIDATION' "$review_validator"
require_contains 'publication_review_approved_by_validator=0' "$review_script"

require_contains 'name: Fedora VM CLI Payload Repeatability Publication Receipt Validator' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-publication-receipt-validator.sh' "$workflow"
require_absent 'sh scripts/run-fedora-vm-cli-payload-repeatability-lane.sh' "$workflow"
require_absent 'sh scripts/fedora-vm-cli-payload-repeatability-publication-receipt.sh' "$workflow"

require_contains 'sh ./scripts/test-fedora-vm-cli-payload-repeatability-publication-receipt-validator.sh' 'Makefile'
require_contains 'fedora-vm-cli-payload-repeatability-publication-receipt-validator:' 'Makefile'

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-fedora-repeatability-publication-receipt.XXXXXX")"
trap 'rm -rf "$tmp"' EXIT INT HUP TERM

valid="$tmp/valid.receipt"
placeholder="$tmp/placeholder.receipt"

cat >"$valid" <<'VALID_RECEIPT'
FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT
publication_receipt_status=published
publication_receipt_date=2026-05-27
published_status_path=docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS.md
published_status_checksum=dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd
publication_review_path=docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW.md
publication_review_checksum=eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee
publication_review_validation_status=ok
publication_review_candidate_valid=1
publication_review_reviewed=1
publication_review_approved_by_validator=0
operator_publication_review_completed=1
repeatability_evidence_publication_approved=1
repeatability_evidence_status_published=1
evidence_status_written=1
publication_receipt_written=1
publication_receipt_attached=1
cli_payload_repeatability_evidence_present=1
host_install_ready_for_cli_payload=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
VALID_RECEIPT

cat >"$placeholder" <<'PLACEHOLDER_RECEIPT'
FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT
publication_receipt_status=published
publication_receipt_date=<required-after-status-publication>
published_status_path=<required-after-status-publication>
published_status_checksum=<required-after-status-publication>
publication_review_path=<required-after-operator-review>
publication_review_checksum=<required-after-operator-review>
publication_review_validation_status=ok
publication_review_candidate_valid=1
publication_review_reviewed=1
publication_review_approved_by_validator=0
operator_publication_review_completed=1
repeatability_evidence_publication_approved=1
repeatability_evidence_status_published=1
evidence_status_written=1
publication_receipt_written=1
publication_receipt_attached=1
cli_payload_repeatability_evidence_present=1
host_install_ready_for_cli_payload=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
PLACEHOLDER_RECEIPT

output=$(sh "$script" --receipt "$valid")
require_output_contains "$output" 'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT VALIDATION'
require_output_contains "$output" 'receipt_validation_status=ok'
require_output_contains "$output" 'publication_receipt_candidate_valid=1'
require_output_contains "$output" 'publication_receipt_placeholder_values_absent=1'
require_output_contains "$output" 'publication_receipt_accepted_by_validator=0'
require_output_contains "$output" 'publication_receipt_written_by_validator=0'
require_output_contains "$output" 'repeatability_evidence_published_by_validator=0'
require_output_contains "$output" 'promotion_allowed_by_publication_receipt_validator_alone=0'
require_output_contains "$output" 'host_mutation_performed=0'

if sh "$script" --receipt "$placeholder" >/dev/null 2>&1; then
  fail 'placeholder publication receipt unexpectedly passed validation'
fi

printf 'fedora_vm_cli_payload_repeatability_publication_receipt_validator: ok\n'
