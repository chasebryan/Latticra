#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora vm cli payload validation status alignment: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora vm cli payload validation status alignment: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_absent() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'fedora vm cli payload validation status alignment: unexpected pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status='docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_STATUS.md'
index='docs/status/README.md'
lane='docs/FEDORA_VM_CLI_PAYLOAD_VALIDATION_LANE.md'
runner='scripts/run-fedora-vm-cli-payload-validation-lane.sh'
docs_guard='scripts/test-fedora-vm-cli-payload-validation-lane-docs.sh'
lane_workflow='.github/workflows/fedora-vm-cli-payload-validation-lane-docs.yml'
status_workflow='.github/workflows/fedora-vm-cli-payload-validation-status.yml'
contract='docs/FEDORA_VM_CLI_TRANSCRIPT_CONTRACT.md'

require_file "$status"
require_file "$index"
require_file "$lane"
require_file "$runner"
require_file "$docs_guard"
require_file "$lane_workflow"
require_file "$status_workflow"
require_file "$contract"
require_file packaging/fedora/latticra.spec
require_file src/latticra_cli.c
require_file scripts/test-latticra-no-effect-cli-status-surface.sh
require_file docs/status/LATTICRA_NO_EFFECT_CLI_RPM_SPEC_UPDATE_STATUS.md

require_contains 'Status: status alignment' "$status"
require_contains 'Date: 2026-05-21' "$status"
require_contains 'manually gated disposable Fedora VM CLI payload validation lane runner landed on `main`' "$status"
require_contains '/usr/bin/latticra' "$status"
require_contains '/usr/share/doc/latticra/README.md' "$status"
require_contains 'runner-readiness evidence only' "$status"
require_contains 'It does not prove that a disposable Fedora VM CLI payload validation run has completed yet.' "$status"
require_contains 'The validation runner remains manually gated and must not be auto-run by normal CI.' "$status"

require_contains 'source=PR #236' "$status"
require_contains 'validation_lane_documented=1' "$status"
require_contains 'validation_runner_present=1' "$status"
require_contains 'validation_lane_docs_guard_present=1' "$status"
require_contains 'validation_lane_docs_workflow_present=1' "$status"
require_contains 'runner_manual_only=1' "$status"
require_contains 'ci_auto_vm_cli_validation_allowed=0' "$status"
require_contains 'disposable_vm_target_required=1' "$status"
require_contains 'daily_driver_block_required=1' "$status"
require_contains 'production_host_block_required=1' "$status"
require_contains 'immutable_fedora_block_required=1' "$status"
require_contains 'clean_snapshot_required=1' "$status"
require_contains 'recovery_path_required=1' "$status"
require_contains 'operator_consent_required=1' "$status"
require_contains 'non_root_operator_required=1' "$status"
require_contains 'sudo_limited_to_rpm_install_removal=1' "$status"
require_contains 'fedora_target_required=1' "$status"
require_contains 'rpm_tooling_required=1' "$status"
require_contains 'rpmbuild_tooling_required=1' "$status"
require_contains 'cc_tooling_required=1' "$status"
require_contains 'local_cli_guard_required=1' "$status"
require_contains 'local_rpm_build_required=1' "$status"
require_contains 'rpm_payload_listing_required=1' "$status"
require_contains 'rpm_payload_cli_binary_required=1' "$status"
require_contains 'rpm_payload_readme_required=1' "$status"
require_contains 'rpm_payload_only_expected_surfaces_required=1' "$status"
require_contains 'unexpected_runtime_surface_absent_required=1' "$status"
require_contains 'installed_cli_binary_required=1' "$status"
require_contains 'installed_readme_required=1' "$status"
require_contains 'rpm_verify_required=1' "$status"
require_contains 'cli_status_validation_required=1' "$status"
require_contains 'cli_version_validation_required=1' "$status"
require_contains 'cli_report_validation_required=1' "$status"
require_contains 'cli_invalid_command_validation_required=1' "$status"
require_contains 'post_removal_cli_absence_required=1' "$status"
require_contains 'post_removal_readme_absence_required=1' "$status"
require_contains 'validation_report_schema_present=1' "$status"
require_contains 'target_evidence_level=9' "$status"
require_contains 'current_evidence_level=8' "$status"
require_contains 'evidence_level_9_achieved=0' "$status"

require_contains 'fedora_vm_cli_transcript_contract_present=1' "$status"
require_contains 'fedora_vm_cli_payload_validation_lane_present=1' "$status"
require_contains 'fedora_vm_cli_payload_validation_runner_present=1' "$status"
require_contains 'fedora_vm_cli_payload_validation_status=blocked-pending-real-vm-run' "$status"
require_contains 'disposable_vm_cli_validation_transcript_present=0' "$status"
require_contains 'disposable_vm_cli_validation_completed=0' "$status"
require_contains 'host_install_ready_for_cli_payload=0' "$status"
require_contains 'production_installer_ready=0' "$status"
require_contains 'fedora_distribution_ready=0' "$status"
require_contains 'fedora_approval_claimed=0' "$status"
require_contains 'daily_driver_install_ready=0' "$status"
require_contains 'immutable_fedora_ready=0' "$status"

require_contains 'This status alignment does not run the validation lane.' "$status"
require_contains 'It does not build a release RPM artifact.' "$status"
require_contains 'It does not install or remove an RPM.' "$status"
require_contains 'It does not validate `/usr/bin/latticra` in a real disposable Fedora VM.' "$status"
require_contains 'The CLI payload validation runner must remain manual and gated by explicit disposable-VM evidence.' "$status"
require_contains 'sh scripts/test-fedora-vm-cli-payload-validation-lane-docs.sh' "$status"
require_contains 'sh scripts/test-fedora-vm-cli-payload-validation-status-alignment.sh' "$status"
require_contains 'fedora_vm_cli_payload_validation_lane_docs: ok' "$status"
require_contains 'fedora_vm_cli_payload_validation_status_alignment: ok' "$status"
require_contains 'Capture real disposable Fedora VM CLI payload validation transcript evidence' "$status"
require_contains 'The root README should not claim CLI payload host install readiness yet.' "$status"
require_contains 'host_install_ready_for_cli_payload=1' "$status"
require_contains 'production installer claim' "$status"

require_contains 'FEDORA_VM_CLI_PAYLOAD_VALIDATION_STATUS.md' "$index"
require_contains 'Current Fedora VM CLI payload validation lane checkpoint' "$index"
require_contains 'source=PR #236' "$index"
require_contains 'validation_runner_present=1' "$index"
require_contains 'runner_manual_only=1' "$index"
require_contains 'ci_auto_vm_cli_validation_allowed=0' "$index"
require_contains 'rpm_payload_cli_binary_required=1' "$index"
require_contains 'rpm_payload_readme_required=1' "$index"
require_contains 'cli_status_validation_required=1' "$index"
require_contains 'cli_version_validation_required=1' "$index"
require_contains 'cli_report_validation_required=1' "$index"
require_contains 'fedora_vm_cli_payload_validation_status=blocked-pending-real-vm-run' "$index"
require_contains 'disposable_vm_cli_validation_transcript_present=0' "$index"
require_contains 'host_install_ready_for_cli_payload=0' "$index"
require_contains 'Capture real disposable Fedora VM CLI payload validation transcript evidence' "$index"

require_contains 'Status: gated validation lane runner' "$lane"
require_contains 'Evidence level: 9 target' "$lane"
require_contains 'FEDORA VM CLI PAYLOAD VALIDATION LANE' "$lane"
require_contains 'LATTICRA_ALLOW_DISPOSABLE_VM_RPM_VALIDATION=1' "$lane"
require_contains 'runner_manual_only=1' "$lane"
require_contains 'ci_auto_vm_cli_validation_allowed=0' "$lane"

require_contains 'require_flag LATTICRA_ALLOW_DISPOSABLE_VM_RPM_VALIDATION 1' "$runner"
require_contains 'require_flag LATTICRA_TARGET_IS_DISPOSABLE_FEDORA_VM 1' "$runner"
require_contains 'require_payload_line '\''/usr/bin/latticra'\''' "$runner"
require_contains 'require_payload_line '\''/usr/share/doc/latticra/README.md'\''' "$runner"
require_contains 'require_payload_only_expected_surfaces' "$runner"
require_contains 'FEDORA VM CLI PAYLOAD VALIDATION LANE' "$runner"
require_contains 'host_install_ready_for_cli_payload=1' "$runner"

require_contains 'FEDORA VM CLI PAYLOAD VALIDATION TRANSCRIPT' "$contract"
require_contains 'transcript_kind=disposable-vm-cli-payload-validation' "$contract"
require_contains 'host_install_ready_for_cli_payload=0' "$contract"
require_contains 'host_install_ready_for_cli_payload=1' "$contract"

require_contains 'name: Fedora VM CLI Payload Validation Status' "$status_workflow"
require_contains 'runs-on: ubuntu-latest' "$status_workflow"
require_contains 'sh scripts/test-fedora-vm-cli-payload-validation-status-alignment.sh' "$status_workflow"
require_absent 'sh scripts/run-fedora-vm-cli-payload-validation-lane.sh' "$status_workflow"

printf 'fedora_vm_cli_payload_validation_status_alignment: ok\n'
