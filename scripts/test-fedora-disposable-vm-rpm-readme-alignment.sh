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
index='docs/status/README.md'

require_file "$readme"
require_file "$status"
require_file "$evidence"
require_file "$index"
require_file docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_LANE.md
require_file docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_TRANSCRIPT_CONTRACT.md
require_file packaging/fedora/latticra.spec

require_contains '## Fedora and local RPM work' "$readme"
require_contains 'Latticra has a Fedora-facing validation lane, but it is intentionally narrow.' "$readme"
require_contains 'The current RPM packaging work is a **local-only draft**.' "$readme"
require_contains 'local_only_draft=1' "$readme"
require_contains 'fedora_approval_claimed=0' "$readme"
require_contains 'fedora_distribution_ready=0' "$readme"
require_contains 'production_installer_ready=0' "$readme"
require_contains 'daily_driver_install_ready=0' "$readme"
require_contains 'immutable_fedora_ready=0' "$readme"
require_contains 'src/latticra_cli.c' "$readme"
require_contains '/usr/bin/latticra' "$readme"
require_contains '/usr/share/doc/latticra/README.md' "$readme"
require_contains 'docs/FEDORA_DEVELOPER_WORKFLOW.md' "$readme"
require_contains 'docs/FEDORA_PACKAGE_METADATA_PLAN.md' "$readme"
require_contains 'docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_LANE.md' "$readme"
require_contains 'docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_TRANSCRIPT_CONTRACT.md' "$readme"
require_contains 'packaging/fedora/latticra.spec' "$readme"

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

require_contains 'FEDORA_DISPOSABLE_VM_RPM_README_ALIGNMENT_STATUS.md' "$index"
require_contains 'Fedora disposable VM RPM README alignment' "$index"

require_contains 'Status: evidence status' "$evidence"
require_contains 'production_installer_ready=0' "$evidence"
require_contains 'fedora_distribution_ready=0' "$evidence"
require_contains 'fedora_approval_claimed=0' "$evidence"

printf 'fedora_disposable_vm_rpm_readme_alignment: ok\n'
