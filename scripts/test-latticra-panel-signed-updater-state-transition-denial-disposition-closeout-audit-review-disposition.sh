#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'latticra panel signed updater state transition denial disposition closeout audit review disposition: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'latticra panel signed updater state transition denial disposition closeout audit review disposition: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'latticra panel signed updater state transition denial disposition closeout audit review disposition: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'latticra panel signed updater state transition denial disposition closeout audit review disposition: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

doc='docs/LATTICRA_PANEL_SIGNED_UPDATER_STATE_TRANSITION_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION.md'
status='docs/status/LATTICRA_PANEL_SIGNED_UPDATER_STATE_TRANSITION_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_STATUS.md'
script='scripts/latticra-panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition.sh'
review_doc='docs/LATTICRA_PANEL_SIGNED_UPDATER_STATE_TRANSITION_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_REVIEW.md'
review_status='docs/status/LATTICRA_PANEL_SIGNED_UPDATER_STATE_TRANSITION_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_STATUS.md'
review_script='scripts/latticra-panel-signed-updater-state-transition-denial-disposition-closeout-audit-review.sh'
review_test='scripts/test-latticra-panel-signed-updater-state-transition-denial-disposition-closeout-audit-review.sh'
audit_doc='docs/LATTICRA_PANEL_SIGNED_UPDATER_STATE_TRANSITION_DENIAL_DISPOSITION_CLOSEOUT_AUDIT.md'
audit_status='docs/status/LATTICRA_PANEL_SIGNED_UPDATER_STATE_TRANSITION_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_STATUS.md'
audit_script='scripts/latticra-panel-signed-updater-state-transition-denial-disposition-closeout-audit.sh'
self_update='docs/SELF_UPDATE_MODEL.md'
index='docs/status/README.md'
makefile='Makefile'
workflow='.github/workflows/latticra-panel-installer.yml'

for file in \
  "$doc" \
  "$status" \
  "$script" \
  "$review_doc" \
  "$review_status" \
  "$review_script" \
  "$review_test" \
  "$audit_doc" \
  "$audit_status" \
  "$audit_script" \
  "$self_update" \
  "$index" \
  "$makefile" \
  "$workflow"
do
  require_file "$file"
done

require_contains 'Status: no-effect signed updater state transition denial disposition closeout audit review disposition' "$doc"
require_contains 'sh scripts/latticra-panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition.sh' "$doc"
require_contains 'signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition_present=1' "$doc"
require_contains 'signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition_stdout_only=1' "$doc"
require_contains 'signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition_file_write_enabled=0' "$doc"
require_contains 'signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition_decision=retain-reviewed-closeout-audit-boundary' "$doc"
require_contains 'signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition_source_review_decision=uphold-accept-closeout-boundary' "$doc"
require_contains 'state_transition_disposition_closeout_audit_review_disposition_decision=retain-reviewed-closeout-audit-boundary' "$doc"
require_contains 'state_transition_disposition_closeout_audit_review_disposition_state=disposed-no-effect' "$doc"
require_contains 'state_transition_execution_allowed=0' "$doc"
require_contains 'audit_review_disposition_write_performed=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'not update-state evidence' "$doc"

require_contains 'Status: no-effect signed updater state transition denial disposition closeout audit review disposition status' "$status"
require_contains 'latticra_panel_signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition_present=1' "$status"
require_contains 'latticra_panel_signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition_guard_present=1' "$status"
require_contains 'signed_updater_state_transition_denial_disposition_closeout_audit_review_present=1' "$status"
require_contains 'signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition_present=1' "$status"
require_contains 'signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition_state=disposed-no-effect' "$status"
require_contains 'signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition_stdout_only=1' "$status"
require_contains 'signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition_file_write_enabled=0' "$status"
require_contains 'signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition_decision=retain-reviewed-closeout-audit-boundary' "$status"
require_contains 'signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition_review_required=1' "$status"
require_contains 'signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition_review_opened=0' "$status"
require_contains 'state_transition_disposition_closeout_audit_review_disposition_decision=retain-reviewed-closeout-audit-boundary' "$status"
require_contains 'state_transition_execution_allowed=0' "$status"
require_contains 'state_transition_execution_performed=0' "$status"
require_contains 'audit_review_disposition_write_performed=0' "$status"
require_contains 'host_mutation_performed=0' "$status"
require_contains 'production_update_ready=0' "$status"

require_contains 'LATTICRA PANEL SIGNED UPDATER STATE TRANSITION DENIAL DISPOSITION CLOSEOUT AUDIT REVIEW DISPOSITION' "$script"
require_contains 'signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition_status=ok' "$script"
require_contains 'signed_updater_state_transition_denial_disposition_closeout_audit_review_state=reviewed-no-effect' "$script"
require_contains 'signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition_state=disposed-no-effect' "$script"
require_contains 'signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition_decision=retain-reviewed-closeout-audit-boundary' "$script"
require_contains 'signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition_review_opened=0' "$script"
require_contains 'state_transition_disposition_closeout_audit_review_disposition_decision=retain-reviewed-closeout-audit-boundary' "$script"
require_contains 'state_transition_execution_allowed=0' "$script"
require_contains 'audit_review_disposition_write_performed=0' "$script"
require_contains 'host_mutation_performed=0' "$script"
require_contains 'next_lane=panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition-review-closeout' "$script"
require_not_contains 'rm ' "$script"
require_not_contains 'curl ' "$script"
require_not_contains 'wget ' "$script"
require_not_contains 'sudo ' "$script"

require_contains 'LATTICRA_PANEL_SIGNED_UPDATER_STATE_TRANSITION_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_STATUS.md' "$index"
require_contains 'signed updater state transition denial disposition closeout audit review disposition status' "$index"

require_contains 'signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition_present=1' "$self_update"
require_contains 'signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition_decision=retain-reviewed-closeout-audit-boundary' "$self_update"
require_contains 'signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition_file_write_enabled=0' "$self_update"
require_contains 'local signed updater state transition denial disposition closeout audit review disposition' "$self_update"

require_contains 'Panel signed-updater state transition denial disposition closeout audit review disposition review closeout' "$review_doc"
require_contains 'Panel signed-updater state transition denial disposition closeout audit review disposition review closeout' "$review_status"
require_contains 'Panel signed-updater state transition denial disposition closeout audit review disposition review closeout' "$audit_doc"
require_contains 'Panel signed-updater state transition denial disposition closeout audit review disposition review closeout' "$audit_status"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition-review-closeout' "$review_script"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition-review-closeout' "$review_test"
require_contains 'panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition-review-closeout' "$audit_script"

require_contains 'latticra-panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition:' "$makefile"
require_contains 'sh ./scripts/test-latticra-panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition.sh' "$makefile"
require_contains 'docs/LATTICRA_PANEL_SIGNED_UPDATER_STATE_TRANSITION_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION.md' "$workflow"
require_contains 'docs/status/LATTICRA_PANEL_SIGNED_UPDATER_STATE_TRANSITION_DENIAL_DISPOSITION_CLOSEOUT_AUDIT_REVIEW_DISPOSITION_STATUS.md' "$workflow"
require_contains 'scripts/test-latticra-panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition.sh' "$workflow"
require_contains 'scripts/latticra-panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition.sh' "$workflow"
require_contains 'Validate Latticra Panel signed updater state transition denial disposition closeout audit review disposition' "$workflow"

sh -n "$script"
sh -n "$0"

output=$(sh "$script")
require_output_contains "$output" 'LATTICRA PANEL SIGNED UPDATER STATE TRANSITION DENIAL DISPOSITION CLOSEOUT AUDIT REVIEW DISPOSITION'
require_output_contains "$output" 'signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition_status=ok'
require_output_contains "$output" 'signed_updater_state_transition_denial_disposition_closeout_audit_review_present=1'
require_output_contains "$output" 'signed_updater_state_transition_denial_disposition_closeout_audit_review_state=reviewed-no-effect'
require_output_contains "$output" 'signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition_present=1'
require_output_contains "$output" 'signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition_state=disposed-no-effect'
require_output_contains "$output" 'signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition_stdout_only=1'
require_output_contains "$output" 'signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition_file_write_enabled=0'
require_output_contains "$output" 'signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition_decision=retain-reviewed-closeout-audit-boundary'
require_output_contains "$output" 'signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition_review_required=1'
require_output_contains "$output" 'signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition_review_opened=0'
require_output_contains "$output" 'state_transition_disposition_closeout_audit_review_decision=uphold-accept-closeout-boundary'
require_output_contains "$output" 'state_transition_disposition_closeout_audit_review_disposition_decision=retain-reviewed-closeout-audit-boundary'
require_output_contains "$output" 'state_transition_disposition_closeout_audit_review_disposition_state=disposed-no-effect'
require_output_contains "$output" 'current_update_state=blocked'
require_output_contains "$output" 'requested_update_state=blocked'
require_output_contains "$output" 'state_transition_decision=deny-transition'
require_output_contains "$output" 'state_transition_execution_allowed=0'
require_output_contains "$output" 'state_transition_execution_performed=0'
require_output_contains "$output" 'state_receipt_written=0'
require_output_contains "$output" 'staged_update_allowed=0'
require_output_contains "$output" 'signed_update_apply_allowed=0'
require_output_contains "$output" 'rollback_execution_allowed=0'
require_output_contains "$output" 'network_fetch_authority=0'
require_output_contains "$output" 'network_fetch_attempted=0'
require_output_contains "$output" 'audit_review_disposition_write_performed=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'production_update_ready=0'
require_output_contains "$output" 'next_lane=panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition-review-closeout'

sh scripts/test-latticra-panel-signed-updater-state-transition-denial-disposition-closeout-audit-review.sh

printf 'latticra_panel_signed_updater_state_transition_denial_disposition_closeout_audit_review_disposition: ok\n'
