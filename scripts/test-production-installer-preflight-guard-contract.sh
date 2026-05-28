#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'production installer preflight guard contract: %s\n' "$1" >&2
  exit 1
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file"
}

require_contains() {
  pattern="$1"
  file="$2"
  grep -Fq -- "$pattern" "$file" ||
    fail "missing required pattern in $file: $pattern"
}

require_output_contains() {
  pattern="$1"
  output="$2"
  case "$output" in
    *"$pattern"*) ;;
    *) fail "missing required output pattern: $pattern" ;;
  esac
}

doc='docs/PRODUCTION_INSTALLER_PREFLIGHT_GUARD_CONTRACT.md'
guard='scripts/production-installer-preflight-guard.sh'
prod='docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md'
ledger='docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md'
artifact='fixtures/artifact/local-artifact-manifest.txt'
host_status='docs/status/FEDORA_HOST_INSTALL_PREFLIGHT_STATUS.md'

for file in "$doc" "$guard" "$prod" "$ledger" "$artifact" "$host_status" Makefile
do
  require_file "$file"
done

require_contains 'Status: no-effect guard contract' "$doc"
require_contains 'Evidence level: 10 target, no-effect preflight guard' "$doc"
require_contains 'sh scripts/production-installer-preflight-guard.sh supported-disposable-fedora' "$doc"
require_contains 'fedora_host_install_preflight_prerequisite_present=1' "$doc"
require_contains 'fedora_host_install_preflight_reused=1' "$doc"
require_contains 'local_artifact_manifest_fixture_required=1' "$doc"
require_contains 'local_artifact_manifest_fixture_present=1' "$doc"
require_contains 'artifact_manifest_fixture_path=fixtures/artifact/local-artifact-manifest.txt' "$doc"
require_contains 'installer_preflight_guard_present=1' "$doc"
require_contains 'installer_preflight_blocks_unsupported_targets=1' "$doc"
require_contains 'installer_preflight_guard_no_effect=1' "$doc"
require_contains 'installer_install_plan_preview_present=<0-or-1>' "$doc"
require_contains 'preflight_passed=<0-or-1>' "$doc"
require_contains 'install_performed=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'network_allowed=0' "$doc"
require_contains 'root_required_to_classify=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'supported_target_family=fedora-disposable-vm' "$doc"
require_contains 'supported_target_mutable_fedora_only=1' "$doc"
require_contains 'blocked_target_non_fedora=1' "$doc"
require_contains 'blocked_target_immutable_fedora=1' "$doc"
require_contains 'blocked_target_network_required=1' "$doc"
require_contains 'blocked_target_missing_artifact_manifest=1' "$doc"
require_contains 'blocked_target_missing_operator_consent=1' "$doc"
require_contains 'blocked_target_missing_install_plan_preview=1' "$doc"
require_contains 'Promote fixture-only artifact integrity status to tagged release artifact checksum and signature evidence.' "$doc"
require_contains 'This guard is not a production installer.' "$doc"

require_contains 'installer_preflight_guard_present=1' "$prod"
require_contains 'installer_preflight_blocks_unsupported_targets=1' "$prod"
require_contains 'installer_install_plan_preview_present=1' "$prod"
require_contains 'production_installer_ready=0' "$prod"
require_contains 'installer_preflight_guard_present=1' "$ledger"
require_contains 'installer_install_plan_preview_present=1' "$ledger"
require_contains 'production-installer-preflight-guard' Makefile
require_contains 'Fedora host install preflight classifier' "$host_status"

supported_output="$(sh "$guard" supported-disposable-fedora)"
require_output_contains 'LATTICRA PRODUCTION INSTALLER PREFLIGHT GUARD' "$supported_output"
require_output_contains 'scenario=supported-disposable-fedora' "$supported_output"
require_output_contains 'guard_decision=blocked-missing-install-plan-preview' "$supported_output"
require_output_contains 'denial=missing-install-plan-preview' "$supported_output"
require_output_contains 'artifact_manifest_present=1' "$supported_output"
require_output_contains 'target_supported=1' "$supported_output"
require_output_contains 'install_candidate=1' "$supported_output"
require_output_contains 'preflight_passed=0' "$supported_output"
require_output_contains 'install_performed=0' "$supported_output"
require_output_contains 'host_mutation_performed=0' "$supported_output"
require_output_contains 'production_installer_ready=0' "$supported_output"

supported_preview_output="$(sh "$guard" supported-disposable-fedora "$artifact" plan-preview-present)"
require_output_contains 'scenario=supported-disposable-fedora' "$supported_preview_output"
require_output_contains 'guard_decision=pass-no-effect' "$supported_preview_output"
require_output_contains 'denial=none' "$supported_preview_output"
require_output_contains 'installer_install_plan_preview_present=1' "$supported_preview_output"
require_output_contains 'preflight_passed=1' "$supported_preview_output"
require_output_contains 'install_performed=0' "$supported_preview_output"
require_output_contains 'host_mutation_performed=0' "$supported_preview_output"

non_fedora_output="$(sh "$guard" non-fedora-host)"
require_output_contains 'scenario=non-fedora-host' "$non_fedora_output"
require_output_contains 'guard_decision=blocked-unsupported-target' "$non_fedora_output"
require_output_contains 'unsupported_target_blocked=1' "$non_fedora_output"
require_output_contains 'preflight_passed=0' "$non_fedora_output"

immutable_output="$(sh "$guard" immutable-fedora-host)"
require_output_contains 'scenario=immutable-fedora-host' "$immutable_output"
require_output_contains 'guard_decision=blocked-immutable-target' "$immutable_output"
require_output_contains 'unsupported_target_blocked=1' "$immutable_output"
require_output_contains 'immutable_fedora_ready=0' "$immutable_output"

network_output="$(sh "$guard" network-required)"
require_output_contains 'scenario=network-required' "$network_output"
require_output_contains 'guard_decision=blocked-network-required' "$network_output"
require_output_contains 'network_policy_blocked=1' "$network_output"
require_output_contains 'network_allowed=0' "$network_output"

missing_artifact_output="$(sh "$guard" missing-artifact-manifest)"
require_output_contains 'scenario=missing-artifact-manifest' "$missing_artifact_output"
require_output_contains 'guard_decision=blocked-missing-artifact-manifest' "$missing_artifact_output"
require_output_contains 'artifact_manifest_present=0' "$missing_artifact_output"

missing_consent_output="$(sh "$guard" missing-operator-consent)"
require_output_contains 'scenario=missing-operator-consent' "$missing_consent_output"
require_output_contains 'guard_decision=blocked-missing-operator-consent' "$missing_consent_output"
require_output_contains 'operator_consent_present=0' "$missing_consent_output"

printf 'production_installer_preflight_guard_contract: ok\n'
