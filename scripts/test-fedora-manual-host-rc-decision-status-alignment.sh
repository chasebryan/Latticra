#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'fedora manual host rc decision status alignment: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'fedora manual host rc decision status alignment: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

status='docs/status/FEDORA_MANUAL_HOST_RC_DECISION_CLASSIFIER_STATUS.md'
index='docs/status/README.md'

require_file "$status"
require_file "$index"
require_file docs/FEDORA_MANUAL_HOST_RC_DECISION_CLASSIFIER.md
require_file docs/FEDORA_MANUAL_HOST_RC_CHECKLIST.md
require_file docs/status/FEDORA_MANUAL_HOST_RC_CHECKLIST_STATUS.md
require_file include/latticra/fedora_manual_host_rc_decision.h
require_file src/fedora_manual_host_rc_decision.c
require_file tests/fedora_manual_host_rc_decision.c
require_file scripts/test-fedora-manual-host-rc-decision-classifier.sh
require_file scripts/test-fedora-manual-host-rc-decision-classifier-docs.sh

require_contains 'Status: status alignment' "$status"
require_contains 'source=PR #217' "$status"
require_contains 'decision_classifier_present=1' "$status"
require_contains 'decision_classifier_guard_present=1' "$status"
require_contains 'decision_classifier_docs_guard_present=1' "$status"
require_contains 'candidate_state_defined=1' "$status"
require_contains 'blocked_state_defined=1' "$status"
require_contains 'invalid_state_defined=1' "$status"
require_contains 'synthetic_candidate_test_present=1' "$status"
require_contains 'blocked_target_tests_present=1' "$status"
require_contains 'blocked_evidence_tests_present=1' "$status"
require_contains 'blocked_boundary_tests_present=1' "$status"
require_contains 'invalid_input_test_present=1' "$status"
require_contains 'classifier_evidence_level=7' "$status"
require_contains 'live_host_validation_completed=0' "$status"
require_contains 'host_change_performed=0' "$status"
require_contains 'sudo_invoked=0' "$status"
require_contains 'rpm_invoked=0' "$status"
require_contains 'dnf_invoked=0' "$status"
require_contains 'network_allowed=0' "$status"
require_contains 'service_operation_allowed=0' "$status"
require_contains 'boot_operation_allowed=0' "$status"
require_contains 'kernel_operation_allowed=0' "$status"
require_contains 'policy_operation_allowed=0' "$status"
require_contains 'production_installer_ready=0' "$status"
require_contains 'fedora_distribution_ready=0' "$status"
require_contains 'fedora_approval_claimed=0' "$status"
require_contains 'manual_host_rc_status=blocked-pending-real-transcript' "$status"
require_contains 'manual_host_release_candidate_ready=0' "$status"
require_contains 'manual_host_dry_run_transcript_present=0' "$status"
require_contains 'host_install_ready=0' "$status"
require_contains 'Add manual Fedora host dry-run transcript contract' "$status"
require_contains 'root README overhaul should wait' "$status"
require_contains 'does not perform host changes' "$status"

require_contains 'FEDORA_MANUAL_HOST_RC_DECISION_CLASSIFIER_STATUS.md' "$index"
require_contains 'Current Fedora manual host RC decision classifier checkpoint' "$index"
require_contains 'Fedora manual host RC decision classifier' "$index"
require_contains 'source=PR #217' "$index"
require_contains 'decision_classifier_present=1' "$index"
require_contains 'decision_classifier_guard_present=1' "$index"
require_contains 'decision_classifier_docs_guard_present=1' "$index"
require_contains 'candidate_state_defined=1' "$index"
require_contains 'blocked_state_defined=1' "$index"
require_contains 'invalid_state_defined=1' "$index"
require_contains 'synthetic_candidate_test_present=1' "$index"
require_contains 'blocked_target_tests_present=1' "$index"
require_contains 'blocked_evidence_tests_present=1' "$index"
require_contains 'blocked_boundary_tests_present=1' "$index"
require_contains 'invalid_input_test_present=1' "$index"
require_contains 'classifier_evidence_level=7' "$index"
require_contains 'manual_host_rc_status=blocked-pending-real-transcript' "$index"
require_contains 'manual_host_dry_run_transcript_present=0' "$index"
require_contains 'host_install_ready=0' "$index"
require_contains 'Add manual Fedora host dry-run transcript contract' "$index"
require_contains 'Previous Fedora manual host RC checklist checkpoint' "$index"
require_contains 'Add no-effect Fedora manual host RC decision classifier' "$index"

printf 'fedora_manual_host_rc_decision_status_alignment: ok\n'
