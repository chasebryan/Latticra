#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra guarded model1 effect demonstration packet review receipt ledger: %s\n' "$1" >&2
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

doc='docs/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_PACKET_REVIEW_RECEIPT_LEDGER.md'
status='docs/status/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_PACKET_REVIEW_RECEIPT_LEDGER_STATUS.md'
intake_doc='docs/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_EVIDENCE_PACKET_INTAKE_VALIDATOR.md'
intake_status='docs/status/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_EVIDENCE_PACKET_INTAKE_VALIDATOR_STATUS.md'
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
workflow='.github/workflows/latticra-guarded-model1-effect-demo-review-receipt-ledger.yml'
ledger_script='scripts/latticra-guarded-model1-effect-demo-review-receipt-ledger.sh'
ledger_guard='scripts/test-latticra-guarded-model1-effect-demonstration-packet-review-receipt-ledger.sh'
packet_validator='scripts/latticra-guarded-model1-effect-demo-evidence-intake.sh'
valid_fixture='fixtures/latticra-model1-demo-evidence/valid-denied.packet'
invalid_fixture='fixtures/latticra-model1-demo-evidence/effect-performed.packet'

for file in "$doc" "$status" "$intake_doc" "$intake_status" "$transition_doc" "$transition_status" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$makefile" "$quality_guard" "$workflow" "$ledger_script" "$ledger_guard" "$packet_validator" "$valid_fixture" "$invalid_fixture"
do
  require_file "$file"
done

sh -n "$ledger_script"
sh -n "$ledger_guard"

for file in "$doc" "$status"
do
  require_contains 'latticra_guarded_model1_effect_demo_packet_review_receipt_ledger_present=1' "$file"
  require_contains 'guarded_demo_packet_review_receipt_ledger_guard_present=1' "$file"
  require_contains 'guarded_demo_packet_review_receipt_ledger_version=1' "$file"
  require_contains 'edge_checkpoint=v0.3.0edge' "$file"
  require_contains 'packet_intake_validator_reference=docs/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_EVIDENCE_PACKET_INTAKE_VALIDATOR.md' "$file"
  require_contains 'packet_intake_validator_status_reference=docs/status/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_EVIDENCE_PACKET_INTAKE_VALIDATOR_STATUS.md' "$file"
  require_contains 'review_receipt_ledger_script=scripts/latticra-guarded-model1-effect-demo-review-receipt-ledger.sh' "$file"
  require_contains 'review_receipt_ledger_guard_script=scripts/test-latticra-guarded-model1-effect-demonstration-packet-review-receipt-ledger.sh' "$file"
  require_contains 'candidate_packet_sha256_recorded=1' "$file"
  require_contains 'packet_intake_validator_output_valid=1' "$file"
  require_contains 'review_receipt_entry_present=1' "$file"
  require_contains 'review_receipt_entry_decision=recorded-denied-no-effect' "$file"
  require_contains 'review_receipt_operator_non_claim_review_required=1' "$file"
  require_contains 'review_receipt_operator_non_claim_review_completed=0' "$file"
  require_contains 'review_receipt_ledger_file_written=0' "$file"
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
  require_contains 'Guarded Model-1 effect demonstration evidence review disposition gate.' "$file"
  require_contains 'latticra_guarded_model1_effect_demonstration_packet_review_receipt_ledger: ok' "$file"
done

for predecessor in "$intake_doc" "$intake_status" "$transition_doc" "$transition_status"
do
  require_contains 'Guarded Model-1 effect demonstration packet review receipt ledger.' "$predecessor"
  require_contains 'Guarded Model-1 effect demonstration evidence review disposition gate.' "$predecessor"
done

require_contains 'Guarded Model-1 Effect Demonstration Packet Review Receipt Ledger' "$docs_hub"
require_contains 'LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_PACKET_REVIEW_RECEIPT_LEDGER_STATUS.md' "$status_index"
require_contains 'guarded Model-1 effect demonstration packet review receipt ledger](docs/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_PACKET_REVIEW_RECEIPT_LEDGER.md)' "$root_readme"
require_contains 'Latest Latticra guarded Model-1 effect demonstration packet review receipt ledger note: 2026-06-12 CDT' "$root_status"
require_contains 'Latest Latticra guarded Model-1 effect demonstration packet review receipt ledger note: 2026-06-12 CDT' "$current_status"
require_contains 'Latest Latticra guarded Model-1 effect demonstration packet review receipt ledger note: 2026-06-12 CDT' "$current_direction"
require_contains 'Latest Latticra guarded Model-1 effect demonstration packet review receipt ledger note: 2026-06-12 CDT' "$upcoming_work"
require_contains 'Guarded Model-1 effect demonstration packet review receipt ledger.' "$current_status"
require_contains 'Guarded Model-1 effect demonstration packet review receipt ledger.' "$current_direction"
require_contains 'Guarded Model-1 effect demonstration packet review receipt ledger.' "$upcoming_work"
require_contains 'Guarded Model-1 effect demonstration evidence review disposition gate.' "$current_status"
require_contains 'Guarded Model-1 effect demonstration evidence review disposition gate.' "$current_direction"
require_contains 'Guarded Model-1 effect demonstration evidence review disposition gate.' "$upcoming_work"
require_contains 'latticra-guarded-model1-effect-demonstration-packet-review-receipt-ledger:' "$makefile"
require_contains 'sh ./scripts/test-latticra-guarded-model1-effect-demonstration-packet-review-receipt-ledger.sh' "$makefile"
require_contains 'latticra-guarded-model1-effect-demonstration-packet-review-receipt-ledger:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-guarded-model1-effect-demonstration-packet-review-receipt-ledger.sh' "$quality_guard"
require_contains 'Run Latticra guarded Model-1 effect demonstration packet review receipt ledger guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-guarded-model1-effect-demonstration-packet-review-receipt-ledger.sh' "$workflow"

expected_sha="$(sha256_file "$valid_fixture")"
output="$(sh "$ledger_script" --packet "$valid_fixture")"
require_output_contains "$output" 'LATTICRA GUARDED MODEL1 EFFECT DEMONSTRATION PACKET REVIEW RECEIPT LEDGER'
require_output_contains "$output" 'packet_review_receipt_ledger_status=ok'
require_output_contains "$output" 'latticra_guarded_model1_effect_demo_packet_review_receipt_ledger_present=1'
require_output_contains "$output" 'candidate_packet_sha256_recorded=1'
require_output_contains "$output" "candidate_packet_sha256=$expected_sha"
require_output_contains "$output" 'packet_intake_validator_output_valid=1'
require_output_contains "$output" 'review_receipt_entry_present=1'
require_output_contains "$output" 'review_receipt_entry_decision=recorded-denied-no-effect'
require_output_contains "$output" 'review_receipt_entry_id=review-receipt-fixture-guarded-model1-demo-no-effect-denied-v1'
require_output_contains "$output" 'review_receipt_redaction_status=complete'
require_output_contains "$output" 'review_receipt_acceptance_decision=not-accepted'
require_output_contains "$output" 'review_receipt_operator_non_claim_review_completed=0'
require_output_contains "$output" 'review_receipt_ledger_file_written=0'
require_output_contains "$output" 'guarded_model1_effect_demonstration_evidence_accepted=0'
require_output_contains "$output" 'model1_bridge_execution_performed=0'
require_output_contains "$output" 'effect_execution_performed=0'
require_output_contains "$output" 'file_mutation_performed=0'
require_output_contains "$output" 'runtime_authority_granted=0'

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-model1-demo-review-receipt-ledger.XXXXXX")"
trap 'rm -rf "$tmp"' EXIT INT HUP TERM

if sh "$ledger_script" --packet "$invalid_fixture" >"$tmp/invalid-ledger.out" 2>"$tmp/invalid-ledger.err"; then
  fail 'expected invalid fixture rejection'
fi
invalid_output="$(cat "$tmp/invalid-ledger.out")"
require_output_contains "$invalid_output" 'packet_review_receipt_ledger_status=rejected'
require_output_contains "$invalid_output" 'packet_intake_validator_output_valid=0'
require_output_contains "$invalid_output" 'review_receipt_entry_present=0'
require_output_contains "$invalid_output" 'guarded_model1_effect_demonstration_evidence_accepted=0'
require_output_contains "$invalid_output" 'runtime_authority_granted=0'
require_output_contains "$invalid_output" 'denial_reason=packet-intake-validator-rejected'

printf 'latticra_guarded_model1_effect_demonstration_packet_review_receipt_ledger: ok\n'
