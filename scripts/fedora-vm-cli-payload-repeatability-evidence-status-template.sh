#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  fedora-vm-cli-payload-repeatability-evidence-status-template.sh

Emits a no-effect Fedora VM CLI payload repeatability evidence status template.
It validates local records and prints the required future evidence status fields.
It does not run the repeatability runner, validate a live transcript, attach a
transcript, write an evidence status record, build an RPM, install an RPM,
remove an RPM, or mutate the host.
USAGE
}

fail() {
  printf 'fedora vm cli payload repeatability evidence status template: %s\n' "$1" >&2
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

require_file docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_ACCEPTANCE_CONTRACT.md
require_file docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_ACCEPTANCE_CONTRACT_STATUS.md
require_file docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_REVIEW_GATE.md
require_file docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_REVIEW_VALIDATOR.md
require_file scripts/fedora-vm-cli-payload-repeatability-transcript-review.sh
require_file scripts/run-fedora-vm-cli-payload-repeatability-lane.sh

require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY EVIDENCE STATUS' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_ACCEPTANCE_CONTRACT.md
require_contains 'repeatability_transcript_accepted=1' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_ACCEPTANCE_CONTRACT.md
require_contains 'The acceptance contract alone cannot promote evidence.' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_ACCEPTANCE_CONTRACT.md
require_contains 'repeatability_transcript_accepted=0' docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_ACCEPTANCE_CONTRACT_STATUS.md
require_contains 'repeatability_transcript_accepted=0' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_REVIEW_GATE.md
require_contains 'repeatability_transcript_accepted=0' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_REVIEW_VALIDATOR.md
require_contains 'evidence_status_written=0' scripts/fedora-vm-cli-payload-repeatability-transcript-review.sh
require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY LANE' scripts/run-fedora-vm-cli-payload-repeatability-lane.sh

cat <<'REPORT'
FEDORA VM CLI PAYLOAD REPEATABILITY EVIDENCE STATUS TEMPLATE

template_status=ok
fedora_vm_cli_payload_repeatability_evidence_status_template_present=1
repeatability_evidence_status_template_mode=no-effect-template
repeatability_evidence_status_template_decision=blocked-template-only-no-status-write
repeatability_evidence_status_template_complete=0
repeatability_runner_executed=0
rpm_build_performed=0
rpm_install_performed=0
rpm_removal_performed=0
host_mutation_performed=0
repeatability_transcript_attached=0
repeatability_transcript_reviewed=0
repeatability_transcript_candidate_valid=0
repeatability_transcript_accepted=0
evidence_status_written=0
second_disposable_vm_cli_validation_completed=0
cli_payload_repeatability_evidence_present=0

[required_prior_review]
repeatability_transcript_attached=1
repeatability_transcript_reviewed=1
repeatability_transcript_candidate_valid=1
repeatability_transcript_placeholder_values_absent=1
repeatability_transcript_required_markers_present=1
repeatability_transcript_value_fields_validated=1
operator_review_required=1
acceptance_contract_confirmed=1

[future_evidence_status_record]
FEDORA VM CLI PAYLOAD REPEATABILITY EVIDENCE STATUS
Status: evidence status alignment
Date: <required-from-accepted-review-date>
source=operator disposable Fedora VM repeatability transcript
transcript_kind=disposable-vm-cli-payload-repeatability
transcript_path=<required-from-operator-attachment>
transcript_checksum=<required-from-accepted-review>
repeatability_transcript_reviewed=1
repeatability_transcript_accepted=1
repeatability_transcript_candidate_valid=1
repeatability_transcript_placeholder_values_absent=1
repeatability_transcript_required_markers_present=1
repeatability_transcript_value_fields_validated=1
source_tree_revision_recorded=1
source_tree_revision=<required-from-real-run>
fedora_os_release_recorded=1
fedora_os_release=<required-from-real-run>
fedora_kernel_version_recorded=1
fedora_kernel_version=<required-from-real-run>
spec_checksum_recorded=1
spec_checksum=<required-from-real-run>
source_archive_checksum_recorded=1
source_archive_checksum=<required-from-real-run>
rpm_nevra_recorded=1
rpm_nevra=<required-from-real-run>
rpm_payload_matches_expected_cli_surfaces=1
validated_cli_mode_still_no_effect=1
validated_runtime_behavior_still_disabled=1
validated_non_claims_preserved=1
rpm_verify_completed=1
removal_validation_performed=1
post_removal_absence_verified=1
second_disposable_vm_cli_validation_completed=1
cli_payload_repeatability_evidence_present=1
host_install_ready_for_cli_payload=1
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
evidence_level=9
evidence_status_written=1

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
