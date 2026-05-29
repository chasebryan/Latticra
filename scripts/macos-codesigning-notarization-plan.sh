#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  macos-codesigning-notarization-plan.sh

Emits the no-effect macOS codesigning and notarization plan. It records future
prerequisites and evidence requirements, but it does not sign an app, submit
notarization, access Apple credentials, mutate host state, or claim readiness.
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
MACOS CODESIGNING AND NOTARIZATION PLAN

macos_codesigning_notarization_plan_status=ok
repo_root=$ROOT
host_kernel_name=$UNAME_S
host_arch=$UNAME_M
macos_codesigning_notarization_plan_present=1
macos_codesigning_notarization_plan_state=defined-no-effect
macos_codesigning_notarization_plan_decision=plan-defined-evidence-not-present
macos_codesigned_app_evidence_present=0
macos_notarized_app_evidence_present=0
macos_verification_transcript_contract_present=1
macos_verification_transcript_evidence_present=0
macos_install_verified=0
commit_user_local_managed_artifacts=0
managed_app_bundle_present_required=1
verification_transcript_evidence_present_required=1
receipt_manifest_present_required=1
candidate_asset_probe_present_required=1
commit_gate_state_closed_until_evidence_required=1
release_signing_identity_reference_contract_present_required=1
release_signing_identity_reference_status_present_required=1
release_artifact_candidate_preflight_contract_present_required=1
operator_signing_intent_review_required=1
operator_notarization_intent_review_required=1
reviewed_apple_account_boundary_required=1
reviewed_network_boundary_required=1
reviewed_staple_boundary_required=1
developer_id_application_identity_reference=planned
codesign_entitlements_scope=planned
hardened_runtime_boundary=planned
notarytool_submission_materials=planned
ticket_stapling_boundary=planned
app_bundle_path_recorded_required=1
signing_identity_reference_recorded_required=1
codesign_command_transcript_required=1
codesign_verification_transcript_required=1
notary_submission_identifier_recorded_required=1
notary_status_recorded_required=1
staple_transcript_required=1
spctl_assessment_transcript_required=1
authority_denial_fields_required=1
review_signoff_required=1
codesign_invocation_performed=0
notary_submission_performed=0
ticket_staple_performed=0
keychain_profile_read_performed=0
secret_key_material_read_performed=0
apple_account_auth_performed=0
network_performed=0
host_mutation_performed=0
root_authority=0
keychain_authority=0
tcc_bypass_authority=0
runtime_authority_granted=0
production_installer_ready=0
next_lane=macos-controlled-os-integration-contracts-plan
REPORT
