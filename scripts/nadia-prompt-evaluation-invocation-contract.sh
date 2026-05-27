#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  nadia-prompt-evaluation-invocation-contract.sh [options]

Options:
  --prompt-evaluation-runtime-handoff <file>  Stage-29 Nadia prompt-evaluation runtime handoff contract
  --request-class <label>                     Operator request classification label
  --invocation-family <label>                 Planned prompt-evaluation invocation family label
  --invocation-format <label>                 Planned prompt-evaluation invocation format label
  --output <dir>                              Output directory for prompt-evaluation invocation contracts

Creates Nadia Stage-30 prompt-evaluation invocation contract metadata only.
It verifies the prompt-evaluation runtime handoff contract and records planned
prompt-evaluation invocation requirements before any runtime invocation,
prompt evaluation, dialogue generation, token generation, or inference
boundary. It does not create invocation requests, submit requests, create
runtime sessions, invoke a runtime, evaluate prompts, generate dialogue,
generate tokens, run inference, execute tools, mutate source, train, distill,
download, or use network.
USAGE
}

fail() {
  printf 'nadia prompt evaluation invocation contract: %s\n' "$1" >&2
  exit "${2:-1}"
}

write_file() {
  target="$1"
  dir=$(dirname -- "$target")

  [ -d "$dir" ] || fail "report directory is missing: $dir" 74
  [ ! -L "$target" ] || fail "refusing to overwrite symlink report: $target" 74
  if [ -e "$target" ] && [ ! -f "$target" ]; then
    fail "refusing to overwrite non-regular report: $target" 74
  fi

  tmp=$(mktemp "$dir/.nadia-prompt-evaluation-invocation.XXXXXX") ||
    fail "failed to create temporary report in: $dir" 74
  if ! cat > "$tmp"; then
    rm -f "$tmp"
    fail "failed to write temporary report: $tmp" 74
  fi
  if ! chmod 0644 "$tmp"; then
    rm -f "$tmp"
    fail "failed to set report mode: $tmp" 74
  fi
  if ! mv -f "$tmp" "$target"; then
    rm -f "$tmp"
    fail "failed to publish report: $target" 74
  fi
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
  actual=$(field_or_unknown "$key" "$PROMPT_EVALUATION_RUNTIME_HANDOFF_ABS")
  [ "$actual" = "$expected" ] || fail "$message" 65
}

reject_boundary_label() {
  name="$1"
  value="$2"
  normalized=$(printf '%s\n' "$value" | tr '[:upper:]' '[:lower:]')
  case "$normalized" in
    *sex*|*sexual*|*porn*|*erotic*|*nude*|*nudity*|*nsfw*|*fetish*|*adult-content*)
      fail "$name is outside Nadia prompt-evaluation-invocation boundary" 65
      ;;
  esac
}

PROMPT_EVALUATION_RUNTIME_HANDOFF=""
REQUEST_CLASS="awareness-education"
INVOCATION_FAMILY="operator-reviewed-prompt-evaluation-invocation"
INVOCATION_FORMAT="contract-only-offline-evaluation-invocation"
OUTPUT=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --prompt-evaluation-runtime-handoff)
      [ "$#" -ge 2 ] || fail "missing value for --prompt-evaluation-runtime-handoff" 64
      PROMPT_EVALUATION_RUNTIME_HANDOFF="$2"
      shift 2
      ;;
    --request-class)
      [ "$#" -ge 2 ] || fail "missing value for --request-class" 64
      REQUEST_CLASS="$2"
      shift 2
      ;;
    --invocation-family)
      [ "$#" -ge 2 ] || fail "missing value for --invocation-family" 64
      INVOCATION_FAMILY="$2"
      shift 2
      ;;
    --invocation-format)
      [ "$#" -ge 2 ] || fail "missing value for --invocation-format" 64
      INVOCATION_FORMAT="$2"
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

if [ -z "$PROMPT_EVALUATION_RUNTIME_HANDOFF" ] && [ -f "reports/nadia/prompt-evaluation-runtime-handoff/latest-prompt-evaluation-runtime-handoff-contract.txt" ]; then
  PROMPT_EVALUATION_RUNTIME_HANDOFF="reports/nadia/prompt-evaluation-runtime-handoff/latest-prompt-evaluation-runtime-handoff-contract.txt"
fi

[ -n "$PROMPT_EVALUATION_RUNTIME_HANDOFF" ] || fail "prompt evaluation runtime handoff contract is required" 64
[ -f "$PROMPT_EVALUATION_RUNTIME_HANDOFF" ] || fail "prompt evaluation runtime handoff contract not found: $PROMPT_EVALUATION_RUNTIME_HANDOFF" 66

reject_boundary_label "request class" "$REQUEST_CLASS"
reject_boundary_label "invocation family" "$INVOCATION_FAMILY"
reject_boundary_label "invocation format" "$INVOCATION_FORMAT"

if [ -z "$OUTPUT" ]; then
  OUTPUT="reports/nadia/prompt-evaluation-invocation"
fi
mkdir -p "$OUTPUT"
OUT_DIR=$(CDPATH= cd -- "$OUTPUT" && pwd -P)

TS=${NADIA_PROMPT_EVALUATION_INVOCATION_TIMESTAMP:-$(date -u +"%Y%m%dT%H%M%SZ")}
REPORT="$OUT_DIR/nadia-prompt-evaluation-invocation-contract-$TS.txt"

PROMPT_EVALUATION_RUNTIME_HANDOFF_ABS=$(cd "$(dirname -- "$PROMPT_EVALUATION_RUNTIME_HANDOFF")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$PROMPT_EVALUATION_RUNTIME_HANDOFF")")
PROMPT_EVALUATION_RUNTIME_HANDOFF_MEASUREMENT=$(measure_file "$PROMPT_EVALUATION_RUNTIME_HANDOFF_ABS")

require_field stage 29-prompt-evaluation-runtime-handoff-contract "prompt evaluation runtime handoff stage must be 29-prompt-evaluation-runtime-handoff-contract"
require_field prompt_evaluation_runtime_handoff_contract_status contract_only "prompt evaluation runtime handoff contract must remain contract-only"
require_field prompt_evaluation_runtime_handoff_stage contract-only "prompt evaluation runtime handoff stage must be contract-only"
require_field prompt_evaluation_runtime_handoff_authority 0 "prompt evaluation runtime handoff authority must remain denied"
require_field prompt_evaluation_runtime_handoff_allowed 0 "prompt evaluation runtime handoff must remain disallowed"
require_field prompt_evaluation_runtime_handoff_performed 0 "prompt evaluation runtime handoff must not be performed"
require_field prompt_evaluation_runtime_handoff_metadata_present 1 "prompt evaluation runtime handoff metadata must be present"
require_field prompt_evaluation_runtime_handoff_decision blocked_contract_only "prompt evaluation runtime handoff decision must be blocked_contract_only"
require_field prompt_evaluation_runtime_handoff_evidence_present 1 "prompt evaluation runtime handoff evidence must be present"
require_field prompt_evaluation_runtime_handoff_source_policy operator-reviewed-offline "prompt evaluation runtime handoff source policy must be operator-reviewed-offline"
require_field prompt_evaluation_runtime_handoff_plan_recorded 1 "prompt evaluation runtime handoff plan must be recorded"
require_field prompt_evaluation_runtime_handoff_result_recorded 0 "prompt evaluation runtime handoff result must not be recorded"
require_field prompt_evaluation_runtime_handoff_runtime_invoked 0 "prompt evaluation runtime handoff runtime must not be invoked"
require_field requires_prompt_evaluation_input_contract 1 "prompt evaluation input contract must be required"
require_field requires_context_window_assembly_contract 1 "context window assembly contract must be required"
require_field requires_prompt_token_sequence_contract 1 "prompt token sequence contract must be required"
require_field requires_prompt_tokenization_contract 1 "prompt tokenization contract must be required"
require_field requires_tokenizer_runtime_attachment_contract 1 "tokenizer runtime attachment contract must be required"
require_field requires_runtime_invocation_contract 1 "runtime invocation contract must be required"
require_field requires_model_load_contract 1 "model load contract must be required"
require_field requires_inference_readiness_contract 1 "inference readiness contract must be required"
require_field requires_local_model_registry_contract 1 "local model registry contract must be required"
require_field requires_prompt_materialization_contract 1 "prompt materialization contract must be required"
require_field requires_prompt_receipt_contract 1 "prompt receipt contract must be required"
require_field requires_future_prompt_evaluation_invocation_contract 1 "future prompt evaluation invocation contract must be required"
require_field prompt_evaluation_runtime_handoff_promotion_allowed 0 "prompt evaluation runtime handoff must not allow promotion"
require_field requires_prompt_evaluation_input_reference 1 "prompt evaluation input reference must be required"
require_field requires_prompt_evaluation_input_schema_policy 1 "prompt evaluation input schema policy must be required"
require_field requires_prompt_evaluation_input_safety_envelope_policy 1 "prompt evaluation input safety envelope policy must be required"
require_field requires_context_window_assembly_reference 1 "context window assembly reference must be required"
require_field requires_prompt_token_sequence_reference 1 "prompt token sequence reference must be required"
require_field requires_prompt_tokenization_reference 1 "prompt tokenization reference must be required"
require_field requires_runtime_profile_reference 1 "runtime profile reference must be required"
require_field requires_runtime_invocation_contract_reference 1 "runtime invocation contract reference must be required"
require_field requires_model_load_contract_reference 1 "model load contract reference must be required"
require_field requires_inference_readiness_contract_reference 1 "inference readiness contract reference must be required"
require_field requires_runtime_handoff_schema_policy 1 "runtime handoff schema policy must be required"
require_field requires_runtime_handoff_denial_policy 1 "runtime handoff denial policy must be required"
require_field requires_prompt_evaluation_invocation_policy 1 "prompt evaluation invocation policy must be required"
require_field requires_token_generation_denial_policy 1 "token generation denial policy must be required"
require_field requires_operator_approval_record 1 "operator approval record must be required"
require_field requires_official_source_snapshot 1 "official source snapshot must be required"
require_field requires_no_prompt_evaluation_runtime_handoff 1 "prompt evaluation runtime handoff denial must be required"
require_field requires_no_runtime_invocation 1 "runtime invocation denial must be required"
require_field requires_no_prompt_evaluation 1 "prompt evaluation denial must be required"
require_field requires_no_dialogue_generation 1 "dialogue generation denial must be required"
require_field requires_no_token_generation 1 "token generation denial must be required"
require_field requires_no_inference 1 "inference denial must be required"
require_field requires_refusal_policy_link 1 "refusal policy link must be required"
require_field requires_survivor_centered_language_review 1 "survivor-centered language review must be required"
require_field prompt_evaluation_runtime_handoff_request_created 0 "runtime handoff request must not be created"
require_field prompt_evaluation_runtime_handoff_request_validated 0 "runtime handoff request must not be validated"
require_field prompt_evaluation_runtime_handoff_request_serialized 0 "runtime handoff request must not be serialized"
require_field prompt_evaluation_runtime_handoff_request_written 0 "runtime handoff request must not be written"
require_field prompt_evaluation_runtime_handoff_request_submitted 0 "runtime handoff request must not be submitted"
require_field prompt_evaluation_runtime_handoff_runtime_selected 0 "runtime must not be selected"
require_field prompt_evaluation_runtime_handoff_model_selected 0 "model must not be selected"
require_field prompt_evaluation_runtime_handoff_session_created 0 "runtime handoff session must not be created"
require_field runtime_handoff_created 0 "runtime handoff must not be created"
require_field runtime_handoff_submitted 0 "runtime handoff must not be submitted"
require_field prompt_evaluation_request_created 0 "prompt evaluation request must not be created"
require_field prompt_evaluation_request_serialized 0 "prompt evaluation request must not be serialized"
require_field prompt_evaluation_request_submitted 0 "prompt evaluation request must not be submitted"
require_field runtime_invocation_requested 0 "runtime invocation must not be requested"
require_field runtime_invocation_authority 0 "runtime invocation authority must remain denied"
require_field runtime_session_authority 0 "runtime session authority must remain denied"
require_field runtime_invoked 0 "runtime must not be invoked"
require_field runtime_session_created 0 "runtime session must not be created"
require_field runtime_process_spawned 0 "runtime process must not be spawned"
require_field runtime_binary_executed 0 "runtime binary must not be executed"
require_field prompt_evaluation_authority 0 "prompt evaluation authority must remain denied"
require_field prompt_evaluated 0 "prompt must not be evaluated"
require_field token_generation_authority 0 "token generation authority must remain denied"
require_field token_generation_performed 0 "token generation must not be performed"
require_field inference_authority 0 "inference authority must remain denied"
require_field inference_performed 0 "inference must not be performed"
require_field future_qa_dialogue_capability_planned 1 "future Q&A capability must remain planned only"
require_field qa_dialogue_generated 0 "Q&A dialogue must not be generated"
require_field q_and_a_format_required 1 "Q&A format requirement must be present"
require_field survivor_centered_dialogue_required 1 "survivor-centered dialogue requirement must be required"
require_field official_source_grounding_required 1 "official source grounding must be required"
require_field live_web_lookup_authority 0 "live web lookup authority must remain denied"
require_field sexual_user_request_authority 0 "sexual user request authority must remain denied"
require_field sexual_content_generation 0 "sexual content generation must remain forbidden"
require_field sexualized_dialogue_generation 0 "sexualized dialogue generation must remain forbidden"
require_field graphic_sexual_detail_allowed 0 "graphic sexual detail must remain forbidden"
require_field erotic_content_allowed 0 "erotic content must remain forbidden"
require_field roleplay_allowed 0 "roleplay must remain forbidden"
require_field survivor_impersonation_allowed 0 "survivor impersonation must remain forbidden"
require_field victim_blaming_allowed 0 "victim blaming must remain forbidden"
require_field genocide_denial_allowed 0 "genocide denial must remain forbidden"
require_field sexual_request_refusal always "sexual requests must always be refused"
require_field manipulation_resistance required "manipulation resistance must remain required"
require_field network_authority 0 "network authority must remain denied"
require_field tool_execution_authority 0 "tool execution authority must remain denied"
require_field tool_execution_performed 0 "tool execution must not be performed"
require_field source_mutation_authority 0 "source mutation authority must remain denied"
require_field self_modification_authority 0 "self-modification authority must remain denied"
require_field training_performed 0 "training must not be performed"
require_field distillation_performed 0 "distillation must not be performed"

PROMPT_EVALUATION_RUNTIME_HANDOFF_CONTRACT_STATUS=$(field_or_unknown prompt_evaluation_runtime_handoff_contract_status "$PROMPT_EVALUATION_RUNTIME_HANDOFF_ABS")
PROMPT_EVALUATION_RUNTIME_HANDOFF_STAGE=$(field_or_unknown prompt_evaluation_runtime_handoff_stage "$PROMPT_EVALUATION_RUNTIME_HANDOFF_ABS")
PROMPT_EVALUATION_RUNTIME_HANDOFF_FAMILY=$(field_or_unknown prompt_evaluation_runtime_handoff_family "$PROMPT_EVALUATION_RUNTIME_HANDOFF_ABS")
PROMPT_EVALUATION_RUNTIME_HANDOFF_FORMAT=$(field_or_unknown prompt_evaluation_runtime_handoff_format "$PROMPT_EVALUATION_RUNTIME_HANDOFF_ABS")
PROMPT_EVALUATION_INPUT_STAGE=$(field_or_unknown prompt_evaluation_input_stage "$PROMPT_EVALUATION_RUNTIME_HANDOFF_ABS")
CONTEXT_WINDOW_ASSEMBLY_STAGE=$(field_or_unknown context_window_assembly_stage "$PROMPT_EVALUATION_RUNTIME_HANDOFF_ABS")
PROMPT_TOKEN_SEQUENCE_STAGE=$(field_or_unknown prompt_token_sequence_stage "$PROMPT_EVALUATION_RUNTIME_HANDOFF_ABS")
PROMPT_TOKENIZATION_STAGE=$(field_or_unknown prompt_tokenization_stage "$PROMPT_EVALUATION_RUNTIME_HANDOFF_ABS")
TOKENIZER_RUNTIME_ATTACHMENT_STAGE=$(field_or_unknown tokenizer_runtime_attachment_stage "$PROMPT_EVALUATION_RUNTIME_HANDOFF_ABS")

write_file "$REPORT" <<REPORT
NADIA PROMPT EVALUATION INVOCATION CONTRACT

timestamp_utc=$TS
system_name=Latticra Nadia Witness Foundation
public_name=Nadia
interactive_name=Nadia
implementation_name=Nadia Witness Foundation
documentation_code_name=Nadia Witness Foundation
stage=30-prompt-evaluation-invocation-contract
output_dir=$OUT_DIR
request_class=$REQUEST_CLASS
prompt_evaluation_invocation_contract_status=contract_only
prompt_evaluation_invocation_stage=contract-only
prompt_evaluation_invocation_authority=0
prompt_evaluation_invocation_allowed=0
prompt_evaluation_invocation_performed=0
prompt_evaluation_invocation_metadata_present=1
prompt_evaluation_invocation_family=$INVOCATION_FAMILY
prompt_evaluation_invocation_format=$INVOCATION_FORMAT
prompt_evaluation_invocation_schema_planned=1
prompt_evaluation_invocation_schema_validated=0
prompt_evaluation_invocation_request_created=0
prompt_evaluation_invocation_request_validated=0
prompt_evaluation_invocation_request_serialized=0
prompt_evaluation_invocation_request_written=0
prompt_evaluation_invocation_request_submitted=0
prompt_evaluation_invocation_request_scheduled=0
prompt_evaluation_invocation_request_queued=0
prompt_evaluation_invocation_runtime_selected=0
prompt_evaluation_invocation_model_selected=0
prompt_evaluation_invocation_session_created=0
prompt_evaluation_invocation_runtime_invoked=0
prompt_evaluation_runtime_handoff_performed=0
runtime_handoff_created=0
runtime_handoff_submitted=0
runtime_invocation_requested=0
runtime_invoked=0
runtime_session_created=0
prompt_evaluation_authority=0
prompt_evaluated=0
token_generation_authority=0
token_generation_performed=0
inference_authority=0
inference_performed=0
qa_dialogue_generated=0
question_generated=0
answer_generated=0
answer_text_generated=0

[inputs]
prompt_evaluation_runtime_handoff=$PROMPT_EVALUATION_RUNTIME_HANDOFF_ABS
prompt_evaluation_runtime_handoff_measurement=$PROMPT_EVALUATION_RUNTIME_HANDOFF_MEASUREMENT
prompt_evaluation_runtime_handoff_stage_required=29-prompt-evaluation-runtime-handoff-contract
prompt_evaluation_runtime_handoff_contract_status=$PROMPT_EVALUATION_RUNTIME_HANDOFF_CONTRACT_STATUS
prompt_evaluation_runtime_handoff_stage=$PROMPT_EVALUATION_RUNTIME_HANDOFF_STAGE
prompt_evaluation_runtime_handoff_family=$PROMPT_EVALUATION_RUNTIME_HANDOFF_FAMILY
prompt_evaluation_runtime_handoff_format=$PROMPT_EVALUATION_RUNTIME_HANDOFF_FORMAT
prompt_evaluation_input_stage=$PROMPT_EVALUATION_INPUT_STAGE
context_window_assembly_stage=$CONTEXT_WINDOW_ASSEMBLY_STAGE
prompt_token_sequence_stage=$PROMPT_TOKEN_SEQUENCE_STAGE
prompt_tokenization_stage=$PROMPT_TOKENIZATION_STAGE
tokenizer_runtime_attachment_stage=$TOKENIZER_RUNTIME_ATTACHMENT_STAGE

[prompt_evaluation_invocation_contract]
prompt_evaluation_invocation_contract_command=scripts/nadia-prompt-evaluation-invocation-contract.sh
installed_prompt_evaluation_invocation_contract_command=latticra-nadia prompt-evaluation-invocation
prompt_evaluation_invocation_decision=blocked_contract_only
prompt_evaluation_invocation_evidence_present=1
prompt_evaluation_invocation_source_policy=operator-reviewed-offline
prompt_evaluation_invocation_plan_recorded=1
prompt_evaluation_invocation_method_planned=offline-prompt-evaluation-invocation-policy-review
prompt_evaluation_invocation_result_recorded=0
prompt_evaluation_invocation_runtime_invoked=0
requires_prompt_evaluation_runtime_handoff_contract=1
requires_prompt_evaluation_input_contract=1
requires_context_window_assembly_contract=1
requires_prompt_token_sequence_contract=1
requires_prompt_tokenization_contract=1
requires_tokenizer_runtime_attachment_contract=1
requires_runtime_invocation_contract=1
requires_model_load_contract=1
requires_inference_readiness_contract=1
requires_local_model_registry_contract=1
requires_prompt_materialization_contract=1
requires_prompt_receipt_contract=1
requires_future_prompt_evaluation_result_contract=1
prompt_evaluation_invocation_promotion_allowed=0

[prompt_evaluation_invocation_requirements]
requires_prompt_evaluation_runtime_handoff_reference=1
requires_prompt_evaluation_input_reference=1
requires_context_window_assembly_reference=1
requires_prompt_token_sequence_reference=1
requires_prompt_tokenization_reference=1
requires_runtime_profile_reference=1
requires_runtime_invocation_contract_reference=1
requires_model_load_contract_reference=1
requires_inference_readiness_contract_reference=1
requires_prompt_evaluation_invocation_schema_policy=1
requires_prompt_evaluation_invocation_denial_policy=1
requires_prompt_evaluation_result_schema_policy=1
requires_token_generation_denial_policy=1
requires_operator_approval_record=1
requires_official_source_snapshot=1
requires_no_prompt_evaluation_invocation=1
requires_no_runtime_invocation=1
requires_no_prompt_evaluation=1
requires_no_dialogue_generation=1
requires_no_token_generation=1
requires_no_inference=1
requires_refusal_policy_link=1
requires_survivor_centered_language_review=1

[prompt_evaluation_invocation_denial_boundary]
prompt_evaluation_invocation_authority=0
prompt_evaluation_invocation_allowed=0
prompt_evaluation_invocation_open_authority=0
prompt_evaluation_invocation_read_authority=0
prompt_evaluation_invocation_write_authority=0
prompt_evaluation_invocation_execute_authority=0
prompt_evaluation_invocation_runtime_authority=0
prompt_evaluation_invocation_prompt_evaluation_authority=0
prompt_evaluation_invocation_token_generation_authority=0
prompt_evaluation_invocation_inference_authority=0
prompt_evaluation_invocation_performed=0
prompt_evaluation_invocation_created=0
prompt_evaluation_invocation_materialized=0
prompt_evaluation_invocation_loaded=0
prompt_evaluation_invocation_opened=0
prompt_evaluation_invocation_read=0
prompt_evaluation_invocation_validated=0
prompt_evaluation_invocation_serialized=0
prompt_evaluation_invocation_written=0
prompt_evaluation_invocation_request_created=0
prompt_evaluation_invocation_request_validated=0
prompt_evaluation_invocation_request_serialized=0
prompt_evaluation_invocation_request_written=0
prompt_evaluation_invocation_request_submitted=0
prompt_evaluation_invocation_request_scheduled=0
prompt_evaluation_invocation_request_queued=0
prompt_evaluation_invocation_runtime_selected=0
prompt_evaluation_invocation_model_selected=0
prompt_evaluation_invocation_session_created=0
prompt_evaluation_invocation_runtime_invoked=0
prompt_evaluation_request_created=0
prompt_evaluation_request_serialized=0
prompt_evaluation_request_submitted=0
runtime_invocation_requested=0
runtime_invocation_authority=0
runtime_session_authority=0
runtime_invoked=0
runtime_session_created=0
runtime_process_spawned=0
runtime_binary_executed=0
prompt_evaluation_authority=0
prompt_evaluated=0
token_generation_authority=0
token_generation_performed=0
inference_authority=0
inference_performed=0

[prompt_evaluation_runtime_handoff_denial_boundary]
prompt_evaluation_runtime_handoff_authority=0
prompt_evaluation_runtime_handoff_allowed=0
prompt_evaluation_runtime_handoff_performed=0
prompt_evaluation_runtime_handoff_request_created=0
prompt_evaluation_runtime_handoff_request_validated=0
prompt_evaluation_runtime_handoff_request_serialized=0
prompt_evaluation_runtime_handoff_request_written=0
prompt_evaluation_runtime_handoff_request_submitted=0
prompt_evaluation_runtime_handoff_runtime_selected=0
prompt_evaluation_runtime_handoff_model_selected=0
prompt_evaluation_runtime_handoff_session_created=0
prompt_evaluation_runtime_handoff_runtime_invoked=0
runtime_handoff_created=0
runtime_handoff_submitted=0

[prompt_evaluation_input_denial_boundary]
prompt_evaluation_input_authority=0
prompt_evaluation_input_allowed=0
prompt_evaluation_input_created=0
prompt_evaluation_input_materialized=0
prompt_evaluation_input_loaded=0
prompt_evaluation_input_opened=0
prompt_evaluation_input_read=0
prompt_evaluation_input_validated=0
prompt_evaluation_input_serialized=0
prompt_evaluation_input_written=0
prompt_evaluation_input_runtime_invoked=0

[context_window_assembly_denial_boundary]
context_window_assembly_authority=0
context_window_assembly_allowed=0
context_window_assembly_performed=0
context_window_assembly_runtime_invoked=0
context_window_assembled=0
context_window_serialized=0

[prompt_token_sequence_denial_boundary]
prompt_token_sequence_authority=0
prompt_token_sequence_allowed=0
prompt_token_sequence_recorded=0
prompt_token_sequence_runtime_invoked=0
prompt_tokens_created=0
prompt_token_count_recorded=0
prompt_token_ids_recorded=0
prompt_token_order_recorded=0
prompt_token_offsets_recorded=0
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
requires_prompt_evaluation_runtime_handoff_review=1
requires_prompt_evaluation_invocation_review=1
requires_prompt_evaluation_result_review=1
requires_survivor_centered_language_review=1
requires_refusal_policy_review=1
requires_future_prompt_evaluation_result_contract=1
REPORT

write_file "$OUT_DIR/latest-prompt-evaluation-invocation-contract.txt" < "$REPORT"

printf 'NADIA_PROMPT_EVALUATION_INVOCATION_CONTRACT=%s\n' "$REPORT"
printf 'NADIA_PROMPT_EVALUATION_INVOCATION_PERFORMED=0\n'
printf 'NADIA_RUNTIME_INVOKED=0\n'
