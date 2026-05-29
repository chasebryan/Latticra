#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'macos codesigning notarization plan: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'macos codesigning notarization plan: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'macos codesigning notarization plan: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_output_contains() {
  output="$1"
  pattern="$2"
  if ! printf '%s\n' "$output" | grep -Fq -- "$pattern"; then
    printf 'macos codesigning notarization plan: missing required output pattern: %s\n' "$pattern" >&2
    exit 1
  fi
}

doc='docs/MACOS_CODESIGNING_NOTARIZATION_PLAN.md'
status='docs/status/MACOS_CODESIGNING_NOTARIZATION_PLAN_STATUS.md'
script='scripts/macos-codesigning-notarization-plan.sh'
workflow='.github/workflows/macos-codesigning-notarization-plan.yml'
index='docs/status/README.md'
transfer_plan='docs/MACOS_INTEGRATION_TRANSFERABILITY_PLAN.md'
transfer_status='docs/status/MACOS_INTEGRATION_TRANSFERABILITY_STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
root_status='STATUS.md'
readme='README.md'
makefile='Makefile'
signing_status='docs/status/PRODUCTION_INSTALLER_RELEASE_SIGNING_IDENTITY_REFERENCE_STATUS.md'
preflight_status='docs/status/PRODUCTION_INSTALLER_RELEASE_ARTIFACT_CANDIDATE_PREFLIGHT_STATUS.md'

require_file "$doc"
require_file "$status"
require_file "$script"
require_file "$workflow"
require_file "$index"
require_file "$transfer_plan"
require_file "$transfer_status"
require_file "$current_status"
require_file "$root_status"
require_file "$readme"
require_file "$makefile"
require_file "$signing_status"
require_file "$preflight_status"

require_contains 'Status: no-effect macOS codesigning and notarization plan' "$doc"
require_contains 'sh scripts/macos-codesigning-notarization-plan.sh' "$doc"
require_contains 'macos_codesigning_notarization_plan_present=1' "$doc"
require_contains 'macos_codesigning_notarization_plan_state=defined-no-effect' "$doc"
require_contains 'macos_codesigning_notarization_plan_decision=plan-defined-evidence-not-present' "$doc"
require_contains 'macos_codesigned_app_evidence_present=0' "$doc"
require_contains 'macos_notarized_app_evidence_present=0' "$doc"
require_contains 'release_signing_identity_reference_contract_present_required=1' "$doc"
require_contains 'reviewed_apple_account_boundary_required=1' "$doc"
require_contains 'codesign_invocation_performed=0' "$doc"
require_contains 'notary_submission_performed=0' "$doc"
require_contains 'production_installer_ready=0' "$doc"
require_contains 'macos_codesigning_notarization_plan: ok' "$doc"

require_contains 'Status: no-effect macOS codesigning and notarization plan status' "$status"
require_contains 'macos_codesigning_notarization_plan_present=1' "$status"
require_contains 'macos_codesigning_notarization_plan_guard_present=1' "$status"
require_contains 'macos_verification_transcript_contract_present=1' "$status"
require_contains 'release_signing_identity_reference_contract_present_required=1' "$status"
require_contains 'codesign_invocation_performed=0' "$status"
require_contains 'notary_submission_performed=0' "$status"
require_contains 'host_mutation_performed=0' "$status"
require_contains 'runtime_authority_granted=0' "$status"
require_contains 'production_installer_ready=0' "$status"
require_contains 'sh scripts/test-macos-codesigning-notarization-plan.sh' "$status"
require_contains 'macos_codesigning_notarization_plan: ok' "$status"

require_contains 'MACOS_CODESIGNING_NOTARIZATION_PLAN_STATUS.md' "$index"
require_contains 'macOS codesigning and notarization plan status' "$index"
require_contains 'stage_5_codesigning_notarization_plan=present' "$transfer_plan"
require_contains 'docs/MACOS_CODESIGNING_NOTARIZATION_PLAN.md' "$transfer_plan"
require_contains 'scripts/macos-codesigning-notarization-plan.sh' "$transfer_plan"
require_contains 'macos_codesigning_notarization_plan_present=1' "$transfer_status"
require_contains 'Latest macOS codesigning and notarization plan note: 2026-05-29 CDT' "$current_status"
require_contains 'Latest macOS codesigning and notarization plan note: 2026-05-29 CDT' "$root_status"
require_contains 'macos_codesigning_notarization_plan_present=1' "$readme"
require_contains 'docs/MACOS_CODESIGNING_NOTARIZATION_PLAN.md' "$readme"
require_contains 'macos-codesigning-notarization-plan:' "$makefile"
require_contains 'sh ./scripts/test-macos-codesigning-notarization-plan.sh' "$makefile"

require_contains 'macos_codesigning_notarization_plan_status=ok' "$script"
require_contains 'macos_codesigning_notarization_plan_present=1' "$script"
require_contains 'macos_verification_transcript_contract_present=1' "$script"
require_contains 'release_signing_identity_reference_contract_present_required=1' "$script"
require_contains 'notary_submission_performed=0' "$script"
require_contains 'next_lane=macos-controlled-os-integration-contracts-plan' "$script"
require_not_contains 'curl ' "$script"
require_not_contains 'wget ' "$script"
require_not_contains 'sudo ' "$script"

require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'sh scripts/test-macos-codesigning-notarization-plan.sh' "$workflow"

output=$(sh "$script")

require_output_contains "$output" 'MACOS CODESIGNING AND NOTARIZATION PLAN'
require_output_contains "$output" 'macos_codesigning_notarization_plan_status=ok'
require_output_contains "$output" 'macos_codesigning_notarization_plan_present=1'
require_output_contains "$output" 'macos_codesigned_app_evidence_present=0'
require_output_contains "$output" 'macos_notarized_app_evidence_present=0'
require_output_contains "$output" 'release_signing_identity_reference_contract_present_required=1'
require_output_contains "$output" 'operator_notarization_intent_review_required=1'
require_output_contains "$output" 'codesign_invocation_performed=0'
require_output_contains "$output" 'notary_submission_performed=0'
require_output_contains "$output" 'network_performed=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'production_installer_ready=0'
require_output_contains "$output" 'next_lane=macos-controlled-os-integration-contracts-plan'

printf 'macos_codesigning_notarization_plan: ok\n'
