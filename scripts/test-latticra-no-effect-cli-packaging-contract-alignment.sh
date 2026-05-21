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

require_contains 'Status: packaging/spec alignment record' "$doc"
require_contains 'Evidence level: 7 packaging alignment, local guard only' "$doc"
require_contains 'Fedora RPM spec transition for the no-effect `latticra` CLI payload' "$doc"
require_contains 'This is packaging/spec alignment only.' "$doc"
require_contains 'It updates `packaging/fedora/latticra.spec` for the CLI payload.' "$doc"
require_contains 'It does not build a new RPM in CI.' "$doc"
require_contains 'It does not install or remove an RPM.' "$doc"
require_contains 'It does not run disposable Fedora VM validation.' "$doc"
require_contains 'It does not claim host install readiness for the CLI payload.' "$doc"

require_contains 'LATTICRA NO-EFFECT CLI PACKAGING CONTRACT ALIGNMENT' "$doc"
require_contains 'packaging_alignment_version=2' "$doc"
require_contains 'cli_payload_contract_present=1' "$doc"
require_contains 'cli_status_surface_implemented=1' "$doc"
require_contains 'cli_packaging_alignment_present=1' "$doc"
require_contains 'fedora_spec_updated_for_cli=1' "$doc"
require_contains 'rpm_payload_expansion_performed=1' "$doc"
require_contains 'rpm_payload_validated=0' "$doc"

require_contains 'validated_package=latticra-0.0.0-0.1.local.fc44.noarch.rpm' "$doc"
require_contains 'validated_payload=/usr/share/doc/latticra/README.md' "$doc"
require_contains 'validated_payload_remains_documentation_only=1' "$doc"
require_contains 'historical_disposable_vm_rpm_evidence_remains_limited=1' "$doc"
require_contains 'That historical evidence does not validate the new CLI payload.' "$doc"

require_contains '/usr/bin/latticra' "$doc"
require_contains '/usr/share/doc/latticra/README.md' "$doc"
require_contains 'BuildArch: noarch' "$doc"
require_contains 'rpm_contains_compiled_c_binary=1' "$doc"
require_contains 'buildarch_noarch_removed=1' "$doc"
require_contains 'cli_binary_install_mode=0755' "$doc"
require_contains 'doc_install_mode=0644' "$doc"

require_contains 'sh scripts/test-latticra-no-effect-cli-status-surface.sh' "$doc"
require_contains 'cc %{optflags} -std=c99 -Wall -Wextra -Werror -pedantic src/latticra_cli.c -o build/latticra' "$doc"
require_contains 'install -m 0755 build/latticra %{buildroot}%{_bindir}/latticra' "$doc"
require_contains 'install -m 0644 README.md %{buildroot}%{_docdir}/%{name}/README.md' "$doc"
require_contains '%{_bindir}/latticra' "$doc"
require_contains '%doc %{_docdir}/%{name}/README.md' "$doc"

require_contains '/etc/latticra' "$doc"
require_contains '/usr/lib/systemd/system/latticra.service' "$doc"
require_contains '/usr/lib/modules' "$doc"
require_contains '/boot/latticra' "$doc"
require_contains '/usr/share/selinux' "$doc"
require_contains 'must also avoid service activation, package-manager actions, network actions, boot changes, kernel-module installation, and SELinux policy installation' "$doc"

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
require_contains 'Add disposable Fedora VM CLI payload validation transcript contract' "$doc"
require_contains 'This alignment is not a completed RPM build transcript.' "$doc"
require_contains 'It is not installation evidence for `/usr/bin/latticra`.' "$doc"
require_contains 'It is not disposable Fedora VM validation of the CLI payload.' "$doc"
require_contains 'It is not host install readiness for the CLI payload.' "$doc"
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

require_contains 'latticra --status' "$contract"
require_contains 'latticra_no_effect_cli_status_surface: ok' "$implementation"
require_contains 'LATTICRA STATUS REPORT' "$cli"
require_contains 'latticra_no_effect_cli_status_surface: ok' "$cli_guard"

require_absent 'BuildArch:      noarch' "$spec"
require_contains 'sh scripts/test-latticra-no-effect-cli-status-surface.sh' "$spec"
require_contains 'mkdir -p build' "$spec"
require_contains 'cc %{optflags} -std=c99 -Wall -Wextra -Werror -pedantic src/latticra_cli.c -o build/latticra' "$spec"
require_contains 'mkdir -p %{buildroot}%{_bindir}' "$spec"
require_contains 'install -m 0755 build/latticra %{buildroot}%{_bindir}/latticra' "$spec"
require_contains 'install -m 0644 README.md %{buildroot}%{_docdir}/%{name}/README.md' "$spec"
require_contains '%{_bindir}/latticra' "$spec"
require_contains '%doc %{_docdir}/%{name}/README.md' "$spec"
require_contains 'Add no-effect CLI binary to local RPM payload draft without claiming VM validation.' "$spec"
require_absent 'systemctl' "$spec"
require_absent '/usr/lib/systemd/system' "$spec"
require_absent '/usr/lib/modules' "$spec"
require_absent '/boot/latticra' "$spec"
require_absent '/usr/share/selinux' "$spec"
require_absent '/etc/latticra' "$spec"

printf 'latticra_no_effect_cli_packaging_contract_alignment: ok\n'
