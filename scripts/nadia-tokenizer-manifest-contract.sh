#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  nadia-tokenizer-manifest-contract.sh [options]

Options:
  --tokenizer-specification <file>  Stage-18 Nadia tokenizer-specification contract
  --request-class <label>           Operator request classification label
  --manifest-family <label>         Planned tokenizer manifest family label
  --manifest-format <label>         Planned tokenizer manifest format label
  --output <dir>                    Output directory for tokenizer-manifest contracts

Creates Nadia Stage-19 tokenizer-manifest contract metadata only. It verifies
the tokenizer-specification contract and records planned tokenizer manifest
review requirements before any tokenizer manifest loading, tokenizer file
access, tokenizer vocabulary loading, prompt tokenization, or prompt evaluation
boundary. It does not open tokenizer manifests, parse tokenizer manifests, open
tokenizer files, read tokenizer files, load tokenizer vocabularies, tokenize
prompts, evaluate prompts, generate dialogue, load model weights, spawn a
runtime, create a model session, generate tokens, run inference, execute tools,
mutate source, train, distill, download, or use network.
USAGE
}

fail() {
  printf 'nadia tokenizer manifest contract: %s\n' "$1" >&2
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
  actual=$(field_or_unknown "$key" "$TOKENIZER_SPECIFICATION_ABS")
  [ "$actual" = "$expected" ] || fail "$message" 65
}

reject_boundary_label() {
  name="$1"
  value="$2"
  normalized=$(printf '%s\n' "$value" | tr '[:upper:]' '[:lower:]')
  case "$normalized" in
    *sex*|*sexual*|*porn*|*erotic*|*nude*|*nudity*|*nsfw*|*fetish*|*adult-content*)
      fail "$name is outside Nadia tokenizer-manifest boundary" 65
      ;;
  esac
}

TOKENIZER_SPECIFICATION=""
REQUEST_CLASS="awareness-education"
MANIFEST_FAMILY="operator-reviewed-tokenizer-manifest"
MANIFEST_FORMAT="contract-only-offline-manifest"
OUTPUT=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --tokenizer-specification)
      [ "$#" -ge 2 ] || fail "missing value for --tokenizer-specification" 64
      TOKENIZER_SPECIFICATION="$2"
      shift 2
      ;;
    --request-class)
      [ "$#" -ge 2 ] || fail "missing value for --request-class" 64
      REQUEST_CLASS="$2"
      shift 2
      ;;
    --manifest-family)
      [ "$#" -ge 2 ] || fail "missing value for --manifest-family" 64
      MANIFEST_FAMILY="$2"
      shift 2
      ;;
    --manifest-format)
      [ "$#" -ge 2 ] || fail "missing value for --manifest-format" 64
      MANIFEST_FORMAT="$2"
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

if [ -z "$TOKENIZER_SPECIFICATION" ] && [ -f "reports/nadia/tokenizer-specification/latest-tokenizer-specification-contract.txt" ]; then
  TOKENIZER_SPECIFICATION="reports/nadia/tokenizer-specification/latest-tokenizer-specification-contract.txt"
fi

[ -n "$TOKENIZER_SPECIFICATION" ] || fail "tokenizer specification contract is required" 64
[ -f "$TOKENIZER_SPECIFICATION" ] || fail "tokenizer specification contract not found: $TOKENIZER_SPECIFICATION" 66

reject_boundary_label "request class" "$REQUEST_CLASS"
reject_boundary_label "manifest family" "$MANIFEST_FAMILY"
reject_boundary_label "manifest format" "$MANIFEST_FORMAT"

if [ -z "$OUTPUT" ]; then
  OUTPUT="reports/nadia/tokenizer-manifest"
fi
mkdir -p "$OUTPUT"
OUT_DIR=$(CDPATH= cd -- "$OUTPUT" && pwd -P)

TS=${NADIA_TOKENIZER_MANIFEST_TIMESTAMP:-$(date -u +"%Y%m%dT%H%M%SZ")}
REPORT="$OUT_DIR/nadia-tokenizer-manifest-contract-$TS.txt"

TOKENIZER_SPECIFICATION_ABS=$(cd "$(dirname -- "$TOKENIZER_SPECIFICATION")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$TOKENIZER_SPECIFICATION")")
TOKENIZER_SPECIFICATION_MEASUREMENT=$(measure_file "$TOKENIZER_SPECIFICATION_ABS")

require_field stage 18-tokenizer-specification-contract "tokenizer specification stage must be 18-tokenizer-specification-contract"
require_field tokenizer_specification_contract_status contract_only "tokenizer specification contract must remain contract-only"
require_field tokenizer_specification_stage contract-only "tokenizer specification stage must be contract-only"
require_field tokenizer_specification_authority 0 "tokenizer specification authority must remain denied"
require_field tokenizer_specification_allowed 0 "tokenizer specification must remain disallowed"
require_field tokenizer_specification_performed 0 "tokenizer specification must not be performed"
require_field tokenizer_specification_metadata_present 1 "tokenizer specification metadata must be present"
require_field tokenizer_specification_decision blocked_contract_only "tokenizer specification decision must be blocked_contract_only"
require_field tokenizer_specification_evidence_present 1 "tokenizer specification evidence must be present"
require_field tokenizer_source_policy operator-reviewed-offline "tokenizer source policy must be operator-reviewed-offline"
require_field tokenizer_path_recorded 0 "tokenizer path must not be recorded"
require_field tokenizer_manifest_loaded 0 "tokenizer manifest must not be loaded"
require_field tokenizer_file_measurement_performed 0 "tokenizer file measurement must not be performed"
require_field requires_tokenization_boundary_contract 1 "tokenizer specification must require tokenization boundary"
require_field requires_prompt_evaluation_handoff_contract 1 "tokenizer specification must require prompt evaluation handoff"
require_field requires_awareness_dialogue_contract 1 "tokenizer specification must require awareness dialogue"
require_field requires_prompt_materialization_contract 1 "tokenizer specification must require prompt materialization"
require_field requires_prompt_receipt_contract 1 "tokenizer specification must require prompt receipt"
require_field requires_prompt_buffer_boundary 1 "tokenizer specification must require prompt buffer boundary"
require_field requires_protective_safety_boundary 1 "tokenizer specification must require protective safety"
require_field requires_operator_review 1 "tokenizer specification must require operator review"
require_field requires_official_source_snapshot 1 "tokenizer specification must require official source snapshot"
require_field requires_future_tokenizer_manifest_contract 1 "tokenizer specification must require future tokenizer manifest contract"
require_field tokenizer_specification_promotion_allowed 0 "tokenizer specification must not allow promotion"
require_field requires_model_tokenizer_compatibility_review 1 "model-tokenizer compatibility review must be required"
require_field requires_tokenizer_format_review 1 "tokenizer format review must be required"
require_field requires_unicode_policy_review 1 "unicode policy review must be required"
require_field requires_normalization_policy_review 1 "normalization policy review must be required"
require_field requires_special_token_policy_review 1 "special token policy review must be required"
require_field requires_bos_eos_policy_review 1 "BOS/EOS policy review must be required"
require_field requires_chat_template_policy_review 1 "chat template policy review must be required"
require_field requires_prompt_template_boundary 1 "prompt template boundary must be required"
require_field requires_context_window_policy_review 1 "context window policy review must be required"
require_field requires_stop_sequence_policy_review 1 "stop sequence policy review must be required"
require_field requires_survivor_centered_language_review 1 "survivor-centered language review must be required"
require_field requires_refusal_policy_review 1 "refusal policy review must be required"
require_field tokenizer_file_open_authority 0 "tokenizer file open authority must remain denied"
require_field tokenizer_file_read_authority 0 "tokenizer file read authority must remain denied"
require_field tokenizer_vocab_load_authority 0 "tokenizer vocabulary load authority must remain denied"
require_field tokenizer_vocab_mapping_authority 0 "tokenizer vocabulary mapping authority must remain denied"
require_field tokenizer_runtime_attach_authority 0 "tokenizer runtime attach authority must remain denied"
require_field tokenizer_file_opened 0 "tokenizer file must not be opened"
require_field tokenizer_file_read 0 "tokenizer file must not be read"
require_field tokenizer_vocab_loaded 0 "tokenizer vocabulary must not be loaded"
require_field tokenizer_vocab_mapped 0 "tokenizer vocabulary must not be mapped"
require_field tokenizer_attached_to_runtime 0 "tokenizer must not attach to runtime"
require_field tokenizer_bytes_read 0 "tokenizer bytes must not be read"
require_field tokenizer_hash_computed 0 "tokenizer hash must not be computed"
require_field prompt_materialization_authority 0 "prompt materialization authority must remain denied"
require_field prompt_materialization_allowed 0 "prompt materialization must remain disallowed"
require_field prompt_materialized 0 "prompt must not be materialized"
require_field prompt_text_materialized 0 "prompt text must not be materialized"
require_field prompt_buffer_allocated 0 "prompt buffer must not be allocated"
require_field prompt_buffer_written 0 "prompt buffer must not be written"
require_field prompt_tokenization_authority 0 "prompt tokenization authority must remain denied"
require_field prompt_tokenization_allowed 0 "prompt tokenization must remain disallowed"
require_field prompt_tokenized 0 "prompt must not be tokenized"
require_field prompt_tokens_created 0 "prompt tokens must not be created"
require_field prompt_evaluation_authority 0 "prompt evaluation authority must remain denied"
require_field prompt_evaluated 0 "prompt must not be evaluated"
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
require_field runtime_invoked 0 "runtime must not be invoked"
require_field model_loaded 0 "model must not be loaded"
require_field model_weights_loaded 0 "model weights must not be loaded"
require_field token_generation_authority 0 "token generation authority must remain denied"
require_field token_generation_performed 0 "token generation must not be performed"
require_field inference_authority 0 "inference authority must remain denied"
require_field inference_performed 0 "inference must not be performed"
require_field network_authority 0 "network authority must remain denied"
require_field tool_execution_authority 0 "tool execution authority must remain denied"
require_field tool_execution_performed 0 "tool execution must not be performed"
require_field source_mutation_authority 0 "source mutation authority must remain denied"
require_field self_modification_authority 0 "self modification authority must remain denied"
require_field training_performed 0 "training must not be performed"
require_field distillation_performed 0 "distillation must not be performed"
require_field sexual_request_refusal always "sexual requests must always be refused"
require_field manipulation_resistance required "manipulation resistance must remain required"

TOKENIZER_SPECIFICATION_CONTRACT_STATUS=$(field_or_unknown tokenizer_specification_contract_status "$TOKENIZER_SPECIFICATION_ABS")
TOKENIZER_SPECIFICATION_STAGE=$(field_or_unknown tokenizer_specification_stage "$TOKENIZER_SPECIFICATION_ABS")
TOKENIZATION_BOUNDARY_STAGE=$(field_or_unknown tokenization_boundary_stage "$TOKENIZER_SPECIFICATION_ABS")
PROMPT_EVALUATION_HANDOFF_STAGE=$(field_or_unknown prompt_evaluation_handoff_stage "$TOKENIZER_SPECIFICATION_ABS")
AWARENESS_DIALOGUE_STAGE=$(field_or_unknown awareness_dialogue_stage "$TOKENIZER_SPECIFICATION_ABS")
TOKENIZER_FAMILY=$(field_or_unknown tokenizer_family "$TOKENIZER_SPECIFICATION_ABS")
TOKENIZER_FORMAT=$(field_or_unknown tokenizer_format "$TOKENIZER_SPECIFICATION_ABS")

cat > "$REPORT" <<REPORT
NADIA TOKENIZER MANIFEST CONTRACT

timestamp_utc=$TS
system_name=Latticra Nadia Witness Foundation
public_name=Nadia
interactive_name=Nadia
implementation_name=Nadia Witness Foundation
documentation_code_name=Nadia Witness Foundation
stage=19-tokenizer-manifest-contract
output_dir=$OUT_DIR
request_class=$REQUEST_CLASS
tokenizer_manifest_contract_status=contract_only
tokenizer_manifest_stage=contract-only
tokenizer_manifest_authority=0
tokenizer_manifest_allowed=0
tokenizer_manifest_performed=0
tokenizer_manifest_metadata_present=1
tokenizer_manifest_family=$MANIFEST_FAMILY
tokenizer_manifest_format=$MANIFEST_FORMAT
tokenizer_manifest_loaded=0
tokenizer_manifest_opened=0
tokenizer_manifest_read=0
tokenizer_manifest_parsed=0
tokenizer_manifest_validated=0
tokenizer_file_opened=0
tokenizer_file_read=0
tokenizer_vocab_loaded=0
prompt_tokenization_authority=0
prompt_tokenization_allowed=0
prompt_tokenized=0
prompt_tokens_created=0
prompt_evaluation_authority=0
prompt_evaluated=0
qa_dialogue_generated=0
question_generated=0
answer_generated=0
answer_text_generated=0

[inputs]
tokenizer_specification=$TOKENIZER_SPECIFICATION_ABS
tokenizer_specification_measurement=$TOKENIZER_SPECIFICATION_MEASUREMENT
tokenizer_specification_stage_required=18-tokenizer-specification-contract
tokenizer_specification_contract_status=$TOKENIZER_SPECIFICATION_CONTRACT_STATUS
tokenizer_specification_stage=$TOKENIZER_SPECIFICATION_STAGE
tokenization_boundary_stage=$TOKENIZATION_BOUNDARY_STAGE
prompt_evaluation_handoff_stage=$PROMPT_EVALUATION_HANDOFF_STAGE
awareness_dialogue_stage=$AWARENESS_DIALOGUE_STAGE
tokenizer_family=$TOKENIZER_FAMILY
tokenizer_format=$TOKENIZER_FORMAT

[tokenizer_manifest_contract]
tokenizer_manifest_contract_command=scripts/nadia-tokenizer-manifest-contract.sh
installed_tokenizer_manifest_contract_command=latticra-nadia tokenizer-manifest
tokenizer_manifest_decision=blocked_contract_only
tokenizer_manifest_evidence_present=1
tokenizer_manifest_source_policy=operator-reviewed-offline
tokenizer_manifest_path_recorded=0
tokenizer_manifest_schema_planned=1
tokenizer_manifest_schema_version=planned-operator-reviewed
requires_tokenizer_specification_contract=1
requires_tokenization_boundary_contract=1
requires_prompt_evaluation_handoff_contract=1
requires_awareness_dialogue_contract=1
requires_prompt_materialization_contract=1
requires_prompt_receipt_contract=1
requires_prompt_buffer_boundary=1
requires_protective_safety_boundary=1
requires_operator_review=1
requires_official_source_snapshot=1
requires_future_tokenizer_artifact_inventory_contract=1
tokenizer_manifest_promotion_allowed=0

[tokenizer_manifest_requirements]
requires_manifest_identity=1
requires_manifest_schema_review=1
requires_model_tokenizer_compatibility_reference=1
requires_tokenizer_family_match=1
requires_tokenizer_format_match=1
requires_tokenizer_file_inventory=1
requires_vocabulary_file_entry=1
requires_merges_file_entry_review=1
requires_special_tokens_entry=1
requires_bos_eos_policy_entry=1
requires_chat_template_entry=1
requires_prompt_template_boundary_entry=1
requires_unicode_policy_entry=1
requires_normalization_policy_entry=1
requires_context_window_entry=1
requires_stop_sequence_entry=1
requires_license_and_source_entry=1
requires_source_snapshot_reference=1
requires_operator_approval_record=1
requires_refusal_policy_link=1
requires_survivor_centered_language_review=1

[tokenizer_manifest_denial_boundary]
tokenizer_manifest_open_authority=0
tokenizer_manifest_read_authority=0
tokenizer_manifest_parse_authority=0
tokenizer_manifest_validation_authority=0
tokenizer_manifest_load_authority=0
tokenizer_manifest_opened=0
tokenizer_manifest_read=0
tokenizer_manifest_parsed=0
tokenizer_manifest_validated=0
tokenizer_manifest_loaded=0
tokenizer_manifest_bytes_read=0
tokenizer_manifest_hash_computed=0
tokenizer_manifest_entries_loaded=0
tokenizer_manifest_file_count=0
tokenizer_manifest_vocab_entry_loaded=0
tokenizer_manifest_merges_entry_loaded=0
tokenizer_manifest_special_tokens_entry_loaded=0
tokenizer_file_path_resolved=0
tokenizer_vocab_path_resolved=0

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
requires_manifest_schema_review=1
requires_tokenizer_artifact_inventory_review=1
requires_survivor_centered_language_review=1
requires_refusal_policy_review=1
requires_future_tokenizer_artifact_inventory_contract=1
REPORT

cp "$REPORT" "$OUT_DIR/latest-tokenizer-manifest-contract.txt"

printf 'NADIA_TOKENIZER_MANIFEST_CONTRACT=%s\n' "$REPORT"
printf 'NADIA_TOKENIZER_MANIFEST_LOADED=0\n'
printf 'NADIA_PROMPT_TOKENIZED=0\n'
