#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora vm cli payload repeatability publication receipt acceptance promotion gate: %s\n' "$1" >&2
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

doc='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_PROMOTION_GATE.md'
status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_PROMOTION_GATE_STATUS.md'
index='docs/status/README.md'
readme='README.md'
script='scripts/fedora-vm-cli-payload-repeatability-publication-receipt-acceptance-promotion-gate.sh'
test_script='scripts/test-fedora-vm-cli-payload-repeatability-publication-receipt-acceptance-promotion-gate.sh'
validator='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_VALIDATOR.md'
validator_status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_VALIDATOR_STATUS.md'
validator_script='scripts/fedora-vm-cli-payload-repeatability-publication-receipt-acceptance.sh'
readiness='docs/FEDORA_READINESS_PLAN.md'
workflow='.github/workflows/fedora-vm-cli-payload-repeatability-publication-receipt-acceptance-promotion-gate.yml'

for file in \
  "$doc" \
  "$status" \
  "$index" \
  "$readme" \
  "$script" \
  "$test_script" \
  "$validator" \
  "$validator_status" \
  "$validator_script" \
  "$readiness" \
  "$workflow"
do
  require_file "$file"
done

sh -n "$script"
sh -n "$test_script"

require_contains 'Status: no-effect receipt acceptance promotion gate' "$doc"
require_contains 'fedora_vm_cli_payload_repeatability_publication_receipt_acceptance_promotion_gate_present=1' "$doc"
require_contains 'publication_receipt_acceptance_promotion_gate_mode=no-effect-gate' "$doc"
require_contains 'publication_receipt_acceptance_validation_report_valid=0' "$doc"
require_contains 'publication_receipt_acceptance_promotion_requested=0' "$doc"
require_contains 'publication_receipt_accepted_by_promotion_gate=0' "$doc"
require_contains 'publication_receipt_written_by_promotion_gate=0' "$doc"
require_contains 'repeatability_evidence_published_by_promotion_gate=0' "$doc"
require_contains 'promotion_allowed_by_publication_receipt_acceptance_promotion_gate_alone=0' "$doc"
require_contains 'production_installer_promotion_allowed=0' "$doc"
require_contains 'fedora_distribution_promotion_allowed=0' "$doc"
require_contains 'sh scripts/fedora-vm-cli-payload-repeatability-publication-receipt-acceptance-promotion-gate.sh --acceptance-validation <path>' "$doc"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-publication-receipt-acceptance-promotion-gate.sh' "$doc"

require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT ACCEPTANCE PROMOTION GATE' "$script"
require_contains 'promotion_gate_status=blocked' "$script"
require_contains 'publication_receipt_acceptance_validation_report_valid=1' "$script"
require_contains 'publication_receipt_accepted_by_promotion_gate=0' "$script"
require_contains 'publication_receipt_written_by_promotion_gate=0' "$script"
require_contains 'repeatability_evidence_published_by_promotion_gate=0' "$script"
require_contains 'promotion_allowed_by_publication_receipt_acceptance_promotion_gate_alone=0' "$script"
require_contains 'production_installer_promotion_allowed=0' "$script"
require_contains 'fedora_distribution_promotion_allowed=0' "$script"
require_contains 'placeholder value is not acceptable' "$script"
require_absent 'sudo ' "$script"
require_absent 'rpmbuild ' "$script"
require_absent 'rpm -Uvh' "$script"
require_absent 'rpm -e' "$script"
require_absent 'dnf ' "$script"
require_absent 'curl ' "$script"
require_absent 'wget ' "$script"

for current_field in \
  'fedora_vm_cli_payload_repeatability_publication_receipt_acceptance_validator_present=1' \
  'fedora_vm_cli_payload_repeatability_publication_receipt_acceptance_promotion_gate_present=1' \
  'publication_receipt_acceptance_promotion_gate_mode=no-effect-gate' \
  'publication_receipt_acceptance_validation_report_valid=0' \
  'publication_receipt_acceptance_promotion_requested=0' \
  'publication_receipt_accepted_by_promotion_gate=0' \
  'publication_receipt_written_by_promotion_gate=0' \
  'repeatability_evidence_published_by_promotion_gate=0' \
  'promotion_allowed_by_publication_receipt_acceptance_promotion_gate_alone=0' \
  'production_installer_promotion_allowed=0' \
  'fedora_distribution_promotion_allowed=0' \
  'publication_receipt_acceptance_candidate_valid=0' \
  'publication_receipt_acceptance_reviewed=0' \
  'publication_receipt_accepted=0' \
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

for validation_field in \
  'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT ACCEPTANCE VALIDATION' \
  'acceptance_validation_status=ok' \
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
  require_contains "$validation_field" "$doc"
  require_contains "$validation_field" "$script"
done

require_contains 'Status: promotion gate/status alignment' "$status"
require_contains 'Date: 2026-05-27' "$status"
require_contains 'keeps production promotion blocked' "$status"
require_contains 'does not claim production installer readiness or Fedora distribution readiness' "$status"
require_contains 'Use a filled receipt acceptance validation report as one prerequisite input to a broader Fedora production-readiness evidence matrix' "$status"

require_contains 'FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_PROMOTION_GATE_STATUS.md' "$index"
require_contains 'Current Fedora VM CLI payload repeatability publication receipt acceptance promotion gate checkpoint' "$index"
require_contains 'receipt acceptance promotion gate is present but keeps production installer and Fedora distribution promotion blocked' "$index"

require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_PROMOTION_GATE.md' "$readme"
require_contains 'docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_RECEIPT_ACCEPTANCE_PROMOTION_GATE_STATUS.md' "$readme"
require_contains 'The repeatability publication receipt acceptance promotion gate is present' "$readme"
require_contains 'keeps production installer and Fedora distribution promotion blocked' "$readme"

require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT ACCEPTANCE VALIDATION' "$validator"
require_contains 'promotion_allowed_by_publication_receipt_acceptance_validator_alone=0' "$validator_status"
require_contains 'promotion_allowed_by_publication_receipt_acceptance_validator_alone=0' "$validator_script"
require_contains 'not a production operating system' "$readiness"

require_contains 'name: Fedora VM CLI Payload Repeatability Publication Receipt Acceptance Promotion Gate' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-publication-receipt-acceptance-promotion-gate.sh' "$workflow"
require_absent 'sh scripts/run-fedora-vm-cli-payload-repeatability-lane.sh' "$workflow"
require_absent 'sh scripts/fedora-vm-cli-payload-repeatability-publication-receipt-acceptance-promotion-gate.sh --acceptance-validation' "$workflow"

require_contains 'sh ./scripts/test-fedora-vm-cli-payload-repeatability-publication-receipt-acceptance-promotion-gate.sh' 'Makefile'
require_contains 'fedora-vm-cli-payload-repeatability-publication-receipt-acceptance-promotion-gate:' 'Makefile'

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-fedora-repeatability-publication-receipt-acceptance-promotion.XXXXXX")"
trap 'rm -rf "$tmp"' EXIT INT HUP TERM

valid="$tmp/valid.acceptance-validation"
placeholder="$tmp/placeholder.acceptance-validation"

cat >"$valid" <<'VALID_ACCEPTANCE_VALIDATION'
FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT ACCEPTANCE VALIDATION
acceptance_validation_status=ok
fedora_vm_cli_payload_repeatability_publication_receipt_acceptance_validator_present=1
publication_receipt_acceptance_validation_mode=no-effect-validation
publication_receipt_acceptance_candidate_valid=1
publication_receipt_acceptance_placeholder_values_absent=1
publication_receipt_acceptance_required_markers_present=1
publication_receipt_acceptance_value_fields_validated=1
publication_receipt_acceptance_reviewed=1
candidate_publication_receipt_accepted=1
candidate_publication_receipt_written=1
candidate_publication_receipt_attached=1
candidate_repeatability_evidence_status_published=1
publication_receipt_accepted_by_acceptance_validator=0
publication_receipt_written_by_acceptance_validator=0
repeatability_evidence_published_by_acceptance_validator=0
promotion_allowed_by_publication_receipt_acceptance_validator_alone=0
host_mutation_performed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
VALID_ACCEPTANCE_VALIDATION

cat >"$placeholder" <<'PLACEHOLDER_ACCEPTANCE_VALIDATION'
FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT ACCEPTANCE VALIDATION
acceptance_validation_status=ok
fedora_vm_cli_payload_repeatability_publication_receipt_acceptance_validator_present=1
publication_receipt_acceptance_validation_mode=no-effect-validation
publication_receipt_acceptance_candidate_valid=1
publication_receipt_acceptance_placeholder_values_absent=1
publication_receipt_acceptance_required_markers_present=1
publication_receipt_acceptance_value_fields_validated=1
publication_receipt_acceptance_reviewed=1
candidate_publication_receipt_accepted=1
candidate_publication_receipt_written=1
candidate_publication_receipt_attached=1
candidate_repeatability_evidence_status_published=1
publication_receipt_accepted_by_acceptance_validator=0
publication_receipt_written_by_acceptance_validator=0
repeatability_evidence_published_by_acceptance_validator=0
promotion_allowed_by_publication_receipt_acceptance_validator_alone=0
host_mutation_performed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
promotion_review_reference=<required-after-operator-review>
PLACEHOLDER_ACCEPTANCE_VALIDATION

output=$(sh "$script" --acceptance-validation "$valid")
require_output_contains "$output" 'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION RECEIPT ACCEPTANCE PROMOTION GATE'
require_output_contains "$output" 'promotion_gate_status=blocked'
require_output_contains "$output" 'publication_receipt_acceptance_validation_report_valid=1'
require_output_contains "$output" 'publication_receipt_acceptance_candidate_valid=1'
require_output_contains "$output" 'publication_receipt_acceptance_reviewed=1'
require_output_contains "$output" 'candidate_publication_receipt_accepted=1'
require_output_contains "$output" 'publication_receipt_accepted_by_promotion_gate=0'
require_output_contains "$output" 'publication_receipt_written_by_promotion_gate=0'
require_output_contains "$output" 'repeatability_evidence_published_by_promotion_gate=0'
require_output_contains "$output" 'promotion_allowed_by_publication_receipt_acceptance_promotion_gate_alone=0'
require_output_contains "$output" 'production_installer_promotion_allowed=0'
require_output_contains "$output" 'fedora_distribution_promotion_allowed=0'
require_output_contains "$output" 'host_mutation_performed=0'

if sh "$script" --acceptance-validation "$placeholder" >/dev/null 2>&1; then
  fail 'placeholder acceptance validation report unexpectedly passed promotion gate'
fi

printf 'fedora_vm_cli_payload_repeatability_publication_receipt_acceptance_promotion_gate: ok\n'
