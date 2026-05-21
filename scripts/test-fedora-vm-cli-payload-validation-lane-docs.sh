#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora vm cli payload validation lane docs: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora vm cli payload validation lane docs: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_absent() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'fedora vm cli payload validation lane docs: unexpected pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

doc='docs/FEDORA_VM_CLI_PAYLOAD_VALIDATION_LANE.md'
runner='scripts/run-fedora-vm-cli-payload-validation-lane.sh'
contract='docs/FEDORA_VM_CLI_TRANSCRIPT_CONTRACT.md'
workflow='.github/workflows/fedora-vm-cli-payload-validation-lane-docs.yml'
spec='packaging/fedora/latticra.spec'
cli='src/latticra_cli.c'
cli_guard='scripts/test-latticra-no-effect-cli-status-surface.sh'

require_file "$doc"
require_file "$runner"
require_file "$contract"
require_file "$workflow"
require_file "$spec"
require_file "$cli"
require_file "$cli_guard"
require_file docs/status/LATTICRA_NO_EFFECT_CLI_RPM_SPEC_UPDATE_STATUS.md
require_file docs/LATTICRA_NO_EFFECT_CLI_PACKAGING_CONTRACT_ALIGNMENT.md

sh -n "$runner"

require_contains 'Status: gated validation lane runner' "$doc"
require_contains 'Evidence level: 9 target' "$doc"
require_contains 'manual disposable Fedora VM validation' "$doc"
require_contains '/usr/bin/latticra' "$doc"
require_contains '/usr/share/doc/latticra/README.md' "$doc"
require_contains 'It must not run automatically in CI.' "$doc"
require_contains 'It must not run on a daily-driver system.' "$doc"
require_contains 'It must not run on a production host.' "$doc"
require_contains 'It must not run on an immutable Fedora target.' "$doc"
require_contains 'Fedora approval' "$doc"
require_contains 'Fedora distribution readiness' "$doc"
require_contains 'daily-driver readiness' "$doc"
require_contains 'immutable Fedora readiness' "$doc"
require_contains 'production installer readiness' "$doc"

require_contains 'LATTICRA_ALLOW_DISPOSABLE_VM_RPM_VALIDATION=1' "$doc"
require_contains 'LATTICRA_TARGET_IS_DISPOSABLE_FEDORA_VM=1' "$doc"
require_contains 'LATTICRA_TARGET_IS_DAILY_DRIVER=0' "$doc"
require_contains 'LATTICRA_TARGET_IS_PRODUCTION_HOST=0' "$doc"
require_contains 'LATTICRA_TARGET_IS_IMMUTABLE_FEDORA=0' "$doc"
require_contains 'LATTICRA_TARGET_HAS_CLEAN_SNAPSHOT=1' "$doc"
require_contains 'LATTICRA_TARGET_HAS_RECOVERY_PATH=1' "$doc"
require_contains 'LATTICRA_OPERATOR_CONSENT_RECORDED=1' "$doc"
require_contains 'ID=fedora' "$doc"
require_contains 'rpm_present=1' "$doc"
require_contains 'rpmbuild_present=1' "$doc"
require_contains 'cc_present=1' "$doc"
require_contains 'sudo_present=1' "$doc"
require_contains 'non-root operator account' "$doc"
require_contains 'uses `sudo` only for RPM installation and removal' "$doc"

require_contains 'src/latticra_cli.c' "$doc"
require_contains 'scripts/test-latticra-no-effect-cli-status-surface.sh' "$doc"
require_contains 'packaging/fedora/latticra.spec' "$doc"
require_contains 'docs/FEDORA_VM_CLI_TRANSCRIPT_CONTRACT.md' "$doc"
require_contains 'sh scripts/test-latticra-no-effect-cli-status-surface.sh' "$doc"

require_contains 'Build a local source archive from the current tree.' "$doc"
require_contains 'Build the local binary RPM with `rpmbuild`.' "$doc"
require_contains 'Confirm the payload contains `/usr/bin/latticra`.' "$doc"
require_contains 'Execute `latticra --status` without root.' "$doc"
require_contains 'Execute `latticra --version` without root.' "$doc"
require_contains 'Execute `latticra --report` without root.' "$doc"
require_contains 'Verify invalid CLI usage exits with code 2.' "$doc"
require_contains 'Confirm the CLI payload is absent after removal.' "$doc"
require_contains 'Confirm the README payload is absent after removal.' "$doc"
require_contains 'Emit a deterministic validation report.' "$doc"

require_contains '/etc/latticra' "$doc"
require_contains '/usr/lib/systemd/system/latticra.service' "$doc"
require_contains '/usr/lib/modules' "$doc"
require_contains '/boot/latticra' "$doc"
require_contains '/usr/share/selinux' "$doc"
require_contains '/usr/sbin/latticra' "$doc"
require_contains 'usage: latticra [--status|--version|--report]' "$doc"

require_contains 'FEDORA VM CLI PAYLOAD VALIDATION LANE' "$doc"
require_contains 'validation_status=ok' "$doc"
require_contains 'package_name=latticra' "$doc"
require_contains 'package_version_recorded=1' "$doc"
require_contains 'package_arch_recorded=1' "$doc"
require_contains 'disposable_vm_target_verified=1' "$doc"
require_contains 'snapshot_evidence_present=1' "$doc"
require_contains 'recovery_evidence_present=1' "$doc"
require_contains 'operator_consent_recorded=1' "$doc"
require_contains 'fedora_os_release_recorded=1' "$doc"
require_contains 'fedora_kernel_version_recorded=1' "$doc"
require_contains 'rpm_tooling_recorded=1' "$doc"
require_contains 'rpmbuild_tooling_recorded=1' "$doc"
require_contains 'fedora_spec_updated_for_cli=1' "$doc"
require_contains 'rpm_payload_expansion_performed=1' "$doc"
require_contains 'rpm_contains_compiled_c_binary=1' "$doc"
require_contains 'buildarch_noarch_removed=1' "$doc"
require_contains 'cli_status_surface_implemented=1' "$doc"
require_contains 'cli_status_surface_guarded_before_packaging=1' "$doc"
require_contains 'local_cli_guard_passed=1' "$doc"
require_contains 'local_rpm_built_from_current_tree=1' "$doc"
require_contains 'rpm_build_command_recorded=1' "$doc"
require_contains 'rpm_name_is_latticra=1' "$doc"
require_contains 'rpm_version_recorded=1' "$doc"
require_contains 'rpm_arch_recorded=1' "$doc"
require_contains 'rpm_path_recorded=1' "$doc"
require_contains 'rpm_metadata_recorded=1' "$doc"
require_contains 'rpm_payload_listing_recorded=1' "$doc"
require_contains 'rpm_payload_contains_cli_binary=1' "$doc"
require_contains 'rpm_payload_contains_readme=1' "$doc"
require_contains 'rpm_payload_contains_only_expected_surfaces=1' "$doc"
require_contains 'unexpected_runtime_surface_absent=1' "$doc"
require_contains 'install_command_recorded=1' "$doc"
require_contains 'installed_cli_binary_present=1' "$doc"
require_contains 'installed_readme_present=1' "$doc"
require_contains 'rpm_verify_completed=1' "$doc"
require_contains 'cli_status_command_recorded=1' "$doc"
require_contains 'cli_version_command_recorded=1' "$doc"
require_contains 'cli_report_command_recorded=1' "$doc"
require_contains 'cli_invalid_command_recorded=1' "$doc"
require_contains 'cli_no_root_required=1' "$doc"
require_contains 'cli_no_host_mutation_observed=1' "$doc"
require_contains 'cli_no_network_observed=1' "$doc"
require_contains 'cli_no_service_operation_observed=1' "$doc"
require_contains 'cli_no_kernel_operation_observed=1' "$doc"
require_contains 'cli_no_boot_operation_observed=1' "$doc"
require_contains 'cli_no_selinux_policy_operation_observed=1' "$doc"
require_contains 'post_removal_cli_absence_verified=1' "$doc"
require_contains 'post_removal_readme_absence_verified=1' "$doc"
require_contains 'disposable_vm_cli_validation_completed=1' "$doc"
require_contains 'host_install_ready_for_cli_payload=1' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'fedora_distribution_ready=0' "$doc"
require_contains 'fedora_approval_claimed=0' "$doc"
require_contains 'daily_driver_install_ready=0' "$doc"
require_contains 'immutable_fedora_ready=0' "$doc"
require_contains 'evidence_level=9' "$doc"

require_contains 'validation_runner_present=1' "$doc"
require_contains 'runner_manual_only=1' "$doc"
require_contains 'ci_auto_vm_cli_validation_allowed=0' "$doc"
require_contains 'disposable_vm_cli_validation_transcript_present=0' "$doc"
require_contains 'host_install_ready_for_cli_payload=0' "$doc"
require_contains 'sh scripts/run-fedora-vm-cli-payload-validation-lane.sh' "$doc"
require_contains 'fedora_vm_cli_payload_validation_lane: ok' "$doc"
require_contains 'sh scripts/test-fedora-vm-cli-payload-validation-lane-docs.sh' "$doc"
require_contains 'fedora_vm_cli_payload_validation_lane_docs: ok' "$doc"
require_contains 'Add disposable Fedora VM CLI payload validation status alignment' "$doc"

require_contains 'require_flag LATTICRA_ALLOW_DISPOSABLE_VM_RPM_VALIDATION 1' "$runner"
require_contains 'require_flag LATTICRA_TARGET_IS_DISPOSABLE_FEDORA_VM 1' "$runner"
require_contains 'require_flag LATTICRA_TARGET_IS_DAILY_DRIVER 0' "$runner"
require_contains 'require_flag LATTICRA_TARGET_IS_PRODUCTION_HOST 0' "$runner"
require_contains 'require_flag LATTICRA_TARGET_IS_IMMUTABLE_FEDORA 0' "$runner"
require_contains 'require_flag LATTICRA_TARGET_HAS_CLEAN_SNAPSHOT 1' "$runner"
require_contains 'require_flag LATTICRA_TARGET_HAS_RECOVERY_PATH 1' "$runner"
require_contains 'require_flag LATTICRA_OPERATOR_CONSENT_RECORDED 1' "$runner"
require_contains '[ "${ID:-}" = "fedora" ]' "$runner"
require_contains 'run as a non-root operator account' "$runner"
require_contains 'require_command sudo' "$runner"
require_contains 'require_command rpmbuild' "$runner"
require_contains 'require_command rpm' "$runner"
require_contains 'sh scripts/test-latticra-no-effect-cli-status-surface.sh' "$runner"
require_contains 'rpmbuild --define "_topdir $rpmtop" -bb "$rpmtop/SPECS/latticra.spec"' "$runner"
require_contains "require_payload_line '/usr/bin/latticra'" "$runner"
require_contains "require_payload_line '/usr/share/doc/latticra/README.md'" "$runner"
require_contains 'require_payload_only_expected_surfaces' "$runner"
require_contains 'sudo rpm -Uvh --nodeps "$rpm_path"' "$runner"
require_contains '/usr/bin/latticra --status' "$runner"
require_contains '/usr/bin/latticra --version' "$runner"
require_contains '/usr/bin/latticra --report' "$runner"
require_contains '/usr/bin/latticra --invalid' "$runner"
require_contains 'invalid_status' "$runner"
require_contains 'sudo rpm -e "$name"' "$runner"
require_contains 'if [ -e /usr/bin/latticra ]; then' "$runner"
require_contains 'if [ -e /usr/share/doc/latticra/README.md ]; then' "$runner"
require_contains 'FEDORA VM CLI PAYLOAD VALIDATION LANE' "$runner"
require_contains 'host_install_ready_for_cli_payload=1' "$runner"
require_contains 'production_installer_ready=0' "$runner"
require_contains 'fedora_distribution_ready=0' "$runner"
require_contains 'fedora_approval_claimed=0' "$runner"
require_contains 'daily_driver_install_ready=0' "$runner"
require_contains 'immutable_fedora_ready=0' "$runner"
require_contains 'fedora_vm_cli_payload_validation_lane: ok' "$runner"

require_contains 'FEDORA VM CLI PAYLOAD VALIDATION TRANSCRIPT' "$contract"
require_contains 'Add disposable Fedora VM CLI payload validation lane runner' "$contract"
require_contains 'fedora_spec_updated_for_cli=1' docs/status/LATTICRA_NO_EFFECT_CLI_RPM_SPEC_UPDATE_STATUS.md
require_contains 'rpm_payload_expansion_performed=1' docs/status/LATTICRA_NO_EFFECT_CLI_RPM_SPEC_UPDATE_STATUS.md
require_contains 'rpm_payload_validated=0' docs/status/LATTICRA_NO_EFFECT_CLI_RPM_SPEC_UPDATE_STATUS.md
require_contains '%{_bindir}/latticra' "$spec"
require_contains 'LATTICRA STATUS REPORT' "$cli"
require_contains 'latticra_no_effect_cli_status_surface: ok' "$cli_guard"

require_contains 'name: Fedora VM CLI Payload Validation Lane Docs' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'sh scripts/test-fedora-vm-cli-payload-validation-lane-docs.sh' "$workflow"
require_absent 'sh scripts/run-fedora-vm-cli-payload-validation-lane.sh' "$workflow"

printf 'fedora_vm_cli_payload_validation_lane_docs: ok\n'
