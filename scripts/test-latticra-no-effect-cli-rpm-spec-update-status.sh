#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra no-effect cli rpm spec update status: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra no-effect cli rpm spec update status: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_absent() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'latticra no-effect cli rpm spec update status: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status='docs/status/LATTICRA_NO_EFFECT_CLI_RPM_SPEC_UPDATE_STATUS.md'
alignment='docs/LATTICRA_NO_EFFECT_CLI_PACKAGING_CONTRACT_ALIGNMENT.md'
spec='packaging/fedora/latticra.spec'
cli='src/latticra_cli.c'
cli_guard='scripts/test-latticra-no-effect-cli-status-surface.sh'
packaging_guard='scripts/test-latticra-no-effect-cli-packaging-contract-alignment.sh'
static_guard='scripts/test-fedora-local-rpm-static-validation.sh'

require_file "$status"
require_file "$alignment"
require_file "$spec"
require_file "$cli"
require_file "$cli_guard"
require_file "$packaging_guard"
require_file "$static_guard"

require_contains 'Status: packaging/spec update status' "$status"
require_contains 'Date: 2026-05-21' "$status"
require_contains 'adding the no-effect CLI payload to the local Fedora RPM spec' "$status"
require_contains 'spec update only' "$status"
require_contains 'not a completed RPM build transcript' "$status"
require_contains 'not disposable Fedora VM validation of the expanded payload' "$status"
require_contains 'not host install readiness for the CLI payload' "$status"

require_contains 'fedora_spec_updated_for_cli=1' "$status"
require_contains 'rpm_payload_expansion_performed=1' "$status"
require_contains 'rpm_contains_compiled_c_binary=1' "$status"
require_contains 'buildarch_noarch_removed=1' "$status"
require_contains 'cli_status_surface_guarded_before_packaging=1' "$status"
require_contains 'cli_binary_compiled_in_build_section=1' "$status"
require_contains 'cli_binary_installed_to_bindir=1' "$status"
require_contains 'readme_installed_to_docdir=1' "$status"
require_contains 'rpm_payload_validated=0' "$status"

require_contains '/usr/bin/latticra' "$status"
require_contains '/usr/share/doc/latticra/README.md' "$status"
require_contains 'sh scripts/test-latticra-no-effect-cli-status-surface.sh' "$status"
require_contains 'cc %{optflags} -std=c99 -Wall -Wextra -Werror -pedantic src/latticra_cli.c -o build/latticra' "$status"
require_contains 'install -m 0755 build/latticra %{buildroot}%{_bindir}/latticra' "$status"
require_contains 'install -m 0644 README.md %{buildroot}%{_docdir}/%{name}/README.md' "$status"
require_contains '%{_bindir}/latticra' "$status"
require_contains '%doc %{_docdir}/%{name}/README.md' "$status"

require_contains '/etc/latticra=absent' "$status"
require_contains '/usr/lib/systemd/system/latticra.service=absent' "$status"
require_contains '/usr/lib/modules=absent' "$status"
require_contains '/boot/latticra=absent' "$status"
require_contains '/usr/share/selinux=absent' "$status"
require_contains 'systemctl=absent' "$status"
require_contains 'rpm_scriptlets=absent' "$status"

require_contains 'validated_package=latticra-0.0.0-0.1.local.fc44.noarch.rpm' "$status"
require_contains 'validated_payload=/usr/share/doc/latticra/README.md' "$status"
require_contains 'historical_disposable_vm_rpm_evidence_remains_limited=1' "$status"
require_contains 'That evidence does not validate `/usr/bin/latticra`.' "$status"

require_contains 'rpm_build_transcript_present=0' "$status"
require_contains 'disposable_vm_cli_validation_completed=0' "$status"
require_contains 'host_install_ready_for_cli_payload=0' "$status"
require_contains 'production_installer_ready=0' "$status"
require_contains 'fedora_distribution_ready=0' "$status"
require_contains 'fedora_approval_claimed=0' "$status"
require_contains 'daily_driver_install_ready=0' "$status"
require_contains 'immutable_fedora_ready=0' "$status"

require_contains 'sh scripts/test-latticra-no-effect-cli-rpm-spec-update-status.sh' "$status"
require_contains 'latticra_no_effect_cli_rpm_spec_update_status: ok' "$status"
require_contains 'Add disposable Fedora VM CLI payload validation transcript contract' "$status"
require_contains 'This status record is not a completed RPM build transcript.' "$status"
require_contains 'It is not RPM install evidence.' "$status"
require_contains 'It is not disposable Fedora VM validation of the CLI payload.' "$status"
require_contains 'It is not host install readiness for the CLI payload.' "$status"
require_contains 'It is not production readiness' "$status"
require_contains 'Fedora approval' "$status"
require_contains 'Fedora distribution readiness' "$status"
require_contains 'daily-driver safety' "$status"
require_contains 'immutable Fedora readiness' "$status"
require_contains 'runtime behavior' "$status"
require_contains 'Lat execution' "$status"
require_contains 'LIR execution' "$status"
require_contains 'service management' "$status"
require_contains 'kernel integration' "$status"
require_contains 'SELinux policy integration' "$status"
require_contains 'update safety' "$status"
require_contains 'recovery safety' "$status"
require_contains 'malware prevention' "$status"
require_contains 'ransomware prevention' "$status"
require_contains 'sandboxing' "$status"
require_contains 'production installer claim' "$status"

require_contains 'fedora_spec_updated_for_cli=1' "$alignment"
require_contains 'rpm_payload_expansion_performed=1' "$alignment"
require_contains 'rpm_payload_validated=0' "$alignment"
require_contains 'Add disposable Fedora VM CLI payload validation transcript contract' "$alignment"

require_absent 'BuildArch:      noarch' "$spec"
require_contains 'sh scripts/test-latticra-no-effect-cli-status-surface.sh' "$spec"
require_contains 'cc %{optflags} -std=c99 -Wall -Wextra -Werror -pedantic src/latticra_cli.c -o build/latticra' "$spec"
require_contains 'install -m 0755 build/latticra %{buildroot}%{_bindir}/latticra' "$spec"
require_contains '%{_bindir}/latticra' "$spec"
require_absent 'systemctl' "$spec"
require_absent '/usr/lib/systemd/system' "$spec"
require_absent '/usr/lib/modules' "$spec"
require_absent '/boot/latticra' "$spec"
require_absent '/usr/share/selinux' "$spec"
require_absent '/etc/latticra' "$spec"

printf 'latticra_no_effect_cli_rpm_spec_update_status: ok\n'
