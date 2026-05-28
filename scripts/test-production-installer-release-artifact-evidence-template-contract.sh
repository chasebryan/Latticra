#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'production installer release artifact evidence template contract: %s\n' "$1" >&2
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

require_not_matching() {
  pattern="$1"
  file="$2"
  if grep -Eq -- "$pattern" "$file"; then
    fail "unexpected executable pattern in $file: $pattern"
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

doc='docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_EVIDENCE_TEMPLATE_CONTRACT.md'
status='docs/status/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_EVIDENCE_TEMPLATE_STATUS.md'
script='scripts/production-installer-release-artifact-evidence-template.sh'
test_script='scripts/test-production-installer-release-artifact-evidence-template-contract.sh'
intake_contract='docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_EVIDENCE_INTAKE_VALIDATOR_CONTRACT.md'
intake_status='docs/status/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_EVIDENCE_INTAKE_VALIDATOR_STATUS.md'
intake_test='scripts/test-production-installer-release-artifact-evidence-intake-validator-contract.sh'
readiness='docs/PRODUCTION_INSTALLER_READINESS_CONTRACT.md'
ledger='docs/status/PRODUCTION_QUALITY_BLOCKER_LEDGER.md'
index='docs/status/README.md'
installer_page='docs/installer.html'
workflow='.github/workflows/production-installer-release-artifact-evidence-template.yml'

for file in "$doc" "$status" "$script" "$test_script" "$intake_contract" \
  "$intake_status" "$intake_test" "$readiness" "$ledger" "$index" \
  "$installer_page" "$workflow" Makefile README.md
do
  require_file "$file"
done

sh -n "$script"
sh -n "$test_script"

require_contains 'Status: no-effect release-artifact evidence template contract' "$doc"
require_contains 'release_artifact_evidence_template_present=1' "$doc"
require_contains 'release_artifact_evidence_template_mode=no-effect-template' "$doc"
require_contains 'release_artifact_evidence_template_decision=blocked-template-only-no-evidence-write' "$doc"
require_contains 'release_artifact_evidence_template_complete=0' "$doc"
require_contains 'release_artifact_evidence_intake_validator_present=1' "$doc"
require_contains 'release_artifact_evidence_written_by_template=0' "$doc"
require_contains 'release_artifact_evidence_accepted_by_template=0' "$doc"
require_contains 'release_artifact_promotion_gate_passed=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'artifact_sha256=<required-artifact-sha256>' "$doc"
require_contains 'sh scripts/production-installer-release-artifact-evidence-template.sh' "$doc"

require_contains 'Status: template/status alignment' "$status"
require_contains 'release_artifact_evidence_template_present=1' "$status"
require_contains 'release_artifact_evidence_template_complete=0' "$status"
require_contains 'release_artifact_evidence_written_by_template=0' "$status"
require_contains 'release_artifact_evidence_accepted_by_template=0' "$status"
require_contains 'network_allowed=0' "$status"
require_contains 'host_mutation_performed=0' "$status"

require_contains 'release_artifact_evidence_template_present=1' "$readiness"
require_contains 'release_artifact_evidence_template_mode=no-effect-template' "$readiness"
require_contains 'release_artifact_evidence_template_complete=0' "$readiness"
require_contains 'release_artifact_evidence_written_by_template=0' "$readiness"
require_contains 'release_artifact_evidence_accepted_by_template=0' "$readiness"

require_contains '## Installer Release Artifact Evidence Template' "$ledger"
require_contains 'release_artifact_evidence_template_present=1' "$ledger"
require_contains 'release_artifact_evidence_template_complete=0' "$ledger"
require_contains 'release_artifact_evidence_written_by_template=0' "$ledger"
require_contains 'This closes the release-artifact evidence-template presence gap only.' "$ledger"
require_contains 'release_artifact_evidence_template_present=1' README.md
require_contains 'docs/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_EVIDENCE_TEMPLATE_CONTRACT.md' README.md
require_contains 'docs/status/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_EVIDENCE_TEMPLATE_STATUS.md' README.md
require_contains 'release artifact evidence template' "$installer_page"
require_contains 'PRODUCTION_INSTALLER_RELEASE_ARTIFACT_EVIDENCE_TEMPLATE_CONTRACT.md' "$index"
require_contains 'PRODUCTION_INSTALLER_RELEASE_ARTIFACT_EVIDENCE_TEMPLATE_STATUS.md' "$index"

require_contains 'release_artifact_evidence_template_present=1' "$intake_contract"
require_contains 'release_artifact_evidence_template_present=1' "$intake_status"
require_contains 'release_artifact_evidence_template_present=1' "$intake_test"
require_contains 'production-installer-release-artifact-evidence-template-contract:' Makefile
require_contains 'sh ./scripts/test-production-installer-release-artifact-evidence-template-contract.sh' Makefile
require_contains 'name: Production Installer Release Artifact Evidence Template' "$workflow"
require_contains 'permissions:' "$workflow"
require_contains 'contents: read' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'sh scripts/test-production-installer-release-artifact-evidence-template-contract.sh' "$workflow"

require_absent 'sudo ' "$script"
require_absent 'dnf ' "$script"
require_absent 'brew ' "$script"
require_absent 'curl ' "$script"
require_absent 'wget ' "$script"
require_not_matching '^[[:space:]]*sudo[[:space:]]' "$script"
require_not_matching '^[[:space:]]*dnf[[:space:]]' "$script"
require_not_matching '^[[:space:]]*brew[[:space:]]' "$script"
require_not_matching '^[[:space:]]*rpm[[:space:]]' "$script"
require_not_matching '^[[:space:]]*rpmbuild[[:space:]]' "$script"
require_not_matching '^[[:space:]]*gpg[[:space:]]' "$script"
require_not_matching '^[[:space:]]*curl[[:space:]]' "$script"
require_not_matching '^[[:space:]]*wget[[:space:]]' "$script"

output="$(sh "$script")"
require_output_contains "$output" 'LATTICRA PRODUCTION INSTALLER RELEASE ARTIFACT EVIDENCE TEMPLATE'
require_output_contains "$output" 'template_status=ok'
require_output_contains "$output" 'release_artifact_evidence_template_present=1'
require_output_contains "$output" 'release_artifact_evidence_template_mode=no-effect-template'
require_output_contains "$output" 'release_artifact_evidence_template_decision=blocked-template-only-no-evidence-write'
require_output_contains "$output" 'release_artifact_evidence_template_complete=0'
require_output_contains "$output" 'release_artifact_evidence_intake_validator_present=1'
require_output_contains "$output" 'release_artifact_evidence_path=artifacts/release/latticra-production-installer-release-artifact-evidence.txt'
require_output_contains "$output" 'release_artifact_candidate_path=artifacts/release/latticra-production-installer.rpm'
require_output_contains "$output" 'release_artifact_signature_path=artifacts/release/latticra-production-installer.rpm.sig'
require_output_contains "$output" 'release_public_key_path=artifacts/release/latticra-release-public-key.asc'
require_output_contains "$output" 'artifact_sha256=<required-artifact-sha256>'
require_output_contains "$output" 'artifact_signature_sha256=<required-signature-sha256>'
require_output_contains "$output" 'release_public_key_sha256=<required-public-key-sha256>'
require_output_contains "$output" 'signature_verification_transcript_sha256=<required-verification-transcript-sha256>'
require_output_contains "$output" 'release_artifact_evidence_written_by_template=0'
require_output_contains "$output" 'release_artifact_evidence_accepted_by_template=0'
require_output_contains "$output" 'release_artifact_evidence_accepted_by_intake_validator=0'
require_output_contains "$output" 'release_artifact_promotion_gate_passed=0'
require_output_contains "$output" 'production_installer_ready=0'
require_output_contains "$output" 'package_manager_invoked=0'
require_output_contains "$output" 'network_allowed=0'
require_output_contains "$output" 'host_mutation_performed=0'

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-release-artifact-template.XXXXXX")"
trap 'rm -rf "$tmp"' EXIT INT HUP TERM

custom_artifact="$tmp/latticra.rpm"
custom_checksum="$tmp/latticra.rpm.sha256"
custom_signature="$tmp/latticra.rpm.sig"
custom_public_key="$tmp/latticra.asc"
custom_verification="$tmp/verification.txt"
custom_reproducibility="$tmp/reproducibility.txt"
custom_review="$tmp/review.txt"
custom_evidence="$tmp/evidence.txt"

custom_output="$(sh "$script" \
  --artifact "$custom_artifact" \
  --sha256 "$custom_checksum" \
  --signature "$custom_signature" \
  --public-key "$custom_public_key" \
  --verification "$custom_verification" \
  --reproducibility "$custom_reproducibility" \
  --review "$custom_review" \
  --evidence "$custom_evidence")"
require_output_contains "$custom_output" "release_artifact_candidate_path=$custom_artifact"
require_output_contains "$custom_output" "release_artifact_checksum_path=$custom_checksum"
require_output_contains "$custom_output" "release_artifact_signature_path=$custom_signature"
require_output_contains "$custom_output" "release_public_key_path=$custom_public_key"
require_output_contains "$custom_output" "release_artifact_evidence_path=$custom_evidence"

if sh "$script" --unknown >/dev/null 2>&1; then
  fail 'unknown argument unexpectedly succeeded'
fi

printf 'production_installer_release_artifact_evidence_template_contract: ok\n'
