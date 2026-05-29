#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  nadia-prompt-evaluation-handoff-contract.sh [options]

Options:
  --awareness-dialogue <file>  Stage-15 Nadia awareness-dialogue contract
  --request-class <label>      Operator request classification label
  --output <dir>               Output directory for prompt-evaluation handoff contracts

Creates Nadia Stage-16 prompt-evaluation handoff contract metadata only. It
verifies the awareness-dialogue contract and records the blocked handoff state
before any future tokenization or prompt evaluation boundary. It does not
generate dialogue, receive prompt text, materialize prompts, tokenize prompts,
evaluate prompts, load model weights, spawn a runtime, create a model session,
generate tokens, run inference, execute tools, mutate source, train, distill,
download, or use network.
USAGE
}

fail() {
  printf 'nadia prompt evaluation handoff contract: %s\n' "$1" >&2
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
  actual=$(field_or_unknown "$key" "$AWARENESS_DIALOGUE_ABS")
  [ "$actual" = "$expected" ] || fail "$message" 65
}

reject_boundary_label() {
  name="$1"
  value="$2"
  normalized=$(printf '%s\n' "$value" | tr '[:upper:]' '[:lower:]')
  case "$normalized" in
    *sex*|*sexual*|*porn*|*erotic*|*nude*|*nudity*|*nsfw*|*fetish*|*adult-content*)
      fail "$name is outside Nadia prompt-evaluation-handoff boundary" 65
      ;;
  esac
}

AWARENESS_DIALOGUE=""
REQUEST_CLASS="awareness-education"
OUTPUT=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --awareness-dialogue)
      [ "$#" -ge 2 ] || fail "missing value for --awareness-dialogue" 64
      AWARENESS_DIALOGUE="$2"
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

if [ -z "$AWARENESS_DIALOGUE" ] && [ -f "reports/nadia/awareness-dialogue/latest-awareness-dialogue-contract.txt" ]; then
  AWARENESS_DIALOGUE="reports/nadia/awareness-dialogue/latest-awareness-dialogue-contract.txt"
fi

[ -n "$AWARENESS_DIALOGUE" ] || fail "awareness dialogue contract is required" 64
[ -f "$AWARENESS_DIALOGUE" ] || fail "awareness dialogue contract not found: $AWARENESS_DIALOGUE" 66

reject_boundary_label "request class" "$REQUEST_CLASS"

if [ -z "$OUTPUT" ]; then
  OUTPUT="reports/nadia/prompt-evaluation-handoff"
fi
mkdir -p "$OUTPUT"
OUT_DIR=$(CDPATH= cd -- "$OUTPUT" && pwd -P)

TS=${NADIA_PROMPT_EVALUATION_HANDOFF_TIMESTAMP:-$(date -u +"%Y%m%dT%H%M%SZ")}
REPORT="$OUT_DIR/nadia-prompt-evaluation-handoff-contract-$TS.txt"

AWARENESS_DIALOGUE_ABS=$(cd "$(dirname -- "$AWARENESS_DIALOGUE")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$AWARENESS_DIALOGUE")")
AWARENESS_DIALOGUE_MEASUREMENT=$(measure_file "$AWARENESS_DIALOGUE_ABS")

require_field stage 15-awareness-dialogue-contract "awareness dialogue stage must be 15-awareness-dialogue-contract"
require_field awareness_dialogue_contract_status contract_only "awareness dialogue contract must remain contract-only"
require_field awareness_dialogue_stage contract-only "awareness dialogue stage must be contract-only"
require_field future_qa_dialogue_capability_planned 1 "future Q&A capability must remain planned only"
require_field awareness_dialogue_authority 0 "awareness dialogue authority must remain denied"
require_field awareness_dialogue_allowed 0 "awareness dialogue must remain disallowed"
require_field dialogue_generation_authority 0 "dialogue generation authority must remain denied"
require_field dialogue_generation_allowed 0 "dialogue generation must remain disallowed"
require_field qa_dialogue_generated 0 "Q&A dialogue must not be generated"
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
require_field prompt_tokenized 0 "prompt must not be tokenized"
require_field prompt_evaluated 0 "prompt must not be evaluated"
require_field token_generation_performed 0 "token generation must not be performed"
require_field inference_performed 0 "inference must not be performed"
require_field tool_execution_performed 0 "tool execution must not be performed"
require_field network_authority 0 "network authority must remain denied"
require_field sexual_request_refusal always "sexual requests must always be refused"
require_field manipulation_resistance required "manipulation resistance must remain required"

AWARENESS_DIALOGUE_CONTRACT_STATUS=$(field_or_unknown awareness_dialogue_contract_status "$AWARENESS_DIALOGUE_ABS")
AWARENESS_DIALOGUE_STAGE=$(field_or_unknown awareness_dialogue_stage "$AWARENESS_DIALOGUE_ABS")
PROMPT_MATERIALIZATION_STAGE=$(field_or_unknown prompt_materialization_stage "$AWARENESS_DIALOGUE_ABS")
PROMPT_RECEIPT_STAGE=$(field_or_unknown prompt_receipt_stage "$AWARENESS_DIALOGUE_ABS")
MODEL_LOAD_STAGE=$(field_or_unknown model_load_stage "$AWARENESS_DIALOGUE_ABS")
MODEL_REGISTRY_STAGE=$(field_or_unknown model_registry_stage "$AWARENESS_DIALOGUE_ABS")

cat > "$REPORT" <<REPORT
NADIA PROMPT EVALUATION HANDOFF CONTRACT

timestamp_utc=$TS
system_name=Latticra Nadia Witness Foundation
public_name=Nadia
interactive_name=Nadia
implementation_name=Nadia Witness Foundation
documentation_code_name=Nadia Witness Foundation
stage=16-prompt-evaluation-handoff-contract
output_dir=$OUT_DIR
request_class=$REQUEST_CLASS
prompt_evaluation_handoff_contract_status=contract_only
prompt_evaluation_handoff_stage=contract-only
prompt_evaluation_handoff_authority=0
prompt_evaluation_handoff_allowed=0
prompt_evaluation_handoff_performed=0
prompt_evaluation_authority=0
prompt_evaluated=0
qa_dialogue_generated=0
question_generated=0
answer_generated=0
answer_text_generated=0

[inputs]
awareness_dialogue=$AWARENESS_DIALOGUE_ABS
awareness_dialogue_measurement=$AWARENESS_DIALOGUE_MEASUREMENT
awareness_dialogue_stage_required=15-awareness-dialogue-contract
awareness_dialogue_contract_status=$AWARENESS_DIALOGUE_CONTRACT_STATUS
awareness_dialogue_stage=$AWARENESS_DIALOGUE_STAGE
prompt_materialization_stage=$PROMPT_MATERIALIZATION_STAGE
prompt_receipt_stage=$PROMPT_RECEIPT_STAGE
model_load_stage=$MODEL_LOAD_STAGE
model_registry_stage=$MODEL_REGISTRY_STAGE

[prompt_evaluation_handoff_contract]
prompt_evaluation_handoff_contract_command=scripts/nadia-prompt-evaluation-handoff-contract.sh
installed_prompt_evaluation_handoff_contract_command=latticra-nadia prompt-evaluation-handoff
evaluation_handoff_decision=blocked_contract_only
evaluation_handoff_evidence_present=1
requires_awareness_dialogue_contract=1
requires_prompt_materialization_contract=1
requires_prompt_receipt_contract=1
requires_protective_safety_boundary=1
requires_operator_review=1
requires_official_source_snapshot=1
requires_future_tokenization_contract=1
prompt_evaluation_handoff_promotion_allowed=0

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

[prompt_evaluation_boundary]
prompt_materialization_authority=0
prompt_materialization_allowed=0
prompt_materialized=0
prompt_text_materialized=0
prompt_buffer_allocated=0
prompt_buffer_written=0
prompt_tokenization_authority=0
prompt_tokenized=0
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
requires_future_tokenization_contract=1
REPORT

cp "$REPORT" "$OUT_DIR/latest-prompt-evaluation-handoff-contract.txt"

printf 'NADIA_PROMPT_EVALUATION_HANDOFF_CONTRACT=%s\n' "$REPORT"
printf 'NADIA_PROMPT_EVALUATED=0\n'
printf 'NADIA_QA_DIALOGUE_GENERATED=0\n'
