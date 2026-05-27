#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora vm cli payload repeatability evidence publication gate: %s\n' "$1" >&2
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

doc='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_PUBLICATION_GATE.md'
status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_PUBLICATION_GATE_STATUS.md'
index='docs/status/README.md'
readme='README.md'
review_gate='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_REVIEW_GATE.md'
transcript_validator='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_REVIEW_VALIDATOR.md'
acceptance='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_ACCEPTANCE_CONTRACT.md'
status_template='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_TEMPLATE.md'
status_validator='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_REVIEW_VALIDATOR.md'
status_validator_status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_REVIEW_VALIDATOR_STATUS.md'
transcript_review='scripts/fedora-vm-cli-payload-repeatability-transcript-review.sh'
status_review='scripts/fedora-vm-cli-payload-repeatability-evidence-status-review.sh'
test_script='scripts/test-fedora-vm-cli-payload-repeatability-evidence-publication-gate.sh'
workflow='.github/workflows/fedora-vm-cli-payload-repeatability-evidence-publication-gate.yml'

for file in \
  "$doc" \
  "$status" \
  "$index" \
  "$readme" \
  "$review_gate" \
  "$transcript_validator" \
  "$acceptance" \
  "$status_template" \
  "$status_validator" \
  "$status_validator_status" \
  "$transcript_review" \
  "$status_review" \
  "$test_script" \
  "$workflow"
do
  require_file "$file"
done

sh -n "$test_script"

require_contains 'Status: publication gate contract' "$doc"
require_contains 'Evidence level: 9 repeatability target, gate only' "$doc"
require_contains 'prevents a passing evidence status candidate review from being treated as published Fedora repeatability evidence' "$doc"
require_contains 'It does not run the repeatability runner.' "$doc"
require_contains 'It does not validate a live transcript.' "$doc"
require_contains 'It does not attach a transcript.' "$doc"
require_contains 'It does not write an evidence status record.' "$doc"
require_contains 'It does not publish repeatability evidence.' "$doc"
require_contains 'It does not mutate a host.' "$doc"

require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_REVIEW_GATE.md' "$doc"
require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_REVIEW_VALIDATOR.md' "$doc"
require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_ACCEPTANCE_CONTRACT.md' "$doc"
require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_TEMPLATE.md' "$doc"
require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_REVIEW_VALIDATOR.md' "$doc"
require_contains 'docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_REVIEW_VALIDATOR_STATUS.md' "$doc"
require_contains 'scripts/fedora-vm-cli-payload-repeatability-transcript-review.sh' "$doc"
require_contains 'scripts/fedora-vm-cli-payload-repeatability-evidence-status-review.sh' "$doc"

for future_field in \
  'repeatability_transcript_attached=1' \
  'repeatability_transcript_reviewed=1' \
  'repeatability_transcript_accepted=1' \
  'repeatability_evidence_status_candidate_valid=1' \
  'repeatability_evidence_status_reviewed=1' \
  'candidate_repeatability_transcript_accepted=1' \
  'candidate_cli_payload_repeatability_evidence_present=1' \
  'candidate_evidence_status_written=1' \
  'operator_publication_review_completed=1' \
  'repeatability_evidence_publication_approved=1' \
  'evidence_status_written=1' \
  'cli_payload_repeatability_evidence_present=1'
do
  require_contains "$future_field" "$doc"
done

for validator_blocker in \
  'repeatability_evidence_status_accepted_by_validator=0' \
  'evidence_status_written_by_validator=0' \
  'promotion_allowed_by_status_validator_alone=0'
do
  require_contains "$validator_blocker" "$doc"
  require_contains "$validator_blocker" "$status"
  require_contains "$validator_blocker" "$index"
  require_contains "$validator_blocker" "$readme"
done

for current_field in \
  'fedora_vm_cli_payload_repeatability_evidence_publication_gate_present=1' \
  'fedora_vm_cli_payload_repeatability_evidence_status_review_validator_present=1' \
  'repeatability_evidence_status_candidate_valid=0' \
  'repeatability_evidence_status_reviewed=0' \
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

require_contains 'Only then write a published evidence status record.' "$doc"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-evidence-publication-gate.sh' "$doc"
require_contains 'Run manual disposable Fedora VM CLI payload repeatability lane, validate transcript and evidence status candidates, then complete operator publication review' "$doc"

require_contains 'Status: publication gate/status alignment' "$status"
require_contains 'Date: 2026-05-26' "$status"
require_contains 'does not write evidence status' "$status"
require_contains 'does not publish repeatability evidence' "$status"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-evidence-publication-gate.sh' "$status"

require_contains 'FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_PUBLICATION_GATE_STATUS.md' "$index"
require_contains 'Current Fedora VM CLI payload repeatability evidence publication gate checkpoint' "$index"
require_contains 'publication gate is present but does not publish repeatability evidence' "$index"

require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_PUBLICATION_GATE.md' "$readme"
require_contains 'docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_PUBLICATION_GATE_STATUS.md' "$readme"
require_contains 'The repeatability evidence publication gate is present' "$readme"
require_contains 'does not publish evidence' "$readme"

require_contains 'repeatability_transcript_accepted=0' "$review_gate"
require_contains 'repeatability_transcript_accepted=0' "$transcript_validator"
require_contains 'The acceptance contract alone cannot promote evidence.' "$acceptance"
require_contains 'evidence_status_written=1' "$status_template"
require_contains 'promotion_allowed_by_status_validator_alone=0' "$status_validator"
require_contains 'promotion_allowed_by_status_validator_alone=0' "$status_validator_status"
require_contains 'evidence_status_written=0' "$transcript_review"
require_contains 'evidence_status_written_by_validator=0' "$status_review"
require_contains 'promotion_allowed_by_status_validator_alone=0' "$status_review"

require_contains 'name: Fedora VM CLI Payload Repeatability Evidence Publication Gate' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-evidence-publication-gate.sh' "$workflow"
require_absent 'sh scripts/run-fedora-vm-cli-payload-repeatability-lane.sh' "$workflow"
require_absent 'sh scripts/fedora-vm-cli-payload-repeatability-evidence-status-review.sh --status' "$workflow"

require_contains 'sh ./scripts/test-fedora-vm-cli-payload-repeatability-evidence-publication-gate.sh' 'Makefile'
require_contains 'fedora-vm-cli-payload-repeatability-evidence-publication-gate:' 'Makefile'

printf 'fedora_vm_cli_payload_repeatability_evidence_publication_gate: ok\n'
