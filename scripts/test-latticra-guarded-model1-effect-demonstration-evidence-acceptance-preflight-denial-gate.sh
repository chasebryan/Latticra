#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra guarded model1 effect demonstration evidence acceptance preflight denial gate: %s\n' "$1" >&2
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

doc='docs/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_EVIDENCE_ACCEPTANCE_PREFLIGHT_DENIAL_GATE.md'
status='docs/status/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_EVIDENCE_ACCEPTANCE_PREFLIGHT_DENIAL_GATE_STATUS.md'
receipt_doc='docs/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_OPERATOR_NON_CLAIM_REVIEW_RECEIPT.md'
receipt_status='docs/status/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_OPERATOR_NON_CLAIM_REVIEW_RECEIPT_STATUS.md'
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
workflow='.github/workflows/latticra-guarded-model1-effect-demo-acceptance-preflight-denial.yml'
gate_script='scripts/latticra-guarded-model1-effect-demo-evidence-acceptance-preflight-denial-gate.sh'
gate_guard='scripts/test-latticra-guarded-model1-effect-demonstration-evidence-acceptance-preflight-denial-gate.sh'
receipt_script='scripts/latticra-guarded-model1-effect-demo-operator-non-claim-review-receipt.sh'
valid_fixture='fixtures/latticra-model1-demo-evidence/valid-denied.packet'
invalid_fixture='fixtures/latticra-model1-demo-evidence/effect-performed.packet'

for file in "$doc" "$status" "$receipt_doc" "$receipt_status" "$transition_doc" "$transition_status" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$makefile" "$quality_guard" "$workflow" "$gate_script" "$gate_guard" "$receipt_script" "$valid_fixture" "$invalid_fixture"
do
  require_file "$file"
done

sh -n "$gate_script"
sh -n "$gate_guard"

for file in "$doc" "$status"
do
  require_contains 'latticra_guarded_model1_effect_demo_evidence_acceptance_preflight_denial_gate_present=1' "$file"
  require_contains 'guarded_demo_evidence_acceptance_preflight_denial_gate_guard_present=1' "$file"
  require_contains 'guarded_demo_evidence_acceptance_preflight_denial_gate_version=1' "$file"
  require_contains 'edge_checkpoint=v0.3.0edge' "$file"
  require_contains 'operator_non_claim_review_receipt_reference=docs/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_OPERATOR_NON_CLAIM_REVIEW_RECEIPT.md' "$file"
  require_contains 'operator_non_claim_review_receipt_status_reference=docs/status/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_OPERATOR_NON_CLAIM_REVIEW_RECEIPT_STATUS.md' "$file"
  require_contains 'operator_non_claim_review_receipt_script=scripts/latticra-guarded-model1-effect-demo-operator-non-claim-review-receipt.sh' "$file"
  require_contains 'evidence_acceptance_preflight_denial_gate_script=scripts/latticra-guarded-model1-effect-demo-evidence-acceptance-preflight-denial-gate.sh' "$file"
  require_contains 'evidence_acceptance_preflight_denial_gate_guard_script=scripts/test-latticra-guarded-model1-effect-demonstration-evidence-acceptance-preflight-denial-gate.sh' "$file"
  require_contains 'operator_non_claim_review_receipt_output_valid=1' "$file"
  require_contains 'operator_non_claim_review_receipt_output_sha256_recorded=1' "$file"
  require_contains 'operator_non_claim_review_receipt_entry_present=1' "$file"
  require_contains 'operator_non_claim_review_receipt_state=recorded-denied-no-effect' "$file"
  require_contains 'operator_non_claim_review_receipt_decision=record-operator-non-claim-review-required-and-incomplete' "$file"
  require_contains 'operator_non_claim_review_completed=0' "$file"
  require_contains 'operator_non_claim_review_acceptance_allowed=0' "$file"
  require_contains 'evidence_acceptance_preflight_denial_entry_present=1' "$file"
  require_contains 'evidence_acceptance_preflight_denial_state=denied-before-acceptance' "$file"
  require_contains 'evidence_acceptance_preflight_denial_decision=deny-evidence-acceptance-until-operator-non-claim-review-complete' "$file"
  require_contains 'evidence_acceptance_preflight_denial_reason=operator-non-claim-review-not-completed' "$file"
  require_contains 'evidence_acceptance_allowed=0' "$file"
  require_contains 'evidence_acceptance_performed=0' "$file"
  require_contains 'evidence_acceptance_file_written=0' "$file"
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
  require_contains 'Guarded Model-1 effect demonstration evidence acceptance denial receipt.' "$file"
  require_contains 'latticra_guarded_model1_effect_demonstration_evidence_acceptance_preflight_denial_gate: ok' "$file"
done

for predecessor in "$receipt_doc" "$receipt_status" "$transition_doc" "$transition_status"
do
  require_contains 'Guarded Model-1 effect demonstration evidence acceptance preflight denial gate.' "$predecessor"
  require_contains 'Guarded Model-1 effect demonstration evidence acceptance denial receipt.' "$predecessor"
done

require_contains 'Guarded Model-1 Effect Demonstration Evidence Acceptance Preflight Denial Gate' "$docs_hub"
require_contains 'LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_EVIDENCE_ACCEPTANCE_PREFLIGHT_DENIAL_GATE_STATUS.md' "$status_index"
require_contains 'guarded Model-1 effect demonstration evidence acceptance preflight denial gate](docs/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_EVIDENCE_ACCEPTANCE_PREFLIGHT_DENIAL_GATE.md)' "$root_readme"
require_contains 'Latest Latticra guarded Model-1 effect demonstration evidence acceptance preflight denial gate note: 2026-06-12 CDT' "$root_status"
require_contains 'Latest Latticra guarded Model-1 effect demonstration evidence acceptance preflight denial gate note: 2026-06-12 CDT' "$current_status"
require_contains 'Latest Latticra guarded Model-1 effect demonstration evidence acceptance preflight denial gate note: 2026-06-12 CDT' "$current_direction"
require_contains 'Latest Latticra guarded Model-1 effect demonstration evidence acceptance preflight denial gate note: 2026-06-12 CDT' "$upcoming_work"
require_contains 'Guarded Model-1 effect demonstration evidence acceptance preflight denial gate.' "$current_status"
require_contains 'Guarded Model-1 effect demonstration evidence acceptance preflight denial gate.' "$current_direction"
require_contains 'Guarded Model-1 effect demonstration evidence acceptance preflight denial gate.' "$upcoming_work"
require_contains 'Guarded Model-1 effect demonstration evidence acceptance denial receipt.' "$current_status"
require_contains 'Guarded Model-1 effect demonstration evidence acceptance denial receipt.' "$current_direction"
require_contains 'Guarded Model-1 effect demonstration evidence acceptance denial receipt.' "$upcoming_work"
require_contains 'latticra-guarded-model1-effect-demonstration-evidence-acceptance-preflight-denial-gate:' "$makefile"
require_contains 'sh ./scripts/test-latticra-guarded-model1-effect-demonstration-evidence-acceptance-preflight-denial-gate.sh' "$makefile"
require_contains 'latticra-guarded-model1-effect-demonstration-evidence-acceptance-preflight-denial-gate:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-guarded-model1-effect-demonstration-evidence-acceptance-preflight-denial-gate.sh' "$quality_guard"
require_contains 'Run Latticra guarded Model-1 effect demonstration evidence acceptance preflight denial gate guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-guarded-model1-effect-demonstration-evidence-acceptance-preflight-denial-gate.sh' "$workflow"

expected_packet_sha="$(sha256_file "$valid_fixture")"
receipt_output="$(sh "$receipt_script" --packet "$valid_fixture")"
expected_receipt_sha="$(sha256_text "$receipt_output")"
output="$(sh "$gate_script" --packet "$valid_fixture")"
require_output_contains "$output" 'LATTICRA GUARDED MODEL1 EFFECT DEMONSTRATION EVIDENCE ACCEPTANCE PREFLIGHT DENIAL GATE'
require_output_contains "$output" 'evidence_acceptance_preflight_denial_gate_status=ok'
require_output_contains "$output" 'candidate_packet_path=fixtures/latticra-model1-demo-evidence/valid-denied.packet'
case "$output" in *'candidate_packet_path=/'* ) fail 'candidate_packet_path must be portable relative' ;; esac
require_output_contains "$output" 'latticra_guarded_model1_effect_demo_evidence_acceptance_preflight_denial_gate_present=1'
require_output_contains "$output" 'candidate_packet_sha256_recorded=1'
require_output_contains "$output" "candidate_packet_sha256=$expected_packet_sha"
require_output_contains "$output" 'operator_non_claim_review_receipt_output_valid=1'
require_output_contains "$output" 'operator_non_claim_review_receipt_output_sha256_recorded=1'
require_output_contains "$output" "operator_non_claim_review_receipt_output_sha256=$expected_receipt_sha"
require_output_contains "$output" 'operator_non_claim_review_receipt_entry_present=1'
require_output_contains "$output" 'operator_non_claim_review_receipt_state=recorded-denied-no-effect'
require_output_contains "$output" 'operator_non_claim_review_receipt_decision=record-operator-non-claim-review-required-and-incomplete'
require_output_contains "$output" 'operator_non_claim_review_completed=0'
require_output_contains "$output" 'operator_non_claim_review_acceptance_allowed=0'
require_output_contains "$output" 'evidence_acceptance_preflight_denial_entry_present=1'
require_output_contains "$output" 'evidence_acceptance_preflight_denial_state=denied-before-acceptance'
require_output_contains "$output" 'evidence_acceptance_preflight_denial_decision=deny-evidence-acceptance-until-operator-non-claim-review-complete'
require_output_contains "$output" 'evidence_acceptance_preflight_denial_reason=operator-non-claim-review-not-completed'
require_output_contains "$output" 'evidence_acceptance_allowed=0'
require_output_contains "$output" 'evidence_acceptance_performed=0'
require_output_contains "$output" 'evidence_acceptance_file_written=0'
require_output_contains "$output" 'guarded_model1_effect_demonstration_evidence_accepted=0'
require_output_contains "$output" 'model1_bridge_execution_performed=0'
require_output_contains "$output" 'model1_process_launch_performed=0'
require_output_contains "$output" 'effect_execution_performed=0'
require_output_contains "$output" 'file_mutation_performed=0'
require_output_contains "$output" 'runtime_authority_granted=0'
require_output_contains "$output" 'denial_reason=operator-non-claim-review-not-completed'

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-model1-demo-acceptance-preflight-denial.XXXXXX")"
trap 'rm -rf "$tmp"' EXIT INT HUP TERM

if sh "$gate_script" --packet "$invalid_fixture" >"$tmp/invalid-gate.out" 2>"$tmp/invalid-gate.err"; then
  fail 'expected invalid fixture rejection'
fi
invalid_output="$(cat "$tmp/invalid-gate.out")"
require_output_contains "$invalid_output" 'evidence_acceptance_preflight_denial_gate_status=rejected'
require_output_contains "$invalid_output" 'operator_non_claim_review_receipt_output_valid=0'
require_output_contains "$invalid_output" 'operator_non_claim_review_receipt_entry_present=0'
require_output_contains "$invalid_output" 'evidence_acceptance_preflight_denial_entry_present=0'
require_output_contains "$invalid_output" 'evidence_acceptance_preflight_denial_state=not-recorded'
require_output_contains "$invalid_output" 'evidence_acceptance_allowed=0'
require_output_contains "$invalid_output" 'guarded_model1_effect_demonstration_evidence_accepted=0'
require_output_contains "$invalid_output" 'runtime_authority_granted=0'
require_output_contains "$invalid_output" 'denial_reason=operator-non-claim-review-receipt-rejected'

printf 'latticra_guarded_model1_effect_demonstration_evidence_acceptance_preflight_denial_gate: ok\n'
