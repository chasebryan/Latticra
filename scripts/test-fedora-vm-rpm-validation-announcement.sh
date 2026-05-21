#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora vm rpm validation announcement: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora vm rpm validation announcement: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

announcements='docs/status/ANNOUNCEMENTS.md'
status='docs/status/FEDORA_VM_RPM_VALIDATION_ANNOUNCEMENT_STATUS.md'
evidence='docs/status/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_EVIDENCE_STATUS.md'
readme_status='docs/status/FEDORA_DISPOSABLE_VM_RPM_README_ALIGNMENT_STATUS.md'
readme='README.md'

require_file "$announcements"
require_file "$status"
require_file "$evidence"
require_file "$readme_status"
require_file "$readme"

require_contains 'Latest Fedora VM RPM validation milestone note: 2026-05-21 03:20 CDT' "$announcements"
require_contains '2026-05-21 03:20 CDT — Disposable Fedora VM local RPM validation milestone' "$announcements"
require_contains 'Status: evidence-backed validation milestone recorded' "$announcements"
require_contains 'disposable_vm_validation_completed=1' "$announcements"
require_contains 'live_host_validation_completed=1' "$announcements"
require_contains 'host_install_ready=1' "$announcements"
require_contains 'validated_package=latticra-0.0.0-0.1.local.fc44.noarch.rpm' "$announcements"
require_contains 'validated_payload=/usr/share/doc/latticra/README.md' "$announcements"
require_contains 'evidence_level=9' "$announcements"
require_contains 'package build, RPM install, RPM verification, RPM removal, and post-removal absence verification' "$announcements"
require_contains 'sh scripts/test-fedora-disposable-vm-local-rpm-validation-evidence-status.sh' "$announcements"
require_contains 'sh scripts/test-fedora-disposable-vm-rpm-readme-alignment.sh' "$announcements"
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
require_contains 'Plan the next Fedora validation lane without widening README or announcement claims beyond disposable Fedora VM local RPM evidence' "$announcements"

require_contains 'Status: announcement/status alignment' "$status"
require_contains 'disposable_vm_validation_completed=1' "$status"
require_contains 'validated_package=latticra-0.0.0-0.1.local.fc44.noarch.rpm' "$status"
require_contains 'validated_payload=/usr/share/doc/latticra/README.md' "$status"
require_contains 'evidence_level=9' "$status"
require_contains 'docs/status/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_EVIDENCE_STATUS.md' "$status"
require_contains 'docs/status/FEDORA_DISPOSABLE_VM_RPM_README_ALIGNMENT_STATUS.md' "$status"
require_contains 'sh scripts/test-fedora-vm-rpm-validation-announcement.sh' "$status"
require_contains 'Plan the next Fedora validation lane without widening README or announcement claims beyond disposable Fedora VM local RPM evidence' "$status"

printf 'fedora_vm_rpm_validation_announcement: ok\n'
