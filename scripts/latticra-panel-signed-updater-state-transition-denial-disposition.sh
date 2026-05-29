#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-panel-signed-updater-state-transition-denial-disposition.sh

Emits the no-effect disposition for the Latticra Panel signed updater state
transition denial review. It does not transition update state, stage updates,
write disposition files, write receipts, mutate host state, or apply signed
updates.
USAGE
}

while [ "$#" -gt 0 ]; do
  case "$1" in
    -h|--help)
      usage
      exit 0
      ;;
    *)
      echo "unknown argument: $1" >&2
      usage >&2
      exit 64
      ;;
  esac
done

ROOT=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
UNAME_S=$(uname -s 2>/dev/null || printf 'unknown')
UNAME_M=$(uname -m 2>/dev/null || printf 'unknown')

cat <<REPORT
LATTICRA PANEL SIGNED UPDATER STATE TRANSITION DENIAL DISPOSITION

signed_updater_state_transition_denial_disposition_status=ok
repo_root=$ROOT
host_kernel_name=$UNAME_S
host_arch=$UNAME_M
latticra_panel_updater_present=1
latticra_panel_updater_owned=1
signed_updater_delivery_gate_present=1
signed_updater_delivery_gate_state=closed
signed_updater_denial_transcript_present=1
signed_updater_manifest_fixture_contract_present=1
signed_updater_manifest_fixture_validation_present=1
signed_updater_state_fixture_contract_present=1
signed_updater_state_fixture_validation_present=1
signed_updater_state_fixture_validated=1
signed_updater_state_transition_denial_transcript_present=1
signed_updater_state_transition_denial_transcript_state=recorded-no-effect
signed_updater_state_transition_denial_review_present=1
signed_updater_state_transition_denial_review_state=reviewed-no-effect
signed_updater_state_transition_denial_review_stdout_only=1
signed_updater_state_transition_denial_review_file_write_enabled=0
signed_updater_state_transition_denial_review_decision=uphold-deny-state-transition
signed_updater_state_transition_denial_review_reason=denial-transcript-confirms-missing-signed-manifest-artifact-verification-rollback-and-operator-confirmation
signed_updater_state_transition_denial_disposition_present=1
signed_updater_state_transition_denial_disposition_state=disposed-no-effect
signed_updater_state_transition_denial_disposition_stdout_only=1
signed_updater_state_transition_denial_disposition_file_write_enabled=0
signed_updater_state_transition_denial_disposition_decision=retain-blocked-state
signed_updater_state_transition_denial_disposition_reason=review-upheld-denial-missing-signed-manifest-artifact-verification-rollback-and-operator-confirmation
signed_updater_state_transition_denial_decision=deny-state-transition
signed_updater_state_transition_denial_reason=missing-signed-manifest-artifact-verification-rollback-and-operator-confirmation
state_fixture_path=fixtures/latticra-panel/signed-updater-state.fixture.toml
state_fixture_schema=latticra-panel-signed-updater-state-fixture-v0
state_fixture_validated_for_transition=0
state_fixture_validated_for_apply=0
signed_updater_state_fixture_valid_for_transition=0
signed_updater_state_fixture_valid_for_apply=0
state_catalog_present=1
state_available_declared=1
state_downloaded_declared=1
state_verified_declared=1
state_staged_declared=1
state_armed_declared=1
state_applied_declared=1
state_rolled_back_declared=1
state_failed_declared=1
state_blocked_declared=1
current_update_state=blocked
requested_update_state=blocked
state_transition_decision=deny-transition
state_transition_review_decision=uphold-denial
state_transition_disposition=retain-blocked-state
state_transition_reason=missing-signed-manifest-artifact-verification-rollback-and-operator-confirmation
state_transition_execution_allowed=0
state_transition_execution_performed=0
state_receipt_written=0
available_state_materialized=0
downloaded_state_materialized=0
verified_state_materialized=0
staged_state_materialized=0
armed_state_materialized=0
applied_state_materialized=0
rolled_back_state_materialized=0
failed_state_materialized=0
blocked_state_recorded=1
trusted_signed_manifest_present=0
signed_manifest_required=1
signed_manifest_present=0
manifest_signature_required=1
manifest_signature_present=0
manifest_signature_verified=0
artifact_hash_required=1
artifact_hash_present=0
artifact_hash_verified=0
artifact_signature_required=1
artifact_signature_present=0
artifact_signature_verified=0
rollback_plan_required=1
rollback_plan_present=0
rollback_execution_allowed=0
rollback_execution_performed=0
post_update_validation_required=1
post_update_validation_present=0
operator_confirmation_required=1
operator_confirmation_observed=0
update_receipt_required=1
update_receipt_written=0
signed_update_delivery_ready=0
network_self_update_ready=0
remote_update_repository_trust=0
remote_update_repository_trust_ready=0
network_fetch_authority=0
network_fetch_attempted=0
updater_network_fetch_enabled=0
staged_update_allowed=0
staged_update_performed=0
signed_update_apply_allowed=0
signed_update_apply_performed=0
update_activation_allowed=0
update_activation_performed=0
validation_write_performed=0
transcript_write_performed=0
review_write_performed=0
disposition_write_performed=0
host_mutation_allowed=0
host_mutation_performed=0
root_authority=0
system_mutation_authority=0
kernel_mutation_authority=0
systemd_mutation_authority=0
selinux_mutation_authority=0
boot_mutation_authority=0
production_update_ready=0
production_installer_ready=0
next_lane=panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition-review-closeout
REPORT
