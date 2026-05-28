#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  production-installer-sbom-evidence-template.sh \
    [--sbom <path>] \
    [--dependency-review <path>] \
    [--vulnerability-review <path>] \
    [--license-review <path>] \
    [--review <path>] \
    [--evidence <path>]

Prints a no-effect template for a future production-installer SBOM evidence
bundle. It does not generate an SBOM, calculate evidence hashes, write evidence
files, accept evidence, attach an SBOM, pass promotion, publish, install,
invoke package managers, use network access, or mutate the host.
USAGE
}

fail() {
  printf 'production installer sbom evidence template: %s\n' "$1" >&2
  exit "${2:-1}"
}

presence() {
  if [ -f "$1" ]; then
    printf '1\n'
  else
    printf '0\n'
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  grep -Fq -- "$pattern" "$file" || fail "missing required pattern in $file: $pattern" 65
}

SBOM='artifacts/release/latticra-production-installer.spdx.json'
DEPENDENCY_REVIEW='artifacts/release/latticra-production-installer-dependency-review.txt'
VULNERABILITY_REVIEW='artifacts/release/latticra-production-installer-vulnerability-review.txt'
LICENSE_REVIEW='artifacts/release/latticra-production-installer-license-review.txt'
REVIEW='artifacts/release/latticra-production-installer-sbom-review.txt'
EVIDENCE='artifacts/release/latticra-production-installer-sbom-evidence.txt'

while [ "$#" -gt 0 ]; do
  case "$1" in
    --sbom)
      [ "$#" -ge 2 ] || fail 'missing value for --sbom' 64
      SBOM="$2"
      shift 2
      ;;
    --dependency-review)
      [ "$#" -ge 2 ] || fail 'missing value for --dependency-review' 64
      DEPENDENCY_REVIEW="$2"
      shift 2
      ;;
    --vulnerability-review)
      [ "$#" -ge 2 ] || fail 'missing value for --vulnerability-review' 64
      VULNERABILITY_REVIEW="$2"
      shift 2
      ;;
    --license-review)
      [ "$#" -ge 2 ] || fail 'missing value for --license-review' 64
      LICENSE_REVIEW="$2"
      shift 2
      ;;
    --review)
      [ "$#" -ge 2 ] || fail 'missing value for --review' 64
      REVIEW="$2"
      shift 2
      ;;
    --evidence)
      [ "$#" -ge 2 ] || fail 'missing value for --evidence' 64
      EVIDENCE="$2"
      shift 2
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      fail "unknown argument: $1" 64
      ;;
  esac
done

require_contains 'production_installer_ready=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'sbom_evidence_intake_validator_present=1' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'sbom_evidence_intake_validator_present=1' docs/PRODUCTION_INSTALLER_SBOM_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md
require_contains 'sbom_evidence_status=complete' docs/PRODUCTION_INSTALLER_SBOM_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md
require_contains 'release_artifact_promotion_gate_passed=0' docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
require_contains 'Production quality blocker ledger' README.md

cat <<TEMPLATE
LATTICRA PRODUCTION INSTALLER SBOM EVIDENCE TEMPLATE
template_status=ok
sbom_evidence_template_present=1
sbom_evidence_template_mode=no-effect-template
sbom_evidence_template_decision=blocked-template-only-no-evidence-write
sbom_evidence_template_complete=0
sbom_evidence_intake_validator_present=1
sbom_evidence_intake_validation_mode=no-effect-validation
sbom_evidence_path=$EVIDENCE
sbom_artifact_path=$SBOM
sbom_dependency_review_path=$DEPENDENCY_REVIEW
sbom_vulnerability_review_path=$VULNERABILITY_REVIEW
sbom_license_review_path=$LICENSE_REVIEW
sbom_review_path=$REVIEW
sbom_artifact_file_present=$(presence "$SBOM")
sbom_dependency_review_file_present=$(presence "$DEPENDENCY_REVIEW")
sbom_vulnerability_review_file_present=$(presence "$VULNERABILITY_REVIEW")
sbom_license_review_file_present=$(presence "$LICENSE_REVIEW")
sbom_review_file_present=$(presence "$REVIEW")

[required_evidence_fields]
LATTICRA PRODUCTION INSTALLER SBOM EVIDENCE
sbom_evidence_status=complete
sbom_artifact_present=1
sbom_format_declared=1
sbom_format=spdx-json
sbom_component_inventory_present=1
sbom_dependency_reviewed=1
sbom_vulnerability_reviewed=1
sbom_license_reviewed=1
sbom_reviewed=1
installer_sbom_recorded=1
sbom_artifact_sha256=<required-sbom-sha256>
sbom_dependency_review_sha256=<required-dependency-review-sha256>
sbom_vulnerability_review_sha256=<required-vulnerability-review-sha256>
sbom_license_review_sha256=<required-license-review-sha256>
sbom_review_sha256=<required-sbom-review-sha256>
release_artifact_promotion_gate_passed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
host_mutation_performed=0

[template_non_effects]
sbom_generated_by_template=0
sbom_evidence_written_by_template=0
sbom_evidence_accepted_by_template=0
sbom_evidence_accepted_by_intake_validator=0
sbom_evidence_written_by_intake_validator=0
installer_sbom_promotion_allowed_by_intake_validator_alone=0
release_artifact_promotion_gate_passed=0
installer_sbom_recorded=0
sbom_attached_to_release_artifact=0
release_artifact_created=0
source_archive_created=0
rpm_build_invoked=0
rpmbuild_invoked=0
rpm_invoked=0
artifact_published=0
install_performed=0
package_manager_invoked=0
network_allowed=0
host_mutation_performed=0
production_installer_ready=0
TEMPLATE
