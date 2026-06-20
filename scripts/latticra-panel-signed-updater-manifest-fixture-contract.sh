#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  latticra-panel-signed-updater-manifest-fixture-contract.sh

Emits the local no-effect signed-updater manifest fixture contract for
Latticra Panel. It does not fetch updates, trust a remote repository, verify
artifacts, stage updates, write receipts, mutate host state, or apply signed
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
FIXTURE_RELATIVE='fixtures/latticra-panel/signed-updater-manifest.fixture.toml'
FIXTURE="$ROOT/$FIXTURE_RELATIVE"

if [ -f "$FIXTURE" ]; then
  MANIFEST_FIXTURE_FILE_PRESENT=1
  CONTRACT_STATUS=ok
else
  MANIFEST_FIXTURE_FILE_PRESENT=0
  CONTRACT_STATUS=missing-fixture
fi

cat <<REPORT
LATTICRA PANEL SIGNED UPDATER MANIFEST FIXTURE CONTRACT

signed_updater_manifest_fixture_contract_status=$CONTRACT_STATUS
repo_root=$ROOT
host_kernel_name=$UNAME_S
host_arch=$UNAME_M
latticra_panel_updater_present=1
latticra_panel_updater_owned=1
signed_updater_delivery_gate_present=1
signed_updater_delivery_gate_state=closed
signed_updater_denial_transcript_present=1
manifest_fixture_path=$(portable_path "$FIXTURE_RELATIVE")
signed_updater_manifest_fixture_contract_present=1
signed_updater_manifest_fixture_present=$MANIFEST_FIXTURE_FILE_PRESENT
signed_updater_manifest_fixture_file_present=$MANIFEST_FIXTURE_FILE_PRESENT
manifest_fixture_schema=latticra-panel-signed-updater-manifest-fixture-v0
manifest_fixture_scope=local-no-effect
manifest_fixture_effect=none
manifest_fixture_trusted_for_apply=0
manifest_fixture_validated_for_apply=0
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
