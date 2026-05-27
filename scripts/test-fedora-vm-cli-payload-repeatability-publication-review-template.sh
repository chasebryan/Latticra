#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora vm cli payload repeatability publication review template: %s\n' "$1" >&2
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

doc='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_TEMPLATE.md'
status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_TEMPLATE_STATUS.md'
index='docs/status/README.md'
readme='README.md'
script='scripts/fedora-vm-cli-payload-repeatability-publication-review-template.sh'
test_script='scripts/test-fedora-vm-cli-payload-repeatability-publication-review-template.sh'
publication_gate='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_PUBLICATION_GATE.md'
publication_gate_status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_PUBLICATION_GATE_STATUS.md'
status_validator='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_REVIEW_VALIDATOR.md'
status_review='scripts/fedora-vm-cli-payload-repeatability-evidence-status-review.sh'
workflow='.github/workflows/fedora-vm-cli-payload-repeatability-publication-review-template.yml'

for file in \
  "$doc" \
  "$status" \
  "$index" \
  "$readme" \
  "$script" \
  "$test_script" \
  "$publication_gate" \
  "$publication_gate_status" \
  "$status_validator" \
  "$status_review" \
  "$workflow"
do
  require_file "$file"
done

sh -n "$script"
sh -n "$test_script"

require_contains 'Status: no-effect publication review template' "$doc"
require_contains 'Evidence level: 9 repeatability target, template only' "$doc"
require_contains 'future operator publication review shape' "$doc"
require_contains 'It does not run the repeatability runner.' "$doc"
require_contains 'It does not validate a live transcript.' "$doc"
require_contains 'It does not attach a transcript.' "$doc"
require_contains 'It does not write an evidence status record.' "$doc"
require_contains 'It does not approve publication.' "$doc"
require_contains 'It does not publish repeatability evidence.' "$doc"
require_contains 'It does not mutate a host.' "$doc"

require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_PUBLICATION_GATE.md' "$doc"
require_contains 'docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_PUBLICATION_GATE_STATUS.md' "$doc"
require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_REVIEW_VALIDATOR.md' "$doc"
require_contains 'scripts/fedora-vm-cli-payload-repeatability-evidence-status-review.sh' "$doc"

for current_field in \
  'fedora_vm_cli_payload_repeatability_evidence_publication_gate_present=1' \
  'fedora_vm_cli_payload_repeatability_publication_review_template_present=1' \
  'publication_review_template_mode=no-effect-template' \
  'publication_review_template_complete=0' \
  'repeatability_evidence_publication_requested=0' \
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
  'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION REVIEW' \
  'publication_review_status=<required-after-operator-review>' \
  'publication_review_date=<required-after-operator-review>' \
  'operator_reviewer=<required-after-operator-review>' \
  'transcript_review_output_attached=1' \
  'evidence_status_review_output_attached=1' \
  'transcript_checksum_matches_status=1' \
  'source_revision_matches_status=1' \
  'status_candidate_validator_passed=1' \
  'publication_gate_reviewed=1' \
  'non_claims_reviewed=1' \
  'operator_publication_review_completed=1' \
  'repeatability_evidence_publication_approved=1' \
  'published_status_path=<required-after-status-write>' \
  'repeatability_evidence_status_published=1' \
  'evidence_status_written=1' \
  'cli_payload_repeatability_evidence_present=1'
do
  require_contains "$future_field" "$doc"
done

require_contains 'Status: template/status alignment' "$status"
require_contains 'Date: 2026-05-26' "$status"
require_contains 'does not approve publication' "$status"
require_contains 'does not publish repeatability evidence' "$status"
require_contains 'Run manual disposable Fedora VM CLI payload repeatability lane, validate transcript and evidence status candidates, then fill the publication review template' "$status"

require_contains 'FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_TEMPLATE_STATUS.md' "$index"
require_contains 'Current Fedora VM CLI payload repeatability publication review template checkpoint' "$index"
require_contains 'publication review template is present but does not approve or publish repeatability evidence' "$index"

require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_TEMPLATE.md' "$readme"
require_contains 'docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_PUBLICATION_REVIEW_TEMPLATE_STATUS.md' "$readme"
require_contains 'The repeatability publication review template is present' "$readme"
require_contains 'does not approve or publish evidence' "$readme"

require_contains 'fedora_vm_cli_payload_repeatability_evidence_publication_gate_present=1' "$publication_gate"
require_contains 'operator_publication_review_completed=0' "$publication_gate_status"
require_contains 'promotion_allowed_by_status_validator_alone=0' "$status_validator"
require_contains 'evidence_status_written_by_validator=0' "$status_review"

require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION REVIEW TEMPLATE' "$script"
require_contains 'publication_review_template_decision=blocked-template-only-no-operator-approval' "$script"
require_contains 'publication_approved_by_template=0' "$script"
require_contains 'repeatability_evidence_published_by_template=0' "$script"
require_absent 'sudo ' "$script"
require_absent 'rpmbuild ' "$script"
require_absent 'rpm -Uvh' "$script"
require_absent 'rpm -e' "$script"
require_absent 'dnf ' "$script"
require_absent 'curl ' "$script"
require_absent 'wget ' "$script"

require_contains 'name: Fedora VM CLI Payload Repeatability Publication Review Template' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-publication-review-template.sh' "$workflow"
require_absent 'sh scripts/run-fedora-vm-cli-payload-repeatability-lane.sh' "$workflow"
require_absent 'sh scripts/fedora-vm-cli-payload-repeatability-publication-review-template.sh' "$workflow"

require_contains 'sh ./scripts/test-fedora-vm-cli-payload-repeatability-publication-review-template.sh' 'Makefile'
require_contains 'fedora-vm-cli-payload-repeatability-publication-review-template:' 'Makefile'

output=$(sh "$script")
require_output_contains "$output" 'FEDORA VM CLI PAYLOAD REPEATABILITY PUBLICATION REVIEW TEMPLATE'
require_output_contains "$output" 'template_status=ok'
require_output_contains "$output" 'fedora_vm_cli_payload_repeatability_publication_review_template_present=1'
require_output_contains "$output" 'publication_review_template_mode=no-effect-template'
require_output_contains "$output" 'publication_review_template_decision=blocked-template-only-no-operator-approval'
require_output_contains "$output" 'publication_approved_by_template=0'
require_output_contains "$output" 'repeatability_evidence_published_by_template=0'
require_output_contains "$output" 'operator_publication_review_completed=0'
require_output_contains "$output" 'repeatability_evidence_publication_approved=0'
require_output_contains "$output" '[future_publication_review_record]'
require_output_contains "$output" 'operator_publication_review_completed=1'
require_output_contains "$output" 'repeatability_evidence_status_published=1'

printf 'fedora_vm_cli_payload_repeatability_publication_review_template: ok\n'
