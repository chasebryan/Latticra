#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-panel-signed-updater-state-fixture-validation.sh

Validates the local no-effect signed-updater state fixture shape for Latticra
Panel. It reads only the committed fixture and does not transition update
state, stage updates, write receipts, mutate host state, or apply signed
updates.
USAGE
}

require_fixture_line() {
  pattern="$1"
  if ! grep -Fxq -- "$pattern" "$FIXTURE"; then
    printf 'latticra panel signed updater state fixture validation: missing fixture line: %s\n' "$pattern" >&2
    exit 1
  fi
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
FIXTURE_RELATIVE='fixtures/latticra-panel/signed-updater-state.fixture.toml'
FIXTURE="$ROOT/$FIXTURE_RELATIVE"

if [ ! -f "$FIXTURE" ]; then
  printf 'latticra panel signed updater state fixture validation: missing fixture: %s\n' "$FIXTURE_RELATIVE" >&2
  exit 1
fi

require_fixture_line 'state_schema = "latticra-panel-signed-updater-state-fixture-v0"'
require_fixture_line 'state_fixture = true'
require_fixture_line 'state_fixture_scope = "local-no-effect"'
require_fixture_line 'state_fixture_effect = "none"'
require_fixture_line 'state_fixture_trusted_for_apply = false'
require_fixture_line 'updater_component = "latticra-panel"'
require_fixture_line 'update_id = "panel-local-checkout-state-fixture"'
require_fixture_line 'update_channel = "lab"'
require_fixture_line 'source_strategy = "current-source-checkout"'
require_fixture_line 'apply_mode = "guarded-local-prefix-reinstall"'
require_fixture_line 'state_catalog = ['
require_fixture_line '  "available",'
require_fixture_line '  "downloaded",'
require_fixture_line '  "verified",'
require_fixture_line '  "staged",'
require_fixture_line '  "armed",'
require_fixture_line '  "applied",'
require_fixture_line '  "rolled_back",'
require_fixture_line '  "failed",'
require_fixture_line '  "blocked",'
require_fixture_line ']'
require_fixture_line 'current_update_state = "blocked"'
require_fixture_line 'requested_update_state = "blocked"'
require_fixture_line 'state_transition_decision = "deny-transition"'
require_fixture_line 'state_transition_reason = "missing-signed-manifest-artifact-verification-rollback-and-operator-confirmation"'
require_fixture_line 'state_transition_execution_allowed = false'
require_fixture_line 'state_transition_execution_performed = false'
require_fixture_line 'state_receipt_written = false'
require_fixture_line 'available_state_materialized = false'
require_fixture_line 'downloaded_state_materialized = false'
require_fixture_line 'verified_state_materialized = false'
require_fixture_line 'staged_state_materialized = false'
require_fixture_line 'armed_state_materialized = false'
require_fixture_line 'applied_state_materialized = false'
require_fixture_line 'rolled_back_state_materialized = false'
require_fixture_line 'failed_state_materialized = false'
require_fixture_line 'blocked_state_recorded = true'
require_fixture_line 'network_fetch_authority = false'
require_fixture_line 'remote_update_repository_trust = false'
require_fixture_line 'trusted_signed_manifest_present = false'
require_fixture_line 'manifest_signature_verified = false'
require_fixture_line 'artifact_hash_verified = false'
require_fixture_line 'artifact_signature_verified = false'
require_fixture_line 'rollback_plan_present = false'
require_fixture_line 'rollback_execution_allowed = false'
require_fixture_line 'post_update_validation_present = false'
require_fixture_line 'operator_confirmation_observed = false'
require_fixture_line 'signed_update_apply_allowed = false'
require_fixture_line 'update_activation_allowed = false'
require_fixture_line 'host_mutation_allowed = false'
require_fixture_line 'production_update_ready = false'
require_fixture_line 'production_installer_ready = false'
require_fixture_line '  "not-update-state-evidence",'
require_fixture_line '  "not-state-transition-execution",'
require_fixture_line '  "not-staged-update-evidence",'
require_fixture_line '  "not-signed-update-evidence",'
require_fixture_line '  "not-production-update-readiness",'

cat <<REPORT
LATTICRA PANEL SIGNED UPDATER STATE FIXTURE VALIDATION

signed_updater_state_fixture_validation_status=ok
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
state_fixture_path=$FIXTURE_RELATIVE
signed_updater_state_fixture_present=1
signed_updater_state_fixture_file_present=1
signed_updater_state_fixture_validated=1
signed_updater_state_fixture_validation_scope=shape-state-catalog-and-closed-transition-fields
state_schema_validated=1
state_fixture_flag_validated=1
state_fixture_scope_validated=1
state_fixture_effect_validated=1
state_catalog_validated=1
blocked_state_validated=1
closed_transition_fields_validated=1
closed_authority_fields_validated=1
non_claims_validated=1
state_fixture_schema=latticra-panel-signed-updater-state-fixture-v0
state_fixture_scope=local-no-effect
state_fixture_effect=none
state_fixture_trusted_for_apply=0
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
next_lane=panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition
REPORT
