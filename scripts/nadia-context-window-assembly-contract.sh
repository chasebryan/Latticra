#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  nadia-context-window-assembly-contract.sh [options]

Options:
  --prompt-token-sequence <file>  Stage-26 Nadia prompt-token-sequence contract
  --request-class <label>         Operator request classification label
  --context-family <label>        Planned context-window family label
  --context-format <label>        Planned context-window format label
  --output <dir>                  Output directory for context-window contracts

Creates Nadia Stage-27 context-window assembly contract metadata only.
It verifies the prompt-token-sequence contract and records planned context
window requirements before any context window assembly, prompt evaluation input
creation, runtime invocation, dialogue generation, token generation, or
inference boundary. It does not read prompt text, create prompt tokens, record
prompt token sequences, assemble context windows, create prompt evaluation
inputs, invoke a runtime, generate dialogue, generate tokens, run inference,
execute tools, mutate source, train, distill, download, or use network.
USAGE
}

fail() {
  printf 'nadia context window assembly contract: %s\n' "$1" >&2
  exit "${2:-1}"
}

measure_file() {
  file="$1"
  if command -v sha256sum >/dev/null 2>&1; then
    sha256sum "$file" | awk '{ print "sha256:" $1 }'
  elif command -v shasum >/dev/null 2>&1; then
    shasum -a 256 "$file" | awk '{ print "sha256:" $1 }'
  else
    cksum "$file" | awk '{ print "cksum:" $1 ":" $2 }'
  fi
}

field_or_unknown() {
  key="$1"
  file="$2"
  awk -F '=' -v key="$key" '
    $1 == key {
      val = $2
      for (i = 3; i <= NF; i++) val = val "=" $i
      print val
      found = 1
      exit
    }
    END {
      if (!found) print "unknown"
    }
  ' "$file"
}

require_field() {
  key="$1"
  expected="$2"
  message="$3"
  actual=$(field_or_unknown "$key" "$PROMPT_TOKEN_SEQUENCE_ABS")
  [ "$actual" = "$expected" ] || fail "$message" 65
}

reject_boundary_label() {
  name="$1"
  value="$2"
  normalized=$(printf '%s\n' "$value" | tr '[:upper:]' '[:lower:]')
  case "$normalized" in
    *sex*|*sexual*|*porn*|*erotic*|*nude*|*nudity*|*nsfw*|*fetish*|*adult-content*)
      fail "$name is outside Nadia context-window-assembly boundary" 65
      ;;
  esac
}

PROMPT_TOKEN_SEQUENCE=""
REQUEST_CLASS="awareness-education"
CONTEXT_FAMILY="operator-reviewed-context-window-assembly"
CONTEXT_FORMAT="contract-only-offline-context-window"
OUTPUT=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --prompt-token-sequence)
      [ "$#" -ge 2 ] || fail "missing value for --prompt-token-sequence" 64
      PROMPT_TOKEN_SEQUENCE="$2"
      shift 2
      ;;
    --request-class)
      [ "$#" -ge 2 ] || fail "missing value for --request-class" 64
      REQUEST_CLASS="$2"
      shift 2
      ;;
    --context-family)
      [ "$#" -ge 2 ] || fail "missing value for --context-family" 64
      CONTEXT_FAMILY="$2"
      shift 2
      ;;
    --context-format)
      [ "$#" -ge 2 ] || fail "missing value for --context-format" 64
      CONTEXT_FORMAT="$2"
      shift 2
      ;;
    --output)
      [ "$#" -ge 2 ] || fail "missing value for --output" 64
      OUTPUT="$2"
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

if [ -z "$PROMPT_TOKEN_SEQUENCE" ] && [ -f "reports/nadia/prompt-token-sequence/latest-prompt-token-sequence-contract.txt" ]; then
  PROMPT_TOKEN_SEQUENCE="reports/nadia/prompt-token-sequence/latest-prompt-token-sequence-contract.txt"
fi

[ -n "$PROMPT_TOKEN_SEQUENCE" ] || fail "prompt token sequence contract is required" 64
[ -f "$PROMPT_TOKEN_SEQUENCE" ] || fail "prompt token sequence contract not found: $PROMPT_TOKEN_SEQUENCE" 66

reject_boundary_label "request class" "$REQUEST_CLASS"
reject_boundary_label "context family" "$CONTEXT_FAMILY"
reject_boundary_label "context format" "$CONTEXT_FORMAT"

if [ -z "$OUTPUT" ]; then
  OUTPUT="reports/nadia/context-window-assembly"
fi
mkdir -p "$OUTPUT"
OUT_DIR=$(CDPATH= cd -- "$OUTPUT" && pwd -P)

TS=${NADIA_CONTEXT_WINDOW_ASSEMBLY_TIMESTAMP:-$(date -u +"%Y%m%dT%H%M%SZ")}
REPORT="$OUT_DIR/nadia-context-window-assembly-contract-$TS.txt"

PROMPT_TOKEN_SEQUENCE_ABS=$(cd "$(dirname -- "$PROMPT_TOKEN_SEQUENCE")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$PROMPT_TOKEN_SEQUENCE")")
PROMPT_TOKEN_SEQUENCE_MEASUREMENT=$(measure_file "$PROMPT_TOKEN_SEQUENCE_ABS")

require_field stage 26-prompt-token-sequence-contract "prompt token sequence stage must be 26-prompt-token-sequence-contract"
require_field prompt_token_sequence_contract_status contract_only "prompt token sequence contract must remain contract-only"
require_field prompt_token_sequence_stage contract-only "prompt token sequence stage must be contract-only"
require_field prompt_token_sequence_authority 0 "prompt token sequence authority must remain denied"
require_field prompt_token_sequence_allowed 0 "prompt token sequence must remain disallowed"
require_field prompt_token_sequence_recorded 0 "prompt token sequence must not be recorded"
require_field prompt_token_sequence_metadata_present 1 "prompt token sequence metadata must be present"
require_field prompt_token_sequence_decision blocked_contract_only "prompt token sequence decision must be blocked_contract_only"
require_field prompt_token_sequence_evidence_present 1 "prompt token sequence evidence must be present"
require_field prompt_token_sequence_source_policy operator-reviewed-offline "prompt token sequence source policy must be operator-reviewed-offline"
require_field prompt_token_sequence_plan_recorded 1 "prompt token sequence plan must be recorded"
require_field prompt_token_sequence_result_recorded 0 "prompt token sequence result must not be recorded"
require_field prompt_token_sequence_count_recorded 0 "prompt token sequence count must not be recorded"
require_field prompt_token_sequence_order_recorded 0 "prompt token sequence order must not be recorded"
require_field prompt_token_sequence_runtime_invoked 0 "prompt token sequence runtime must not be invoked"
require_field requires_prompt_tokenization_contract 1 "prompt tokenization contract must be required"
require_field requires_tokenizer_runtime_attachment_contract 1 "tokenizer runtime attachment contract must be required"
require_field requires_tokenizer_artifact_binding_contract 1 "tokenizer artifact binding contract must be required"
require_field requires_tokenizer_artifact_verification_contract 1 "tokenizer artifact verification contract must be required"
require_field requires_tokenizer_artifact_measurement_contract 1 "tokenizer artifact measurement contract must be required"
require_field requires_tokenizer_artifact_inventory_contract 1 "tokenizer artifact inventory contract must be required"
require_field requires_tokenizer_manifest_contract 1 "tokenizer manifest contract must be required"
require_field requires_tokenizer_specification_contract 1 "tokenizer specification contract must be required"
require_field requires_tokenization_boundary_contract 1 "tokenization boundary contract must be required"
require_field requires_prompt_materialization_contract 1 "prompt materialization contract must be required"
require_field requires_prompt_receipt_contract 1 "prompt receipt contract must be required"
require_field requires_future_context_window_assembly_contract 1 "future context window assembly contract must be required"
require_field prompt_token_sequence_promotion_allowed 0 "prompt token sequence must not allow promotion"
require_field requires_prompt_tokenization_reference 1 "prompt tokenization reference must be required"
require_field requires_prompt_tokenization_contract_reference 1 "prompt tokenization contract reference must be required"
require_field requires_tokenizer_runtime_attachment_reference 1 "tokenizer runtime attachment reference must be required"
require_field requires_prompt_materialization_reference 1 "prompt materialization reference must be required"
require_field requires_prompt_receipt_reference 1 "prompt receipt reference must be required"
require_field requires_prompt_token_count_policy 1 "prompt token count policy must be required"
require_field requires_prompt_token_order_policy 1 "prompt token order policy must be required"
require_field requires_prompt_token_id_visibility_policy 1 "prompt token ID visibility policy must be required"
require_field requires_prompt_token_offset_policy 1 "prompt token offset policy must be required"
require_field requires_context_window_policy 1 "context window policy must be required"
require_field requires_no_prompt_token_ids_recorded 1 "prompt token ID denial must be required"
require_field requires_no_attention_mask_creation 1 "attention mask creation denial must be required"
require_field requires_no_position_id_creation 1 "position ID creation denial must be required"
require_field requires_no_context_window_assembly 1 "context window assembly denial must be required"
require_field requires_no_runtime_invocation 1 "runtime invocation denial must be required"
require_field requires_no_prompt_evaluation 1 "prompt evaluation denial must be required"
require_field requires_no_dialogue_generation 1 "dialogue generation denial must be required"
require_field requires_no_inference 1 "inference denial must be required"
require_field requires_refusal_policy_link 1 "refusal policy link must be required"
require_field requires_survivor_centered_language_review 1 "survivor-centered language review must be required"
require_field prompt_token_sequence_open_authority 0 "prompt token sequence open authority must remain denied"
require_field prompt_token_sequence_read_authority 0 "prompt token sequence read authority must remain denied"
require_field prompt_token_sequence_write_authority 0 "prompt token sequence write authority must remain denied"
require_field prompt_token_sequence_execute_authority 0 "prompt token sequence execute authority must remain denied"
require_field prompt_token_sequence_runtime_authority 0 "prompt token sequence runtime authority must remain denied"
require_field prompt_token_sequence_token_id_record_authority 0 "prompt token ID record authority must remain denied"
require_field prompt_token_sequence_order_record_authority 0 "prompt token order record authority must remain denied"
require_field prompt_token_sequence_offset_record_authority 0 "prompt token offset record authority must remain denied"
require_field prompt_token_sequence_context_window_authority 0 "prompt token sequence context window authority must remain denied"
require_field prompt_token_ids_recorded 0 "prompt token IDs must not be recorded"
require_field prompt_token_order_recorded 0 "prompt token order must not be recorded"
require_field prompt_token_offsets_recorded 0 "prompt token offsets must not be recorded"
require_field prompt_token_byte_offsets_recorded 0 "prompt token byte offsets must not be recorded"
require_field prompt_attention_mask_created 0 "prompt attention mask must not be created"
require_field prompt_position_ids_created 0 "prompt position IDs must not be created"
require_field context_window_assembled 0 "context window must not be assembled"
require_field prompt_evaluation_input_created 0 "prompt evaluation input must not be created"
require_field prompt_text_read 0 "prompt text must not be read"
require_field prompt_text_received 0 "prompt text must not be received"
require_field prompt_text_materialized 0 "prompt text must not be materialized"
require_field prompt_tokens_created 0 "prompt tokens must not be created"
require_field prompt_token_count_recorded 0 "prompt token count must not be recorded"
require_field prompt_token_sequence_recorded 0 "prompt token sequence must not be recorded"
require_field prompt_tokenized 0 "prompt must not be tokenized"
require_field tokenizer_runtime_attachment_performed 0 "tokenizer runtime attachment must not be performed"
require_field tokenizer_attached_to_runtime 0 "tokenizer must not be attached to runtime"
require_field runtime_session_created 0 "runtime session must not be created"
require_field runtime_invoked 0 "runtime must not be invoked"
require_field runtime_process_spawned 0 "runtime process must not be spawned"
require_field runtime_binary_executed 0 "runtime binary must not be executed"
require_field tokenizer_artifact_binding_performed 0 "tokenizer artifact binding must not be performed"
require_field tokenizer_artifact_file_opened 0 "tokenizer artifact file must not be opened"
require_field tokenizer_artifact_file_read 0 "tokenizer artifact file must not be read"
require_field tokenizer_artifact_hash_computed 0 "tokenizer artifact hash must not be computed"
require_field tokenizer_manifest_loaded 0 "tokenizer manifest must not be loaded"
require_field tokenizer_manifest_parsed 0 "tokenizer manifest must not be parsed"
require_field tokenizer_file_opened 0 "tokenizer file must not be opened"
require_field tokenizer_vocab_loaded 0 "tokenizer vocabulary must not be loaded"
require_field future_qa_dialogue_capability_planned 1 "future Q&A capability must remain planned only"
require_field qa_dialogue_generated 0 "Q&A dialogue must not be generated"
require_field q_and_a_format_required 1 "Q&A format requirement must be present"
require_field survivor_centered_dialogue_required 1 "survivor-centered dialogue requirement must be present"
require_field official_source_grounding_required 1 "official source grounding must be required"
require_field live_web_lookup_authority 0 "live web lookup authority must remain denied"
require_field sexualized_dialogue_generation 0 "sexualized dialogue generation must remain forbidden"
require_field graphic_sexual_detail_allowed 0 "graphic sexual detail must remain forbidden"
require_field victim_blaming_allowed 0 "victim blaming must remain forbidden"
require_field genocide_denial_allowed 0 "genocide denial must remain forbidden"
require_field sexual_request_refusal always "sexual requests must always be refused"
require_field manipulation_resistance required "manipulation resistance must remain required"
require_field prompt_evaluated 0 "prompt must not be evaluated"
require_field token_generation_performed 0 "token generation must not be performed"
require_field inference_performed 0 "inference must not be performed"
require_field tool_execution_performed 0 "tool execution must not be performed"
require_field network_authority 0 "network authority must remain denied"

PROMPT_TOKEN_SEQUENCE_CONTRACT_STATUS=$(field_or_unknown prompt_token_sequence_contract_status "$PROMPT_TOKEN_SEQUENCE_ABS")
PROMPT_TOKEN_SEQUENCE_STAGE=$(field_or_unknown prompt_token_sequence_stage "$PROMPT_TOKEN_SEQUENCE_ABS")
PROMPT_TOKEN_SEQUENCE_FAMILY=$(field_or_unknown prompt_token_sequence_family "$PROMPT_TOKEN_SEQUENCE_ABS")
PROMPT_TOKEN_SEQUENCE_FORMAT=$(field_or_unknown prompt_token_sequence_format "$PROMPT_TOKEN_SEQUENCE_ABS")
PROMPT_TOKENIZATION_STAGE=$(field_or_unknown prompt_tokenization_stage "$PROMPT_TOKEN_SEQUENCE_ABS")
TOKENIZER_RUNTIME_ATTACHMENT_STAGE=$(field_or_unknown tokenizer_runtime_attachment_stage "$PROMPT_TOKEN_SEQUENCE_ABS")
TOKENIZER_ARTIFACT_BINDING_STAGE=$(field_or_unknown tokenizer_artifact_binding_stage "$PROMPT_TOKEN_SEQUENCE_ABS")
TOKENIZER_ARTIFACT_VERIFICATION_STAGE=$(field_or_unknown tokenizer_artifact_verification_stage "$PROMPT_TOKEN_SEQUENCE_ABS")
TOKENIZER_ARTIFACT_MEASUREMENT_STAGE=$(field_or_unknown tokenizer_artifact_measurement_stage "$PROMPT_TOKEN_SEQUENCE_ABS")
TOKENIZER_ARTIFACT_INVENTORY_STAGE=$(field_or_unknown tokenizer_artifact_inventory_stage "$PROMPT_TOKEN_SEQUENCE_ABS")
TOKENIZER_MANIFEST_STAGE=$(field_or_unknown tokenizer_manifest_stage "$PROMPT_TOKEN_SEQUENCE_ABS")
TOKENIZER_SPECIFICATION_STAGE=$(field_or_unknown tokenizer_specification_stage "$PROMPT_TOKEN_SEQUENCE_ABS")
TOKENIZATION_BOUNDARY_STAGE=$(field_or_unknown tokenization_boundary_stage "$PROMPT_TOKEN_SEQUENCE_ABS")

cat > "$REPORT" <<REPORT
NADIA CONTEXT WINDOW ASSEMBLY CONTRACT

timestamp_utc=$TS
system_name=Latticra Nadia Witness Foundation
public_name=Nadia
interactive_name=Nadia
implementation_name=Nadia Witness Foundation
documentation_code_name=Nadia Witness Foundation
stage=27-context-window-assembly-contract
output_dir=$OUT_DIR
request_class=$REQUEST_CLASS
context_window_assembly_contract_status=contract_only
context_window_assembly_stage=contract-only
context_window_assembly_authority=0
context_window_assembly_allowed=0
context_window_assembly_performed=0
context_window_assembly_metadata_present=1
context_window_family=$CONTEXT_FAMILY
context_window_format=$CONTEXT_FORMAT
context_window_loaded=0
context_window_opened=0
context_window_read=0
context_window_validated=0
context_window_assembled=0
context_window_token_budget_recorded=0
context_window_entry_count_recorded=0
context_window_truncation_applied=0
context_window_serialized=0
context_window_runtime_invoked=0
prompt_evaluation_input_created=0
prompt_evaluation_input_materialized=0
prompt_evaluation_input_validated=0
prompt_evaluation_input_written=0
runtime_invoked=0
runtime_session_created=0
prompt_evaluation_authority=0
prompt_evaluated=0
qa_dialogue_generated=0
question_generated=0
answer_generated=0
answer_text_generated=0

[inputs]
prompt_token_sequence=$PROMPT_TOKEN_SEQUENCE_ABS
prompt_token_sequence_measurement=$PROMPT_TOKEN_SEQUENCE_MEASUREMENT
prompt_token_sequence_stage_required=26-prompt-token-sequence-contract
prompt_token_sequence_contract_status=$PROMPT_TOKEN_SEQUENCE_CONTRACT_STATUS
prompt_token_sequence_stage=$PROMPT_TOKEN_SEQUENCE_STAGE
prompt_token_sequence_family=$PROMPT_TOKEN_SEQUENCE_FAMILY
prompt_token_sequence_format=$PROMPT_TOKEN_SEQUENCE_FORMAT
prompt_tokenization_stage=$PROMPT_TOKENIZATION_STAGE
tokenizer_runtime_attachment_stage=$TOKENIZER_RUNTIME_ATTACHMENT_STAGE
tokenizer_artifact_binding_stage=$TOKENIZER_ARTIFACT_BINDING_STAGE
tokenizer_artifact_verification_stage=$TOKENIZER_ARTIFACT_VERIFICATION_STAGE
tokenizer_artifact_measurement_stage=$TOKENIZER_ARTIFACT_MEASUREMENT_STAGE
tokenizer_artifact_inventory_stage=$TOKENIZER_ARTIFACT_INVENTORY_STAGE
tokenizer_manifest_stage=$TOKENIZER_MANIFEST_STAGE
tokenizer_specification_stage=$TOKENIZER_SPECIFICATION_STAGE
tokenization_boundary_stage=$TOKENIZATION_BOUNDARY_STAGE

[context_window_assembly_contract]
context_window_assembly_contract_command=scripts/nadia-context-window-assembly-contract.sh
installed_context_window_assembly_contract_command=latticra-nadia context-window-assembly
context_window_assembly_decision=blocked_contract_only
context_window_assembly_evidence_present=1
context_window_assembly_source_policy=operator-reviewed-offline
context_window_assembly_plan_recorded=1
context_window_assembly_method_planned=offline-context-window-policy-review
context_window_assembly_result_recorded=0
context_window_assembly_runtime_invoked=0
requires_prompt_token_sequence_contract=1
requires_prompt_tokenization_contract=1
requires_tokenizer_runtime_attachment_contract=1
requires_tokenizer_artifact_binding_contract=1
requires_tokenizer_artifact_verification_contract=1
requires_tokenizer_artifact_measurement_contract=1
requires_tokenizer_artifact_inventory_contract=1
requires_tokenizer_manifest_contract=1
requires_tokenizer_specification_contract=1
requires_tokenization_boundary_contract=1
requires_prompt_materialization_contract=1
requires_prompt_receipt_contract=1
requires_future_prompt_evaluation_input_contract=1
context_window_assembly_promotion_allowed=0

[context_window_assembly_requirements]
requires_prompt_token_sequence_reference=1
requires_prompt_tokenization_reference=1
requires_tokenizer_runtime_attachment_reference=1
requires_prompt_materialization_reference=1
requires_prompt_receipt_reference=1
requires_context_window_layout_policy=1
requires_context_window_token_budget_policy=1
requires_context_window_truncation_policy=1
requires_context_window_ordering_policy=1
requires_attention_mask_policy=1
requires_position_id_policy=1
requires_prompt_evaluation_input_policy=1
requires_operator_approval_record=1
requires_official_source_snapshot=1
requires_no_prompt_text_read=1
requires_no_prompt_token_creation=1
requires_no_prompt_token_sequence_recording=1
requires_no_prompt_token_ids_recorded=1
requires_no_context_window_assembly=1
requires_no_prompt_evaluation_input_creation=1
requires_no_runtime_invocation=1
requires_no_prompt_evaluation=1
requires_no_dialogue_generation=1
requires_no_inference=1
requires_refusal_policy_link=1
requires_survivor_centered_language_review=1

[context_window_assembly_denial_boundary]
context_window_assembly_authority=0
context_window_assembly_allowed=0
context_window_assembly_open_authority=0
context_window_assembly_read_authority=0
context_window_assembly_write_authority=0
context_window_assembly_execute_authority=0
context_window_assembly_runtime_authority=0
context_window_assembly_prompt_evaluation_input_authority=0
context_window_assembly_context_write_authority=0
context_window_assembly_performed=0
context_window_assembly_result_recorded=0
context_window_assembly_runtime_invoked=0
context_window_loaded=0
context_window_opened=0
context_window_read=0
context_window_validated=0
context_window_assembled=0
context_window_bytes_read=0
context_window_hash_computed=0
context_window_entries_loaded=0
context_window_token_budget_recorded=0
context_window_entry_count_recorded=0
context_window_truncation_applied=0
context_window_serialized=0
context_window_file_written=0
prompt_evaluation_input_created=0
prompt_evaluation_input_materialized=0
prompt_evaluation_input_validated=0
prompt_evaluation_input_written=0

[prompt_token_sequence_denial_boundary]
prompt_token_sequence_authority=0
prompt_token_sequence_allowed=0
prompt_token_sequence_open_authority=0
prompt_token_sequence_read_authority=0
prompt_token_sequence_write_authority=0
prompt_token_sequence_execute_authority=0
prompt_token_sequence_runtime_authority=0
prompt_token_sequence_token_id_record_authority=0
prompt_token_sequence_order_record_authority=0
prompt_token_sequence_offset_record_authority=0
prompt_token_sequence_context_window_authority=0
prompt_token_sequence_opened=0
prompt_token_sequence_read=0
prompt_token_sequence_validated=0
prompt_token_sequence_loaded=0
prompt_token_sequence_bytes_read=0
prompt_token_sequence_hash_computed=0
prompt_token_sequence_entries_loaded=0
prompt_token_sequence_recorded=0
prompt_token_sequence_result_recorded=0
prompt_token_sequence_count_recorded=0
prompt_token_sequence_order_recorded=0
prompt_token_sequence_runtime_invoked=0
prompt_token_sequence_file_written=0
prompt_tokens_created=0
prompt_token_count_recorded=0
prompt_token_sequence_recorded=0
prompt_token_buffer_created=0
prompt_token_buffer_written=0
prompt_token_ids_recorded=0
prompt_token_order_recorded=0
prompt_token_offsets_recorded=0
prompt_token_byte_offsets_recorded=0
prompt_attention_mask_created=0
prompt_position_ids_created=0

[prompt_tokenization_denial_boundary]
prompt_tokenization_authority=0
prompt_tokenization_allowed=0
prompt_tokenization_performed=0
prompt_tokenization_runtime_invoked=0
prompt_tokenized=0
prompt_text_read=0
prompt_text_received=0
prompt_text_materialized=0
prompt_buffer_allocated=0
prompt_buffer_written=0
prompt_tokens_created=0
prompt_token_count_recorded=0
prompt_token_sequence_recorded=0

[tokenizer_runtime_attachment_denial_boundary]
tokenizer_runtime_attachment_authority=0
tokenizer_runtime_attachment_allowed=0
tokenizer_runtime_attachment_performed=0
tokenizer_runtime_attachment_attached=0
tokenizer_runtime_attachment_runtime_invoked=0
tokenizer_runtime_attachment_session_created=0
tokenizer_attached_to_runtime=0
runtime_tokenizer_attachment_performed=0
runtime_session_created=0
runtime_invoked=0
runtime_process_spawned=0
runtime_binary_executed=0

[tokenizer_artifact_denial_boundary]
tokenizer_artifact_binding_performed=0
tokenizer_artifact_path_resolved=0
tokenizer_artifact_file_opened=0
tokenizer_artifact_file_read=0
tokenizer_artifact_hash_computed=0
tokenizer_manifest_loaded=0
tokenizer_manifest_parsed=0
tokenizer_file_opened=0
tokenizer_file_read=0
tokenizer_vocab_loaded=0

[dialogue_scope]
future_qa_dialogue_capability_planned=1
dialogue_scope=official-nadia-initiative-awareness-work
dialogue_format=question-and-answer
q_and_a_format_required=1
survivor_centered_dialogue_required=1
respectful_tone_required=1
plain_language_required=1
source_attribution_required=1
official_source_grounding_required=1
source_snapshot_policy=operator-reviewed-offline
live_web_lookup_authority=0

[awareness_topic_register]
topic_yazidi_genocide_awareness=1
topic_survivor_voice_and_dignity=1
topic_conflict_related_sexual_violence_awareness_non_graphic=1
topic_genocide_prevention=1
topic_justice_and_accountability=1
topic_women_peace_justice_security=1
topic_sinjar_reconstruction=1
topic_security_and_safe_return=1
topic_education_restoration=1
topic_healthcare_and_mental_health=1
topic_livelihoods_and_food_security=1
topic_wash_clean_water_sanitation_hygiene=1
topic_womens_empowerment=1
topic_legal_rights_and_reparations_awareness=1
topic_cultural_preservation_and_memorialization=1
topic_community_driven_survivor_centric_development=1
topic_responsible_support_and_digital_activism=1

[dialogue_safety_boundary]
sexual_user_request_authority=0
sexual_content_generation=0
sexualized_dialogue_generation=0
graphic_sexual_detail_allowed=0
erotic_content_allowed=0
roleplay_allowed=0
survivor_impersonation_allowed=0
survivor_identifying_speculation_allowed=0
victim_blaming_allowed=0
genocide_denial_allowed=0
hate_or_collective_blame_allowed=0
medical_advice_authority=0
legal_advice_authority=0
trauma_counseling_authority=0
crisis_intervention_authority=0
sexual_request_refusal=always
manipulation_resistance=required
prompt_injection_override_authority=0
policy_bypass_authority=0
namesake_cause_awareness=1

[runtime_boundary]
runtime_invocation_authority=0
runtime_session_authority=0
runtime_invoked=0
runtime_session_created=0
model_loaded=0
model_weights_loaded=0
token_generation_authority=0
token_generation_performed=0
inference_authority=0
inference_performed=0
prompt_evaluation_authority=0
prompt_evaluated=0

[authority]
offline_by_default=1
network_authority=0
tool_execution_authority=0
tool_execution_performed=0
source_mutation_authority=0
self_modification_authority=0
training_performed=0
distillation_performed=0

[operator_review]
requires_operator_review=1
requires_awareness_topic_review=1
requires_official_source_review=1
requires_artifact_inventory_review=1
requires_artifact_measurement_review=1
requires_artifact_verification_review=1
requires_artifact_binding_review=1
requires_runtime_attachment_review=1
requires_prompt_tokenization_review=1
requires_prompt_token_sequence_review=1
requires_context_window_assembly_review=1
requires_prompt_evaluation_input_review=1
requires_survivor_centered_language_review=1
requires_refusal_policy_review=1
requires_future_prompt_evaluation_input_contract=1
REPORT

cp "$REPORT" "$OUT_DIR/latest-context-window-assembly-contract.txt"

printf 'NADIA_CONTEXT_WINDOW_ASSEMBLY_CONTRACT=%s\n' "$REPORT"
printf 'NADIA_CONTEXT_WINDOW_ASSEMBLED=0\n'
printf 'NADIA_PROMPT_EVALUATION_INPUT_CREATED=0\n'
