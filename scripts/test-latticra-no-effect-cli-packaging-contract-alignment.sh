#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra no-effect cli packaging contract alignment: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra no-effect cli packaging contract alignment: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_absent() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'latticra no-effect cli packaging contract alignment: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

doc='docs/LATTICRA_NO_EFFECT_CLI_PACKAGING_CONTRACT_ALIGNMENT.md'
contract='docs/LATTICRA_NO_EFFECT_CLI_PAYLOAD_CONTRACT.md'
implementation='docs/LATTICRA_NO_EFFECT_CLI_STATUS_SURFACE_IMPLEMENTATION.md'
cli='src/latticra_cli.c'
cli_guard='scripts/test-latticra-no-effect-cli-status-surface.sh'
spec='packaging/fedora/latticra.spec'

require_file "$doc"
require_file "$contract"
require_file "$implementation"
require_file "$cli"
require_file "$cli_guard"
require_file "$spec"

require_contains 'Status: contract alignment record' "$doc"
require_contains 'Evidence level: 7 packaging alignment, contract only' "$doc"
require_contains 'future Fedora RPM payload transition for the no-effect `latticra` CLI' "$doc"
require_contains 'This is contract/status alignment only.' "$doc"
require_contains 'It does not update `packaging/fedora/latticra.spec`.' "$doc"
require_contains 'It does not add `/usr/bin/latticra` to the RPM payload.' "$doc"
require_contains 'It does not build a new RPM.' "$doc"
require_contains 'It does not install or remove an RPM.' "$doc"
require_contains 'It does not run disposable Fedora VM validation.' "$doc"
require_contains 'It does not claim host install readiness for the CLI payload.' "$doc"

require_contains 'LATTICRA NO-EFFECT CLI PACKAGING CONTRACT ALIGNMENT' "$doc"
require_contains 'packaging_alignment_version=1' "$doc"
require_contains 'cli_payload_contract_present=1' "$doc"
require_contains 'cli_status_surface_implemented=1' "$doc"
require_contains 'cli_packaging_alignment_present=1' "$doc"
require_contains 'fedora_spec_updated_for_cli=0' "$doc"
require_contains 'rpm_payload_expansion_performed=0' "$doc"
require_contains 'rpm_payload_validated=0' "$doc"

require_contains 'current_validated_package=latticra-0.0.0-0.1.local.fc44.noarch.rpm' "$doc"
require_contains 'current_validated_payload=/usr/share/doc/latticra/README.md' "$doc"
require_contains 'current_validated_payload_remains_documentation_only=1' "$doc"
require_contains 'current_disposable_vm_rpm_evidence_remains_valid=1' "$doc"
require_contains 'BuildArch: noarch' "$doc"
require_contains '%doc %{_docdir}/%{name}/README.md' "$doc"

require_contains '/usr/bin/latticra' "$doc"
require_contains '/usr/share/doc/latticra/README.md' "$doc"
require_contains 'future_rpm_contains_compiled_c_binary=1' "$doc"
require_contains 'future_rpm_buildarch_must_not_be_noarch=1' "$doc"
require_contains 'future_spec_must_remove_noarch_claim=1' "$doc"
require_contains 'future_cli_binary_install_mode=0755' "$doc"
require_contains 'future_doc_install_mode=0644' "$doc"
require_contains 'must not continue to present the payload as architecture-independent noarch packaging' "$doc"

require_contains 'src/latticra_cli.c_present=1' "$doc"
require_contains 'cli_local_guard_present=1' "$doc"
require_contains 'cli_local_guard_passes_before_packaging=1' "$doc"
require_contains 'fedora_spec_installs_cli_binary=1' "$doc"
require_contains 'fedora_spec_installs_readme=1' "$doc"
require_contains 'fedora_spec_does_not_install_services=1' "$doc"
require_contains 'fedora_spec_does_not_install_kernel_modules=1' "$doc"
require_contains 'fedora_spec_does_not_install_boot_files=1' "$doc"
require_contains 'fedora_spec_does_not_install_selinux_policy=1' "$doc"
require_contains 'fedora_spec_does_not_enable_services=1' "$doc"
require_contains 'fedora_spec_does_not_run_network_operations=1' "$doc"

require_contains '/etc/latticra' "$doc"
require_contains '/usr/lib/systemd/system/latticra.service' "$doc"
require_contains '/usr/lib/modules' "$doc"
require_contains '/boot/latticra' "$doc"
require_contains '/usr/share/selinux' "$doc"

require_contains 'expanded_payload_validation_transcript_present=1' "$doc"
require_contains 'cli_binary_present_after_install=1' "$doc"
require_contains 'cli_status_command_recorded=1' "$doc"
require_contains 'cli_version_command_recorded=1' "$doc"
require_contains 'cli_report_command_recorded=1' "$doc"
require_contains 'cli_status_output_matches_contract=1' "$doc"
require_contains 'cli_no_root_required=1' "$doc"
require_contains 'cli_no_host_mutation_observed=1' "$doc"
require_contains 'cli_no_network_observed=1' "$doc"
require_contains 'rpm_verify_completed=1' "$doc"
require_contains 'removal_validation_performed=1' "$doc"
require_contains 'cli_removed_after_rpm_removal=1' "$doc"
require_contains 'post_removal_cli_absence_verified=1' "$doc"

require_contains 'disposable_vm_cli_validation_completed=0' "$doc"
require_contains 'host_install_ready_for_cli_payload=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'fedora_distribution_ready=0' "$doc"
require_contains 'fedora_approval_claimed=0' "$doc"
require_contains 'daily_driver_install_ready=0' "$doc"
require_contains 'immutable_fedora_ready=0' "$doc"

require_contains 'sh scripts/test-latticra-no-effect-cli-packaging-contract-alignment.sh' "$doc"
require_contains 'latticra_no_effect_cli_packaging_contract_alignment: ok' "$doc"
require_contains 'Update Fedora RPM spec for no-effect CLI payload without claiming VM validation' "$doc"
require_contains 'This alignment is not an RPM spec update.' "$doc"
require_contains 'It is not RPM payload expansion.' "$doc"
require_contains 'It is not installation evidence for `/usr/bin/latticra`.' "$doc"
require_contains 'It is not disposable Fedora VM validation of the CLI payload.' "$doc"
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
require_contains 'SELinux policy integration' "$doc"
require_contains 'update safety' "$doc"
require_contains 'recovery safety' "$doc"
require_contains 'malware prevention' "$doc"
require_contains 'ransomware prevention' "$doc"
require_contains 'sandboxing' "$doc"
require_contains 'production installer claim' "$doc"

require_contains 'cli_payload_implemented=0' "$contract"
require_contains 'latticra_no_effect_cli_status_surface: ok' "$implementation"
require_contains 'LATTICRA STATUS REPORT' "$cli"
require_contains 'latticra_no_effect_cli_status_surface: ok' "$cli_guard"

require_contains 'BuildArch:      noarch' "$spec"
require_contains 'install -m 0644 README.md %{buildroot}%{_docdir}/%{name}/README.md' "$spec"
require_contains '%doc %{_docdir}/%{name}/README.md' "$spec"
require_absent 'src/latticra_cli.c' "$spec"
require_absent '%{_bindir}/latticra' "$spec"
require_absent '/usr/bin/latticra' "$spec"
require_absent 'install -m 0755' "$spec"
require_absent 'systemctl' "$spec"
require_absent '/usr/lib/systemd/system' "$spec"
require_absent '/usr/lib/modules' "$spec"
require_absent '/boot/latticra' "$spec"
require_absent '/usr/share/selinux' "$spec"

printf 'latticra_no_effect_cli_packaging_contract_alignment: ok\n'
