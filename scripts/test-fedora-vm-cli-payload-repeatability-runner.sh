#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora vm cli payload repeatability runner: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora vm cli payload repeatability runner: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_absent() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'fedora vm cli payload repeatability runner: unexpected pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

runner='scripts/run-fedora-vm-cli-payload-repeatability-lane.sh'
doc='docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_RUNNER_PLAN.md'
status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_RUNNER_STATUS.md'
plan_status='docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_RUNNER_PLAN_STATUS.md'
index='docs/status/README.md'
readme='README.md'
workflow='.github/workflows/fedora-vm-cli-payload-repeatability-runner.yml'

require_file "$runner"
require_file "$doc"
require_file "$status"
require_file "$plan_status"
require_file "$index"
require_file "$readme"
require_file "$workflow"
require_file docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT.md
require_file docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT_STATUS.md
require_file docs/FEDORA_VM_CLI_PAYLOAD_NEXT_VALIDATION_LANE_PLAN.md
require_file docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md
require_file packaging/fedora/latticra.spec
require_file README.md
require_file src/latticra_cli.c
require_file scripts/test-latticra-no-effect-cli-status-surface.sh
require_file scripts/run-fedora-vm-cli-payload-validation-lane.sh

sh -n "$runner"

require_contains 'set -eu' "$runner"
require_contains 'require_flag LATTICRA_ALLOW_DISPOSABLE_VM_RPM_VALIDATION 1' "$runner"
require_contains 'require_flag LATTICRA_ALLOW_CLI_PAYLOAD_REPEATABILITY_VALIDATION 1' "$runner"
require_contains 'require_flag LATTICRA_TARGET_IS_DISPOSABLE_FEDORA_VM 1' "$runner"
require_contains 'require_flag LATTICRA_TARGET_IS_DAILY_DRIVER 0' "$runner"
require_contains 'require_flag LATTICRA_TARGET_IS_PRODUCTION_HOST 0' "$runner"
require_contains 'require_flag LATTICRA_TARGET_IS_IMMUTABLE_FEDORA 0' "$runner"
require_contains 'require_flag LATTICRA_TARGET_HAS_CLEAN_SNAPSHOT 1' "$runner"
require_contains 'require_flag LATTICRA_TARGET_HAS_RECOVERY_PATH 1' "$runner"
require_contains 'require_flag LATTICRA_OPERATOR_CONSENT_RECORDED 1' "$runner"
require_contains '[ "${ID:-}" = "fedora" ]' "$runner"
require_contains 'run as a non-root operator account; sudo is used only for rpm install/removal' "$runner"

for cmd in awk cat cc find git grep gzip id mktemp python3 rpm rpmbuild sha256sum sort sudo tar uname; do
  require_contains "require_command $cmd" "$runner"
done

require_contains 'require_file docs/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT.md' "$runner"
require_contains 'require_file docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_TRANSCRIPT_CONTRACT_STATUS.md' "$runner"
require_contains 'require_file docs/FEDORA_VM_CLI_PAYLOAD_NEXT_VALIDATION_LANE_PLAN.md' "$runner"
require_contains 'require_file docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md' "$runner"
require_contains 'require_file packaging/fedora/latticra.spec' "$runner"
require_contains 'require_file README.md' "$runner"
require_contains 'require_file src/latticra_cli.c' "$runner"
require_contains 'require_file scripts/test-latticra-no-effect-cli-status-surface.sh' "$runner"
require_contains 'require_file scripts/run-fedora-vm-cli-payload-validation-lane.sh' "$runner"

require_contains 'prior_validated_package=latticra-0.0.0-0.1.local.fc44.x86_64.rpm' "$runner"
require_contains 'source_tree_revision_recorded=1' "$runner"
require_contains 'spec_checksum_recorded=1' "$runner"
require_contains 'source_archive_checksum_recorded=1' "$runner"
require_contains 'rpm_nevra_recorded=1' "$runner"
require_contains 'disposable_vm_cli_validation_completed=1' "$runner"
require_contains 'host_install_ready_for_cli_payload=1' "$runner"
require_contains 'validated_package=latticra-0.0.0-0.1.local.fc44.x86_64.rpm' "$runner"

require_contains 'sh scripts/test-latticra-no-effect-cli-status-surface.sh' "$runner"
require_contains 'source_tree_revision="$(git rev-parse --verify HEAD)"' "$runner"
require_contains "spec_checksum=\"\$(sha256sum packaging/fedora/latticra.spec | awk '{ print \$1 }')\"" "$runner"
require_contains 'symlink_entry=$(find . -path' "$runner"
require_contains 'refusing source archive with symlink entry' "$runner"
require_contains '"git", "ls-files"' "$runner"
require_contains 'gzip.GzipFile' "$runner"
require_contains 'mtime=0' "$runner"
require_contains 'info.uid = 0' "$runner"
require_contains 'info.gid = 0' "$runner"
require_contains 'write_source_archive "$source_archive" "$root"' "$runner"
require_contains 'source_archive_checksum="$(sha256sum "$source_archive" | awk' "$runner"
require_contains 'rpmbuild --define "_topdir $rpmtop" -bb "$rpmtop/SPECS/latticra.spec"' "$runner"

require_contains 'require_payload_line' "$runner"
require_contains "require_payload_line '/usr/bin/latticra'" "$runner"
require_contains "require_payload_line '/usr/share/doc/latticra/README.md'" "$runner"
require_contains "require_no_payload_pattern '^/etc/latticra(/|$)'" "$runner"
require_contains "require_no_payload_pattern '^/usr/lib/systemd/system/latticra\\.service$'" "$runner"
require_contains "require_no_payload_pattern '^/usr/lib/modules(/|$)'" "$runner"
require_contains "require_no_payload_pattern '^/boot/latticra(/|$)'" "$runner"
require_contains "require_no_payload_pattern '^/usr/share/selinux(/|$)'" "$runner"
require_contains "require_no_payload_pattern '^/usr/sbin/latticra$'" "$runner"
require_contains 'require_payload_only_expected_surfaces' "$runner"

require_contains 'sudo rpm -Uvh --nodeps "$rpm_path"' "$runner"
require_contains 'sudo rpm -e "$name"' "$runner"
require_contains 'rpm -V "$name"' "$runner"
require_contains '/usr/bin/latticra --status' "$runner"
require_contains '/usr/bin/latticra --version' "$runner"
require_contains '/usr/bin/latticra --report' "$runner"
require_contains '/usr/bin/latticra --prevention-research' "$runner"
require_contains '/usr/bin/latticra --prevention-boundary' "$runner"
require_contains '/usr/bin/latticra --prevention-method sql' "$runner"
require_contains '/usr/bin/latticra --invalid' "$runner"
require_contains 'invalid CLI command exited with $invalid_status instead of 2' "$runner"
require_contains 'usage: latticra [--status|--version|--report|--prevention-research|--prevention-boundary|--prevention-method <id>]' "$runner"
require_contains 'LATTICRA PREVENTION RESEARCH REPORT' "$runner"
require_contains 'LATTICRA PREVENTION BOUNDARY REPORT' "$runner"
require_contains 'LATTICRA PREVENTION METHOD' "$runner"
require_contains 'method_id=sql' "$runner"
require_contains 'source=owasp-sql-injection' "$runner"
require_contains 'prevention_method_matrix_version=1' "$runner"
require_contains 'method_nosql=driver-structured-query-objects' "$runner"
require_contains 'method_ldap=ldap-filter-or-dn-context-encoding' "$runner"
require_contains 'xml_external_entities_disabled_required=1' "$runner"
require_contains 'boundary_inventory_version=1' "$runner"
require_contains 'boundary_count=8' "$runner"
require_contains 'boundary_server_fetch=ssrf' "$runner"
require_contains 'source_sink_pairing_required=1' "$runner"
require_contains 'deny_before_boundary_required=1' "$runner"
require_contains 'adversarial_fixture_required=1' "$runner"
require_contains 'cli_prevention_research_output_recorded=1' "$runner"
require_contains 'cli_prevention_boundary_output_recorded=1' "$runner"
require_contains 'cli_prevention_method_output_recorded=1' "$runner"

require_contains 'FEDORA VM CLI PAYLOAD REPEATABILITY LANE' "$runner"
require_contains 'validation_status=ok' "$runner"
require_contains 'repeatability_validation_status=ok' "$runner"
require_contains 'transcript_kind=disposable-vm-cli-payload-repeatability' "$runner"
require_contains 'prior_cli_payload_evidence_recorded=1' "$runner"
require_contains 'source_tree_revision=$source_tree_revision' "$runner"
require_contains 'fedora_kernel_version=$(uname -r)' "$runner"
require_contains 'spec_checksum=$spec_checksum' "$runner"
require_contains 'source_archive_checksum=$source_archive_checksum' "$runner"
require_contains 'rpm_nevra=$rpm_nevra' "$runner"
require_contains 'rpm_payload_matches_expected_cli_surfaces=1' "$runner"
require_contains 'validated_cli_mode_still_no_effect=1' "$runner"
require_contains 'validated_runtime_behavior_still_disabled=1' "$runner"
require_contains 'validated_non_claims_preserved=1' "$runner"
require_contains 'second_disposable_vm_cli_validation_completed=1' "$runner"
require_contains 'cli_payload_repeatability_evidence_present=1' "$runner"
require_contains 'host_install_ready_for_cli_payload=1' "$runner"
require_contains 'production_installer_ready=0' "$runner"
require_contains 'fedora_distribution_ready=0' "$runner"
require_contains 'fedora_approval_claimed=0' "$runner"
require_contains 'daily_driver_install_ready=0' "$runner"
require_contains 'immutable_fedora_ready=0' "$runner"
require_contains 'evidence_level=9' "$runner"
require_contains "printf 'fedora_vm_cli_payload_repeatability_lane: ok" "$runner"

require_contains 'Status: implemented runner plan' "$doc"
require_contains 'fedora_vm_cli_payload_repeatability_runner_present=1' "$doc"
require_contains 'repeatability_runner_manual_only=1' "$doc"
require_contains 'ci_auto_repeatability_validation_allowed=0' "$doc"
require_contains 'Capture reviewed Fedora VM CLI payload repeatability transcript evidence' "$doc"

require_contains 'Status: runner/status alignment' "$status"
require_contains 'fedora_vm_cli_payload_repeatability_transcript_contract_present=1' "$status"
require_contains 'fedora_vm_cli_payload_repeatability_runner_plan_present=1' "$status"
require_contains 'fedora_vm_cli_payload_repeatability_runner_present=1' "$status"
require_contains 'repeatability_runner_manual_only=1' "$status"
require_contains 'ci_auto_repeatability_validation_allowed=0' "$status"
require_contains 'second_disposable_vm_cli_validation_completed=0' "$status"
require_contains 'cli_payload_repeatability_evidence_present=0' "$status"
require_contains 'host_install_ready_for_cli_payload=1' "$status"
require_contains 'production_installer_ready=0' "$status"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-runner.sh' "$status"
require_contains 'Capture reviewed Fedora VM CLI payload repeatability transcript evidence' "$status"

require_contains 'fedora_vm_cli_payload_repeatability_runner_present=1' "$plan_status"
require_contains 'repeatability_runner_manual_only=1' "$plan_status"
require_contains 'ci_auto_repeatability_validation_allowed=0' "$plan_status"

require_contains 'FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_RUNNER_STATUS.md' "$index"
require_contains 'Current Fedora VM CLI payload repeatability runner checkpoint' "$index"
require_contains 'fedora_vm_cli_payload_repeatability_runner_present=1' "$index"
require_contains 'repeatability_runner_manual_only=1' "$index"
require_contains 'ci_auto_repeatability_validation_allowed=0' "$index"
require_contains 'docs/status/FEDORA_VM_CLI_PAYLOAD_REPEATABILITY_RUNNER_STATUS.md' "$readme"
require_contains 'name: Fedora VM CLI Payload Repeatability Runner' "$workflow"
require_contains 'permissions:' "$workflow"
require_contains 'contents: read' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-fedora-vm-cli-payload-repeatability-runner.sh' "$workflow"
require_absent 'run-fedora-vm-cli-payload-repeatability-lane.sh' "$workflow"

printf 'fedora_vm_cli_payload_repeatability_runner: ok\n'
