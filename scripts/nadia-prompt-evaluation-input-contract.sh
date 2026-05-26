#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  nadia-prompt-evaluation-input-contract.sh [options]

Options:
  --context-window-assembly <file>  Stage-27 Nadia context-window assembly contract
  --request-class <label>           Operator request classification label
  --input-family <label>            Planned prompt-evaluation-input family label
  --input-format <label>            Planned prompt-evaluation-input format label
  --output <dir>                    Output directory for prompt-evaluation-input contracts

Creates Nadia Stage-28 prompt-evaluation-input contract metadata only.
It verifies the context-window assembly contract and records planned prompt
evaluation input requirements before any prompt evaluation input creation,
runtime invocation, prompt evaluation, dialogue generation, token generation,
or inference boundary. It does not read prompt text, assemble context windows,
create prompt evaluation inputs, invoke a runtime, evaluate prompts, generate
dialogue, generate tokens, run inference, execute tools, mutate source, train,
distill, download, or use network.
USAGE
}

fail() {
  printf 'nadia prompt evaluation input contract: %s\n' "$1" >&2
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
  actual=$(field_or_unknown "$key" "$CONTEXT_WINDOW_ASSEMBLY_ABS")
  [ "$actual" = "$expected" ] || fail "$message" 65
}

reject_boundary_label() {
  name="$1"
  value="$2"
  normalized=$(printf '%s\n' "$value" | tr '[:upper:]' '[:lower:]')
  case "$normalized" in
    *sex*|*sexual*|*porn*|*erotic*|*nude*|*nudity*|*nsfw*|*fetish*|*adult-content*)
      fail "$name is outside Nadia prompt-evaluation-input boundary" 65
      ;;
  esac
}

CONTEXT_WINDOW_ASSEMBLY=""
REQUEST_CLASS="awareness-education"
INPUT_FAMILY="operator-reviewed-prompt-evaluation-input"
INPUT_FORMAT="contract-only-offline-evaluation-input"
OUTPUT=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --context-window-assembly)
      [ "$#" -ge 2 ] || fail "missing value for --context-window-assembly" 64
      CONTEXT_WINDOW_ASSEMBLY="$2"
      shift 2
      ;;
    --request-class)
      [ "$#" -ge 2 ] || fail "missing value for --request-class" 64
      REQUEST_CLASS="$2"
      shift 2
      ;;
    --input-family)
      [ "$#" -ge 2 ] || fail "missing value for --input-family" 64
      INPUT_FAMILY="$2"
      shift 2
      ;;
    --input-format)
      [ "$#" -ge 2 ] || fail "missing value for --input-format" 64
      INPUT_FORMAT="$2"
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

if [ -z "$CONTEXT_WINDOW_ASSEMBLY" ] && [ -f "reports/nadia/context-window-assembly/latest-context-window-assembly-contract.txt" ]; then
  CONTEXT_WINDOW_ASSEMBLY="reports/nadia/context-window-assembly/latest-context-window-assembly-contract.txt"
fi

[ -n "$CONTEXT_WINDOW_ASSEMBLY" ] || fail "context window assembly contract is required" 64
[ -f "$CONTEXT_WINDOW_ASSEMBLY" ] || fail "context window assembly contract not found: $CONTEXT_WINDOW_ASSEMBLY" 66

reject_boundary_label "request class" "$REQUEST_CLASS"
reject_boundary_label "input family" "$INPUT_FAMILY"
reject_boundary_label "input format" "$INPUT_FORMAT"

if [ -z "$OUTPUT" ]; then
  OUTPUT="reports/nadia/prompt-evaluation-input"
fi
mkdir -p "$OUTPUT"
OUT_DIR=$(CDPATH= cd -- "$OUTPUT" && pwd -P)

TS=${NADIA_PROMPT_EVALUATION_INPUT_TIMESTAMP:-$(date -u +"%Y%m%dT%H%M%SZ")}
REPORT="$OUT_DIR/nadia-prompt-evaluation-input-contract-$TS.txt"

CONTEXT_WINDOW_ASSEMBLY_ABS=$(cd "$(dirname -- "$CONTEXT_WINDOW_ASSEMBLY")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$CONTEXT_WINDOW_ASSEMBLY")")
CONTEXT_WINDOW_ASSEMBLY_MEASUREMENT=$(measure_file "$CONTEXT_WINDOW_ASSEMBLY_ABS")

require_field stage 27-context-window-assembly-contract "context window assembly stage must be 27-context-window-assembly-contract"
require_field context_window_assembly_contract_status contract_only "context window assembly contract must remain contract-only"
require_field context_window_assembly_stage contract-only "context window assembly stage must be contract-only"
require_field context_window_assembly_authority 0 "context window assembly authority must remain denied"
require_field context_window_assembly_allowed 0 "context window assembly must remain disallowed"
require_field context_window_assembly_performed 0 "context window assembly must not be performed"
require_field context_window_assembly_metadata_present 1 "context window assembly metadata must be present"
require_field context_window_assembly_decision blocked_contract_only "context window assembly decision must be blocked_contract_only"
require_field context_window_assembly_evidence_present 1 "context window assembly evidence must be present"
require_field context_window_assembly_source_policy operator-reviewed-offline "context window assembly source policy must be operator-reviewed-offline"
require_field context_window_assembly_plan_recorded 1 "context window assembly plan must be recorded"
require_field context_window_assembly_result_recorded 0 "context window assembly result must not be recorded"
require_field context_window_assembly_runtime_invoked 0 "context window assembly runtime must not be invoked"
require_field requires_prompt_token_sequence_contract 1 "prompt token sequence contract must be required"
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
require_field requires_future_prompt_evaluation_input_contract 1 "future prompt evaluation input contract must be required"
require_field context_window_assembly_promotion_allowed 0 "context window assembly must not allow promotion"
require_field requires_context_window_layout_policy 1 "context window layout policy must be required"
require_field requires_context_window_token_budget_policy 1 "context window token budget policy must be required"
require_field requires_context_window_truncation_policy 1 "context window truncation policy must be required"
require_field requires_context_window_ordering_policy 1 "context window ordering policy must be required"
require_field requires_attention_mask_policy 1 "attention mask policy must be required"
require_field requires_position_id_policy 1 "position ID policy must be required"
require_field requires_prompt_evaluation_input_policy 1 "prompt evaluation input policy must be required"
require_field requires_no_context_window_assembly 1 "context window assembly denial must be required"
require_field requires_no_prompt_evaluation_input_creation 1 "prompt evaluation input creation denial must be required"
require_field requires_no_runtime_invocation 1 "runtime invocation denial must be required"
require_field requires_no_prompt_evaluation 1 "prompt evaluation denial must be required"
require_field requires_no_dialogue_generation 1 "dialogue generation denial must be required"
require_field requires_no_inference 1 "inference denial must be required"
require_field requires_refusal_policy_link 1 "refusal policy link must be required"
require_field requires_survivor_centered_language_review 1 "survivor-centered language review must be required"
require_field context_window_assembly_open_authority 0 "context window open authority must remain denied"
require_field context_window_assembly_read_authority 0 "context window read authority must remain denied"
require_field context_window_assembly_write_authority 0 "context window write authority must remain denied"
require_field context_window_assembly_execute_authority 0 "context window execute authority must remain denied"
require_field context_window_assembly_runtime_authority 0 "context window runtime authority must remain denied"
require_field context_window_assembly_prompt_evaluation_input_authority 0 "prompt evaluation input authority must remain denied"
require_field context_window_loaded 0 "context window must not be loaded"
require_field context_window_opened 0 "context window must not be opened"
require_field context_window_read 0 "context window must not be read"
require_field context_window_validated 0 "context window must not be validated"
require_field context_window_assembled 0 "context window must not be assembled"
require_field context_window_token_budget_recorded 0 "context window token budget must not be recorded"
require_field context_window_entry_count_recorded 0 "context window entry count must not be recorded"
require_field context_window_truncation_applied 0 "context window truncation must not be applied"
require_field context_window_serialized 0 "context window must not be serialized"
require_field prompt_evaluation_input_created 0 "prompt evaluation input must not be created"
require_field prompt_evaluation_input_materialized 0 "prompt evaluation input must not be materialized"
require_field prompt_evaluation_input_validated 0 "prompt evaluation input must not be validated"
require_field prompt_evaluation_input_written 0 "prompt evaluation input must not be written"
require_field prompt_token_sequence_authority 0 "prompt token sequence authority must remain denied"
require_field prompt_token_sequence_allowed 0 "prompt token sequence must remain disallowed"
require_field prompt_token_sequence_recorded 0 "prompt token sequence must not be recorded"
require_field prompt_token_ids_recorded 0 "prompt token IDs must not be recorded"
require_field prompt_token_order_recorded 0 "prompt token order must not be recorded"
require_field prompt_token_offsets_recorded 0 "prompt token offsets must not be recorded"
require_field prompt_attention_mask_created 0 "prompt attention mask must not be created"
require_field prompt_position_ids_created 0 "prompt position IDs must not be created"
require_field prompt_text_read 0 "prompt text must not be read"
require_field prompt_text_received 0 "prompt text must not be received"
require_field prompt_text_materialized 0 "prompt text must not be materialized"
require_field prompt_tokens_created 0 "prompt tokens must not be created"
require_field prompt_token_count_recorded 0 "prompt token count must not be recorded"
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
require_field survivor_centered_dialogue_required 1 "survivor-centered dialogue requirement must be required"
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

CONTEXT_WINDOW_ASSEMBLY_CONTRACT_STATUS=$(field_or_unknown context_window_assembly_contract_status "$CONTEXT_WINDOW_ASSEMBLY_ABS")
CONTEXT_WINDOW_ASSEMBLY_STAGE=$(field_or_unknown context_window_assembly_stage "$CONTEXT_WINDOW_ASSEMBLY_ABS")
CONTEXT_WINDOW_FAMILY=$(field_or_unknown context_window_family "$CONTEXT_WINDOW_ASSEMBLY_ABS")
CONTEXT_WINDOW_FORMAT=$(field_or_unknown context_window_format "$CONTEXT_WINDOW_ASSEMBLY_ABS")
PROMPT_TOKEN_SEQUENCE_STAGE=$(field_or_unknown prompt_token_sequence_stage "$CONTEXT_WINDOW_ASSEMBLY_ABS")
PROMPT_TOKENIZATION_STAGE=$(field_or_unknown prompt_tokenization_stage "$CONTEXT_WINDOW_ASSEMBLY_ABS")
TOKENIZER_RUNTIME_ATTACHMENT_STAGE=$(field_or_unknown tokenizer_runtime_attachment_stage "$CONTEXT_WINDOW_ASSEMBLY_ABS")
TOKENIZATION_BOUNDARY_STAGE=$(field_or_unknown tokenization_boundary_stage "$CONTEXT_WINDOW_ASSEMBLY_ABS")

cat > "$REPORT" <<REPORT
NADIA PROMPT EVALUATION INPUT CONTRACT

timestamp_utc=$TS
system_name=Latticra Nadia Witness Foundation
public_name=Nadia
interactive_name=Nadia
implementation_name=Nadia Witness Foundation
documentation_code_name=Nadia Witness Foundation
stage=28-prompt-evaluation-input-contract
output_dir=$OUT_DIR
request_class=$REQUEST_CLASS
prompt_evaluation_input_contract_status=contract_only
prompt_evaluation_input_stage=contract-only
prompt_evaluation_input_authority=0
prompt_evaluation_input_allowed=0
prompt_evaluation_input_created=0
prompt_evaluation_input_metadata_present=1
prompt_evaluation_input_family=$INPUT_FAMILY
prompt_evaluation_input_format=$INPUT_FORMAT
prompt_evaluation_input_schema_planned=1
prompt_evaluation_input_schema_validated=0
prompt_evaluation_input_context_reference_recorded=0
prompt_evaluation_input_token_reference_recorded=0
prompt_evaluation_input_safety_envelope_recorded=0
prompt_evaluation_input_loaded=0
prompt_evaluation_input_opened=0
prompt_evaluation_input_read=0
prompt_evaluation_input_materialized=0
prompt_evaluation_input_validated=0
prompt_evaluation_input_serialized=0
prompt_evaluation_input_written=0
context_window_assembled=0
runtime_invoked=0
runtime_session_created=0
prompt_evaluation_authority=0
prompt_evaluated=0
qa_dialogue_generated=0
question_generated=0
answer_generated=0
answer_text_generated=0

[inputs]
context_window_assembly=$CONTEXT_WINDOW_ASSEMBLY_ABS
context_window_assembly_measurement=$CONTEXT_WINDOW_ASSEMBLY_MEASUREMENT
context_window_assembly_stage_required=27-context-window-assembly-contract
context_window_assembly_contract_status=$CONTEXT_WINDOW_ASSEMBLY_CONTRACT_STATUS
context_window_assembly_stage=$CONTEXT_WINDOW_ASSEMBLY_STAGE
context_window_family=$CONTEXT_WINDOW_FAMILY
context_window_format=$CONTEXT_WINDOW_FORMAT
prompt_token_sequence_stage=$PROMPT_TOKEN_SEQUENCE_STAGE
prompt_tokenization_stage=$PROMPT_TOKENIZATION_STAGE
tokenizer_runtime_attachment_stage=$TOKENIZER_RUNTIME_ATTACHMENT_STAGE
tokenization_boundary_stage=$TOKENIZATION_BOUNDARY_STAGE

[prompt_evaluation_input_contract]
prompt_evaluation_input_contract_command=scripts/nadia-prompt-evaluation-input-contract.sh
installed_prompt_evaluation_input_contract_command=latticra-nadia prompt-evaluation-input
prompt_evaluation_input_decision=blocked_contract_only
prompt_evaluation_input_evidence_present=1
prompt_evaluation_input_source_policy=operator-reviewed-offline
prompt_evaluation_input_plan_recorded=1
prompt_evaluation_input_method_planned=offline-prompt-evaluation-input-policy-review
prompt_evaluation_input_result_recorded=0
prompt_evaluation_input_runtime_invoked=0
requires_context_window_assembly_contract=1
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
requires_future_prompt_evaluation_runtime_handoff_contract=1
prompt_evaluation_input_promotion_allowed=0

[prompt_evaluation_input_requirements]
requires_context_window_assembly_reference=1
requires_context_window_policy_reference=1
requires_context_window_token_budget_policy=1
requires_context_window_truncation_policy=1
requires_context_window_ordering_policy=1
requires_prompt_token_sequence_reference=1
requires_prompt_tokenization_reference=1
requires_attention_mask_policy=1
requires_position_id_policy=1
requires_evaluation_input_schema_policy=1
requires_evaluation_input_context_reference_policy=1
requires_evaluation_input_token_sequence_reference_policy=1
requires_evaluation_input_safety_envelope_policy=1
requires_evaluation_input_runtime_denial_policy=1
requires_operator_approval_record=1
requires_official_source_snapshot=1
requires_no_context_window_assembly=1
requires_no_prompt_evaluation_input_creation=1
requires_no_runtime_invocation=1
requires_no_prompt_evaluation=1
requires_no_dialogue_generation=1
requires_no_inference=1
requires_refusal_policy_link=1
requires_survivor_centered_language_review=1

[prompt_evaluation_input_denial_boundary]
prompt_evaluation_input_authority=0
prompt_evaluation_input_allowed=0
prompt_evaluation_input_open_authority=0
prompt_evaluation_input_read_authority=0
prompt_evaluation_input_write_authority=0
prompt_evaluation_input_execute_authority=0
prompt_evaluation_input_runtime_authority=0
prompt_evaluation_input_context_reference_authority=0
prompt_evaluation_input_token_sequence_reference_authority=0
prompt_evaluation_input_runtime_handoff_authority=0
prompt_evaluation_input_created=0
prompt_evaluation_input_materialized=0
prompt_evaluation_input_loaded=0
prompt_evaluation_input_opened=0
prompt_evaluation_input_read=0
prompt_evaluation_input_validated=0
prompt_evaluation_input_serialized=0
prompt_evaluation_input_written=0
prompt_evaluation_input_schema_validated=0
prompt_evaluation_input_context_reference_recorded=0
prompt_evaluation_input_token_reference_recorded=0
prompt_evaluation_input_safety_envelope_recorded=0
prompt_evaluation_input_file_written=0
prompt_evaluation_input_bytes_read=0
prompt_evaluation_input_hash_computed=0
prompt_evaluation_input_runtime_invoked=0

[context_window_assembly_denial_boundary]
context_window_assembly_authority=0
context_window_assembly_allowed=0
context_window_assembly_open_authority=0
context_window_assembly_read_authority=0
context_window_assembly_write_authority=0
context_window_assembly_execute_authority=0
context_window_assembly_runtime_authority=0
context_window_assembly_prompt_evaluation_input_authority=0
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

[prompt_token_sequence_denial_boundary]
prompt_token_sequence_authority=0
prompt_token_sequence_allowed=0
prompt_token_sequence_open_authority=0
prompt_token_sequence_read_authority=0
prompt_token_sequence_write_authority=0
prompt_token_sequence_execute_authority=0
prompt_token_sequence_runtime_authority=0
prompt_token_sequence_context_window_authority=0
prompt_token_sequence_recorded=0
prompt_token_sequence_result_recorded=0
prompt_token_sequence_count_recorded=0
prompt_token_sequence_order_recorded=0
prompt_token_sequence_runtime_invoked=0
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
requires_prompt_evaluation_runtime_handoff_review=1
requires_survivor_centered_language_review=1
requires_refusal_policy_review=1
requires_future_prompt_evaluation_runtime_handoff_contract=1
REPORT

cp "$REPORT" "$OUT_DIR/latest-prompt-evaluation-input-contract.txt"

printf 'NADIA_PROMPT_EVALUATION_INPUT_CONTRACT=%s\n' "$REPORT"
printf 'NADIA_PROMPT_EVALUATION_INPUT_CREATED=0\n'
printf 'NADIA_PROMPT_EVALUATED=0\n'
