#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  fedora-vm-cli-payload-repeatability-publication-receipt-acceptance-promotion-gate.sh --acceptance-validation <path>

Checks a supplied Fedora VM CLI payload repeatability publication receipt
acceptance validation report and emits a no-effect promotion gate report. It
does not run the repeatability runner, validate a live transcript, validate a
receipt candidate, write evidence status, approve publication, publish
repeatability evidence, write or accept a receipt, build an RPM, install an
RPM, remove an RPM, promote production readiness, or mutate the host.
USAGE
}

fail() {
  printf 'fedora vm cli payload repeatability publication receipt acceptance promotion gate: %s\n' "$1" >&2
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

require_absent() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    fail "unexpected pattern in $file: $pattern"
  fi
}

reject_placeholders() {
  file="$1"
  if grep -Eq -- '<required|<placeholder>|TODO|TBD' "$file"; then
    fail "placeholder value is not acceptable in acceptance validation report"
  fi
}

ACCEPTANCE_VALIDATION_REPORT=''

while [ "$#" -gt 0 ]; do
  case "$1" in
    --acceptance-validation)
      [ "$#" -ge 2 ] || fail "missing value for --acceptance-validation" 64
      ACCEPTANCE_VALIDATION_REPORT="$2"
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

[ -n "$ACCEPTANCE_VALIDATION_REPORT" ] || fail 'missing --acceptance-validation path' 64
require_file "$ACCEPTANCE_VALIDATION_REPORT"
require_file docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_VALIDATOR.md
require_file docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_VALIDATOR_STATUS.md
require_file scripts/fedora-vm-cli-payload-repeatability-publication-receipt-acceptance.sh
require_file docs/FEDORA_READINESS_PLAN.md

require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT ACCEPTANCE VALIDATION' docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_VALIDATOR.md
require_contains 'promotion_allowed_by_publication_receipt_acceptance_validator_alone=0' docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_VALIDATOR_STATUS.md
require_contains 'promotion_allowed_by_publication_receipt_acceptance_validator_alone=0' scripts/fedora-vm-cli-payload-repeatability-publication-receipt-acceptance.sh
require_contains 'not a production operating system' docs/FEDORA_READINESS_PLAN.md

for marker in \
  'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT ACCEPTANCE VALIDATION' \
  'acceptance_validation_status=ok' \
  'fedora_vm_cli_payload_repeatability_publication_receipt_acceptance_validator_present=1' \
  'publication_receipt_acceptance_validation_mode=no-effect-validation' \
  'publication_receipt_acceptance_candidate_valid=1' \
  'publication_receipt_acceptance_placeholder_values_absent=1' \
  'publication_receipt_acceptance_required_markers_present=1' \
  'publication_receipt_acceptance_value_fields_validated=1' \
  'publication_receipt_acceptance_reviewed=1' \
  'candidate_publication_receipt_accepted=1' \
  'candidate_publication_receipt_written=1' \
  'candidate_publication_receipt_attached=1' \
  'candidate_repeatability_evidence_status_published=1' \
  'publication_receipt_accepted_by_acceptance_validator=0' \
  'publication_receipt_written_by_acceptance_validator=0' \
  'repeatability_evidence_published_by_acceptance_validator=0' \
  'promotion_allowed_by_publication_receipt_acceptance_validator_alone=0' \
  'host_mutation_performed=0' \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0'
do
  require_contains "$marker" "$ACCEPTANCE_VALIDATION_REPORT"
done

reject_placeholders "$ACCEPTANCE_VALIDATION_REPORT"

for forbidden_claim in \
  'production_installer_ready=1' \
  'fedora_distribution_ready=1' \
  'fedora_approval_claimed=1' \
  'daily_driver_install_ready=1' \
  'immutable_fedora_ready=1' \
  'host_mutation_performed=1' \
  'promotion_allowed_by_publication_receipt_acceptance_validator_alone=1'
do
  require_absent "$forbidden_claim" "$ACCEPTANCE_VALIDATION_REPORT"
done

cat <<'REPORT'
FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT ACCEPTANCE PROMOTION GATE
promotion_gate_status=blocked
fedora_vm_cli_payload_repeatability_publication_receipt_acceptance_promotion_gate_present=1
publication_receipt_acceptance_promotion_gate_mode=no-effect-gate
publication_receipt_acceptance_validation_report_valid=1
publication_receipt_acceptance_candidate_valid=1
publication_receipt_acceptance_reviewed=1
candidate_publication_receipt_accepted=1
candidate_publication_receipt_written=1
candidate_publication_receipt_attached=1
candidate_repeatability_evidence_status_published=1
publication_receipt_accepted_by_promotion_gate=0
publication_receipt_written_by_promotion_gate=0
repeatability_evidence_published_by_promotion_gate=0
promotion_allowed_by_publication_receipt_acceptance_promotion_gate_alone=0
production_installer_promotion_allowed=0
fedora_distribution_promotion_allowed=0
host_mutation_performed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
REPORT
