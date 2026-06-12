#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

fail() {
  printf 'latticra guarded model1 effect demonstration evidence packet intake validator: %s\n' "$1" >&2
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

require_rejected_packet() {
  packet="$1"
  reason="$2"
  out="$tmp/$(basename "$packet").out"
  err="$tmp/$(basename "$packet").err"
  if sh "$validator" --packet "$packet" >"$out" 2>"$err"; then
    fail "expected packet rejection: $packet"
  fi
  output="$(cat "$out")"
  require_output_contains "$output" 'intake_validation_status=rejected'
  require_output_contains "$output" 'guarded_demo_evidence_packet_candidate_valid=0'
  require_output_contains "$output" 'guarded_model1_effect_demonstration_evidence_accepted=0'
  require_output_contains "$output" 'runtime_authority_granted=0'
  require_output_contains "$output" "denial_reason=$reason"
}

doc='docs/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_EVIDENCE_PACKET_INTAKE_VALIDATOR.md'
status='docs/status/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_EVIDENCE_PACKET_INTAKE_VALIDATOR_STATUS.md'
boundary_doc='docs/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_EVIDENCE_BOUNDARY.md'
boundary_status='docs/status/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_EVIDENCE_BOUNDARY_STATUS.md'
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
workflow='.github/workflows/latticra-guarded-model1-effect-demo-evidence-packet-intake-validator.yml'
validator='scripts/latticra-guarded-model1-effect-demo-evidence-intake.sh'
valid_fixture='fixtures/latticra-model1-demo-evidence/valid-denied.packet'
missing_redaction_fixture='fixtures/latticra-model1-demo-evidence/missing-redaction.packet'
unredacted_fixture='fixtures/latticra-model1-demo-evidence/unredacted.packet'
effect_performed_fixture='fixtures/latticra-model1-demo-evidence/effect-performed.packet'
claim_promoting_fixture='fixtures/latticra-model1-demo-evidence/claim-promoting.packet'

for file in "$doc" "$status" "$boundary_doc" "$boundary_status" "$transition_doc" "$transition_status" "$status_index" "$docs_hub" "$root_readme" "$root_status" "$current_status" "$current_direction" "$upcoming_work" "$makefile" "$quality_guard" "$workflow" "$validator" "$valid_fixture" "$missing_redaction_fixture" "$unredacted_fixture" "$effect_performed_fixture" "$claim_promoting_fixture"
do
  require_file "$file"
done

sh -n "$validator"
sh -n "$0"

for file in "$doc" "$status"
do
  require_contains 'latticra_guarded_model1_effect_demo_evidence_packet_intake_validator_present=1' "$file"
  require_contains 'guarded_demo_evidence_packet_validator_guard_present=1' "$file"
  require_contains 'guarded_demo_evidence_packet_validator_version=1' "$file"
  require_contains 'edge_checkpoint=v0.3.0edge' "$file"
  require_contains 'transition_intake_reference=docs/LATTICRA_EFFECT_SUBSTRATE_TRANSITION_INTAKE.md' "$file"
  require_contains 'guarded_demo_evidence_boundary_reference=docs/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_EVIDENCE_BOUNDARY.md' "$file"
  require_contains 'effect_contract_schema_reference=docs/LATTICRA_EFFECT_CONTRACT_SCHEMA.md' "$file"
  require_contains 'model1_bridge_protocol_reference=docs/LATTICRA_MODEL1_BRIDGE_PROTOCOL_CONTRACT.md' "$file"
  require_contains 'model1_import_mixed_build_review_boundary_reference=docs/LATTICRA_MODEL1_IMPORT_MIXED_BUILD_REVIEW_BOUNDARY.md' "$file"
  require_contains 'validator_script=scripts/latticra-guarded-model1-effect-demo-evidence-intake.sh' "$file"
  require_contains 'validator_guard_script=scripts/test-latticra-guarded-model1-effect-demonstration-evidence-packet-intake-validator.sh' "$file"
  require_contains 'fixture_directory=fixtures/latticra-model1-demo-evidence' "$file"
  require_contains 'guarded_demo_evidence_packet_fixture_valid_present=1' "$file"
  require_contains 'guarded_demo_evidence_packet_fixture_missing_redaction_rejected=1' "$file"
  require_contains 'guarded_demo_evidence_packet_fixture_unredacted_rejected=1' "$file"
  require_contains 'guarded_demo_evidence_packet_fixture_effect_performed_rejected=1' "$file"
  require_contains 'guarded_demo_evidence_packet_fixture_claim_promoting_rejected=1' "$file"
  require_contains 'guarded_demo_evidence_packet_candidate_valid=1' "$file"
  require_contains 'guarded_demo_evidence_packet_required_fields_present=1' "$file"
  require_contains 'guarded_demo_evidence_packet_required_values_valid=1' "$file"
  require_contains 'guarded_demo_evidence_packet_negative_fields_zero=1' "$file"
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
  require_contains 'Guarded Model-1 effect demonstration packet review receipt ledger.' "$file"
  require_contains 'latticra_guarded_model1_effect_demonstration_evidence_packet_intake_validator: ok' "$file"
done

for required_field in guarded_demo_evidence_id guarded_demo_evidence_version source_revision request_contract_reference bridge_protocol_reference model1_import_review_reference operator_workflow_reference requested_effect allowed_effect deny_by_default_decision bridge_request_message_id bridge_request_trace_id bridge_request_digest bridge_response_message_id bridge_response_trace_id bridge_response_digest target_identity target_revision target_evidence_id target_observation_digest redaction_status non_claim_review_reference acceptance_decision denial_reason guarded_model1_effect_demonstration_satisfied guarded_model1_effect_demonstration_evidence_accepted model1_bridge_execution_performed model1_process_launch_performed effect_execution_performed command_execution_performed file_mutation_performed network_performed host_mutation_performed runtime_authority_granted production_readiness_claim distribution_readiness_claim
do
  require_contains "$required_field" "$doc"
  require_contains "$required_field" "$valid_fixture"
done

for predecessor in "$boundary_doc" "$boundary_status" "$transition_doc" "$transition_status"
do
  require_contains 'Guarded Model-1 effect demonstration evidence packet intake validator.' "$predecessor"
  require_contains 'Guarded Model-1 effect demonstration packet review receipt ledger.' "$predecessor"
done

require_contains 'Guarded Model-1 Effect Demonstration Evidence Packet Intake Validator' "$docs_hub"
require_contains 'LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_EVIDENCE_PACKET_INTAKE_VALIDATOR_STATUS.md' "$status_index"
require_contains 'guarded Model-1 effect demonstration evidence packet intake validator](docs/LATTICRA_GUARDED_MODEL1_EFFECT_DEMONSTRATION_EVIDENCE_PACKET_INTAKE_VALIDATOR.md)' "$root_readme"
require_contains 'Latest Latticra guarded Model-1 effect demonstration evidence packet intake validator note: 2026-06-12 CDT' "$root_status"
require_contains 'Latest Latticra guarded Model-1 effect demonstration evidence packet intake validator note: 2026-06-12 CDT' "$current_status"
require_contains 'Latest Latticra guarded Model-1 effect demonstration evidence packet intake validator note: 2026-06-12 CDT' "$current_direction"
require_contains 'Latest Latticra guarded Model-1 effect demonstration evidence packet intake validator note: 2026-06-12 CDT' "$upcoming_work"
require_contains 'Guarded Model-1 effect demonstration evidence packet intake validator.' "$current_status"
require_contains 'Guarded Model-1 effect demonstration evidence packet intake validator.' "$current_direction"
require_contains 'Guarded Model-1 effect demonstration evidence packet intake validator.' "$upcoming_work"
require_contains 'Guarded Model-1 effect demonstration packet review receipt ledger.' "$current_status"
require_contains 'Guarded Model-1 effect demonstration packet review receipt ledger.' "$current_direction"
require_contains 'Guarded Model-1 effect demonstration packet review receipt ledger.' "$upcoming_work"
require_contains 'latticra-guarded-model1-effect-demonstration-evidence-packet-intake-validator:' "$makefile"
require_contains 'sh ./scripts/test-latticra-guarded-model1-effect-demonstration-evidence-packet-intake-validator.sh' "$makefile"
require_contains 'latticra-guarded-model1-effect-demonstration-evidence-packet-intake-validator:' "$quality_guard"
require_contains 'sh ./scripts/test-latticra-guarded-model1-effect-demonstration-evidence-packet-intake-validator.sh' "$quality_guard"
require_contains 'Run Latticra guarded Model-1 effect demonstration evidence packet intake validator guard' "$workflow"
require_contains 'uses: actions/checkout@34e114876b0b11c390a56381ad16ebd13914f8d5' "$workflow"
require_contains 'persist-credentials: false' "$workflow"
require_contains 'timeout-minutes: 10' "$workflow"
require_contains 'sh scripts/test-latticra-guarded-model1-effect-demonstration-evidence-packet-intake-validator.sh' "$workflow"

tmp="$(mktemp -d "${TMPDIR:-/tmp}/latticra-model1-demo-evidence-intake.XXXXXX")"
trap 'rm -rf "$tmp"' EXIT INT HUP TERM

output="$(sh "$validator" --packet "$valid_fixture")"
require_output_contains "$output" 'LATTICRA GUARDED MODEL1 EFFECT DEMONSTRATION EVIDENCE PACKET INTAKE VALIDATION'
require_output_contains "$output" 'intake_validation_status=ok'
require_output_contains "$output" 'latticra_guarded_model1_effect_demo_evidence_packet_intake_validator_present=1'
require_output_contains "$output" 'guarded_demo_evidence_packet_candidate_valid=1'
require_output_contains "$output" 'guarded_demo_evidence_packet_required_fields_present=1'
require_output_contains "$output" 'guarded_demo_evidence_packet_required_values_valid=1'
require_output_contains "$output" 'guarded_demo_evidence_packet_negative_fields_zero=1'
require_output_contains "$output" 'guarded_model1_effect_demonstration_satisfied=0'
require_output_contains "$output" 'guarded_model1_effect_demonstration_evidence_accepted=0'
require_output_contains "$output" 'model1_bridge_execution_performed=0'
require_output_contains "$output" 'model1_process_launch_performed=0'
require_output_contains "$output" 'effect_dispatch_performed=0'
require_output_contains "$output" 'effect_execution_performed=0'
require_output_contains "$output" 'command_execution_performed=0'
require_output_contains "$output" 'file_mutation_performed=0'
require_output_contains "$output" 'network_performed=0'
require_output_contains "$output" 'host_mutation_performed=0'
require_output_contains "$output" 'runtime_authority_granted=0'
require_output_contains "$output" 'production_readiness_claim=0'
require_output_contains "$output" 'distribution_readiness_claim=0'

require_rejected_packet "$missing_redaction_fixture" 'missing-field:redaction_status'
require_rejected_packet "$unredacted_fixture" 'field-mismatch:redaction_status:expected=complete:actual=required'
require_rejected_packet "$effect_performed_fixture" 'field-mismatch:effect_execution_performed:expected=0:actual=1'
require_rejected_packet "$claim_promoting_fixture" 'field-mismatch:production_readiness_claim:expected=0:actual=1'

printf 'latticra_guarded_model1_effect_demonstration_evidence_packet_intake_validator: ok\n'
