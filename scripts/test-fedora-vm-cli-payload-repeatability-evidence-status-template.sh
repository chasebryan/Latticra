#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'fedora vm cli payload repeatability evidence status template: %s\n' "$1" >&2
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

doc='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_TEMPLATE.md'
status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_TEMPLATE_STATUS.md'
index='docs/status/README.md'
readme='README.md'
script='scripts/fedora-vm-cli-payload-repeatability-evidence-status-template.sh'
test_script='scripts/test-fedora-vm-cli-payload-repeatability-evidence-status-template.sh'
acceptance='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_ACCEPTANCE_CONTRACT.md'
acceptance_status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_ACCEPTANCE_CONTRACT_STATUS.md'
review_gate='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_REVIEW_GATE.md'
review_validator='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_REVIEW_VALIDATOR.md'
review_script='scripts/fedora-vm-cli-payload-repeatability-transcript-review.sh'
runner='scripts/run-fedora-vm-cli-payload-repeatability-lane.sh'
workflow='.github/workflows/fedora-vm-cli-payload-repeatability-evidence-status-template.yml'

for file in \
  "$doc" \
  "$status" \
  "$index" \
  "$readme" \
  "$script" \
  "$test_script" \
  "$acceptance" \
  "$acceptance_status" \
  "$review_gate" \
  "$review_validator" \
  "$review_script" \
  "$runner" \
  "$workflow"
do
  require_file "$file"
done

sh -n "$script"
sh -n "$test_script"

require_contains 'Status: no-effect repeatability evidence status template' "$doc"
require_contains 'Evidence level: 9 repeatability target, template only' "$doc"
require_contains 'future accepted evidence status shape' "$doc"
require_contains 'It does not run the repeatability runner.' "$doc"
require_contains 'It does not validate a live transcript.' "$doc"
require_contains 'It does not attach a transcript.' "$doc"
require_contains 'It does not write an evidence status record.' "$doc"
require_contains 'It does not accept repeatability evidence.' "$doc"
require_contains 'It does not mutate a host.' "$doc"
require_contains 'sh scripts/fedora-vm-cli-payload-repeatability-evidence-status-template.sh' "$doc"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-evidence-status-template.sh' "$doc"

for current_field in \
  'fedora_vm_cli_payload_repeatability_evidence_acceptance_contract_present=1' \
  'fedora_vm_cli_payload_repeatability_evidence_status_template_present=1' \
  'repeatability_evidence_status_template_mode=no-effect-template' \
  'repeatability_evidence_status_template_complete=0' \
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

for future_field in \
  'FEDORA VM CLI PAYLOAD REPEATABILITY EVIDENCE STATUS' \
  'Status: evidence status alignment' \
  'Date: <required-from-accepted-review-date>' \
  'source=operator disposable Fedora VM repeatability transcript' \
  'transcript_kind=disposable-vm-cli-payload-repeatability' \
  'transcript_path=<required-from-operator-attachment>' \
  'transcript_checksum=<required-from-accepted-review>' \
  'repeatability_transcript_reviewed=1' \
  'repeatability_transcript_accepted=1' \
  'repeatability_transcript_candidate_valid=1' \
  'repeatability_transcript_placeholder_values_absent=1' \
  'repeatability_transcript_required_markers_present=1' \
  'repeatability_transcript_value_fields_validated=1' \
  'source_tree_revision_recorded=1' \
  'source_tree_revision=<required-from-real-run>' \
  'fedora_os_release_recorded=1' \
  'fedora_os_release=<required-from-real-run>' \
  'fedora_kernel_version_recorded=1' \
  'fedora_kernel_version=<required-from-real-run>' \
  'spec_checksum_recorded=1' \
  'spec_checksum=<required-from-real-run>' \
  'source_archive_checksum_recorded=1' \
  'source_archive_checksum=<required-from-real-run>' \
  'rpm_nevra_recorded=1' \
  'rpm_nevra=<required-from-real-run>' \
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
  'evidence_level=9' \
  'evidence_status_written=1'
do
  require_contains "$future_field" "$doc"
done

require_contains 'Status: template/status alignment' "$status"
require_contains 'Date: 2026-05-26' "$status"
require_contains 'does not write evidence status' "$status"
require_contains 'does not mark repeatability evidence present' "$status"
require_contains 'Run manual disposable Fedora VM CLI payload repeatability lane, validate transcript candidate, and use the evidence status template to write accepted repeatability evidence status' "$status"

require_contains 'FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_TEMPLATE_STATUS.md' "$index"
require_contains 'Current Fedora VM CLI payload repeatability evidence status template checkpoint' "$index"
require_contains 'evidence status template is present but does not attach, accept, or write repeatability evidence' "$index"

require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_TEMPLATE.md' "$readme"
require_contains 'docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_EVIDENCE_STATUS_TEMPLATE_STATUS.md' "$readme"
require_contains 'The repeatability evidence status template is present' "$readme"
require_contains 'does not write or accept evidence' "$readme"

require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY EVIDENCE STATUS' "$acceptance"
require_contains 'repeatability_transcript_accepted=0' "$acceptance_status"
require_contains 'repeatability_transcript_accepted=0' "$review_gate"
require_contains 'repeatability_transcript_accepted=0' "$review_validator"
require_contains 'evidence_status_written=0' "$review_script"
require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY LANE' "$runner"

require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY EVIDENCE STATUS TEMPLATE' "$script"
require_contains 'repeatability_evidence_status_template_decision=blocked-template-only-no-status-write' "$script"
require_contains 'repeatability_runner_executed=0' "$script"
require_contains 'rpm_build_performed=0' "$script"
require_contains 'rpm_install_performed=0' "$script"
require_contains 'rpm_removal_performed=0' "$script"
require_contains 'host_mutation_performed=0' "$script"
require_absent 'sudo ' "$script"
require_absent 'rpmbuild ' "$script"
require_absent 'rpm -Uvh' "$script"
require_absent 'rpm -e' "$script"
require_absent 'dnf ' "$script"
require_absent 'curl ' "$script"
require_absent 'wget ' "$script"

require_contains 'name: Fedora VM CLI Payload Repeatability Evidence Status Template' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-evidence-status-template.sh' "$workflow"
require_absent 'sh scripts/run-fedora-vm-cli-payload-repeatability-lane.sh' "$workflow"

require_contains 'sh ./scripts/test-fedora-vm-cli-payload-repeatability-evidence-status-template.sh' 'Makefile'
require_contains 'fedora-vm-cli-payload-repeatability-evidence-status-template:' 'Makefile'

output=$(sh "$script")
require_output_contains "$output" 'FEDORA VM CLI PAYLOAD REPEATABILITY EVIDENCE STATUS TEMPLATE'
require_output_contains "$output" 'template_status=ok'
require_output_contains "$output" 'fedora_vm_cli_payload_repeatability_evidence_status_template_present=1'
require_output_contains "$output" 'repeatability_evidence_status_template_mode=no-effect-template'
require_output_contains "$output" 'repeatability_evidence_status_template_decision=blocked-template-only-no-status-write'
require_output_contains "$output" 'repeatability_transcript_accepted=0'
require_output_contains "$output" 'evidence_status_written=0'
require_output_contains "$output" '[required_prior_review]'
require_output_contains "$output" 'repeatability_transcript_accepted=1'
require_output_contains "$output" '[future_evidence_status_record]'
require_output_contains "$output" 'FEDORA VM CLI PAYLOAD REPEATABILITY EVIDENCE STATUS'
require_output_contains "$output" 'source_tree_revision=<required-from-real-run>'
require_output_contains "$output" 'fedora_os_release=<required-from-real-run>'
require_output_contains "$output" 'fedora_kernel_version=<required-from-real-run>'
require_output_contains "$output" 'spec_checksum=<required-from-real-run>'
require_output_contains "$output" 'source_archive_checksum=<required-from-real-run>'
require_output_contains "$output" 'rpm_nevra=<required-from-real-run>'
require_output_contains "$output" 'cli_payload_repeatability_evidence_present=1'
require_output_contains "$output" 'evidence_status_written=1'

printf 'fedora_vm_cli_payload_repeatability_evidence_status_template: ok\n'
