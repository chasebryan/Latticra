#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra no-effect cli payload contract: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra no-effect cli payload contract: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

doc='docs/LATTICRA_NO_EFFECT_CLI_PAYLOAD_CONTRACT.md'
readme='README.md'
evidence='docs/status/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_EVIDENCE_STATUS.md'
readme_status='docs/status/FEDORA_DISPOSABLE_VM_RPM_README_ALIGNMENT_STATUS.md'

require_file "$doc"
require_file "$readme"
require_file "$evidence"
require_file "$readme_status"
require_file packaging/fedora/latticra.spec

require_contains 'Status: contract record' "$doc"
require_contains 'Evidence level: 9 target, contract only' "$doc"
require_contains 'future no-effect `/usr/bin/latticra` CLI payload' "$doc"
require_contains 'This is a contract only.' "$doc"
require_contains 'It does not implement `/usr/bin/latticra`.' "$doc"
require_contains 'It does not update the Fedora RPM spec.' "$doc"
require_contains 'It does not add a binary payload to the RPM.' "$doc"
require_contains 'It does not install, remove, or validate a new RPM.' "$doc"
require_contains 'It does not run the disposable Fedora VM validation lane.' "$doc"
require_contains 'It does not grant runtime authority.' "$doc"

require_contains 'LATTICRA NO-EFFECT CLI PAYLOAD CONTRACT' "$doc"
require_contains 'cli_payload_contract_version=1' "$doc"
require_contains 'cli_binary_path=/usr/bin/latticra' "$doc"
require_contains 'cli_payload_planned=1' "$doc"
require_contains 'cli_payload_implemented=0' "$doc"
require_contains 'cli_rpm_payload_validated=0' "$doc"
require_contains 'operator_review_required=1' "$doc"

require_contains 'current_validated_package=latticra-0.0.0-0.1.local.fc44.noarch.rpm' "$doc"
require_contains 'current_validated_payload=/usr/share/doc/latticra/README.md' "$doc"
require_contains 'current_validated_payload_remains_documentation_only=1' "$doc"
require_contains 'current_disposable_vm_rpm_evidence_remains_valid=1' "$doc"
require_contains 'does not currently validate' "$doc"
require_contains '/usr/bin/latticra' "$doc"

require_contains 'cli_report_only=1' "$doc"
require_contains 'cli_runtime_behavior_allowed=0' "$doc"
require_contains 'cli_host_mutation_allowed=0' "$doc"
require_contains 'cli_network_allowed=0' "$doc"
require_contains 'cli_root_required=0' "$doc"
require_contains 'cli_file_write_allowed=0' "$doc"
require_contains 'cli_file_read_required=0' "$doc"
require_contains 'cli_service_operation_allowed=0' "$doc"
require_contains 'cli_kernel_operation_allowed=0' "$doc"
require_contains 'cli_package_manager_allowed=0' "$doc"
require_contains 'cli_boot_operation_allowed=0' "$doc"
require_contains 'cli_selinux_policy_operation_allowed=0' "$doc"
require_contains 'cli_effect_authority_default=denied' "$doc"
require_contains 'cli_exit_status_deterministic=1' "$doc"

require_contains 'latticra --status' "$doc"
require_contains 'latticra --version' "$doc"
require_contains 'latticra --report' "$doc"
require_contains 'No command may execute Lat' "$doc"
require_contains 'execute LIR' "$doc"
require_contains 'mutate host state' "$doc"
require_contains 'invoke services' "$doc"
require_contains 'invoke package managers' "$doc"
require_contains 'touch the boot path' "$doc"
require_contains 'load kernel modules' "$doc"
require_contains 'change SELinux policy' "$doc"
require_contains 'open network connections' "$doc"
require_contains 'require root' "$doc"

require_contains 'LATTICRA STATUS REPORT' "$doc"
require_contains 'project=latticra' "$doc"
require_contains 'mode=no-effect' "$doc"
require_contains 'runtime_behavior=disabled' "$doc"
require_contains 'host_mutation=0' "$doc"
require_contains 'network=0' "$doc"
require_contains 'kernel_operation=0' "$doc"
require_contains 'service_operation=0' "$doc"
require_contains 'package_manager_operation=0' "$doc"
require_contains 'boot_operation=0' "$doc"
require_contains 'selinux_policy_operation=0' "$doc"
require_contains 'effect_authority=denied' "$doc"

require_contains 'implementation_language=C' "$doc"
require_contains 'external_runtime_dependencies=0' "$doc"
require_contains 'dynamic_network_dependency=0' "$doc"
require_contains 'privileged_execution_required=0' "$doc"
require_contains 'fixed_output_schema=1' "$doc"
require_contains 'deterministic_report_order=1' "$doc"

require_contains '/usr/share/doc/latticra/README.md' "$doc"
require_contains '/etc/latticra' "$doc"
require_contains '/usr/lib/systemd/system/latticra.service' "$doc"
require_contains '/usr/lib/modules' "$doc"
require_contains '/boot/latticra' "$doc"

require_contains 'cli_binary_present_after_install=1' "$doc"
require_contains 'cli_status_command_recorded=1' "$doc"
require_contains 'cli_version_command_recorded=1' "$doc"
require_contains 'cli_report_command_recorded=1' "$doc"
require_contains 'cli_status_output_matches_contract=1' "$doc"
require_contains 'cli_no_root_required=1' "$doc"
require_contains 'cli_no_host_mutation_observed=1' "$doc"
require_contains 'cli_no_network_observed=1' "$doc"
require_contains 'cli_removed_after_rpm_removal=1' "$doc"
require_contains 'post_removal_cli_absence_verified=1' "$doc"
require_contains 'package build, RPM install, RPM verification, RPM removal, and post-removal absence verification' "$doc"

require_contains 'cli_payload_contract_present=1' "$doc"
require_contains 'disposable_vm_cli_validation_completed=0' "$doc"
require_contains 'host_install_ready_for_cli_payload=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'fedora_distribution_ready=0' "$doc"
require_contains 'fedora_approval_claimed=0' "$doc"
require_contains 'daily_driver_install_ready=0' "$doc"
require_contains 'immutable_fedora_ready=0' "$doc"

require_contains 'sh scripts/test-latticra-no-effect-cli-payload-contract.sh' "$doc"
require_contains 'latticra_no_effect_cli_payload_contract: ok' "$doc"
require_contains 'Implement no-effect Latticra CLI status surface' "$doc"
require_contains 'should not update Fedora validation status until a real disposable Fedora VM RPM validation transcript exists' "$doc"

require_contains 'This contract is not a CLI implementation.' "$doc"
require_contains 'It is not RPM payload expansion.' "$doc"
require_contains 'It is not disposable Fedora VM validation of `/usr/bin/latticra`.' "$doc"
require_contains 'It is not production readiness' "$doc"
require_contains 'Fedora approval' "$doc"
require_contains 'Fedora distribution readiness' "$doc"
require_contains 'daily-driver safety' "$doc"
require_contains 'immutable Fedora readiness' "$doc"
require_contains 'runtime behavior' "$doc"
require_contains 'Lat execution' "$doc"
require_contains 'LIR execution' "$doc"
require_contains 'service management' "$doc"
require_contains 'kernel integration' "$doc"
require_contains 'update safety' "$doc"
require_contains 'recovery safety' "$doc"
require_contains 'malware prevention' "$doc"
require_contains 'ransomware prevention' "$doc"
require_contains 'sandboxing' "$doc"
require_contains 'production installer claim' "$doc"

printf 'latticra_no_effect_cli_payload_contract: ok\n'
