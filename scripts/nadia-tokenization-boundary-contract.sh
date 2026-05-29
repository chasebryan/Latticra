#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  nadia-tokenization-boundary-contract.sh [options]

Options:
  --prompt-evaluation-handoff <file>  Stage-16 Nadia prompt-evaluation handoff contract
  --request-class <label>             Operator request classification label
  --output <dir>                      Output directory for tokenization-boundary contracts

Creates Nadia Stage-17 tokenization-boundary contract metadata only. It verifies
the prompt-evaluation handoff contract and records the blocked tokenization
state before any future tokenizer specification, prompt tokenization, or prompt
evaluation boundary. It does not generate dialogue, receive prompt text,
materialize prompts, load tokenizer files, load tokenizer vocabularies, tokenize
prompts, evaluate prompts, load model weights, spawn a runtime, create a model
session, generate tokens, run inference, execute tools, mutate source, train,
distill, download, or use network.
USAGE
}

fail() {
  printf 'nadia tokenization boundary contract: %s\n' "$1" >&2
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
  actual=$(field_or_unknown "$key" "$PROMPT_EVALUATION_HANDOFF_ABS")
  [ "$actual" = "$expected" ] || fail "$message" 65
}

reject_boundary_label() {
  name="$1"
  value="$2"
  normalized=$(printf '%s\n' "$value" | tr '[:upper:]' '[:lower:]')
  case "$normalized" in
    *sex*|*sexual*|*porn*|*erotic*|*nude*|*nudity*|*nsfw*|*fetish*|*adult-content*)
      fail "$name is outside Nadia tokenization-boundary boundary" 65
      ;;
  esac
}

PROMPT_EVALUATION_HANDOFF=""
REQUEST_CLASS="awareness-education"
OUTPUT=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --prompt-evaluation-handoff)
      [ "$#" -ge 2 ] || fail "missing value for --prompt-evaluation-handoff" 64
      PROMPT_EVALUATION_HANDOFF="$2"
      shift 2
      ;;
    --request-class)
      [ "$#" -ge 2 ] || fail "missing value for --request-class" 64
      REQUEST_CLASS="$2"
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

if [ -z "$PROMPT_EVALUATION_HANDOFF" ] && [ -f "reports/nadia/prompt-evaluation-handoff/latest-prompt-evaluation-handoff-contract.txt" ]; then
  PROMPT_EVALUATION_HANDOFF="reports/nadia/prompt-evaluation-handoff/latest-prompt-evaluation-handoff-contract.txt"
fi

[ -n "$PROMPT_EVALUATION_HANDOFF" ] || fail "prompt evaluation handoff contract is required" 64
[ -f "$PROMPT_EVALUATION_HANDOFF" ] || fail "prompt evaluation handoff contract not found: $PROMPT_EVALUATION_HANDOFF" 66

reject_boundary_label "request class" "$REQUEST_CLASS"

if [ -z "$OUTPUT" ]; then
  OUTPUT="reports/nadia/tokenization-boundary"
fi
mkdir -p "$OUTPUT"
OUT_DIR=$(CDPATH= cd -- "$OUTPUT" && pwd -P)

TS=${NADIA_TOKENIZATION_BOUNDARY_TIMESTAMP:-$(date -u +"%Y%m%dT%H%M%SZ")}
REPORT="$OUT_DIR/nadia-tokenization-boundary-contract-$TS.txt"

PROMPT_EVALUATION_HANDOFF_ABS=$(cd "$(dirname -- "$PROMPT_EVALUATION_HANDOFF")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$PROMPT_EVALUATION_HANDOFF")")
PROMPT_EVALUATION_HANDOFF_MEASUREMENT=$(measure_file "$PROMPT_EVALUATION_HANDOFF_ABS")

require_field stage 16-prompt-evaluation-handoff-contract "prompt evaluation handoff stage must be 16-prompt-evaluation-handoff-contract"
require_field prompt_evaluation_handoff_contract_status contract_only "prompt evaluation handoff contract must remain contract-only"
require_field prompt_evaluation_handoff_stage contract-only "prompt evaluation handoff stage must be contract-only"
require_field prompt_evaluation_handoff_authority 0 "prompt evaluation handoff authority must remain denied"
require_field prompt_evaluation_handoff_allowed 0 "prompt evaluation handoff must remain disallowed"
require_field prompt_evaluation_handoff_performed 0 "prompt evaluation handoff must not be performed"
require_field prompt_evaluation_authority 0 "prompt evaluation authority must remain denied"
require_field prompt_evaluated 0 "prompt must not be evaluated"
require_field evaluation_handoff_decision blocked_contract_only "evaluation handoff decision must be blocked_contract_only"
require_field evaluation_handoff_evidence_present 1 "evaluation handoff evidence must be present"
require_field requires_awareness_dialogue_contract 1 "handoff must require awareness dialogue contract"
require_field requires_prompt_materialization_contract 1 "handoff must require prompt materialization contract"
require_field requires_prompt_receipt_contract 1 "handoff must require prompt receipt contract"
require_field requires_protective_safety_boundary 1 "handoff must require protective safety"
require_field requires_operator_review 1 "handoff must require operator review"
require_field requires_official_source_snapshot 1 "handoff must require official source snapshot"
require_field requires_future_tokenization_contract 1 "handoff must require future tokenization contract"
require_field prompt_evaluation_handoff_promotion_allowed 0 "handoff must not allow promotion"
require_field future_qa_dialogue_capability_planned 1 "future Q&A capability must remain planned only"
require_field qa_dialogue_generated 0 "Q&A dialogue must not be generated"
require_field question_generated 0 "questions must not be generated"
require_field answer_generated 0 "answers must not be generated"
require_field answer_text_generated 0 "answer text must not be generated"
require_field q_and_a_format_required 1 "Q&A format requirement must be present"
require_field survivor_centered_dialogue_required 1 "survivor-centered dialogue requirement must be present"
require_field official_source_grounding_required 1 "official source grounding must be required"
require_field live_web_lookup_authority 0 "live web lookup authority must remain denied"
require_field topic_yazidi_genocide_awareness 1 "Yazidi genocide awareness topic must be present"
require_field topic_conflict_related_sexual_violence_awareness_non_graphic 1 "non-graphic conflict-related sexual violence awareness topic must be present"
require_field topic_womens_empowerment 1 "women's empowerment topic must be present"
require_field sexualized_dialogue_generation 0 "sexualized dialogue generation must remain forbidden"
require_field graphic_sexual_detail_allowed 0 "graphic sexual detail must remain forbidden"
require_field victim_blaming_allowed 0 "victim blaming must remain forbidden"
require_field genocide_denial_allowed 0 "genocide denial must remain forbidden"
require_field medical_advice_authority 0 "medical advice authority must remain denied"
require_field legal_advice_authority 0 "legal advice authority must remain denied"
require_field trauma_counseling_authority 0 "trauma counseling authority must remain denied"
require_field prompt_materialized 0 "prompt must not be materialized"
require_field prompt_text_materialized 0 "prompt text must not be materialized"
require_field prompt_buffer_allocated 0 "prompt buffer must not be allocated"
require_field prompt_buffer_written 0 "prompt buffer must not be written"
require_field prompt_tokenization_authority 0 "prompt tokenization authority must remain denied"
require_field prompt_tokenized 0 "prompt must not be tokenized"
require_field token_generation_performed 0 "token generation must not be performed"
require_field inference_performed 0 "inference must not be performed"
require_field tool_execution_performed 0 "tool execution must not be performed"
require_field network_authority 0 "network authority must remain denied"
require_field sexual_request_refusal always "sexual requests must always be refused"
require_field manipulation_resistance required "manipulation resistance must remain required"

PROMPT_EVALUATION_HANDOFF_CONTRACT_STATUS=$(field_or_unknown prompt_evaluation_handoff_contract_status "$PROMPT_EVALUATION_HANDOFF_ABS")
PROMPT_EVALUATION_HANDOFF_STAGE=$(field_or_unknown prompt_evaluation_handoff_stage "$PROMPT_EVALUATION_HANDOFF_ABS")
AWARENESS_DIALOGUE_STAGE=$(field_or_unknown awareness_dialogue_stage "$PROMPT_EVALUATION_HANDOFF_ABS")
PROMPT_MATERIALIZATION_STAGE=$(field_or_unknown prompt_materialization_stage "$PROMPT_EVALUATION_HANDOFF_ABS")
PROMPT_RECEIPT_STAGE=$(field_or_unknown prompt_receipt_stage "$PROMPT_EVALUATION_HANDOFF_ABS")
MODEL_LOAD_STAGE=$(field_or_unknown model_load_stage "$PROMPT_EVALUATION_HANDOFF_ABS")
MODEL_REGISTRY_STAGE=$(field_or_unknown model_registry_stage "$PROMPT_EVALUATION_HANDOFF_ABS")

cat > "$REPORT" <<REPORT
NADIA TOKENIZATION BOUNDARY CONTRACT

timestamp_utc=$TS
system_name=Latticra Nadia Witness Foundation
public_name=Nadia
interactive_name=Nadia
implementation_name=Nadia Witness Foundation
documentation_code_name=Nadia Witness Foundation
stage=17-tokenization-boundary-contract
output_dir=$OUT_DIR
request_class=$REQUEST_CLASS
tokenization_boundary_contract_status=contract_only
tokenization_boundary_stage=contract-only
tokenization_boundary_authority=0
tokenization_boundary_allowed=0
tokenization_boundary_performed=0
prompt_tokenization_authority=0
prompt_tokenization_allowed=0
prompt_tokenized=0
prompt_tokens_created=0
tokenizer_file_opened=0
tokenizer_vocab_loaded=0
prompt_evaluation_authority=0
prompt_evaluated=0
qa_dialogue_generated=0
question_generated=0
answer_generated=0
answer_text_generated=0

[inputs]
prompt_evaluation_handoff=$PROMPT_EVALUATION_HANDOFF_ABS
prompt_evaluation_handoff_measurement=$PROMPT_EVALUATION_HANDOFF_MEASUREMENT
prompt_evaluation_handoff_stage_required=16-prompt-evaluation-handoff-contract
prompt_evaluation_handoff_contract_status=$PROMPT_EVALUATION_HANDOFF_CONTRACT_STATUS
prompt_evaluation_handoff_stage=$PROMPT_EVALUATION_HANDOFF_STAGE
awareness_dialogue_stage=$AWARENESS_DIALOGUE_STAGE
prompt_materialization_stage=$PROMPT_MATERIALIZATION_STAGE
prompt_receipt_stage=$PROMPT_RECEIPT_STAGE
model_load_stage=$MODEL_LOAD_STAGE
model_registry_stage=$MODEL_REGISTRY_STAGE

[tokenization_boundary_contract]
tokenization_boundary_contract_command=scripts/nadia-tokenization-boundary-contract.sh
installed_tokenization_boundary_contract_command=latticra-nadia tokenization-boundary
tokenization_decision=blocked_contract_only
tokenization_evidence_present=1
requires_prompt_evaluation_handoff_contract=1
requires_awareness_dialogue_contract=1
requires_prompt_materialization_contract=1
requires_prompt_receipt_contract=1
requires_prompt_buffer_boundary=1
requires_protective_safety_boundary=1
requires_operator_review=1
requires_official_source_snapshot=1
requires_future_tokenizer_specification_contract=1
tokenization_boundary_promotion_allowed=0

[tokenizer_denial_boundary]
tokenizer_file_open_authority=0
tokenizer_file_read_authority=0
tokenizer_vocab_load_authority=0
tokenizer_vocab_mapping_authority=0
tokenizer_runtime_attach_authority=0
tokenizer_file_opened=0
tokenizer_file_read=0
tokenizer_vocab_loaded=0
tokenizer_vocab_mapped=0
tokenizer_attached_to_runtime=0
tokenizer_bytes_read=0
tokenizer_hash_computed=0

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

[prompt_boundary]
prompt_materialization_authority=0
prompt_materialization_allowed=0
prompt_materialized=0
prompt_text_materialized=0
prompt_buffer_allocated=0
prompt_buffer_written=0
prompt_tokenization_authority=0
prompt_tokenization_allowed=0
prompt_tokenized=0
prompt_tokens_created=0
prompt_evaluation_handoff_authority=0
prompt_evaluation_handoff_allowed=0
prompt_evaluation_handoff_performed=0
prompt_evaluation_authority=0
prompt_evaluated=0

[runtime_boundary]
runtime_invoked=0
model_loaded=0
model_weights_loaded=0
token_generation_authority=0
token_generation_performed=0
inference_authority=0
inference_performed=0

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
requires_survivor_centered_language_review=1
requires_refusal_policy_review=1
requires_future_tokenizer_specification_contract=1
REPORT

cp "$REPORT" "$OUT_DIR/latest-tokenization-boundary-contract.txt"

printf 'NADIA_TOKENIZATION_BOUNDARY_CONTRACT=%s\n' "$REPORT"
printf 'NADIA_PROMPT_TOKENIZED=0\n'
printf 'NADIA_PROMPT_EVALUATED=0\n'
