#!/usr/bin/env sh
# SPDX-License-Identifier: AGPL-3.0-or-later
set -eu

tmpdir="$(mktemp -d "${TMPDIR:-/tmp}/latticra-nadia-stage11.XXXXXX")"
trap 'rm -rf "$tmpdir"' EXIT INT HUP TERM

require_file() {
  file="$1"
  if [ ! -f "$file" ]; then
    printf 'nadia runtime invocation contract stage 11: missing file: %s\n' "$file" >&2
    exit 1
  fi
}

require_contains() {
  pattern="$1"
  file="$2"
  if ! grep -Fq -- "$pattern" "$file"; then
    printf 'nadia runtime invocation contract stage 11: missing required pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

require_not_contains() {
  pattern="$1"
  file="$2"
  if grep -Fq -- "$pattern" "$file"; then
    printf 'nadia runtime invocation contract stage 11: forbidden pattern in %s: %s\n' "$file" "$pattern" >&2
    exit 1
  fi
}

stage11_doc='docs/NADIA_RUNTIME_INVOCATION_CONTRACT_STAGE_11.md'
stage11_status='docs/status/NADIA_RUNTIME_INVOCATION_CONTRACT_STAGE_11_STATUS.md'
foundation='docs/NADIA_OFFLINE_AI_FOUNDATION.md'
status_index='docs/status/README.md'
foundation_index='docs/FOUNDATION_INDEX.md'
readme='README.md'
root_status='STATUS.md'
current_status='docs/status/CURRENT_STATUS.md'
invocation_script='scripts/nadia-runtime-invocation-contract.sh'
stage11_guard='scripts/test-nadia-runtime-invocation-contract-stage-11.sh'
apply_script='installer/scripts/latticra-installer-apply.sh'
panel_config='installer/latticra-installer/src/config.rs'
panel_ui='installer/latticra-installer/src/ui.rs'
installer_readme='installer/README.md'
ui_model='installer/docs/UI_CONFIGURATION_MODEL.md'
components_manifest='installer/manifests/components.toml'
makefile='Makefile'

require_file "$stage11_doc"
require_file "$stage11_status"
require_file "$foundation"
require_file "$status_index"
require_file "$foundation_index"
require_file "$readme"
require_file "$root_status"
require_file "$current_status"
require_file "$invocation_script"
require_file "$stage11_guard"
require_file "$apply_script"
require_file "$panel_config"
require_file "$panel_ui"
require_file "$installer_readme"
require_file "$ui_model"
require_file "$components_manifest"
require_file "$makefile"

require_contains 'Status: Stage-11 implementation contract' "$stage11_doc"
require_contains 'nadia_stage_11_runtime_invocation_contract_present=1' "$stage11_doc"
require_contains 'runtime_invocation_contract_command=scripts/nadia-runtime-invocation-contract.sh' "$stage11_doc"
require_contains 'installed_runtime_invocation_contract_command=latticra-nadia runtime-invocation' "$stage11_doc"
require_contains 'runtime_invocation_authority=0' "$stage11_doc"
require_contains 'runtime_invocation_allowed=0' "$stage11_doc"
require_contains 'runtime_invoked=0' "$stage11_doc"
require_contains 'invocation_decision=blocked_contract_only' "$stage11_doc"
require_contains 'runtime_process_spawned=0' "$stage11_doc"
require_contains 'runtime_binary_executed=0' "$stage11_doc"
require_contains 'runtime_session_created=0' "$stage11_doc"
require_contains 'model_weights_loaded=0' "$stage11_doc"
require_contains 'token_generation_performed=0' "$stage11_doc"
require_contains 'sh scripts/test-nadia-runtime-invocation-contract-stage-11.sh' "$stage11_doc"

require_contains 'Status: implementation status record' "$stage11_status"
require_contains 'nadia_runtime_invocation_contract_generator_present=1' "$stage11_status"
require_contains 'runtime_invocation_contract_status=contract_only' "$stage11_status"
require_contains 'invocation_promotion_allowed=0' "$stage11_status"

require_contains 'Stage-11: Runtime Invocation Contract' "$foundation"
require_contains 'scripts/nadia-runtime-invocation-contract.sh' "$foundation"
require_contains 'NADIA_RUNTIME_INVOCATION_CONTRACT_STAGE_11.md' "$foundation_index"
require_contains 'NADIA_RUNTIME_INVOCATION_CONTRACT_STAGE_11_STATUS.md' "$status_index"
require_contains 'nadia_stage_11_runtime_invocation_contract_present=1' "$readme"
require_contains 'implementation_name=Nadia Witness Foundation' "$readme"
require_contains 'Latest Nadia runtime invocation contract Stage-11 note: 2026-05-25 CDT' "$root_status"
require_contains 'Latest Nadia runtime invocation contract Stage-11 note: 2026-05-25 CDT' "$current_status"
require_contains 'Nadia runtime invocation contract Stage-11' "$current_status"

require_contains 'NADIA RUNTIME INVOCATION CONTRACT' "$invocation_script"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$invocation_script"
require_contains 'public_name=Nadia' "$invocation_script"
require_contains 'runtime_invocation_authority=0' "$invocation_script"
require_contains 'runtime_invocation_allowed=0' "$invocation_script"
require_contains 'runtime_invoked=0' "$invocation_script"
require_contains 'runtime_process_spawned=0' "$invocation_script"
require_contains 'runtime_binary_executed=0' "$invocation_script"
require_contains 'runtime_session_created=0' "$invocation_script"
require_contains 'token_generation_authority=0' "$invocation_script"
require_contains 'token_generation_performed=0' "$invocation_script"
require_contains 'model_runtime_invoked=0' "$invocation_script"
require_contains 'inference_performed=0' "$invocation_script"
require_contains 'model_weights_loaded=0' "$invocation_script"
require_contains 'sexual_request_refusal=always' "$invocation_script"
require_not_contains 'curl ' "$invocation_script"
require_not_contains 'wget ' "$invocation_script"
require_not_contains 'ssh ' "$invocation_script"

require_contains 'runtime-invocation' "$apply_script"
require_contains 'scripts/nadia-runtime-invocation-contract.sh' "$apply_script"
require_contains 'runtime_invocation_contract_stage=11-runtime-invocation-contract' "$panel_config"
require_contains 'nadia runtime-invocation' "$panel_ui"
require_contains 'latticra-nadia runtime-invocation' "$installer_readme"
require_contains 'nadia runtime-invocation' "$ui_model"
require_contains 'runtime-invocation' "$components_manifest"
require_contains 'nadia-runtime-invocation' "$makefile"

out="$tmpdir/latticra-nadia-stage11-invocation-test"
context_out="$tmpdir/latticra-nadia-stage11-context-test"
runtime_out="$tmpdir/latticra-nadia-stage11-runtime-test"
plan_out="$tmpdir/latticra-nadia-stage11-plan-test"
mode_out="$tmpdir/latticra-nadia-stage11-mode-test"
ledger_out="$tmpdir/latticra-nadia-stage11-ledger-test"
safety_out="$tmpdir/latticra-nadia-stage11-safety-test"
tool_out="$tmpdir/latticra-nadia-stage11-tool-test"
contract_out="$tmpdir/latticra-nadia-stage11-contract-test"
registry_out="$tmpdir/latticra-nadia-stage11-registry-test"
readiness_out="$tmpdir/latticra-nadia-stage11-readiness-test"
context_stdout="$tmpdir/latticra-nadia-stage11-context-test.out"
runtime_stdout="$tmpdir/latticra-nadia-stage11-runtime-test.out"
plan_stdout="$tmpdir/latticra-nadia-stage11-plan-test.out"
mode_stdout="$tmpdir/latticra-nadia-stage11-mode-test.out"
ledger_stdout="$tmpdir/latticra-nadia-stage11-ledger-test.out"
safety_stdout="$tmpdir/latticra-nadia-stage11-safety-test.out"
tool_stdout="$tmpdir/latticra-nadia-stage11-tool-test.out"
contract_stdout="$tmpdir/latticra-nadia-stage11-contract-test.out"
registry_stdout="$tmpdir/latticra-nadia-stage11-registry-test.out"
readiness_stdout="$tmpdir/latticra-nadia-stage11-readiness-test.out"
invocation_stdout="$tmpdir/latticra-nadia-stage11-invocation-test.out"
reject_stdout="$tmpdir/latticra-nadia-stage11-reject-test.out"
reject_stderr="$tmpdir/latticra-nadia-stage11-reject-test.err"
mkdir -p "$out" "$context_out" "$runtime_out" "$plan_out" "$mode_out" "$ledger_out" "$safety_out" "$tool_out" "$contract_out" "$registry_out" "$readiness_out"
NADIA_CONTEXT_PACK_TIMESTAMP=stage11-test sh scripts/nadia-context-pack.sh --repo . --output "$context_out" >"$context_stdout"
NADIA_RUNTIME_PROFILE_TIMESTAMP=stage11-test sh scripts/nadia-runtime-profile.sh \
  --context-tokens 8192 \
  --memory-mib 16384 \
  --output "$runtime_out" >"$runtime_stdout"
NADIA_PROMPT_PLAN_TIMESTAMP=stage11-test sh scripts/nadia-prompt-plan.sh \
  --context-pack "$context_out/nadia-context-pack-stage11-test.txt" \
  --runtime-profile "$runtime_out/nadia-runtime-profile-stage11-test.txt" \
  --task "runtime invocation contract planning" \
  --output "$plan_out" >"$plan_stdout"
NADIA_MODE_VALIDATION_TIMESTAMP=stage11-test sh scripts/nadia-mode-validate.sh \
  --prompt-plan "$plan_out/nadia-prompt-plan-stage11-test.txt" \
  --mode ai-development \
  --output "$mode_out" >"$mode_stdout"
NADIA_PRODUCTIVITY_LEDGER_TIMESTAMP=stage11-test sh scripts/nadia-productivity-ledger.sh \
  --mode-validation "$mode_out/nadia-mode-validation-stage11-test.txt" \
  --outcome "accepted runtime invocation boundary" \
  --recommendation "keep invocation contract-only" \
  --output "$ledger_out" >"$ledger_stdout"
NADIA_PROTECTIVE_SAFETY_TIMESTAMP=stage11-test sh scripts/nadia-protective-safety-boundary.sh \
  --productivity-entry "$ledger_out/nadia-productivity-entry-stage11-test.txt" \
  --request-class software-development \
  --output "$safety_out" >"$safety_stdout"
NADIA_TOOL_PREFLIGHT_TIMESTAMP=stage11-test sh scripts/nadia-tool-authority-preflight.sh \
  --protective-safety "$safety_out/nadia-protective-safety-stage11-test.txt" \
  --tool-class metadata-read \
  --action "prepare runtime invocation contract evidence" \
  --output "$tool_out" >"$tool_stdout"
NADIA_PROMPT_CONTRACT_TIMESTAMP=stage11-test sh scripts/nadia-prompt-evaluation-contract.sh \
  --tool-preflight "$tool_out/nadia-tool-preflight-stage11-test.txt" \
  --request-class software-development \
  --output "$contract_out" >"$contract_stdout"
NADIA_MODEL_REGISTRY_TIMESTAMP=stage11-test sh scripts/nadia-local-model-registry-contract.sh \
  --prompt-contract "$contract_out/nadia-prompt-contract-stage11-test.txt" \
  --runtime-profile "$runtime_out/nadia-runtime-profile-stage11-test.txt" \
  --model-id local-coding-assistant-candidate \
  --quantization q4_k_m \
  --source operator-provided-local \
  --license operator-review-required \
  --output "$registry_out" >"$registry_stdout"
NADIA_INFERENCE_READINESS_TIMESTAMP=stage11-test sh scripts/nadia-inference-readiness-contract.sh \
  --model-registry "$registry_out/nadia-model-registry-contract-stage11-test.txt" \
  --request-class software-development \
  --output "$readiness_out" >"$readiness_stdout"
NADIA_RUNTIME_INVOCATION_TIMESTAMP=stage11-test sh "$invocation_script" \
  --inference-readiness "$readiness_out/nadia-inference-readiness-contract-stage11-test.txt" \
  --request-class software-development \
  --output "$out" >"$invocation_stdout"
invocation="$out/nadia-runtime-invocation-contract-stage11-test.txt"

require_file "$invocation"
require_file "$out/latest-runtime-invocation-contract.txt"
require_contains 'NADIA RUNTIME INVOCATION CONTRACT' "$invocation"
require_contains 'system_name=Latticra Nadia Witness Foundation' "$invocation"
require_contains 'public_name=Nadia' "$invocation"
require_contains 'stage=11-runtime-invocation-contract' "$invocation"
require_contains 'request_class=software-development' "$invocation"
require_contains 'runtime_invocation_contract_status=contract_only' "$invocation"
require_contains 'runtime_invocation_stage=contract-only' "$invocation"
require_contains 'runtime_invocation_authority=0' "$invocation"
require_contains 'runtime_invocation_allowed=0' "$invocation"
require_contains 'runtime_invoked=0' "$invocation"
require_contains 'inference_readiness_stage=10-inference-readiness-contract' "$invocation"
require_contains 'model_registry_stage=9-local-model-registry-contract' "$invocation"
require_contains 'model_id=local-coding-assistant-candidate' "$invocation"
require_contains 'invocation_decision=blocked_contract_only' "$invocation"
require_contains 'requires_inference_readiness_contract=1' "$invocation"
require_contains 'requires_model_registry_contract=1' "$invocation"
require_contains 'requires_prompt_contract=1' "$invocation"
require_contains 'requires_future_model_load_contract=1' "$invocation"
require_contains 'invocation_promotion_allowed=0' "$invocation"
require_contains 'runtime_process_spawn_authority=0' "$invocation"
require_contains 'runtime_binary_execution_authority=0' "$invocation"
require_contains 'runtime_session_authority=0' "$invocation"
require_contains 'token_generation_authority=0' "$invocation"
require_contains 'runtime_process_spawned=0' "$invocation"
require_contains 'runtime_binary_executed=0' "$invocation"
require_contains 'runtime_session_created=0' "$invocation"
require_contains 'token_generation_performed=0' "$invocation"
require_contains 'candidate_usable_for_inference=0' "$invocation"
require_contains 'candidate_selected_for_runtime=0' "$invocation"
require_contains 'model_selection_authority=0' "$invocation"
require_contains 'model_load_authority=0' "$invocation"
require_contains 'sexual_content_generation=0' "$invocation"
require_contains 'sexual_request_refusal=always' "$invocation"
require_contains 'prompt_materialized=0' "$invocation"
require_contains 'prompt_evaluation_authority=0' "$invocation"
require_contains 'prompt_evaluated=0' "$invocation"
require_contains 'model_runtime_invoked=0' "$invocation"
require_contains 'inference_authority=0' "$invocation"
require_contains 'inference_performed=0' "$invocation"
require_contains 'model_weights_loaded=0' "$invocation"
require_contains 'model_weights_downloaded=0' "$invocation"
require_contains 'tool_execution_authority=0' "$invocation"
require_contains 'network_authority=0' "$invocation"

if NADIA_RUNTIME_INVOCATION_TIMESTAMP=stage11-reject sh "$invocation_script" \
  --inference-readiness "$readiness_out/nadia-inference-readiness-contract-stage11-test.txt" \
  --request-class sexual \
  --output "$out" >"$reject_stdout" 2>"$reject_stderr"; then
  printf 'nadia runtime invocation contract stage 11: sexual request class was not rejected\n' >&2
  exit 1
fi
require_contains 'outside Nadia runtime-invocation boundary' "$reject_stderr"

printf 'nadia_runtime_invocation_contract_stage_11: ok\n'
