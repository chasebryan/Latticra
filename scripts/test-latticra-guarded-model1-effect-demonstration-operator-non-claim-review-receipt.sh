#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra guarded model1 effect demonstration operator non-claim review receipt: %s\n' "$1" >&2
  exit 1
}

require_file() {
  file="$1"
  [ -f "$file" ] || fail "missing file: $file"
}

require_contains() {
  pattern="$1"
  file="$2"
  grep -Fq -- "$pattern" "$file" || fail "missing pattern in $file: $pattern"
}

require_output_contains() {
  output="$1"
  pattern="$2"
  case "$output" in
    *"$pattern"*) ;;
    *) fail "missing output pattern: $pattern" ;;
  esac
}

sha256_file() {
  file="$1"
  if command -v sha256sum >/dev/null 2>&1; then
    sha256sum "$file" | awk '{ print "sha256:" $1 }'
  elif command -v shasum >/dev/null 2>&1; then
    shasum -a 256 "$file" | awk '{ print "sha256:" $1 }'
  else
    fail 'sha256 tool unavailable'
  fi
}

sha256_text() {
  text="$1"
  if command -v sha256sum >/dev/null 2>&1; then
    printf '%s' "$text" | sha256sum | awk '{ print "sha256:" $1 }'
  elif command -v shasum >/dev/null 2>&1; then
    printf '%s' "$text" | shasum -a 256 | awk '{ print "sha256:" $1 }'
  else
    fail 'sha256 tool unavailable'
  fi
}

doc='docs/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_OPERATOR_NON_CLAIM_REVIEW_RECEIPT.md'
status='docs/status/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_OPERATOR_NON_CLAIM_REVIEW_RECEIPT_STATUS.md'
checklist_doc='docs/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_OPERATOR_NON_CLAIM_REVIEW_CHECKLIST.md'
checklist_status='docs/status/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_OPERATOR_NON_CLAIM_REVIEW_CHECKLIST_STATUS.md'
transition_doc='docs/LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE.md'
transition_status='docs/status/LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE_STATUS.md'
status_index='docs/status/README.md'
docs_hub='docs/README.md'
root_readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
current_direction='docs/project_notes/CURRENT_DIRECTION.md'
upcoming_work='docs/project_notes/UPCOMING_WORK.md'
makefile='Makefile'
quality_guard='scripts/test-quality-safety-guards.sh'
workflow='.github/workflows/latticra-guarded-model1-effect-demo-non-claim-receipt.yml'
receipt_script='scripts/latticra-guarded-model1-effect-demo-operator-non-claim-review-receipt.sh'
receipt_guard='scripts/test-latticra-guarded-model1-effect-demonstration-operator-non-claim-review-receipt.sh'
checklist_script='scripts/latticra-guarded-model1-effect-demo-operator-non-claim-review-checklist.sh'
valid_fixture='fixtures/latticra-model1-demo-evidence/valid-denied.packet'
invalid_fixture='fixtures/latticra-model1-demo-evidence/effect-performed.packet'

for file in "$doc" "$status" "$checklist_doc" "$checklist_status" "$transition_doc" "$transition_status" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$makefile" "$quality_guard" "$workflow" "$receipt_script" "$receipt_guard" "$checklist_script" "$valid_fixture" "$invalid_fixture"
do
  require_file "$file"
done

sh -n "$receipt_script"
sh -n "$receipt_guard"

for file in "$doc" "$status"
do
  require_contains 'latticra_guarded_model1_effect_demo_operator_non_claim_review_receipt_present=1' "$file"
  require_contains 'guarded_demo_operator_non_claim_review_receipt_guard_present=1' "$file"
  require_contains 'guarded_demo_operator_non_claim_review_receipt_version=1' "$file"
  require_contains 'edge_checkpoint=v0.3.0edge' "$file"
  require_contains 'operator_non_claim_review_checklist_reference=docs/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_OPERATOR_NON_CLAIM_REVIEW_CHECKLIST.md' "$file"
  require_contains 'operator_non_claim_review_checklist_status_reference=docs/status/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_OPERATOR_NON_CLAIM_REVIEW_CHECKLIST_STATUS.md' "$file"
  require_contains 'operator_non_claim_review_checklist_script=scripts/latticra-guarded-model1-effect-demo-operator-non-claim-review-checklist.sh' "$file"
  require_contains 'operator_non_claim_review_receipt_script=scripts/latticra-guarded-model1-effect-demo-operator-non-claim-review-receipt.sh' "$file"
  require_contains 'operator_non_claim_review_receipt_guard_script=scripts/test-latticra-guarded-model1-effect-demonstration-operator-non-claim-review-receipt.sh' "$file"
  require_contains 'operator_non_claim_review_checklist_output_valid=1' "$file"
  require_contains 'operator_non_claim_review_checklist_output_sha256_recorded=1' "$file"
  require_contains 'operator_non_claim_review_checklist_entry_present=1' "$file"
  require_contains 'operator_non_claim_review_checklist_state=required-not-completed' "$file"
  require_contains 'operator_non_claim_review_checklist_decision=deny-evidence-until-non-claim-review-complete' "$file"
  require_contains 'operator_non_claim_review_receipt_entry_present=1' "$file"
  require_contains 'operator_non_claim_review_receipt_state=recorded-denied-no-effect' "$file"
  require_contains 'operator_non_claim_review_receipt_decision=record-operator-non-claim-review-required-and-incomplete' "$file"
  require_contains 'operator_non_claim_review_receipt_reason=operator-non-claim-review-checklist-incomplete' "$file"
  require_contains 'operator_non_claim_review_receipt_file_written=0' "$file"
  require_contains 'operator_non_claim_review_required=1' "$file"
  require_contains 'operator_non_claim_review_completed=0' "$file"
  require_contains 'operator_non_claim_review_acceptance_allowed=0' "$file"
  require_contains 'guarded_model1_effect_demonstration_satisfied=0' "$file"
  require_contains 'guarded_model1_effect_demonstration_evidence_accepted=0' "$file"
  require_contains 'model1_bridge_execution_performed=0' "$file"
  require_contains 'model1_process_launch_performed=0' "$file"
  require_contains 'effect_dispatch_performed=0' "$file"
  require_contains 'effect_execution_performed=0' "$file"
  require_contains 'command_execution_performed=0' "$file"
  require_contains 'file_mutation_performed=0' "$file"
  require_contains 'network_performed=0' "$file"
  require_contains 'host_mutation_performed=0' "$file"
  require_contains 'runtime_authority_granted=0' "$file"
  require_contains 'production_readiness_claim=0' "$file"
  require_contains 'distribution_readiness_claim=0' "$file"
  require_contains 'Guarded Model-1 effect demonstration evidence acceptance preflight denial gate.' "$file"
  require_contains 'latticra_guarded_model1_effect_demonstration_operator_non_claim_review_receipt: ok' "$file"
done

for predecessor in "$checklist_doc" "$checklist_status" "$transition_doc" "$transition_status"
do
  require_contains 'Guarded Model-1 effect demonstration operator non-claim review receipt.' "$predecessor"
  require_contains 'Guarded Model-1 effect demonstration evidence acceptance preflight denial gate.' "$predecessor"
done

require_contains 'Guarded Model-1 Effect Demonstration Operator Non-Claim Review Receipt' "$docs_hub"
require_contains 'LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_OPERATOR_NON_CLAIM_REVIEW_RECEIPT_STATUS.md' "$status_index"
require_contains 'guarded Model-1 effect demonstration operator non-claim review receipt](docs/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_OPERATOR_NON_CLAIM_REVIEW_RECEIPT.md)' "$root_readme"
require_contains 'Latest Latticra guarded Model-1 effect demonstration operator non-claim review receipt note: 2026-06-12 CDT' "$root_status"
require_contains 'Latest Latticra guarded Model-1 effect demonstration operator non-claim review receipt note: 2026-06-12 CDT' "$current_status"
require_contains 'Latest Latticra guarded Model-1 effect demonstration operator non-claim review receipt note: 2026-06-12 CDT' "$current_direction"
require_contains 'Latest Latticra guarded Model-1 effect demonstration operator non-claim review receipt note: 2026-06-12 CDT' "$upcoming_work"
require_contains 'Guarded Model-1 effect demonstration operator non-claim review receipt.' "$current_status"
require_contains 'Guarded Model-1 effect demonstration operator non-claim review receipt.' "$current_direction"
require_contains 'Guarded Model-1 effect demonstration operator non-claim review receipt.' "$upcoming_work"
require_contains 'Guarded Model-1 effect demonstration evidence acceptance preflight denial gate.' "$current_status"
require_contains 'Guarded Model-1 effect demonstration evidence acceptance preflight denial gate.' "$current_direction"
require_contains 'Guarded Model-1 effect demonstration evidence acceptance preflight denial gate.' "$upcoming_work"
require_contains 'latticra-guarded-model1-effect-demonstration-operator-non-claim-review-receipt:' "$makefile"
require_contains 'sh ./scripts/test-latticra-guarded-model1-effect-demonstration-operator-non-claim-review-receipt.sh' "$makefile"
require_contains 'latticra-guarded-model1-effect-demonstration-operator-non-claim-review-receipt:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-guarded-model1-effect-demonstration-operator-non-claim-review-receipt.sh' "$quality_guard"
require_contains 'Run Latticra guarded Model-1 effect demonstration operator non-claim review receipt guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-guarded-model1-effect-demonstration-operator-non-claim-review-receipt.sh' "$workflow"

expected_packet_sha="$(sha256_file "$valid_fixture")"
checklist_output="$(sh "$checklist_script" --packet "$valid_fixture")"
expected_checklist_sha="$(sha256_text "$checklist_output")"
output="$(sh "$receipt_script" --packet "$valid_fixture")"
require_output_contains "$output" 'LATTICRA GUARDED MODEL1 EFFECT DEMONSTRATION OPERATOR NON CLAIM REVIEW RECEIPT'
require_output_contains "$output" 'operator_non_claim_review_receipt_status=ok'
require_output_contains "$output" "candidate_packet_path=fixtures/latticra-model1-demo-evidence/valid-denied.packet"
case "$output" in *candidate_packet_path=/ * ) fail "candidate_packet_path must be portable relative" ;; esac
require_output_contains "$output" 'candidate_packet_path=fixtures/latticra-model1-demo-evidence/valid-denied.packet'
case "$output" in *'candidate_packet_path=/'* ) fail 'candidate_packet_path must be portable relative' ;; esac
require_output_contains "$output" 'latticra_guarded_model1_effect_demo_operator_non_claim_review_receipt_present=1'
require_output_contains "$output" 'candidate_packet_sha256_recorded=1'
require_output_contains "$output" "candidate_packet_sha256=$expected_packet_sha"
require_output_contains "$output" 'operator_non_claim_review_checklist_output_valid=1'
require_output_contains "$output" 'operator_non_claim_review_checklist_output_sha256_recorded=1'
require_output_contains "$output" "operator_non_claim_review_checklist_output_sha256=$expected_checklist_sha"
require_output_contains "$output" 'operator_non_claim_review_checklist_entry_present=1'
require_output_contains "$output" 'operator_non_claim_review_checklist_state=required-not-completed'
require_output_contains "$output" 'operator_non_claim_review_receipt_entry_present=1'
require_output_contains "$output" 'operator_non_claim_review_receipt_state=recorded-denied-no-effect'
require_output_contains "$output" 'operator_non_claim_review_receipt_decision=record-operator-non-claim-review-required-and-incomplete'
require_output_contains "$output" 'operator_non_claim_review_receipt_file_written=0'
require_output_contains "$output" 'operator_non_claim_review_completed=0'
require_output_contains "$output" 'operator_non_claim_review_acceptance_allowed=0'
require_output_contains "$output" 'guarded_model1_effect_demonstration_evidence_accepted=0'
require_output_contains "$output" 'model1_bridge_execution_performed=0'
require_output_contains "$output" 'effect_execution_performed=0'
require_output_contains "$output" 'file_mutation_performed=0'
require_output_contains "$output" 'runtime_authority_granted=0'
require_output_contains "$output" 'denial_reason=operator-non-claim-review-checklist-incomplete'

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-model1-demo-non-claim-receipt.XXXXXX")"
trap 'rm -rf "$tmp"' EXIT INT HUP TERM

if sh "$receipt_script" --packet "$invalid_fixture" >"$tmp/invalid-receipt.out" 2>"$tmp/invalid-receipt.err"; then
  fail 'expected invalid fixture rejection'
fi
invalid_output="$(cat "$tmp/invalid-receipt.out")"
require_output_contains "$invalid_output" 'operator_non_claim_review_receipt_status=rejected'
require_output_contains "$invalid_output" 'operator_non_claim_review_checklist_output_valid=0'
require_output_contains "$invalid_output" 'operator_non_claim_review_receipt_entry_present=0'
require_output_contains "$invalid_output" 'operator_non_claim_review_receipt_state=not-recorded'
require_output_contains "$invalid_output" 'operator_non_claim_review_acceptance_allowed=0'
require_output_contains "$invalid_output" 'guarded_model1_effect_demonstration_evidence_accepted=0'
require_output_contains "$invalid_output" 'runtime_authority_granted=0'
require_output_contains "$invalid_output" 'denial_reason=operator-non-claim-review-checklist-rejected'

printf 'latticra_guarded_model1_effect_demonstration_operator_non_claim_review_receipt: ok\n'
