#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fixture="${1:-fixtures/artifact/local-artifact-manifest.txt}"
sbom_artifact_path="${2:-artifacts/release/latticra-production-installer.spdx.json}"

if [ ! -f "$fixture" ]; then
  printf 'production installer sbom status: missing fixture: %s\n' "$fixture" >&2
  exit 1
fi

require_line() {
  pattern="$1"
  if ! grep -Fq -- "$pattern" "$fixture"; then
    printf 'production installer sbom status: missing fixture line: %s\n' "$pattern" >&2
    exit 1
  fi
}

require_line 'artifact_sbom_path=none'
require_line 'artifact_sbom_recorded=0'
require_line 'production_installer_ready=0'

sbom_artifact_present=0
if [ -f "$sbom_artifact_path" ]; then
  sbom_artifact_present=1
fi

printf '%s\n' \
  'LATTICRA PRODUCTION INSTALLER SBOM STATUS' \
  'status_version=1' \
  'status_mode=no-effect-installer-sbom-status' \
  'production_installer_sbom_status_present=1' \
  'installer_sbom_status_present=1' \
  'installer_sbom_review_gate_present=1' \
  'installer_sbom_status_no_effect=1' \
  'local_artifact_manifest_fixture_required=1' \
  'local_artifact_manifest_fixture_present=1' \
  "artifact_manifest_fixture_path=$fixture" \
  'production_installer_artifact_integrity_status_present=1' \
  'production_installer_release_artifact_promotion_gate_present=1' \
  'release_artifact_promotion_gate_passed=0' \
  'artifact_manifest_sbom_path=none' \
  'artifact_manifest_sbom_recorded=0' \
  "sbom_artifact_path=$sbom_artifact_path" \
  "sbom_artifact_present=$sbom_artifact_present" \
  'sbom_format_declared=0' \
  'sbom_component_inventory_present=0' \
  'sbom_dependency_reviewed=0' \
  'sbom_vulnerability_reviewed=0' \
  'sbom_license_reviewed=0' \
  'sbom_reviewed=0' \
  'sbom_evidence_intake_validator_present=1' \
  'sbom_evidence_intake_validation_mode=no-effect-validation' \
  'sbom_evidence_candidate_valid=0' \
  'sbom_evidence_accepted_by_intake_validator=0' \
  'sbom_evidence_written_by_intake_validator=0' \
  'installer_sbom_promotion_allowed_by_intake_validator_alone=0' \
  'installer_sbom_recorded=0' \
  'install_performed=0' \
  'host_mutation_performed=0' \
  'network_allowed=0' \
  'no_effect=1' \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0'
