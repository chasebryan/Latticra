#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

usage() {
  cat <<'USAGE'
Usage:
  nadia-tokenizer-runtime-attachment-contract.sh [options]

Options:
  --tokenizer-artifact-binding <file>  Stage-23 Nadia tokenizer-artifact-binding contract
  --request-class <label>              Operator request classification label
  --attachment-family <label>          Planned tokenizer runtime attachment family label
  --attachment-format <label>          Planned tokenizer runtime attachment format label
  --output <dir>                       Output directory for tokenizer-runtime-attachment contracts

Creates Nadia Stage-24 tokenizer-runtime-attachment contract metadata only.
It verifies the tokenizer-artifact-binding contract and records planned
tokenizer runtime attachment requirements before any tokenizer artifact
opening, artifact reading, artifact hashing, artifact binding, tokenizer
runtime attachment, runtime session creation, tokenizer manifest loading,
tokenizer file access, tokenizer vocabulary loading, prompt tokenization, or
prompt evaluation boundary. It does not open tokenizer artifacts, read tokenizer
artifacts, hash tokenizer artifacts, bind tokenizer artifacts, attach tokenizers
to a runtime, load tokenizer manifests, tokenize prompts, evaluate prompts,
generate dialogue, load model weights, spawn a runtime, create a model session,
generate tokens, run inference, execute tools, mutate source, train, distill,
download, or use network.
USAGE
}

fail() {
  printf 'nadia tokenizer runtime attachment contract: %s\n' "$1" >&2
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
  actual=$(field_or_unknown "$key" "$TOKENIZER_ARTIFACT_BINDING_ABS")
  [ "$actual" = "$expected" ] || fail "$message" 65
}

reject_boundary_label() {
  name="$1"
  value="$2"
  normalized=$(printf '%s\n' "$value" | tr '[:upper:]' '[:lower:]')
  case "$normalized" in
    *sex*|*sexual*|*porn*|*erotic*|*nude*|*nudity*|*nsfw*|*fetish*|*adult-content*)
      fail "$name is outside Nadia tokenizer-runtime-attachment boundary" 65
      ;;
  esac
}

TOKENIZER_ARTIFACT_BINDING=""
REQUEST_CLASS="awareness-education"
ATTACHMENT_FAMILY="operator-reviewed-tokenizer-runtime-attachment"
ATTACHMENT_FORMAT="contract-only-offline-attachment"
OUTPUT=""

while [ "$#" -gt 0 ]; do
  case "$1" in
    --tokenizer-artifact-binding)
      [ "$#" -ge 2 ] || fail "missing value for --tokenizer-artifact-binding" 64
      TOKENIZER_ARTIFACT_BINDING="$2"
      shift 2
      ;;
    --request-class)
      [ "$#" -ge 2 ] || fail "missing value for --request-class" 64
      REQUEST_CLASS="$2"
      shift 2
      ;;
    --attachment-family)
      [ "$#" -ge 2 ] || fail "missing value for --attachment-family" 64
      ATTACHMENT_FAMILY="$2"
      shift 2
      ;;
    --attachment-format)
      [ "$#" -ge 2 ] || fail "missing value for --attachment-format" 64
      ATTACHMENT_FORMAT="$2"
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

if [ -z "$TOKENIZER_ARTIFACT_BINDING" ] && [ -f "reports/nadia/tokenizer-artifact-binding/latest-tokenizer-artifact-binding-contract.txt" ]; then
  TOKENIZER_ARTIFACT_BINDING="reports/nadia/tokenizer-artifact-binding/latest-tokenizer-artifact-binding-contract.txt"
fi

[ -n "$TOKENIZER_ARTIFACT_BINDING" ] || fail "tokenizer artifact binding contract is required" 64
[ -f "$TOKENIZER_ARTIFACT_BINDING" ] || fail "tokenizer artifact binding contract not found: $TOKENIZER_ARTIFACT_BINDING" 66

reject_boundary_label "request class" "$REQUEST_CLASS"
reject_boundary_label "attachment family" "$ATTACHMENT_FAMILY"
reject_boundary_label "attachment format" "$ATTACHMENT_FORMAT"

if [ -z "$OUTPUT" ]; then
  OUTPUT="reports/nadia/tokenizer-runtime-attachment"
fi
mkdir -p "$OUTPUT"
OUT_DIR=$(CDPATH= cd -- "$OUTPUT" && pwd -P)

TS=${NADIA_TOKENIZER_RUNTIME_ATTACHMENT_TIMESTAMP:-$(date -u +"%Y%m%dT%H%M%SZ")}
REPORT="$OUT_DIR/nadia-tokenizer-runtime-attachment-contract-$TS.txt"

TOKENIZER_ARTIFACT_BINDING_ABS=$(cd "$(dirname -- "$TOKENIZER_ARTIFACT_BINDING")" && printf '%s/%s\n' "$(pwd -P)" "$(basename -- "$TOKENIZER_ARTIFACT_BINDING")")
TOKENIZER_ARTIFACT_BINDING_MEASUREMENT=$(measure_file "$TOKENIZER_ARTIFACT_BINDING_ABS")

require_field stage 23-tokenizer-artifact-binding-contract "tokenizer artifact binding stage must be 23-tokenizer-artifact-binding-contract"
require_field tokenizer_artifact_binding_contract_status contract_only "tokenizer artifact binding contract must remain contract-only"
require_field tokenizer_artifact_binding_stage contract-only "tokenizer artifact binding stage must be contract-only"
require_field tokenizer_artifact_binding_authority 0 "tokenizer artifact binding authority must remain denied"
require_field tokenizer_artifact_binding_allowed 0 "tokenizer artifact binding must remain disallowed"
require_field tokenizer_artifact_binding_performed 0 "tokenizer artifact binding must not be performed"
require_field tokenizer_artifact_binding_metadata_present 1 "tokenizer artifact binding metadata must be present"
require_field tokenizer_artifact_binding_decision blocked_contract_only "tokenizer artifact binding decision must be blocked_contract_only"
require_field tokenizer_artifact_binding_evidence_present 1 "tokenizer artifact binding evidence must be present"
require_field tokenizer_artifact_binding_source_policy operator-reviewed-offline "tokenizer artifact binding source policy must be operator-reviewed-offline"
require_field tokenizer_artifact_binding_plan_recorded 1 "tokenizer artifact binding plan must be recorded"
require_field tokenizer_artifact_binding_result_recorded 0 "tokenizer artifact binding result must not be recorded"
require_field tokenizer_artifact_binding_record_created 0 "tokenizer artifact binding record must not be created"
require_field tokenizer_artifact_binding_manifest_reference_recorded 0 "tokenizer artifact binding manifest reference must not be recorded"
require_field tokenizer_artifact_binding_artifact_reference_recorded 0 "tokenizer artifact binding artifact reference must not be recorded"
require_field tokenizer_artifact_binding_runtime_attach_recorded 0 "tokenizer artifact binding runtime attach must not be recorded"
require_field requires_tokenizer_artifact_verification_contract 1 "tokenizer artifact binding must require tokenizer artifact verification"
require_field requires_tokenizer_artifact_measurement_contract 1 "tokenizer artifact binding must require tokenizer artifact measurement"
require_field requires_tokenizer_artifact_inventory_contract 1 "tokenizer artifact binding must require tokenizer artifact inventory"
require_field requires_tokenizer_manifest_contract 1 "tokenizer artifact binding must require tokenizer manifest"
require_field requires_tokenizer_specification_contract 1 "tokenizer artifact binding must require tokenizer specification"
require_field requires_tokenization_boundary_contract 1 "tokenizer artifact binding must require tokenization boundary"
require_field requires_future_tokenizer_runtime_attachment_contract 1 "tokenizer artifact binding must require future tokenizer runtime attachment contract"
require_field tokenizer_artifact_binding_promotion_allowed 0 "tokenizer artifact binding must not allow promotion"
require_field requires_verified_artifact_reference 1 "verified artifact reference must be required"
require_field requires_artifact_identity 1 "artifact identity must be required"
require_field requires_artifact_role_classification 1 "artifact role classification must be required"
require_field requires_verification_contract_reference 1 "verification contract reference must be required"
require_field requires_measurement_contract_reference 1 "measurement contract reference must be required"
require_field requires_inventory_entry_reference 1 "inventory entry reference must be required"
require_field requires_manifest_entry_reference 1 "manifest entry reference must be required"
require_field requires_tokenizer_specification_reference 1 "tokenizer specification reference must be required"
require_field requires_digest_match_record 1 "digest match record must be required"
require_field requires_size_match_record 1 "size match record must be required"
require_field requires_no_runtime_attachment 1 "runtime attachment must remain forbidden"
require_field requires_refusal_policy_link 1 "refusal policy link must be required"
require_field requires_survivor_centered_language_review 1 "survivor-centered language review must be required"
require_field tokenizer_artifact_binding_open_authority 0 "tokenizer artifact binding open authority must remain denied"
require_field tokenizer_artifact_binding_read_authority 0 "tokenizer artifact binding read authority must remain denied"
require_field tokenizer_artifact_binding_write_authority 0 "tokenizer artifact binding write authority must remain denied"
require_field tokenizer_artifact_binding_hash_authority 0 "tokenizer artifact binding hash authority must remain denied"
require_field tokenizer_artifact_binding_validation_authority 0 "tokenizer artifact binding validation authority must remain denied"
require_field tokenizer_artifact_binding_load_authority 0 "tokenizer artifact binding load authority must remain denied"
require_field tokenizer_artifact_binding_attach_authority 0 "tokenizer artifact binding attach authority must remain denied"
require_field tokenizer_artifact_binding_runtime_attach_authority 0 "tokenizer artifact binding runtime attach authority must remain denied"
require_field tokenizer_artifact_binding_manifest_bind_authority 0 "tokenizer artifact binding manifest bind authority must remain denied"
require_field tokenizer_artifact_binding_tokenizer_bind_authority 0 "tokenizer artifact binding tokenizer bind authority must remain denied"
require_field tokenizer_artifact_binding_opened 0 "tokenizer artifact binding must not be opened"
require_field tokenizer_artifact_binding_read 0 "tokenizer artifact binding must not be read"
require_field tokenizer_artifact_binding_validated 0 "tokenizer artifact binding must not be validated"
require_field tokenizer_artifact_binding_loaded 0 "tokenizer artifact binding must not be loaded"
require_field tokenizer_artifact_binding_bytes_read 0 "tokenizer artifact binding bytes must not be read"
require_field tokenizer_artifact_binding_hash_computed 0 "tokenizer artifact binding hash must not be computed"
require_field tokenizer_artifact_binding_entries_loaded 0 "tokenizer artifact binding entries must not be loaded"
require_field tokenizer_artifact_binding_bound 0 "tokenizer artifact binding must not bind"
require_field tokenizer_artifact_binding_runtime_attachment_performed 0 "tokenizer runtime attachment must not be performed"
require_field tokenizer_artifact_binding_file_written 0 "tokenizer artifact binding file must not be written"
require_field tokenizer_artifact_bound_to_manifest 0 "tokenizer artifact must not be bound to manifest"
require_field tokenizer_artifact_bound_to_tokenizer 0 "tokenizer artifact must not be bound to tokenizer"
require_field tokenizer_attached_to_runtime 0 "tokenizer must not be attached to runtime"
require_field tokenizer_runtime_attachment_performed 0 "tokenizer runtime attachment must not be performed"
require_field tokenizer_artifact_file_opened 0 "tokenizer artifact file must not be opened"
require_field tokenizer_artifact_file_read 0 "tokenizer artifact file must not be read"
require_field tokenizer_artifact_hash_computed 0 "tokenizer artifact hash must not be computed"
require_field tokenizer_artifact_verification_performed 0 "tokenizer artifact verification must not be performed"
require_field tokenizer_artifact_binding_performed 0 "tokenizer artifact binding must not be performed"
require_field tokenizer_manifest_opened 0 "tokenizer manifest must not be opened"
require_field tokenizer_manifest_read 0 "tokenizer manifest must not be read"
require_field tokenizer_manifest_parsed 0 "tokenizer manifest must not be parsed"
require_field tokenizer_manifest_loaded 0 "tokenizer manifest must not be loaded"
require_field tokenizer_file_opened 0 "tokenizer file must not be opened"
require_field tokenizer_file_read 0 "tokenizer file must not be read"
require_field tokenizer_vocab_loaded 0 "tokenizer vocabulary must not be loaded"
require_field tokenizer_runtime_attach_authority 0 "tokenizer runtime attach authority must remain denied"
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

TOKENIZER_ARTIFACT_BINDING_CONTRACT_STATUS=$(field_or_unknown tokenizer_artifact_binding_contract_status "$TOKENIZER_ARTIFACT_BINDING_ABS")
TOKENIZER_ARTIFACT_BINDING_STAGE=$(field_or_unknown tokenizer_artifact_binding_stage "$TOKENIZER_ARTIFACT_BINDING_ABS")
TOKENIZER_ARTIFACT_VERIFICATION_STAGE=$(field_or_unknown tokenizer_artifact_verification_stage "$TOKENIZER_ARTIFACT_BINDING_ABS")
TOKENIZER_ARTIFACT_MEASUREMENT_STAGE=$(field_or_unknown tokenizer_artifact_measurement_stage "$TOKENIZER_ARTIFACT_BINDING_ABS")
TOKENIZER_ARTIFACT_INVENTORY_STAGE=$(field_or_unknown tokenizer_artifact_inventory_stage "$TOKENIZER_ARTIFACT_BINDING_ABS")
TOKENIZER_MANIFEST_STAGE=$(field_or_unknown tokenizer_manifest_stage "$TOKENIZER_ARTIFACT_BINDING_ABS")
TOKENIZER_SPECIFICATION_STAGE=$(field_or_unknown tokenizer_specification_stage "$TOKENIZER_ARTIFACT_BINDING_ABS")
TOKENIZATION_BOUNDARY_STAGE=$(field_or_unknown tokenization_boundary_stage "$TOKENIZER_ARTIFACT_BINDING_ABS")
TOKENIZER_ARTIFACT_BINDING_FAMILY=$(field_or_unknown tokenizer_artifact_binding_family "$TOKENIZER_ARTIFACT_BINDING_ABS")
TOKENIZER_ARTIFACT_BINDING_FORMAT=$(field_or_unknown tokenizer_artifact_binding_format "$TOKENIZER_ARTIFACT_BINDING_ABS")

cat > "$REPORT" <<REPORT
NADIA TOKENIZER RUNTIME ATTACHMENT CONTRACT

timestamp_utc=$TS
system_name=Latticra Nadia Witness Foundation
public_name=Nadia
interactive_name=Nadia
implementation_name=Nadia Witness Foundation
documentation_code_name=Nadia Witness Foundation
stage=24-tokenizer-runtime-attachment-contract
output_dir=$OUT_DIR
request_class=$REQUEST_CLASS
tokenizer_runtime_attachment_contract_status=contract_only
tokenizer_runtime_attachment_stage=contract-only
tokenizer_runtime_attachment_authority=0
tokenizer_runtime_attachment_allowed=0
tokenizer_runtime_attachment_performed=0
tokenizer_runtime_attachment_metadata_present=1
tokenizer_runtime_attachment_family=$ATTACHMENT_FAMILY
tokenizer_runtime_attachment_format=$ATTACHMENT_FORMAT
tokenizer_runtime_attachment_loaded=0
tokenizer_runtime_attachment_opened=0
tokenizer_runtime_attachment_read=0
tokenizer_runtime_attachment_validated=0
tokenizer_runtime_attachment_attached=0
tokenizer_runtime_attachment_runtime_invoked=0
tokenizer_attached_to_runtime=0
runtime_invoked=0
runtime_session_created=0
runtime_process_spawned=0
runtime_binary_executed=0
tokenizer_artifact_path_resolved=0
tokenizer_artifact_file_opened=0
tokenizer_artifact_file_read=0
tokenizer_artifact_hash_computed=0
tokenizer_artifact_binding_performed=0
tokenizer_artifact_verification_performed=0
tokenizer_artifact_measurement_performed=0
tokenizer_artifact_digest_recorded=0
tokenizer_artifact_size_recorded=0
tokenizer_manifest_loaded=0
tokenizer_manifest_parsed=0
tokenizer_file_opened=0
tokenizer_file_read=0
tokenizer_vocab_loaded=0
tokenizer_vocab_mapped=0
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
tokenizer_artifact_binding=$TOKENIZER_ARTIFACT_BINDING_ABS
tokenizer_artifact_binding_measurement=$TOKENIZER_ARTIFACT_BINDING_MEASUREMENT
tokenizer_artifact_binding_stage_required=23-tokenizer-artifact-binding-contract
tokenizer_artifact_binding_contract_status=$TOKENIZER_ARTIFACT_BINDING_CONTRACT_STATUS
tokenizer_artifact_binding_stage=$TOKENIZER_ARTIFACT_BINDING_STAGE
tokenizer_artifact_verification_stage=$TOKENIZER_ARTIFACT_VERIFICATION_STAGE
tokenizer_artifact_measurement_stage=$TOKENIZER_ARTIFACT_MEASUREMENT_STAGE
tokenizer_artifact_inventory_stage=$TOKENIZER_ARTIFACT_INVENTORY_STAGE
tokenizer_manifest_stage=$TOKENIZER_MANIFEST_STAGE
tokenizer_specification_stage=$TOKENIZER_SPECIFICATION_STAGE
tokenization_boundary_stage=$TOKENIZATION_BOUNDARY_STAGE
tokenizer_artifact_binding_family=$TOKENIZER_ARTIFACT_BINDING_FAMILY
tokenizer_artifact_binding_format=$TOKENIZER_ARTIFACT_BINDING_FORMAT

[tokenizer_runtime_attachment_contract]
tokenizer_runtime_attachment_contract_command=scripts/nadia-tokenizer-runtime-attachment-contract.sh
installed_tokenizer_runtime_attachment_contract_command=latticra-nadia tokenizer-runtime-attachment
tokenizer_runtime_attachment_decision=blocked_contract_only
tokenizer_runtime_attachment_evidence_present=1
tokenizer_runtime_attachment_source_policy=operator-reviewed-offline
tokenizer_runtime_attachment_plan_recorded=1
tokenizer_runtime_attachment_method_planned=offline-runtime-tokenizer-attachment-review
tokenizer_runtime_attachment_result_recorded=0
tokenizer_runtime_attachment_record_created=0
tokenizer_runtime_attachment_runtime_reference_recorded=0
tokenizer_runtime_attachment_tokenizer_reference_recorded=0
tokenizer_runtime_attachment_session_created=0
requires_tokenizer_artifact_binding_contract=1
requires_tokenizer_artifact_verification_contract=1
requires_tokenizer_artifact_measurement_contract=1
requires_tokenizer_artifact_inventory_contract=1
requires_tokenizer_manifest_contract=1
requires_tokenizer_specification_contract=1
requires_tokenization_boundary_contract=1
requires_runtime_profile_contract=1
requires_runtime_invocation_contract=1
requires_model_load_contract=1
requires_future_prompt_tokenization_contract=1
tokenizer_runtime_attachment_promotion_allowed=0

[tokenizer_runtime_attachment_requirements]
requires_bound_tokenizer_artifact_reference=1
requires_binding_contract_reference=1
requires_verified_artifact_reference=1
requires_artifact_identity=1
requires_artifact_role_classification=1
requires_runtime_profile_reference=1
requires_runtime_invocation_reference=1
requires_model_load_reference=1
requires_manifest_entry_reference=1
requires_tokenizer_specification_reference=1
requires_digest_match_record=1
requires_size_match_record=1
requires_operator_approval_record=1
requires_official_source_snapshot=1
requires_no_runtime_invocation=1
requires_no_runtime_session_creation=1
requires_no_prompt_tokenization=1
requires_no_prompt_evaluation=1
requires_no_inference=1
requires_refusal_policy_link=1
requires_survivor_centered_language_review=1

[tokenizer_runtime_attachment_denial_boundary]
tokenizer_runtime_attachment_authority=0
tokenizer_runtime_attachment_allowed=0
tokenizer_runtime_attachment_open_authority=0
tokenizer_runtime_attachment_read_authority=0
tokenizer_runtime_attachment_write_authority=0
tokenizer_runtime_attachment_validation_authority=0
tokenizer_runtime_attachment_load_authority=0
tokenizer_runtime_attachment_attach_authority=0
tokenizer_runtime_attachment_runtime_invoke_authority=0
tokenizer_runtime_attachment_session_authority=0
tokenizer_runtime_attachment_tokenizer_bind_authority=0
tokenizer_runtime_attachment_opened=0
tokenizer_runtime_attachment_read=0
tokenizer_runtime_attachment_validated=0
tokenizer_runtime_attachment_loaded=0
tokenizer_runtime_attachment_bytes_read=0
tokenizer_runtime_attachment_hash_computed=0
tokenizer_runtime_attachment_entries_loaded=0
tokenizer_runtime_attachment_performed=0
tokenizer_runtime_attachment_attached=0
tokenizer_runtime_attachment_record_created=0
tokenizer_runtime_attachment_runtime_reference_loaded=0
tokenizer_runtime_attachment_tokenizer_reference_loaded=0
tokenizer_runtime_attachment_runtime_reference_recorded=0
tokenizer_runtime_attachment_tokenizer_reference_recorded=0
tokenizer_runtime_attachment_runtime_invoked=0
tokenizer_runtime_attachment_session_created=0
tokenizer_runtime_attachment_result_recorded=0
tokenizer_runtime_attachment_file_written=0
tokenizer_attached_to_runtime=0
tokenizer_runtime_attachment_performed=0
runtime_tokenizer_attachment_performed=0
runtime_session_created=0
runtime_invoked=0
runtime_process_spawned=0
runtime_binary_executed=0

[tokenizer_artifact_binding_denial_boundary]
tokenizer_artifact_binding_authority=0
tokenizer_artifact_binding_allowed=0
tokenizer_artifact_binding_open_authority=0
tokenizer_artifact_binding_read_authority=0
tokenizer_artifact_binding_write_authority=0
tokenizer_artifact_binding_hash_authority=0
tokenizer_artifact_binding_validation_authority=0
tokenizer_artifact_binding_load_authority=0
tokenizer_artifact_binding_attach_authority=0
tokenizer_artifact_binding_runtime_attach_authority=0
tokenizer_artifact_binding_manifest_bind_authority=0
tokenizer_artifact_binding_tokenizer_bind_authority=0
tokenizer_artifact_binding_opened=0
tokenizer_artifact_binding_read=0
tokenizer_artifact_binding_validated=0
tokenizer_artifact_binding_loaded=0
tokenizer_artifact_binding_bytes_read=0
tokenizer_artifact_binding_hash_computed=0
tokenizer_artifact_binding_entries_loaded=0
tokenizer_artifact_binding_performed=0
tokenizer_artifact_binding_bound=0
tokenizer_artifact_binding_record_created=0
tokenizer_artifact_binding_manifest_reference_loaded=0
tokenizer_artifact_binding_artifact_reference_loaded=0
tokenizer_artifact_binding_manifest_reference_recorded=0
tokenizer_artifact_binding_artifact_reference_recorded=0
tokenizer_artifact_binding_runtime_attach_recorded=0
tokenizer_artifact_binding_runtime_attachment_performed=0
tokenizer_artifact_binding_result_recorded=0
tokenizer_artifact_binding_file_written=0
tokenizer_artifact_bound_to_manifest=0
tokenizer_artifact_bound_to_tokenizer=0

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

[tokenizer_artifact_denial_boundary]
tokenizer_artifact_digest_recorded=0
tokenizer_artifact_size_recorded=0
tokenizer_artifact_path_resolved=0
tokenizer_artifact_file_opened=0
tokenizer_artifact_file_read=0
tokenizer_artifact_bytes_read=0
tokenizer_artifact_hash_computed=0
tokenizer_artifact_measurement_performed=0
tokenizer_artifact_verification_performed=0
tokenizer_artifact_binding_performed=0

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
requires_survivor_centered_language_review=1
requires_refusal_policy_review=1
requires_future_prompt_tokenization_contract=1
REPORT

cp "$REPORT" "$OUT_DIR/latest-tokenizer-runtime-attachment-contract.txt"

printf 'NADIA_TOKENIZER_RUNTIME_ATTACHMENT_CONTRACT=%s\n' "$REPORT"
printf 'NADIA_TOKENIZER_RUNTIME_ATTACHMENT_PERFORMED=0\n'
printf 'NADIA_PROMPT_TOKENIZED=0\n'
