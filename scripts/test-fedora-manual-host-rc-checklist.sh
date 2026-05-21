#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora manual host rc checklist: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora manual host rc checklist: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

checklist='docs/FEDORA_MANUAL_HOST_RC_CHECKLIST.md'

require_file "$checklist"
require_file docs/status/FEDORA_INSTALLROOT_RPM_LIFECYCLE_STATUS.md
require_file docs/FEDORA_LOCAL_RPM_EXECUTION_LANE.md
require_file docs/FEDORA_RPM_GATE_CLASSIFIER.md
require_file docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER.md

require_contains 'Status: release-candidate checklist' "$checklist"
require_contains 'Evidence level: 7 target, checklist only' "$checklist"
require_contains 'controlled_installroot_lifecycle_ready=1' "$checklist"
require_contains 'manual_host_release_candidate_ready=0' "$checklist"
require_contains 'production_installer_ready=0' "$checklist"
require_contains 'fedora_distribution_ready=0' "$checklist"
require_contains 'fedora_approval_claimed=0' "$checklist"
require_contains 'target_is_disposable_fedora_vm=1' "$checklist"
require_contains 'target_is_daily_driver=0' "$checklist"
require_contains 'target_is_production_host=0' "$checklist"
require_contains 'target_is_immutable_fedora=0' "$checklist"
require_contains 'target_has_clean_snapshot=1' "$checklist"
require_contains 'target_has_recovery_path=1' "$checklist"
require_contains 'operator_consent_recorded=1' "$checklist"
require_contains 'local_rpm_built_from_current_tree=1' "$checklist"
require_contains 'rpm_name_is_latticra=1' "$checklist"
require_contains 'rpm_payload_is_documentation_only=1' "$checklist"
require_contains 'unexpected_runtime_surface_absent=1' "$checklist"
require_contains 'installroot_lifecycle_evidence_present=1' "$checklist"
require_contains 'post_removal_absence_evidence_present=1' "$checklist"
require_contains 'host_preflight_classification=ready-local-rpm' "$checklist"
require_contains 'rpm_gate_status=allowed' "$checklist"
require_contains 'removal_rollback_status=removal-ready' "$checklist"
require_contains 'FEDORA MANUAL HOST RC CHECKLIST' "$checklist"
require_contains 'manual_host_rc_status=blocked' "$checklist"
require_contains 'host_change_performed=0' "$checklist"
require_contains 'manual_host_rc_status=candidate' "$checklist"
require_contains 'Latticra has controlled Fedora installroot RPM lifecycle evidence.' "$checklist"
require_contains 'Latticra is production installer ready.' "$checklist"
require_contains 'fedora_manual_host_rc_checklist: ok' "$checklist"
require_contains 'does not perform host changes' "$checklist"

printf 'fedora_manual_host_rc_checklist: ok\n'
