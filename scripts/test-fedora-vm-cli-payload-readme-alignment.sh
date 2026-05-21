#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora vm cli payload readme alignment: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora vm cli payload readme alignment: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

readme='README.md'
evidence='docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md'
local_evidence='docs/status/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_EVIDENCE_STATUS.md'

require_file "$readme"
require_file "$evidence"
require_file "$local_evidence"
require_file docs/FEDORA_VM_CLI_PAYLOAD_VALIDATION_LANE.md
require_file docs/FEDORA_VM_CLI_TRANSCRIPT_CONTRACT.md

require_contains 'disposable Fedora VM CLI payload validation evidence' "$readme"
require_contains 'disposable_vm_cli_validation_completed=1' "$readme"
require_contains 'host_install_ready_for_cli_payload=1' "$readme"
require_contains 'production_installer_ready=0' "$readme"
require_contains 'fedora_distribution_ready=0' "$readme"
require_contains 'fedora_approval_claimed=0' "$readme"
require_contains 'daily_driver_install_ready=0' "$readme"
require_contains 'immutable_fedora_ready=0' "$readme"
require_contains 'latticra-0.0.0-0.1.local.fc44.x86_64.rpm' "$readme"
require_contains '/usr/bin/latticra' "$readme"
require_contains '/usr/share/doc/latticra/README.md' "$readme"
require_contains 'CLI status/version/report validation' "$readme"
require_contains 'This means the local CLI RPM payload has evidence-backed disposable Fedora VM validation.' "$readme"
require_contains 'does **not** mean Latticra is production ready' "$readme"
require_contains 'a production installer' "$readme"
require_contains 'a bootable OS replacement' "$readme"
require_contains 'a security product' "$readme"
require_contains 'command execution beyond the validated no-effect `latticra` CLI status/version/report surface' "$readme"
require_contains 'The only install-readiness statements currently supported by evidence are disposable Fedora VM local RPM validation' "$readme"
require_contains 'disposable Fedora VM CLI payload validation for the local no-effect CLI RPM' "$readme"

require_contains 'docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md' "$readme"
require_contains 'docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_STATUS.md' "$readme"
require_contains 'docs/FEDORA_VM_CLI_PAYLOAD_VALIDATION_LANE.md' "$readme"
require_contains 'docs/FEDORA_VM_CLI_TRANSCRIPT_CONTRACT.md' "$readme"
require_contains 'sh scripts/test-fedora-vm-cli-payload-validation-evidence-status.sh' "$readme"

require_contains 'validated_package=latticra-0.0.0-0.1.local.fc44.x86_64.rpm' "$evidence"
require_contains 'disposable_vm_cli_validation_completed=1' "$evidence"
require_contains 'host_install_ready_for_cli_payload=1' "$evidence"
require_contains 'production_installer_ready=0' "$evidence"

printf 'fedora_vm_cli_payload_readme_alignment: ok\n'
