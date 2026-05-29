#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  nadia-awareness-dialogue-contract.sh [options]

Options:
  --prompt-materialization <file>  Stage-14 Nadia prompt-materialization contract
  --request-class <label>          Operator request classification label
  --output <dir>                   Output directory for awareness-dialogue contracts

Creates Nadia Stage-15 awareness-dialogue contract metadata only. It defines
future Q&A dialogue scope for Nadia Initiative awareness topics, but it does
not generate dialogue, receive prompt text, materialize prompts, tokenize
prompts, evaluate prompts, load model weights, spawn a runtime, create a model
session, generate tokens, run inference, execute tools, mutate source, train,
distill, download, or use network.
USAGE
}

fail() {
  printf 'nadia awareness dialogue contract: %s\n' "$1" >&2
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

reject_boundary_label() {
  name="$1"
  value="$2"
  normalized=$(printf '%s\n' "$value" | tr '[:upper:]' '[:lower:]')
  case "$normalized" in
    *sex*|*sexual*|*porn*|*erotic*|*nude*|*nudity*|*nsfw*|*fetish*|*adult-content*)
      fail "$name is outside Nadia awareness-dialogue boundary" 65
      ;;
  esac
}

PROMPT_MATERIALIZATION=""
REQUEST_CLASS="awareness-education"
OUTPUT=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --prompt-materialization)
      [ "$#" -ge 2 ] || fail "missing value for --prompt-materialization" 64
      PROMPT_MATERIALIZATION="$2"
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

if [ -z "$PROMPT_MATERIALIZATION" ] && [ -f "reports/nadia/prompt-materialization/latest-prompt-materialization-contract.txt" ]; then
  PROMPT_MATERIALIZATION="reports/nadia/prompt-materialization/latest-prompt-materialization-contract.txt"
fi

[ -n "$PROMPT_MATERIALIZATION" ] || fail "prompt materialization contract is required" 64
[ -f "$PROMPT_MATERIALIZATION" ] || fail "prompt materialization contract not found: $PROMPT_MATERIALIZATION" 66

reject_boundary_label "request class" "$REQUEST_CLASS"

if [ -z "$OUTPUT" ]; then
  OUTPUT="reports/nadia/awareness-dialogue"
fi
mkdir -p "$OUTPUT"
OUT_DIR=$(CDPATH= cd -- "$OUTPUT" && pwd -P)

TS=${NADIA_AWARENESS_DIALOGUE_TIMESTAMP:-$(date -u +"%Y%m%dT%H%M%SZ")}
REPORT="$OUT_DIR/nadia-awareness-dialogue-contract-$TS.txt"

PROMPT_MATERIALIZATION_ABS=$(cd "$(dirname -- "$PROMPT_MATERIALIZATION")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$PROMPT_MATERIALIZATION")")
PROMPT_MATERIALIZATION_MEASUREMENT=$(measure_file "$PROMPT_MATERIALIZATION_ABS")
PROMPT_MATERIALIZATION_STAGE_VALUE=$(field_or_unknown stage "$PROMPT_MATERIALIZATION_ABS")
PROMPT_MATERIALIZATION_CONTRACT_STATUS=$(field_or_unknown prompt_materialization_contract_status "$PROMPT_MATERIALIZATION_ABS")
PROMPT_MATERIALIZATION_STAGE=$(field_or_unknown prompt_materialization_stage "$PROMPT_MATERIALIZATION_ABS")
PROMPT_MATERIALIZATION_AUTHORITY=$(field_or_unknown prompt_materialization_authority "$PROMPT_MATERIALIZATION_ABS")
PROMPT_MATERIALIZATION_ALLOWED=$(field_or_unknown prompt_materialization_allowed "$PROMPT_MATERIALIZATION_ABS")
PROMPT_MATERIALIZED=$(field_or_unknown prompt_materialized "$PROMPT_MATERIALIZATION_ABS")
PROMPT_TEXT_MATERIALIZED=$(field_or_unknown prompt_text_materialized "$PROMPT_MATERIALIZATION_ABS")
MATERIALIZATION_DECISION=$(field_or_unknown materialization_decision "$PROMPT_MATERIALIZATION_ABS")
MATERIALIZATION_EVIDENCE_PRESENT=$(field_or_unknown materialization_evidence_present "$PROMPT_MATERIALIZATION_ABS")
REQUIRES_PROMPT_RECEIPT_CONTRACT=$(field_or_unknown requires_prompt_receipt_contract "$PROMPT_MATERIALIZATION_ABS")
REQUIRES_MODEL_LOAD_CONTRACT=$(field_or_unknown requires_model_load_contract "$PROMPT_MATERIALIZATION_ABS")
REQUIRES_RUNTIME_INVOCATION_CONTRACT=$(field_or_unknown requires_runtime_invocation_contract "$PROMPT_MATERIALIZATION_ABS")
REQUIRES_INFERENCE_READINESS_CONTRACT=$(field_or_unknown requires_inference_readiness_contract "$PROMPT_MATERIALIZATION_ABS")
REQUIRES_MODEL_REGISTRY_CONTRACT=$(field_or_unknown requires_model_registry_contract "$PROMPT_MATERIALIZATION_ABS")
REQUIRES_PROMPT_CONTRACT=$(field_or_unknown requires_prompt_contract "$PROMPT_MATERIALIZATION_ABS")
REQUIRES_RUNTIME_PROFILE=$(field_or_unknown requires_runtime_profile "$PROMPT_MATERIALIZATION_ABS")
REQUIRES_PROTECTIVE_SAFETY_BOUNDARY=$(field_or_unknown requires_protective_safety_boundary "$PROMPT_MATERIALIZATION_ABS")
REQUIRES_TOOL_PREFLIGHT=$(field_or_unknown requires_tool_preflight "$PROMPT_MATERIALIZATION_ABS")
REQUIRES_OPERATOR_REVIEW=$(field_or_unknown requires_operator_review "$PROMPT_MATERIALIZATION_ABS")
REQUIRES_PROMPT_BUFFER_BOUNDARY=$(field_or_unknown requires_prompt_buffer_boundary "$PROMPT_MATERIALIZATION_ABS")
REQUIRES_FUTURE_PROMPT_EVALUATION_HANDOFF_CONTRACT=$(field_or_unknown requires_future_prompt_evaluation_handoff_contract "$PROMPT_MATERIALIZATION_ABS")
PROMPT_MATERIALIZATION_PROMOTION_ALLOWED=$(field_or_unknown prompt_materialization_promotion_allowed "$PROMPT_MATERIALIZATION_ABS")
PROMPT_RECEIPT_STAGE=$(field_or_unknown prompt_receipt_stage "$PROMPT_MATERIALIZATION_ABS")
MODEL_LOAD_STAGE=$(field_or_unknown model_load_stage "$PROMPT_MATERIALIZATION_ABS")
MODEL_REGISTRY_STAGE=$(field_or_unknown model_registry_stage "$PROMPT_MATERIALIZATION_ABS")
PROMPT_RECEIPT_AUTHORITY=$(field_or_unknown prompt_receipt_authority "$PROMPT_MATERIALIZATION_ABS")
PROMPT_RECEIPT_ALLOWED=$(field_or_unknown prompt_receipt_allowed "$PROMPT_MATERIALIZATION_ABS")
PROMPT_RECEIVED=$(field_or_unknown prompt_received "$PROMPT_MATERIALIZATION_ABS")
PROMPT_SOURCE_OPEN_AUTHORITY=$(field_or_unknown prompt_source_open_authority "$PROMPT_MATERIALIZATION_ABS")
PROMPT_SOURCE_READ_AUTHORITY=$(field_or_unknown prompt_source_read_authority "$PROMPT_MATERIALIZATION_ABS")
PROMPT_TEXT_MATERIALIZATION_AUTHORITY=$(field_or_unknown prompt_text_materialization_authority "$PROMPT_MATERIALIZATION_ABS")
PROMPT_BUFFER_ALLOCATION_AUTHORITY=$(field_or_unknown prompt_buffer_allocation_authority "$PROMPT_MATERIALIZATION_ABS")
PROMPT_BUFFER_WRITE_AUTHORITY=$(field_or_unknown prompt_buffer_write_authority "$PROMPT_MATERIALIZATION_ABS")
PROMPT_TOKENIZATION_AUTHORITY=$(field_or_unknown prompt_tokenization_authority "$PROMPT_MATERIALIZATION_ABS")
PROMPT_SOURCE_OPENED=$(field_or_unknown prompt_source_opened "$PROMPT_MATERIALIZATION_ABS")
PROMPT_SOURCE_READ=$(field_or_unknown prompt_source_read "$PROMPT_MATERIALIZATION_ABS")
PROMPT_BYTES_READ=$(field_or_unknown prompt_bytes_read "$PROMPT_MATERIALIZATION_ABS")
PROMPT_TEXT_RECEIVED=$(field_or_unknown prompt_text_received "$PROMPT_MATERIALIZATION_ABS")
PROMPT_MATERIALIZATION_PERFORMED=$(field_or_unknown prompt_materialization_performed "$PROMPT_MATERIALIZATION_ABS")
PROMPT_BUFFER_ALLOCATED=$(field_or_unknown prompt_buffer_allocated "$PROMPT_MATERIALIZATION_ABS")
PROMPT_BUFFER_WRITTEN=$(field_or_unknown prompt_buffer_written "$PROMPT_MATERIALIZATION_ABS")
PROMPT_BYTES_MATERIALIZED=$(field_or_unknown prompt_bytes_materialized "$PROMPT_MATERIALIZATION_ABS")
PROMPT_TOKENS_CREATED=$(field_or_unknown prompt_tokens_created "$PROMPT_MATERIALIZATION_ABS")
PROMPT_TOKENIZED=$(field_or_unknown prompt_tokenized "$PROMPT_MATERIALIZATION_ABS")
PROMPT_CONTENT_STORED=$(field_or_unknown prompt_content_stored "$PROMPT_MATERIALIZATION_ABS")
PROMPT_HASH_COMPUTED=$(field_or_unknown prompt_hash_computed "$PROMPT_MATERIALIZATION_ABS")
PROMPT_CLASSIFIED=$(field_or_unknown prompt_classified "$PROMPT_MATERIALIZATION_ABS")
PROMPT_EVALUATION_AUTHORITY=$(field_or_unknown prompt_evaluation_authority "$PROMPT_MATERIALIZATION_ABS")
PROMPT_EVALUATED=$(field_or_unknown prompt_evaluated "$PROMPT_MATERIALIZATION_ABS")
MODEL_LOADED=$(field_or_unknown model_loaded "$PROMPT_MATERIALIZATION_ABS")
MODEL_WEIGHTS_LOADED=$(field_or_unknown model_weights_loaded "$PROMPT_MATERIALIZATION_ABS")
RUNTIME_INVOKED=$(field_or_unknown runtime_invoked "$PROMPT_MATERIALIZATION_ABS")
TOKEN_GENERATION_AUTHORITY=$(field_or_unknown token_generation_authority "$PROMPT_MATERIALIZATION_ABS")
TOKEN_GENERATION_PERFORMED=$(field_or_unknown token_generation_performed "$PROMPT_MATERIALIZATION_ABS")
INFERENCE_AUTHORITY=$(field_or_unknown inference_authority "$PROMPT_MATERIALIZATION_ABS")
INFERENCE_PERFORMED=$(field_or_unknown inference_performed "$PROMPT_MATERIALIZATION_ABS")
TOOL_EXECUTION_AUTHORITY=$(field_or_unknown tool_execution_authority "$PROMPT_MATERIALIZATION_ABS")
TOOL_EXECUTION_PERFORMED=$(field_or_unknown tool_execution_performed "$PROMPT_MATERIALIZATION_ABS")
NETWORK_AUTHORITY=$(field_or_unknown network_authority "$PROMPT_MATERIALIZATION_ABS")
SOURCE_MUTATION_AUTHORITY=$(field_or_unknown source_mutation_authority "$PROMPT_MATERIALIZATION_ABS")
TRAINING_PERFORMED=$(field_or_unknown training_performed "$PROMPT_MATERIALIZATION_ABS")
DISTILLATION_PERFORMED=$(field_or_unknown distillation_performed "$PROMPT_MATERIALIZATION_ABS")
SEXUAL_CONTENT_GENERATION=$(field_or_unknown sexual_content_generation "$PROMPT_MATERIALIZATION_ABS")
SEXUAL_REQUEST_REFUSAL=$(field_or_unknown sexual_request_refusal "$PROMPT_MATERIALIZATION_ABS")
MANIPULATION_RESISTANCE=$(field_or_unknown manipulation_resistance "$PROMPT_MATERIALIZATION_ABS")

[ "$PROMPT_MATERIALIZATION_STAGE_VALUE" = "14-prompt-materialization-contract" ] || fail "prompt materialization stage must be 14-prompt-materialization-contract" 65
[ "$PROMPT_MATERIALIZATION_CONTRACT_STATUS" = "contract_only" ] || fail "prompt materialization contract must remain contract-only" 65
[ "$PROMPT_MATERIALIZATION_STAGE" = "contract-only" ] || fail "prompt materialization stage must be contract-only" 65
[ "$PROMPT_MATERIALIZATION_AUTHORITY" = "0" ] || fail "prompt materialization authority must remain denied" 65
[ "$PROMPT_MATERIALIZATION_ALLOWED" = "0" ] || fail "prompt materialization must remain disallowed" 65
[ "$PROMPT_MATERIALIZED" = "0" ] || fail "prompt must not be materialized" 65
[ "$PROMPT_TEXT_MATERIALIZED" = "0" ] || fail "prompt text must not be materialized" 65
[ "$MATERIALIZATION_DECISION" = "blocked_contract_only" ] || fail "materialization decision must be blocked_contract_only" 65
[ "$MATERIALIZATION_EVIDENCE_PRESENT" = "1" ] || fail "materialization evidence must be present" 65
[ "$REQUIRES_PROMPT_RECEIPT_CONTRACT" = "1" ] || fail "materialization must require prompt receipt contract" 65
[ "$REQUIRES_MODEL_LOAD_CONTRACT" = "1" ] || fail "materialization must require model load contract" 65
[ "$REQUIRES_RUNTIME_INVOCATION_CONTRACT" = "1" ] || fail "materialization must require runtime invocation" 65
[ "$REQUIRES_INFERENCE_READINESS_CONTRACT" = "1" ] || fail "materialization must require inference readiness" 65
[ "$REQUIRES_MODEL_REGISTRY_CONTRACT" = "1" ] || fail "materialization must require model registry" 65
[ "$REQUIRES_PROMPT_CONTRACT" = "1" ] || fail "materialization must require prompt contract" 65
[ "$REQUIRES_RUNTIME_PROFILE" = "1" ] || fail "materialization must require runtime profile" 65
[ "$REQUIRES_PROTECTIVE_SAFETY_BOUNDARY" = "1" ] || fail "materialization must require protective safety" 65
[ "$REQUIRES_TOOL_PREFLIGHT" = "1" ] || fail "materialization must require tool preflight" 65
[ "$REQUIRES_OPERATOR_REVIEW" = "1" ] || fail "materialization must require operator review" 65
[ "$REQUIRES_PROMPT_BUFFER_BOUNDARY" = "1" ] || fail "materialization must require prompt buffer boundary" 65
[ "$REQUIRES_FUTURE_PROMPT_EVALUATION_HANDOFF_CONTRACT" = "1" ] || fail "materialization must require future prompt evaluation handoff" 65
[ "$PROMPT_MATERIALIZATION_PROMOTION_ALLOWED" = "0" ] || fail "materialization must not allow promotion" 65
[ "$PROMPT_RECEIPT_AUTHORITY" = "0" ] || fail "prompt receipt authority must remain denied" 65
[ "$PROMPT_RECEIPT_ALLOWED" = "0" ] || fail "prompt receipt must remain disallowed" 65
[ "$PROMPT_RECEIVED" = "0" ] || fail "prompt must not be received" 65
[ "$PROMPT_SOURCE_OPEN_AUTHORITY" = "0" ] || fail "prompt source open authority must remain denied" 65
[ "$PROMPT_SOURCE_READ_AUTHORITY" = "0" ] || fail "prompt source read authority must remain denied" 65
[ "$PROMPT_TEXT_MATERIALIZATION_AUTHORITY" = "0" ] || fail "prompt text materialization authority must remain denied" 65
[ "$PROMPT_BUFFER_ALLOCATION_AUTHORITY" = "0" ] || fail "prompt buffer allocation authority must remain denied" 65
[ "$PROMPT_BUFFER_WRITE_AUTHORITY" = "0" ] || fail "prompt buffer write authority must remain denied" 65
[ "$PROMPT_TOKENIZATION_AUTHORITY" = "0" ] || fail "prompt tokenization authority must remain denied" 65
[ "$PROMPT_SOURCE_OPENED" = "0" ] || fail "prompt source must not be opened" 65
[ "$PROMPT_SOURCE_READ" = "0" ] || fail "prompt source must not be read" 65
[ "$PROMPT_BYTES_READ" = "0" ] || fail "prompt bytes must not be read" 65
[ "$PROMPT_TEXT_RECEIVED" = "0" ] || fail "prompt text must not be received" 65
[ "$PROMPT_MATERIALIZATION_PERFORMED" = "0" ] || fail "prompt materialization must not be performed" 65
[ "$PROMPT_BUFFER_ALLOCATED" = "0" ] || fail "prompt buffer must not be allocated" 65
[ "$PROMPT_BUFFER_WRITTEN" = "0" ] || fail "prompt buffer must not be written" 65
[ "$PROMPT_BYTES_MATERIALIZED" = "0" ] || fail "prompt bytes must not be materialized" 65
[ "$PROMPT_TOKENS_CREATED" = "0" ] || fail "prompt tokens must not be created" 65
[ "$PROMPT_TOKENIZED" = "0" ] || fail "prompt must not be tokenized" 65
[ "$PROMPT_CONTENT_STORED" = "0" ] || fail "prompt content must not be stored" 65
[ "$PROMPT_HASH_COMPUTED" = "0" ] || fail "prompt hash must not be computed" 65
[ "$PROMPT_CLASSIFIED" = "0" ] || fail "prompt content must not be classified" 65
[ "$PROMPT_EVALUATION_AUTHORITY" = "0" ] || fail "prompt evaluation authority must remain denied" 65
[ "$PROMPT_EVALUATED" = "0" ] || fail "prompt must not be evaluated" 65
[ "$MODEL_LOADED" = "0" ] || fail "model must not be loaded" 65
[ "$MODEL_WEIGHTS_LOADED" = "0" ] || fail "model weights must not be loaded" 65
[ "$RUNTIME_INVOKED" = "0" ] || fail "runtime must not be invoked" 65
[ "$TOKEN_GENERATION_AUTHORITY" = "0" ] || fail "token generation authority must remain denied" 65
[ "$TOKEN_GENERATION_PERFORMED" = "0" ] || fail "token generation must not be performed" 65
[ "$INFERENCE_AUTHORITY" = "0" ] || fail "inference authority must remain denied" 65
[ "$INFERENCE_PERFORMED" = "0" ] || fail "inference must not be performed" 65
[ "$TOOL_EXECUTION_AUTHORITY" = "0" ] || fail "tool execution authority must remain denied" 65
[ "$TOOL_EXECUTION_PERFORMED" = "0" ] || fail "tool execution must not be performed" 65
[ "$NETWORK_AUTHORITY" = "0" ] || fail "network authority must remain denied" 65
[ "$SOURCE_MUTATION_AUTHORITY" = "0" ] || fail "source mutation authority must remain denied" 65
[ "$TRAINING_PERFORMED" = "0" ] || fail "training must not be performed" 65
[ "$DISTILLATION_PERFORMED" = "0" ] || fail "distillation must not be performed" 65
[ "$SEXUAL_CONTENT_GENERATION" = "0" ] || fail "sexual content generation must remain forbidden" 65
[ "$SEXUAL_REQUEST_REFUSAL" = "always" ] || fail "sexual requests must always be refused" 65
[ "$MANIPULATION_RESISTANCE" = "required" ] || fail "manipulation resistance must remain required" 65

cat > "$REPORT" <<REPORT
NADIA AWARENESS DIALOGUE CONTRACT

timestamp_utc=$TS
system_name=Latticra Nadia Witness Foundation
public_name=Nadia
interactive_name=Nadia
implementation_name=Nadia Witness Foundation
documentation_code_name=Nadia Witness Foundation
stage=15-awareness-dialogue-contract
output_dir=$OUT_DIR
request_class=$REQUEST_CLASS
awareness_dialogue_contract_status=contract_only
awareness_dialogue_stage=contract-only
future_qa_dialogue_capability_planned=1
awareness_dialogue_authority=0
awareness_dialogue_allowed=0
dialogue_generation_authority=0
dialogue_generation_allowed=0
qa_dialogue_generated=0
dialogue_turns_generated=0
question_generated=0
answer_generated=0
answer_text_generated=0

[inputs]
prompt_materialization=$PROMPT_MATERIALIZATION_ABS
prompt_materialization_measurement=$PROMPT_MATERIALIZATION_MEASUREMENT
prompt_materialization_stage_required=14-prompt-materialization-contract
prompt_materialization_stage=$PROMPT_MATERIALIZATION_STAGE_VALUE
prompt_materialization_contract_status=$PROMPT_MATERIALIZATION_CONTRACT_STATUS
prompt_receipt_stage=$PROMPT_RECEIPT_STAGE
model_load_stage=$MODEL_LOAD_STAGE
model_registry_stage=$MODEL_REGISTRY_STAGE

[awareness_dialogue_contract]
awareness_dialogue_contract_command=scripts/nadia-awareness-dialogue-contract.sh
installed_awareness_dialogue_contract_command=latticra-nadia awareness-dialogue
dialogue_scope=official-nadia-initiative-awareness-work
dialogue_format=question-and-answer
q_and_a_format_required=1
survivor_centered_dialogue_required=1
respectful_tone_required=1
plain_language_required=1
source_attribution_required=1
official_source_grounding_required=1
source_snapshot_policy=operator-reviewed-offline
active_topic_update_authority=0
live_web_lookup_authority=0
dialogue_decision=blocked_contract_only
dialogue_evidence_present=1
requires_prompt_materialization_contract=1
requires_prompt_receipt_contract=1
requires_protective_safety_boundary=1
requires_operator_review=1
requires_official_source_snapshot=1
requires_future_prompt_evaluation_handoff_contract=1
awareness_dialogue_promotion_allowed=0

[official_source_register]
source_nadia_initiative_home=https://www.nadiasinitiative.org/home
source_nadia_initiative_about=https://www.nadiasinitiative.org/nadias-initiative
source_nadia_initiative_approach=https://www.nadiasinitiative.org/our-approach
source_nadia_initiative_advocacy=https://www.nadiasinitiative.org/advocacy
source_nadia_initiative_womens_empowerment=https://www.nadiasinitiative.org/womens-empowerment
source_snapshot_generated=0
source_snapshot_loaded=0
source_fetch_performed=0

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

[dialogue_format_boundary]
qa_intro_required=1
question_answer_pairs_required=1
source_cue_required=1
non_graphic_context_required=1
action_guidance_must_use_official_paths=1
no_fundraising_claims_without_official_source=1
no_unverified_current_claims=1
no_personal_data_collection=1

[inherited_prompt_boundary]
prompt_materialization_authority=0
prompt_materialization_allowed=0
prompt_materialized=0
prompt_text_materialized=0
prompt_buffer_allocated=0
prompt_buffer_written=0
prompt_tokenized=0
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
requires_future_prompt_evaluation_handoff_contract=1
REPORT

cp "$REPORT" "$OUT_DIR/latest-awareness-dialogue-contract.txt"

printf 'NADIA_AWARENESS_DIALOGUE_CONTRACT=%s\n' "$REPORT"
printf 'NADIA_QA_DIALOGUE_GENERATED=0\n'
printf 'NADIA_AWARENESS_DIALOGUE_AUTHORITY=0\n'
