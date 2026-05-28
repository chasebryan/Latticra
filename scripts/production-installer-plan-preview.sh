#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

scenario="${1:-supported-disposable-fedora}"
artifact_manifest="${2:-fixtures/artifact/local-artifact-manifest.txt}"
guard='scripts/production-installer-preflight-guard.sh'

if [ "$scenario" = 'missing-artifact-manifest' ]; then
  artifact_manifest='fixtures/artifact/missing-local-artifact-manifest.txt'
fi

guard_output="$(sh "$guard" "$scenario" "$artifact_manifest" plan-preview-present)"

preflight_guard_passed=0
preview_decision='blocked-preflight'
plan_entries_rendered=0

case "$guard_output" in
  *"preflight_passed=1"*)
    preflight_guard_passed=1
    preview_decision='rendered-no-effect'
    plan_entries_rendered=6
    ;;
esac

printf '%s\n' \
  'LATTICRA PRODUCTION INSTALLER PLAN PREVIEW' \
  'plan_preview_version=1' \
  'plan_preview_mode=no-effect-renderer' \
  "scenario=$scenario" \
  'installer_install_plan_preview_present=1' \
  'installer_install_plan_preview_no_effect=1' \
  'preflight_guard_required=1' \
  'preflight_guard_present=1' \
  "preflight_guard_passed=$preflight_guard_passed" \
  "preview_decision=$preview_decision" \
  "plan_entries_rendered=$plan_entries_rendered" \
  "artifact_manifest_path=$artifact_manifest" \
  'planned_payload_entry=/usr/bin/latticra' \
  'planned_payload_entry=/usr/share/doc/latticra/README.md'

if [ "$preflight_guard_passed" -eq 1 ]; then
  printf '%s\n' \
    'plan_entry=verify-artifact-manifest' \
    'plan_entry=validate-no-network-requirement' \
    'plan_entry=validate-operator-consent' \
    'plan_entry=review-cli-payload-placement' \
    'plan_entry=preserve-no-service-boot-kernel-selinux-effects' \
    'plan_entry=record-install-transcript-requirement'
fi

printf '%s\n' \
  'install_performed=0' \
  'host_mutation_performed=0' \
  'network_allowed=0' \
  'receipt_written=0' \
  'root_required_to_preview=0' \
  'no_effect=1' \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0'
