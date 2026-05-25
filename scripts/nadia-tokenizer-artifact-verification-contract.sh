#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  nadia-tokenizer-artifact-verification-contract.sh [options]

Options:
  --tokenizer-artifact-measurement <file>  Stage-21 Nadia tokenizer-artifact-measurement contract
  --request-class <label>                  Operator request classification label
  --verification-family <label>            Planned tokenizer artifact verification family label
  --verification-format <label>            Planned tokenizer artifact verification format label
  --output <dir>                           Output directory for tokenizer-artifact-verification contracts

Creates Nadia Stage-22 tokenizer-artifact-verification contract metadata only.
It verifies the tokenizer-artifact-measurement contract and records planned
tokenizer artifact verification requirements before any tokenizer artifact
opening, artifact reading, artifact hashing, digest comparison, size
comparison, tokenizer manifest loading, tokenizer file access, tokenizer
vocabulary loading, prompt tokenization, or prompt evaluation boundary. It does
not open tokenizer artifacts, read tokenizer artifacts, hash tokenizer
artifacts, compare tokenizer artifact digests, verify tokenizer artifacts, load
tokenizer manifests, tokenize prompts, evaluate prompts, generate dialogue,
load model weights, spawn a runtime, create a model session, generate tokens,
run inference, execute tools, mutate source, train, distill, download, or use
network.
USAGE
}

fail() {
  printf 'nadia tokenizer artifact verification contract: %s\n' "$1" >&2
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
  actual=$(field_or_unknown "$key" "$TOKENIZER_ARTIFACT_MEASUREMENT_ABS")
  [ "$actual" = "$expected" ] || fail "$message" 65
}

reject_boundary_label() {
  name="$1"
  value="$2"
  normalized=$(printf '%s\n' "$value" | tr '[:upper:]' '[:lower:]')
  case "$normalized" in
    *sex*|*sexual*|*porn*|*erotic*|*nude*|*nudity*|*nsfw*|*fetish*|*adult-content*)
      fail "$name is outside Nadia tokenizer-artifact-verification boundary" 65
      ;;
  esac
}

TOKENIZER_ARTIFACT_MEASUREMENT=""
REQUEST_CLASS="awareness-education"
VERIFICATION_FAMILY="operator-reviewed-tokenizer-artifact-verification"
VERIFICATION_FORMAT="contract-only-offline-verification"
OUTPUT=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --tokenizer-artifact-measurement)
      [ "$#" -ge 2 ] || fail "missing value for --tokenizer-artifact-measurement" 64
      TOKENIZER_ARTIFACT_MEASUREMENT="$2"
      shift 2
      ;;
    --request-class)
      [ "$#" -ge 2 ] || fail "missing value for --request-class" 64
      REQUEST_CLASS="$2"
      shift 2
      ;;
    --verification-family)
      [ "$#" -ge 2 ] || fail "missing value for --verification-family" 64
      VERIFICATION_FAMILY="$2"
      shift 2
      ;;
    --verification-format)
      [ "$#" -ge 2 ] || fail "missing value for --verification-format" 64
      VERIFICATION_FORMAT="$2"
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

if [ -z "$TOKENIZER_ARTIFACT_MEASUREMENT" ] && [ -f "reports/nadia/tokenizer-artifact-measurement/latest-tokenizer-artifact-measurement-contract.txt" ]; then
  TOKENIZER_ARTIFACT_MEASUREMENT="reports/nadia/tokenizer-artifact-measurement/latest-tokenizer-artifact-measurement-contract.txt"
fi

[ -n "$TOKENIZER_ARTIFACT_MEASUREMENT" ] || fail "tokenizer artifact measurement contract is required" 64
[ -f "$TOKENIZER_ARTIFACT_MEASUREMENT" ] || fail "tokenizer artifact measurement contract not found: $TOKENIZER_ARTIFACT_MEASUREMENT" 66

reject_boundary_label "request class" "$REQUEST_CLASS"
reject_boundary_label "verification family" "$VERIFICATION_FAMILY"
reject_boundary_label "verification format" "$VERIFICATION_FORMAT"

if [ -z "$OUTPUT" ]; then
  OUTPUT="reports/nadia/tokenizer-artifact-verification"
fi
mkdir -p "$OUTPUT"
OUT_DIR=$(CDPATH= cd -- "$OUTPUT" && pwd -P)

TS=${NADIA_TOKENIZER_ARTIFACT_VERIFICATION_TIMESTAMP:-$(date -u +"%Y%m%dT%H%M%SZ")}
REPORT="$OUT_DIR/nadia-tokenizer-artifact-verification-contract-$TS.txt"

TOKENIZER_ARTIFACT_MEASUREMENT_ABS=$(cd "$(dirname -- "$TOKENIZER_ARTIFACT_MEASUREMENT")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$TOKENIZER_ARTIFACT_MEASUREMENT")")
TOKENIZER_ARTIFACT_MEASUREMENT_MEASUREMENT=$(measure_file "$TOKENIZER_ARTIFACT_MEASUREMENT_ABS")

require_field stage 21-tokenizer-artifact-measurement-contract "tokenizer artifact measurement stage must be 21-tokenizer-artifact-measurement-contract"
require_field tokenizer_artifact_measurement_contract_status contract_only "tokenizer artifact measurement contract must remain contract-only"
require_field tokenizer_artifact_measurement_stage contract-only "tokenizer artifact measurement stage must be contract-only"
require_field tokenizer_artifact_measurement_authority 0 "tokenizer artifact measurement authority must remain denied"
require_field tokenizer_artifact_measurement_allowed 0 "tokenizer artifact measurement must remain disallowed"
require_field tokenizer_artifact_measurement_performed 0 "tokenizer artifact measurement must not be performed"
require_field tokenizer_artifact_measurement_metadata_present 1 "tokenizer artifact measurement metadata must be present"
require_field tokenizer_artifact_measurement_decision blocked_contract_only "tokenizer artifact measurement decision must be blocked_contract_only"
require_field tokenizer_artifact_measurement_evidence_present 1 "tokenizer artifact measurement evidence must be present"
require_field tokenizer_artifact_measurement_source_policy operator-reviewed-offline "tokenizer artifact measurement source policy must be operator-reviewed-offline"
require_field tokenizer_artifact_measurement_plan_recorded 1 "tokenizer artifact measurement plan must be recorded"
require_field tokenizer_artifact_measurement_result_recorded 0 "tokenizer artifact measurement result must not be recorded"
require_field tokenizer_artifact_measurement_digest_recorded 0 "tokenizer artifact measurement digest must not be recorded"
require_field tokenizer_artifact_measurement_size_recorded 0 "tokenizer artifact measurement size must not be recorded"
require_field requires_tokenizer_artifact_inventory_contract 1 "tokenizer artifact measurement must require tokenizer artifact inventory"
require_field requires_tokenizer_manifest_contract 1 "tokenizer artifact measurement must require tokenizer manifest"
require_field requires_tokenizer_specification_contract 1 "tokenizer artifact measurement must require tokenizer specification"
require_field requires_tokenization_boundary_contract 1 "tokenizer artifact measurement must require tokenization boundary"
require_field requires_future_tokenizer_artifact_verification_contract 1 "tokenizer artifact measurement must require future tokenizer artifact verification contract"
require_field tokenizer_artifact_measurement_promotion_allowed 0 "tokenizer artifact measurement must not allow promotion"
require_field requires_artifact_identity 1 "artifact identity must be required"
require_field requires_artifact_role_classification 1 "artifact role classification must be required"
require_field requires_inventory_entry_reference 1 "inventory entry reference must be required"
require_field requires_measurement_algorithm_policy 1 "measurement algorithm policy must be required"
require_field requires_digest_format_policy 1 "digest format policy must be required"
require_field requires_size_record_policy 1 "size record policy must be required"
require_field requires_reproducible_measurement_policy 1 "reproducible measurement policy must be required"
require_field requires_operator_approval_record 1 "operator approval record must be required"
require_field requires_official_source_snapshot 1 "official source snapshot must be required"
require_field requires_no_runtime_binding 1 "runtime binding must remain forbidden"
require_field requires_refusal_policy_link 1 "refusal policy link must be required"
require_field requires_survivor_centered_language_review 1 "survivor-centered language review must be required"
require_field tokenizer_artifact_measurement_open_authority 0 "tokenizer artifact measurement open authority must remain denied"
require_field tokenizer_artifact_measurement_read_authority 0 "tokenizer artifact measurement read authority must remain denied"
require_field tokenizer_artifact_measurement_hash_authority 0 "tokenizer artifact measurement hash authority must remain denied"
require_field tokenizer_artifact_measurement_validation_authority 0 "tokenizer artifact measurement validation authority must remain denied"
require_field tokenizer_artifact_measurement_load_authority 0 "tokenizer artifact measurement load authority must remain denied"
require_field tokenizer_artifact_measurement_opened 0 "tokenizer artifact measurement must not be opened"
require_field tokenizer_artifact_measurement_read 0 "tokenizer artifact measurement must not be read"
require_field tokenizer_artifact_measurement_validated 0 "tokenizer artifact measurement must not be validated"
require_field tokenizer_artifact_measurement_loaded 0 "tokenizer artifact measurement must not be loaded"
require_field tokenizer_artifact_measurement_bytes_read 0 "tokenizer artifact measurement bytes must not be read"
require_field tokenizer_artifact_measurement_hash_computed 0 "tokenizer artifact measurement hash must not be computed"
require_field tokenizer_artifact_measurement_entries_loaded 0 "tokenizer artifact measurement entries must not be loaded"
require_field tokenizer_artifact_path_resolved 0 "tokenizer artifact path must not be resolved"
require_field tokenizer_artifact_file_opened 0 "tokenizer artifact file must not be opened"
require_field tokenizer_artifact_file_read 0 "tokenizer artifact file must not be read"
require_field tokenizer_artifact_bytes_read 0 "tokenizer artifact bytes must not be read"
require_field tokenizer_artifact_hash_computed 0 "tokenizer artifact hash must not be computed"
require_field tokenizer_artifact_digest_recorded 0 "tokenizer artifact digest must not be recorded"
require_field tokenizer_artifact_size_recorded 0 "tokenizer artifact size must not be recorded"
require_field tokenizer_artifact_inventory_opened 0 "tokenizer artifact inventory must not be opened"
require_field tokenizer_artifact_inventory_read 0 "tokenizer artifact inventory must not be read"
require_field tokenizer_artifact_inventory_loaded 0 "tokenizer artifact inventory must not be loaded"
require_field tokenizer_artifact_scan_performed 0 "tokenizer artifact scan must not be performed"
require_field tokenizer_artifact_stat_performed 0 "tokenizer artifact stat must not be performed"
require_field tokenizer_manifest_opened 0 "tokenizer manifest must not be opened"
require_field tokenizer_manifest_read 0 "tokenizer manifest must not be read"
require_field tokenizer_manifest_parsed 0 "tokenizer manifest must not be parsed"
require_field tokenizer_manifest_loaded 0 "tokenizer manifest must not be loaded"
require_field tokenizer_file_opened 0 "tokenizer file must not be opened"
require_field tokenizer_file_read 0 "tokenizer file must not be read"
require_field tokenizer_vocab_loaded 0 "tokenizer vocabulary must not be loaded"
require_field prompt_materialized 0 "prompt must not be materialized"
require_field prompt_tokenized 0 "prompt must not be tokenized"
require_field prompt_evaluated 0 "prompt must not be evaluated"
require_field future_qa_dialogue_capability_planned 1 "future Q&A capability must remain planned only"
require_field qa_dialogue_generated 0 "Q&A dialogue must not be generated"
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
require_field runtime_invoked 0 "runtime must not be invoked"
require_field model_loaded 0 "model must not be loaded"
require_field model_weights_loaded 0 "model weights must not be loaded"
require_field token_generation_performed 0 "token generation must not be performed"
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

TOKENIZER_ARTIFACT_MEASUREMENT_CONTRACT_STATUS=$(field_or_unknown tokenizer_artifact_measurement_contract_status "$TOKENIZER_ARTIFACT_MEASUREMENT_ABS")
TOKENIZER_ARTIFACT_MEASUREMENT_STAGE=$(field_or_unknown tokenizer_artifact_measurement_stage "$TOKENIZER_ARTIFACT_MEASUREMENT_ABS")
TOKENIZER_ARTIFACT_INVENTORY_STAGE=$(field_or_unknown tokenizer_artifact_inventory_stage "$TOKENIZER_ARTIFACT_MEASUREMENT_ABS")
TOKENIZER_MANIFEST_STAGE=$(field_or_unknown tokenizer_manifest_stage "$TOKENIZER_ARTIFACT_MEASUREMENT_ABS")
TOKENIZER_SPECIFICATION_STAGE=$(field_or_unknown tokenizer_specification_stage "$TOKENIZER_ARTIFACT_MEASUREMENT_ABS")
TOKENIZATION_BOUNDARY_STAGE=$(field_or_unknown tokenization_boundary_stage "$TOKENIZER_ARTIFACT_MEASUREMENT_ABS")
TOKENIZER_ARTIFACT_MEASUREMENT_FAMILY=$(field_or_unknown tokenizer_artifact_measurement_family "$TOKENIZER_ARTIFACT_MEASUREMENT_ABS")
TOKENIZER_ARTIFACT_MEASUREMENT_FORMAT=$(field_or_unknown tokenizer_artifact_measurement_format "$TOKENIZER_ARTIFACT_MEASUREMENT_ABS")

cat > "$REPORT" <<REPORT
NADIA TOKENIZER ARTIFACT VERIFICATION CONTRACT

timestamp_utc=$TS
system_name=Latticra Nadia Witness Foundation
public_name=Nadia
interactive_name=Nadia
implementation_name=Nadia Witness Foundation
documentation_code_name=Nadia Witness Foundation
stage=22-tokenizer-artifact-verification-contract
output_dir=$OUT_DIR
request_class=$REQUEST_CLASS
tokenizer_artifact_verification_contract_status=contract_only
tokenizer_artifact_verification_stage=contract-only
tokenizer_artifact_verification_authority=0
tokenizer_artifact_verification_allowed=0
tokenizer_artifact_verification_performed=0
tokenizer_artifact_verification_metadata_present=1
tokenizer_artifact_verification_family=$VERIFICATION_FAMILY
tokenizer_artifact_verification_format=$VERIFICATION_FORMAT
tokenizer_artifact_verification_loaded=0
tokenizer_artifact_verification_opened=0
tokenizer_artifact_verification_read=0
tokenizer_artifact_verification_validated=0
tokenizer_artifact_verification_compared=0
tokenizer_artifact_path_resolved=0
tokenizer_artifact_file_opened=0
tokenizer_artifact_file_read=0
tokenizer_artifact_hash_computed=0
tokenizer_artifact_measurement_performed=0
tokenizer_artifact_verification_performed=0
tokenizer_artifact_digest_recorded=0
tokenizer_artifact_size_recorded=0
tokenizer_manifest_loaded=0
tokenizer_manifest_parsed=0
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
tokenizer_artifact_measurement=$TOKENIZER_ARTIFACT_MEASUREMENT_ABS
tokenizer_artifact_measurement_measurement=$TOKENIZER_ARTIFACT_MEASUREMENT_MEASUREMENT
tokenizer_artifact_measurement_stage_required=21-tokenizer-artifact-measurement-contract
tokenizer_artifact_measurement_contract_status=$TOKENIZER_ARTIFACT_MEASUREMENT_CONTRACT_STATUS
tokenizer_artifact_measurement_stage=$TOKENIZER_ARTIFACT_MEASUREMENT_STAGE
tokenizer_artifact_inventory_stage=$TOKENIZER_ARTIFACT_INVENTORY_STAGE
tokenizer_manifest_stage=$TOKENIZER_MANIFEST_STAGE
tokenizer_specification_stage=$TOKENIZER_SPECIFICATION_STAGE
tokenization_boundary_stage=$TOKENIZATION_BOUNDARY_STAGE
tokenizer_artifact_measurement_family=$TOKENIZER_ARTIFACT_MEASUREMENT_FAMILY
tokenizer_artifact_measurement_format=$TOKENIZER_ARTIFACT_MEASUREMENT_FORMAT

[tokenizer_artifact_verification_contract]
tokenizer_artifact_verification_contract_command=scripts/nadia-tokenizer-artifact-verification-contract.sh
installed_tokenizer_artifact_verification_contract_command=latticra-nadia tokenizer-artifact-verification
tokenizer_artifact_verification_decision=blocked_contract_only
tokenizer_artifact_verification_evidence_present=1
tokenizer_artifact_verification_source_policy=operator-reviewed-offline
tokenizer_artifact_verification_plan_recorded=1
tokenizer_artifact_verification_method_planned=offline-digest-and-size-policy-review
tokenizer_artifact_verification_comparison_performed=0
tokenizer_artifact_verification_result_recorded=0
tokenizer_artifact_verification_digest_match_recorded=0
tokenizer_artifact_verification_size_match_recorded=0
tokenizer_artifact_source_signature_verified=0
requires_tokenizer_artifact_measurement_contract=1
requires_tokenizer_artifact_inventory_contract=1
requires_tokenizer_manifest_contract=1
requires_tokenizer_specification_contract=1
requires_tokenization_boundary_contract=1
requires_future_tokenizer_artifact_binding_contract=1
tokenizer_artifact_verification_promotion_allowed=0

[tokenizer_artifact_verification_requirements]
requires_artifact_identity=1
requires_artifact_role_classification=1
requires_measurement_contract_reference=1
requires_inventory_entry_reference=1
requires_expected_digest_policy=1
requires_observed_digest_policy=1
requires_digest_comparison_policy=1
requires_size_comparison_policy=1
requires_source_snapshot_reference=1
requires_license_and_source_review=1
requires_operator_approval_record=1
requires_official_source_snapshot=1
requires_no_runtime_binding=1
requires_refusal_policy_link=1
requires_survivor_centered_language_review=1

[tokenizer_artifact_verification_denial_boundary]
tokenizer_artifact_verification_authority=0
tokenizer_artifact_verification_allowed=0
tokenizer_artifact_verification_open_authority=0
tokenizer_artifact_verification_read_authority=0
tokenizer_artifact_verification_hash_authority=0
tokenizer_artifact_verification_validation_authority=0
tokenizer_artifact_verification_load_authority=0
tokenizer_artifact_verification_compare_authority=0
tokenizer_artifact_verification_bind_authority=0
tokenizer_artifact_verification_opened=0
tokenizer_artifact_verification_read=0
tokenizer_artifact_verification_validated=0
tokenizer_artifact_verification_loaded=0
tokenizer_artifact_verification_bytes_read=0
tokenizer_artifact_verification_hash_computed=0
tokenizer_artifact_verification_entries_loaded=0
tokenizer_artifact_verification_performed=0
tokenizer_artifact_verification_compared=0
tokenizer_artifact_verification_comparison_performed=0
tokenizer_artifact_verification_digest_comparison_performed=0
tokenizer_artifact_verification_size_comparison_performed=0
tokenizer_artifact_verification_expected_digest_loaded=0
tokenizer_artifact_verification_observed_digest_loaded=0
tokenizer_artifact_verification_digest_match_recorded=0
tokenizer_artifact_verification_size_match_recorded=0
tokenizer_artifact_verification_result_recorded=0
tokenizer_artifact_source_signature_verified=0
tokenizer_artifact_digest_recorded=0
tokenizer_artifact_size_recorded=0
tokenizer_artifact_path_resolved=0
tokenizer_artifact_file_opened=0
tokenizer_artifact_file_read=0
tokenizer_artifact_bytes_read=0
tokenizer_artifact_hash_computed=0

[tokenizer_artifact_measurement_denial_boundary]
tokenizer_artifact_measurement_authority=0
tokenizer_artifact_measurement_allowed=0
tokenizer_artifact_measurement_open_authority=0
tokenizer_artifact_measurement_read_authority=0
tokenizer_artifact_measurement_hash_authority=0
tokenizer_artifact_measurement_validation_authority=0
tokenizer_artifact_measurement_load_authority=0
tokenizer_artifact_measurement_opened=0
tokenizer_artifact_measurement_read=0
tokenizer_artifact_measurement_validated=0
tokenizer_artifact_measurement_loaded=0
tokenizer_artifact_measurement_bytes_read=0
tokenizer_artifact_measurement_hash_computed=0
tokenizer_artifact_measurement_entries_loaded=0
tokenizer_artifact_measurement_performed=0
tokenizer_artifact_measurement_result_recorded=0
tokenizer_artifact_measurement_digest_recorded=0
tokenizer_artifact_measurement_size_recorded=0
tokenizer_artifact_digest_recorded=0
tokenizer_artifact_size_recorded=0

[tokenizer_artifact_inventory_denial_boundary]
tokenizer_artifact_inventory_open_authority=0
tokenizer_artifact_inventory_read_authority=0
tokenizer_artifact_inventory_parse_authority=0
tokenizer_artifact_inventory_validation_authority=0
tokenizer_artifact_inventory_load_authority=0
tokenizer_artifact_path_resolution_authority=0
tokenizer_artifact_scan_authority=0
tokenizer_artifact_stat_authority=0
tokenizer_artifact_hash_authority=0
tokenizer_artifact_inventory_opened=0
tokenizer_artifact_inventory_read=0
tokenizer_artifact_inventory_parsed=0
tokenizer_artifact_inventory_validated=0
tokenizer_artifact_inventory_loaded=0
tokenizer_artifact_inventory_bytes_read=0
tokenizer_artifact_inventory_hash_computed=0
tokenizer_artifact_inventory_entries_loaded=0
tokenizer_artifact_inventory_entry_count=0
tokenizer_artifact_inventory_file_count=0
tokenizer_artifact_path_resolved=0
tokenizer_artifact_scan_performed=0
tokenizer_artifact_stat_performed=0
tokenizer_artifact_file_opened=0
tokenizer_artifact_file_read=0
tokenizer_artifact_bytes_read=0
tokenizer_artifact_hash_computed=0
tokenizer_artifact_measurement_performed=0
tokenizer_vocab_artifact_loaded=0
tokenizer_merges_artifact_loaded=0
tokenizer_model_artifact_loaded=0
tokenizer_special_tokens_artifact_loaded=0

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
requires_artifact_inventory_review=1
requires_artifact_measurement_review=1
requires_artifact_verification_review=1
requires_artifact_binding_review=1
requires_survivor_centered_language_review=1
requires_refusal_policy_review=1
requires_future_tokenizer_artifact_binding_contract=1
REPORT

cp "$REPORT" "$OUT_DIR/latest-tokenizer-artifact-verification-contract.txt"

printf 'NADIA_TOKENIZER_ARTIFACT_VERIFICATION_CONTRACT=%s\n' "$REPORT"
printf 'NADIA_TOKENIZER_ARTIFACT_VERIFICATION_PERFORMED=0\n'
printf 'NADIA_PROMPT_TOKENIZED=0\n'
