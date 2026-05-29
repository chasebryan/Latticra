#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora vm cli payload repeatability publication receipt acceptance contract: %s\n' "$1" >&2
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

doc='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_CONTRACT.md'
status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_CONTRACT_STATUS.md'
index='docs/status/README.md'
readme='README.md'
receipt_validator='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_VALIDATOR.md'
receipt_validator_status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_VALIDATOR_STATUS.md'
receipt_script='scripts/fedora-vm-cli-payload-repeatability-publication-receipt.sh'
receipt_template='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_TEMPLATE.md'
receipt_template_script='scripts/fedora-vm-cli-payload-repeatability-publication-receipt-template.sh'
review_validator='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_VALIDATOR.md'
test_script='scripts/test-fedora-vm-cli-payload-repeatability-publication-receipt-acceptance-contract.sh'
workflow='.github/workflows/fedora-vm-cli-payload-repeatability-publication-receipt-acceptance-contract.yml'

for file in \
  "$doc" \
  "$status" \
  "$index" \
  "$readme" \
  "$receipt_validator" \
  "$receipt_validator_status" \
  "$receipt_script" \
  "$receipt_template" \
  "$receipt_template_script" \
  "$review_validator" \
  "$test_script" \
  "$workflow"
do
  require_file "$file"
done

sh -n "$test_script"

require_contains 'Status: receipt acceptance contract' "$doc"
require_contains 'Evidence level: 9 repeatability target, contract only' "$doc"
require_contains 'future acceptance rule for a validated Fedora VM CLI payload repeatability publication receipt' "$doc"
require_contains 'It does not run the repeatability runner.' "$doc"
require_contains 'It does not validate a live transcript.' "$doc"
require_contains 'It does not validate a publication receipt candidate.' "$doc"
require_contains 'It does not write an evidence status record.' "$doc"
require_contains 'It does not approve publication.' "$doc"
require_contains 'It does not publish repeatability evidence.' "$doc"
require_contains 'It does not write or accept a receipt by itself.' "$doc"
require_contains 'It does not mutate a host.' "$doc"

for dependency in \
  'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_TEMPLATE.md' \
  'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_VALIDATOR.md' \
  'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_VALIDATOR.md' \
  'scripts/fedora-vm-cli-payload-repeatability-publication-receipt.sh' \
  'scripts/fedora-vm-cli-payload-repeatability-publication-receipt-template.sh' \
  'README.md'
do
  require_contains "$dependency" "$doc"
done

for prerequisite in \
  'publication_receipt_candidate_valid=1' \
  'publication_receipt_placeholder_values_absent=1' \
  'publication_receipt_required_markers_present=1' \
  'publication_receipt_value_fields_validated=1' \
  'publication_receipt_reviewed=1' \
  'candidate_publication_review_validated=1' \
  'candidate_repeatability_evidence_status_published=1' \
  'candidate_publication_receipt_written=1' \
  'publication_receipt_accepted=1'
do
  require_contains "$prerequisite" "$doc"
done

for accepted_field in \
  'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT ACCEPTANCE' \
  'publication_receipt_acceptance_status=accepted' \
  'publication_receipt_candidate_valid=1' \
  'publication_receipt_placeholder_values_absent=1' \
  'publication_receipt_required_markers_present=1' \
  'publication_receipt_value_fields_validated=1' \
  'publication_receipt_reviewed=1' \
  'publication_receipt_accepted=1' \
  'publication_receipt_written=1' \
  'publication_receipt_attached=1' \
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
  require_contains "$accepted_field" "$doc"
done

for current_field in \
  'fedora_vm_cli_payload_repeatability_publication_receipt_validator_present=1' \
  'fedora_vm_cli_payload_repeatability_publication_receipt_acceptance_contract_present=1' \
  'publication_receipt_candidate_valid=0' \
  'publication_receipt_reviewed=0' \
  'publication_receipt_accepted_by_validator=0' \
  'publication_receipt_accepted=0' \
  'publication_receipt_written_by_validator=0' \
  'publication_receipt_written=0' \
  'publication_receipt_attached=0' \
  'repeatability_evidence_published_by_validator=0' \
  'promotion_allowed_by_publication_receipt_validator_alone=0' \
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

require_contains 'The receipt acceptance contract alone cannot accept a receipt.' "$doc"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-publication-receipt-acceptance-contract.sh' "$doc"
require_contains 'fedora_vm_cli_payload_repeatability_publication_receipt_acceptance_contract: ok' "$doc"
require_contains 'Run manual disposable Fedora VM CLI payload repeatability lane, validate transcript and evidence status candidates, validate publication review and receipt candidates, then perform operator receipt acceptance review' "$doc"
require_contains 'not repeatability evidence' "$doc"
require_contains 'not host mutation' "$doc"
require_contains 'not production readiness' "$doc"
require_contains 'not Fedora approval' "$doc"

require_contains 'Status: receipt acceptance contract/status alignment' "$status"
require_contains 'Date: 2026-05-27' "$status"
require_contains 'does not write or accept a receipt' "$status"
require_contains 'does not publish repeatability evidence' "$status"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-publication-receipt-acceptance-contract.sh' "$status"

require_contains 'FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_CONTRACT_STATUS.md' "$index"
require_contains 'Current Fedora VM CLI payload repeatability publication receipt acceptance contract checkpoint' "$index"
require_contains 'receipt acceptance contract is present but does not accept a receipt or publish repeatability evidence' "$index"

require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_CONTRACT.md' "$readme"
require_contains 'docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_CONTRACT_STATUS.md' "$readme"
require_contains 'fedora_vm_cli_payload_repeatability_publication_receipt_acceptance_contract_present=1' "$readme"
require_contains 'The repeatability publication receipt acceptance contract is present' "$readme"
require_contains 'does not accept a receipt or publish evidence' "$readme"

require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT VALIDATION' "$receipt_validator"
require_contains 'publication_receipt_candidate_valid=0' "$receipt_validator_status"
require_contains 'publication_receipt_accepted_by_validator=0' "$receipt_script"
require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT' "$receipt_template"
require_contains 'publication_receipt_template_complete=0' "$receipt_template_script"
require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION REVIEW VALIDATION' "$review_validator"

require_contains 'name: Fedora VM CLI Payload Repeatability Publication Receipt Acceptance Contract' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-publication-receipt-acceptance-contract.sh' "$workflow"
require_absent 'sh scripts/run-fedora-vm-cli-payload-repeatability-lane.sh' "$workflow"
require_absent 'sh scripts/fedora-vm-cli-payload-repeatability-publication-receipt.sh' "$workflow"

require_contains 'sh ./scripts/test-fedora-vm-cli-payload-repeatability-publication-receipt-acceptance-contract.sh' 'Makefile'
require_contains 'fedora-vm-cli-payload-repeatability-publication-receipt-acceptance-contract:' 'Makefile'

printf 'fedora_vm_cli_payload_repeatability_publication_receipt_acceptance_contract: ok\n'
