#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora disposable vm local rpm validation lane docs: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora disposable vm local rpm validation lane docs: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

doc='docs/FEDORA_DISPOSABLE_VM_LOCAL_RPM_VALIDATION_LANE.md'
runner='scripts/run-fedora-disposable-vm-local-rpm-validation-lane.sh'

require_file "$doc"
require_file "$runner"
require_file docs/FEDORA_DISPOSABLE_VM_EFFECT_GATE.md
require_file docs/FEDORA_DISPOSABLE_VM_EFFECT_GATE_CLASSIFIER.md
require_file docs/status/FEDORA_DISPOSABLE_VM_EFFECT_GATE_CLASSIFIER_STATUS.md
require_file packaging/fedora/latticra.spec

require_contains 'Status: gated validation lane' "$doc"
require_contains 'Evidence level: 9 target' "$doc"
require_contains 'disposable Fedora VM' "$doc"
require_contains 'LATTICRA_ALLOW_DISPOSABLE_VM_RPM_VALIDATION=1' "$doc"
require_contains 'LATTICRA_TARGET_IS_DISPOSABLE_FEDORA_VM=1' "$doc"
require_contains 'LATTICRA_TARGET_IS_DAILY_DRIVER=0' "$doc"
require_contains 'LATTICRA_TARGET_IS_PRODUCTION_HOST=0' "$doc"
require_contains 'LATTICRA_TARGET_HAS_CLEAN_SNAPSHOT=1' "$doc"
require_contains 'LATTICRA_TARGET_HAS_RECOVERY_PATH=1' "$doc"
require_contains 'LATTICRA_OPERATOR_CONSENT_RECORDED=1' "$doc"
require_contains 'ID=fedora' "$doc"
require_contains 'rpm_present=1' "$doc"
require_contains 'rpmbuild_present=1' "$doc"
require_contains 'rpm_name_is_latticra=1' "$doc"
require_contains 'rpm_version_recorded=1' "$doc"
require_contains 'rpm_payload_listing_recorded=1' "$doc"
require_contains 'rpm_payload_is_documentation_only=1' "$doc"
require_contains 'unexpected_runtime_surface_absent=1' "$doc"
require_contains '/usr/share/doc/latticra/README.md' "$doc"
require_contains '/usr/bin/latticra' "$doc"
require_contains '/etc/latticra' "$doc"
require_contains '/usr/lib/systemd/system/latticra.service' "$doc"
require_contains 'FEDORA DISPOSABLE VM LOCAL RPM VALIDATION LANE' "$doc"
require_contains 'validation_status=ok' "$doc"
require_contains 'vm_rpmdb_mutated=1' "$doc"
require_contains 'vm_filesystem_mutated=1' "$doc"
require_contains 'install_validation_performed=1' "$doc"
require_contains 'removal_validation_performed=1' "$doc"
require_contains 'post_removal_absence_verified=1' "$doc"
require_contains 'live_host_validation_completed=1' "$doc"
require_contains 'host_install_ready=1' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'fedora_distribution_ready=0' "$doc"
require_contains 'fedora_approval_claimed=0' "$doc"
require_contains 'fedora_disposable_vm_local_rpm_validation_lane_docs: ok' "$doc"
require_contains 'Add disposable Fedora VM local RPM validation status alignment' "$doc"
require_contains 'root README can be overhauled' "$doc"

require_contains 'LATTICRA_ALLOW_DISPOSABLE_VM_RPM_VALIDATION' "$runner"
require_contains 'LATTICRA_TARGET_IS_DISPOSABLE_FEDORA_VM' "$runner"
require_contains 'LATTICRA_TARGET_IS_DAILY_DRIVER' "$runner"
require_contains 'LATTICRA_TARGET_IS_PRODUCTION_HOST' "$runner"
require_contains 'LATTICRA_TARGET_HAS_CLEAN_SNAPSHOT' "$runner"
require_contains 'LATTICRA_TARGET_HAS_RECOVERY_PATH' "$runner"
require_contains 'LATTICRA_OPERATOR_CONSENT_RECORDED' "$runner"
require_contains 'validation_status=ok' "$runner"
require_contains 'host_install_ready=1' "$runner"

printf 'fedora_disposable_vm_local_rpm_validation_lane_docs: ok\n'
