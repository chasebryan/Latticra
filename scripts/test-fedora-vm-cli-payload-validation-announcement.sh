#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora vm cli payload validation announcement: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora vm cli payload validation announcement: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

announcements='docs/status/ANNOUNCEMENTS.md'
status='docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_ANNOUNCEMENT_STATUS.md'
evidence='docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md'
readme_status='docs/status/FEDORA_VM_CLI_PAYLOAD_README_ALIGNMENT_STATUS.md'
index='docs/status/README.md'
readme='README.md'
workflow='.github/workflows/fedora-vm-cli-payload-validation-announcement.yml'

require_file "$announcements"
require_file "$status"
require_file "$evidence"
require_file "$readme_status"
require_file "$index"
require_file "$readme"
require_file "$workflow"

require_contains 'Latest Fedora VM CLI payload validation milestone note: 2026-05-26 04:12 CDT' "$announcements"
require_contains '2026-05-26 04:12 CDT — Disposable Fedora VM CLI payload validation milestone' "$announcements"
require_contains 'Status: evidence-backed CLI payload validation milestone recorded' "$announcements"
require_contains 'disposable_vm_cli_validation_completed=1' "$announcements"
require_contains 'host_install_ready_for_cli_payload=1' "$announcements"
require_contains 'validated_package=latticra-0.0.0-0.1.local.fc44.x86_64.rpm' "$announcements"
require_contains 'validated_payload=/usr/bin/latticra' "$announcements"
require_contains 'validated_payload=/usr/share/doc/latticra/README.md' "$announcements"
require_contains 'evidence_level=9' "$announcements"
require_contains 'local RPM build, package installation, CLI `--status`, `--version`, `--report`, invalid-command validation, RPM removal, and post-removal absence verification' "$announcements"
require_contains 'sh scripts/test-fedora-vm-cli-payload-validation-evidence-status.sh' "$announcements"
require_contains 'sh scripts/test-fedora-vm-cli-payload-readme-alignment.sh' "$announcements"
require_contains 'does not claim production readiness' "$announcements"
require_contains 'Fedora approval' "$announcements"
require_contains 'Fedora distribution readiness' "$announcements"
require_contains 'daily-driver safety' "$announcements"
require_contains 'immutable Fedora readiness' "$announcements"
require_contains 'security capability' "$announcements"
require_contains 'update safety' "$announcements"
require_contains 'recovery safety' "$announcements"
require_contains 'sandboxing' "$announcements"
require_contains 'malware prevention' "$announcements"
require_contains 'ransomware prevention' "$announcements"
require_contains 'bootable OS replacement behavior' "$announcements"
require_contains 'kernel runtime readiness' "$announcements"
require_contains 'production installer' "$announcements"
require_contains 'Plan the next Fedora CLI payload validation lane without widening README or announcement claims beyond disposable Fedora VM evidence' "$announcements"

require_contains 'Status: announcement/status alignment' "$status"
require_contains 'Date: 2026-05-26' "$status"
require_contains 'disposable_vm_cli_validation_completed=1' "$status"
require_contains 'host_install_ready_for_cli_payload=1' "$status"
require_contains 'validated_package=latticra-0.0.0-0.1.local.fc44.x86_64.rpm' "$status"
require_contains 'validated_payload=/usr/bin/latticra' "$status"
require_contains 'validated_payload=/usr/share/doc/latticra/README.md' "$status"
require_contains 'evidence_level=9' "$status"
require_contains 'docs/status/FEDORA_VM_CLI_PAYLOAD_VALIDATION_EVIDENCE_STATUS.md' "$status"
require_contains 'docs/status/FEDORA_VM_CLI_PAYLOAD_README_ALIGNMENT_STATUS.md' "$status"
require_contains 'sh scripts/test-fedora-vm-cli-payload-validation-announcement.sh' "$status"
require_contains 'Plan the next Fedora CLI payload validation lane without widening README or announcement claims beyond disposable Fedora VM evidence' "$status"

require_contains 'FEDORA_VM_CLI_PAYLOAD_VALIDATION_ANNOUNCEMENT_STATUS.md' "$index"
require_contains 'Current Fedora VM CLI payload announcement checkpoint' "$index"
require_contains 'disposable_vm_cli_validation_completed=1' "$index"
require_contains 'host_install_ready_for_cli_payload=1' "$index"
require_contains 'validated_package=latticra-0.0.0-0.1.local.fc44.x86_64.rpm' "$index"
require_contains 'validated_payload=/usr/bin/latticra' "$index"
require_contains 'validated_payload=/usr/share/doc/latticra/README.md' "$index"

require_contains 'Status: evidence status alignment' "$evidence"
require_contains 'disposable_vm_cli_validation_completed=1' "$evidence"
require_contains 'host_install_ready_for_cli_payload=1' "$evidence"

require_contains 'Status: README/status alignment' "$readme_status"
require_contains 'fedora_vm_cli_payload_validation_status=evidence-recorded' "$readme_status"

require_contains 'host_install_ready_for_cli_payload=1' "$readme"
require_contains 'name: Fedora VM CLI Payload Validation Announcement' "$workflow"
require_contains 'runs-on: ubuntu-latest' "$workflow"
require_contains 'sh scripts/test-fedora-vm-cli-payload-validation-announcement.sh' "$workflow"

printf 'fedora_vm_cli_payload_validation_announcement: ok\n'
