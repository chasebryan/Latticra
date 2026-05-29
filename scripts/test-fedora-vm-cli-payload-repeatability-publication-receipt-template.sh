#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora vm cli payload repeatability publication receipt template: %s\n' "$1" >&2
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

doc='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_TEMPLATE.md'
status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_TEMPLATE_STATUS.md'
index='docs/status/README.md'
readme='README.md'
script='scripts/fedora-vm-cli-payload-repeatability-publication-receipt-template.sh'
test_script='scripts/test-fedora-vm-cli-payload-repeatability-publication-receipt-template.sh'
review_validator='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_VALIDATOR.md'
review_validator_status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_VALIDATOR_STATUS.md'
review_script='scripts/fedora-vm-cli-payload-repeatability-publication-review.sh'
publication_gate='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_PUBLICATION_GATE.md'
workflow='.github/workflows/fedora-vm-cli-payload-repeatability-publication-receipt-template.yml'

for file in \
  "$doc" \
  "$status" \
  "$index" \
  "$readme" \
  "$script" \
  "$test_script" \
  "$review_validator" \
  "$review_validator_status" \
  "$review_script" \
  "$publication_gate" \
  "$workflow"
do
  require_file "$file"
done

sh -n "$script"
sh -n "$test_script"

require_contains 'Status: no-effect publication receipt template' "$doc"
require_contains 'fedora_vm_cli_payload_repeatability_publication_receipt_template_present=1' "$doc"
require_contains 'publication_receipt_template_mode=no-effect-template' "$doc"
require_contains 'publication_receipt_template_complete=0' "$doc"
require_contains 'publication_receipt_written=0' "$doc"
require_contains 'publication_receipt_attached=0' "$doc"
require_contains 'sh scripts/fedora-vm-cli-payload-repeatability-publication-receipt-template.sh' "$doc"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-publication-receipt-template.sh' "$doc"

require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT TEMPLATE' "$script"
require_contains 'publication_receipt_template_decision=blocked-template-only-no-publication' "$script"
require_contains 'publication_review_validated_by_template=0' "$script"
require_contains 'repeatability_evidence_published_by_template=0' "$script"
require_contains 'publication_receipt_written_by_template=0' "$script"
require_contains '[future_publication_receipt_record]' "$script"
require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT' "$script"
require_absent 'sudo ' "$script"
require_absent 'rpmbuild ' "$script"
require_absent 'rpm -Uvh' "$script"
require_absent 'rpm -e' "$script"
require_absent 'dnf ' "$script"
require_absent 'curl ' "$script"
require_absent 'wget ' "$script"

for current_field in \
  'fedora_vm_cli_payload_repeatability_publication_review_validator_present=1' \
  'fedora_vm_cli_payload_repeatability_publication_receipt_template_present=1' \
  'publication_receipt_template_mode=no-effect-template' \
  'publication_receipt_template_complete=0' \
  'publication_review_candidate_valid=0' \
  'publication_review_reviewed=0' \
  'publication_review_approved_by_validator=0' \
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

for future_field in \
  'publication_receipt_status=<required-after-status-publication>' \
  'publication_receipt_date=<required-after-status-publication>' \
  'published_status_path=<required-after-status-publication>' \
  'published_status_checksum=<required-after-status-publication>' \
  'publication_review_path=<required-after-operator-review>' \
  'publication_review_checksum=<required-after-operator-review>' \
  'publication_review_validation_status=ok' \
  'publication_review_candidate_valid=1' \
  'publication_review_reviewed=1' \
  'operator_publication_review_completed=1' \
  'repeatability_evidence_publication_approved=1' \
  'publication_receipt_written=1' \
  'publication_receipt_attached=1'
do
  require_contains "$future_field" "$doc"
  require_contains "$future_field" "$script"
done

require_contains 'Status: template/status alignment' "$status"
require_contains 'Date: 2026-05-27' "$status"
require_contains 'without writing a receipt or publishing evidence' "$status"
require_contains 'Run manual disposable Fedora VM CLI payload repeatability lane, validate transcript and evidence status candidates, validate the publication review candidate, then fill the publication receipt template' "$status"

require_contains 'FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_TEMPLATE_STATUS.md' "$index"
require_contains 'Current Fedora VM CLI payload repeatability publication receipt template checkpoint' "$index"
require_contains 'publication receipt template is present but does not write a receipt or publish repeatability evidence' "$index"

require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_TEMPLATE.md' "$readme"
require_contains 'docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_TEMPLATE_STATUS.md' "$readme"
require_contains 'The repeatability publication receipt template is present' "$readme"
require_contains 'does not write a receipt or publish evidence' "$readme"

require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION REVIEW VALIDATION' "$review_validator"
require_contains 'publication_review_candidate_valid=0' "$review_validator_status"
require_contains 'publication_review_approved_by_validator=0' "$review_script"
require_contains 'operator_publication_review_completed=1' "$publication_gate"

require_contains 'name: Fedora VM CLI Payload Repeatability Publication Receipt Template' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-publication-receipt-template.sh' "$workflow"
require_absent 'sh scripts/run-fedora-vm-cli-payload-repeatability-lane.sh' "$workflow"
require_absent 'sh scripts/fedora-vm-cli-payload-repeatability-publication-receipt-template.sh' "$workflow"

require_contains 'sh ./scripts/test-fedora-vm-cli-payload-repeatability-publication-receipt-template.sh' 'Makefile'
require_contains 'fedora-vm-cli-payload-repeatability-publication-receipt-template:' 'Makefile'

output=$(sh "$script")
require_output_contains "$output" 'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT TEMPLATE'
require_output_contains "$output" 'fedora_vm_cli_payload_repeatability_publication_receipt_template_present=1'
require_output_contains "$output" 'publication_receipt_template_mode=no-effect-template'
require_output_contains "$output" 'publication_receipt_template_decision=blocked-template-only-no-publication'
require_output_contains "$output" 'publication_receipt_template_complete=0'
require_output_contains "$output" 'publication_review_validated_by_template=0'
require_output_contains "$output" 'repeatability_evidence_published_by_template=0'
require_output_contains "$output" 'publication_receipt_written_by_template=0'
require_output_contains "$output" '[future_publication_receipt_record]'
require_output_contains "$output" 'publication_receipt_written=1'
require_output_contains "$output" 'publication_receipt_attached=1'

printf 'fedora_vm_cli_payload_repeatability_publication_receipt_template: ok\n'
