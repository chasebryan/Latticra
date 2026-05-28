#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'production installer sbom evidence intake validator contract: %s\n' "$1" >&2
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

require_absent() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    fail "unexpected pattern in $file: $pattern"
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  case "$output" in
    *"$pattern"*) ;;
    *) fail "missing required output pattern: $pattern" ;;
  esac
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

doc='docs/PRODUCTION_INSTALLER_SBOM_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md'
status='docs/status/PRODUCTION_INSTALLER_SBOM_EVIDENCE_INTAKE_VALIDATOR_STATUS.md'
script='scripts/production-installer-sbom-evidence-intake.sh'
test_script='scripts/test-production-installer-sbom-evidence-intake-validator-contract.sh'
sbom_status='docs/PRODUCTION_INSTALLER_SBOM_STATUS_CONTRACT.md'
readiness='docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md'
promotion_gate='docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_PROMOTION_GATE_CONTRACT.md'
template_contract='docs/PRODUCTION_INSTALLER_SBOM_EVIDENCE_TEMPLATE_CONTRACT.md'
ledger='docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md'
index='docs/status/README.md'
workflow='.github/workflows/production-installer-sbom-evidence-intake-validator.yml'
installer_page='docs/installer.html'

for file in "$doc" "$status" "$script" "$test_script" "$sbom_status" "$readiness" "$promotion_gate" "$template_contract" "$ledger" "$index" "$workflow" "$installer_page" Makefile README.md
do
  require_file "$file"
done

sh -n "$script"
sh -n "$test_script"

require_contains 'Status: no-effect SBOM evidence intake validator contract' "$doc"
require_contains 'sbom_evidence_intake_validator_present=1' "$doc"
require_contains 'sbom_evidence_intake_validation_mode=no-effect-validation' "$doc"
require_contains 'sbom_evidence_template_present=1' "$doc"
require_contains 'sbom_evidence_template_complete=0' "$doc"
require_contains 'sbom_evidence_candidate_valid=0' "$doc"
require_contains 'sbom_artifact_file_present=0' "$doc"
require_contains 'sbom_artifact_sha256_recorded=0' "$doc"
require_contains 'sbom_evidence_accepted_by_intake_validator=0' "$doc"
require_contains 'sbom_evidence_written_by_intake_validator=0' "$doc"
require_contains 'installer_sbom_promotion_allowed_by_intake_validator_alone=0' "$doc"
require_contains 'release_artifact_promotion_gate_passed=0' "$doc"
require_contains 'installer_sbom_recorded=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'sh scripts/production-installer-sbom-evidence-intake.sh \' "$doc"
require_contains 'sh scripts/test-production-installer-sbom-evidence-intake-validator-contract.sh' "$doc"

require_contains 'LATTICRA PRODUCTION INSTALLER SBOM EVIDENCE INTAKE VALIDATION' "$script"
require_contains 'sbom_evidence_intake_validation_mode=no-effect-validation' "$script"
require_contains 'sbom_evidence_candidate_valid=1' "$script"
require_contains 'candidate_sbom_format=$sbom_format' "$script"
require_contains 'candidate_installer_sbom_recorded=1' "$script"
require_contains 'sbom_evidence_accepted_by_intake_validator=0' "$script"
require_contains 'sbom_evidence_written_by_intake_validator=0' "$script"
require_contains 'installer_sbom_promotion_allowed_by_intake_validator_alone=0' "$script"
require_contains 'release_artifact_promotion_gate_passed=0' "$script"
require_contains 'installer_sbom_recorded=0' "$script"
require_contains 'placeholder value is not acceptable in SBOM evidence' "$script"
require_contains 'unsupported SBOM format markers' "$script"
require_absent 'sudo ' "$script"
require_absent 'dnf ' "$script"
require_absent 'rpm -' "$script"
require_absent 'rpmbuild' "$script"
require_absent 'mock ' "$script"
require_absent 'curl ' "$script"
require_absent 'wget ' "$script"

for current_field in \
  'sbom_evidence_intake_validator_present=1' \
  'sbom_evidence_intake_validation_mode=no-effect-validation' \
  'sbom_evidence_template_present=1' \
  'sbom_evidence_template_complete=0' \
  'sbom_evidence_candidate_valid=0' \
  'sbom_artifact_file_present=0' \
  'sbom_artifact_sha256_recorded=0' \
  'sbom_dependency_review_present=0' \
  'sbom_vulnerability_review_present=0' \
  'sbom_license_review_present=0' \
  'sbom_review_present=0' \
  'sbom_evidence_accepted_by_intake_validator=0' \
  'sbom_evidence_written_by_intake_validator=0' \
  'installer_sbom_promotion_allowed_by_intake_validator_alone=0' \
  'release_artifact_promotion_gate_passed=0' \
  'installer_sbom_recorded=0' \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0' \
  'host_mutation_performed=0'
do
  require_contains "$current_field" "$doc"
  require_contains "$current_field" "$status"
done

for future_field in \
  'sbom_evidence_status=complete' \
  'sbom_artifact_present=1' \
  'sbom_format_declared=1' \
  'sbom_format=spdx-json' \
  'sbom_component_inventory_present=1' \
  'sbom_dependency_reviewed=1' \
  'sbom_vulnerability_reviewed=1' \
  'sbom_license_reviewed=1' \
  'sbom_reviewed=1' \
  'installer_sbom_recorded=1' \
  'release_artifact_promotion_gate_passed=0' \
  'production_installer_ready=0' \
  'fedora_distribution_ready=0' \
  'fedora_approval_claimed=0' \
  'daily_driver_install_ready=0' \
  'immutable_fedora_ready=0' \
  'host_mutation_performed=0'
do
  require_contains "$future_field" "$doc"
  require_contains "$future_field" "$status"
  require_contains "$future_field" "$script"
done

require_contains 'PRODUCTION_INSTALLER_SBOM_EVIDENCE_INTAKE_VALIDATOR_STATUS.md' "$index"
require_contains 'PRODUCTION_INSTALLER_SBOM_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md' "$index"
require_contains 'sbom_evidence_intake_validator_present=1' "$readiness"
require_contains 'sbom_evidence_intake_validation_mode=no-effect-validation' "$readiness"
require_contains 'sbom_evidence_template_present=1' "$readiness"
require_contains 'sbom_evidence_template_complete=0' "$readiness"
require_contains 'sbom_evidence_candidate_valid=0' "$readiness"
require_contains 'sbom_evidence_accepted_by_intake_validator=0' "$readiness"
require_contains 'sbom_evidence_template_present=1' "$template_contract"
require_contains 'sbom_evidence_intake_validator_present=1' "$ledger"
require_contains 'sbom_evidence_intake_validator_present=1' README.md
require_contains 'docs/PRODUCTION_INSTALLER_SBOM_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md' README.md
require_contains 'docs/status/PRODUCTION_INSTALLER_SBOM_EVIDENCE_INTAKE_VALIDATOR_STATUS.md' README.md
require_contains 'sbom_evidence_intake_validator' "$installer_page"

require_contains 'production-installer-sbom-evidence-intake-validator-contract:' Makefile
require_contains 'sh ./scripts/test-production-installer-sbom-evidence-intake-validator-contract.sh' Makefile
require_contains 'name: Production Installer SBOM Evidence Intake Validator' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-production-installer-sbom-evidence-intake-validator-contract.sh' "$workflow"
require_absent 'sh scripts/production-installer-sbom-evidence-intake.sh' "$workflow"

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-sbom-evidence-intake.XXXXXX")"
trap 'rm -rf "$tmp"' EXIT INT HUP TERM

sbom="$tmp/latticra-production-installer.spdx.json"
bad_sbom="$tmp/not-an-sbom.txt"
dependency_review="$tmp/dependency-review.txt"
vulnerability_review="$tmp/vulnerability-review.txt"
license_review="$tmp/license-review.txt"
review="$tmp/sbom-review.txt"
valid_evidence="$tmp/sbom-evidence.txt"
bad_hash_evidence="$tmp/sbom-bad-hash-evidence.txt"
placeholder_evidence="$tmp/sbom-placeholder-evidence.txt"

cat >"$sbom" <<'SPDX_JSON'
{
  "spdxVersion": "SPDX-2.3",
  "SPDXID": "SPDXRef-DOCUMENT",
  "name": "latticra-production-installer",
  "documentNamespace": "https://latticra.local/spdx/latticra-production-installer",
  "creationInfo": {
    "created": "2026-05-27T00:00:00Z",
    "creators": ["Tool: latticra-fixture"]
  },
  "packages": [
    {
      "name": "latticra-production-installer",
      "SPDXID": "SPDXRef-Package-LatticraInstaller",
      "downloadLocation": "NOASSERTION",
      "filesAnalyzed": false,
      "licenseConcluded": "NOASSERTION",
      "licenseDeclared": "NOASSERTION",
      "copyrightText": "NOASSERTION"
    }
  ]
}
SPDX_JSON

printf 'not an sbom\n' >"$bad_sbom"
printf 'dependency review fixture\n' >"$dependency_review"
printf 'vulnerability review fixture\n' >"$vulnerability_review"
printf 'license review fixture\n' >"$license_review"
printf 'sbom review fixture\n' >"$review"

sbom_sha="$(sha256_file "$sbom")"
dependency_review_sha="$(sha256_file "$dependency_review")"
vulnerability_review_sha="$(sha256_file "$vulnerability_review")"
license_review_sha="$(sha256_file "$license_review")"
review_sha="$(sha256_file "$review")"

cat >"$valid_evidence" <<VALID_EVIDENCE
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
sbom_artifact_sha256=$sbom_sha
sbom_dependency_review_sha256=$dependency_review_sha
sbom_vulnerability_review_sha256=$vulnerability_review_sha
sbom_license_review_sha256=$license_review_sha
sbom_review_sha256=$review_sha
release_artifact_promotion_gate_passed=0
production_installer_ready=0
fedora_distribution_ready=0
fedora_approval_claimed=0
daily_driver_install_ready=0
immutable_fedora_ready=0
host_mutation_performed=0
VALID_EVIDENCE

cp "$valid_evidence" "$bad_hash_evidence"
sed "s/$sbom_sha/0000000000000000000000000000000000000000000000000000000000000000/" "$valid_evidence" >"$bad_hash_evidence"
cp "$valid_evidence" "$placeholder_evidence"
printf '%s\n' 'sbom_review_reference=<required-review-id>' >>"$placeholder_evidence"

output="$(sh "$script" \
  --sbom "$sbom" \
  --dependency-review "$dependency_review" \
  --vulnerability-review "$vulnerability_review" \
  --license-review "$license_review" \
  --review "$review" \
  --evidence "$valid_evidence")"

require_output_contains "$output" 'LATTICRA PRODUCTION INSTALLER SBOM EVIDENCE INTAKE VALIDATION'
require_output_contains "$output" 'intake_validation_status=ok'
require_output_contains "$output" 'sbom_evidence_intake_validator_present=1'
require_output_contains "$output" 'sbom_evidence_candidate_valid=1'
require_output_contains "$output" 'candidate_sbom_format=spdx-json'
require_output_contains "$output" "candidate_sbom_artifact_sha256=$sbom_sha"
require_output_contains "$output" "candidate_sbom_dependency_review_sha256=$dependency_review_sha"
require_output_contains "$output" "candidate_sbom_vulnerability_review_sha256=$vulnerability_review_sha"
require_output_contains "$output" "candidate_sbom_license_review_sha256=$license_review_sha"
require_output_contains "$output" "candidate_sbom_review_sha256=$review_sha"
require_output_contains "$output" 'sbom_evidence_accepted_by_intake_validator=0'
require_output_contains "$output" 'sbom_evidence_written_by_intake_validator=0'
require_output_contains "$output" 'installer_sbom_promotion_allowed_by_intake_validator_alone=0'
require_output_contains "$output" 'release_artifact_promotion_gate_passed=0'
require_output_contains "$output" 'installer_sbom_recorded=0'
require_output_contains "$output" 'production_installer_ready=0'
require_output_contains "$output" 'host_mutation_performed=0'

if sh "$script" \
  --sbom "$bad_sbom" \
  --dependency-review "$dependency_review" \
  --vulnerability-review "$vulnerability_review" \
  --license-review "$license_review" \
  --review "$review" \
  --evidence "$valid_evidence" >/dev/null 2>&1; then
  fail 'unsupported SBOM evidence unexpectedly passed validation'
fi

if sh "$script" \
  --sbom "$sbom" \
  --dependency-review "$dependency_review" \
  --vulnerability-review "$vulnerability_review" \
  --license-review "$license_review" \
  --review "$review" \
  --evidence "$bad_hash_evidence" >/dev/null 2>&1; then
  fail 'bad-hash SBOM evidence unexpectedly passed validation'
fi

if sh "$script" \
  --sbom "$sbom" \
  --dependency-review "$dependency_review" \
  --vulnerability-review "$vulnerability_review" \
  --license-review "$license_review" \
  --review "$review" \
  --evidence "$placeholder_evidence" >/dev/null 2>&1; then
  fail 'placeholder SBOM evidence unexpectedly passed validation'
fi

printf 'production_installer_sbom_evidence_intake_validator_contract: ok\n'
