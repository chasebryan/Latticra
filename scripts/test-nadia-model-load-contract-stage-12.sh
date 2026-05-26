#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia model load contract stage 12: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia model load contract stage 12: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'nadia model load contract stage 12: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage12_doc='docs/NADIA_MODEL_LOAD_CONTRACT_STAGE_12.md'
stage12_status='docs/status/NADIA_MODEL_LOAD_CONTRACT_STAGE_12_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
status_index='docs/status/README.md'
foundation_index='docs/FOUNDATION_INDEX.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
model_load_script='scripts/nadia-model-load-contract.sh'
stage12_guard='scripts/test-nadia-model-load-contract-stage-12.sh'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
makefile='Makefile'

require_file "$stage12_doc"
require_file "$stage12_status"
require_file "$foundation"
require_file "$status_index"
require_file "$foundation_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$model_load_script"
require_file "$stage12_guard"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$installer_readme"
require_file "$ui_model"
require_file "$components_manifest"
require_file "$makefile"

require_contains 'Status: Stage-12 implementation contract' "$stage12_doc"
require_contains 'nadia_stage_12_model_load_contract_present=1' "$stage12_doc"
require_contains 'model_load_contract_command=scripts/nadia-model-load-contract.sh' "$stage12_doc"
require_contains 'installed_model_load_contract_command=latticra-nadia model-load' "$stage12_doc"
require_contains 'model_load_authority=0' "$stage12_doc"
require_contains 'model_load_allowed=0' "$stage12_doc"
require_contains 'model_loaded=0' "$stage12_doc"
require_contains 'load_decision=blocked_contract_only' "$stage12_doc"
require_contains 'model_file_opened=0' "$stage12_doc"
require_contains 'model_weights_mapped=0' "$stage12_doc"
require_contains 'model_weights_loaded=0' "$stage12_doc"
require_contains 'model_load_performed=0' "$stage12_doc"
require_contains 'sh scripts/test-nadia-model-load-contract-stage-12.sh' "$stage12_doc"

require_contains 'Status: implementation status record' "$stage12_status"
require_contains 'nadia_model_load_contract_generator_present=1' "$stage12_status"
require_contains 'model_load_contract_status=contract_only' "$stage12_status"
require_contains 'load_promotion_allowed=0' "$stage12_status"

require_contains 'Stage-12: Model Load Contract' "$foundation"
require_contains 'scripts/nadia-model-load-contract.sh' "$foundation"
require_contains 'NADIA_MODEL_LOAD_CONTRACT_STAGE_12.md' "$foundation_index"
require_contains 'NADIA_MODEL_LOAD_CONTRACT_STAGE_12_STATUS.md' "$status_index"
require_contains 'nadia_stage_12_model_load_contract_present=1' "$readme"
require_contains 'implementation_name=Nadia Witness Foundation' "$readme"
require_contains 'Latest Nadia model load contract Stage-12 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia model load contract Stage-12 note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia model load contract Stage-12' "$current_status"

require_contains 'NADIA MODEL LOAD CONTRACT' "$model_load_script"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$model_load_script"
require_contains 'public_name=Nadia' "$model_load_script"
require_contains 'model_load_authority=0' "$model_load_script"
require_contains 'model_load_allowed=0' "$model_load_script"
require_contains 'model_loaded=0' "$model_load_script"
require_contains 'model_file_opened=0' "$model_load_script"
require_contains 'model_memory_map_created=0' "$model_load_script"
require_contains 'model_weights_mapped=0' "$model_load_script"
require_contains 'model_weights_loaded=0' "$model_load_script"
require_contains 'model_load_performed=0' "$model_load_script"
require_contains 'token_generation_authority=0' "$model_load_script"
require_contains 'token_generation_performed=0' "$model_load_script"
require_contains 'inference_performed=0' "$model_load_script"
require_contains 'sexual_request_refusal=always' "$model_load_script"
require_not_contains 'curl ' "$model_load_script"
require_not_contains 'wget ' "$model_load_script"
require_not_contains 'ssh ' "$model_load_script"

require_contains 'model-load' "$apply_script"
require_contains 'scripts/nadia-model-load-contract.sh' "$apply_script"
require_contains 'model_load_contract_stage=12-model-load-contract' "$panel_config"
require_contains 'nadia model-load' "$panel_ui"
require_contains 'latticra-nadia model-load' "$installer_readme"
require_contains 'nadia model-load' "$ui_model"
require_contains 'model-load' "$components_manifest"
require_contains 'nadia-model-load' "$makefile"

out="${TMPDIR:-/tmp}/latticra-nadia-stage12-load-test"
context_out="${TMPDIR:-/tmp}/latticra-nadia-stage12-context-test"
runtime_out="${TMPDIR:-/tmp}/latticra-nadia-stage12-runtime-test"
plan_out="${TMPDIR:-/tmp}/latticra-nadia-stage12-plan-test"
mode_out="${TMPDIR:-/tmp}/latticra-nadia-stage12-mode-test"
ledger_out="${TMPDIR:-/tmp}/latticra-nadia-stage12-ledger-test"
safety_out="${TMPDIR:-/tmp}/latticra-nadia-stage12-safety-test"
tool_out="${TMPDIR:-/tmp}/latticra-nadia-stage12-tool-test"
contract_out="${TMPDIR:-/tmp}/latticra-nadia-stage12-contract-test"
registry_out="${TMPDIR:-/tmp}/latticra-nadia-stage12-registry-test"
readiness_out="${TMPDIR:-/tmp}/latticra-nadia-stage12-readiness-test"
invocation_out="${TMPDIR:-/tmp}/latticra-nadia-stage12-invocation-test"
rm -rf "$out" "$context_out" "$runtime_out" "$plan_out" "$mode_out" "$ledger_out" "$safety_out" "$tool_out" "$contract_out" "$registry_out" "$readiness_out" "$invocation_out"
mkdir -p "$out" "$context_out" "$runtime_out" "$plan_out" "$mode_out" "$ledger_out" "$safety_out" "$tool_out" "$contract_out" "$registry_out" "$readiness_out" "$invocation_out"
NADIA_CONTEXT_PACK_TIMESTAMP=stage12-test sh scripts/nadia-context-pack.sh --repo . --output "$context_out" >/tmp/latticra-nadia-stage12-context-test.out
NADIA_RUNTIME_PROFILE_TIMESTAMP=stage12-test sh scripts/nadia-runtime-profile.sh \
  --context-tokens 8192 \
  --memory-mib 16384 \
  --output "$runtime_out" >/tmp/latticra-nadia-stage12-runtime-test.out
NADIA_PROMPT_PLAN_TIMESTAMP=stage12-test sh scripts/nadia-prompt-plan.sh \
  --context-pack "$context_out/nadia-context-pack-stage12-test.txt" \
  --runtime-profile "$runtime_out/nadia-runtime-profile-stage12-test.txt" \
  --task "model load contract planning" \
  --output "$plan_out" >/tmp/latticra-nadia-stage12-plan-test.out
NADIA_MODE_VALIDATION_TIMESTAMP=stage12-test sh scripts/nadia-mode-validate.sh \
  --prompt-plan "$plan_out/nadia-prompt-plan-stage12-test.txt" \
  --mode ai-development \
  --output "$mode_out" >/tmp/latticra-nadia-stage12-mode-test.out
NADIA_PRODUCTIVITY_LEDGER_TIMESTAMP=stage12-test sh scripts/nadia-productivity-ledger.sh \
  --mode-validation "$mode_out/nadia-mode-validation-stage12-test.txt" \
  --outcome "accepted model load boundary" \
  --recommendation "keep model load contract-only" \
  --output "$ledger_out" >/tmp/latticra-nadia-stage12-ledger-test.out
NADIA_PROTECTIVE_SAFETY_TIMESTAMP=stage12-test sh scripts/nadia-protective-safety-boundary.sh \
  --productivity-entry "$ledger_out/nadia-productivity-entry-stage12-test.txt" \
  --request-class software-development \
  --output "$safety_out" >/tmp/latticra-nadia-stage12-safety-test.out
NADIA_TOOL_PREFLIGHT_TIMESTAMP=stage12-test sh scripts/nadia-tool-authority-preflight.sh \
  --protective-safety "$safety_out/nadia-protective-safety-stage12-test.txt" \
  --tool-class metadata-read \
  --action "prepare model load contract evidence" \
  --output "$tool_out" >/tmp/latticra-nadia-stage12-tool-test.out
NADIA_PROMPT_CONTRACT_TIMESTAMP=stage12-test sh scripts/nadia-prompt-evaluation-contract.sh \
  --tool-preflight "$tool_out/nadia-tool-preflight-stage12-test.txt" \
  --request-class software-development \
  --output "$contract_out" >/tmp/latticra-nadia-stage12-contract-test.out
NADIA_MODEL_REGISTRY_TIMESTAMP=stage12-test sh scripts/nadia-local-model-registry-contract.sh \
  --prompt-contract "$contract_out/nadia-prompt-contract-stage12-test.txt" \
  --runtime-profile "$runtime_out/nadia-runtime-profile-stage12-test.txt" \
  --model-id local-coding-assistant-candidate \
  --quantization q4_k_m \
  --source operator-provided-local \
  --license operator-review-required \
  --output "$registry_out" >/tmp/latticra-nadia-stage12-registry-test.out
NADIA_INFERENCE_READINESS_TIMESTAMP=stage12-test sh scripts/nadia-inference-readiness-contract.sh \
  --model-registry "$registry_out/nadia-model-registry-contract-stage12-test.txt" \
  --request-class software-development \
  --output "$readiness_out" >/tmp/latticra-nadia-stage12-readiness-test.out
NADIA_RUNTIME_INVOCATION_TIMESTAMP=stage12-test sh scripts/nadia-runtime-invocation-contract.sh \
  --inference-readiness "$readiness_out/nadia-inference-readiness-contract-stage12-test.txt" \
  --request-class software-development \
  --output "$invocation_out" >/tmp/latticra-nadia-stage12-invocation-test.out
NADIA_MODEL_LOAD_TIMESTAMP=stage12-test sh "$model_load_script" \
  --runtime-invocation "$invocation_out/nadia-runtime-invocation-contract-stage12-test.txt" \
  --request-class software-development \
  --output "$out" >/tmp/latticra-nadia-stage12-load-test.out
load="$out/nadia-model-load-contract-stage12-test.txt"

require_file "$load"
require_file "$out/latest-model-load-contract.txt"
require_contains 'NADIA MODEL LOAD CONTRACT' "$load"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$load"
require_contains 'public_name=Nadia' "$load"
require_contains 'stage=12-model-load-contract' "$load"
require_contains 'request_class=software-development' "$load"
require_contains 'model_load_contract_status=contract_only' "$load"
require_contains 'model_load_stage=contract-only' "$load"
require_contains 'model_load_authority=0' "$load"
require_contains 'model_load_allowed=0' "$load"
require_contains 'model_loaded=0' "$load"
require_contains 'runtime_invocation_stage=11-runtime-invocation-contract' "$load"
require_contains 'model_registry_stage=9-local-model-registry-contract' "$load"
require_contains 'model_id=local-coding-assistant-candidate' "$load"
require_contains 'load_decision=blocked_contract_only' "$load"
require_contains 'requires_runtime_invocation_contract=1' "$load"
require_contains 'requires_inference_readiness_contract=1' "$load"
require_contains 'requires_model_registry_contract=1' "$load"
require_contains 'requires_prompt_contract=1' "$load"
require_contains 'requires_future_prompt_receipt_contract=1' "$load"
require_contains 'load_promotion_allowed=0' "$load"
require_contains 'model_file_open_authority=0' "$load"
require_contains 'model_weight_read_authority=0' "$load"
require_contains 'model_weight_mapping_authority=0' "$load"
require_contains 'model_weight_verification_authority=0' "$load"
require_contains 'runtime_model_attach_authority=0' "$load"
require_contains 'model_file_opened=0' "$load"
require_contains 'model_file_descriptor_opened=0' "$load"
require_contains 'model_memory_map_created=0' "$load"
require_contains 'model_weights_mapped=0' "$load"
require_contains 'model_weights_loaded=0' "$load"
require_contains 'model_weights_attached=0' "$load"
require_contains 'model_weight_measurement_performed=0' "$load"
require_contains 'model_weight_verification_performed=0' "$load"
require_contains 'model_load_performed=0' "$load"
require_contains 'runtime_process_spawned=0' "$load"
require_contains 'runtime_session_created=0' "$load"
require_contains 'token_generation_performed=0' "$load"
require_contains 'candidate_usable_for_inference=0' "$load"
require_contains 'candidate_selected_for_runtime=0' "$load"
require_contains 'model_selection_authority=0' "$load"
require_contains 'sexual_content_generation=0' "$load"
require_contains 'sexual_request_refusal=always' "$load"
require_contains 'prompt_materialized=0' "$load"
require_contains 'prompt_evaluation_authority=0' "$load"
require_contains 'prompt_evaluated=0' "$load"
require_contains 'model_runtime_invoked=0' "$load"
require_contains 'inference_authority=0' "$load"
require_contains 'inference_performed=0' "$load"
require_contains 'tool_execution_authority=0' "$load"
require_contains 'network_authority=0' "$load"

if NADIA_MODEL_LOAD_TIMESTAMP=stage12-reject sh "$model_load_script" \
  --runtime-invocation "$invocation_out/nadia-runtime-invocation-contract-stage12-test.txt" \
  --request-class sexual \
  --output "$out" >/tmp/latticra-nadia-stage12-reject-test.out 2>/tmp/latticra-nadia-stage12-reject-test.err; then
  printf 'nadia model load contract stage 12: sexual request class was not rejected\n' >&2
  exit 1
fi
require_contains 'outside Nadia model-load boundary' /tmp/latticra-nadia-stage12-reject-test.err

printf 'nadia_model_load_contract_stage_12: ok\n'
