#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'production installer sbom status contract: %s\n' "$1" >&2
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

doc='docs/PRODUCTION_INSTALLER_SBOM_STATUS_CONTRACT.md'
status_script='scripts/production-installer-sbom-status.sh'
test_script='scripts/test-production-installer-sbom-status-contract.sh'
fixture='fixtures/artifact/local-artifact-manifest.txt'
prod='docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md'
ledger='docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md'
index='docs/status/README.md'
installer_page='docs/installer.html'

for file in "$doc" "$status_script" "$test_script" "$fixture" "$prod" "$ledger" "$index" "$installer_page" Makefile
do
  require_file "$file"
done

require_contains 'Status: no-effect installer SBOM status contract' "$doc"
require_contains 'Evidence level: 10 target, status evidence only' "$doc"
require_contains 'sh scripts/production-installer-sbom-status.sh' "$doc"
require_contains 'artifact_sbom_path=none' "$doc"
require_contains 'artifact_sbom_recorded=0' "$doc"
require_contains 'production_installer_sbom_status_present=1' "$doc"
require_contains 'installer_sbom_status_present=1' "$doc"
require_contains 'installer_sbom_review_gate_present=1' "$doc"
require_contains 'installer_sbom_status_no_effect=1' "$doc"
require_contains 'sbom_artifact_present=0' "$doc"
require_contains 'sbom_format_declared=0' "$doc"
require_contains 'sbom_component_inventory_present=0' "$doc"
require_contains 'sbom_dependency_reviewed=0' "$doc"
require_contains 'sbom_vulnerability_reviewed=0' "$doc"
require_contains 'sbom_license_reviewed=0' "$doc"
require_contains 'sbom_reviewed=0' "$doc"
require_contains 'sbom_evidence_intake_validator_present=1' "$doc"
require_contains 'sbom_evidence_intake_validation_mode=no-effect-validation' "$doc"
require_contains 'sbom_evidence_candidate_valid=0' "$doc"
require_contains 'sbom_evidence_accepted_by_intake_validator=0' "$doc"
require_contains 'sbom_evidence_written_by_intake_validator=0' "$doc"
require_contains 'installer_sbom_promotion_allowed_by_intake_validator_alone=0' "$doc"
require_contains 'installer_sbom_recorded=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'It does not generate, review, sign, publish, or attach an SBOM to a release artifact.' "$doc"
require_contains 'sbom_artifact_present=1' "$doc"
require_contains 'sbom_reviewed=1' "$doc"
require_contains 'installer_sbom_recorded=1' "$doc"
require_contains 'Generate and review a production-installer SBOM for the tagged release artifact candidate.' "$doc"
require_contains 'This status record is not a production installer.' "$doc"

require_contains 'artifact_sbom_path=none' "$fixture"
require_contains 'artifact_sbom_recorded=0' "$fixture"

require_contains 'production_installer_sbom_status_present=1' "$prod"
require_contains 'installer_sbom_status_present=1' "$prod"
require_contains 'installer_sbom_review_gate_present=1' "$prod"
require_contains 'installer_sbom_status_no_effect=1' "$prod"
require_contains 'sbom_evidence_intake_validator_present=1' "$prod"
require_contains 'sbom_evidence_intake_validation_mode=no-effect-validation' "$prod"
require_contains 'sbom_evidence_candidate_valid=0' "$prod"
require_contains 'sbom_evidence_accepted_by_intake_validator=0' "$prod"
require_contains 'installer_sbom_recorded=0' "$prod"
require_contains 'production_installer_sbom_status_present=1' "$ledger"
require_contains 'installer_sbom_status_present=1' "$ledger"
require_contains 'installer_sbom_review_gate_present=1' "$ledger"
require_contains 'installer_sbom_status_no_effect=1' "$ledger"
require_contains 'sbom_evidence_intake_validator_present=1' "$ledger"
require_contains 'sbom_evidence_intake_validation_mode=no-effect-validation' "$ledger"
require_contains 'installer_sbom_recorded=0' "$ledger"
require_contains 'PRODUCTION_INSTALLER_SBOM_STATUS_CONTRACT.md' "$index"
require_contains 'PRODUCTION_INSTALLER_SBOM_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md' "$index"
require_contains 'installer_sbom_status' "$installer_page"
require_contains 'test-production-installer-sbom-status-contract.sh' Makefile

output="$(sh "$status_script")"
require_output_contains 'LATTICRA PRODUCTION INSTALLER SBOM STATUS' "$output"
require_output_contains 'status_mode=no-effect-installer-sbom-status' "$output"
require_output_contains 'production_installer_sbom_status_present=1' "$output"
require_output_contains 'installer_sbom_status_present=1' "$output"
require_output_contains 'installer_sbom_review_gate_present=1' "$output"
require_output_contains 'installer_sbom_status_no_effect=1' "$output"
require_output_contains 'local_artifact_manifest_fixture_present=1' "$output"
require_output_contains 'production_installer_artifact_integrity_status_present=1' "$output"
require_output_contains 'production_installer_release_artifact_promotion_gate_present=1' "$output"
require_output_contains 'release_artifact_promotion_gate_passed=0' "$output"
require_output_contains 'artifact_manifest_sbom_path=none' "$output"
require_output_contains 'artifact_manifest_sbom_recorded=0' "$output"
require_output_contains 'sbom_artifact_path=artifacts/release/latticra-production-installer.spdx.json' "$output"
require_output_contains 'sbom_artifact_present=0' "$output"
require_output_contains 'sbom_format_declared=0' "$output"
require_output_contains 'sbom_component_inventory_present=0' "$output"
require_output_contains 'sbom_dependency_reviewed=0' "$output"
require_output_contains 'sbom_vulnerability_reviewed=0' "$output"
require_output_contains 'sbom_license_reviewed=0' "$output"
require_output_contains 'sbom_reviewed=0' "$output"
require_output_contains 'sbom_evidence_intake_validator_present=1' "$output"
require_output_contains 'sbom_evidence_intake_validation_mode=no-effect-validation' "$output"
require_output_contains 'sbom_evidence_candidate_valid=0' "$output"
require_output_contains 'sbom_evidence_accepted_by_intake_validator=0' "$output"
require_output_contains 'sbom_evidence_written_by_intake_validator=0' "$output"
require_output_contains 'installer_sbom_promotion_allowed_by_intake_validator_alone=0' "$output"
require_output_contains 'installer_sbom_recorded=0' "$output"
require_output_contains 'install_performed=0' "$output"
require_output_contains 'host_mutation_performed=0' "$output"
require_output_contains 'network_allowed=0' "$output"
require_output_contains 'production_installer_ready=0' "$output"

printf 'production_installer_sbom_status_contract: ok\n'
