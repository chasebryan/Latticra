#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  fedora-vm-cli-payload-repeatability-publication-review-template.sh

Emits a no-effect Fedora VM CLI payload repeatability publication review
template. It validates local records and prints the required future operator
review fields. It does not run the repeatability runner, validate a live
transcript, attach a transcript, write evidence status, approve publication,
publish evidence, build an RPM, install an RPM, remove an RPM, or mutate the
host.
USAGE
}

fail() {
  printf 'fedora vm cli payload repeatability publication review template: %s\n' "$1" >&2
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

require_file docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_PUBLICATION_GATE.md
require_file docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_PUBLICATION_GATE_STATUS.md
require_file docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_REVIEW_VALIDATOR.md
require_file scripts/fedora-vm-cli-payload-repeatability-evidence-status-review.sh

require_contains 'fedora_vm_cli_payload_repeatability_evidence_publication_gate_present=1' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_PUBLICATION_GATE.md
require_contains 'operator_publication_review_completed=0' docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_PUBLICATION_GATE_STATUS.md
require_contains 'promotion_allowed_by_status_validator_alone=0' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_REVIEW_VALIDATOR.md
require_contains 'evidence_status_written_by_validator=0' scripts/fedora-vm-cli-payload-repeatability-evidence-status-review.sh

cat <<'REPORT'
FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION REVIEW TEMPLATE

template_status=ok
fedora_vm_cli_payload_repeatability_publication_review_template_present=1
publication_review_template_mode=no-effect-template
publication_review_template_decision=blocked-template-only-no-operator-approval
publication_review_template_complete=0
repeatability_runner_executed=0
transcript_attached_by_template=0
evidence_status_written_by_template=0
publication_approved_by_template=0
repeatability_evidence_published_by_template=0
host_mutation_performed=0
repeatability_evidence_publication_requested=0
operator_publication_review_completed=0
repeatability_evidence_publication_approved=0
repeatability_evidence_status_published=0
repeatability_transcript_accepted=0
evidence_status_written=0
second_disposable_vm_cli_validation_completed=0
cli_payload_repeatability_evidence_present=0

[future_required_inputs]
repeatability_transcript_attached=1
repeatability_transcript_reviewed=1
repeatability_transcript_accepted=1
repeatability_evidence_status_candidate_valid=1
repeatability_evidence_status_reviewed=1
candidate_repeatability_transcript_accepted=1
candidate_cli_payload_repeatability_evidence_present=1
candidate_evidence_status_written=1

[future_publication_review_record]
FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION REVIEW
publication_review_status=<required-after-operator-review>
publication_review_date=<required-after-operator-review>
operator_reviewer=<required-after-operator-review>
transcript_review_output_attached=1
evidence_status_review_output_attached=1
transcript_checksum_matches_status=1
source_revision_matches_status=1
status_candidate_validator_passed=1
publication_gate_reviewed=1
non_claims_reviewed=1
operator_publication_review_completed=1
repeatability_evidence_publication_approved=1
published_status_path=<required-after-status-write>
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
