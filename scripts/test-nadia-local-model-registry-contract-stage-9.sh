#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia local model registry contract stage 9: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia local model registry contract stage 9: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'nadia local model registry contract stage 9: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage9_doc='docs/NADIA_LOCAL_MODEL_REGISTRY_CONTRACT_STAGE_9.md'
stage9_status='docs/status/NADIA_LOCAL_MODEL_REGISTRY_CONTRACT_STAGE_9_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
status_index='docs/status/README.md'
foundation_index='docs/FOUNDATION_INDEX.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
registry_script='scripts/nadia-local-model-registry-contract.sh'
stage9_guard='scripts/test-nadia-local-model-registry-contract-stage-9.sh'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
makefile='Makefile'

require_file "$stage9_doc"
require_file "$stage9_status"
require_file "$foundation"
require_file "$status_index"
require_file "$foundation_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$registry_script"
require_file "$stage9_guard"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$installer_readme"
require_file "$ui_model"
require_file "$components_manifest"
require_file "$makefile"

require_contains 'Status: Stage-9 implementation contract' "$stage9_doc"
require_contains 'nadia_stage_9_local_model_registry_contract_present=1' "$stage9_doc"
require_contains 'model_registry_contract_command=scripts/nadia-local-model-registry-contract.sh' "$stage9_doc"
require_contains 'installed_model_registry_contract_command=latticra-nadia model-registry' "$stage9_doc"
require_contains 'model_registry_authority=0' "$stage9_doc"
require_contains 'candidate_review_status=operator_review_required' "$stage9_doc"
require_contains 'model_selection_authority=0' "$stage9_doc"
require_contains 'model_runtime_invoked=0' "$stage9_doc"
require_contains 'model_weights_loaded=0' "$stage9_doc"
require_contains 'sh scripts/test-nadia-local-model-registry-contract-stage-9.sh' "$stage9_doc"

require_contains 'Status: implementation status record' "$stage9_status"
require_contains 'nadia_model_registry_contract_generator_present=1' "$stage9_status"
require_contains 'registry_contract_status=metadata_only' "$stage9_status"
require_contains 'registry_promotion_allowed=0' "$stage9_status"

require_contains 'Stage-9: Local Model Registry Contract' "$foundation"
require_contains 'scripts/nadia-local-model-registry-contract.sh' "$foundation"
require_contains 'NADIA_LOCAL_MODEL_REGISTRY_CONTRACT_STAGE_9.md' "$foundation_index"
require_contains 'NADIA_LOCAL_MODEL_REGISTRY_CONTRACT_STAGE_9_STATUS.md' "$status_index"
require_contains 'nadia_stage_9_local_model_registry_contract_present=1' "$readme"
require_contains 'Latest Nadia local model registry contract Stage-9 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia local model registry contract Stage-9 note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia local model registry contract Stage-9' "$current_status"

require_contains 'NADIA LOCAL MODEL REGISTRY CONTRACT' "$registry_script"
require_contains 'model_registry_authority=0' "$registry_script"
require_contains 'model_selection_authority=0' "$registry_script"
require_contains 'model_install_authority=0' "$registry_script"
require_contains 'model_runtime_invoked=0' "$registry_script"
require_contains 'inference_performed=0' "$registry_script"
require_contains 'model_weights_loaded=0' "$registry_script"
require_contains 'model_weights_downloaded=0' "$registry_script"
require_contains 'sexual_request_refusal=always' "$registry_script"
require_not_contains 'curl ' "$registry_script"
require_not_contains 'wget ' "$registry_script"
require_not_contains 'ssh ' "$registry_script"

require_contains 'model-registry' "$apply_script"
require_contains 'scripts/nadia-local-model-registry-contract.sh' "$apply_script"
require_contains 'local_model_registry_contract_stage=9-local-model-registry-contract' "$panel_config"
require_contains 'nadia model-registry' "$panel_ui"
require_contains 'latticra-nadia model-registry' "$installer_readme"
require_contains 'nadia model-registry' "$ui_model"
require_contains 'model-registry' "$components_manifest"
require_contains 'nadia-model-registry' "$makefile"

out="${TMPDIR:-/tmp}/latticra-nadia-stage9-registry-test"
context_out="${TMPDIR:-/tmp}/latticra-nadia-stage9-context-test"
runtime_out="${TMPDIR:-/tmp}/latticra-nadia-stage9-runtime-test"
plan_out="${TMPDIR:-/tmp}/latticra-nadia-stage9-plan-test"
mode_out="${TMPDIR:-/tmp}/latticra-nadia-stage9-mode-test"
ledger_out="${TMPDIR:-/tmp}/latticra-nadia-stage9-ledger-test"
safety_out="${TMPDIR:-/tmp}/latticra-nadia-stage9-safety-test"
tool_out="${TMPDIR:-/tmp}/latticra-nadia-stage9-tool-test"
contract_out="${TMPDIR:-/tmp}/latticra-nadia-stage9-contract-test"
rm -rf "$out" "$context_out" "$runtime_out" "$plan_out" "$mode_out" "$ledger_out" "$safety_out" "$tool_out" "$contract_out"
mkdir -p "$out" "$context_out" "$runtime_out" "$plan_out" "$mode_out" "$ledger_out" "$safety_out" "$tool_out" "$contract_out"
NADIA_CONTEXT_PACK_TIMESTAMP=stage9-test sh scripts/nadia-context-pack.sh --repo . --output "$context_out" >/tmp/latticra-nadia-stage9-context-test.out
NADIA_RUNTIME_PROFILE_TIMESTAMP=stage9-test sh scripts/nadia-runtime-profile.sh \
  --context-tokens 8192 \
  --memory-mib 16384 \
  --output "$runtime_out" >/tmp/latticra-nadia-stage9-runtime-test.out
NADIA_PROMPT_PLAN_TIMESTAMP=stage9-test sh scripts/nadia-prompt-plan.sh \
  --context-pack "$context_out/nadia-context-pack-stage9-test.txt" \
  --runtime-profile "$runtime_out/nadia-runtime-profile-stage9-test.txt" \
  --task "local model registry contract planning" \
  --output "$plan_out" >/tmp/latticra-nadia-stage9-plan-test.out
NADIA_MODE_VALIDATION_TIMESTAMP=stage9-test sh scripts/nadia-mode-validate.sh \
  --prompt-plan "$plan_out/nadia-prompt-plan-stage9-test.txt" \
  --mode ai-development \
  --output "$mode_out" >/tmp/latticra-nadia-stage9-mode-test.out
NADIA_PRODUCTIVITY_LEDGER_TIMESTAMP=stage9-test sh scripts/nadia-productivity-ledger.sh \
  --mode-validation "$mode_out/nadia-mode-validation-stage9-test.txt" \
  --outcome "accepted local model registry boundary" \
  --recommendation "keep registry metadata-only" \
  --output "$ledger_out" >/tmp/latticra-nadia-stage9-ledger-test.out
NADIA_PROTECTIVE_SAFETY_TIMESTAMP=stage9-test sh scripts/nadia-protective-safety-boundary.sh \
  --productivity-entry "$ledger_out/nadia-productivity-entry-stage9-test.txt" \
  --request-class software-development \
  --output "$safety_out" >/tmp/latticra-nadia-stage9-safety-test.out
NADIA_TOOL_PREFLIGHT_TIMESTAMP=stage9-test sh scripts/nadia-tool-authority-preflight.sh \
  --protective-safety "$safety_out/nadia-protective-safety-stage9-test.txt" \
  --tool-class metadata-read \
  --action "prepare model registry contract evidence" \
  --output "$tool_out" >/tmp/latticra-nadia-stage9-tool-test.out
NADIA_PROMPT_CONTRACT_TIMESTAMP=stage9-test sh scripts/nadia-prompt-evaluation-contract.sh \
  --tool-preflight "$tool_out/nadia-tool-preflight-stage9-test.txt" \
  --request-class software-development \
  --output "$contract_out" >/tmp/latticra-nadia-stage9-contract-test.out
NADIA_MODEL_REGISTRY_TIMESTAMP=stage9-test sh "$registry_script" \
  --prompt-contract "$contract_out/nadia-prompt-contract-stage9-test.txt" \
  --runtime-profile "$runtime_out/nadia-runtime-profile-stage9-test.txt" \
  --model-id local-coding-assistant-candidate \
  --quantization q4_k_m \
  --source operator-provided-local \
  --license operator-review-required \
  --output "$out" >/tmp/latticra-nadia-stage9-registry-test.out
registry="$out/nadia-model-registry-contract-stage9-test.txt"

require_file "$registry"
require_file "$out/latest-model-registry-contract.txt"
require_contains 'NADIA LOCAL MODEL REGISTRY CONTRACT' "$registry"
require_contains 'stage=9-local-model-registry-contract' "$registry"
require_contains 'registry_contract_status=metadata_only' "$registry"
require_contains 'model_registry_authority=0' "$registry"
require_contains 'prompt_contract_stage=8-prompt-evaluation-contract' "$registry"
require_contains 'runtime_profile_stage=2-runtime-profile-boundary' "$registry"
require_contains 'model_id=local-coding-assistant-candidate' "$registry"
require_contains 'model_format=gguf' "$registry"
require_contains 'quantization=q4_k_m' "$registry"
require_contains 'context_window_tokens=8192' "$registry"
require_contains 'memory_budget_mib=16384' "$registry"
require_contains 'candidate_recorded=1' "$registry"
require_contains 'candidate_review_status=operator_review_required' "$registry"
require_contains 'candidate_usable_for_inference=0' "$registry"
require_contains 'model_selection_authority=0' "$registry"
require_contains 'model_install_authority=0' "$registry"
require_contains 'model_download_authority=0' "$registry"
require_contains 'model_load_authority=0' "$registry"
require_contains 'model_weight_inspection_authority=0' "$registry"
require_contains 'registry_promotion_allowed=0' "$registry"
require_contains 'sexual_content_generation=0' "$registry"
require_contains 'sexual_request_refusal=always' "$registry"
require_contains 'prompt_evaluation_authority=0' "$registry"
require_contains 'prompt_evaluated=0' "$registry"
require_contains 'model_runtime_invoked=0' "$registry"
require_contains 'inference_performed=0' "$registry"
require_contains 'model_weights_installed=0' "$registry"
require_contains 'model_weights_loaded=0' "$registry"
require_contains 'model_weights_downloaded=0' "$registry"
require_contains 'tool_execution_authority=0' "$registry"
require_contains 'network_authority=0' "$registry"

if NADIA_MODEL_REGISTRY_TIMESTAMP=stage9-reject sh "$registry_script" \
  --prompt-contract "$contract_out/nadia-prompt-contract-stage9-test.txt" \
  --runtime-profile "$runtime_out/nadia-runtime-profile-stage9-test.txt" \
  --model-id sexual-model-candidate \
  --output "$out" >/tmp/latticra-nadia-stage9-reject-test.out 2>/tmp/latticra-nadia-stage9-reject-test.err; then
  printf 'nadia local model registry contract stage 9: sexual model label was not rejected\n' >&2
  exit 1
fi
require_contains 'outside Nadia local model-registry boundary' /tmp/latticra-nadia-stage9-reject-test.err

printf 'nadia_local_model_registry_contract_stage_9: ok\n'
