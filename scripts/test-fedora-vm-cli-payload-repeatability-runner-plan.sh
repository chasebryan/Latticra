#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora vm cli payload repeatability runner plan: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora vm cli payload repeatability runner plan: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

doc='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_RUNNER_PLAN.md'
status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_RUNNER_PLAN_STATUS.md'
index='docs/status/README.md'
readme='README.md'
contract='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT.md'
contract_status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT_STATUS.md'
workflow='.github/workflows/fedora-vm-cli-payload-repeatability-runner-plan.yml'
runner='scripts/run-fedora-vm-cli-payload-repeatability-lane.sh'
runner_guard='scripts/test-fedora-vm-cli-payload-repeatability-runner.sh'

require_file "$doc"
require_file "$status"
require_file "$index"
require_file "$readme"
require_file "$contract"
require_file "$contract_status"
require_file "$workflow"
require_file "$runner"
require_file "$runner_guard"
require_file packaging/fedora/latticra.spec
require_file src/latticra_cli.c
require_file scripts/run-fedora-vm-cli-payload-validation-lane.sh
require_file scripts/test-latticra-no-effect-cli-status-surface.sh

require_contains 'Status: implemented runner plan' "$doc"
require_contains 'manual disposable Fedora VM repeatability runner' "$doc"
require_contains 'without running it' "$doc"
require_contains 'This plan records the runner.' "$doc"
require_contains 'It does not execute RPM commands.' "$doc"
require_contains 'It does not install or remove an RPM.' "$doc"
require_contains 'It does not mutate a host.' "$doc"
require_contains 'scripts/run-fedora-vm-cli-payload-repeatability-lane.sh' "$doc"
require_contains 'must remain manual-only and must not be called by normal CI' "$doc"
require_contains 'scripts/test-fedora-vm-cli-payload-repeatability-runner-plan.sh' "$doc"
require_contains 'scripts/test-fedora-vm-cli-payload-repeatability-runner.sh' "$doc"

require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT.md' "$doc"
require_contains 'docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT_STATUS.md' "$doc"
require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_NEXT_VALIDATION_LANE_PLAN.md' "$doc"
require_contains 'docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md' "$doc"
require_contains 'packaging/fedora/latticra.spec' "$doc"
require_contains 'README.md' "$doc"
require_contains 'src/latticra_cli.c' "$doc"
require_contains 'scripts/run-fedora-vm-cli-payload-validation-lane.sh' "$doc"

require_contains 'LATTICRA_ALLOW_DISPOSABLE_VM_RPM_VALIDATION=1' "$doc"
require_contains 'LATTICRA_ALLOW_CLI_PAYLOAD_REPEATABILITY_VALIDATION=1' "$doc"
require_contains 'LATTICRA_TARGET_IS_DISPOSABLE_FEDORA_VM=1' "$doc"
require_contains 'LATTICRA_TARGET_IS_DAILY_DRIVER=0' "$doc"
require_contains 'LATTICRA_TARGET_IS_PRODUCTION_HOST=0' "$doc"
require_contains 'LATTICRA_TARGET_IS_IMMUTABLE_FEDORA=0' "$doc"
require_contains 'LATTICRA_TARGET_HAS_CLEAN_SNAPSHOT=1' "$doc"
require_contains 'LATTICRA_TARGET_HAS_RECOVERY_PATH=1' "$doc"
require_contains 'LATTICRA_OPERATOR_CONSENT_RECORDED=1' "$doc"
require_contains 'operator_is_non_root=1' "$doc"
require_contains 'sudo` only for RPM install and RPM removal' "$doc"

for cmd in awk cat cc find git grep gzip id mktemp rpm rpmbuild sha256sum sort sudo tar uname; do
  require_contains "$cmd" "$doc"
done
require_contains 'fail closed rather than silently omitting checksum evidence' "$doc"

require_contains 'Capture source tree revision.' "$doc"
require_contains 'Capture packaging/fedora/latticra.spec checksum.' "$doc"
require_contains 'Capture source archive checksum.' "$doc"
require_contains 'Capture RPM NEVRA, path, arch, and metadata.' "$doc"
require_contains 'Confirm forbidden payload surfaces are absent.' "$doc"
require_contains 'Execute latticra --status without root.' "$doc"
require_contains 'Verify invalid CLI usage exits with code 2.' "$doc"
require_contains 'Emit the repeatability transcript and deterministic report.' "$doc"

require_contains '/usr/bin/latticra' "$doc"
require_contains '/usr/share/doc/latticra/README.md' "$doc"
require_contains '/etc/latticra' "$doc"
require_contains '/usr/lib/systemd/system/latticra.service' "$doc"
require_contains '/usr/lib/modules' "$doc"
require_contains '/boot/latticra' "$doc"
require_contains '/usr/share/selinux' "$doc"
require_contains '/usr/sbin/latticra' "$doc"

require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY LANE' "$doc"
require_contains 'validation_status=ok' "$doc"
require_contains 'repeatability_validation_status=ok' "$doc"
require_contains 'transcript_kind=disposable-vm-cli-payload-repeatability' "$doc"
require_contains 'prior_cli_payload_evidence_recorded=1' "$doc"
require_contains 'source_tree_revision_recorded=1' "$doc"
require_contains 'source_tree_revision=$source_tree_revision' "$doc"
require_contains 'spec_checksum_recorded=1' "$doc"
require_contains 'spec_checksum=$spec_checksum' "$doc"
require_contains 'source_archive_checksum_recorded=1' "$doc"
require_contains 'source_archive_checksum=$source_archive_checksum' "$doc"
require_contains 'rpm_nevra_recorded=1' "$doc"
require_contains 'rpm_nevra=$rpm_nevra' "$doc"
require_contains 'package_name=$name' "$doc"
require_contains 'package_version=$version' "$doc"
require_contains 'package_arch=$rpm_arch' "$doc"
require_contains 'rpm_payload_matches_expected_cli_surfaces=1' "$doc"
require_contains 'validated_cli_mode_still_no_effect=1' "$doc"
require_contains 'validated_runtime_behavior_still_disabled=1' "$doc"
require_contains 'validated_non_claims_preserved=1' "$doc"
require_contains 'second_disposable_vm_cli_validation_completed=1' "$doc"
require_contains 'cli_payload_repeatability_evidence_present=1' "$doc"
require_contains 'host_install_ready_for_cli_payload=1' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'fedora_distribution_ready=0' "$doc"
require_contains 'fedora_approval_claimed=0' "$doc"
require_contains 'daily_driver_install_ready=0' "$doc"
require_contains 'immutable_fedora_ready=0' "$doc"
require_contains 'evidence_level=9' "$doc"

require_contains 'fedora_vm_cli_payload_repeatability_transcript_contract_present=1' "$doc"
require_contains 'fedora_vm_cli_payload_repeatability_runner_plan_present=1' "$doc"
require_contains 'fedora_vm_cli_payload_repeatability_runner_present=1' "$doc"
require_contains 'repeatability_runner_manual_only=1' "$doc"
require_contains 'ci_auto_repeatability_validation_allowed=0' "$doc"
require_contains 'second_disposable_vm_cli_validation_completed=0' "$doc"
require_contains 'cli_payload_repeatability_evidence_present=0' "$doc"
require_contains 'This plan is not a completed repeatability transcript.' "$doc"
require_contains 'It does not run `scripts/run-fedora-vm-cli-payload-repeatability-lane.sh`.' "$doc"
require_contains 'It does not run `rpmbuild`.' "$doc"
require_contains 'It does not run `rpm`.' "$doc"
require_contains 'Capture reviewed Fedora VM CLI payload repeatability transcript evidence' "$doc"
require_contains 'fedora_vm_cli_payload_repeatability_runner_plan: ok' "$doc"

require_contains 'Status: plan/status alignment' "$status"
require_contains 'Date: 2026-05-26' "$status"
require_contains 'LATTICRA_ALLOW_CLI_PAYLOAD_REPEATABILITY_VALIDATION=1' "$status"
require_contains 'fedora_vm_cli_payload_repeatability_runner_plan_present=1' "$status"
require_contains 'fedora_vm_cli_payload_repeatability_runner_present=1' "$status"
require_contains 'repeatability_runner_manual_only=1' "$status"
require_contains 'ci_auto_repeatability_validation_allowed=0' "$status"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-runner-plan.sh' "$status"
require_contains 'Capture reviewed Fedora VM CLI payload repeatability transcript evidence' "$status"

require_contains 'FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_RUNNER_PLAN_STATUS.md' "$index"
require_contains 'FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_RUNNER_STATUS.md' "$index"
require_contains 'Current Fedora VM CLI payload repeatability runner plan checkpoint' "$index"
require_contains 'fedora_vm_cli_payload_repeatability_runner_plan_present=1' "$index"
require_contains 'fedora_vm_cli_payload_repeatability_runner_present=1' "$index"
require_contains 'repeatability_runner_manual_only=1' "$index"
require_contains 'ci_auto_repeatability_validation_allowed=0' "$index"
require_contains 'Capture reviewed Fedora VM CLI payload repeatability transcript evidence' "$index"

require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_RUNNER_PLAN.md' "$readme"
require_contains 'docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_RUNNER_STATUS.md' "$readme"
require_contains 'Add Fedora VM CLI payload repeatability runner plan' "$contract"
require_contains 'Add Fedora VM CLI payload repeatability runner plan' "$contract_status"

require_contains 'name: Fedora VM CLI Payload Repeatability Runner Plan' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-runner-plan.sh' "$workflow"

printf 'fedora_vm_cli_payload_repeatability_runner_plan: ok\n'
