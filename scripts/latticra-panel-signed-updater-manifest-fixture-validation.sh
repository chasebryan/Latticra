#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-panel-signed-updater-manifest-fixture-validation.sh

Validates the local no-effect signed-updater manifest fixture shape for
Latticra Panel. It reads only the committed fixture and does not fetch updates,
trust a remote repository, verify artifacts, stage updates, write receipts,
mutate host state, or apply signed updates.
USAGE
}

require_fixture_line() {
  pattern="$1"
  if ! grep -Fxq -- "$pattern" "$FIXTURE"; then
    printf 'latticra panel signed updater manifest fixture validation: missing fixture line: %s\n' "$pattern" >&2
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
FIXTURE_RELATIVE='fixtures/latticra-panel/signed-updater-manifest.fixture.toml'
FIXTURE="$ROOT/$FIXTURE_RELATIVE"

. "$ROOT/scripts/lib/latticra-portable-paths.sh"

if [ ! -f "$FIXTURE" ]; then
  printf 'latticra panel signed updater manifest fixture validation: missing fixture: %s\n' "$FIXTURE_RELATIVE" >&2
  exit 1
fi

require_fixture_line 'manifest_schema = "latticra-panel-signed-updater-manifest-fixture-v0"'
require_fixture_line 'manifest_fixture = true'
require_fixture_line 'manifest_fixture_scope = "local-no-effect"'
require_fixture_line 'manifest_fixture_effect = "none"'
require_fixture_line 'manifest_fixture_trusted_for_apply = false'
require_fixture_line 'update_id = "panel-local-checkout-fixture"'
require_fixture_line 'update_channel = "lab"'
require_fixture_line 'source_strategy = "current-source-checkout"'
require_fixture_line 'apply_mode = "guarded-local-prefix-reinstall"'
require_fixture_line 'target_component = "latticra-panel"'
require_fixture_line 'target_version = "fixture-only"'
require_fixture_line 'network_fetch_authority = false'
require_fixture_line 'remote_update_repository_trust = false'
require_fixture_line 'signed_update_delivery_ready = false'
require_fixture_line 'trusted_signed_manifest_present = false'
require_fixture_line 'manifest_signature_present = false'
require_fixture_line 'manifest_signature_verified = false'
require_fixture_line 'artifact_hash_present = false'
require_fixture_line 'artifact_hash_verified = false'
require_fixture_line 'artifact_signature_present = false'
require_fixture_line 'artifact_signature_verified = false'
require_fixture_line 'channel_policy_present = false'
require_fixture_line 'compatibility_policy_present = false'
require_fixture_line 'rollback_plan_present = false'
require_fixture_line 'post_update_validation_present = false'
require_fixture_line 'operator_confirmation_observed = false'
require_fixture_line 'update_receipt_written = false'
require_fixture_line 'staged_update_allowed = false'
require_fixture_line 'signed_update_apply_allowed = false'
require_fixture_line 'host_mutation_allowed = false'
require_fixture_line 'production_update_ready = false'
require_fixture_line 'production_installer_ready = false'
require_fixture_line '  "not-a-trusted-update-manifest",'
require_fixture_line '  "not-signed-update-evidence",'
require_fixture_line '  "not-artifact-verification-evidence",'
require_fixture_line '  "not-network-update-evidence",'
require_fixture_line '  "not-production-update-readiness",'

cat <<REPORT
LATTICRA PANEL SIGNED UPDATER MANIFEST FIXTURE VALIDATION

signed_updater_manifest_fixture_validation_status=ok
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
manifest_fixture_path=$(portable_path "$FIXTURE_RELATIVE")
signed_updater_manifest_fixture_present=1
signed_updater_manifest_fixture_file_present=1
signed_updater_manifest_fixture_validated=1
signed_updater_manifest_fixture_validation_scope=shape-and-closed-authority-fields
manifest_schema_validated=1
manifest_fixture_flag_validated=1
manifest_fixture_scope_validated=1
manifest_fixture_effect_validated=1
local_checkout_strategy_validated=1
closed_authority_fields_validated=1
non_claims_validated=1
manifest_fixture_schema=latticra-panel-signed-updater-manifest-fixture-v0
manifest_fixture_scope=local-no-effect
manifest_fixture_effect=none
manifest_fixture_trusted_for_apply=0
manifest_fixture_validated_for_apply=0
signed_updater_manifest_fixture_valid_for_apply=0
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
channel_policy_required=1
channel_policy_present=0
compatibility_policy_required=1
compatibility_policy_present=0
rollback_plan_required=1
rollback_plan_present=0
rollback_evidence_present=0
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
next_lane=panel-signed-updater-state-transition-denial-disposition-closeout-audit-review-disposition-review-closeout
REPORT
