#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora vm cli payload repeatability evidence review gate: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora vm cli payload repeatability evidence review gate: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_absent() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'fedora vm cli payload repeatability evidence review gate: unexpected pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

doc='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_REVIEW_GATE.md'
status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_REVIEW_GATE_STATUS.md'
index='docs/status/README.md'
readme='README.md'
contract='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT.md'
template='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CAPTURE_TEMPLATE.md'
template_status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CAPTURE_TEMPLATE_STATUS.md'
review_validator='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_REVIEW_VALIDATOR.md'
review_validator_status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_REVIEW_VALIDATOR_STATUS.md'
template_script='scripts/fedora-vm-cli-payload-repeatability-transcript-template.sh'
template_guard='scripts/test-fedora-vm-cli-payload-repeatability-transcript-template.sh'
review_script='scripts/fedora-vm-cli-payload-repeatability-transcript-review.sh'
review_guard='scripts/test-fedora-vm-cli-payload-repeatability-transcript-review-validator.sh'
runner_plan='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_RUNNER_PLAN.md'
runner_status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_RUNNER_STATUS.md'
evidence='docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md'
runner='scripts/run-fedora-vm-cli-payload-repeatability-lane.sh'
runner_guard='scripts/test-fedora-vm-cli-payload-repeatability-runner.sh'
workflow='.github/workflows/fedora-vm-cli-payload-repeatability-evidence-review-gate.yml'

require_file "$doc"
require_file "$status"
require_file "$index"
require_file "$readme"
require_file "$contract"
require_file "$template"
require_file "$template_status"
require_file "$review_validator"
require_file "$review_validator_status"
require_file "$template_script"
require_file "$template_guard"
require_file "$review_script"
require_file "$review_guard"
require_file "$runner_plan"
require_file "$runner_status"
require_file "$evidence"
require_file "$runner"
require_file "$runner_guard"
require_file "$workflow"

require_contains 'Status: review gate contract' "$doc"
require_contains 'Evidence level: 9 repeatability target, gate only' "$doc"
require_contains 'real disposable Fedora VM transcript is attached and reviewed' "$doc"
require_contains 'It does not run the repeatability runner.' "$doc"
require_contains 'It does not execute RPM commands.' "$doc"
require_contains 'It does not install or remove an RPM.' "$doc"
require_contains 'It does not mutate a host.' "$doc"
require_contains 'It does not mark repeatability evidence present.' "$doc"

require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT.md' "$doc"
require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CAPTURE_TEMPLATE.md' "$doc"
require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_REVIEW_VALIDATOR.md' "$doc"
require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_RUNNER_PLAN.md' "$doc"
require_contains 'docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CAPTURE_TEMPLATE_STATUS.md' "$doc"
require_contains 'docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_REVIEW_VALIDATOR_STATUS.md' "$doc"
require_contains 'docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_RUNNER_STATUS.md' "$doc"
require_contains 'docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md' "$doc"
require_contains 'scripts/fedora-vm-cli-payload-repeatability-transcript-template.sh' "$doc"
require_contains 'scripts/test-fedora-vm-cli-payload-repeatability-transcript-template.sh' "$doc"
require_contains 'scripts/fedora-vm-cli-payload-repeatability-transcript-review.sh' "$doc"
require_contains 'scripts/test-fedora-vm-cli-payload-repeatability-transcript-review-validator.sh' "$doc"
require_contains 'scripts/run-fedora-vm-cli-payload-repeatability-lane.sh' "$doc"
require_contains 'scripts/test-fedora-vm-cli-payload-repeatability-runner.sh' "$doc"

for field in \
  'FEDORA VM CLI PAYLOAD REPEATABILITY TRANSCRIPT' \
  'transcript_kind=disposable-vm-cli-payload-repeatability' \
  'transcript_version=1' \
  'operator_review_required=1' \
  'repeatability_transcript_recorded_after_real_run=1' \
  'prior_cli_payload_evidence_recorded=1' \
  'FEDORA VM CLI PAYLOAD REPEATABILITY LANE' \
  'validation_status=ok' \
  'repeatability_validation_status=ok' \
  'source_tree_revision_recorded=1' \
  'source_tree_revision=' \
  'fedora_os_release_recorded=1' \
  'fedora_kernel_version_recorded=1' \
  'fedora_kernel_version=' \
  'spec_checksum_recorded=1' \
  'spec_checksum=' \
  'source_archive_checksum_recorded=1' \
  'source_archive_checksum=' \
  'rpm_nevra_recorded=1' \
  'rpm_nevra=' \
  'package_name=latticra' \
  'package_version=0.0.0' \
  'rpm_payload_listing_recorded=1' \
  'rpm_payload_matches_expected_cli_surfaces=1' \
  'unexpected_runtime_surface_absent=1' \
  'cli_status_output_recorded=1' \
  'cli_version_output_recorded=1' \
  'cli_report_output_recorded=1' \
  'cli_invalid_command_exit_recorded=1' \
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
  'evidence_level=9' \
  'fedora_vm_cli_payload_repeatability_lane: ok'
do
  require_contains "$field" "$doc"
done

require_contains 'source_tree_revision' "$doc"
require_contains 'fedora_kernel_version' "$doc"
require_contains 'spec_checksum' "$doc"
require_contains 'source_archive_checksum' "$doc"
require_contains 'rpm_nevra' "$doc"

for gate_field in \
  'fedora_vm_cli_payload_repeatability_evidence_review_gate_present=1' \
  'fedora_vm_cli_payload_repeatability_transcript_capture_template_present=1' \
  'fedora_vm_cli_payload_repeatability_transcript_review_validator_present=1' \
  'repeatability_transcript_template_mode=no-effect-template' \
  'repeatability_transcript_template_complete=0' \
  'repeatability_transcript_candidate_valid=0' \
  'repeatability_transcript_review_required=1' \
  'repeatability_transcript_attached=0' \
  'repeatability_transcript_reviewed=0' \
  'repeatability_transcript_accepted=0' \
  'second_disposable_vm_cli_validation_completed=0' \
  'cli_payload_repeatability_evidence_present=0' \
  'host_install_ready_for_cli_payload=1' \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0'
do
  require_contains "$gate_field" "$doc"
  require_contains "$gate_field" "$status"
done

require_contains 'Print scripts/fedora-vm-cli-payload-repeatability-transcript-template.sh before the manual run.' "$doc"
require_contains 'Run scripts/run-fedora-vm-cli-payload-repeatability-lane.sh manually inside a disposable Fedora VM.' "$doc"
require_contains 'Attach the complete transcript using the capture template shape.' "$doc"
require_contains 'Validate the transcript candidate with scripts/fedora-vm-cli-payload-repeatability-transcript-review.sh.' "$doc"
require_contains 'Only then add an evidence status record with repeatability_transcript_accepted=1.' "$doc"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-evidence-review-gate.sh' "$doc"
require_contains 'Run manual disposable Fedora VM CLI payload repeatability lane, validate the transcript candidate, and then add reviewed evidence status' "$doc"

require_contains 'Status: review gate/status alignment' "$status"
require_contains 'Date: 2026-05-26' "$status"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_contract_present=1' "$status"
require_contains 'fedora_vm_cli_payload_repeatability_runner_present=1' "$status"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-evidence-review-gate.sh' "$status"
require_contains 'Run manual disposable Fedora VM CLI payload repeatability lane, validate the transcript candidate, and then add reviewed evidence status' "$status"

require_contains 'FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_REVIEW_GATE_STATUS.md' "$index"
require_contains 'Current Fedora VM CLI payload repeatability evidence review gate checkpoint' "$index"
require_contains 'fedora_vm_cli_payload_repeatability_evidence_review_gate_present=1' "$index"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_capture_template_present=1' "$index"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_review_validator_present=1' "$index"
require_contains 'repeatability_transcript_accepted=0' "$index"

require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_REVIEW_GATE.md' "$readme"
require_contains 'docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_REVIEW_GATE_STATUS.md' "$readme"
require_contains 'fedora_vm_cli_payload_repeatability_evidence_review_gate_present=1' "$readme"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_capture_template_present=1' "$readme"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_review_validator_present=1' "$readme"
require_contains 'repeatability_transcript_accepted=0' "$readme"

require_contains 'source_tree_revision_recorded=1' "$contract"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_capture_template_present=1' "$template"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_capture_template_present=1' "$template_status"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_review_validator_present=1' "$review_validator"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_review_validator_present=1' "$review_validator_status"
require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY TRANSCRIPT CAPTURE TEMPLATE' "$template_script"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_template: ok' "$template_guard"
require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY TRANSCRIPT REVIEW' "$review_script"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_review_validator: ok' "$review_guard"
require_contains 'fedora_vm_cli_payload_repeatability_runner_present=1' "$runner_status"
require_contains 'repeatability_validation_status=ok' "$runner"
require_contains 'fedora_vm_cli_payload_repeatability_runner: ok' "$runner_guard"
require_contains 'disposable_vm_cli_validation_completed=1' "$evidence"

require_contains 'name: Fedora VM CLI Payload Repeatability Evidence Review Gate' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-evidence-review-gate.sh' "$workflow"
require_absent 'sh scripts/run-fedora-vm-cli-payload-repeatability-lane.sh' "$workflow"

printf 'fedora_vm_cli_payload_repeatability_evidence_review_gate: ok\n'
