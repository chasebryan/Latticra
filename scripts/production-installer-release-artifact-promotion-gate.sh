#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

release_artifact_path="${1:-artifacts/release/latticra-production-installer.rpm}"

release_artifact_present=0
if [ -f "$release_artifact_path" ]; then
  release_artifact_present=1
fi

printf '%s\n' \
  'LATTICRA PRODUCTION INSTALLER RELEASE ARTIFACT PROMOTION GATE' \
  'gate_version=1' \
  'gate_mode=no-effect-release-artifact-promotion' \
  'release_artifact_promotion_gate_present=1' \
  'release_artifact_promotion_gate_no_effect=1' \
  'release_artifact_promotion_gate_passed=0' \
  'release_artifact_promotion_gate_decision=blocked-missing-tagged-release-artifact' \
  'release_artifact_candidate_preflight_present=1' \
  'release_artifact_candidate_preflight_passed=0' \
  'release_artifact_candidate_inputs_satisfied=0' \
  'release_artifact_promotion_required_evidence_count=9' \
  'release_artifact_promotion_satisfied_evidence_count=0' \
  "release_artifact_path=$release_artifact_path" \
  "release_artifact_present=$release_artifact_present" \
  'release_artifact_built_from_tag=0' \
  'release_artifact_reproducible=0' \
  'release_artifact_sha256_recorded=0' \
  'release_artifact_signature_present=0' \
  'release_artifact_signature_verified=0' \
  'release_public_key_documented=0' \
  'signature_verification_documented=0' \
  'artifact_integrity_reviewed=0' \
  'production_installer_artifact_integrity_status_required=1' \
  'artifact_integrity_status_present=1' \
  'installer_artifact_checksum_status_present=1' \
  'installer_artifact_signature_status_present=1' \
  'local_artifact_manifest_fixture_present=1' \
  'production_installer_preflight_guard_present=1' \
  'installer_install_plan_preview_present=1' \
  'installer_artifact_reproducible=0' \
  'installer_artifact_checksum_recorded=0' \
  'installer_artifact_signature_recorded=0' \
  'installer_public_key_documented=0' \
  'install_performed=0' \
  'host_mutation_performed=0' \
  'network_allowed=0' \
  'no_effect=1' \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0'
