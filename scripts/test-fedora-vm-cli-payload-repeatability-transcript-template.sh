#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora vm cli payload repeatability transcript template: %s\n' "$1" >&2
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

doc='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CAPTURE_TEMPLATE.md'
status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CAPTURE_TEMPLATE_STATUS.md'
index='docs/status/README.md'
readme='README.md'
script='scripts/fedora-vm-cli-payload-repeatability-transcript-template.sh'
test_script='scripts/test-fedora-vm-cli-payload-repeatability-transcript-template.sh'
contract='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT.md'
runner_plan='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_RUNNER_PLAN.md'
review_gate='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_REVIEW_GATE.md'
review_gate_status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_REVIEW_GATE_STATUS.md'
review_validator='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_REVIEW_VALIDATOR.md'
review_validator_status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_REVIEW_VALIDATOR_STATUS.md'
review_script='scripts/fedora-vm-cli-payload-repeatability-transcript-review.sh'
evidence='docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md'
runner='scripts/run-fedora-vm-cli-payload-repeatability-lane.sh'
workflow='.github/workflows/fedora-vm-cli-payload-repeatability-transcript-template.yml'

for file in \
  "$doc" \
  "$status" \
  "$index" \
  "$readme" \
  "$script" \
  "$test_script" \
  "$contract" \
  "$runner_plan" \
  "$review_gate" \
  "$review_gate_status" \
  "$review_validator" \
  "$review_validator_status" \
  "$review_script" \
  "$evidence" \
  "$runner" \
  "$workflow"
do
  require_file "$file"
done

sh -n "$script"
sh -n "$test_script"

require_contains 'Status: no-effect repeatability transcript capture template' "$doc"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_capture_template_present=1' "$doc"
require_contains 'repeatability_transcript_template_mode=no-effect-template' "$doc"
require_contains 'repeatability_transcript_template_decision=blocked-template-only-no-vm-execution' "$doc"
require_contains 'repeatability_transcript_template_complete=0' "$doc"
require_contains 'repeatability_runner_executed=0' "$doc"
require_contains 'rpm_build_performed=0' "$doc"
require_contains 'rpm_install_performed=0' "$doc"
require_contains 'rpm_removal_performed=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'sh scripts/fedora-vm-cli-payload-repeatability-transcript-template.sh' "$doc"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-transcript-template.sh' "$doc"
require_contains 'scripts/fedora-vm-cli-payload-repeatability-transcript-review.sh --transcript <path>' "$doc"
require_contains 'Run manual disposable Fedora VM CLI payload repeatability lane, validate the transcript candidate, and then add reviewed evidence status' "$doc"

require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY TRANSCRIPT CAPTURE TEMPLATE' "$script"
require_contains 'repeatability_transcript_template_decision=blocked-template-only-no-vm-execution' "$script"
require_contains 'repeatability_runner_executed=0' "$script"
require_contains 'rpm_build_performed=0' "$script"
require_contains 'rpm_install_performed=0' "$script"
require_contains 'rpm_removal_performed=0' "$script"
require_contains 'host_mutation_performed=0' "$script"
require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY TRANSCRIPT' "$script"
require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY LANE' "$script"
require_contains 'source_tree_revision=<required-from-real-run>' "$script"
require_contains 'fedora_kernel_version=<required-from-real-run>' "$script"
require_contains 'spec_checksum=<required-from-real-run>' "$script"
require_contains 'source_archive_checksum=<required-from-real-run>' "$script"
require_contains 'rpm_nevra=<required-from-real-run>' "$script"
require_absent 'sudo ' "$script"
require_absent 'rpmbuild ' "$script"
require_absent 'rpm -Uvh' "$script"
require_absent 'rpm -e' "$script"
require_absent 'dnf ' "$script"
require_absent 'curl ' "$script"
require_absent 'wget ' "$script"

require_contains 'Status: template/status alignment' "$status"
require_contains 'Date: 2026-05-26' "$status"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_capture_template_present=1' "$status"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_review_validator_present=1' "$status"
require_contains 'repeatability_transcript_template_mode=no-effect-template' "$status"
require_contains 'repeatability_transcript_template_complete=0' "$status"
require_contains 'repeatability_transcript_candidate_valid=0' "$status"
require_contains 'repeatability_transcript_accepted=0' "$status"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-transcript-template.sh' "$status"

require_contains 'FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CAPTURE_TEMPLATE_STATUS.md' "$index"
require_contains 'Current Fedora VM CLI payload repeatability transcript capture template checkpoint' "$index"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_capture_template_present=1' "$index"
require_contains 'repeatability_transcript_template_complete=0' "$index"
require_contains 'repeatability_transcript_accepted=0' "$index"

require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CAPTURE_TEMPLATE.md' "$readme"
require_contains 'docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CAPTURE_TEMPLATE_STATUS.md' "$readme"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_capture_template_present=1' "$readme"
require_contains 'repeatability_transcript_template_mode=no-effect-template' "$readme"

require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CAPTURE_TEMPLATE.md' "$review_gate"
require_contains 'scripts/fedora-vm-cli-payload-repeatability-transcript-template.sh' "$review_gate"
require_contains 'scripts/fedora-vm-cli-payload-repeatability-transcript-review.sh' "$review_gate"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_capture_template_present=1' "$review_gate"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_capture_template_present=1' "$review_gate_status"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_review_validator_present=1' "$review_gate"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_review_validator_present=1' "$review_gate_status"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_review_validator_present=1' "$review_validator"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_review_validator_present=1' "$review_validator_status"
require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY TRANSCRIPT REVIEW' "$review_script"

require_contains 'transcript_kind=disposable-vm-cli-payload-repeatability' "$contract"
require_contains 'fedora_vm_cli_payload_repeatability_runner_present=1' "$runner_plan"
require_contains 'repeatability_transcript_accepted=0' "$review_gate"
require_contains 'validated_package=latticra-0.0.0-0.1.local.fc44.x86_64.rpm' "$evidence"
require_contains 'repeatability_validation_status=ok' "$runner"

require_contains 'name: Fedora VM CLI Payload Repeatability Transcript Template' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-transcript-template.sh' "$workflow"
require_absent 'sh scripts/run-fedora-vm-cli-payload-repeatability-lane.sh' "$workflow"

output=$(sh "$script")
require_output_contains "$output" 'FEDORA VM CLI PAYLOAD REPEATABILITY TRANSCRIPT CAPTURE TEMPLATE'
require_output_contains "$output" 'template_status=ok'
require_output_contains "$output" 'fedora_vm_cli_payload_repeatability_transcript_capture_template_present=1'
require_output_contains "$output" 'repeatability_transcript_template_mode=no-effect-template'
require_output_contains "$output" 'repeatability_transcript_template_decision=blocked-template-only-no-vm-execution'
require_output_contains "$output" 'repeatability_runner_executed=0'
require_output_contains "$output" 'rpm_build_performed=0'
require_output_contains "$output" 'rpm_install_performed=0'
require_output_contains "$output" 'rpm_removal_performed=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'FEDORA VM CLI PAYLOAD REPEATABILITY TRANSCRIPT'
require_output_contains "$output" 'FEDORA VM CLI PAYLOAD REPEATABILITY LANE'
require_output_contains "$output" 'source_tree_revision=<required-from-real-run>'
require_output_contains "$output" 'fedora_kernel_version=<required-from-real-run>'
require_output_contains "$output" 'spec_checksum=<required-from-real-run>'
require_output_contains "$output" 'source_archive_checksum=<required-from-real-run>'
require_output_contains "$output" 'rpm_nevra=<required-from-real-run>'
require_output_contains "$output" 'repeatability_transcript_accepted=0'
require_output_contains "$output" 'cli_payload_repeatability_evidence_present=0'

printf 'fedora_vm_cli_payload_repeatability_transcript_template: ok\n'
