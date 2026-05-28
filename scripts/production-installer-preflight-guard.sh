#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

scenario="${1:-supported-disposable-fedora}"
artifact_manifest="${2:-fixtures/artifact/local-artifact-manifest.txt}"
plan_preview_state="${3:-missing-install-plan-preview}"

artifact_manifest_present=0
installer_install_plan_preview_present=0
target_supported=0
unsupported_target_blocked=0
network_policy_blocked=0
operator_consent_present=1
install_candidate=0
preflight_passed=0
guard_decision='blocked-unknown-scenario'
denial='unknown-scenario'
host_classification='unknown-host'
target_classification='unknown-target'
supported_target_family='fedora-disposable-vm'

if [ "$plan_preview_state" = 'plan-preview-present' ]; then
  installer_install_plan_preview_present=1
fi

if [ -f "$artifact_manifest" ]; then
  artifact_manifest_present=1
fi

case "$scenario" in
  supported-disposable-fedora)
    target_supported=1
    host_classification='mutable-fedora-host'
    target_classification='fedora-disposable-vm'
    if [ "$artifact_manifest_present" -eq 1 ]; then
      install_candidate=1
      if [ "$installer_install_plan_preview_present" -eq 1 ]; then
        guard_decision='pass-no-effect'
        denial='none'
        preflight_passed=1
      else
        guard_decision='blocked-missing-install-plan-preview'
        denial='missing-install-plan-preview'
      fi
    else
      guard_decision='blocked-missing-artifact-manifest'
      denial='missing-artifact-manifest'
    fi
    ;;
  non-fedora-host)
    unsupported_target_blocked=1
    host_classification='non-fedora-host'
    target_classification='unsupported-host'
    guard_decision='blocked-unsupported-target'
    denial='non-fedora-host'
    ;;
  immutable-fedora-host)
    unsupported_target_blocked=1
    host_classification='immutable-fedora-host'
    target_classification='unsupported-immutable-fedora'
    guard_decision='blocked-immutable-target'
    denial='immutable-fedora-host'
    ;;
  network-required)
    target_supported=1
    network_policy_blocked=1
    host_classification='mutable-fedora-host'
    target_classification='fedora-disposable-vm'
    guard_decision='blocked-network-required'
    denial='network-required'
    ;;
  missing-artifact-manifest)
    artifact_manifest='fixtures/artifact/missing-local-artifact-manifest.txt'
    artifact_manifest_present=0
    target_supported=1
    host_classification='mutable-fedora-host'
    target_classification='fedora-disposable-vm'
    guard_decision='blocked-missing-artifact-manifest'
    denial='missing-artifact-manifest'
    ;;
  missing-operator-consent)
    target_supported=1
    operator_consent_present=0
    host_classification='mutable-fedora-host'
    target_classification='fedora-disposable-vm'
    guard_decision='blocked-missing-operator-consent'
    denial='missing-operator-consent'
    ;;
  *)
    printf 'production installer preflight guard: unsupported scenario: %s\n' "$scenario" >&2
    exit 2
    ;;
esac

printf '%s\n' \
  'LATTICRA PRODUCTION INSTALLER PREFLIGHT GUARD' \
  'guard_version=1' \
  'guard_mode=no-effect-classifier' \
  "scenario=$scenario" \
  "guard_decision=$guard_decision" \
  "denial=$denial" \
  'installer_preflight_guard_present=1' \
  'installer_preflight_blocks_unsupported_targets=1' \
  'installer_preflight_guard_no_effect=1' \
  'fedora_host_install_preflight_prerequisite_present=1' \
  'fedora_host_install_preflight_reused=1' \
  'local_artifact_manifest_fixture_required=1' \
  "artifact_manifest_path=$artifact_manifest" \
  "artifact_manifest_present=$artifact_manifest_present" \
  "host_classification=$host_classification" \
  "target_classification=$target_classification" \
  "supported_target_family=$supported_target_family" \
  "target_supported=$target_supported" \
  "unsupported_target_blocked=$unsupported_target_blocked" \
  "network_policy_blocked=$network_policy_blocked" \
  "operator_consent_present=$operator_consent_present" \
  "installer_install_plan_preview_present=$installer_install_plan_preview_present" \
  "preflight_passed=$preflight_passed" \
  "install_candidate=$install_candidate" \
  'install_performed=0' \
  'host_mutation_performed=0' \
  'network_allowed=0' \
  'root_required_to_classify=0' \
  'no_effect=1' \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0'
