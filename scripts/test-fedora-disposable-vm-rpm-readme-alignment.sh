#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora disposable vm rpm readme alignment: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora disposable vm rpm readme alignment: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

readme='README.md'
status='docs/status/FEDORA_DISPOSABLE_VM_RPM_README_ALIGNMENT_STATUS.md'
evidence='docs/status/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_EVIDENCE_STATUS.md'
cli_evidence='docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md'
index='docs/status/README.md'

require_file "$readme"
require_file "$status"
require_file "$evidence"
require_file "$cli_evidence"
require_file "$index"
require_file docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_LANE.md
require_file docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_TRANSCRIPT_CONTRACT.md

require_contains 'Fedora disposable VM RPM validation' "$readme"
require_contains 'two evidence-backed disposable Fedora VM validation records' "$readme"
require_contains 'disposable_vm_local_rpm_validation_completed=1' "$readme"
require_contains 'disposable_vm_cli_validation_completed=1' "$readme"
require_contains 'host_install_ready=1' "$readme"
require_contains 'host_install_ready_for_cli_payload=1' "$readme"
require_contains 'production_installer_ready=0' "$readme"
require_contains 'fedora_distribution_ready=0' "$readme"
require_contains 'fedora_approval_claimed=0' "$readme"
require_contains 'daily_driver_install_ready=0' "$readme"
require_contains 'immutable_fedora_ready=0' "$readme"
require_contains 'evidence_level=9' "$readme"
require_contains 'latticra-0.0.0-0.1.local.fc44.noarch.rpm' "$readme"
require_contains 'latticra-0.0.0-0.1.local.fc44.x86_64.rpm' "$readme"
require_contains '/usr/bin/latticra' "$readme"
require_contains '/usr/share/doc/latticra/README.md' "$readme"
require_contains 'RPM install, RPM verification, CLI status/version/report validation' "$readme"
require_contains 'does **not** mean Latticra is production ready' "$readme"
require_contains 'Fedora approved' "$readme"
require_contains 'Fedora distribution ready' "$readme"
require_contains 'daily-driver safe' "$readme"
require_contains 'immutable-Fedora ready' "$readme"
require_contains 'production installer' "$readme"
require_contains 'bootable OS replacement' "$readme"
require_contains 'security product' "$readme"
require_contains 'sandbox' "$readme"
require_contains 'malware/ransomware prevention system' "$readme"
require_contains 'FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md' "$readme"
require_contains 'FEDORA_VM_CLI_PAYLOAD_VALIDATION_STATUS.md' "$readme"
require_contains 'FEDORA_VM_CLI_PAYLOAD_VALIDATION_LANE.md' "$readme"
require_contains 'FEDORA_VM_CLI_TRANSCRIPT_CONTRACT.md' "$readme"
require_contains 'FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_EVIDENCE_STATUS.md' "$readme"
require_contains 'FEDORA_DISPOSABLE_VM_RPM_README_ALIGNMENT_STATUS.md' "$readme"
require_contains 'FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_LANE.md' "$readme"
require_contains 'FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_TRANSCRIPT_CONTRACT.md' "$readme"
require_contains 'The only install-readiness statements currently supported by evidence are disposable Fedora VM local RPM validation' "$readme"
require_contains 'disposable Fedora VM CLI payload validation for the local no-effect CLI RPM' "$readme"
require_contains 'Fedora disposable VM RPM README alignment is covered by:' "$readme"
require_contains 'sh scripts/test-fedora-disposable-vm-rpm-readme-alignment.sh' "$readme"

require_contains 'Status: README/status alignment' "$status"
require_contains 'disposable_vm_local_rpm_validation_completed=1' "$status"
require_contains 'host_install_ready=1' "$status"
require_contains 'production_installer_ready=0' "$status"
require_contains 'fedora_distribution_ready=0' "$status"
require_contains 'fedora_approval_claimed=0' "$status"
require_contains 'daily_driver_install_ready=0' "$status"
require_contains 'immutable_fedora_ready=0' "$status"
require_contains 'sh scripts/test-fedora-disposable-vm-rpm-readme-alignment.sh' "$status"
require_contains 'Add public announcement wording for disposable Fedora VM RPM validation milestone' "$status"

require_contains 'validated_package=latticra-0.0.0-0.1.local.fc44.x86_64.rpm' "$cli_evidence"
require_contains 'host_install_ready_for_cli_payload=1' "$cli_evidence"
require_contains 'production_installer_ready=0' "$cli_evidence"
require_contains 'FEDORA_DISPOSABLE_VM_RPM_README_ALIGNMENT_STATUS.md' "$index"
require_contains 'Fedora disposable VM RPM README alignment' "$index"

printf 'fedora_disposable_vm_rpm_readme_alignment: ok\n'
