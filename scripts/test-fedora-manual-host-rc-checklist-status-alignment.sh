#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora manual host rc checklist status alignment: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora manual host rc checklist status alignment: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status='docs/status/FEDORA_MANUAL_HOST_RC_CHECKLIST_STATUS.md'
index='docs/status/README.md'
checklist='docs/FEDORA_MANUAL_HOST_RC_CHECKLIST.md'

require_file "$status"
require_file "$index"
require_file "$checklist"
require_file scripts/test-fedora-manual-host-rc-checklist.sh
require_file docs/status/FEDORA_INSTALLROOT_RPM_LIFECYCLE_STATUS.md
require_file docs/FEDORA_LOCAL_RPM_EXECUTION_LANE.md
require_file docs/FEDORA_RPM_GATE_CLASSIFIER.md
require_file docs/FEDORA_RPM_REMOVAL_ROLLBACK_CLASSIFIER.md

require_contains 'Status: status alignment' "$status"
require_contains 'source=PR #215' "$status"
require_contains 'checklist_documented=1' "$status"
require_contains 'checklist_guard_present=1' "$status"
require_contains 'controlled_installroot_lifecycle_ready=1' "$status"
require_contains 'manual_host_rc_status=blocked' "$status"
require_contains 'manual_host_release_candidate_ready=0' "$status"
require_contains 'live_host_validation_completed=0' "$status"
require_contains 'host_change_performed=0' "$status"
require_contains 'production_installer_ready=0' "$status"
require_contains 'fedora_distribution_ready=0' "$status"
require_contains 'fedora_approval_claimed=0' "$status"
require_contains 'fedora_candidate_compose_claimed=0' "$status"
require_contains 'fedora_go_no_go_claimed=0' "$status"
require_contains 'checklist_target_evidence_level=7' "$status"
require_contains 'current_evidence_level=6' "$status"
require_contains 'evidence_level_7_achieved=0' "$status"
require_contains 'target_is_disposable_fedora_vm=1' "$status"
require_contains 'target_has_clean_snapshot=1' "$status"
require_contains 'target_has_recovery_path=1' "$status"
require_contains 'operator_consent_recorded=1' "$status"
require_contains 'rpm_payload_is_documentation_only=1' "$status"
require_contains 'unexpected_runtime_surface_absent=1' "$status"
require_contains 'host_preflight_classification=ready-local-rpm' "$status"
require_contains 'rpm_gate_status=allowed' "$status"
require_contains 'removal_rollback_status=removal-ready' "$status"
require_contains 'manual_host_rc_checklist_present=1' "$status"
require_contains 'manual_host_rc_guard_present=1' "$status"
require_contains 'host_install_ready=0' "$status"
require_contains 'Add no-effect Fedora manual host RC decision classifier' "$status"
require_contains 'does not perform host changes' "$status"

require_contains 'FEDORA_MANUAL_HOST_RC_CHECKLIST_STATUS.md' "$index"
require_contains 'Current Fedora manual host RC checklist checkpoint' "$index"
require_contains 'Fedora manual host RC checklist' "$index"
require_contains 'source=PR #215' "$index"
require_contains 'checklist_documented=1' "$index"
require_contains 'checklist_guard_present=1' "$index"
require_contains 'manual_host_rc_status=blocked' "$index"
require_contains 'manual_host_release_candidate_ready=0' "$index"
require_contains 'live_host_validation_completed=0' "$index"
require_contains 'host_change_performed=0' "$index"
require_contains 'fedora_candidate_compose_claimed=0' "$index"
require_contains 'fedora_go_no_go_claimed=0' "$index"
require_contains 'evidence_level_7_achieved=0' "$index"
require_contains 'manual_host_rc_checklist_present=1' "$index"
require_contains 'manual_host_rc_guard_present=1' "$index"
require_contains 'host_install_ready=0' "$index"
require_contains 'Add no-effect Fedora manual host RC decision classifier' "$index"
require_contains 'Previous Fedora installroot RPM lifecycle checkpoint' "$index"
require_contains 'Add manual host-install release-candidate checklist' "$index"

printf 'fedora_manual_host_rc_checklist_status_alignment: ok\n'
