#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia prompt evaluation invocation contract stage 30: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia prompt evaluation invocation contract stage 30: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage30_doc='docs/NADIA_PROMPT_EVALUATION_INVOCATION_CONTRACT_STAGE_30.md'
stage30_status='docs/status/NADIA_PROMPT_EVALUATION_INVOCATION_CONTRACT_STAGE_30_STATUS.md'
stage29_status='docs/status/NADIA_PROMPT_EVALUATION_RUNTIME_HANDOFF_CONTRACT_STAGE_29_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
foundation_index='docs/FOUNDATION_INDEX.md'
status_index='docs/status/README.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
invocation_script='scripts/nadia-prompt-evaluation-invocation-contract.sh'
stage30_guard='scripts/test-nadia-prompt-evaluation-invocation-contract-stage-30.sh'
workflow='.github/workflows/nadia-prompt-evaluation-invocation-contract-stage-30.yml'
makefile='Makefile'

require_file "$stage30_doc"
require_file "$stage30_status"
require_file "$stage29_status"
require_file "$foundation"
require_file "$foundation_index"
require_file "$status_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$installer_readme"
require_file "$ui_model"
require_file "$components_manifest"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$invocation_script"
require_file "$stage30_guard"
require_file "$workflow"
require_file "$makefile"

require_contains 'Status: Stage-30 implementation contract' "$stage30_doc"
require_contains 'nadia_stage_30_prompt_evaluation_invocation_contract_present=1' "$stage30_doc"
require_contains 'prompt_evaluation_invocation_contract_command=scripts/nadia-prompt-evaluation-invocation-contract.sh' "$stage30_doc"
require_contains 'installed_prompt_evaluation_invocation_contract_command=latticra-nadia prompt-evaluation-invocation' "$stage30_doc"
require_contains 'prompt_evaluation_invocation_contract_status=contract_only' "$stage30_doc"
require_contains 'prompt_evaluation_invocation_authority=0' "$stage30_doc"
require_contains 'requires_prompt_evaluation_runtime_handoff_contract=1' "$stage30_doc"
require_contains 'requires_future_prompt_evaluation_result_contract=1' "$stage30_doc"
require_contains 'prompt_evaluation_invocation_request_created=0' "$stage30_doc"
require_contains 'prompt_evaluation_invocation_request_submitted=0' "$stage30_doc"
require_contains 'runtime_invoked=0' "$stage30_doc"
require_contains 'prompt_evaluated=0' "$stage30_doc"
require_contains 'token_generation_performed=0' "$stage30_doc"
require_contains 'inference_performed=0' "$stage30_doc"
require_contains 'sh scripts/test-nadia-prompt-evaluation-invocation-contract-stage-30.sh' "$stage30_doc"

require_contains 'Status: implementation status record' "$stage30_status"
require_contains 'nadia_stage_30_prompt_evaluation_invocation_contract_present=1' "$stage30_status"
require_contains 'nadia_prompt_evaluation_invocation_contract_generator_present=1' "$stage30_status"
require_contains 'prompt_evaluation_invocation_contract_status=contract_only' "$stage30_status"
require_contains 'prompt_evaluation_invocation_promotion_allowed=0' "$stage30_status"
require_contains 'prompt_evaluation_invocation_request_created=0' "$stage30_status"
require_contains 'runtime_invoked=0' "$stage30_status"
require_contains 'prompt_evaluated=0' "$stage30_status"
require_contains 'token_generation_performed=0' "$stage30_status"
require_contains 'inference_performed=0' "$stage30_status"
require_contains 'prompt-evaluation result contract' "$stage30_status"
require_contains 'Stage-31 now defines a prompt-evaluation result contract' "$stage30_status"

require_contains 'Stage-30: Prompt Evaluation Invocation Contract' "$foundation"
require_contains 'NADIA_PROMPT_EVALUATION_INVOCATION_CONTRACT_STAGE_30.md' "$foundation_index"
require_contains 'NADIA_PROMPT_EVALUATION_INVOCATION_CONTRACT_STAGE_30_STATUS.md' "$status_index"
require_contains 'prompt-evaluation invocation contract' "$stage29_status"
require_contains 'Nadia prompt evaluation invocation contract Stage-30 + guardrails' "$foundation_index"
require_contains 'nadia_stage_30_prompt_evaluation_invocation_contract_present=1' "$readme"
require_contains 'latticra-nadia prompt-evaluation-invocation' "$readme"
require_contains '| Nadia offline AI foundation | 72% |' "$readme"
require_contains 'Latest Nadia prompt evaluation invocation contract Stage-30 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia prompt evaluation invocation contract Stage-30 note: 2026-05-25 CDT' "$current_status"
require_contains '| Nadia offline AI foundation | 72% |' "$root_status"
require_contains '| Nadia offline AI foundation | 72% |' "$current_status"
require_contains 'Nadia prompt evaluation invocation contract Stage-30' "$current_status"
require_contains 'latticra-nadia prompt-evaluation-invocation' "$installer_readme"
require_contains 'prompt-evaluation invocation request creation' "$installer_readme"
require_contains 'nadia prompt-evaluation-invocation' "$ui_model"
require_contains 'Stage-31, Stage-32, Stage-33, Stage-34, Stage-35, Stage-36, Stage-37, and Stage-38 console surfaces are metadata-only' "$ui_model"
require_contains 'share/latticra/nadia/prompt-evaluation-invocation' "$components_manifest"
require_contains 'prompt-evaluation invocation request creation' "$components_manifest"
require_contains 'prompt-evaluation-invocation metadata records future prompt evaluation result requirements' "$components_manifest"
require_contains 'scripts/nadia-prompt-evaluation-invocation-contract.sh' "$apply_script"
require_contains 'prompt_evaluation_invocation_contract_stage=30-prompt-evaluation-invocation-contract' "$apply_script"
require_contains 'prompt_evaluation_invocation_request_created=0' "$apply_script"
require_contains 'stage=38-prompt-evaluation-result-release-receipt-review-disposition-release-contract' "$apply_script"
require_contains 'stage=38-prompt-evaluation-result-release-receipt-review-disposition-release-contract' "$panel_config"
require_contains 'prompt_evaluation_invocation_contract_stage=30-prompt-evaluation-invocation-contract' "$panel_config"
require_contains 'nadia prompt-evaluation-invocation' "$panel_ui"
require_contains 'nadia_prompt_evaluation_invocation=stage-30-prompt-evaluation-invocation-contract' "$panel_ui"
require_contains 'nadia-prompt-evaluation-invocation' "$makefile"
require_contains 'sh ./scripts/nadia-prompt-evaluation-invocation-contract.sh' "$makefile"
require_contains 'sh scripts/test-nadia-prompt-evaluation-invocation-contract-stage-30.sh' "$workflow"

require_contains 'NADIA PROMPT EVALUATION INVOCATION CONTRACT' "$invocation_script"
require_contains 'prompt_evaluation_invocation_contract_status=contract_only' "$invocation_script"
require_contains 'requires_prompt_evaluation_runtime_handoff_contract=1' "$invocation_script"
require_contains 'requires_future_prompt_evaluation_result_contract=1' "$invocation_script"
require_contains 'prompt_evaluation_invocation_request_created=0' "$invocation_script"
require_contains 'prompt_evaluation_invocation_request_submitted=0' "$invocation_script"
require_contains 'runtime_invoked=0' "$invocation_script"
require_contains 'prompt_evaluated=0' "$invocation_script"
require_contains 'token_generation_performed=0' "$invocation_script"
require_contains 'inference_performed=0' "$invocation_script"
require_contains 'outside Nadia prompt-evaluation-invocation boundary' "$invocation_script"

tmp_root="${TMPDIR:-/tmp}"
tmp_root="${tmp_root%/}"
tmpdir=$(mktemp -d "$tmp_root/latticra-nadia-stage30-invocation-test.XXXXXX")
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

handoff="$tmpdir/prompt-evaluation-runtime-handoff-stage29-fixture.txt"
out="$tmpdir/out"
mkdir -p "$out"

cat > "$handoff" <<'EOF_HANDOFF'
NADIA PROMPT EVALUATION RUNTIME HANDOFF CONTRACT
stage=29-prompt-evaluation-runtime-handoff-contract
prompt_evaluation_runtime_handoff_contract_status=contract_only
prompt_evaluation_runtime_handoff_stage=contract-only
prompt_evaluation_runtime_handoff_authority=0
prompt_evaluation_runtime_handoff_allowed=0
prompt_evaluation_runtime_handoff_performed=0
prompt_evaluation_runtime_handoff_metadata_present=1
prompt_evaluation_runtime_handoff_family=operator-reviewed-prompt-evaluation-runtime-handoff
prompt_evaluation_runtime_handoff_format=contract-only-offline-runtime-handoff
prompt_evaluation_runtime_handoff_decision=blocked_contract_only
prompt_evaluation_runtime_handoff_evidence_present=1
prompt_evaluation_runtime_handoff_source_policy=operator-reviewed-offline
prompt_evaluation_runtime_handoff_plan_recorded=1
prompt_evaluation_runtime_handoff_result_recorded=0
prompt_evaluation_runtime_handoff_runtime_invoked=0
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
requires_future_prompt_evaluation_invocation_contract=1
prompt_evaluation_runtime_handoff_promotion_allowed=0
requires_prompt_evaluation_input_reference=1
requires_prompt_evaluation_input_schema_policy=1
requires_prompt_evaluation_input_safety_envelope_policy=1
requires_context_window_assembly_reference=1
requires_prompt_token_sequence_reference=1
requires_prompt_tokenization_reference=1
requires_runtime_profile_reference=1
requires_runtime_invocation_contract_reference=1
requires_model_load_contract_reference=1
requires_inference_readiness_contract_reference=1
requires_runtime_handoff_schema_policy=1
requires_runtime_handoff_denial_policy=1
requires_prompt_evaluation_invocation_policy=1
requires_token_generation_denial_policy=1
requires_operator_approval_record=1
requires_official_source_snapshot=1
requires_no_prompt_evaluation_runtime_handoff=1
requires_no_runtime_invocation=1
requires_no_prompt_evaluation=1
requires_no_dialogue_generation=1
requires_no_token_generation=1
requires_no_inference=1
requires_refusal_policy_link=1
requires_survivor_centered_language_review=1
prompt_evaluation_runtime_handoff_request_created=0
prompt_evaluation_runtime_handoff_request_validated=0
prompt_evaluation_runtime_handoff_request_serialized=0
prompt_evaluation_runtime_handoff_request_written=0
prompt_evaluation_runtime_handoff_request_submitted=0
prompt_evaluation_runtime_handoff_runtime_selected=0
prompt_evaluation_runtime_handoff_model_selected=0
prompt_evaluation_runtime_handoff_session_created=0
runtime_handoff_created=0
runtime_handoff_submitted=0
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
future_qa_dialogue_capability_planned=1
qa_dialogue_generated=0
q_and_a_format_required=1
survivor_centered_dialogue_required=1
official_source_grounding_required=1
live_web_lookup_authority=0
sexual_user_request_authority=0
sexual_content_generation=0
sexualized_dialogue_generation=0
graphic_sexual_detail_allowed=0
erotic_content_allowed=0
roleplay_allowed=0
survivor_impersonation_allowed=0
victim_blaming_allowed=0
genocide_denial_allowed=0
sexual_request_refusal=always
manipulation_resistance=required
network_authority=0
tool_execution_authority=0
tool_execution_performed=0
source_mutation_authority=0
self_modification_authority=0
training_performed=0
distillation_performed=0
prompt_evaluation_input_stage=contract-only
context_window_assembly_stage=contract-only
prompt_token_sequence_stage=contract-only
prompt_tokenization_stage=contract-only
tokenizer_runtime_attachment_stage=contract-only
EOF_HANDOFF

NADIA_PROMPT_EVALUATION_INVOCATION_TIMESTAMP=stage30-test sh "$invocation_script" \
  --prompt-evaluation-runtime-handoff "$handoff" \
  --request-class awareness-education \
  --invocation-family operator-reviewed-prompt-evaluation-invocation \
  --invocation-format contract-only-offline-evaluation-invocation \
  --output "$out" > "$tmpdir/stdout.txt"

report="$out/nadia-prompt-evaluation-invocation-contract-stage30-test.txt"
require_file "$report"
require_file "$out/latest-prompt-evaluation-invocation-contract.txt"
require_contains 'NADIA PROMPT EVALUATION INVOCATION CONTRACT' "$report"
require_contains 'stage=30-prompt-evaluation-invocation-contract' "$report"
require_contains 'prompt_evaluation_invocation_contract_status=contract_only' "$report"
require_contains 'prompt_evaluation_invocation_authority=0' "$report"
require_contains 'prompt_evaluation_invocation_performed=0' "$report"
require_contains 'requires_prompt_evaluation_runtime_handoff_contract=1' "$report"
require_contains 'requires_future_prompt_evaluation_result_contract=1' "$report"
require_contains 'prompt_evaluation_invocation_promotion_allowed=0' "$report"
require_contains 'prompt_evaluation_invocation_request_created=0' "$report"
require_contains 'prompt_evaluation_invocation_request_submitted=0' "$report"
require_contains 'runtime_invoked=0' "$report"
require_contains 'runtime_session_created=0' "$report"
require_contains 'prompt_evaluated=0' "$report"
require_contains 'token_generation_performed=0' "$report"
require_contains 'inference_performed=0' "$report"
require_contains 'qa_dialogue_generated=0' "$report"
require_contains 'sexual_request_refusal=always' "$report"
require_contains 'manipulation_resistance=required' "$report"
require_contains 'network_authority=0' "$report"
require_contains 'tool_execution_performed=0' "$report"
require_contains 'source_mutation_authority=0' "$report"

if sh "$invocation_script" \
  --prompt-evaluation-runtime-handoff "$handoff" \
  --request-class sexual-content \
  --output "$out" > "$tmpdir/boundary.out" 2>&1; then
  printf 'nadia prompt evaluation invocation contract stage 30: sexual boundary label was accepted\n' >&2
  exit 1
fi
require_contains 'outside Nadia prompt-evaluation-invocation boundary' "$tmpdir/boundary.out"

printf 'nadia_prompt_evaluation_invocation_contract_stage_30: ok\n'
