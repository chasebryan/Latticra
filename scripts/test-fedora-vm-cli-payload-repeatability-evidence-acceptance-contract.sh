#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora vm cli payload repeatability evidence acceptance contract: %s\n' "$1" >&2
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

doc='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_ACCEPTANCE_CONTRACT.md'
status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_ACCEPTANCE_CONTRACT_STATUS.md'
index='docs/status/README.md'
readme='README.md'
contract='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT.md'
template='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CAPTURE_TEMPLATE.md'
review_validator='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_REVIEW_VALIDATOR.md'
review_gate='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_REVIEW_GATE.md'
evidence='docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md'
review_script='scripts/fedora-vm-cli-payload-repeatability-transcript-review.sh'
runner='scripts/run-fedora-vm-cli-payload-repeatability-lane.sh'
test_script='scripts/test-fedora-vm-cli-payload-repeatability-evidence-acceptance-contract.sh'
workflow='.github/workflows/fedora-vm-cli-payload-repeatability-evidence-acceptance-contract.yml'

for file in \
  "$doc" \
  "$status" \
  "$index" \
  "$readme" \
  "$contract" \
  "$template" \
  "$review_validator" \
  "$review_gate" \
  "$evidence" \
  "$review_script" \
  "$runner" \
  "$test_script" \
  "$workflow"
do
  require_file "$file"
done

sh -n "$test_script"

require_contains 'Status: acceptance contract' "$doc"
require_contains 'Evidence level: 9 repeatability target, contract only' "$doc"
require_contains 'future evidence status record after a real Fedora VM repeatability transcript is validated and accepted' "$doc"
require_contains 'It does not run the repeatability runner.' "$doc"
require_contains 'It does not validate a live transcript.' "$doc"
require_contains 'It does not attach a transcript.' "$doc"
require_contains 'It does not write an evidence status record.' "$doc"
require_contains 'It does not accept repeatability evidence.' "$doc"
require_contains 'It does not mutate a host.' "$doc"

require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT.md' "$doc"
require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CAPTURE_TEMPLATE.md' "$doc"
require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_REVIEW_VALIDATOR.md' "$doc"
require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_REVIEW_GATE.md' "$doc"
require_contains 'docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md' "$doc"
require_contains 'scripts/fedora-vm-cli-payload-repeatability-transcript-review.sh' "$doc"
require_contains 'scripts/run-fedora-vm-cli-payload-repeatability-lane.sh' "$doc"

for prerequisite in \
  'repeatability_transcript_attached=1' \
  'repeatability_transcript_reviewed=1' \
  'repeatability_transcript_candidate_valid=1' \
  'repeatability_transcript_placeholder_values_absent=1' \
  'repeatability_transcript_required_markers_present=1' \
  'repeatability_transcript_value_fields_validated=1' \
  'repeatability_transcript_accepted=1' \
  'evidence_status_written=1'
do
  require_contains "$prerequisite" "$doc"
done

for accepted_field in \
  'FEDORA VM CLI PAYLOAD REPEATABILITY EVIDENCE STATUS' \
  'Status: evidence status alignment' \
  'source=operator disposable Fedora VM repeatability transcript' \
  'transcript_kind=disposable-vm-cli-payload-repeatability' \
  'repeatability_transcript_reviewed=1' \
  'repeatability_transcript_accepted=1' \
  'repeatability_transcript_candidate_valid=1' \
  'repeatability_transcript_placeholder_values_absent=1' \
  'repeatability_transcript_required_markers_present=1' \
  'repeatability_transcript_value_fields_validated=1' \
  'source_tree_revision_recorded=1' \
  'fedora_os_release_recorded=1' \
  'fedora_kernel_version_recorded=1' \
  'spec_checksum_recorded=1' \
  'source_archive_checksum_recorded=1' \
  'rpm_nevra_recorded=1' \
  'rpm_payload_matches_expected_cli_surfaces=1' \
  'validated_cli_mode_still_no_effect=1' \
  'validated_runtime_behavior_still_disabled=1' \
  'validated_non_claims_preserved=1' \
  'rpm_verify_completed=1' \
  'removal_validation_performed=1' \
  'post_removal_absence_verified=1' \
  'second_disposable_vm_cli_validation_completed=1' \
  'cli_payload_repeatability_evidence_present=1' \
  'host_install_ready_for_cli_payload=1' \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0' \
  'evidence_level=9'
do
  require_contains "$accepted_field" "$doc"
done

for current_field in \
  'fedora_vm_cli_payload_repeatability_evidence_acceptance_contract_present=1' \
  'repeatability_transcript_attached=0' \
  'repeatability_transcript_reviewed=0' \
  'repeatability_transcript_candidate_valid=0' \
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

require_contains 'The acceptance contract alone cannot promote evidence.' "$doc"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-evidence-acceptance-contract.sh' "$doc"
require_contains 'fedora_vm_cli_payload_repeatability_evidence_acceptance_contract: ok' "$doc"
require_contains 'Run manual disposable Fedora VM CLI payload repeatability lane, validate transcript candidate, and write accepted repeatability evidence status' "$doc"
require_contains 'not repeatability evidence' "$doc"
require_contains 'not host mutation' "$doc"
require_contains 'not production readiness' "$doc"
require_contains 'not Fedora approval' "$doc"

require_contains 'Status: acceptance contract/status alignment' "$status"
require_contains 'Date: 2026-05-26' "$status"
require_contains 'does not write evidence status' "$status"
require_contains 'does not mark repeatability evidence present' "$status"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-evidence-acceptance-contract.sh' "$status"
require_contains 'Run manual disposable Fedora VM CLI payload repeatability lane, validate transcript candidate, and write accepted repeatability evidence status' "$status"

require_contains 'FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_ACCEPTANCE_CONTRACT_STATUS.md' "$index"
require_contains 'Current Fedora VM CLI payload repeatability evidence acceptance contract checkpoint' "$index"
require_contains 'acceptance contract is present but does not attach, accept, or write repeatability evidence' "$index"
require_contains 'Run manual disposable Fedora VM CLI payload repeatability lane, validate transcript candidate, and write accepted repeatability evidence status' "$index"

require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_ACCEPTANCE_CONTRACT.md' "$readme"
require_contains 'docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_ACCEPTANCE_CONTRACT_STATUS.md' "$readme"
require_contains 'fedora_vm_cli_payload_repeatability_evidence_acceptance_contract_present=1' "$readme"
require_contains 'The repeatability evidence acceptance contract is present' "$readme"
require_contains 'no evidence status is written or accepted' "$readme"

require_contains 'transcript_kind=disposable-vm-cli-payload-repeatability' "$contract"
require_contains 'Status: no-effect repeatability transcript capture template' "$template"
require_contains 'repeatability_transcript_accepted=0' "$review_validator"
require_contains 'repeatability_transcript_accepted=0' "$review_gate"
require_contains 'disposable_vm_cli_validation_completed=1' "$evidence"
require_contains 'repeatability_transcript_accepted=0' "$review_script"
require_contains 'repeatability_validation_status=ok' "$runner"

require_contains 'name: Fedora VM CLI Payload Repeatability Evidence Acceptance Contract' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-evidence-acceptance-contract.sh' "$workflow"
require_absent 'sh scripts/run-fedora-vm-cli-payload-repeatability-lane.sh' "$workflow"

require_contains 'sh ./scripts/test-fedora-vm-cli-payload-repeatability-evidence-acceptance-contract.sh' 'Makefile'
require_contains 'fedora-vm-cli-payload-repeatability-evidence-acceptance-contract:' 'Makefile'

printf 'fedora_vm_cli_payload_repeatability_evidence_acceptance_contract: ok\n'
