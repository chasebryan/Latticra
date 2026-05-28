#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'production installer plan preview contract: %s\n' "$1" >&2
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

doc='docs/PRODUCTION_INSTALLER_PLAN_PREVIEW_CONTRACT.md'
preview='scripts/production-installer-plan-preview.sh'
guard='scripts/production-installer-preflight-guard.sh'
prod='docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md'
ledger='docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md'
artifact='fixtures/artifact/local-artifact-manifest.txt'

for file in "$doc" "$preview" "$guard" "$prod" "$ledger" "$artifact" Makefile
do
  require_file "$file"
done

require_contains 'Status: no-effect plan-preview contract' "$doc"
require_contains 'Evidence level: 10 target, no-effect plan preview' "$doc"
require_contains 'sh scripts/production-installer-plan-preview.sh supported-disposable-fedora' "$doc"
require_contains 'production_installer_preflight_guard_required=1' "$doc"
require_contains 'production_installer_preflight_guard_present=1' "$doc"
require_contains 'local_artifact_manifest_fixture_present=1' "$doc"
require_contains 'installer_install_plan_preview_present=1' "$doc"
require_contains 'installer_install_plan_preview_no_effect=1' "$doc"
require_contains 'preflight_guard_passed=<0-or-1>' "$doc"
require_contains 'planned_payload_entry=/usr/bin/latticra' "$doc"
require_contains 'planned_payload_entry=/usr/share/doc/latticra/README.md' "$doc"
require_contains 'install_performed=0' "$doc"
require_contains 'host_mutation_performed=0' "$doc"
require_contains 'network_allowed=0' "$doc"
require_contains 'receipt_written=0' "$doc"
require_contains 'root_required_to_preview=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'plan_entry=verify-artifact-manifest' "$doc"
require_contains 'plan_entry=validate-no-network-requirement' "$doc"
require_contains 'plan_entry=validate-operator-consent' "$doc"
require_contains 'plan_entry=review-cli-payload-placement' "$doc"
require_contains 'plan_entry=preserve-no-service-boot-kernel-selinux-effects' "$doc"
require_contains 'plan_entry=record-install-transcript-requirement' "$doc"
require_contains 'preview_blocks_non_fedora=1' "$doc"
require_contains 'preview_blocks_immutable_fedora=1' "$doc"
require_contains 'preview_blocks_network_required=1' "$doc"
require_contains 'preview_blocks_missing_artifact_manifest=1' "$doc"
require_contains 'preview_blocks_missing_operator_consent=1' "$doc"
require_contains 'Promote fixture-only artifact integrity status to tagged release artifact checksum and signature evidence.' "$doc"
require_contains 'This preview is not a production installer.' "$doc"

require_contains 'installer_install_plan_preview_present=1' "$prod"
require_contains 'installer_install_plan_preview_present=1' "$ledger"
require_contains 'production-installer-plan-preview' Makefile

guard_with_preview_output="$(sh "$guard" supported-disposable-fedora "$artifact" plan-preview-present)"
require_output_contains 'guard_decision=pass-no-effect' "$guard_with_preview_output"
require_output_contains 'denial=none' "$guard_with_preview_output"
require_output_contains 'installer_install_plan_preview_present=1' "$guard_with_preview_output"
require_output_contains 'preflight_passed=1' "$guard_with_preview_output"
require_output_contains 'install_performed=0' "$guard_with_preview_output"
require_output_contains 'host_mutation_performed=0' "$guard_with_preview_output"

preview_output="$(sh "$preview" supported-disposable-fedora)"
require_output_contains 'LATTICRA PRODUCTION INSTALLER PLAN PREVIEW' "$preview_output"
require_output_contains 'scenario=supported-disposable-fedora' "$preview_output"
require_output_contains 'preview_decision=rendered-no-effect' "$preview_output"
require_output_contains 'preflight_guard_passed=1' "$preview_output"
require_output_contains 'plan_entries_rendered=6' "$preview_output"
require_output_contains 'installer_install_plan_preview_present=1' "$preview_output"
require_output_contains 'installer_install_plan_preview_no_effect=1' "$preview_output"
require_output_contains 'planned_payload_entry=/usr/bin/latticra' "$preview_output"
require_output_contains 'planned_payload_entry=/usr/share/doc/latticra/README.md' "$preview_output"
require_output_contains 'plan_entry=verify-artifact-manifest' "$preview_output"
require_output_contains 'plan_entry=record-install-transcript-requirement' "$preview_output"
require_output_contains 'install_performed=0' "$preview_output"
require_output_contains 'host_mutation_performed=0' "$preview_output"
require_output_contains 'network_allowed=0' "$preview_output"
require_output_contains 'production_installer_ready=0' "$preview_output"

blocked_output="$(sh "$preview" non-fedora-host)"
require_output_contains 'scenario=non-fedora-host' "$blocked_output"
require_output_contains 'preview_decision=blocked-preflight' "$blocked_output"
require_output_contains 'preflight_guard_passed=0' "$blocked_output"
require_output_contains 'plan_entries_rendered=0' "$blocked_output"
require_output_contains 'install_performed=0' "$blocked_output"
require_output_contains 'production_installer_ready=0' "$blocked_output"

printf 'production_installer_plan_preview_contract: ok\n'
