#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  fedora-vm-cli-payload-repeatability-publication-receipt-acceptance-template.sh

Emits a no-effect Fedora VM CLI payload repeatability publication receipt
acceptance template. It validates local records and prints the required future
accepted receipt fields. It does not run the repeatability runner, validate a
live transcript, validate a receipt candidate, write evidence status, approve
publication, publish evidence, write or accept a receipt, build an RPM, install
an RPM, remove an RPM, or mutate the host.
USAGE
}

fail() {
  printf 'fedora vm cli payload repeatability publication receipt acceptance template: %s\n' "$1" >&2
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

require_file docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_CONTRACT.md
require_file docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_CONTRACT_STATUS.md
require_file docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_VALIDATOR.md
require_file scripts/fedora-vm-cli-payload-repeatability-publication-receipt.sh

require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT ACCEPTANCE' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_CONTRACT.md
require_contains 'publication_receipt_accepted=1' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_CONTRACT.md
require_contains 'The receipt acceptance contract alone cannot accept a receipt.' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_CONTRACT.md
require_contains 'publication_receipt_accepted=0' docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_CONTRACT_STATUS.md
require_contains 'publication_receipt_accepted_by_validator=0' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_VALIDATOR.md
require_contains 'publication_receipt_accepted_by_validator=0' scripts/fedora-vm-cli-payload-repeatability-publication-receipt.sh

cat <<'REPORT'
FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT ACCEPTANCE TEMPLATE

template_status=ok
fedora_vm_cli_payload_repeatability_publication_receipt_acceptance_template_present=1
publication_receipt_acceptance_template_mode=no-effect-template
publication_receipt_acceptance_template_decision=blocked-template-only-no-receipt-acceptance
publication_receipt_acceptance_template_complete=0
repeatability_runner_executed=0
publication_receipt_validated_by_template=0
evidence_status_written_by_template=0
publication_approved_by_template=0
repeatability_evidence_published_by_template=0
publication_receipt_written_by_template=0
publication_receipt_accepted_by_template=0
host_mutation_performed=0
publication_receipt_candidate_valid=0
publication_receipt_reviewed=0
publication_receipt_accepted_by_validator=0
publication_receipt_accepted=0
operator_publication_review_completed=0
repeatability_evidence_publication_approved=0
repeatability_evidence_status_published=0
publication_receipt_written=0
publication_receipt_attached=0
repeatability_transcript_accepted=0
evidence_status_written=0
second_disposable_vm_cli_validation_completed=0
cli_payload_repeatability_evidence_present=0

[future_required_inputs]
publication_receipt_candidate_valid=1
publication_receipt_placeholder_values_absent=1
publication_receipt_required_markers_present=1
publication_receipt_value_fields_validated=1
publication_receipt_reviewed=1
candidate_publication_review_validated=1
candidate_repeatability_evidence_status_published=1
candidate_publication_receipt_written=1
operator_review_required=1
acceptance_contract_confirmed=1

[future_receipt_acceptance_record]
FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT ACCEPTANCE
publication_receipt_acceptance_status=accepted
publication_receipt_candidate_valid=1
publication_receipt_placeholder_values_absent=1
publication_receipt_required_markers_present=1
publication_receipt_value_fields_validated=1
publication_receipt_reviewed=1
publication_receipt_accepted=1
publication_receipt_written=1
publication_receipt_attached=1
operator_publication_review_completed=1
repeatability_evidence_publication_approved=1
repeatability_evidence_status_published=1
evidence_status_written=1
cli_payload_repeatability_evidence_present=1
host_install_ready_for_cli_payload=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0

[non_claims]
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
security_hardening_claimed=0
update_safety_claimed=0
recovery_safety_claimed=0
os_replacement_ready=0
REPORT
