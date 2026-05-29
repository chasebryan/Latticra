#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  fedora-vm-cli-payload-repeatability-publication-receipt-template.sh

Emits a no-effect Fedora VM CLI payload repeatability publication receipt
template. It validates local records and prints the required future receipt
fields. It does not run the repeatability runner, validate a live transcript,
validate a publication review candidate, write evidence status, approve
publication, publish evidence, write a receipt, build an RPM, install an RPM,
remove an RPM, or mutate the host.
USAGE
}

fail() {
  printf 'fedora vm cli payload repeatability publication receipt template: %s\n' "$1" >&2
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

require_file docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_VALIDATOR.md
require_file docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_VALIDATOR_STATUS.md
require_file scripts/fedora-vm-cli-payload-repeatability-publication-review.sh
require_file docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_PUBLICATION_GATE.md

require_contains 'fedora_vm_cli_payload_repeatability_publication_review_validator_present=1' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_VALIDATOR.md
require_contains 'publication_review_candidate_valid=0' docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_VALIDATOR_STATUS.md
require_contains 'publication_review_approved_by_validator=0' scripts/fedora-vm-cli-payload-repeatability-publication-review.sh
require_contains 'operator_publication_review_completed=1' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_PUBLICATION_GATE.md

cat <<'REPORT'
FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT TEMPLATE

template_status=ok
fedora_vm_cli_payload_repeatability_publication_receipt_template_present=1
publication_receipt_template_mode=no-effect-template
publication_receipt_template_decision=blocked-template-only-no-publication
publication_receipt_template_complete=0
repeatability_runner_executed=0
publication_review_validated_by_template=0
evidence_status_written_by_template=0
publication_approved_by_template=0
repeatability_evidence_published_by_template=0
publication_receipt_written_by_template=0
host_mutation_performed=0
publication_review_candidate_valid=0
publication_review_reviewed=0
publication_review_approved_by_validator=0
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
publication_review_validation_status=ok
publication_review_candidate_valid=1
publication_review_reviewed=1
operator_publication_review_completed=1
repeatability_evidence_publication_approved=1
published_status_path_recorded=1
published_status_checksum_recorded=1

[future_publication_receipt_record]
FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT
publication_receipt_status=<required-after-status-publication>
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
