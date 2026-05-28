#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  production-installer-sbom-evidence-intake.sh \
    --sbom <path> \
    --dependency-review <path> \
    --vulnerability-review <path> \
    --license-review <path> \
    --review <path> \
    --evidence <path>

Validates a future production-installer SBOM evidence bundle.
It checks local file presence, SBOM shape markers, evidence hashes,
required review markers, and placeholder absence. It does not generate,
accept, publish, attach, or promote an SBOM, and it does not mutate the host.
Evidence manifests declare sbom_format=spdx-json or sbom_format=cyclonedx-json.
USAGE
}

fail() {
  printf 'production installer sbom evidence intake: %s\n' "$1" >&2
  exit "${2:-1}"
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file" 66
}

require_nonempty_file() {
  file="$1"
  require_file "$file"
  [ -s "$file" ] || fail "empty file: $file"
}

require_contains() {
  pattern="$1"
  file="$2"
  grep -Fq -- "$pattern" "$file" || fail "missing required pattern in $file: $pattern"
}

require_absent() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    fail "unexpected pattern in $file: $pattern"
  fi
}

reject_placeholders() {
  file="$1"
  if grep -Eq -- '<required|<placeholder>|TODO|TBD' "$file"; then
    fail "placeholder value is not acceptable in SBOM evidence"
  fi
}

sha256_file() {
  file="$1"
  if command -v sha256sum >/dev/null 2>&1; then
    set -- $(sha256sum "$file")
    printf '%s\n' "$1" | tr 'A-F' 'a-f'
  elif command -v shasum >/dev/null 2>&1; then
    set -- $(shasum -a 256 "$file")
    printf '%s\n' "$1" | tr 'A-F' 'a-f'
  else
    fail 'missing sha256 tool'
  fi
}

require_digest() {
  digest="$1"
  label="$2"
  printf '%s\n' "$digest" | grep -Eq '^[0-9a-f]{64}$' ||
    fail "invalid sha256 digest for $label"
}

detect_sbom_format() {
  file="$1"
  if grep -Fq '"spdxVersion"' "$file" &&
     grep -Fq '"SPDXID"' "$file" &&
     grep -Fq '"packages"' "$file"; then
    printf '%s\n' 'spdx-json'
    return 0
  fi
  if grep -Fq '"bomFormat"' "$file" &&
     grep -Fq 'CycloneDX' "$file" &&
     grep -Fq '"components"' "$file"; then
    printf '%s\n' 'cyclonedx-json'
    return 0
  fi
  fail 'unsupported SBOM format markers: expected SPDX JSON or CycloneDX JSON'
}

SBOM=''
DEPENDENCY_REVIEW=''
VULNERABILITY_REVIEW=''
LICENSE_REVIEW=''
REVIEW=''
EVIDENCE=''

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

[ -n "$SBOM" ] || fail 'missing --sbom path' 64
[ -n "$DEPENDENCY_REVIEW" ] || fail 'missing --dependency-review path' 64
[ -n "$VULNERABILITY_REVIEW" ] || fail 'missing --vulnerability-review path' 64
[ -n "$LICENSE_REVIEW" ] || fail 'missing --license-review path' 64
[ -n "$REVIEW" ] || fail 'missing --review path' 64
[ -n "$EVIDENCE" ] || fail 'missing --evidence path' 64

for file in "$SBOM" "$DEPENDENCY_REVIEW" "$VULNERABILITY_REVIEW" "$LICENSE_REVIEW" "$REVIEW" "$EVIDENCE"
do
  require_nonempty_file "$file"
done

require_file docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_file docs/PRODUCTION_INSTALLER_SBOM_STATUS_CONTRACT.md
require_file docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_PROMOTION_GATE_CONTRACT.md
require_file scripts/production-installer-sbom-status.sh
require_file docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md
require_file README.md

require_contains 'production_installer_ready=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'release_artifact_promotion_gate_passed=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'production_installer_sbom_status_present=1' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'installer_sbom_status_present=1' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'installer_sbom_recorded=0' docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md
require_contains 'Status: no-effect installer SBOM status contract' docs/PRODUCTION_INSTALLER_SBOM_STATUS_CONTRACT.md
require_contains 'release_artifact_promotion_gate_present=1' docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_PROMOTION_GATE_CONTRACT.md
require_contains 'release_artifact_promotion_gate_passed=0' docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md

sbom_format="$(detect_sbom_format "$SBOM")"
require_contains '"name"' "$SBOM"

sbom_sha256="$(sha256_file "$SBOM")"
dependency_review_sha256="$(sha256_file "$DEPENDENCY_REVIEW")"
vulnerability_review_sha256="$(sha256_file "$VULNERABILITY_REVIEW")"
license_review_sha256="$(sha256_file "$LICENSE_REVIEW")"
review_sha256="$(sha256_file "$REVIEW")"

require_digest "$sbom_sha256" 'SBOM'
require_digest "$dependency_review_sha256" 'dependency review'
require_digest "$vulnerability_review_sha256" 'vulnerability review'
require_digest "$license_review_sha256" 'license review'
require_digest "$review_sha256" 'SBOM review'

for marker in \
  'LATTICRA PRODUCTION INSTALLER SBOM EVIDENCE' \
  'sbom_evidence_status=complete' \
  'sbom_artifact_present=1' \
  'sbom_format_declared=1' \
  "sbom_format=$sbom_format" \
  'sbom_component_inventory_present=1' \
  'sbom_dependency_reviewed=1' \
  'sbom_vulnerability_reviewed=1' \
  'sbom_license_reviewed=1' \
  'sbom_reviewed=1' \
  'installer_sbom_recorded=1' \
  "sbom_artifact_sha256=$sbom_sha256" \
  "sbom_dependency_review_sha256=$dependency_review_sha256" \
  "sbom_vulnerability_review_sha256=$vulnerability_review_sha256" \
  "sbom_license_review_sha256=$license_review_sha256" \
  "sbom_review_sha256=$review_sha256" \
  'release_artifact_promotion_gate_passed=0' \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0' \
  'host_mutation_performed=0'
do
  require_contains "$marker" "$EVIDENCE"
done

reject_placeholders "$EVIDENCE"

for forbidden_claim in \
  'sbom_evidence_accepted_by_intake_validator=1' \
  'sbom_evidence_written_by_intake_validator=1' \
  'installer_sbom_promotion_allowed_by_intake_validator_alone=1' \
  'release_artifact_promotion_gate_passed=1' \
  'production_installer_ready=1' \
  'fedora_distribution_ready=1' \
  'fedora_approval_claimed=1' \
  'daily_driver_install_ready=1' \
  'immutable_fedora_ready=1' \
  'host_mutation_performed=1'
do
  require_absent "$forbidden_claim" "$EVIDENCE"
done

cat <<REPORT
LATTICRA PRODUCTION INSTALLER SBOM EVIDENCE INTAKE VALIDATION
intake_validation_status=ok
sbom_evidence_intake_validator_present=1
sbom_evidence_intake_validation_mode=no-effect-validation
sbom_evidence_candidate_valid=1
sbom_artifact_file_present=1
sbom_artifact_sha256_recorded=1
candidate_sbom_artifact_sha256=$sbom_sha256
candidate_sbom_format=$sbom_format
candidate_sbom_format_declared=1
candidate_sbom_component_inventory_present=1
candidate_sbom_dependency_reviewed=1
candidate_sbom_vulnerability_reviewed=1
candidate_sbom_license_reviewed=1
candidate_sbom_reviewed=1
candidate_installer_sbom_recorded=1
candidate_sbom_dependency_review_sha256=$dependency_review_sha256
candidate_sbom_vulnerability_review_sha256=$vulnerability_review_sha256
candidate_sbom_license_review_sha256=$license_review_sha256
candidate_sbom_review_sha256=$review_sha256
sbom_evidence_accepted_by_intake_validator=0
sbom_evidence_written_by_intake_validator=0
installer_sbom_promotion_allowed_by_intake_validator_alone=0
release_artifact_promotion_gate_passed=0
installer_sbom_recorded=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
host_mutation_performed=0
REPORT
