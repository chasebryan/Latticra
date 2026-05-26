#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia inference readiness contract stage 10: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia inference readiness contract stage 10: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'nadia inference readiness contract stage 10: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage10_doc='docs/NADIA_INFERENCE_READINESS_CONTRACT_STAGE_10.md'
stage10_status='docs/status/NADIA_INFERENCE_READINESS_CONTRACT_STAGE_10_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
status_index='docs/status/README.md'
foundation_index='docs/FOUNDATION_INDEX.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
readiness_script='scripts/nadia-inference-readiness-contract.sh'
stage10_guard='scripts/test-nadia-inference-readiness-contract-stage-10.sh'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
makefile='Makefile'

require_file "$stage10_doc"
require_file "$stage10_status"
require_file "$foundation"
require_file "$status_index"
require_file "$foundation_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$readiness_script"
require_file "$stage10_guard"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$installer_readme"
require_file "$ui_model"
require_file "$components_manifest"
require_file "$makefile"

require_contains 'Status: Stage-10 implementation contract' "$stage10_doc"
require_contains 'nadia_stage_10_inference_readiness_contract_present=1' "$stage10_doc"
require_contains 'inference_readiness_contract_command=scripts/nadia-inference-readiness-contract.sh' "$stage10_doc"
require_contains 'installed_inference_readiness_contract_command=latticra-nadia inference-readiness' "$stage10_doc"
require_contains 'inference_readiness_authority=0' "$stage10_doc"
require_contains 'inference_ready=0' "$stage10_doc"
require_contains 'readiness_decision=blocked_contract_only' "$stage10_doc"
require_contains 'runtime_invocation_authority=0' "$stage10_doc"
require_contains 'model_runtime_invoked=0' "$stage10_doc"
require_contains 'model_weights_loaded=0' "$stage10_doc"
require_contains 'sh scripts/test-nadia-inference-readiness-contract-stage-10.sh' "$stage10_doc"

require_contains 'Status: implementation status record' "$stage10_status"
require_contains 'nadia_inference_readiness_contract_generator_present=1' "$stage10_status"
require_contains 'inference_readiness_contract_status=contract_only' "$stage10_status"
require_contains 'readiness_promotion_allowed=0' "$stage10_status"

require_contains 'Stage-10: Inference Readiness Contract' "$foundation"
require_contains 'scripts/nadia-inference-readiness-contract.sh' "$foundation"
require_contains 'NADIA_INFERENCE_READINESS_CONTRACT_STAGE_10.md' "$foundation_index"
require_contains 'NADIA_INFERENCE_READINESS_CONTRACT_STAGE_10_STATUS.md' "$status_index"
require_contains 'nadia_stage_10_inference_readiness_contract_present=1' "$readme"
require_contains 'Latest Nadia inference readiness contract Stage-10 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia inference readiness contract Stage-10 note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia inference readiness contract Stage-10' "$current_status"

require_contains 'NADIA INFERENCE READINESS CONTRACT' "$readiness_script"
require_contains 'inference_readiness_authority=0' "$readiness_script"
require_contains 'inference_ready=0' "$readiness_script"
require_contains 'runtime_invocation_authority=0' "$readiness_script"
require_contains 'token_generation_authority=0' "$readiness_script"
require_contains 'model_runtime_invoked=0' "$readiness_script"
require_contains 'inference_performed=0' "$readiness_script"
require_contains 'model_weights_loaded=0' "$readiness_script"
require_contains 'sexual_request_refusal=always' "$readiness_script"
require_not_contains 'curl ' "$readiness_script"
require_not_contains 'wget ' "$readiness_script"
require_not_contains 'ssh ' "$readiness_script"

require_contains 'inference-readiness' "$apply_script"
require_contains 'scripts/nadia-inference-readiness-contract.sh' "$apply_script"
require_contains 'inference_readiness_contract_stage=10-inference-readiness-contract' "$panel_config"
require_contains 'nadia inference-readiness' "$panel_ui"
require_contains 'latticra-nadia inference-readiness' "$installer_readme"
require_contains 'nadia inference-readiness' "$ui_model"
require_contains 'inference-readiness' "$components_manifest"
require_contains 'nadia-inference-readiness' "$makefile"

out="${TMPDIR:-/tmp}/latticra-nadia-stage10-readiness-test"
context_out="${TMPDIR:-/tmp}/latticra-nadia-stage10-context-test"
runtime_out="${TMPDIR:-/tmp}/latticra-nadia-stage10-runtime-test"
plan_out="${TMPDIR:-/tmp}/latticra-nadia-stage10-plan-test"
mode_out="${TMPDIR:-/tmp}/latticra-nadia-stage10-mode-test"
ledger_out="${TMPDIR:-/tmp}/latticra-nadia-stage10-ledger-test"
safety_out="${TMPDIR:-/tmp}/latticra-nadia-stage10-safety-test"
tool_out="${TMPDIR:-/tmp}/latticra-nadia-stage10-tool-test"
contract_out="${TMPDIR:-/tmp}/latticra-nadia-stage10-contract-test"
registry_out="${TMPDIR:-/tmp}/latticra-nadia-stage10-registry-test"
rm -rf "$out" "$context_out" "$runtime_out" "$plan_out" "$mode_out" "$ledger_out" "$safety_out" "$tool_out" "$contract_out" "$registry_out"
mkdir -p "$out" "$context_out" "$runtime_out" "$plan_out" "$mode_out" "$ledger_out" "$safety_out" "$tool_out" "$contract_out" "$registry_out"
NADIA_CONTEXT_PACK_TIMESTAMP=stage10-test sh scripts/nadia-context-pack.sh --repo . --output "$context_out" >/tmp/latticra-nadia-stage10-context-test.out
NADIA_RUNTIME_PROFILE_TIMESTAMP=stage10-test sh scripts/nadia-runtime-profile.sh \
  --context-tokens 8192 \
  --memory-mib 16384 \
  --output "$runtime_out" >/tmp/latticra-nadia-stage10-runtime-test.out
NADIA_PROMPT_PLAN_TIMESTAMP=stage10-test sh scripts/nadia-prompt-plan.sh \
  --context-pack "$context_out/nadia-context-pack-stage10-test.txt" \
  --runtime-profile "$runtime_out/nadia-runtime-profile-stage10-test.txt" \
  --task "inference readiness contract planning" \
  --output "$plan_out" >/tmp/latticra-nadia-stage10-plan-test.out
NADIA_MODE_VALIDATION_TIMESTAMP=stage10-test sh scripts/nadia-mode-validate.sh \
  --prompt-plan "$plan_out/nadia-prompt-plan-stage10-test.txt" \
  --mode ai-development \
  --output "$mode_out" >/tmp/latticra-nadia-stage10-mode-test.out
NADIA_PRODUCTIVITY_LEDGER_TIMESTAMP=stage10-test sh scripts/nadia-productivity-ledger.sh \
  --mode-validation "$mode_out/nadia-mode-validation-stage10-test.txt" \
  --outcome "accepted inference readiness boundary" \
  --recommendation "keep readiness contract-only" \
  --output "$ledger_out" >/tmp/latticra-nadia-stage10-ledger-test.out
NADIA_PROTECTIVE_SAFETY_TIMESTAMP=stage10-test sh scripts/nadia-protective-safety-boundary.sh \
  --productivity-entry "$ledger_out/nadia-productivity-entry-stage10-test.txt" \
  --request-class software-development \
  --output "$safety_out" >/tmp/latticra-nadia-stage10-safety-test.out
NADIA_TOOL_PREFLIGHT_TIMESTAMP=stage10-test sh scripts/nadia-tool-authority-preflight.sh \
  --protective-safety "$safety_out/nadia-protective-safety-stage10-test.txt" \
  --tool-class metadata-read \
  --action "prepare inference readiness contract evidence" \
  --output "$tool_out" >/tmp/latticra-nadia-stage10-tool-test.out
NADIA_PROMPT_CONTRACT_TIMESTAMP=stage10-test sh scripts/nadia-prompt-evaluation-contract.sh \
  --tool-preflight "$tool_out/nadia-tool-preflight-stage10-test.txt" \
  --request-class software-development \
  --output "$contract_out" >/tmp/latticra-nadia-stage10-contract-test.out
NADIA_MODEL_REGISTRY_TIMESTAMP=stage10-test sh scripts/nadia-local-model-registry-contract.sh \
  --prompt-contract "$contract_out/nadia-prompt-contract-stage10-test.txt" \
  --runtime-profile "$runtime_out/nadia-runtime-profile-stage10-test.txt" \
  --model-id local-coding-assistant-candidate \
  --quantization q4_k_m \
  --source operator-provided-local \
  --license operator-review-required \
  --output "$registry_out" >/tmp/latticra-nadia-stage10-registry-test.out
NADIA_INFERENCE_READINESS_TIMESTAMP=stage10-test sh "$readiness_script" \
  --model-registry "$registry_out/nadia-model-registry-contract-stage10-test.txt" \
  --request-class software-development \
  --output "$out" >/tmp/latticra-nadia-stage10-readiness-test.out
readiness="$out/nadia-inference-readiness-contract-stage10-test.txt"

require_file "$readiness"
require_file "$out/latest-inference-readiness-contract.txt"
require_contains 'NADIA INFERENCE READINESS CONTRACT' "$readiness"
require_contains 'stage=10-inference-readiness-contract' "$readiness"
require_contains 'request_class=software-development' "$readiness"
require_contains 'inference_readiness_contract_status=contract_only' "$readiness"
require_contains 'inference_readiness_stage=contract-only' "$readiness"
require_contains 'inference_readiness_authority=0' "$readiness"
require_contains 'inference_ready=0' "$readiness"
require_contains 'model_registry_stage=9-local-model-registry-contract' "$readiness"
require_contains 'model_id=local-coding-assistant-candidate' "$readiness"
require_contains 'readiness_decision=blocked_contract_only' "$readiness"
require_contains 'requires_model_registry_contract=1' "$readiness"
require_contains 'requires_future_runtime_invocation_contract=1' "$readiness"
require_contains 'readiness_promotion_allowed=0' "$readiness"
require_contains 'runtime_invocation_authority=0' "$readiness"
require_contains 'token_generation_authority=0' "$readiness"
require_contains 'model_session_authority=0' "$readiness"
require_contains 'candidate_usable_for_inference=0' "$readiness"
require_contains 'candidate_selected_for_runtime=0' "$readiness"
require_contains 'model_selection_authority=0' "$readiness"
require_contains 'model_load_authority=0' "$readiness"
require_contains 'sexual_content_generation=0' "$readiness"
require_contains 'sexual_request_refusal=always' "$readiness"
require_contains 'prompt_materialized=0' "$readiness"
require_contains 'prompt_evaluation_authority=0' "$readiness"
require_contains 'prompt_evaluated=0' "$readiness"
require_contains 'model_runtime_invoked=0' "$readiness"
require_contains 'runtime_invoked=0' "$readiness"
require_contains 'inference_authority=0' "$readiness"
require_contains 'inference_performed=0' "$readiness"
require_contains 'model_weights_loaded=0' "$readiness"
require_contains 'model_weights_downloaded=0' "$readiness"
require_contains 'tool_execution_authority=0' "$readiness"
require_contains 'network_authority=0' "$readiness"

if NADIA_INFERENCE_READINESS_TIMESTAMP=stage10-reject sh "$readiness_script" \
  --model-registry "$registry_out/nadia-model-registry-contract-stage10-test.txt" \
  --request-class sexual \
  --output "$out" >/tmp/latticra-nadia-stage10-reject-test.out 2>/tmp/latticra-nadia-stage10-reject-test.err; then
  printf 'nadia inference readiness contract stage 10: sexual request class was not rejected\n' >&2
  exit 1
fi
require_contains 'outside Nadia inference-readiness boundary' /tmp/latticra-nadia-stage10-reject-test.err

printf 'nadia_inference_readiness_contract_stage_10: ok\n'
